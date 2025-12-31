#include "cameraNode.h"

CameraNode::CameraNode(QObject *parent)
    : NodeThread(std::make_shared<rclcpp::Node>(pc_camera_node_name, pc_camera_node_namespace),
                 constructNodeName(esp32_camera_node_namespace, esp32_camera_serial_msg_topic_name),
                 constructNodeName(esp32_camera_node_namespace, esp32_camera_heartbeat_topic_name),
                 parent) {
    qRegisterMetaType<sensor_msgs::msg::CompressedImage::SharedPtr>("const sensor_msgs::msg::CompressedImage::SharedPtr");
    qRegisterMetaType<CameraSettingsSrv::Response::SharedPtr>("const CameraSettingsSrv::Response::SharedPtr");
    qRegisterMetaType<sensor_msgs::msg::Image::SharedPtr>("const sensor_msgs::msg::Image::SharedPtr");

    service_client_ = node_->create_client<CameraSettingsSrv>(constructNodeName(esp32_camera_node_namespace, esp32_camera_settings_service_name));

    raw_image_publisher_ = node_->create_publisher<sensor_msgs::msg::Image>(camera_image_raw_topic_name, best_effort_qos_);
    compressed_image_subscription_ = node_->create_subscription<sensor_msgs::msg::CompressedImage>(constructNodeName(esp32_camera_node_namespace, esp32_camera_image_topic_name), reliable_qos_, std::bind(&CameraNode::recv_compressed_image_msg, this, std::placeholders::_1));
    yolo_detect_image_subscription_ = node_->create_subscription<sensor_msgs::msg::Image>(yolo_detect_image_topic_name, best_effort_qos_, std::bind(&CameraNode::recv_yolo_detect_image, this, std::placeholders::_1));
}

void CameraNode::recv_compressed_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    cv::Mat img = cv::imdecode(
        cv::Mat(msg->data), cv::IMREAD_COLOR);

    if (img.empty()) {
        RCLCPP_WARN(node_->get_logger(), "Decode compressed image failed");
        return;
    }

    // 3. cv::Mat → ROS Image
    cv_bridge::CvImage cv_img;
    cv_img.header = msg->header; // 保留时间戳 + frame_id
    cv_img.encoding = "bgr8";    // ESP32 摄像头通常是 BGR
    cv_img.image = img;

    auto image_msg = cv_img.toImageMsg();

    // 4. 发布 image
    raw_image_publisher_->publish(*image_msg);
    // emit compressedImageMsgReceived(msg);
    // emit rawImageMsgReceived(image_msg);
}

void CameraNode::recv_yolo_detect_image(const sensor_msgs::msg::Image::SharedPtr msg) {

    std::cout << "Received YOLO detected image." << std::endl;
    emit rawImageMsgReceived(msg);
}

void CameraNode::ask_service_response(CameraSettingsSrv::Request::SharedPtr request) {
    if (!connected()) {
        emit serviceResponsed(request->id, nullptr);
        return;
    }

    auto id = request->id;

    if (service_client_->service_is_ready()) {
        service_client_->async_send_request(request,
                                            [this, id](rclcpp::Client<CameraSettingsSrv>::SharedFuture future) {
                                                emit serviceResponsed(id, future.get());
                                            });
    } else {
        emit serviceResponsed(id, nullptr);
    }
}