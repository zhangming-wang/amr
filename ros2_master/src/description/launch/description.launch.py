import os
from launch import LaunchDescription
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from script.kill_process import kill_process  # type: ignore
from launch.event_handlers import OnShutdown, OnProcessExit
from launch.actions import LogInfo
from launch.actions import RegisterEventHandler


def generate_launch_description():

    # kill_process(["description_robot_state_publisher", "description_rviz2"])

    pkg_share = get_package_share_directory("description")

    use_sim_time = LaunchConfiguration("use_sim_time", default="false")

    urdf_path = os.path.join(pkg_share, "urdf", "amr.xacro")
    rviz_config_path = os.path.join(pkg_share, "config", "display_settings.rviz")

    # 1. Robot State Publisher
    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[
            {"robot_description": Command(["xacro", " ", urdf_path])},
            {"use_sim_time": use_sim_time},
        ],
        name="robot_state_publisher",
        output="screen",
    )

    # 3. RViz2
    rviz_launch_node = Node(
        package="rviz2",
        executable="rviz2",
        arguments=["-d", rviz_config_path],
        output="screen",
        name="rviz2",
        parameters=[{"use_sim_time": use_sim_time}],
    )

    return LaunchDescription(
        [
            robot_state_publisher_node,
            rviz_launch_node,
            # Node(
            #     package="joint_state_publisher_gui",
            #     executable="joint_state_publisher_gui",
            #     output="screen",
            # ),
            # Node(
            #     package="joint_state_publisher",
            #     executable="joint_state_publisher",
            #     output="screen",
            # ),
        ]
    )
