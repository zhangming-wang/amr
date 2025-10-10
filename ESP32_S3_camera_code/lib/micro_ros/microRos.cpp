#include "microRos.h"

MicroRos::MicroRos() {
    allocator_ = rcl_get_default_allocator();
}
MicroRos::~MicroRos() {
    stop_task();
}

MicroRos &MicroRos::get_instance() {
    static MicroRos microRos;
    return microRos;
}

void MicroRos::init(const std::string &node_name, const std::string &node_namespace, const std::string &wifi_name, const std::string &wifi_passward, const std::string &ip, const uint16_t port) {
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

    cameraControl_ = &ESP32Cam::get_instance();
}

bool MicroRos::is_connected() {
    return connected;
}

void MicroRos::clean() {
    _destroy_timer();

    rcl_ret_t ret;

    if (camera_settings_service_initialized_) {
        ret = rcl_service_fini(&camera_settings_service_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rcl_service_fini motion_params_service error: %d\n", ret);
        }
        camera_settings_service_initialized_ = false;
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

bool MicroRos::init() {
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
        ret = rclc_publisher_init_default(&image_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, CompressedImage), esp32_camera_image_topic_name); // esp32_camera_image_topic_name
        if (ret != RCL_RET_OK) {
            Serial.printf("image_publisher_:rclc_publisher_init_default:%d\n", ret);
            return false;
        }
        image_publisher_initialized_ = true;
    }

    // if (!camera_settings_service_initialized_) {
    //     ret = rclc_service_init_default(&camera_settings_service_initialized_, &node_, ROSIDL_GET_SRV_TYPE_SUPPORT(motion_params_service, srv, MotionParamsService), camera_settings_service);
    //     if (ret != RCL_RET_OK) {
    //         Serial.printf("rclc_service_init_default motion_params_service:%d\n", ret);
    //         return false;
    //     }
    //     ret = rclc_executor_add_service(&executor, &motion_params_service_, &motion_params_request_, &motion_params_response_, motion_params_service_callback);
    //     if (ret != RCL_RET_OK) {
    //         Serial.printf("rclc_executor_add_service motion_params_service:%d\n", ret);
    //         ret = rcl_service_fini(&camera_settings_service_initialized_, &node_);
    //         if (ret != RCL_RET_OK) {
    //             Serial.printf("rcl_service_fini motion_params_service error: %d\n", ret);
    //         }
    //         return false;
    //     }
    //     camera_settings_service_initialized_ = true;
    // }

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

bool MicroRos::_create_timer() {
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

void MicroRos::_destroy_timer() {
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

void MicroRos::set_enable_series_capture(bool status) {
    enable_series_capture_ = status;
    reset_timer();
}

bool MicroRos::get_enable_series_capture() {
    return enable_series_capture_;
}

rcl_publisher_t *MicroRos::get_image_publisher() {
    return &image_publisher_;
}

void MicroRos::capture_image() {
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
    }
    // Serial.printf("发布图像耗时: %d ms\n", millis() - begin_time);

    cameraControl_->release_photo(image_);

    // Serial.printf("释放图像耗时: %d ms\n", millis() - begin_time);
}

void MicroRos::reset_timer() {
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
        Serial.println("enable_pub_motion_status is false,create timer stopped!");
    }
}

void MicroRos::start_task() {
    if (enable_task_run_ == false) {
        enable_task_run_ = true;
        BaseType_t microros_task_create_result = xTaskCreatePinnedToCore(microros_task, "microros_task", 65536, this, 1, NULL, 1);
        if (microros_task_create_result == pdPASS) {
            Serial.println("microros_task created successfully.");
        } else {
            Serial.printf("Failed to create microros_task. Error code: %d\n", microros_task_create_result);
        }
    }
}

void MicroRos::stop_task() {
    enable_task_run_ = false;
}

bool MicroRos::is_enable_task_run() {
    return enable_task_run_;
}

void MicroRos::microros_task(void *args) {
    MicroRos *microRos = static_cast<MicroRos *>(args);
    bool init_success = false;
    microRos->connected = false;
    while (microRos->is_enable_task_run()) {
        if (!init_success) {
            if (!microRos->init()) {
                Serial.println("microros init failed, try again...");
                vTaskDelay(pdMS_TO_TICKS(500));
                continue;
            } else {
                Serial.println("microros task is running...");
                init_success = true;
            }
        }
        rclc_executor_spin_some(&microRos->executor, RCL_MS_TO_NS(MicroRos::get_instance().cameraControl_->get_params().milliseconds));
        if (rmw_uros_ping_agent(10, 10) != RCL_RET_OK) {
            microRos->connected = false;
            Serial.println("microros is disconnected, reconnecting...");
            init_success = false;
            vTaskDelay(pdMS_TO_TICKS(500));
        } else if (microRos->connected == false) {
            microRos->connected = true;
        }
    }
    microRos->clean();
    vTaskDelete(NULL);
}

void MicroRos::timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
    MicroRos::get_instance().capture_image();
}