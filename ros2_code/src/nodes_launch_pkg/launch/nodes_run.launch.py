from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory

from launch_ros.actions import LifecycleNode
from launch.actions import DeclareLaunchArgument
import os


def generate_launch_description():
    share_dir = get_package_share_directory("nodes_launch_pkg")

    params_file_path = os.path.join(share_dir, "params", "params.yaml")

    micro_ros_agent = Node(
        package="micro_ros_agent",
        executable="micro_ros_agent",
        name="micro_ros_agent",
        output="screen",
        arguments=["udp4", "--port", "8888"],
    )

    tcpserver_node = Node(
        package="serial2wifi",
        executable="tcpserver",
        name="tcpserver",
        output="screen",
        parameters=[params_file_path],
    )

    ydlidar_node = Node(
        package="ydlidar",
        executable="ydlidar_node",
        name="ydlidar_node",
        output="screen",
        emulate_tty=True,
        parameters=[params_file_path],
    )

    control_panel = Node(
        package="control_panel",
        executable="control_panel",
        output="screen",
    )

    return LaunchDescription(
        [
            micro_ros_agent,
            # tcpserver_node,
            # ydlidar_node,
            control_panel,
        ]
    )
