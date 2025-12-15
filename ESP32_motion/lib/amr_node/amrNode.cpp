#include "amrNode.h"

void (*serial_print)(const std::string &) = AMRNode::_serial_print;

AMRNode::AMRNode() {
    task_name_ = "amr_node_task";
    core_id_ = 0;
    priority_ = 3;
    IPAddress agent_ip;
    agent_ip.fromString(wifi_IP.c_str());
    locator_.address = agent_ip;
    locator_.port = micro_ros_port;
    allocator_ = rcl_get_default_allocator();

    rcl_ret_t ret = rcl_clock_init(RCL_STEADY_TIME, &clock_);
    if (ret != RCL_RET_OK) {
        serial_print("rcl_clock_init error: " + std::to_string(ret));
    }

    motionControl_ = &MotionControl::instance();
    mpu6050Control_ = &MPU6050Control::instance();
}

bool AMRNode::init_micro_ros() {
    clean_micro_ros();
    int num_handles = 4;
    rcl_ret_t ret;

    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    auto status = rmw_uros_set_custom_transport(
        false,
        (void *)&locator_,
        platformio_transport_open,
        platformio_transport_close,
        platformio_transport_write,
        platformio_transport_read);

    if (status != 0) {
        serial_print("rmw_uros_set_custom_transport:" + std::to_string(status));
        return false;
    }

    // set_microros_wifi_transports(const_cast<char *>(wifi_name_.c_str()), const_cast<char *>(wifi_passward_.c_str()), agent_ip, port_);

    if (!support_initialized_) {
        ret = rclc_support_init(&support_, 0, NULL, &allocator_);
        if (ret != RCL_RET_OK) {
            serial_print("rclc_support_init:" + std::to_string(ret));
            return false;
        }
        support_initialized_ = true;
    }

    while (!rmw_uros_epoch_synchronized()) {
        rmw_uros_sync_session(1000);
        delay(10);
    }

    if (!node_initialized_) {
        node_ = rcl_get_zero_initialized_node();
        ret = rclc_node_init_default(&node_, esp32_motion_node_name.c_str(), esp32_motion_node_namespace.c_str(), &support_);
        if (ret != RCL_RET_OK) {
            serial_print("rcl_get_zero_initialized_node:" + std::to_string(ret));
            return false;
        }
        node_initialized_ = true;
    }

    if (!executor_initialized_) {
        ret = rclc_executor_init(&executor_, &support_.context, num_handles, &allocator_);
        if (ret != RCL_RET_OK) {
            serial_print("rclc_executor_init:" + std::to_string(ret));
            return false;
        }
        executor_initialized_ = true;
    }

    if (!motion_cmd_vel_subscription_initialized_) {
        rmw_qos_profile_t my_qos = rmw_qos_profile_default;
        my_qos.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT; // 可靠RMW_QOS_POLICY_RELIABILITY_RELIABLE
        my_qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;           // 保存最后 N 条
        my_qos.depth = 1;                                            // 队列长度
        my_qos.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;      // 临时消息

        ret = rclc_subscription_init(&motion_cmd_vel_subscription_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), constructNodeName(pc_motion_node_namespace, pc_cmd_vel_topic_name).c_str(), &my_qos);
        if (ret != RCL_RET_OK) {
            serial_print("rclc_motion_cmd_vel_subscription_init_default:" + std::to_string(ret));
            return false;
        } else {
            ret = rclc_executor_add_subscription(&executor_, &motion_cmd_vel_subscription_, &msg_cmd_vel, msg_twist_callback, ON_NEW_DATA);
            if (ret != RCL_RET_OK) {
                serial_print("rclc_executor_add_subscription:" + std::to_string(ret));
                ret = rcl_subscription_fini(&motion_cmd_vel_subscription_, &node_);
                if (ret != RCL_RET_OK) {
                    serial_print("rcl_motion_cmd_vel_subscription_fini error: " + std::to_string(ret));
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
            serial_print("rclc_control_cmd_vel_subscription_init_default:" + std::to_string(ret));
            return false;
        } else {
            ret = rclc_executor_add_subscription(&executor_, &control_cmd_vel_subscription_, &msg_cmd_vel, msg_twist_callback, ON_NEW_DATA);
            if (ret != RCL_RET_OK) {
                serial_print("rclc_executor_add_control_cmd_vel_subscription:" + std::to_string(ret));
                ret = rcl_subscription_fini(&control_cmd_vel_subscription_, &node_);
                if (ret != RCL_RET_OK) {
                    serial_print("rcl_control_cmd_vel_subscription_fini error: " + std::to_string(ret));
                }
                return false;
            }
        }
        control_cmd_vel_subscription_initialized_ = true;
    }

    if (!odom_publisher_initialized_) {
        ret = rclc_publisher_init_default(&odom_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(nav_msgs, msg, Odometry), "/odom"); //
        if (ret != RCL_RET_OK) {
            serial_print("odom_publisher_:rclc_publisher_init_default:" + std::to_string(ret));
            return false;
        }
        odom_publisher_initialized_ = true;
    }
    if (!imu_publisher_initialized_) {
        ret = rclc_publisher_init_default(&imu_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Imu), "/imu"); //
        if (ret != RCL_RET_OK) {
            serial_print("imu_publisher_:rclc_publisher_init_default:" + std::to_string(ret));
            return false;
        }
        imu_publisher_initialized_ = true;
    }

    if (!motion_status_publisher_initialized_) {
        ret = rclc_publisher_init_best_effort(&motion_status_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(motion_status_msgs, msg, MotionStatus), esp32_motion_status_topic_name); //
        if (ret != RCL_RET_OK) {
            serial_print("motion_status_publisher_:rclc_publisher_init_default:" + std::to_string(ret));
            return false;
        }
        motion_status_publisher_initialized_ = true;
    }

    if (!serial_msg_publisher_initialized_) {
        ret = rclc_publisher_init_best_effort(&serial_msg_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), esp32_motion_serial_msg_topic_name); //
        if (ret != RCL_RET_OK) {
            serial_print("serial_msg_publisher_:rclc_publisher_init_default:" + std::to_string(ret));
            return false;
        }
        serial_msg_publisher_initialized_ = true;
    }

    if (!motion_settings_service_initialized_) {
        ret = rclc_service_init_default(&motion_settings_service_, &node_, ROSIDL_GET_SRV_TYPE_SUPPORT(motion_settings_service, srv, MotionSettingsService), esp32_motion_settings_service_name);
        if (ret != RCL_RET_OK) {
            serial_print("rclc_service_init_default motion_settings_service:" + std::to_string(ret));
            return false;
        }
        ret = rclc_executor_add_service(&executor_, &motion_settings_service_, &motion_settings_request_, &motion_settings_response_, motion_settings_service_callback);
        if (ret != RCL_RET_OK) {
            serial_print("rclc_executor_add_service motion_settings_service:" + std::to_string(ret));
            ret = rcl_service_fini(&motion_settings_service_, &node_);
            if (ret != RCL_RET_OK) {
                serial_print("rcl_service_fini motion_settings_service error: " + std::to_string(ret));
            }
            return false;
        }
        motion_settings_service_initialized_ = true;
    }

    return true;
}

