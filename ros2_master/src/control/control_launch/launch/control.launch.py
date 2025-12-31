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
import os
import signal
import time


def generate_launch_description():

    system_clean(["micro_ros_agent", "control_panel", "yolo_detect"])
    time.sleep(1)

    current_share_directory = get_package_share_directory("control_launch")

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
        Node(
            package="image_detect",
            executable="yolo_detect",
            output="screen",
            parameters=[current_share_directory + "/config/yolo_detect.yaml"],
        ),
    ]

    nodes_list = [
        *control_panel_nodes,
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
