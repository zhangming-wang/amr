from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
from script.kill_process import kill_process  # type: ignore


def generate_launch_description():

    # kill_process(["serialserver", "ydlidar_node"])

    share_dir = get_package_share_directory("lidar_launch")

    params_file_path = os.path.join(share_dir, "config", "lidar_params.yaml")

    lidar_nodes = [
        Node(
            package="serial2wifi",
            executable="serialserver",
            name="serialserver",
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
            respawn=True,
            respawn_delay=1.0,
        ),
    ]
    nodes_list = [
        *lidar_nodes,
    ]

    return LaunchDescription(nodes_list)
