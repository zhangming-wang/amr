from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory

from launch_ros.actions import LifecycleNode
from launch.actions import DeclareLaunchArgument
import os
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    share_dir = get_package_share_directory("nodes_launch_pkg")

    params_file_path = os.path.join(share_dir, "params", "params.yaml")

    control_panel_nodes = [
        Node(
            package="micro_ros_agent",
            executable="micro_ros_agent",
            name="micro_ros_agent",
            output="screen",
            arguments=["udp4", "--port", "8888"],
        ),
        Node(
            package="control_panel",
            executable="control_panel",
            output="screen",
        ),
    ]

    lidar_nodes = [
        Node(
            package="serial2wifi",
            executable="tcpserver",
            name="tcpserver",
            output="screen",
            parameters=[params_file_path],
        ),
        Node(
            package="ydlidar",
            executable="ydlidar_node",
            name="ydlidar_node",
            output="screen",
            emulate_tty=True,
            parameters=[params_file_path],
        ),
    ]

    amr_nodes = [
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(get_package_share_directory("amr_launch"), "launch", "amr_sim.launch.py")
            )
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(get_package_share_directory("amr_nav2"), "launch", "amr_nav2.launch.py")
            )
        ),
        Node(
            package="amr_cmd",
            executable="init_pose",
            output="screen",
            parameters=[{"use_sim_time": True}],
        ),
    ]

    nodes_list = [
        *control_panel_nodes,
        # *lidar_nodes,
        *amr_nodes,
    ]

    return LaunchDescription(nodes_list)
