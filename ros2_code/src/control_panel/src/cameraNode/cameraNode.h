#pragma once

#include "../common/enum.h"
#include "../common/settings.h"
#include "camera_settings_service/srv/camera_settings_service.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <QDebug>
#include <QMutex>
#include <QObject>
#include <QQueue>
#include <QThread>
#include <atomic>

using CameraSettingsSrv = camera_settings_service::srv::CameraSettingsService;

class CameraNode : public QThread {
    Q_OBJECT
public:
    enum CommandState {
        Fail = -1,
        Add = 0,
        Running = 1,
        Success = 2
    };

    struct Command {
        Command(int64_t id, CameraSettingsSrv::Request::SharedPtr request) : id(id), request(request) {
        }
        int64_t id;
        CameraSettingsSrv::Request::SharedPtr request;
    };

    CameraNode(const std::string &node_name, const std::string &node_nammspace, QObject *parent = nullptr);
    ~CameraNode();

    bool add_camera_settings_service(int64_t id, CameraSettingsSrv::Request::SharedPtr request);
    bool is_connected() const;

protected:
    void run() override;
    void recv_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg);

signals:
    void cameraSettingsServiceResponsed(CameraSettingsSrv::Response::SharedPtr);
    void imageMsgReceived(const sensor_msgs::msg::CompressedImage::SharedPtr);
    void commandStateChanged(int64_t, int);
    void connectedChanged(bool);
    void nodeClosed();

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<CameraSettingsSrv>::SharedPtr camera_settings_client_;
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr image_subscription_;

    std::atomic<bool> connected_;
    int try_connect_cnt_ = 0;

    QQueue<Command> command_queue_;
    QMutex mutex_;

    void _run_command(const Command &command);
    void _send_heartbeat_request();
    void _ask_camera_settings_service(CameraSettingsSrv::Request::SharedPtr request);
};