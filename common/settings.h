#pragma once

static constexpr const char *wifi_name = "TP-LINK_403";
static constexpr const char *wifi_password = "403123456";
static constexpr const char *wifi_IP = "192.168.1.101";

static constexpr const int micro_ros_port = 8888;
static constexpr const int http_port = 80;
static constexpr const int tcp_client_port = 8889;

static constexpr const int ydlidar_baudrate = 115200;

// static constexpr const char *esp32_ip = "192.168.1.100";
// static constexpr const char *esp32_gateway = "192.168.1.1";
// static constexpr const char *esp32_subnet = "255.255.255.0";

static constexpr const char *esp32_camera_node_name = "esp32_camera_node";
static constexpr const char *esp32_camera_node_namespace = "esp32";
static constexpr const char *esp32_camera_image_topic_name = "image_topic";
static constexpr const char *esp32_camera_settings_service_name = "camera_settings_service";

static constexpr const char *pc_camera_node_name = "pc_camera_node";
static constexpr const char *pc_camera_node_namespace = "pc";

static constexpr const char *esp32_motion_node_name = "esp32_motion_node";
static constexpr const char *esp32_motion_node_namespace = "esp32";
static constexpr const char *esp32_motion_status_topic_name = "motion_status_topic";
static constexpr const char *esp32_motion_serial_msg_topic_name = "motion_serial_msg_topic";
static constexpr const char *esp32_motion_settings_service_name = "motion_settings_service";

static constexpr const char *pc_motion_node_name = "pc_motion_node";
static constexpr const char *pc_motion_node_namespace = "pc";

static constexpr const char *pc_motion_cmd_vel_topic_name = "/cmd_vel";

static constexpr const char *esp32_bluetooth_slave_name = "esp32_bluetooth_slave";
