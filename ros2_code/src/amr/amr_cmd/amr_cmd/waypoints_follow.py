from geometry_msgs.msg import PoseStamped
from nav2_simple_commander.robot_navigator import BasicNavigator
import rclpy
import sys
import tf_transformations
import math


def main():
    rclpy.init()
    navigator = BasicNavigator()
    navigator.waitUntilNav2Active()

    goal_poses = []

    if (len(sys.argv) - 1) % 3 == 0 and len(sys.argv) > 1:
        for i in range((len(sys.argv) - 1) // 3):
            goal_x = float(sys.argv[1 + i * 3])
            goal_y = float(sys.argv[2 + i * 3])
            goal_angle = float(sys.argv[3 + i * 3])

            goal_pose = PoseStamped()
            goal_pose.header.frame_id = "map"
            goal_pose.header.stamp = navigator.get_clock().now().to_msg()
            goal_pose.pose.position.x = goal_x
            goal_pose.pose.position.y = goal_y
            goal_pose.pose.orientation.w = tf_transformations.quaternion_from_euler(0, 0, goal_angle / math.pi * 180)[3]

            goal_poses.append(goal_pose)

    navigator.followWaypoints(goal_poses)
    while not navigator.isTaskComplete():
        feedback = navigator.getFeedback()
        navigator.get_logger().info(f"路点编号: {feedback.current_waypoint}" if feedback else "没有反馈信息")

    result = navigator.getResult()
    navigator.get_logger().info(f"导航结果: {result}")

    rclpy.shutdown()
