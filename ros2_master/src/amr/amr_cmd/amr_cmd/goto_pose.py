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

    if len(sys.argv) == 4:
        goal_x = float(sys.argv[1])
        goal_y = float(sys.argv[2])
        goal_angle = float(sys.argv[3])
    else:
        goal_x = 0.0
        goal_y = 0.0
        goal_angle = 0.0

    goal_pose = PoseStamped()
    goal_pose.header.frame_id = "map"
    goal_pose.header.stamp = navigator.get_clock().now().to_msg()
    goal_pose.pose.position.x = goal_x
    goal_pose.pose.position.y = goal_y
    goal_pose.pose.orientation.w = tf_transformations.quaternion_from_euler(0, 0, goal_angle / math.pi * 180)[3]
    navigator.goToPose(goal_pose)

    while not navigator.isTaskComplete():
        feedback = navigator.getFeedback()
        navigator.get_logger().info(f"剩余距离: {feedback.distance_remaining:.2f} 米" if feedback else "没有反馈信息")

    result = navigator.getResult()
    navigator.get_logger().info(f"导航结果: {result}")

    rclpy.shutdown()
