#include "motionNode.h"

MotionNode::MotionNode(QObject *parent)
    : NodeThread(std::make_shared<rclcpp::Node>(pc_motion_node_name, pc_motion_node_namespace),
                 constructNodeName(esp32_motion_node_namespace, esp32_motion_serial_msg_topic_name),
                 constructNodeName(esp32_motion_node_namespace, esp32_motion_heartbeat_topic_name),
                 parent) {
    qRegisterMetaType<MotionSettingsSrv::Response::SharedPtr>("const MotionSettingsSrv::Response::SharedPtr");
    qRegisterMetaType<MotionStatusMsg::SharedPtr>("const MotionStatusMsg::SharedPtr");

    static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(node_);
    _pub_static_odomToBasefootprint_tf();

    service_client_ = node_->create_client<MotionSettingsSrv>(constructNodeName(esp32_motion_node_namespace, esp32_motion_settings_service_name));
    motion_status_subscription_ = node_->create_subscription<MotionStatusMsg>(constructNodeName(esp32_motion_node_namespace, esp32_motion_status_topic_name), best_effort_qos_, std::bind(&MotionNode::recv_motion_status_msg, this, std::placeholders::_1));

    twist_publisher_ = node_->create_publisher<geometry_msgs::msg::Twist>(constructNodeName(pc_motion_node_namespace, pc_cmd_vel_topic_name), best_effort_qos_);
    joint_state_publisher_ = node_->create_publisher<sensor_msgs::msg::JointState>("/joint_states", best_effort_qos_);
    odom_publisher_ = node_->create_publisher<nav_msgs::msg::Odometry>("/odom", reliable_qos_);
    imu_publisher_ = node_->create_publisher<sensor_msgs::msg::Imu>("/imu", best_effort_qos_);

    current_joint_state_.name = {"left_front_wheel_joint", "left_back_wheel_joint", "right_front_wheel_joint", "right_back_wheel_joint"};
    current_joint_state_.position.resize(4, 0.0);
    current_joint_state_.velocity.resize(4, 0.0);
    current_joint_state_.effort.resize(4, 0.0);
    current_joint_state_.header.frame_id = "base_footprint";

    imu_msg_.header.frame_id = "imu_link";
    for (int i = 0; i < 9; ++i) {
        imu_msg_.orientation_covariance[i] = 0.0;
        imu_msg_.angular_velocity_covariance[i] = 0.0;
        imu_msg_.linear_acceleration_covariance[i] = 0.0;
    }
    imu_msg_.orientation_covariance[0] = 0.02 * 0.02; // roll
    imu_msg_.orientation_covariance[4] = 0.02 * 0.02; // pitch
    imu_msg_.orientation_covariance[8] = 1e6;         // yaw（无磁力计）

    // angular velocity
    imu_msg_.angular_velocity_covariance[0] = 0.001 * 0.001;
    imu_msg_.angular_velocity_covariance[4] = 0.001 * 0.001;
    imu_msg_.angular_velocity_covariance[8] = 0.001 * 0.001;

    // linear acceleration
    imu_msg_.linear_acceleration_covariance[0] = -1;
    imu_msg_.linear_acceleration_covariance[4] = -1;
    imu_msg_.linear_acceleration_covariance[8] = -1;

    odom_msg_.header.frame_id = "odom";
    odom_msg_.child_frame_id = "base_footprint";
    odom_msg_.pose.covariance.fill(0.0);
    odom_msg_.pose.covariance[0] = 0.02 * 0.02;
    odom_msg_.pose.covariance[7] = 0.02 * 0.02;
    odom_msg_.pose.covariance[14] = 1e6;
    odom_msg_.pose.covariance[21] = 1e6;
    odom_msg_.pose.covariance[28] = 1e6;
    odom_msg_.pose.covariance[35] = 0.05 * 0.05;

    // twist
    odom_msg_.twist.covariance.fill(0.0);
    odom_msg_.twist.covariance[0] = 0.1 * 0.1;
    odom_msg_.twist.covariance[7] = 0.1 * 0.1;
    odom_msg_.twist.covariance[14] = 1e6;
    odom_msg_.twist.covariance[21] = 1e6;
    odom_msg_.twist.covariance[28] = 1e6;
    odom_msg_.twist.covariance[35] = 0.1 * 0.1;
}

