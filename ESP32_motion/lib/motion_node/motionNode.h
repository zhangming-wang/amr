#pragma once

#include "enum.h"
#include "geometry_msgs/msg/twist.h"
#include "motionControl.h"
#include "nav_msgs/msg/odometry.h"
#include "system.h"
extern "C" {
#include "motion_settings_service/srv/motion_settings_service.h"
#include "motion_status_msgs/msg/motion_status.h"
}
#include "baseNode.h"
#include "mpu6050Control.h"
#include "settings.h"

class MotionNode : public BaseNode<MotionNode> {

    friend class Singleton<MotionNode>;

protected:
    MotionNode();
    void sleep() override { vTaskDelay(pdMS_TO_TICKS(motionControl_->get_milliseconds())); }
    void spin_micro_ros() override { rclc_executor_spin_some(&executor_, RCL_MS_TO_NS(motionControl_->get_milliseconds())); };

    bool init_micro_ros() override;
    void clean_micro_ros() override;

public:
    void set_enable_pub_motion_status(bool status);
    bool get_enable_pub_motion_status();

    void publish_msgs();

private:
    rcl_subscription_t motion_cmd_vel_subscription_, control_cmd_vel_subscription_;
    rcl_publisher_t motion_status_publisher_, odom_publisher_, imu_publisher_;
    rcl_service_t motion_settings_service_;

    std::string motion_cmd_vel_topic_name_;
    std::string motion_services_name_;
    std::string motion_status_topic_name_;

    motion_settings_service__srv__MotionSettingsService_Request motion_settings_request_;
    motion_settings_service__srv__MotionSettingsService_Response motion_settings_response_;
    geometry_msgs__msg__Twist motion_twist_msg_, control_twist_msg_;

    bool motion_settings_service_initialized_ = false;
    bool motion_cmd_vel_subscription_initialized_ = false;
    bool control_cmd_vel_subscription_initialized_ = false;
    bool motion_status_publisher_initialized_ = false;
    bool odom_publisher_initialized_ = false;
    bool imu_publisher_initialized_ = false;

    bool enable_pub_motion_status_ = false;

    MotionControl *motionControl_ = nullptr;
    MPU6050Control *mpu6050Control_ = nullptr;

    static void motion_settings_service_callback(const void *req, void *res);
    static void msg_twist_callback(const void *msg);
};
