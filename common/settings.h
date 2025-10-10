#pragma once

static constexpr const char *wifi_name = "TP-LINK_403";
static constexpr const char *wifi_password = "403123456";
static constexpr const char *wifi_IP = "192.168.1.101";

static constexpr const int micro_ros_port = 8888;
static constexpr const int http_port = 80;

static constexpr const char *esp32_ip = "192.168.1.190";
static constexpr const char *esp32_gateway = "192.168.1.1";
static constexpr const char *esp32_subnet = "255.255.255.0";

static constexpr const char *motion_node_name = "motion_node";
static constexpr const char *motion_node_namespace = "";
static constexpr const char *motion_status_topic_name = "motion_status_topic";
static constexpr const char *motion_params_service_name = "motion_params_service";

static constexpr const char *esp32_camera_node_name = "esp32_camera_node";
static constexpr const char *esp32_camera_node_namespace = "esp32";
static constexpr const char *esp32_camera_image_topic_name = "image_topic";
static constexpr const char *esp32_camera_settings_service_name = "camera_settings_service";

static constexpr const char *pc_camera_node_name = "pc_camera_node";
static constexpr const char *pc_camera_node_namespace = "pc";
static constexpr const char *pc_camera_image_topic_name = "image_topic";
static constexpr const char *pc_camera_settings_service_name = "camera_settings_service";