void MotionNode::_pub_static_odomToBasefootprint_tf() {
    geometry_msgs::msg::TransformStamped odom2base;
    odom2base.header.stamp = node_->now();
    odom2base.header.frame_id = "odom";
    odom2base.child_frame_id = "base_footprint";
    odom2base.transform.translation.x = 0.0;
    odom2base.transform.translation.y = 0.0;
    odom2base.transform.translation.z = 0.0;
    odom2base.transform.rotation.x = 0.0;
    odom2base.transform.rotation.y = 0.0;
    odom2base.transform.rotation.z = 0.0;
    odom2base.transform.rotation.w = 1.0;
    static_broadcaster_->sendTransform(odom2base);
}

void MotionNode::_construct_joint_state_msg(const MotionStatusMsg::SharedPtr msg) {
    current_joint_state_.header.stamp = rclcpp::Time(msg->stamp / 1000000000, msg->stamp % 1000000000);
    current_joint_state_.position[0] = msg->left_front_total_distance;
    current_joint_state_.position[1] = msg->left_back_total_distance;
    current_joint_state_.position[2] = msg->right_front_total_distance;
    current_joint_state_.position[3] = msg->right_back_total_distance;

    current_joint_state_.velocity[0] = msg->left_front_current_v;
    current_joint_state_.velocity[1] = msg->left_back_current_v;
    current_joint_state_.velocity[2] = msg->right_front_current_v;
    current_joint_state_.velocity[3] = msg->right_back_current_v;

    joint_state_publisher_->publish(current_joint_state_);
}

void MotionNode::_construct_imu_msg(const MotionStatusMsg::SharedPtr msg) {
    imu_msg_.header.stamp = rclcpp::Time(msg->stamp / 1000000000, msg->stamp % 1000000000);
    tf2::Quaternion q;
    q.setRPY(msg->imu_roll, msg->imu_pitch, msg->imu_yaw); // 弧度
    imu_msg_.orientation.x = q.x();
    imu_msg_.orientation.y = q.y();
    imu_msg_.orientation.z = q.z();
    imu_msg_.orientation.w = q.w();

    // angular velocity
    imu_msg_.angular_velocity.x = msg->imu_gyro_x;
    imu_msg_.angular_velocity.y = msg->imu_gyro_y;
    imu_msg_.angular_velocity.z = msg->imu_gyro_z;

    // linear acceleration
    imu_msg_.linear_acceleration.x = 0.0;
    imu_msg_.linear_acceleration.y = 0.0;
    imu_msg_.linear_acceleration.z = 0.0;

    imu_publisher_->publish(imu_msg_);
}

void MotionNode::_construct_odom_msg(const MotionStatusMsg::SharedPtr msg) {
    odom_msg_.header.stamp = rclcpp::Time(msg->stamp / 1000000000, msg->stamp % 1000000000);

    if (last_motion_status_msg_ && msg->seq - last_motion_status_msg_->seq != 1) {
        _forwardKinematicsDistance(msg->left_front_total_distance - last_motion_status_msg_->left_front_total_distance, msg->left_back_total_distance - last_motion_status_msg_->left_back_total_distance, msg->right_front_total_distance - last_motion_status_msg_->right_front_total_distance, msg->right_back_total_distance - last_motion_status_msg_->right_back_total_distance);
    } else {
        _forwardKinematicsDistance(msg->left_front_dt_distance, msg->left_back_dt_distance, msg->right_front_dt_distance, msg->right_back_dt_distance);
    }

    _forwardKinematicsSpeed(msg->left_front_current_v, msg->left_back_current_v, msg->right_front_current_v, msg->right_back_current_v);
    last_motion_status_msg_ = msg;

    odom_msg_.pose.pose = current_pose_;
    odom_msg_.twist.twist = current_twist_;

    odom_publisher_->publish(odom_msg_);
}

