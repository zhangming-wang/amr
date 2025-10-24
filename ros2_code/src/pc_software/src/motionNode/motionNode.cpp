#include "motionNode.h"
#include "../common/enum.h"

MotionNode::MotionNode(const std::string &node_name, const std::string &node_namespace, QObject *parent) : QThread(parent), node_(std::make_shared<rclcpp::Node>(node_name, node_namespace)) {
    qRegisterMetaType<int64_t>("const int64_t");
    qRegisterMetaType<std_msgs::msg::String::SharedPtr>("const std_msgs::msg::String::SharedPtr");
    qRegisterMetaType<nav_msgs::msg::Odometry::SharedPtr>("const nav_msgs::msg::Odometry::SharedPtr");
    qRegisterMetaType<MotionStatusMsg::SharedPtr>("const MotionStatusMsg::SharedPtr");
    qRegisterMetaType<MotionSettingsSrv::Response::SharedPtr>("const MotionSettingsSrv::Response::SharedPtr");

    micro_ros_is_online_.store(false);

    rclcpp::QoS reliable_qos(rclcpp::KeepLast(1));
    reliable_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
    rclcpp::QoS best_effort_qos(rclcpp::KeepLast(1));
    best_effort_qos.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);

    std::string service_name, motion_status_topic_name, serial_msg_topic_name;
    std::string ns(esp32_motion_node_namespace);
    std::string srv(esp32_motion_settings_service_name);
    std::string motion_status_msg(esp32_motion_status_topic_name);
    std::string serial_msg(esp32_motion_serial_msg_topic_name);

    if (ns.empty()) {       // 处理命名空间为空的情况
        service_name = srv; // 直接使用服务名，让ROS2自动处理根路径
        motion_status_topic_name = motion_status_msg;
        serial_msg_topic_name = serial_msg;
    } else {
        if (ns.front() != '/') { // 确保命名空间以单斜杠开头
            service_name = "/" + ns;
            motion_status_topic_name = "/" + ns;
            serial_msg_topic_name = "/" + ns;
        } else {
            service_name = ns;
            motion_status_topic_name = ns;
            serial_msg_topic_name = ns;
        }
        if (!service_name.empty() && service_name.back() != '/') { // 添加服务名，确保中间只有一个斜杠
            service_name += "/";
            motion_status_topic_name += "/";
            serial_msg_topic_name += "/";
        }
        service_name += srv;
        motion_status_topic_name += motion_status_msg;
        serial_msg_topic_name += serial_msg;
    }

    serial_msg_subscription_ = node_->create_subscription<std_msgs::msg::String>(serial_msg_topic_name, best_effort_qos, std::bind(&MotionNode::recv_serial_msg, this, std::placeholders::_1));
    motion_status_subscription_ = node_->create_subscription<MotionStatusMsg>(motion_status_topic_name, best_effort_qos, std::bind(&MotionNode::recv_motion_status_msg, this, std::placeholders::_1));
    // odom_subscription_ = node_->create_subscription<nav_msgs::msg::Odometry>("/odom", qos, std::bind(&MotionNode::recv_odom_msg, this, std::placeholders::_1));

    motion_settings_client_ = node_->create_client<MotionSettingsSrv>(service_name);

    twist_publisher_ = node_->create_publisher<geometry_msgs::msg::Twist>(pc_motion_cmd_vel_topic_name, best_effort_qos);
}

bool MotionNode::micro_ros_is_online() {
    return micro_ros_is_online_.load();
}

void MotionNode::run() {
    Command command = Command(0, -1, nullptr, nullptr);
    rclcpp::Rate rate(5000);

    const std::chrono::seconds heartbeat_interval(1);               // 心跳间隔1秒
    auto current_heartbeat_time = std::chrono::steady_clock::now(); // 上次次发送心跳的时间
    auto last_heartbeat_time = current_heartbeat_time - heartbeat_interval;

    while (rclcpp::ok()) {
        rclcpp::spin_some(node_);
        {
            QMutexLocker locker(&mutex_);
            if (!command_queue_.isEmpty()) {
                command = command_queue_.front();
                command_queue_.pop_front();
            } else {
                command.reset();
            }
        }
        if (command.isValid()) {
            _run_command(command);
        } else {
            if (current_heartbeat_time - last_heartbeat_time >= heartbeat_interval) {
                _send_heartbeat_request();
                last_heartbeat_time = current_heartbeat_time;
            }
        }

        rate.sleep();

        current_heartbeat_time = std::chrono::steady_clock::now();
    }

    micro_ros_is_online_.store(false);

    emit nodeClosed();
}

