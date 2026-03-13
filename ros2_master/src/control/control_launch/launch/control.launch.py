from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from script.kill_process import kill_process  # type: ignore
import os
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


def generate_launch_description():

    kill_process(["micro_ros_agent", "control_panel", "yolo_detect", "ekf_node"])

    use_sim_time = LaunchConfiguration("use_sim_time", default="false")

    current_share_directory = get_package_share_directory("control_launch")

    control_params_path = os.path.join(
        current_share_directory, "config", "control_params.yaml"
    )

    description_launch_path = os.path.join(
        get_package_share_directory("description"),
        "launch",
        "description.launch.py",  # 目标包名  # 文件夹名  # 文件名
    )

    nodes_list = [
        Node(
            package="micro_ros_agent",
            executable="micro_ros_agent",
            name="micro_ros_agent",
            output="screen",
            arguments=["udp4", "--port", "8888"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
        Node(
            package="control_panel",
            executable="control_panel",
            # name="control_panel",
            output="screen",
            parameters=[{"use_sim_time": use_sim_time}],
        ),
        Node(
            package="image_detect",
            executable="yolo_detect",
            name="yolo_detect",
            output="screen",
            parameters=[control_params_path, {"use_sim_time": use_sim_time}],
        ),
        Node(
            package="robot_localization",
            executable="ekf_node",
            name="ekf_node",
            output="screen",
            parameters=[
                control_params_path,
                {"use_sim_time": use_sim_time},
            ],  # 加载你的参数文件
            remappings=[("/odometry/filtered", "/odom_filtered")],
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(description_launch_path),
        ),
    ]

    return LaunchDescription(nodes_list)
