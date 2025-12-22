#pragma once

static constexpr const char *wifi_name = "TP-LINK_403";
static constexpr const char *wifi_password = "403123456";
static constexpr const char *wifi_IP = "192.168.1.102";

static constexpr const int micro_ros_port = 8888;

static constexpr const int ydlidar_tcp_client_port = 8889;
static constexpr const int ydlidar_baudrate = 115200;

static constexpr const char *pc_camera_node_name = "pc_camera_node";
static constexpr const char *pc_camera_node_namespace = "pc";

static constexpr const char *pc_motion_node_name = "pc_motion_node";
static constexpr const char *pc_motion_node_namespace = "pc";
static constexpr const char *pc_cmd_vel_topic_name = "cmd_vel";

static constexpr const char *esp32_camera_node_name = "esp32_camera_node";
static constexpr const char *esp32_camera_node_namespace = "esp32";
static constexpr const char *esp32_camera_image_topic_name = "compressed_image_topic";
static constexpr const char *esp32_camera_settings_service_name = "camera_settings_service";
static constexpr const char *esp32_camera_heartbeat_topic_name = "camera_heartbeat_topic";
static constexpr const char *esp32_camera_serial_msg_topic_name = "camera_serial_msg_topic";

static constexpr const char *esp32_motion_node_name = "esp32_motion_node";
static constexpr const char *esp32_motion_node_namespace = "esp32";
static constexpr const char *esp32_motion_status_topic_name = "motion_status_topic";
static constexpr const char *esp32_motion_serial_msg_topic_name = "motion_serial_msg_topic";
static constexpr const char *esp32_motion_settings_service_name = "motion_settings_service";
static constexpr const char *esp32_motion_heartbeat_topic_name = "motion_heartbeat_topic";

static constexpr const char *odom_topic_name = "/odom";
static constexpr const char *imu_topic_name = "/imu";
static constexpr const char *cmd_vel_topic_name = "/cmd_vel";
static constexpr const char *scan_topic_name = "/scan";
static constexpr const char *scan_points_topic_name = "/scan/points";
static constexpr const char *joint_states_topic_name = "/joint_states";
static constexpr const char *camera_image_raw_topic_name = "/camera/image_raw";

static constexpr const char *base_footprint_tf_frame_id = "base_footprint";
static constexpr const char *base_link_tf_frame_id = "base_link";
static constexpr const char *odom_tf_frame_id = "odom";
static constexpr const char *imu_tf_frame_id = "imu_link";
static constexpr const char *camera_tf_frame_id = "camera_link";

static constexpr const char *left_front_wheel_joint_name = "left_front_wheel_joint";
static constexpr const char *left_back_wheel_joint_name = "left_back_wheel_joint";
static constexpr const char *right_front_wheel_joint_name = "right_front_wheel_joint";
static constexpr const char *right_back_wheel_joint_name = "right_back_wheel_joint";
