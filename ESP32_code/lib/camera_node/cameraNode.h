#pragma once

#include "Arduino.h"
#include "cameraControl.h"
#include "enum.h"
#include "esp_camera.h"
#include "fb_gfx.h"
#include "rclc/rclc.h"
#include "rclc/timer.h" // 包含 rclc_system_time_now 的声明
#include "rosidl_runtime_c/primitives_sequence_functions.h"
#include "settings.h"
#include "soc/rtc_cntl_reg.h" // disable brownout problems
#include "soc/soc.h"          // disable brownout problems
#include <Arduino.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <micro_ros_platformio.h>
#include <micro_ros_utilities/string_utilities.h>
#include <micro_ros_utilities/type_utilities.h>
#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <rcutils/error_handling.h>
#include <rosidl_runtime_c/string_functions.h>
#include <sensor_msgs/msg/compressed_image.h>
#include <sensor_msgs/msg/image.h>
#include <std_msgs/msg/int32.h>
extern "C" {
#include "camera_settings_service/srv/camera_settings_service.h"
}

class CameraNode {

private:
    CameraNode();
    ~CameraNode();

public:
    CameraNode(const CameraNode &) = delete;
    CameraNode &operator=(const CameraNode &) = delete;

    void set_enable_series_capture(bool status);
    bool get_enable_series_capture();

    static CameraNode &get_instance();
    void init(const std::string &node_name, const std::string &node_namespace, const std::string &wifi_name, const std::string &wifi_passward, const std::string &ip, const uint16_t port);
    void start_task();
    void stop_task();

    void capture_image();

    rcl_publisher_t *get_image_publisher();

    bool is_connected();

    void reset_timer();

private:
    std::string node_name_, node_namespace_;

    rcl_node_t node_;
    rclc_executor_t executor;
    rcl_allocator_t allocator_;
    rclc_support_t support_;
    micro_ros_agent_locator locator_;

    std::string ip_;
    uint16_t port_;
    std::string wifi_name_;
    std::string wifi_passward_;

    rcl_publisher_t image_publisher_;
    rcl_service_t camera_settings_service_;
    rcl_timer_t timer_;

    // WiFiUDP wifi_udp_;

    sensor_msgs__msg__CompressedImage image_msg_;
    camera_fb_t *image_ = nullptr;

    bool support_initialized_ = false;
    bool node_initialized_ = false;
    bool executor_initialized_ = false;
    bool timer_initialized_ = false;
    bool camera_settings_service_initialized_ = false;
    bool image_publisher_initialized_ = false;

    bool enable_task_run_ = false;
    bool enable_series_capture_ = true;

    CameraControl *cameraControl_ = nullptr;

    camera_settings_service__srv__CameraSettingsService_Request camera_settings_request_;
    camera_settings_service__srv__CameraSettingsService_Response camera_settings_response_;

    bool _create_timer();
    void _destroy_timer();

    volatile bool connected = false;

    bool init();
    void clean();
    bool is_enable_task_run();

    static void camera_settings_service_callback(const void *req, void *res);
    static void timer_callback(rcl_timer_t *timer, int64_t last_call_time);
    static void camera_node_task(void *args);
};