void AMRNode::clean_micro_ros() {
    rcl_ret_t ret;

    if (motion_settings_service_initialized_) {
        ret = rcl_service_fini(&motion_settings_service_, &node_);
        if (ret != RCL_RET_OK) {
            serial_print("rcl_service_fini motion_settings_service error: " + std::to_string(ret));
        }
        motion_settings_service_initialized_ = false;
    }
    if (motion_cmd_vel_subscription_initialized_) {
        ret = rcl_subscription_fini(&motion_cmd_vel_subscription_, &node_);
        if (ret != RCL_RET_OK) {
            serial_print("rcl_motion_cmd_vel_subscription_fini error: " + std::to_string(ret));
        }
        motion_cmd_vel_subscription_initialized_ = false;
    }
    if (control_cmd_vel_subscription_initialized_) {
        ret = rcl_subscription_fini(&control_cmd_vel_subscription_, &node_);
        if (ret != RCL_RET_OK) {
            serial_print("rcl_control_cmd_vel_subscription_fini error: " + std::to_string(ret));
        }
        control_cmd_vel_subscription_initialized_ = false;
    }

    if (motion_status_publisher_initialized_) {
        ret = rcl_publisher_fini(&motion_status_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            serial_print("motion_status_publisher:rcl_publisher_fini error: " + std::to_string(ret));
        }
        motion_status_publisher_initialized_ = false;
    }
    if (odom_publisher_initialized_) {
        ret = rcl_publisher_fini(&odom_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            serial_print("odom_publisher:rcl_publisher_fini error: " + std::to_string(ret));
        }
        odom_publisher_initialized_ = false;
    }
    if (imu_publisher_initialized_) {
        ret = rcl_publisher_fini(&imu_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            serial_print("imu_publisher:rcl_publisher_fini error: " + std::to_string(ret));
        }
        imu_publisher_initialized_ = false;
    }

    if (serial_msg_publisher_initialized_) {
        ret = rcl_publisher_fini(&serial_msg_publisher_, &node_);
        if (ret != RCL_RET_OK) {
            serial_print("serial_msg_publisher_:rcl_publisher_fini error: " + std::to_string(ret));
        }
        serial_msg_publisher_initialized_ = false;
    }
    if (executor_initialized_) {
        ret = rclc_executor_fini(&executor_);
        if (ret != RCL_RET_OK) {
            serial_print("executor_initialized_ error: " + std::to_string(ret));
        }
        executor_initialized_ = false;
    }
    if (node_initialized_) {
        ret = rcl_node_fini(&node_);
        if (ret != RCL_RET_OK) {
            serial_print("rcl_node_fini error: " + std::to_string(ret));
        }
        node_initialized_ = false;
    }
    if (support_initialized_) {
        ret = rclc_support_fini(&support_);
        if (ret != RCL_RET_OK) {
            serial_print("rclc_support_fini error: " + std::to_string(ret));
        }
        support_initialized_ = false;
    }
}

