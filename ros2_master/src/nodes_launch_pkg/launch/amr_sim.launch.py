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
        *amr_nodes,
    ]

    return LaunchDescription(nodes_list)
