#pragma once

#include "enum.h"
#include "geometry_msgs/msg/twist.h"
#include "motionControl.h"
#include "nav_msgs/msg/odometry.h"
#include "tools.h"
extern "C" {
#include "motion_settings_service/srv/motion_settings_service.h"
#include "motion_status_msgs/msg/motion_status.h"
}
#include "settings.h"
#include <Arduino.h>
#include <WiFi.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <std_msgs/msg/string.h>

class MotionNode {

private:
    MotionNode();
    ~MotionNode();

public:
    MotionNode(const MotionNode &) = delete;
    MotionNode &operator=(const MotionNode &) = delete;

    static MotionNode &get_instance();
    void init(const std::string &node_name, const std::string &node_namespace, const std::string &wifi_name, const std::string &wifi_passward, const std::string &ip, const uint16_t port);
    void start_task();
    void stop_task();

    bool is_connected();

    void set_enable_pub_motion_status(bool status);
    bool get_enable_pub_motion_status();

    rcl_publisher_t *get_motion_status_publisher();
    // rcl_publisher_t *get_odom_publisher();
    rcl_publisher_t *get_serial_msg_publisher();

    void reset_timer();

private:
    rcl_allocator_t allocator_;
    rclc_support_t support_;
    rcl_node_t node_;
    std::string node_name_, node_namespace_;

    micro_ros_agent_locator locator_;

    std::string ip_;
    uint16_t port_;
    std::string wifi_name_;
    std::string wifi_passward_;

    rcl_subscription_t motion_cmd_vel_subscription_, control_cmd_vel_subscription_;
    rcl_publisher_t motion_status_publisher_, serial_msg_publisher_; //, odom_publisher_
    rcl_service_t motion_settings_service_;
    rcl_timer_t timer_;

    motion_settings_service__srv__MotionSettingsService_Request motion_settings_request_;
    motion_settings_service__srv__MotionSettingsService_Response motion_settings_response_;

    bool support_initialized_ = false;
    bool node_initialized_ = false;
    bool executor_initialized_ = false;
    bool timer_initialized_ = false;
    bool motion_settings_service_initialized_ = false;
    bool motion_cmd_vel_subscription_initialized_ = false;
    bool control_cmd_vel_subscription_initialized_ = false;
    bool motion_status_publisher_initialized_ = false;
    bool serial_msg_publisher_initialized_ = false; //, odom_publisher_initialized_ = false

    bool enable_pub_motion_status_ = false;
    bool enable_task_run_ = false;

    bool _create_timer();
    void _destroy_timer();

    rclc_executor_t executor;
    geometry_msgs__msg__Twist msg_cmd_vel;
    motion_status_msgs__msg__MotionStatus msg_motion_status;

    volatile bool connected = false;
    MotionControl *motionControl = nullptr;

    bool init();
    void clean();
    bool is_enable_task_run();

    static void motion_settings_service_callback(const void *req, void *res);
    static void timer_callback(rcl_timer_t *timer, int64_t last_call_time);
    static void motion_node_task(void *args);
    static void msg_twist_callback(const void *msg);
};

void _serial_print(const std::string &msg);