void AMRNode::set_enable_pub_motion_status(bool status) {
    enable_pub_motion_status_ = status;
}

bool AMRNode::get_enable_pub_motion_status() {
    return enable_pub_motion_status_;
}

rcl_publisher_t *AMRNode::get_motion_status_publisher() {
    return &motion_status_publisher_;
}

rcl_publisher_t *AMRNode::get_odom_publisher() {
    return &odom_publisher_;
}

rcl_publisher_t *AMRNode::get_serial_msg_publisher() {
    return &serial_msg_publisher_;
}

void AMRNode::update() {
    if (!connected_) {
        if (!init_micro_ros()) {
            serial_print("motion node init failed, try again...");
            vTaskDelay(pdMS_TO_TICKS(500));
            break;
        } else {
            serial_print("motion node task is running...");
            connected_ = true;
        }
    }

    rclc_executor_spin_some(&executor_, RCL_MS_TO_NS(motionControl_->get_milliseconds()));
    if (rmw_uros_ping_agent(100, 10) != RCL_RET_OK) {
        serial_print("motion node is disconnected, reconnecting...");
        connected_ = false;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void AMRNode::sleep() {
    vTaskDelay(pdMS_TO_TICKS(motionControl_->get_milliseconds()));
}

void AMRNode::motion_settings_service_callback(const void *req, void *res) {
    const motion_settings_service__srv__MotionSettingsService_Request *request = (const motion_settings_service__srv__MotionSettingsService_Request *)req;
    motion_settings_service__srv__MotionSettingsService_Response *response = (motion_settings_service__srv__MotionSettingsService_Response *)res;

    AMRNode &instance = AMRNode::instance();

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

void AMRNode::msg_twist_callback(const void *msg) {
    const geometry_msgs__msg__Twist *twist_msg = static_cast<const geometry_msgs__msg__Twist *>(msg);
    AMRNode::instance().motionControl_->set_twist(*twist_msg);
}

void AMRNode::publish_msgs() {
    rcl_time_point_value_t now_ns;
    rcl_clock_get_now(&clock_, &now_ns);

    auto odom_msg = motionControl_->get_odom_msg();
    auto imu_msg = mpu6050Control_->get_imu_msg();

    odom_msg.header.stamp.sec = now_ns / 1000000000;
    odom_msg.header.stamp.nanosec = now_ns % 1000000000;
    imu_msg.header.stamp.sec = now_ns / 1000000000;
    imu_msg.header.stamp.nanosec = now_ns % 1000000000;

    rcl_ret_t ret;

    ret = rcl_publish(&odom_publisher_, &odom_msg, NULL);
    if (ret != RCL_RET_OK) {
        Serial.print("error: pub odom msg failed:");
        Serial.println(ret);
    }

    ret = rcl_publish(&imu_publisher_, &imu_msg, NULL);
    if (ret != RCL_RET_OK) {
        Serial.print("error: pub imu msg failed:");
        Serial.println(ret);
    }

    if (enable_pub_motion_status_) {
        ret = rcl_publish(&motion_status_publisher_, &motionControl_->get_motion_status_msg(), NULL);
        if (ret != RCL_RET_OK) {
            Serial.print("error: pub motion status msg failed:");
            Serial.println(ret);
        }
    }
}

void AMRNode::_serial_print(const std::string &msg) {
    Serial.println(msg.c_str());

    if (AMRNode::instance().connected()) {
        std_msgs__msg__String ros_msg;
        rosidl_runtime_c__String__init(&ros_msg.data);
        rosidl_runtime_c__String__assign(&ros_msg.data, msg.c_str());

        rcl_ret_t ret;
        ret = rcl_publish(AMRNode::instance().serial_msg_publisher_, &ros_msg, NULL);
        if (ret != RCL_RET_OK) {
            Serial.print("error: pub serial msg failed:");
            Serial.println(ret);
        }
    }
}