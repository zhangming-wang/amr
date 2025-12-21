#include "cameraNode.h"

CameraNode::CameraNode() {
    task_name_ = "camera_node_task";
    num_handles_ = 3;
    stack_size_ = 16384;

    node_name_ = esp32_camera_node_name;
    node_namespace_ = esp32_camera_node_namespace;
    serial_msg_topic_name_ = constructNodeName(esp32_camera_node_namespace, esp32_camera_serial_msg_topic_name);
    heartbeat_topic_name_ = constructNodeName(esp32_camera_node_namespace, esp32_camera_heartbeat_topic_name);

    camera_image_topic_name_ = constructNodeName(esp32_camera_node_namespace, esp32_camera_image_topic_name);
    camera_service_name_ = constructNodeName(esp32_camera_node_namespace, esp32_camera_settings_service_name);

    cameraControl_ = &CameraControl::instance();

    image_msg_.header.frame_id = micro_ros_string_utilities_init("camera_link");
    image_msg_.format = micro_ros_string_utilities_init("jpeg");
}

bool CameraNode::init_micro_ros() {
    rcl_ret_t ret;
    if (!image_publisher_initialized_) {
        ret = rclc_publisher_init_default(&image_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, CompressedImage), camera_image_topic_name_.c_str());
        if (ret != RCL_RET_OK) {
            Serial.printf("image_publisher_:rclc_publisher_init_default:%d\n", ret);
            return false;
        }
        image_publisher_initialized_ = true;
    }

    if (!camera_settings_service_initialized_) {
        ret = rclc_service_init_default(&camera_settings_service_, &node_, ROSIDL_GET_SRV_TYPE_SUPPORT(camera_settings_service, srv, CameraSettingsService), camera_service_name_.c_str());
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_service_init_default camera_settings_service:%d\n", ret);
            return false;
        }
        ret = rclc_executor_add_service(&executor_, &camera_settings_service_, &camera_settings_request_, &camera_settings_response_, camera_settings_service_callback);
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
        _create_publish_image_timer();
    }

    return true;
}

void CameraNode::clean_micro_ros() {
    _destroy_publish_image_timer();

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
}

void CameraNode::set_enable_series_capture(bool status) {
    enable_series_capture_ = status;
    if (enable_series_capture_) {
        _create_publish_image_timer();
    } else {
        _destroy_publish_image_timer();
    }
}

bool CameraNode::get_enable_series_capture() {
    return enable_series_capture_;
}

void CameraNode::publish_image_msg() {
    if (!connected()) {
        return;
    }
    if (!image_publisher_initialized_) {
        return;
    }

    auto image_ = cameraControl_->capture_image();
    if (!image_) {
        return;
    }

    auto now_ns = get_now_ns();
    image_msg_.header.stamp.sec = static_cast<int32_t>(now_ns / 1000000000ULL);
    image_msg_.header.stamp.nanosec = static_cast<uint32_t>(now_ns % 1000000000ULL);

    image_msg_.data.capacity = image_->len;
    image_msg_.data.data = (uint8_t *)image_->buf;
    image_msg_.data.size = image_->len;

    rcl_ret_t ret = rcl_publish(&image_publisher_, &image_msg_, NULL);
    if (ret != RCL_RET_OK) {
        Serial.printf("error: 发布图像失败，错误码: %d ，图像大小: %d\n", ret, image_msg_.data.size);
    }

    cameraControl_->release_image();
}

void CameraNode::camera_settings_service_callback(const void *req, void *res) {
    const camera_settings_service__srv__CameraSettingsService_Request *request = (const camera_settings_service__srv__CameraSettingsService_Request *)req;
    camera_settings_service__srv__CameraSettingsService_Response *response = (camera_settings_service__srv__CameraSettingsService_Response *)res;

    CameraNode &instance = CameraNode::instance();
    if (request->mode == CameraService::Type::HeartBeat) {
        ;
    } else if (request->mode == CameraService::Type::Restart) {
        restart_device();
    } else if (request->mode == CameraService::Type::Capture) {
        instance.publish_image_msg();
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

        bool need_restart_timer = false;
        if (request->milliseconds != params.milliseconds) {
            params.milliseconds = request->milliseconds;
            need_restart_timer = true;
        }

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

        if (need_restart_timer && instance.enable_series_capture_) {
            instance._create_publish_image_timer();
        }

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
        instance.cameraControl_->set_config(config);
    } else if (request->mode == CameraService::Type::SaveConfig) {
        instance.cameraControl_->save_config();
    }

    response->state = request->mode;
    response->id = request->id;
}

void CameraNode::publish_image_timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
    CameraNode::instance().publish_image_msg();
}

void CameraNode::_create_publish_image_timer() {
    if (publish_image_timer_initialized_) {
        _destroy_publish_image_timer();
    }
    rcl_ret_t ret = rclc_timer_init_default(&publish_image_timer_, &support_, RCL_MS_TO_NS(cameraControl_->get_params().milliseconds), publish_image_timer_callback);
    if (ret != RCL_RET_OK) {
        Serial.printf("publish_image_timer_: rclc_timer_init_default error: %d\n", ret);
        return;
    }
    ret = rclc_executor_add_timer(&executor_, &publish_image_timer_);
    if (ret != RCL_RET_OK) {
        Serial.printf("publish_image_timer_: rclc_executor_add_timer error: %d\n", ret);
        ret = rcl_timer_fini(&publish_image_timer_);
        return;
    }
    publish_image_timer_initialized_ = true;
}

void CameraNode::_destroy_publish_image_timer() {
    if (publish_image_timer_initialized_) {
        rcl_ret_t ret = rclc_executor_remove_timer(&executor_, &publish_image_timer_);
        if (ret != RCL_RET_OK) {
            Serial.printf("publish_image_timer_: rclc_executor_remove_timer error: %d\n", ret);
        }
        ret = rcl_timer_fini(&publish_image_timer_);
        if (ret != RCL_RET_OK) {
            Serial.printf("publish_image_timer_: rcl_timer_fini error: %d\n", ret);
        }
        publish_image_timer_initialized_ = false;
    }
}