#include "nodeThread.h"

NodeThread::NodeThread(rclcpp::Node::SharedPtr node,
                       const std::string &serial_msg_topic_name,
                       const std::string &heartbeat_topic_name,
                       QObject *parent)
    : node_(node),
      QThread(parent) {
    qRegisterMetaType<uint64_t>("const uint64_t");
    qRegisterMetaType<std_msgs::msg::String::SharedPtr>("const std_msgs::msg::String::SharedPtr");

    connected_.store(false);

    serial_msg_subscription_ = node_->create_subscription<std_msgs::msg::String>(serial_msg_topic_name, best_effort_qos_, std::bind(&NodeThread::recv_serial_msg, this, std::placeholders::_1));
    heartbeat_subscription_ = node_->create_subscription<std_msgs::msg::Empty>(heartbeat_topic_name, best_effort_qos_, std::bind(&NodeThread::recv_heartbeat_msg, this, std::placeholders::_1));

    heartbeat_timer_.setInterval(3000);
    heartbeat_timer_.setSingleShot(false);
    connect(&heartbeat_timer_, &QTimer::timeout, this, [this]() { // 心跳超时处理
        connected_.store(false);
        emit connectChanged(false);
    });
    connect(this, &NodeThread::restartTimerSignal, &heartbeat_timer_, static_cast<void (QTimer::*)()>(&QTimer::start));
    heartbeat_timer_.start();
}

bool NodeThread::connected() {
    return connected_.load();
}

void NodeThread::run() {
    rclcpp::Rate rate(200);

    while (rclcpp::ok()) {
        rclcpp::spin_some(node_);
        rate.sleep();
    }

    connected_.store(false);
    emit nodeClosed();
}

void NodeThread::recv_serial_msg(const std_msgs::msg::String::SharedPtr msg) {
    emit serialMsgChanged(msg);
}

void NodeThread::recv_heartbeat_msg(const std_msgs::msg::Empty::SharedPtr msg) {
    emit restartTimerSignal();
    if (connected_.load() == false) {
        connected_.store(true);
        emit connectChanged(true);
    }
}
