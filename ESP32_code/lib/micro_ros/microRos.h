#pragma once

#include "centerControl.h"
#include "enum.h"
#include "geometry_msgs/msg/twist.h"
#include "nav_msgs/msg/odometry.h"
extern "C" {
#include "motion_params_service/srv/motion_params_service.h"
#include "motion_status_msgs/msg/motion_status.h"
}
#include <Arduino.h>
#include <WiFi.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <std_msgs/msg/string.h>

class MicroRos {
public:
    friend void microros_task(void *args);

    MicroRos(const std::string &node_name, const std::string &wifi_name, const std::string &wifi_passward, const std::string &ip, const uint16_t port);
    void start_task();
    void stop_task();

    bool is_connected();

    rcl_publisher_t *get_motion_status_publisher();
    // rcl_publisher_t *get_odom_publisher();
    rcl_publisher_t *get_serial_msg_publisher();

    bool reCreate_service_timer();

    rclc_executor_t executor;
    geometry_msgs__msg__Twist msg_cmd_vel;
    motion_status_msgs__msg__MotionStatus msg_motion_status;

private:
    rcl_allocator_t allocator_;
    rclc_support_t support_;
    rcl_node_t node_;
    std::string node_name_;

    micro_ros_agent_locator locator_;

    std::string ip_;
    uint16_t port_;
    std::string wifi_name_;
    std::string wifi_passward_;

    rcl_subscription_t cmd_vel_subscription_;
    rcl_publisher_t motion_status_publisher_, serial_msg_publisher_; //, odom_publisher_
    rcl_service_t motion_params_service_;
    rcl_timer_t timer_;

    motion_params_service__srv__MotionParamsService_Request motion_params_request_;
    motion_params_service__srv__MotionParamsService_Response motion_params_response_;

    bool support_initialized_ = false;
    bool node_initialized_ = false;
    bool executor_initialized_ = false;
    bool timer_initialized_ = false;
    bool motion_params_service_initialized_ = false;
    bool cmd_vel_subscription_initialized_ = false;
    bool motion_status_publisher_initialized_ = false, serial_msg_publisher_initialized_ = false; //, odom_publisher_initialized_ = false

    bool init();
    void clean();
    bool enable_task_run = false;

    volatile bool connected = false;
};

void motion_params_service_callback(const void *req, void *res);

void timer_callback(rcl_timer_t *timer, int64_t last_call_time);

void microros_task(void *args);

void msg_twist_callback(const void *msg);

void _serial_print(const std::string &msg);

extern MicroRos microRos;
