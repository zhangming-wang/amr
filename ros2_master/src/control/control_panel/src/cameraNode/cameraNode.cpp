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
    compressed_image_subscription_ = node_->create_subscription<sensor_msgs::msg::CompressedImage>(constructNodeName(esp32_camera_node_namespace, esp32_camera_image_topic_name), reliable_qos_, std::bind(&CameraNode::recv_compressed_image_msg, this, std::placeholders::_1));
    raw_image_publisher_ = node_->create_publisher<sensor_msgs::msg::Image>(camera_image_raw_topic_name, best_effort_qos_);

    std::string model_path = ament_index_cpp::get_package_share_directory("control_panel") + "src/models/yolov5nu.onnx";
    if (std::filesystem::exists(model_path))
        net_ = std::make_shared<cv::dnn::Net>(cv::dnn::readNetFromONNX(model_path));
    else
        RCLCPP_ERROR(node_->get_logger(), "Cannot find model file: %s", model_path.c_str());

    if (net_) {
        net_->setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        net_->setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    } else {
        RCLCPP_ERROR(node_->get_logger(), "Failed to load DNN model.");
    }
}

void CameraNode::recv_compressed_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    // publish_compressed_image(msg);
    publish_raw_image(msg);
}

void CameraNode::publish_raw_image(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    cv::Mat img = cv::imdecode(
        cv::Mat(msg->data), cv::IMREAD_COLOR);

    if (img.empty()) {
        RCLCPP_WARN(node_->get_logger(), "Decode compressed image failed");
        return;
    }

    if (net_) {
        _detectYOLO(img);
    }

    // 3. cv::Mat → ROS Image
    cv_bridge::CvImage cv_img;
    cv_img.header = msg->header; // 保留时间戳 + frame_id
    cv_img.encoding = "bgr8";    // ESP32 摄像头通常是 BGR
    cv_img.image = img;

    auto image_msg = cv_img.toImageMsg();

    // 4. 发布 image
    raw_image_publisher_->publish(*image_msg);
    emit rawImageMsgReceived(image_msg);
}
void CameraNode::publish_compressed_image(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    emit CompressedImageMsgReceived(msg);
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

void CameraNode::_detectYOLO(cv::Mat &img) {
    // 1. 预处理
    cv::Mat blob;
    cv::dnn::blobFromImage(
        img,
        blob,
        1.0 / 255.0,
        cv::Size(640, 640),
        cv::Scalar(),
        true, // BGR -> RGB
        false);

    // 2. 推理
    net_->setInput(blob);

    std::vector<cv::Mat> outputs;
    net_->forward(outputs);

    if (outputs.empty())
        return;

    cv::Mat out = outputs[0];

    // 3. 后处理
    const int num_classes = 80;
    const int elements = 84; // 4 + 1 + 79
    const int num_boxes = out.size[2];

    float *data = (float *)out.data;

    for (int i = 0; i < num_boxes; ++i) {
        float obj_conf = data[4];
        if (obj_conf < 0.5f) {
            data += elements;
            continue;
        }

        int class_id = -1;
        float max_class_score = 0.f;
        for (int c = 0; c < num_classes; ++c) {
            float score = data[5 + c];
            if (score > max_class_score) {
                max_class_score = score;
                class_id = c;
            }
        }

        float confidence = obj_conf * max_class_score;
        if (confidence < 0.5f) {
            data += elements;
            continue;
        }

        // YOLO bbox: cx, cy, w, h (relative to 640)
        float cx = data[0];
        float cy = data[1];
        float w = data[2];
        float h = data[3];

        int left = int((cx - 0.5f * w) * img.cols / 640);
        int top = int((cy - 0.5f * h) * img.rows / 640);
        int width = int(w * img.cols / 640);
        int height = int(h * img.rows / 640);

        cv::rectangle(
            img,
            cv::Rect(left, top, width, height),
            cv::Scalar(0, 255, 0),
            2);

        data += elements;
    }
}