from ultralytics import YOLO
import cv2
from rclpy.node import Node
from ament_index_python.packages import get_package_share_directory
from rclpy.qos import QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import Image
from os import path
from cv_bridge import CvBridge
import rclpy


class YoloDetectNode(Node):
    def __init__(self):
        super().__init__(node_name="yolo_detect_node", namespace="")

        current_share_directory = get_package_share_directory("image_detect")

        self.declare_parameter("sub_image_topic_name", "/camera/image_raw")
        self.declare_parameter("pub_image_topic_name", "/yolo_detect/image_annotated")
        self.declare_parameter("model_path", "")
        self.declare_parameter("device", "cuda:0")
        self.declare_parameter("conf_threshold", 0.25)
        self.declare_parameter("iou_threshold", 0.45)
        self.declare_parameter("image_size", 640)
        self.declare_parameter("verbose", True)

        self.m_sub_image_topic_name = self.get_parameter("sub_image_topic_name").get_parameter_value().string_value
        self.m_pub_image_topic_name = self.get_parameter("pub_image_topic_name").get_parameter_value().string_value
        self.m_model_path = self.get_parameter("model_path").get_parameter_value().string_value
        self.m_device = self.get_parameter("device").get_parameter_value().string_value
        self.m_conf_threshold = self.get_parameter("conf_threshold").get_parameter_value().double_value
        self.m_iou_threshold = self.get_parameter("iou_threshold").get_parameter_value().double_value
        self.m_image_size = self.get_parameter("image_size").get_parameter_value().integer_value
        self.m_verbose = self.get_parameter("verbose").get_parameter_value().bool_value

        if len(self.m_model_path) == 0:
            self.m_model_path = current_share_directory + "/model/yolov5lu.pt"

        best_effort_qos = QoSProfile(reliability=ReliabilityPolicy.BEST_EFFORT, depth=1)

        self.m_image_sub = self.create_subscription(
            msg_type=Image,  # 替换为实际的消息类型
            topic=self.m_sub_image_topic_name,
            callback=self.image_callback,
            qos_profile=best_effort_qos,
        )

        self.m_image_pub = self.create_publisher(
            msg_type=Image,  # 替换为实际的消息类型
            topic=self.m_pub_image_topic_name,
            qos_profile=best_effort_qos,
        )

        if not path.exists(self.m_model_path):
            self.get_logger().error(f"Model path {self.m_model_path} does not exist!")
            self.m_model = None
        else:
            self.get_logger().info(f"Loading model from {self.m_model_path}")
            self.m_model = YOLO(self.m_model_path)
            self.m_model.to(device=self.m_device)

        self.m_bridge = CvBridge()

    def image_callback(self, msg):
        if self.m_model is None:
            self.get_logger().error("Model is not loaded, cannot perform detection.")
            return

        if isinstance(msg, Image):
            cv_image = self.m_bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")
        else:
            cv_image = msg  # 已经是 numpy.ndarray

        annotated_img = self.detect(cv_image)

        # cv2.imwrite(
        #     "/home/dev/workspace/amr/ros2_master/test/" + str(int(time.time())) + ".jpg", annotated_img
        # )  # 保存检测结果图片

        image_msg = self.m_bridge.cv2_to_imgmsg(annotated_img, encoding="bgr8")

        self.m_image_pub.publish(image_msg)

    def detect(self, img):
        results = self.m_model.predict(
            source=img,
            imgsz=self.m_image_size,
            conf=self.m_conf_threshold,
            iou=self.m_iou_threshold,
            verbose=self.m_verbose,
        )
        if len(results) == 0:
            return img
        annotated_frame = results[0].plot()
        return annotated_frame


import time
import threading


def run_node(yolo_detect_node):
    cnt = 0
    while rclpy.ok():
        # 这里可以添加代码来获取图像，例如从摄像头或视频流
        # 假设我们有一个函数 get_image() 返回一个 numpy.ndarray 图像
        img = cv2.imread("/home/dev/workspace/amr/test/yolo_test/bird.jpg")  # 示例：读取本地图片
        yolo_detect_node.image_callback(img)
        time.sleep(0.5)  # 控制处理频率

        if cnt >= 10:
            yolo_detect_node.get_logger().info("测试次数到达，退出线程")
            break
        cnt += 1


def main(args=None):
    rclpy.init(args=args)

    yolo_detect_node = YoloDetectNode()

    # threading.Thread(target=run_node, args=(yolo_detect_node,)).start()

    rclpy.spin(yolo_detect_node)
    yolo_detect_node.destroy_node()

    rclpy.shutdown()
