#!/usr/bin/env python3

import os
import pty
import socket
import select
import subprocess
import rclpy
from rclpy.node import Node
import time
from motion_status_msgs.msg import MotionStatus  # type: ignore


class SerialServerNode(Node):
    def __init__(self):
        super().__init__("serial_server_node")

        # 声明 ROS 2 参数
        self.declare_parameter("serial_port", "/tmp/laserport")
        self.declare_parameter("motion_status_topic", "/motion_status")

        # 获取 ROS 2 参数
        self.serial_port = self.get_parameter("serial_port").get_parameter_value().string_value
        self.motion_status_topic = self.get_parameter("motion_status_topic").get_parameter_value().string_value

        self.motion_status_subscriber = self.create_subscription(
            MotionStatus,
            self.motion_status_topic,
            self.motion_status_callback,
            qos_profile=rclpy.qos.QoSProfile(depth=10, reliability=rclpy.qos.ReliabilityPolicy.BEST_EFFORT),
        )

        self.master, self.slave = pty.openpty()
        if os.path.exists(self.serial_port):
            os.remove(self.serial_port)
        os.symlink(os.ttyname(self.slave), self.serial_port)
        self.get_logger().info(f"串口设备:{self.serial_port} 已创建")

    def motion_status_callback(self, msg: MotionStatus):
        data = msg.sensor_status.data[0 : msg.sensor_status.size]
        os.write(self.master, data)


def main():
    rclpy.init()
    node = SerialServerNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
