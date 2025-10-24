#include "cameraNode.h"

CameraNode::CameraNode() {
    allocator_ = rcl_get_default_allocator();
}
CameraNode::~CameraNode() {
    stop_task();
}

CameraNode &CameraNode::get_instance() {
    static CameraNode instance;
    return instance;
}

void CameraNode::init(const std::string &node_name, const std::string &node_namespace, const std::string &wifi_name, const std::string &wifi_passward, const std::string &ip, const uint16_t port) {
    node_name_ = node_name;
    node_namespace_ = node_namespace;
    wifi_name_ = wifi_name;
    wifi_passward_ = wifi_passward;
    ip_ = ip;
    port_ = port;

    IPAddress agent_ip;
    agent_ip.fromString(ip.c_str());
    locator_.address = agent_ip;
    locator_.port = port;

    cameraControl_ = &CameraControl::get_instance();
}

bool CameraNode::is_connected() {
    return connected;
}

void CameraNode::clean() {
    _destroy_timer();

    rcl_ret_t ret;

    if (camera_settings_service_initialized_) {
        ret = rcl_service_fini(&camera_settings_service_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rcl_service_fini camera_settings_service error: %d\n", ret);
        }
        camera_settings_service_initialized_ = false;
    }

    if (image_publisher_initialized_) {
        ret = rcl_publisher_fini(&image_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("image_publisher:rcl_publisher_fini error: : %d\n", ret);
        }
        image_publisher_initialized_ = false;
    }

    if (executor_initialized_) {
        ret = rclc_executor_fini(&executor);
        if (ret != RCL_RET_OK) {
            Serial.printf("executor_initialized_ error: %d\n", ret);
        }
        executor_initialized_ = false;
    }
    if (node_initialized_) {
        ret = rcl_node_fini(&node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rcl_node_fini error: %d\n", ret);
        }
        node_initialized_ = false;
    }
    if (support_initialized_) {
        ret = rclc_support_fini(&support_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_support_fini error: %d\n", ret);
        }
        support_initialized_ = false;
    }
}

bool CameraNode::init() {
    clean();
    int num_handles = 2;
    bool init_success = true;
    IPAddress agent_ip;
    rcl_ret_t ret;
    agent_ip.fromString(ip_.c_str());

    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    auto status = rmw_uros_set_custom_transport(
        false,
        (void *)&locator_,
        platformio_transport_open,
        platformio_transport_close,
        platformio_transport_write,
        platformio_transport_read);

    if (status != 0) {
        Serial.printf("rmw_uros_set_custom_transport:%d\n", status);
        return false;
    }

    // set_microros_wifi_transports(const_cast<char *>(wifi_name_.c_str()), const_cast<char *>(wifi_passward_.c_str()), agent_ip, port_);

    if (!support_initialized_) {
        ret = rclc_support_init(&support_, 0, NULL, &allocator_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_support_init:%d\n", ret);
            return false;
        }
        support_initialized_ = true;
    }

    while (!rmw_uros_epoch_synchronized()) {
        rmw_uros_sync_session(1000);
        delay(10);
    }

    if (!node_initialized_) {
        node_ = rcl_get_zero_initialized_node();
        ret = rclc_node_init_default(&node_, node_name_.c_str(), node_namespace_.c_str(), &support_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rcl_get_zero_initialized_node:%d\n", ret);
            return false;
        }
        node_initialized_ = true;
    }

    if (!executor_initialized_) {
        ret = rclc_executor_init(&executor, &support_.context, num_handles, &allocator_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_executor_init:%d\n", ret);
            return false;
        }
        executor_initialized_ = true;
    }

    if (!image_publisher_initialized_) {
        ret = rclc_publisher_init_default(&image_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, CompressedImage), esp32_camera_image_topic_name);
        if (ret != RCL_RET_OK) {
            Serial.printf("image_publisher_:rclc_publisher_init_default:%d\n", ret);
            return false;
        }
        image_publisher_initialized_ = true;
    }

    if (!camera_settings_service_initialized_) {
        ret = rclc_service_init_default(&camera_settings_service_, &node_, ROSIDL_GET_SRV_TYPE_SUPPORT(camera_settings_service, srv, CameraSettingsService), esp32_camera_settings_service_name);
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_service_init_default camera_settings_service:%d\n", ret);
            return false;
        }
        ret = rclc_executor_add_service(&executor, &camera_settings_service_, &camera_settings_request_, &camera_settings_response_, camera_settings_service_callback);
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_executor_add_service camera_settings_service:%d\n", ret);
            ret = rcl_service_fini(&camera_settings_service_, &node_);
            if (ret != RCL_RET_OK) {
                Serial.printf("rcl_service_fini camera_settings_service error: %d\n", ret);
            }
            return false;
        }
        camera_settings_service_initialized_ = true;
    }

    if (enable_series_capture_) {
        if (!_create_timer()) {
            return false;
        }
    }

    char const *frame_id = "cam_frame";
    char const *format_str = "jpeg";

    image_msg_.header.frame_id = micro_ros_string_utilities_init(frame_id);
    image_msg_.format = micro_ros_string_utilities_init(format_str);

    return true;
}

