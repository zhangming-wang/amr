from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory

from launch_ros.actions import LifecycleNode
from launch.actions import DeclareLaunchArgument
import os


def generate_launch_description():
    share_dir = get_package_share_directory("nodes_launch_pkg")

    params_declare = DeclareLaunchArgument(
        "params_file",
        default_value=os.path.join(share_dir, "params", "params.yaml"),
        description="FPath to the ROS2 parameters file to use.",
    )
    parameter_file = LaunchConfiguration("params_file")

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
        parameters=[parameter_file],
    )

    ydlidar_node = Node(
        package="ydlidar",
        executable="ydlidar_node",
        name="ydlidar_node",
        output="screen",
        emulate_tty=True,
        parameters=[parameter_file],
    )

    pc_software = Node(
        package="pc_software",
        executable="pc_software",
        # name="pc_software",
        output="screen",
    )

    return LaunchDescription(
        [
            params_declare,
            micro_ros_agent,
            tcpserver_node,
            ydlidar_node,
            pc_software,
        ]
    )
