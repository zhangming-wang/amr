#pragma once

#include "../common/enum.h"
#include "../common/settings.h"
#include "../common/tools.h"
#include "geometry_msgs/msg/twist.hpp"
#include "motion_settings_service/srv/motion_settings_service.hpp"
#include "motion_status_msgs/msg/motion_status.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <QApplication>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QQueue>
#include <QThread>
#include <QTimer>
#include <atomic>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

using MotionSettingsSrv = motion_settings_service::srv::MotionSettingsService;
using MotionStatusMsg = motion_status_msgs::msg::MotionStatus;

class MotionNode : public QThread {
    Q_OBJECT
public:
    enum CommandState {
        Fail = -1,
        Add = 0,
        Running = 1,
        Success = 2,
        SerialMsg = 3
    };

    enum CommandType {
        NoType = -1,
        Topic = 0,
        Service = 1,
    };

    struct Command {
        Command(int64_t id, int type, std::shared_ptr<geometry_msgs::msg::Twist> twist, MotionSettingsSrv::Request::SharedPtr request) : id(id), type(type), twist_topic(twist), motion_settings_request(request) {
        }
        void reset() {
            id = 0;
            type = CommandType::NoType;
            twist_topic = nullptr;
            motion_settings_request = nullptr;
        }

        bool isValid() {
            return type != CommandType::NoType && (twist_topic || motion_settings_request);
        }
        int64_t id;
        int type;
        std::shared_ptr<geometry_msgs::msg::Twist> twist_topic;
        MotionSettingsSrv::Request::SharedPtr motion_settings_request;
    };

    MotionNode(const std::string &node_name, const std::string &node_namespace, QObject *parent = nullptr);
    bool add_twist(int64_t id, std::shared_ptr<geometry_msgs::msg::Twist> twist);
    bool add_motion_settings_service(int64_t id, MotionSettingsSrv::Request::SharedPtr request);
    bool micro_ros_is_online();

protected:
    void run();

signals:
    void motionStatusMsgChanged(MotionStatusMsg::SharedPtr);
    // void odomMsgChanged(nav_msgs::msg::Odometry::SharedPtr);
    void serialMsgChanged(std_msgs::msg::String::SharedPtr);

    void motionSettingsServiceResponsed(MotionSettingsSrv::Response::SharedPtr);
    void restartedWatchDogTimer();
    void stoppedWatchDogTimer();
    void connectChanged(bool);

    void commandStateChanged(int64_t id, int state);

    void nodeClosed();

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_publisher_;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr serial_msg_subscription_;
    rclcpp::Subscription<MotionStatusMsg>::SharedPtr motion_status_subscription_;
    // rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_subscription_;

    rclcpp::Client<MotionSettingsSrv>::SharedPtr motion_settings_client_;

    std::atomic<bool> micro_ros_is_online_;
    int try_connect_cnt_ = 0;

    void recv_motion_status_msg(const MotionStatusMsg::SharedPtr msg);
    // void recv_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg);
    void recv_serial_msg(const std_msgs::msg::String::SharedPtr msg);

    void _publish_twist(std::shared_ptr<geometry_msgs::msg::Twist> twist);
    void _ask_motion_settings_service(MotionSettingsSrv::Request::SharedPtr request);
    void _send_heartbeat_request();

    void _run_command(const Command &command);

    QQueue<Command> command_queue_;
    QMutex mutex_;
};
