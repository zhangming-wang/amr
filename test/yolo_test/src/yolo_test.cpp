
#include <filesystem>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

int main() {
    try {
        std::string model_path =
            "/home/dev/workspace/amr/ros2_master/src/control/control_panel/src/model/yolov5lu.onnx";

        cv::dnn::Net net = cv::dnn::readNetFromONNX(model_path);
        net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

        std::string image_path =
            "/home/dev/workspace/amr/test/src/bird.jpg";

        if (!std::filesystem::exists(image_path)) {
            std::cerr << "Image not found: " << image_path << std::endl;
            return -1;
        }

        cv::Mat img = cv::imread(image_path);
        if (img.empty()) {
            std::cerr << "Failed to load image" << std::endl;
            return -1;
        }

        // ===== 1. 预处理 =====
        cv::Mat blob;
        cv::dnn::blobFromImage(
            img,
            blob,
            1.0 / 255.0,
            cv::Size(640, 640),
            cv::Scalar(),
            true, // swapRB
            false // crop
        );

        net.setInput(blob);

        std::vector<cv::Mat> outputs;
        net.forward(outputs);

        cv::Mat out = outputs[0]; // 1x84x8400
        int dim1 = out.size[1];   // 84
        int dim2 = out.size[2];   // 8400
        float *data = (float *)out.data;

        for (int i = 0; i < dim2; i++) {
            float *pred = data + i * dim1;

            float cx = pred[0];
            float cy = pred[1];
            float w = pred[2];
            float h = pred[3];
            float obj_conf = pred[4];

            if (obj_conf < 0.4f)
                continue;

            int class_id = -1;
            float max_score = 0.f;
            for (int c = 0; c < 80; c++) {
                float score = pred[5 + c];
                if (score > max_score) {
                    max_score = score;
                    class_id = c;
                }
            }

            float conf = obj_conf * max_score;
            if (conf < 0.4f)
                continue;

            int left = int((cx - 0.5f * w) * img.cols / 640);
            int top = int((cy - 0.5f * h) * img.rows / 640);
            int width = int(w * img.cols / 640);
            int height = int(h * img.rows / 640);

            cv::rectangle(img, cv::Rect(left, top, width, height), cv::Scalar(0, 255, 0), 2);
        }

        // ===== 5. 显示结果 =====
        cv::imshow("YOLO Detection", img);
        cv::waitKey(0);
        cv::destroyAllWindows();

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}