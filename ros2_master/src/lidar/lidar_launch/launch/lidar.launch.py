from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
from script.kill_process import kill_process  # type: ignore
from launch.substitutions import LaunchConfiguration


def generate_launch_description():

    kill_process(["serialserver", "ydlidar_node","scan_to_scan_filter_chain"])
    
    use_sim_time = LaunchConfiguration("use_sim_time", default="false")

    share_dir = get_package_share_directory("lidar_launch")

    lidar_params_file_path = os.path.join(share_dir, "config", "lidar_params.yaml")

    lidar_nodes = [
        Node(
            package="serial2wifi",
            executable="serialserver",
            name="serialserver",
            output="screen",
            parameters=[lidar_params_file_path,{"use_sim_time":use_sim_time}],
        ),
        Node(
            package="ydlidar",
            executable="ydlidar_node",
            name="ydlidar_node",
            output="screen",
            emulate_tty=True,
            parameters=[lidar_params_file_path,{"use_sim_time":use_sim_time}],
            respawn=True,
            respawn_delay=1.0,
        ),
        Node(
            package='laser_filters',
            executable='scan_to_scan_filter_chain',
            name='scan_to_scan_filter_chain',
            parameters=[lidar_params_file_path,{"use_sim_time":use_sim_time}],
            remappings=[
                ('scan', '/scan'),        # 假设您的雷达发布在 /scan_raw
                ('scan_filtered', '/scan_filtered')    # SLAM 节点将订阅这个过滤后的 /scan
            ]
        ),
    ]
    nodes_list = [
        *lidar_nodes,
    ]

    return LaunchDescription(nodes_list)
