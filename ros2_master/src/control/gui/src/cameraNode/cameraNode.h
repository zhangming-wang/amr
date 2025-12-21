#pragma once

#include "../baseNode/nodeThread.h"
#include "../common/settings.h"
#include "../common/system.h"
#include "camera_settings_service/srv/camera_settings_service.hpp"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <sensor_msgs/msg/image.hpp>

using CameraSettingsSrv = camera_settings_service::srv::CameraSettingsService;

class CameraNode : public NodeThread {
    Q_OBJECT
public:
    CameraNode(QObject *parent = nullptr);
    ~CameraNode();

    void ask_service_response(CameraSettingsSrv::Request::SharedPtr request);

protected:
    void recv_compressed_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
    void publish_raw_image(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
    void publish_compressed_image(const sensor_msgs::msg::CompressedImage::SharedPtr msg);

signals:
    void CompressedImageMsgReceived(const sensor_msgs::msg::CompressedImage::SharedPtr);
    void rawImageMsgReceived(const sensor_msgs::msg::Image::SharedPtr);
    void serviceResponsed(uint64_t id, CameraSettingsSrv::Response::SharedPtr);

private:
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr compressed_image_subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr raw_image_publisher_;
    rclcpp::Client<CameraSettingsSrv>::SharedPtr service_client_;
};