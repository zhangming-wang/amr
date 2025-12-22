#include "motionNode.h"

MotionNode::MotionNode() {
    task_name_ = "motion_node_task";
    num_handles_ = 6;

    node_name_ = esp32_motion_node_name;
    node_namespace_ = esp32_motion_node_namespace;
    serial_msg_topic_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_serial_msg_topic_name);
    heartbeat_topic_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_heartbeat_topic_name);

    motion_services_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_settings_service_name);

    motion_status_topic_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_status_topic_name);
    motion_cmd_vel_topic_name_ = constructNodeName(pc_motion_node_namespace, pc_cmd_vel_topic_name);

    motionControl_ = &MotionControl::instance();
    mpu6050Control_ = &MPU6050Control::instance();
}

bool MotionNode::init_micro_ros() {
    rmw_qos_profile_t best_effort_qos = rmw_qos_profile_default;
    best_effort_qos.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
    best_effort_qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    best_effort_qos.depth = 1;
    best_effort_qos.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    rcl_ret_t ret;
    if (!motion_cmd_vel_subscription_initialized_) {
        ret = rclc_subscription_init(&motion_cmd_vel_subscription_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), motion_cmd_vel_topic_name_.c_str(), &best_effort_qos);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] cmd_vel subscription init failed: %d\n", ret);
            return false;
        }

        ret = rclc_executor_add_subscription(&executor_,
                                             &motion_cmd_vel_subscription_, &motion_twist_msg_, msg_twist_callback, ON_NEW_DATA);

        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] cmd_vel subscription add to executor failed: %d\n", ret);
            ret = rcl_subscription_fini(&motion_cmd_vel_subscription_, &node_);
            return false;
        }
        motion_cmd_vel_subscription_initialized_ = true;
    }

    if (!control_cmd_vel_subscription_initialized_) {
        ret = rclc_subscription_init_default(&control_cmd_vel_subscription_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), cmd_vel_topic_name);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] control cmd_vel subscription init failed: %d\n", ret);
            return false;
        }

        ret = rclc_executor_add_subscription(&executor_, &control_cmd_vel_subscription_, &control_twist_msg_, msg_twist_callback, ON_NEW_DATA);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] control cmd_vel subscription add to executor failed: %d\n", ret);
            ret = rcl_subscription_fini(&control_cmd_vel_subscription_, &node_);
            return false;
        }
        control_cmd_vel_subscription_initialized_ = true;
    }

    if (!motion_status_publisher_initialized_) {
        ret = rclc_publisher_init(&motion_status_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(motion_status_msgs, msg, MotionStatus), motion_status_topic_name_.c_str(), &best_effort_qos);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] motion status publisher init failed: %d\n", ret);
            return false;
        }
        motion_status_publisher_initialized_ = true;
    }

    if (!motion_settings_service_initialized_) {
        ret = rclc_service_init_default(&motion_settings_service_, &node_, ROSIDL_GET_SRV_TYPE_SUPPORT(motion_settings_service, srv, MotionSettingsService), motion_services_name_.c_str());
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] motion settings service init failed: %d\n", ret);
            return false;
        }

        ret = rclc_executor_add_service(&executor_, &motion_settings_service_, &motion_settings_request_, &motion_settings_response_, motion_settings_service_callback);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] motion settings service add to executor failed: %d\n", ret);
            ret = rcl_service_fini(&motion_settings_service_, &node_);
            return false;
        }
        motion_settings_service_initialized_ = true;
    }

    return _create_publish_motion_status_timer();
}

