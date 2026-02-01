from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from script.kill_process import kill_process  # type: ignore


def generate_launch_description():

    # kill_process(["micro_ros_agent", "control_panel", "yolo_detect"])

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
            # name="control_panel",
            output="screen",
        ),
        Node(
            package="image_detect",
            executable="yolo_detect",
            name="yolo_detect",
            output="screen",
            parameters=[current_share_directory + "/config/yolo_detect.yaml"],
        ),
    ]

    nodes_list = [
        *control_panel_nodes,
    ]

    return LaunchDescription(nodes_list)