void MotionNode::_send_heartbeat_request() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::HeartBeat;
    _ask_motion_settings_service(request);
}

void MotionNode::_run_command(const Command &command) { // const Command &command
    if (command.type == CommandType::Topic && command.twist_topic) {
        // emit commandStateChanged(command.id, CommandState::Running);
        _publish_twist(command.twist_topic);
        // emit commandStateChanged(command.id, CommandState::Success);
    } else if (command.type == CommandType::Service && command.motion_settings_request) {
        emit commandStateChanged(command.id, CommandState::Running);
        _ask_motion_settings_service(command.motion_settings_request);
    }
}

bool MotionNode::add_twist(int64_t id, std::shared_ptr<geometry_msgs::msg::Twist> twist) {
    if (micro_ros_is_online()) {
        QMutexLocker locker(&mutex_);
        command_queue_.clear();
        command_queue_.push_back(Command(id, CommandType::Topic, twist, nullptr));
        return true;
    } else {
        return false;
    }
}

bool MotionNode::add_motion_settings_service(int64_t id, MotionSettingsSrv::Request::SharedPtr request) {
    if (micro_ros_is_online()) {
        QMutexLocker locker(&mutex_);
        command_queue_.push_back(Command(id, CommandType::Service, nullptr, request));
        return true;
    } else {
        return false;
    }
}

void MotionNode::_publish_twist(std::shared_ptr<geometry_msgs::msg::Twist> twist) {
    if (micro_ros_is_online()) {
        twist_publisher_->publish(*twist);
    }
}

void MotionNode::_ask_motion_settings_service(MotionSettingsSrv::Request::SharedPtr request) {
    if (motion_settings_client_->service_is_ready()) {
        // motion_settings_client_->async_send_request(request,
        //                                           [this, request](rclcpp::Client<MotionSettingsSrv>::SharedFuture future) {
        //                                               if (future.valid()) {
        //                                                   emit motionSettingsServiceResponsed(future.get());
        //                                               } else {
        //                                                   emit commandStateChanged(request->id, CommandState::Fail);
        //                                               }
        //                                           });

        auto future_result = motion_settings_client_->async_send_request(request);
        auto ret = rclcpp::spin_until_future_complete(node_, future_result, std::chrono::milliseconds(1000));
        if (request->mode == MotionService::Type::HeartBeat) {
            if (ret == rclcpp::FutureReturnCode::SUCCESS) {
                try_connect_cnt_ = 0;
                if (!micro_ros_is_online()) {
                    emit connectChanged(true);
                    micro_ros_is_online_.store(true);
                }
            } else {
                try_connect_cnt_ += 1;
                if (try_connect_cnt_ >= 3) {
                    emit connectChanged(false);
                    micro_ros_is_online_.store(false);
                }
            }
        } else {
            if (ret == rclcpp::FutureReturnCode::SUCCESS) {
                emit motionSettingsServiceResponsed(future_result.get());
            } else {
                emit commandStateChanged(request->id, CommandState::Fail);
            }
        }
    } else {
        if (request->mode == MotionService::Type::HeartBeat) {
            try_connect_cnt_ += 1;
            if (try_connect_cnt_ >= 3) {
                emit connectChanged(false);
                micro_ros_is_online_.store(false);
            }
        } else {
            emit commandStateChanged(request->id, CommandState::Fail);
        }
    }
}

void MotionNode::recv_motion_status_msg(const MotionStatusMsg::SharedPtr msg) {
    emit motionStatusMsgChanged(msg);
}

// void MotionNode::recv_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg) {
//     emit odomMsgChanged(msg);
// }

void MotionNode::recv_serial_msg(const std_msgs::msg::String::SharedPtr msg) {
    emit serialMsgChanged(msg);
}
