#include "motionNodeTask.h"

MotionNodeTask::MotionNodeTask() {
    task_name_ = "motion_node_task";
    core_id_ = 0;
    priority_ = 9;
    stack_size_ = 16384;
    num_handles_ = 6;

    node_name_ = esp32_motion_node_name;
    node_namespace_ = esp32_motion_node_namespace;
    serial_msg_topic_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_serial_msg_topic_name);
    heartbeat_topic_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_heartbeat_topic_name);

    motion_services_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_settings_service_name);

    motion_status_topic_name_ = constructNodeName(esp32_motion_node_namespace, esp32_motion_status_topic_name);
    motion_cmd_vel_topic_name_ = constructNodeName(pc_motion_node_namespace, pc_cmd_vel_topic_name);
}

bool MotionNodeTask::init_micro_ros() {
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

void MotionNodeTask::clean_micro_ros() {
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

void MotionNodeTask::motion_settings_service_callback(const void *req, void *res) {
    const motion_settings_service__srv__MotionSettingsService_Request *request = (const motion_settings_service__srv__MotionSettingsService_Request *)req;
    motion_settings_service__srv__MotionSettingsService_Response *response = (motion_settings_service__srv__MotionSettingsService_Response *)res;

    auto instance = &MotionNodeTask::instance();
    auto motionControl = &MotionControlTask::instance();
    auto sensorsControl = &SensorsControlTask::instance();

    if (request->mode == MotionService::Type::HeartBeat) {
        ;
    } else if (request->mode == MotionService::Type::Restart) {
        restart_device();
    } else if (request->mode == MotionService::Type::Brake) {
        motionControl->brake();
    } else if (request->mode == MotionService::Type::StopMove) {
        motionControl->stop_move();
    } else if (request->mode == MotionService::Type::MoveFront) {
        motionControl->move_front();
    } else if (request->mode == MotionService::Type::MoveBack) {
        motionControl->move_back();
    } else if (request->mode == MotionService::Type::TurnLeft) {
        motionControl->turn_left();
    } else if (request->mode == MotionService::Type::TurnRight) {
        motionControl->turn_right();
    }

    else if (request->mode == MotionService::Type::CalibrateMPU6050) {
        sensorsControl->get_mpu6050_control()->start_calibration();
    }

    else if (request->mode == MotionService::Type::SetSpeedPercent) {
        motionControl->set_speed_percent(request->linear_speed_percent, request->angular_speed_percent);
        response->spd_plan_settings.max_v = motionControl->get_speed_plan_parms().max_v;
        response->spd_plan_settings.max_w = motionControl->get_speed_plan_parms().max_w;
        motionControl->get_speed_percent(response->linear_speed_percent, response->angular_speed_percent);
    } else if (request->mode == MotionService::Type::SetSpeedPlanState) {
        auto spd_params = motionControl->get_speed_plan_parms();
        spd_params.enable = request->spd_plan_settings.enable;
        motionControl->set_speed_plan_parms(spd_params);
        response->spd_plan_settings.enable = spd_params.enable;
    }

    else if (request->mode == MotionService::Type::ReadParams) {
        motionControl->read_params(response);
        sensorsControl->read_params(response);
    } else if (request->mode == MotionService::Type::WriteParams) {
        if (motionControl->get_speed_plan_parms().milliseconds != request->spd_plan_settings.milliseconds) {
            instance->_create_publish_motion_status_timer();
        }

        motionControl->write_params(request);
        sensorsControl->write_params(request);

        motionControl->get_speed_percent(response->linear_speed_percent, response->angular_speed_percent);
    } else if (request->mode == MotionService::Type::SaveParams) {
        motionControl->save_params();
        sensorsControl->save_params();
    }

    else if (request->mode == MotionService::Type::ReadConfig) {
        motionControl->read_config(response);
        sensorsControl->read_config(response);
    } else if (request->mode == MotionService::Type::WriteConfig) {
        motionControl->write_config(request);
        sensorsControl->write_config(request);
    } else if (request->mode == MotionService::Type::SaveConfig) {
        motionControl->save_config();
        sensorsControl->save_config();
    }

    response->mode = request->mode;
    response->id = request->id;
}

void MotionNodeTask::msg_twist_callback(const void *msg) {
    const geometry_msgs__msg__Twist *twist_msg = static_cast<const geometry_msgs__msg__Twist *>(msg);
    MotionControlTask::instance().set_twist(*twist_msg);
}

void MotionNodeTask::publish_msgs() {
    if (!connected()) {
        return;
    }

    if (motion_status_publisher_initialized_) {
        motion_status_msg_.seq++;
        motion_status_msg_.stamp = get_now_ns();
        MotionControlTask::instance().get_data(motion_status_msg_);
        SensorsControlTask::instance().get_data(motion_status_msg_);
        rcl_ret_t ret = rcl_publish(&motion_status_publisher_, &motion_status_msg_, nullptr);
        if (ret != RCL_RET_OK) {
            Serial.printf("[micro_ros] motion status publish failed: %d\n", ret);
        }
    }
}

void MotionNodeTask::publish_motion_status_timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
    MotionNodeTask::instance().publish_msgs();
}

bool MotionNodeTask::_create_publish_motion_status_timer() {
    _destroy_publish_motion_status_timer();

    if (!publish_motion_status_timer_initialized_) {
        rcl_ret_t ret = rclc_timer_init_default(&publish_motion_status_timer_, &support_, RCL_MS_TO_NS(MotionControlTask::instance().get_speed_plan_parms().milliseconds), publish_motion_status_timer_callback);
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

void MotionNodeTask::_destroy_publish_motion_status_timer() {
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