void MotionNode::_forwardKinematicsDistance(double left_front_distance, double left_back_distance, double right_front_distance, double right_back_distance) {
    if (is_mecanum_wheel_) {
        double dx = (left_front_distance + left_back_distance + right_front_distance + right_back_distance) / 4.0;
        double dy = (-left_front_distance + left_back_distance - right_front_distance + right_back_distance) / 4.0;
        double dtheta = (-left_front_distance + left_back_distance + right_front_distance - right_back_distance) / (4.0 * (track_width_ + wheel_width_));

        double cos_yaw = cos(current_pose2d_.theta);
        double sin_yaw = sin(current_pose2d_.theta);

        current_pose2d_.x += cos_yaw * dx - sin_yaw * dy;
        current_pose2d_.y += sin_yaw * dx + cos_yaw * dy;
        current_pose2d_.theta += dtheta;
    } else {
        double dl = 0.5 * (left_front_distance + left_back_distance);
        double dr = 0.5 * (right_front_distance + right_back_distance);
        double d_center = 0.5 * (dl + dr);
        double dtheta = (dr - dl) / track_width_;
        double yaw_mid = current_pose2d_.theta + 0.5 * dtheta;

        current_pose2d_.x += d_center * cos(yaw_mid);
        current_pose2d_.y += d_center * sin(yaw_mid);
        current_pose2d_.theta += dtheta;
    }

    current_pose2d_.theta = atan2(sin(current_pose2d_.theta), cos(current_pose2d_.theta));

    current_pose_.position.x = current_pose2d_.x;
    current_pose_.position.y = current_pose2d_.y;
    current_pose_.position.z = 0.0;

    current_pose_.orientation.x = 0.0;
    current_pose_.orientation.y = 0.0;
    current_pose_.orientation.z = sin(current_pose2d_.theta * 0.5);
    current_pose_.orientation.w = cos(current_pose2d_.theta * 0.5);
}

void MotionNode::_forwardKinematicsSpeed(double left_front_speed, double left_back_speed, double right_front_speed, double right_back_speed) {
    if (is_mecanum_wheel_) {
        current_twist_.linear.x = (left_front_speed - left_back_speed - right_front_speed + right_back_speed) / 4.0;
        current_twist_.linear.y = (left_front_speed + left_back_speed + right_front_speed + right_back_speed) / 4.0;
        current_twist_.angular.z = (-left_front_speed - left_back_speed + right_front_speed + right_back_speed) / (2.0 * (track_width_ + wheel_width_));
    } else {
        double v_left = (left_front_speed + left_back_speed) / 2.0;
        double v_right = (right_front_speed + right_back_speed) / 2.0;

        current_twist_.linear.x = (v_left + v_right) / 2.0;
        current_twist_.linear.y = 0.0;
        current_twist_.angular.z = (v_right - v_left) / track_width_;
    }
}

void MotionNode::set_model_param(double track_width, double wheel_width, bool is_mecanum_wheel) {
    track_width_ = track_width;
    wheel_width_ = wheel_width;
    is_mecanum_wheel_ = is_mecanum_wheel;
}

void MotionNode::publish_twist(std::shared_ptr<geometry_msgs::msg::Twist> twist) {
    if (connected()) {
        twist_publisher_->publish(*twist);
    }
}

void MotionNode::recv_motion_status_msg(const MotionStatusMsg::SharedPtr msg) {
    _construct_imu_msg(msg);
    _construct_odom_msg(msg);
    _construct_joint_state_msg(msg);
    emit motionStatusMsgChanged(msg);
}

void MotionNode::ask_service_response(MotionSettingsSrv::Request::SharedPtr request) {
    if (!connected()) {
        emit serviceResponsed(request->id, nullptr);
        return;
    }

    auto id = request->id;

    if (service_client_->service_is_ready()) {
        service_client_->async_send_request(request,
                                            [this, id](rclcpp::Client<MotionSettingsSrv>::SharedFuture future) {
                                                emit serviceResponsed(id, future.get());
                                            });
    } else {
        emit serviceResponsed(id, nullptr);
    }
}