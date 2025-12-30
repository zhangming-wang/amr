#pragma once

#include "camera_settings_service/srv/camera_settings_service.hpp"
#include "motion_settings_service/srv/motion_settings_service.hpp"
#include "rclcpp/qos.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/string.hpp"
#include <QMutexLocker>
#include <QQueue>
#include <QThread>
#include <QTimer>
#include <atomic>

class NodeThread : public QThread {
    Q_OBJECT
public:
    NodeThread(rclcpp::Node::SharedPtr node, const std::string &serial_msg_topic_name, const std::string &heartbeat_topic_name, QObject *parent = nullptr);
    virtual ~NodeThread() = default;
    bool connected();

signals:
    void serialMsgChanged(std_msgs::msg::String::SharedPtr);
    void connectChanged(bool);
    void nodeClosed();

    void restartTimerSignal();

protected:
    void run() override;
    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr serial_msg_subscription_;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr heartbeat_subscription_;

    QTimer heartbeat_timer_;
    std::atomic<bool> connected_{false};

    rclcpp::QoS reliable_qos_{rclcpp::QoS(10).reliable()};
    rclcpp::QoS best_effort_qos_{rclcpp::QoS(1).best_effort()};

    void recv_serial_msg(const std_msgs::msg::String::SharedPtr msg);
    void recv_heartbeat_msg(const std_msgs::msg::Empty::SharedPtr msg);
};