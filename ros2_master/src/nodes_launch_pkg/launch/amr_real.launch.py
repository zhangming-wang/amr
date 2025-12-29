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
    system_clean()

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
            respawn=True,
            respawn_delay=1.0,
        ),
    ]

    amr_nodes = [
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(get_package_share_directory("amr_launch"), "launch", "amr_real.launch.py")
            )
        ),
        # IncludeLaunchDescription(
        #     PythonLaunchDescriptionSource(
        #         os.path.join(get_package_share_directory("amr_nav2"), "launch", "amr_nav2.launch.py")
        #     )
        # ),
        # Node(
        #     package="amr_cmd",
        #     executable="init_pose",
        #     output="screen",
        #     parameters=[{"use_sim_time": False}],
        # ),
    ]

    nodes_list = [
        # *control_panel_nodes,
        *lidar_nodes,
        # *amr_nodes,
    ]

    return LaunchDescription(nodes_list)


def system_clean():
    keywords = [
        "micro_ros_agent",
        "serial2wifi/tcpserver",
        "ydlidar",
    ]

    pids = set()

    for kw in keywords:
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

    # 清理资源
    os.system("rm -f /tmp/tty_lidar")
