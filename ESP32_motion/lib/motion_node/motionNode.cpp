#include "motionNode.h"

MotionNode::MotionNode() {
    task_name_ = "motion_node_task";
    num_handles_ = 4;

    motion_cmd_vel_topic_name_ = constructNodeName(pc_motion_node_namespace, pc_cmd_vel_topic_name);
    motion_status_topic_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_status_topic_name);
    motion_services_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_settings_service_name);

    motionControl_ = &MotionControl::instance();
    mpu6050Control_ = &MPU6050Control::instance();
}

bool MotionNode::init_micro_ros() {
    rcl_ret_t ret;
    if (!motion_cmd_vel_subscription_initialized_) {
        rmw_qos_profile_t my_qos = rmw_qos_profile_default;
        my_qos.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT; // 可靠RMW_QOS_POLICY_RELIABILITY_RELIABLE
        my_qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;           // 保存最后 N 条
        my_qos.depth = 1;                                            // 队列长度
        my_qos.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;      // 临时消息

        ret = rclc_subscription_init(&motion_cmd_vel_subscription_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), motion_cmd_vel_topic_name_.c_str(), &my_qos);
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_motion_cmd_vel_subscription_init_default:%d\n", ret);
            return false;
        } else {
            ret = rclc_executor_add_subscription(&executor_, &motion_cmd_vel_subscription_, &motion_twist_msg_, msg_twist_callback, ON_NEW_DATA);
            if (ret != RCL_RET_OK) {
                Serial.printf("rclc_executor_add_motion_cmd_vel_subscription:%d\n", ret);
                ret = rcl_subscription_fini(&motion_cmd_vel_subscription_, &node_);
                if (ret != RCL_RET_OK) {
                    Serial.printf("rcl_motion_cmd_vel_subscription_fini error:%d\n", ret);
                }
                return false;
            }
        }
        motion_cmd_vel_subscription_initialized_ = true;
    }
    if (!control_cmd_vel_subscription_initialized_) {
        rmw_qos_profile_t my_qos = rmw_qos_profile_default;
        my_qos.reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE; // 可靠RMW_QOS_POLICY_RELIABILITY_RELIABLE
        my_qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;        // 保存最后 N 条
        my_qos.depth = 10;                                        // 队列长度
        my_qos.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;   // 临时消息

        ret = rclc_subscription_init(&control_cmd_vel_subscription_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), "/cmd_vel", &my_qos);
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_control_cmd_vel_subscription_init_default:%d\n", ret);
            return false;
        } else {
            ret = rclc_executor_add_subscription(&executor_, &control_cmd_vel_subscription_, &control_twist_msg_, msg_twist_callback, ON_NEW_DATA);
            if (ret != RCL_RET_OK) {
                Serial.printf("rclc_executor_add_control_cmd_vel_subscription:%d\n", ret);
                ret = rcl_subscription_fini(&control_cmd_vel_subscription_, &node_);
                if (ret != RCL_RET_OK) {
                    Serial.printf("rcl_control_cmd_vel_subscription_fini error:%d\n", ret);
                }
                return false;
            }
        }
        control_cmd_vel_subscription_initialized_ = true;
    }
    if (!odom_publisher_initialized_) {
        ret = rclc_publisher_init_default(&odom_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(nav_msgs, msg, Odometry), "/odom"); //
        if (ret != RCL_RET_OK) {
            Serial.printf("odom_publisher_:rclc_publisher_init_default:%d\n", ret);
            return false;
        }
        odom_publisher_initialized_ = true;
    }
    if (!imu_publisher_initialized_) {
        ret = rclc_publisher_init_default(&imu_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Imu), "/imu"); //
        if (ret != RCL_RET_OK) {
            Serial.printf("imu_publisher_:rclc_publisher_init_default:%d\n", ret);
            return false;
        }
        imu_publisher_initialized_ = true;
    }
    if (!motion_status_publisher_initialized_) {
        ret = rclc_publisher_init_best_effort(&motion_status_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(motion_status_msgs, msg, MotionStatus), motion_status_topic_name_.c_str()); //
        if (ret != RCL_RET_OK) {
            Serial.printf("motion_status_publisher_:rclc_publisher_init_best_effort:%d\n", ret);
            return false;
        }
        motion_status_publisher_initialized_ = true;
    }
    if (!motion_settings_service_initialized_) {
        ret = rclc_service_init_default(&motion_settings_service_, &node_, ROSIDL_GET_SRV_TYPE_SUPPORT(motion_settings_service, srv, MotionSettingsService), motion_services_name_.c_str());
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_service_init_default motion_settings_service:%d\n", ret);
            return false;
        }
        ret = rclc_executor_add_service(&executor_, &motion_settings_service_, &motion_settings_request_, &motion_settings_response_, motion_settings_service_callback);
        if (ret != RCL_RET_OK) {
            Serial.printf("rclc_executor_add_service motion_settings_service:%d\n", ret);
            ret = rcl_service_fini(&motion_settings_service_, &node_);
            if (ret != RCL_RET_OK) {
                Serial.printf("rcl_service_fini motion_settings_service error:%d\n", ret);
            }
            return false;
        }
        motion_settings_service_initialized_ = true;
    }

    return true;
}

