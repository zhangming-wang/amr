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
#include "baseTask.h"
#include "mpu6050Control.h"
#include "settings.h"
#include "system.h"
#include <Arduino.h>
#include <WiFi.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rcl/time.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <std_msgs/msg/string.h>
#include <string>
class AMRNode : public BaseTaskSingleton<AMRNode> {

    friend class Singleton<AMRNode>;

public:
    void set_enable_pub_motion_status(bool status);
    bool get_enable_pub_motion_status();

    bool connected() { return connected_; }

    void update() override;

protected:
    AMRNode();
    void init_task() override {}
    void clean_task() override { clean_micro_ros(); }
    void sleep() override { vTaskDelay(pdMS_TO_TICKS(motionControl_->get_milliseconds())); }

private:
    rcl_allocator_t allocator_;
    rclc_support_t support_;
    rcl_node_t node_;
    micro_ros_agent_locator locator_;
    rcl_clock_t clock_;
    rclc_executor_t executor_;

    rcl_subscription_t motion_cmd_vel_subscription_, control_cmd_vel_subscription_;
    rcl_publisher_t motion_status_publisher_, odom_publisher_, imu_publisher_, serial_msg_publisher_;
    rcl_service_t motion_settings_service_;

    motion_settings_service__srv__MotionSettingsService_Request motion_settings_request_;
    motion_settings_service__srv__MotionSettingsService_Response motion_settings_response_;

    bool support_initialized_ = false;
    bool node_initialized_ = false;
    bool executor_initialized_ = false;
    bool motion_settings_service_initialized_ = false;
    bool motion_cmd_vel_subscription_initialized_ = false;
    bool control_cmd_vel_subscription_initialized_ = false;
    bool motion_status_publisher_initialized_ = false;
    bool serial_msg_publisher_initialized_ = false;
    bool odom_publisher_initialized_ = false;
    bool imu_publisher_initialized_ = false;

    bool enable_pub_motion_status_ = false;

    MotionControl *motionControl_ = nullptr;
    MPU6050Control *mpu6050Control_ = nullptr;

    bool connected_ = false;

    bool init_micro_ros();
    void clean_micro_ros();

    static void motion_settings_service_callback(const void *req, void *res);
    static void msg_twist_callback(const void *msg);
    static void _serial_print(const std::string &msg);
};
