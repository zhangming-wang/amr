#include "nodeqthread.h"
#include "../common/enum.h"

NodeQThread::NodeQThread(const std::string &node_name, QObject *parent) : QThread(parent), node_(std::make_shared<rclcpp::Node>(node_name)) {
    qRegisterMetaType<int64_t>("const int64_t");
    qRegisterMetaType<std_msgs::msg::String::SharedPtr>("const std_msgs::msg::String::SharedPtr");
    qRegisterMetaType<nav_msgs::msg::Odometry::SharedPtr>("const nav_msgs::msg::Odometry::SharedPtr");
    qRegisterMetaType<motion_status_msgs::msg::MotionStatus::SharedPtr>("const motion_status_msgs::msg::MotionStatus::SharedPtr");
    qRegisterMetaType<motion_params_service::srv::MotionParamsService::Response::SharedPtr>("const motion_params_service::srv::MotionParamsService::Response::SharedPtr");

    micro_ros_is_online_.store(false);

    rclcpp::QoS reliable_qos(rclcpp::KeepLast(1));
    reliable_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
    rclcpp::QoS best_effort_qos(rclcpp::KeepLast(1));
    best_effort_qos.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);

    twist_publisher_ = node_->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", best_effort_qos);

    serial_msg_subscription_ = node_->create_subscription<std_msgs::msg::String>("/serial_msg_topic", best_effort_qos, std::bind(&NodeQThread::recv_serial_msg, this, std::placeholders::_1));
    motion_status_subscription_ = node_->create_subscription<motion_status_msgs::msg::MotionStatus>("/motion_status_topic", best_effort_qos, std::bind(&NodeQThread::recv_motion_status_msg, this, std::placeholders::_1));
    // odom_subscription_ = node_->create_subscription<nav_msgs::msg::Odometry>("/odom", qos, std::bind(&NodeQThread::recv_odom_msg, this, std::placeholders::_1));

    motion_params_client_ = node_->create_client<motion_params_service::srv::MotionParamsService>("/motion_params_service");
}

bool NodeQThread::micro_ros_is_online() {
    return micro_ros_is_online_.load();
}

void NodeQThread::run() {
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
}

void NodeQThread::_send_heartbeat_request() {
    motion_params_service::srv::MotionParamsService::Request::SharedPtr request(std::make_shared<motion_params_service::srv::MotionParamsService::Request>());
    request->mode = ServiceType::HeartBeat;
    _ask_motion_params_service(request);
}

void NodeQThread::_run_command(const Command &command) { // const Command &command
    if (command.type == CommandType::Topic && command.twist_topic) {
        // emit commandStateChanged(command.id, CommandState::Running);
        _publish_twist(command.twist_topic);
        // emit commandStateChanged(command.id, CommandState::Success);
    } else if (command.type == CommandType::Service && command.motion_params_request) {
        emit commandStateChanged(command.id, CommandState::Running);
        _ask_motion_params_service(command.motion_params_request);
    }
}

bool NodeQThread::add_twist(int64_t id, std::shared_ptr<geometry_msgs::msg::Twist> twist) {
    if (micro_ros_is_online()) {
        QMutexLocker locker(&mutex_);
        command_queue_.clear();
        command_queue_.push_back(Command(id, CommandType::Topic, twist, nullptr));
        return true;
    } else {
        return false;
    }
}

bool NodeQThread::add_motion_params_service(int64_t id, motion_params_service::srv::MotionParamsService::Request::SharedPtr request) {
    if (micro_ros_is_online()) {
        QMutexLocker locker(&mutex_);
        command_queue_.push_back(Command(id, CommandType::Service, nullptr, request));
        return true;
    } else {
        return false;
    }
}

void NodeQThread::_publish_twist(std::shared_ptr<geometry_msgs::msg::Twist> twist) {
    if (micro_ros_is_online()) {
        twist_publisher_->publish(*twist);
    }
}

void NodeQThread::_ask_motion_params_service(motion_params_service::srv::MotionParamsService::Request::SharedPtr request) {
    if (motion_params_client_->service_is_ready()) {
        // motion_params_client_->async_send_request(request,
        //                                           [this, request](rclcpp::Client<motion_params_service::srv::MotionParamsService>::SharedFuture future) {
        //                                               if (future.valid()) {
        //                                                   emit motionParamsServiceResponsed(future.get());
        //                                               } else {
        //                                                   emit commandStateChanged(request->id, CommandState::Fail);
        //                                               }
        //                                           });

        auto future_result = motion_params_client_->async_send_request(request);
        auto ret = rclcpp::spin_until_future_complete(node_, future_result, std::chrono::milliseconds(3000));
        if (request->mode == ServiceType::HeartBeat) {
            if (ret == rclcpp::FutureReturnCode::SUCCESS) {
                try_connect_cnt_ = 0;
                if (!micro_ros_is_online()) {
                    emit microRosConnected();
                    micro_ros_is_online_.store(true);
                }
            } else {
                try_connect_cnt_ += 1;
                if (try_connect_cnt_ >= 3) {
                    micro_ros_is_online_.store(false);
                }
            }
        } else {
            if (ret == rclcpp::FutureReturnCode::SUCCESS) {
                emit motionParamsServiceResponsed(future_result.get());
            } else {
                emit commandStateChanged(request->id, CommandState::Fail);
            }
        }
    } else {
        if (request->mode == ServiceType::HeartBeat) {
            try_connect_cnt_ += 1;
            if (try_connect_cnt_ >= 3) {
                micro_ros_is_online_.store(false);
            }
        } else {
            emit commandStateChanged(request->id, CommandState::Fail);
        }
    }
}

void NodeQThread::recv_motion_status_msg(const motion_status_msgs::msg::MotionStatus::SharedPtr msg) {
    emit motionStatusMsgChanged(msg);
}

// void NodeQThread::recv_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg) {
//     emit odomMsgChanged(msg);
// }

void NodeQThread::recv_serial_msg(const std_msgs::msg::String::SharedPtr msg) {
    emit serialMsgChanged(msg);
}
