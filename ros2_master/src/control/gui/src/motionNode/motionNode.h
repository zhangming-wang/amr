#pragma once

#include "../baseNode/nodeThread.h"
#include "../common/settings.h"
#include "../common/system.h"
#include "geometry_msgs/msg/pose2_d.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "motion_settings_service/srv/motion_settings_service.hpp"
#include "motion_status_msgs/msg/motion_status.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2_ros/static_transform_broadcaster.h>

using MotionSettingsSrv = motion_settings_service::srv::MotionSettingsService;
using MotionStatusMsg = motion_status_msgs::msg::MotionStatus;

class MotionNode : public NodeThread {
    Q_OBJECT

public:
    MotionNode(QObject *parent = nullptr);
    void publish_twist(std::shared_ptr<geometry_msgs::msg::Twist> twist);
    void ask_service_response(MotionSettingsSrv::Request::SharedPtr request);
    void set_model_param(double track_width, double wheel_width, bool is_mecanum_wheel);

signals:
    void motionStatusMsgChanged(MotionStatusMsg::SharedPtr);
    void serviceResponsed(uint64_t id, MotionSettingsSrv::Response::SharedPtr);

private:
    rclcpp::Subscription<MotionStatusMsg>::SharedPtr motion_status_subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_publisher_;
    rclcpp::Client<MotionSettingsSrv>::SharedPtr service_client_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_publisher_;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_publisher_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_publisher_;
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> static_broadcaster_;

    sensor_msgs::msg::Imu imu_msg_;
    nav_msgs::msg::Odometry odom_msg_;
    geometry_msgs::msg::Pose2D current_pose2d_;
    geometry_msgs::msg::Pose current_pose_;
    geometry_msgs::msg::Twist current_twist_;
    sensor_msgs::msg::JointState current_joint_state_;

    MotionStatusMsg::SharedPtr last_motion_status_msg_ = nullptr;

    double track_width_ = 1.0, wheel_width_ = 1.0;
    bool is_mecanum_wheel_ = false;

    void _construct_imu_msg(const MotionStatusMsg::SharedPtr msg);
    void _construct_odom_msg(const MotionStatusMsg::SharedPtr msg);
    void _construct_joint_state_msg(const MotionStatusMsg::SharedPtr msg);

    void _forwardKinematicsDistance(double left_front_distance, double left_back_distance, double right_front_distance, double right_back_distance);
    void _forwardKinematicsSpeed(double left_front_speed, double left_back_speed, double right_front_speed, double right_back_speed);

    void _pub_static_odomToBasefootprint_tf();

    void recv_motion_status_msg(const MotionStatusMsg::SharedPtr msg);
};
