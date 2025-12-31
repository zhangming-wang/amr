from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory

from launch_ros.actions import LifecycleNode
from launch.actions import DeclareLaunchArgument
import os
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import subprocess
import signal
import time


def generate_launch_description():

    system_clean(["tcpserver", "ydlidar_node"])

    share_dir = get_package_share_directory("lidar_launch")

    params_file_path = os.path.join(share_dir, "config", "lidar_params.yaml")

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
            respawn=True,
            respawn_delay=1.0,
        ),
    ]
    nodes_list = [
        *lidar_nodes,
    ]

    return LaunchDescription(nodes_list)


def system_clean(process_list: list):

    pids = set()

    for kw in process_list:
        try:
            out = subprocess.check_output(["pgrep", "-f", kw], stderr=subprocess.DEVNULL, text=True)
            print(f"找到进程 {kw} : {out.strip()}")
            for pid in out.split():
                pids.add(int(pid))
        except subprocess.CalledProcessError:
            pass

    # 先优雅关闭
    for pid in pids:
        try:
            os.kill(pid, signal.SIGTERM)
        except ProcessLookupError:
            pass

    time.sleep(0.5)

    # 再强制兜底
    for pid in pids:
        try:
            os.kill(pid, signal.SIGKILL)
        except ProcessLookupError:
            pass
