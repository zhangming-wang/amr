#include "cameraNode.h"

CameraNode::CameraNode(const std::string &node_name, const std::string &node_nammspace, QObject *parent) : QThread(parent), node_(std::make_shared<rclcpp::Node>(node_name, node_nammspace)) {
    qRegisterMetaType<int64_t>("const int64_t");
    qRegisterMetaType<CameraSettingsSrv::Response::SharedPtr>("const CameraSettingsSrv::Response::SharedPtr");
    qRegisterMetaType<sensor_msgs::msg::CompressedImage::SharedPtr>("const sensor_msgs::msg::CompressedImage::SharedPtr");

    connected_.store(false);

    rclcpp::QoS reliable_qos(rclcpp::KeepLast(10));
    reliable_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
    rclcpp::QoS best_effort_qos(rclcpp::KeepLast(1));
    best_effort_qos.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);

    // 优化版本：减少字符串构造，处理路径格式
    std::string service_name, topic_name;
    std::string ns(esp32_camera_node_namespace);
    std::string srv(esp32_camera_settings_service_name);
    std::string msg(esp32_camera_image_topic_name);

    if (ns.empty()) {       // 处理命名空间为空的情况
        service_name = srv; // 直接使用服务名，让ROS2自动处理根路径
        topic_name = msg;
    } else {
        if (ns.front() != '/') { // 确保命名空间以单斜杠开头
            service_name = "/" + ns;
            topic_name = "/" + ns;
        } else {
            service_name = ns;
            topic_name = ns;
        }
        if (!service_name.empty() && service_name.back() != '/') { // 添加服务名，确保中间只有一个斜杠
            service_name += "/";
            topic_name += "/";
        }
        service_name += srv;
        topic_name += msg;
    }
    camera_settings_client_ = node_->create_client<CameraSettingsSrv>(service_name); // 创建服务客户端
    image_subscription_ = node_->create_subscription<sensor_msgs::msg::CompressedImage>(topic_name, reliable_qos, std::bind(&CameraNode::recv_image_msg, this, std::placeholders::_1));
}

CameraNode::~CameraNode() {
}

bool CameraNode::is_connected() const {
    return connected_.load();
}

bool CameraNode::add_camera_settings_service(int64_t id, CameraSettingsSrv::Request::SharedPtr request) {
    if (is_connected()) {
        QMutexLocker locker(&mutex_);
        command_queue_.push_back(Command(id, request));
        return true;
    } else {
        return false;
    }
}

void CameraNode::recv_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    emit imageMsgReceived(msg);
}

void CameraNode::run() {
    Command command(0, nullptr);
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
                command = Command(0, nullptr);
            }
        }
        if (command.request) {
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
    connected_.store(false);

    emit nodeClosed();
}

void CameraNode::_send_heartbeat_request() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::HeartBeat;
    _ask_camera_settings_service(request);
}

void CameraNode::_run_command(const Command &command) { // const Command &command
    if (command.request) {
        emit commandStateChanged(command.id, CommandState::Running);
        _ask_camera_settings_service(command.request);
    }
}

void CameraNode::_ask_camera_settings_service(CameraSettingsSrv::Request::SharedPtr request) {
    if (camera_settings_client_->service_is_ready()) {
        auto future_result = camera_settings_client_->async_send_request(request);
        auto ret = rclcpp::spin_until_future_complete(node_, future_result, std::chrono::milliseconds(1000));
        if (request->mode == CameraService::Type::HeartBeat) {
            if (ret == rclcpp::FutureReturnCode::SUCCESS) {
                try_connect_cnt_ = 0;
                if (!connected_.load()) {
                    connected_.store(true);
                    emit connectedChanged(true);
                }
            } else {
                try_connect_cnt_ += 1;
                if (try_connect_cnt_ >= 3) {
                    connected_.store(false);
                    emit connectedChanged(false);
                }
            }
        } else {
            if (ret == rclcpp::FutureReturnCode::SUCCESS) {
                emit cameraSettingsServiceResponsed(future_result.get());
            } else {
                emit commandStateChanged(request->id, CommandState::Fail);
            }
        }
    } else {
        if (request->mode == CameraService::Type::HeartBeat) {
            try_connect_cnt_ += 1;
            if (try_connect_cnt_ >= 3) {
                connected_.store(false);
                emit connectedChanged(false);
            }
        }
    }
}