bool CameraNode::_create_timer() {
    if (!timer_initialized_) {
        auto ret = rclc_timer_init_default(&timer_, &support_, RCL_MS_TO_NS(cameraControl_->get_params().milliseconds), timer_callback); //
        if (ret != RCL_RET_OK) {
            Serial.println("rclc_timer_init_default.");
            return false;
        }
        ret = rclc_executor_add_timer(&executor, &timer_);
        if (ret != RCL_RET_OK) {
            Serial.println("rclc_executor_add_timer.");
            ret = rcl_timer_fini(&timer_);
            if (ret != RCL_RET_OK) {
                Serial.println("rcl_timer_fini error.");
            }
            return false;
        }
        timer_initialized_ = true;
    }
    return true;
}

void CameraNode::_destroy_timer() {
    if (timer_initialized_) {
        auto ret = rclc_executor_remove_timer(&executor, &timer_);
        if (ret != RCL_RET_OK) {
            Serial.println("rclc_executor_remove_timer error.");
        }
        ret = rcl_timer_fini(&timer_);
        if (ret != RCL_RET_OK) {
            Serial.println("rcl_timer_fini error.");
        }
        timer_initialized_ = false;
    }
}

void CameraNode::set_enable_series_capture(bool status) {
    enable_series_capture_ = status;
    reset_timer();
}

bool CameraNode::get_enable_series_capture() {
    return enable_series_capture_;
}

rcl_publisher_t *CameraNode::get_image_publisher() {
    return &image_publisher_;
}

void CameraNode::capture_image() {
    // static unsigned long begin_time = 0;
    // unsigned long current_time = millis();
    // Serial.printf("间隔时间: %d ms， 帧率: %.2f\n", current_time - begin_time, 1000.0 / (current_time - begin_time));
    // begin_time = current_time;

    image_ = cameraControl_->capture_photo();
    if (!image_) {
        Serial.println("错误: 接收到空图像指针");
        return;
    }

    // Serial.printf("拍照耗时: %d ms, 图像大小: %d bytes\n", millis() - begin_time, image_->len);

    if (is_connected()) {
        image_msg_.header.stamp.sec = millis() / 1000;
        image_msg_.header.stamp.nanosec = (millis() % 1000) * 1000000;
        image_msg_.data.capacity = image_->len;
        image_msg_.data.data = (uint8_t *)image_->buf;
        image_msg_.data.size = image_->len;

        rcl_ret_t ret = rcl_publish(&image_publisher_, &image_msg_, NULL);
        if (ret != RCL_RET_OK) {
            Serial.printf("error: 发布图像失败，错误码: %d ，图像大小: %d\n", ret, image_msg_.data.size);
        }

        // if (wifi_udp_.beginPacket(wifi_IP, wifi_port) == 0) {
        //     Serial.println("UDP beginPacket failed!");
        // } else {
        //     size_t written = wifi_udp_.write(image_->buf, image_->len);
        //     if (written != image_->len) {
        //         Serial.println("UDP write incomplete!");
        //     } else {
        //         if (wifi_udp_.endPacket() == 0) {
        //             Serial.println("UDP endPacket failed!");
        //         }
        //     }
        // }
    }
    // Serial.printf("发布图像耗时: %d ms\n", millis() - begin_time);

    cameraControl_->release_photo(image_);

    // Serial.printf("释放图像耗时: %d ms\n", millis() - begin_time);
}

void CameraNode::reset_timer() {
    if (enable_series_capture_) {
        if (timer_initialized_) {
            int64_t period_ns;
            rcl_ret_t ret = rcl_timer_get_period(&timer_, &period_ns);
            if (ret != RCL_RET_OK || RCL_MS_TO_NS(cameraControl_->get_params().milliseconds) != period_ns) {
                _destroy_timer();
            }
        }
        if (_create_timer()) {
            Serial.println("create timer success.");
        } else {
            Serial.println("create timer failed.");
        }
    } else {
        _destroy_timer();
        Serial.println("enable_pub_image is false,create timer stopped!");
    }
}

void CameraNode::start_task() {
    if (enable_task_run_ == false) {
        enable_task_run_ = true;
        BaseType_t microros_task_create_result = xTaskCreatePinnedToCore(camera_node_task, "camera_node_task", 65536, this, 1, NULL, 0);
        if (microros_task_create_result == pdPASS) {
            Serial.println("camera_node_task created successfully.");
        } else {
            Serial.printf("Failed to create camera_node_task. Error code: %d\n", microros_task_create_result);
        }
    }
}