void MotionNode::clean_micro_ros() {
    rcl_ret_t ret;

    if (motion_settings_service_initialized_) {
        ret = rcl_service_fini(&motion_settings_service_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rcl_service_fini motion_settings_service error:%d\n", ret);
        }
        motion_settings_service_initialized_ = false;
    }
    if (motion_cmd_vel_subscription_initialized_) {
        ret = rcl_subscription_fini(&motion_cmd_vel_subscription_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rcl_motion_cmd_vel_subscription_fini error:%d\n", ret);
        }
        motion_cmd_vel_subscription_initialized_ = false;
    }
    if (control_cmd_vel_subscription_initialized_) {
        ret = rcl_subscription_fini(&control_cmd_vel_subscription_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rcl_control_cmd_vel_subscription_fini error:%d\n", ret);
        }
        control_cmd_vel_subscription_initialized_ = false;
    }
    if (motion_status_publisher_initialized_) {
        ret = rcl_publisher_fini(&motion_status_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("motion_status_publisher:rcl_publisher_fini error:%d\n", ret);
        }
        motion_status_publisher_initialized_ = false;
    }
    if (odom_publisher_initialized_) {
        ret = rcl_publisher_fini(&odom_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("odom_publisher:rcl_publisher_fini error:%d\n", ret);
        }
        odom_publisher_initialized_ = false;
    }
    if (imu_publisher_initialized_) {
        ret = rcl_publisher_fini(&imu_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("imu_publisher:rcl_publisher_fini error:%d\n", ret);
        }
        imu_publisher_initialized_ = false;
    }
}

void MotionNode::set_enable_pub_motion_status(bool status) {
    enable_pub_motion_status_ = status;
}

bool MotionNode::get_enable_pub_motion_status() {
    return enable_pub_motion_status_;
}

