#pragma once

#include "geometry_msgs/msg/twist.hpp"
#include "motion_params_service/srv/motion_params_service.hpp"
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
    Command(int64_t id, int type, std::shared_ptr<geometry_msgs::msg::Twist> twist, motion_params_service::srv::MotionParamsService::Request::SharedPtr request) : id(id), type(type), twist_topic(twist), motion_params_request(request) {
    }
    void reset() {
        id = 0;
        type = CommandType::NoType;
        twist_topic = nullptr;
        motion_params_request = nullptr;
    }

    bool isValid() {
        return type != CommandType::NoType && (twist_topic || motion_params_request);
    }
    int64_t id;
    int type;
    std::shared_ptr<geometry_msgs::msg::Twist> twist_topic;
    motion_params_service::srv::MotionParamsService::Request::SharedPtr motion_params_request;
};

class NodeQThread : public QThread {
    Q_OBJECT
public:
    NodeQThread(const std::string &node_name, QObject *parent = nullptr);
    bool add_twist(int64_t id, std::shared_ptr<geometry_msgs::msg::Twist> twist);
    bool add_motion_params_service(int64_t id, motion_params_service::srv::MotionParamsService::Request::SharedPtr request);
    bool micro_ros_is_online();

protected:
    void run();

signals:
    void motionStatusMsgChanged(motion_status_msgs::msg::MotionStatus::SharedPtr);
    // void odomMsgChanged(nav_msgs::msg::Odometry::SharedPtr);
    void serialMsgChanged(std_msgs::msg::String::SharedPtr);

    void motionParamsServiceResponsed(motion_params_service::srv::MotionParamsService::Response::SharedPtr);
    void restartedWatchDogTimer();
    void stoppedWatchDogTimer();
    void microRosConnected();

    void commandStateChanged(int64_t id, int state);

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_publisher_;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr serial_msg_subscription_;
    rclcpp::Subscription<motion_status_msgs::msg::MotionStatus>::SharedPtr motion_status_subscription_;
    // rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_subscription_;

    rclcpp::Client<motion_params_service::srv::MotionParamsService>::SharedPtr motion_params_client_;

    std::atomic<bool> micro_ros_is_online_;
    int try_connect_cnt_ = 0;

    void recv_motion_status_msg(const motion_status_msgs::msg::MotionStatus::SharedPtr msg);
    // void recv_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg);
    void recv_serial_msg(const std_msgs::msg::String::SharedPtr msg);

    void _publish_twist(std::shared_ptr<geometry_msgs::msg::Twist> twist);
    void _ask_motion_params_service(motion_params_service::srv::MotionParamsService::Request::SharedPtr request);
    void _send_heartbeat_request();

    void _run_command(const Command &command);

    QQueue<Command> command_queue_;
    QMutex mutex_;
};