void CameraNode::stop_task() {
    enable_task_run_ = false;
}

bool CameraNode::is_enable_task_run() {
    return enable_task_run_;
}

void CameraNode::camera_node_task(void *args) {
    CameraNode *cameraNode = static_cast<CameraNode *>(args);
    bool init_success = false;
    cameraNode->connected = false;
    while (cameraNode->is_enable_task_run()) {
        if (!init_success) {
            if (!cameraNode->init()) {
                Serial.println("microros init failed, try again...");
                vTaskDelay(pdMS_TO_TICKS(500));
                continue;
            } else {
                Serial.println("microros task is running...");
                // CameraNode::get_instance().cameraControl_->init(false);
                init_success = true;
            }
        }
        rclc_executor_spin_some(&cameraNode->executor, RCL_MS_TO_NS(cameraNode->cameraControl_->get_params().milliseconds));
        if (rmw_uros_ping_agent(10, 10) != RCL_RET_OK) {
            cameraNode->connected = false;
            Serial.println("microros is disconnected, reconnecting...");
            init_success = false;
            vTaskDelay(pdMS_TO_TICKS(500));
        } else if (cameraNode->connected == false) {
            cameraNode->connected = true;
        }
    }
    cameraNode->clean();
    vTaskDelete(NULL);
}

void CameraNode::timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
    CameraNode::get_instance().capture_image();
}