void MotionNode::clean_micro_ros() {
    _destroy_publish_motion_status_timer();
    rcl_ret_t ret;
    if (motion_settings_service_initialized_) {
        ret = rclc_executor_remove_service(&executor_, &motion_settings_service_);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] motion settings service remove from executor failed: %d\n", ret);
        }
        ret = rcl_service_fini(&motion_settings_service_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] motion settings service fini failed: %d\n", ret);
        }
        motion_settings_service_initialized_ = false;
    }

    if (motion_cmd_vel_subscription_initialized_) {
        ret = rcl_subscription_fini(&motion_cmd_vel_subscription_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] cmd_vel subscription fini failed: %d\n", ret);
        }
        motion_cmd_vel_subscription_initialized_ = false;
    }

    if (control_cmd_vel_subscription_initialized_) {
        ret = rcl_subscription_fini(&control_cmd_vel_subscription_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] control cmd_vel subscription fini failed: %d\n", ret);
        }
        control_cmd_vel_subscription_initialized_ = false;
    }

    if (motion_status_publisher_initialized_) {
        ret = rcl_publisher_fini(&motion_status_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] motion status publisher fini failed: %d\n", ret);
        }
        motion_status_publisher_initialized_ = false;
    }
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

    else if (request->mode == MotionService::Type::CalibrateMPU6050) {
        instance.mpu6050Control_->start_calibration();
    }

    else if (request->mode == MotionService::Type::SetSpeedPercent) {
        instance.motionControl_->set_speed_percent(request->speed_percent);
        response->max_v = instance.motionControl_->get_max_speed();
        response->speed_percent = instance.motionControl_->get_speed_percent();
    } else if (request->mode == MotionService::Type::SetSpeedPlanState) {
        instance.motionControl_->set_speed_plan_state(request->enable_speed_plan);
    }

    else if (request->mode == MotionService::Type::ReadParams) {
        instance.motionControl_->read_params(response);
        instance.mpu6050Control_->read_params(response);
    } else if (request->mode == MotionService::Type::WriteParams) {
        if (instance.motionControl_->get_milliseconds() != request->milliseconds) {
            instance.motionControl_->set_milliseconds(request->milliseconds);
            instance._create_publish_motion_status_timer();
        }

        instance.motionControl_->set_left_front_motor_pid_params(request->left_front_motor_p, request->left_front_motor_i, request->left_front_motor_d, request->left_front_motor_max_total_integral);
        instance.motionControl_->set_left_back_motor_pid_params(request->left_back_motor_p, request->left_back_motor_i, request->left_back_motor_d, request->left_back_motor_max_total_integral);

        instance.motionControl_->set_right_front_motor_pid_params(request->right_front_motor_p, request->right_front_motor_i, request->right_front_motor_d, request->right_front_motor_max_total_integral);
        instance.motionControl_->set_right_back_motor_pid_params(request->right_back_motor_p, request->right_back_motor_i, request->right_back_motor_d, request->right_back_motor_max_total_integral);

        instance.motionControl_->set_speed_plan_parms(request->max_v, request->max_acc, request->jerk);

        instance.motionControl_->set_motor_enable_flags(request->motor_enable_flags);

        response->max_v = instance.motionControl_->get_max_speed();
        response->speed_percent = instance.motionControl_->get_speed_percent();

        instance.mpu6050Control_->set_offset(request->mpu6050_accel_offset_x, request->mpu6050_accel_offset_y, request->mpu6050_accel_offset_z,
                                             request->mpu6050_gyro_offset_x, request->mpu6050_gyro_offset_y, request->mpu6050_gyro_offset_z);
    } else if (request->mode == MotionService::Type::SaveParams) {
        instance.motionControl_->save_params();
        instance.mpu6050Control_->save_params();
    }

    else if (request->mode == MotionService::Type::ReadConfig) {
        instance.motionControl_->read_config(response);
        instance.mpu6050Control_->read_config(response);
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

        instance.mpu6050Control_->set_pins(request->mpu6050_pin_sda, request->mpu6050_pin_scl);
    } else if (request->mode == MotionService::Type::SaveConfig) {
        instance.motionControl_->save_config();
        instance.mpu6050Control_->save_config();
    }

    response->state = request->mode;
    response->id = request->id;
}

void MotionNode::msg_twist_callback(const void *msg) {
    const geometry_msgs__msg__Twist *twist_msg = static_cast<const geometry_msgs__msg__Twist *>(msg);
    MotionNode::instance().motionControl_->set_twist(*twist_msg);
}

void MotionNode::publish_msgs() {
    if (!connected()) {
        return;
    }

    if (motion_status_publisher_initialized_) {
        motion_status_msg_.stamp = get_now_ns();
        motionControl_->get_motion_status(motion_status_msg_);
        mpu6050Control_->get_motion_status(motion_status_msg_);
        rcl_ret_t ret = rcl_publish(&motion_status_publisher_, &motion_status_msg_, nullptr);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] motion status publish failed: %d\n", ret);
        }
    }
}

void MotionNode::publish_motion_status_timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
    MotionNode::instance().publish_msgs();
}

bool MotionNode::_create_publish_motion_status_timer() {
    _destroy_publish_motion_status_timer();

    if (!publish_motion_status_timer_initialized_) {
        rcl_ret_t ret = rclc_timer_init_default(&publish_motion_status_timer_, &support_, RCL_MS_TO_NS(motionControl_->get_milliseconds()), publish_motion_status_timer_callback);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] publish motion status timer init failed: %d\n", ret);
            return false;
        }
        ret = rclc_executor_add_timer(&executor_, &publish_motion_status_timer_);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] publish motion status timer add to executor failed: %d\n", ret);
            ret = rcl_timer_fini(&publish_motion_status_timer_);
            return false;
        }
        publish_motion_status_timer_initialized_ = true;
    }

    return true;
}

void MotionNode::_destroy_publish_motion_status_timer() {
    if (publish_motion_status_timer_initialized_) {
        rcl_ret_t ret = rclc_executor_remove_timer(&executor_, &publish_motion_status_timer_);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] publish motion status timer remove from executor failed: %d\n", ret);
        }
        ret = rcl_timer_fini(&publish_motion_status_timer_);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] publish motion status timer fini failed: %d\n", ret);
        }
        publish_motion_status_timer_initialized_ = false;
    }
}