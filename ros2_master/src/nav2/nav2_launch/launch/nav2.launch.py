from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
from launch.substitutions import LaunchConfiguration
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from script.kill_process import kill_process  # type: ignore


def generate_launch_description():

    kill_process(["nav2_rviz2"])

    pkg_share_dir = get_package_share_directory("nav2_launch")
    nav2_bringup_dir = get_package_share_directory("nav2_bringup")
    rviz_config_dir = os.path.join(nav2_bringup_dir, "rviz", "nav2_default_view.rviz")

    use_sim_time = LaunchConfiguration("use_sim_time", default="true")
    map_yaml_path = os.path.join(pkg_share_dir, "map", "room.yaml")
    nav2_params_path = os.path.join(pkg_share_dir, "config", "nav2_params.yaml")

    return LaunchDescription(
        [
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(os.path.join(nav2_bringup_dir, "launch", "bringup_launch.py")),
                launch_arguments={
                    "map": map_yaml_path,
                    "use_sim_time": use_sim_time,
                    "params_file": nav2_params_path,
                }.items(),
            ),
            Node(
                package="rviz2",
                executable="rviz2",
                name="nav2_rviz2",
                output="screen",
                arguments=["-d", rviz_config_dir],
                parameters=[{"use_sim_time": use_sim_time}],
            ),
        ]
    )