void CameraNode::camera_settings_service_callback(const void *req, void *res) {
    const camera_settings_service__srv__CameraSettingsService_Request *request = (const camera_settings_service__srv__CameraSettingsService_Request *)req;
    camera_settings_service__srv__CameraSettingsService_Response *response = (camera_settings_service__srv__CameraSettingsService_Response *)res;

    CameraNode &instance = CameraNode::get_instance();
    if (request->mode == CameraService::Type::HeartBeat) {
        ;
    } else if (request->mode == CameraService::Type::Restart) {
        instance.cameraControl_->init(false);
    } else if (request->mode == CameraService::Type::Capture) {
        instance.capture_image();
    } else if (request->mode == CameraService::Type::SetEnableSeriesCapture) {
        instance.set_enable_series_capture(request->enable_series_capture);
    }

    else if (request->mode == CameraService::Type::ReadParams) {
        auto params = instance.cameraControl_->get_params();
        response->enable_series_capture = instance.enable_series_capture_;
        response->milliseconds = params.milliseconds;
        response->pixformat = params.pixformat;
        response->framesize = params.status.framesize;
        response->quality = params.status.quality;
        response->brightness = params.status.brightness;
        response->contrast = params.status.contrast;
        response->saturation = params.status.saturation;
        response->sharpness = params.status.sharpness;
        response->denoise = params.status.denoise;
        response->special_effect = params.status.special_effect;
        response->wb_mode = params.status.wb_mode;
        response->awb = params.status.awb;
        response->awb_gain = params.status.awb_gain;
        response->aec = params.status.aec;
        response->aec2 = params.status.aec2;
        response->ae_level = params.status.ae_level;
        response->aec_value = params.status.aec_value;
        response->agc = params.status.agc;
        response->agc_gain = params.status.agc_gain;
        response->gainceiling = params.status.gainceiling;
        response->bpc = params.status.bpc;
        response->wpc = params.status.wpc;
        response->raw_gma = params.status.raw_gma;
        response->lenc = params.status.lenc;
        response->hmirror = params.status.hmirror;
        response->vflip = params.status.vflip;
        response->dcw = params.status.dcw;
        response->colorbar = params.status.colorbar;
    } else if (request->mode == CameraService::Type::WriteParams) {
        auto params = instance.cameraControl_->get_params();

        params.milliseconds = request->milliseconds;
        params.pixformat = static_cast<pixformat_t>(request->pixformat);
        params.status.framesize = static_cast<framesize_t>(request->framesize);
        params.status.quality = request->quality;
        params.status.brightness = request->brightness;
        params.status.contrast = request->contrast;
        params.status.saturation = request->saturation;
        params.status.sharpness = request->sharpness;
        params.status.denoise = request->denoise;
        params.status.special_effect = request->special_effect;
        params.status.wb_mode = request->wb_mode;
        params.status.awb = request->awb;
        params.status.awb_gain = request->awb_gain;
        params.status.aec = request->aec;
        params.status.aec2 = request->aec2;
        params.status.ae_level = request->ae_level;
        params.status.aec_value = request->aec_value;
        params.status.agc = request->agc;
        params.status.agc_gain = request->agc_gain;
        params.status.gainceiling = request->gainceiling;
        params.status.bpc = request->bpc;
        params.status.wpc = request->wpc;
        params.status.raw_gma = request->raw_gma;
        params.status.lenc = request->lenc;
        params.status.hmirror = request->hmirror;
        params.status.vflip = request->vflip;
        params.status.dcw = request->dcw;
        params.status.colorbar = request->colorbar;

        instance.cameraControl_->set_params(params);
        instance.reset_timer();

        params = instance.cameraControl_->get_params();
        response->enable_series_capture = instance.enable_series_capture_;
        response->milliseconds = params.milliseconds;
        response->pixformat = params.pixformat;
        response->framesize = params.status.framesize;
        response->quality = params.status.quality;
        response->brightness = params.status.brightness;
        response->contrast = params.status.contrast;
        response->saturation = params.status.saturation;
        response->sharpness = params.status.sharpness;
        response->denoise = params.status.denoise;
        response->special_effect = params.status.special_effect;
        response->wb_mode = params.status.wb_mode;
        response->awb = params.status.awb;
        response->awb_gain = params.status.awb_gain;
        response->aec = params.status.aec;
        response->aec2 = params.status.aec2;
        response->ae_level = params.status.ae_level;
        response->aec_value = params.status.aec_value;
        response->agc = params.status.agc;
        response->agc_gain = params.status.agc_gain;
        response->gainceiling = params.status.gainceiling;
        response->bpc = params.status.bpc;
        response->wpc = params.status.wpc;
        response->raw_gma = params.status.raw_gma;
        response->lenc = params.status.lenc;
        response->hmirror = params.status.hmirror;
        response->vflip = params.status.vflip;
        response->dcw = params.status.dcw;
        response->colorbar = params.status.colorbar;
    } else if (request->mode == CameraService::Type::SaveParams) {
        instance.cameraControl_->save_params();
    }

    else if (request->mode == CameraService::Type::ReadConfig) {
        auto config = instance.cameraControl_->get_config();

        response->pin_pwdn = config.pin_pwdn;
        response->pin_reset = config.pin_reset;
        response->pin_xclk = config.pin_xclk;
        response->pin_sccb_sda = config.pin_sccb_sda;
        response->pin_sccb_scl = config.pin_sccb_scl;
        response->pin_d7 = config.pin_d7;
        response->pin_d6 = config.pin_d6;
        response->pin_d5 = config.pin_d5;
        response->pin_d4 = config.pin_d4;
        response->pin_d3 = config.pin_d3;
        response->pin_d2 = config.pin_d2;
        response->pin_d1 = config.pin_d1;
        response->pin_d0 = config.pin_d0;
        response->xclk_freq_hz = config.xclk_freq_hz;
        response->fb_count = config.fb_count;
        response->frame_size = config.frame_size;
        response->pixel_format = config.pixel_format;
        response->ledc_timer = config.ledc_timer;
        response->ledc_channel = config.ledc_channel;
        response->grab_mode = config.grab_mode;
        response->fb_location = config.fb_location;
#if CONFIG_CAMERA_CONVERTER_ENABLED
        response->conv_mode = config.conv_mode;
#endif
    } else if (request->mode == CameraService::Type::WriteConfig) {
        auto config = instance.cameraControl_->get_config();

        config.pin_pwdn = request->pin_pwdn;
        config.pin_reset = request->pin_reset;
        config.pin_xclk = request->pin_xclk;
        config.pin_sccb_sda = request->pin_sccb_sda;
        config.pin_sccb_scl = request->pin_sccb_scl;
        config.pin_d7 = request->pin_d7;
        config.pin_d6 = request->pin_d6;
        config.pin_d5 = request->pin_d5;
        config.pin_d4 = request->pin_d4;
        config.pin_d3 = request->pin_d3;
        config.pin_d2 = request->pin_d2;
        config.pin_d1 = request->pin_d1;
        config.pin_d0 = request->pin_d0;
        config.xclk_freq_hz = request->xclk_freq_hz;
        config.fb_count = request->fb_count;
        config.frame_size = static_cast<framesize_t>(request->frame_size);
        config.pixel_format = static_cast<pixformat_t>(request->pixel_format);
        config.ledc_timer = static_cast<ledc_timer_t>(request->ledc_timer);
        config.ledc_channel = static_cast<ledc_channel_t>(request->ledc_channel);
        config.grab_mode = static_cast<camera_grab_mode_t>(request->grab_mode);
        config.fb_location = static_cast<camera_fb_location_t>(request->fb_location);
#if CONFIG_CAMERA_CONVERTER_ENABLED
        config.conv_mode = static_cast<camera_conv_mode_t>(request->conv_mode);
#endif
        instance._destroy_timer();
        instance.cameraControl_->set_config(config);
        instance._create_timer();
    } else if (request->mode == CameraService::Type::SaveConfig) {
        instance.cameraControl_->save_config();
    }

    response->state = request->mode;
    response->id = request->id;
}