void MotionNode::motion_settings_service_callback(const void *req, void *res) {
    const motion_settings_service__srv__MotionSettingsService_Request *request = (const motion_settings_service__srv__MotionSettingsService_Request *)req;
    motion_settings_service__srv__MotionSettingsService_Response *response = (motion_settings_service__srv__MotionSettingsService_Response *)res;

    MotionNode &instance = MotionNode::instance();

    if (request->mode == MotionService::Type::HeartBeat) {
        ;
    } else if (request->mode == MotionService::Type::Restart) {
        instance.motionControl_->restart_task();
    } else if (request->mode == MotionService::Type::Brake) {
        instance.motionControl_->brake();
    } else if (request->mode == MotionService::Type::StopMove) {
        instance.motionControl_->stop_move();
    } else if (request->mode == MotionService::Type::MoveFront) {
        instance.motionControl_->move_front();
    } else if (request->mode == MotionService::Type::MoveBack) {
        instance.motionControl_->move_back();
    } else if (request->mode == MotionService::Type::MoveLeft) {
        instance.motionControl_->move_left();
    } else if (request->mode == MotionService::Type::MoveRight) {
        instance.motionControl_->move_right();
    } else if (request->mode == MotionService::Type::MoveLeftFront) {
        instance.motionControl_->move_left_front();
    } else if (request->mode == MotionService::Type::MoveRightFront) {
        instance.motionControl_->move_right_front();
    } else if (request->mode == MotionService::Type::MoveLeftBack) {
        instance.motionControl_->move_left_back();
    } else if (request->mode == MotionService::Type::MoveRightBack) {
        instance.motionControl_->move_right_back();
    } else if (request->mode == MotionService::Type::TurnLeft) {
        instance.motionControl_->turn_left();
    } else if (request->mode == MotionService::Type::TurnRight) {
        instance.motionControl_->turn_right();
    }

    else if (request->mode == MotionService::Type::CalibrateIMU) {
        instance.mpu6050Control_->start_calibration();
    }

    else if (request->mode == MotionService::Type::SetSpeedPercent) {
        instance.motionControl_->set_speed_percent(request->speed_percent);
        response->max_v = instance.motionControl_->get_max_speed();
        response->speed_percent = instance.motionControl_->get_speed_percent();
    }

    else if (request->mode == MotionService::Type::SetSpeedPlanState) {
        instance.motionControl_->set_speed_plan_state(request->enable_speed_plan);
    }

    else if (request->mode == MotionService::Type::SetEnablePubMotionStatus) {
        instance.set_enable_pub_motion_status(request->enable_pub_motion_status);
    }

    else if (request->mode == MotionService::Type::ReadParams) {
        instance.motionControl_->read_params(response);
        response->enable_pub_motion_status = instance.get_enable_pub_motion_status();
    } else if (request->mode == MotionService::Type::WriteParams) {
        instance.motionControl_->set_milliseconds(request->milliseconds);
        instance.motionControl_->set_loop_period_cnt(request->position_loop_milliseconds_cnt, request->speed_loop_milliseconds_cnt);

        instance.motionControl_->set_position_pid_params(request->position_p, request->position_i, request->position_d, request->position_max_total_integral);

        instance.motionControl_->set_line_speed_pid_params(request->line_speed_p, request->line_speed_i, request->line_speed_d, request->line_speed_max_total_integral);
        instance.motionControl_->set_angle_speed_pid_params(request->angle_speed_p, request->angle_speed_i, request->angle_speed_d, request->angle_speed_max_total_integral);

        instance.motionControl_->set_left_front_motor_pid_params(request->left_front_motor_p, request->left_front_motor_i, request->left_front_motor_d, request->left_front_motor_max_total_integral);
        instance.motionControl_->set_left_back_motor_pid_params(request->left_back_motor_p, request->left_back_motor_i, request->left_back_motor_d, request->left_back_motor_max_total_integral);

        instance.motionControl_->set_right_front_motor_pid_params(request->right_front_motor_p, request->right_front_motor_i, request->right_front_motor_d, request->right_front_motor_max_total_integral);
        instance.motionControl_->set_right_back_motor_pid_params(request->right_back_motor_p, request->right_back_motor_i, request->right_back_motor_d, request->right_back_motor_max_total_integral);

        instance.motionControl_->set_speed_plan_parms(request->max_v, request->max_acc, request->jerk);

        instance.motionControl_->set_motor_enable_flags(request->motor_enable_flags);

        response->max_v = instance.motionControl_->get_max_speed();
        response->speed_percent = instance.motionControl_->get_speed_percent();
    } else if (request->mode == MotionService::Type::SaveParams) {
        instance.motionControl_->save_params();
    }

    else if (request->mode == MotionService::Type::ReadConfig) {
        instance.motionControl_->read_config(response);
    } else if (request->mode == MotionService::Type::WriteConfig) {
        instance.motionControl_->set_wheel_type(request->is_mecanum_wheel);
        instance.motionControl_->set_model_params(request->track_width, request->wheel_width);
        instance.motionControl_->set_left_front_motor_config_params(request->left_front_motor_pina, request->left_front_motor_pinb, request->left_front_encoder_pina, request->left_front_encoder_pinb, request->left_front_motor_pinpwm,
                                                                    request->left_front_motor_wheel_diameter, request->left_front_motor_pluses_per_revolution, request->left_front_motor_revolutions_per_minute);
        instance.motionControl_->set_left_back_motor_config_params(request->left_back_motor_pina, request->left_back_motor_pinb, request->left_back_encoder_pina, request->left_back_encoder_pinb, request->left_back_motor_pinpwm,
                                                                   request->left_back_motor_wheel_diameter, request->left_back_motor_pluses_per_revolution, request->left_back_motor_revolutions_per_minute);
        instance.motionControl_->set_right_front_motor_config_params(request->right_front_motor_pina, request->right_front_motor_pinb, request->right_front_encoder_pina, request->right_front_encoder_pinb, request->right_front_motor_pinpwm,
                                                                     request->right_front_motor_wheel_diameter, request->right_front_motor_pluses_per_revolution, request->right_front_motor_revolutions_per_minute);
        instance.motionControl_->set_right_back_motor_config_params(request->right_back_motor_pina, request->right_back_motor_pinb, request->right_back_encoder_pina, request->right_back_encoder_pinb, request->right_back_motor_pinpwm,
                                                                    request->right_back_motor_wheel_diameter, request->right_back_motor_pluses_per_revolution, request->right_back_motor_revolutions_per_minute);
        instance.motionControl_->update_target_max_speed();
    } else if (request->mode == MotionService::Type::SaveConfig) {
        instance.motionControl_->save_config();
    }

    response->state = request->mode;
    response->id = request->id;
}

void MotionNode::msg_twist_callback(const void *msg) {
    const geometry_msgs__msg__Twist *twist_msg = static_cast<const geometry_msgs__msg__Twist *>(msg);
    MotionNode::instance().motionControl_->set_twist(*twist_msg);
}

void MotionNode::publish_msgs() {
    auto odom_msg = motionControl_->get_odom_msg();
    auto imu_msg = mpu6050Control_->get_imu_msg();

    update_timestamp(odom_msg.header.stamp);
    update_timestamp(imu_msg.header.stamp);

    rcl_ret_t ret;
    ret = rcl_publish(&odom_publisher_, &odom_msg, NULL);
    if (ret != RCL_RET_OK) {
        Serial.printf("error: pub odom msg failed:%d\n", ret);
    }

    ret = rcl_publish(&imu_publisher_, &imu_msg, NULL);
    if (ret != RCL_RET_OK) {
        Serial.printf("error: pub imu msg failed:%d\n", ret);
    }

    if (enable_pub_motion_status_) {
        ret = rcl_publish(&motion_status_publisher_, &motionControl_->get_motion_status_msg(), NULL);
        if (ret != RCL_RET_OK) {
            Serial.printf("error: pub motion status msg failed:%d\n", ret);
        }
    }
}