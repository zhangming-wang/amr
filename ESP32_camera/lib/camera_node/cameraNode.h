#pragma once

#include "Arduino.h"
#include "cameraControl.h"
#include "enum.h"
#include "esp_camera.h"
#include <sensor_msgs/msg/compressed_image.h>
#include <sensor_msgs/msg/image.h>
extern "C" {
#include "camera_settings_service/srv/camera_settings_service.h"
}
#include "baseNode.h"
#include "baseTask.h"
#include "settings.h"
#include "system.h"

class CameraNode : public BaseNode<CameraNode> {

    friend class Singleton<CameraNode>;

protected:
    CameraNode();

    bool init_micro_ros() override;
    void clean_micro_ros() override;

public:
    void set_enable_series_capture(bool status);
    bool get_enable_series_capture();

    void publish_image_msg();

private:
    rcl_publisher_t image_publisher_;
    rcl_service_t camera_settings_service_;
    rcl_timer_t publish_image_timer_;

    bool camera_settings_service_initialized_ = false;
    bool image_publisher_initialized_ = false;
    bool publish_image_timer_initialized_ = false;

    bool enable_series_capture_ = true;
    std::string camera_image_topic_name_, camera_service_name_;

    CameraControl *cameraControl_ = nullptr;
    sensor_msgs__msg__CompressedImage image_msg_;

    camera_settings_service__srv__CameraSettingsService_Request camera_settings_request_;
    camera_settings_service__srv__CameraSettingsService_Response camera_settings_response_;

    bool _create_publish_image_timer();
    void _destroy_publish_image_timer();

    static void camera_settings_service_callback(const void *req, void *res);
    static void publish_image_timer_callback(rcl_timer_t *timer, int64_t last_call_time);
};