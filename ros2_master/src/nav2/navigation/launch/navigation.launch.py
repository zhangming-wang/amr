from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
from launch.substitutions import LaunchConfiguration
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from script.kill_process import kill_process  # type: ignore
from launch.actions import TimerAction


def generate_launch_description():

    # kill_process(["nav2_rviz2"])

    pkg_share_dir = get_package_share_directory("navigation")
    nav2_bringup_dir = get_package_share_directory("nav2_bringup")
    rviz_config_dir = os.path.join(nav2_bringup_dir, "rviz", "nav2_default_view.rviz")

    use_sim_time = LaunchConfiguration("use_sim_time", default="false")
    map_yaml_path = os.path.join(pkg_share_dir, "map", "room.yaml")
    nav2_params_path = os.path.join(pkg_share_dir, "config", "nav2_params.yaml")

    init_pose_node = Node(
        package="command",
        executable="init_pose",
        name="init_pose",
        output="screen",
        parameters=[{"use_sim_time": use_sim_time}],
    )

    return LaunchDescription(
        [
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    os.path.join(get_package_share_directory("control_launch"), "launch", "control.launch.py")
                ),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    os.path.join(get_package_share_directory("lidar_launch"), "launch", "lidar.launch.py")
                ),
            ),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(os.path.join(nav2_bringup_dir, "launch", "bringup_launch.py")),
                launch_arguments={
                    "map": map_yaml_path,
                    "use_sim_time": use_sim_time,
                    "params_file": nav2_params_path,
                }.items(),
            ),
            TimerAction(  # （可选）再等 1.0 秒
                period=1.0,
                actions=[init_pose_node],  # ✅ 再启动 init_pose
            ),
            Node(
                package="rviz2",
                executable="rviz2",
                name="nav2_rviz2",
                output="screen",
                arguments=["-d", rviz_config_dir],
                parameters=[{"use_sim_time": False}],
            ),
        ]
    )
