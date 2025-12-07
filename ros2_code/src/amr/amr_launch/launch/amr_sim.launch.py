import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import Command, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.actions import TimerAction
from launch.actions import RegisterEventHandler
from launch.event_handlers import OnProcessStart, OnProcessExit


def generate_launch_description():
    pkg_share = get_package_share_directory("amr_launch")

    use_sim_time = LaunchConfiguration("use_sim_time", default="true")

    urdf_path = os.path.join(pkg_share, "urdf", "amr_sim.xacro")
    gazebo_world_path = os.path.join(pkg_share, "world", "nav_linux.sdf")
    rviz_config_path = os.path.join(pkg_share, "config", "display_settings.rviz")
    gazebo_bridge_config_path = os.path.join(pkg_share, "config", "gazebo_bridge.yaml")
    controller_config_path = os.path.join(pkg_share, "config", "ros2_controllers.yaml")

    rviz_nodes = [
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            parameters=[
                {"robot_description": Command(["xacro", " ", urdf_path])},
                {"use_sim_time": use_sim_time},
            ],
            output="screen",
        ),
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
        Node(
            package="rviz2",
            executable="rviz2",
            arguments=["-d", rviz_config_path],
            output="screen",
            parameters=[{"use_sim_time": use_sim_time}],
        ),
    ]

    gazebo_nodes = [
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(get_package_share_directory("ros_gz_sim"), "launch", "gz_sim.launch.py")
            ),
            launch_arguments={"gz_args": f"{gazebo_world_path} -r"}.items(),
        ),
        Node(
            package="ros_gz_bridge",
            executable="parameter_bridge",
            parameters=[{"config_file": gazebo_bridge_config_path}, {"use_sim_time": use_sim_time}],
            output="screen",
        ),
        Node(
            package="ros_gz_sim",
            executable="create",
            parameters=[{"use_sim_time": use_sim_time}],
            arguments=[
                "-topic",
                "robot_description",
                "-x",
                "-1.0",  # x坐标（例如设为2米）
                "-y",
                "2.0",  # y坐标（例如设为1米）
                "-z",
                "0.1",  # z坐标（离地高度，避免卡地）
            ],
        ),
    ]

    controller_nodes = [
        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[controller_config_path, {"use_sim_time": use_sim_time}],
            remappings=[
                ("~/robot_description", "/robot_description"),
            ],
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["joint_state_broadcaster"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
    ]

    diff_drive_nodes = [
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["diff_drive_controller"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
        Node(
            package="topic_tools",
            executable="relay",
            name="cmd_vel_to_controller",
            arguments=["/cmd_vel", "/diff_drive_controller/cmd_vel_unstamped"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
    ]

    mecanum_drive_nodes = [
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["mecanum_drive_controller"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
        Node(
            package="topic_tools",
            executable="relay",
            name="cmd_vel_to_controller",
            arguments=["/cmd_vel", "/mecanum_drive_controller/reference_unstamped"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
        Node(
            package="topic_tools",
            executable="relay",
            name="controller_state_to_topic",
            arguments=["/mecanum_drive_controller/controller_state", "/controller_state"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
        Node(
            package="topic_tools",
            executable="relay",
            name="odometry_to_topic",
            arguments=["/mecanum_drive_controller/odometry", "/odometry"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
        Node(
            package="topic_tools",
            executable="relay",
            name="tf_to_topic",
            arguments=["/mecanum_drive_controller/tf_odometry", "/tf"],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
    ]

    nodes_lis = [
        *rviz_nodes,
        *gazebo_nodes,
        *controller_nodes,
        *diff_drive_nodes,
    ]

    return LaunchDescription(nodes_lis)
