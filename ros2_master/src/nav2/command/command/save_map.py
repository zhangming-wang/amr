#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from slam_toolbox.srv import SaveMap
from std_msgs.msg import String


class MapSaverClient(Node):
    def __init__(self):
        super().__init__("map_saver_client")
        # 创建客户端
        self.cli = self.create_client(SaveMap, "/slam_toolbox/save_map")

        # 等待服务准备好
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("Waiting for /slam_toolbox/save_map service...")

        # 创建请求
        self.req = SaveMap.Request()
        # 设置完整路径和文件名（不带扩展名）
        self.req.name = String()
        self.req.name.data = "/home/linux/work/amr/ros2_master/src/nav2/navigation/map/room"

    def send_request(self):
        # 异步调用
        self.future = self.cli.call_async(self.req)


def main(args=None):
    rclpy.init(args=args)
    map_saver = MapSaverClient()
    map_saver.send_request()

    # 等待结果
    while rclpy.ok():
        rclpy.spin_once(map_saver)
        if map_saver.future.done():
            try:
                response = map_saver.future.result()
            except Exception as e:
                map_saver.get_logger().error("Service call failed %r" % (e,))
            else:
                map_saver.get_logger().info(f"Save map result code: {response.result}")
            break

    map_saver.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
