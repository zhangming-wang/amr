#pragma once

#include "enum.h"
#include "geometry_msgs/msg/twist.h"
#include "nav_msgs/msg/odometry.h"
#include "system.h"
extern "C" {
#include "motion_settings_service/srv/motion_settings_service.h"
#include "motion_status_msgs/msg/motion_status.h"
}
#include "baseNode.h"
#include "motionControlTask.h"
#include "sensorsControlTask.h"

class MotionNodeTask : public BaseNode<MotionNodeTask> {

    friend class Singleton<MotionNodeTask>;

protected:
    MotionNodeTask();
    bool init_micro_ros() override;
    void clean_micro_ros() override;

public:
    void publish_msgs();

private:
    rcl_subscription_t motion_cmd_vel_subscription_, control_cmd_vel_subscription_;
    rcl_publisher_t motion_status_publisher_;
    rcl_service_t motion_settings_service_;
    rcl_timer_t publish_motion_status_timer_;

    std::string motion_cmd_vel_topic_name_;
    std::string motion_services_name_;
    std::string motion_status_topic_name_;

    motion_settings_service__srv__MotionSettingsService_Request motion_settings_request_;
    motion_settings_service__srv__MotionSettingsService_Response motion_settings_response_;
    geometry_msgs__msg__Twist motion_twist_msg_, control_twist_msg_;
    motion_status_msgs__msg__MotionStatus motion_status_msg_;

    bool motion_settings_service_initialized_ = false;
    bool motion_cmd_vel_subscription_initialized_ = false;
    bool control_cmd_vel_subscription_initialized_ = false;
    bool motion_status_publisher_initialized_ = false;
    bool publish_motion_status_timer_initialized_ = false;

    bool _create_publish_motion_status_timer();
    void _destroy_publish_motion_status_timer();

    static void motion_settings_service_callback(const void *req, void *res);
    static void msg_twist_callback(const void *msg);
    static void publish_motion_status_timer_callback(rcl_timer_t *timer, int64_t last_call_time);
};
