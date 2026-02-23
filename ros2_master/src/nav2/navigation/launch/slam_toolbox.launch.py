from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from script.kill_process import kill_process  # type: ignore
import os
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():

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
                PythonLaunchDescriptionSource(
                    os.path.join(get_package_share_directory("slam_toolbox"), "launch", "online_async_launch.py")
                ),
                launch_arguments={
                    "slam_params_file": os.path.join(
                        get_package_share_directory("navigation"), "config", "mapper_params_online_async.yaml"
                    )
                }.items(),
            ),
        ]
    )
