#include "centerControl.h"

CenterControl::CenterControl() {
    speedPlan_ = std::make_shared<SpeedPlan>();
    left_front_motor_control_ = std::make_shared<MotorControl>("lfm");
    left_back_motor_control_ = std::make_shared<MotorControl>("lbm");
    right_front_motor_control_ = std::make_shared<MotorControl>("rfm");
    right_back_motor_control_ = std::make_shared<MotorControl>("rbm");

    line_speed_loop_ = std::make_shared<PIDControl>("lsl");
    angle_speed_loop_ = std::make_shared<PIDControl>("asl");
    position_loop_ = std::make_shared<PIDControl>("pl");

    mutex_ = xSemaphoreCreateMutex();

    // odom_msg_.header.frame_id = micro_ros_string_utilities_set(odom_msg_.header.frame_id, "odom");
    // odom_msg_.child_frame_id = micro_ros_string_utilities_set(odom_msg_.child_frame_id, "base_link");
    // odom_msg_.twist.twist.linear.y = 0;
    // odom_msg_.twist.twist.linear.z = 0;
    // odom_msg_.twist.twist.angular.x = 0;
    // odom_msg_.twist.twist.angular.y = 0;
    // odom_msg_.pose.pose.position.z = 0;
    // odom_msg_.pose.pose.orientation.x = 0;
    // odom_msg_.pose.pose.orientation.y = 0;
}

void CenterControl::init_and_start() {
    _load_settings();
    _load_params();

    set_milliseconds(milliseconds_);
    set_speed_plan_parms(max_v_, max_acc_, jerk_);
    start();
}

void CenterControl::restart() {
    stop();
    delay(100);
    start();
}

void CenterControl::start() {
    _start_control_timer();
}

void CenterControl::stop() {
    stop_move();
    _stop_control_timer();
}

void CenterControl::set_model_params(float track_width, float wheel_width) {
    track_width_ = track_width;
    wheel_width_ = wheel_width;
}

void CenterControl::set_left_front_motor_settings_params(int motor_pinA, int motor_pinB, int encoder_pinA, int encoder_pinB, int motor_pinPWM, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    left_front_motor_control_->set_motor_params(motor_pinA, motor_pinB, encoder_pinA, encoder_pinB, motor_pinPWM, wheel_diameter, pluses_per_revolution, revolutions_per_minute);
}

void CenterControl::set_left_back_motor_settings_params(int motor_pinA, int motor_pinB, int encoder_pinA, int encoder_pinB, int motor_pinPWM, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    left_back_motor_control_->set_motor_params(motor_pinA, motor_pinB, encoder_pinA, encoder_pinB, motor_pinPWM, wheel_diameter, pluses_per_revolution, revolutions_per_minute);
}

void CenterControl::set_right_front_motor_settings_params(int motor_pinA, int motor_pinB, int encoder_pinA, int encoder_pinB, int motor_pinPWM, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    right_front_motor_control_->set_motor_params(motor_pinA, motor_pinB, encoder_pinA, encoder_pinB, motor_pinPWM, wheel_diameter, pluses_per_revolution, revolutions_per_minute);
}

void CenterControl::set_right_back_motor_settings_params(int motor_pinA, int motor_pinB, int encoder_pinA, int encoder_pinB, int motor_pinPWM, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    right_back_motor_control_->set_motor_params(motor_pinA, motor_pinB, encoder_pinA, encoder_pinB, motor_pinPWM, wheel_diameter, pluses_per_revolution, revolutions_per_minute);
}

void CenterControl::set_left_front_motor_pid_params(float p, float i, float d, float max_total_integral) {
    left_front_motor_control_->set_pid_params(p, i, d, max_total_integral);
}

void CenterControl::set_left_back_motor_pid_params(float p, float i, float d, float max_total_integral) {
    left_back_motor_control_->set_pid_params(p, i, d, max_total_integral);
}

void CenterControl::set_right_front_motor_pid_params(float p, float i, float d, float max_total_integral) {
    right_front_motor_control_->set_pid_params(p, i, d, max_total_integral);
}

void CenterControl::set_right_back_motor_pid_params(float p, float i, float d, float max_total_integral) {
    right_back_motor_control_->set_pid_params(p, i, d, max_total_integral);
}

void CenterControl::set_position_pid_params(float p, float i, float d, float max_total_integral) {
    position_loop_->set_pid_params(p, i, d, max_total_integral);
}

void CenterControl::set_line_speed_pid_params(float p, float i, float d, float max_total_integral) {
    line_speed_loop_->set_pid_params(p, i, d, max_total_integral);
}

void CenterControl::set_angle_speed_pid_params(float p, float i, float d, float max_total_integral) {
    angle_speed_loop_->set_pid_params(p, i, d, max_total_integral);
}

void CenterControl::set_speed_plan_parms(float max_v, float max_acc, float jerk) {
    if (max_v > target_max_v_)
        max_v = target_max_v_;

    max_v_ = max_v;
    max_acc_ = max_acc;
    jerk_ = jerk;

    speed_percent_ = max_v_ / target_max_v_;
    // max_w_ = target_max_w_ * speed_percent_;

    speedPlan_->set_maxAcc_and_jerk(max_acc_, jerk_);
}

void CenterControl::set_wheel_type(bool is_mecanum_wheel) {
    is_mecanum_wheel_ = is_mecanum_wheel;
}

void CenterControl::set_milliseconds(int milliseconds) {
    int milliseconds_tmp = milliseconds_;
    milliseconds_ = milliseconds;

    if (esp_timer_is_active(control_timer_) && milliseconds_tmp != milliseconds_) {
        _stop_control_timer();
    }
    _start_control_timer();
}

int CenterControl::get_milliseconds() {
    return milliseconds_;
}

void CenterControl::set_loop_period_cnt(int position_loop_period_cnt, int speed_loop_period_cnt) {
    position_loop_period_cnt_ = position_loop_period_cnt;
    speed_loop_period_cnt_ = speed_loop_period_cnt;
}

float CenterControl::get_max_speed() {
    return max_v_;
}

void CenterControl::set_speed_percent(float percent) {
    percent = fabs(percent);
    if (percent >= 1)
        percent = 1;
    speed_percent_ = percent;
    max_v_ = target_max_v_ * speed_percent_;
    // max_w_ = target_max_w_ * speed_percent_;
}

float CenterControl::get_speed_percent() {
    return speed_percent_;
}

void CenterControl::set_speed_plan_state(bool enable) {
    enable_speed_plan_ = enable;
}

void CenterControl::_start_control_timer() {
    if (!control_timer_) {
        esp_timer_create_args_t timer_args = {
            .callback = &control_loop,
            .arg = this,
            .name = "control_timer"};
        auto ret = esp_timer_create(&timer_args, &control_timer_);
        if (ret != ESP_OK) {
            serial_print("control timer created failed.");
            Serial.print("Timer creation failed:");
            Serial.println(ret);
            control_timer_ = nullptr;
            return;
        } else {
            serial_print("control timer created success!");
        }
    }
    if (!esp_timer_is_active(control_timer_)) {
        uint64_t period = milliseconds_ * 1000;
        auto ret = esp_timer_start_periodic(control_timer_, period);
        if (ret != ESP_OK) {
            serial_print("control timer start failed: " + ret);
        } else {
            serial_print("control timer start success!");
        }
    }
}

void CenterControl::_stop_control_timer() {
    stop_move();
    if (control_timer_ && esp_timer_is_active(control_timer_)) {
        esp_timer_stop(control_timer_);
    }
}

void CenterControl::move_relative_euler_pose(float euler_pose_x, float euler_pose_y, float euler_pose_yaw) {
    target_euler_pose_.x = current_euler_pose_.x + euler_pose_x;
    target_euler_pose_.y = current_euler_pose_.y + euler_pose_y;
    target_euler_pose_.yaw = current_euler_pose_.yaw + euler_pose_yaw;
}

void CenterControl::move_absolute_euler_pose(float euler_pose_x, float euler_pose_y, float euler_pose_yaw) {
    target_euler_pose_.x = euler_pose_x;
    target_euler_pose_.y = euler_pose_y;
    target_euler_pose_.yaw = euler_pose_yaw;
}

void CenterControl::brake() {
    running_ = false;
    left_front_motor_control_->brake();
    left_back_motor_control_->brake();
    right_front_motor_control_->brake();
    right_back_motor_control_->brake();
}

void CenterControl::stop_move() {
    auto wheel_speed = WheelSpeed();
    wheel_speed.left_front_v = 0;
    wheel_speed.left_back_v = 0;
    wheel_speed.right_front_v = 0;
    wheel_speed.right_back_v = 0;
    start_move(wheel_speed);
}

void CenterControl::move_front() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = max_v;
    wheel_speed.left_back_v = max_v;
    wheel_speed.right_front_v = max_v;
    wheel_speed.right_back_v = max_v;
    start_move(wheel_speed);
}

void CenterControl::move_back() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = -max_v;
    wheel_speed.left_back_v = -max_v;
    wheel_speed.right_front_v = -max_v;
    wheel_speed.right_back_v = -max_v;
    start_move(wheel_speed);
}

void CenterControl::move_left() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = -max_v;
    wheel_speed.left_back_v = -max_v;
    wheel_speed.right_front_v = max_v;
    wheel_speed.right_back_v = max_v;
    start_move(wheel_speed);
}

void CenterControl::move_right() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = max_v;
    wheel_speed.left_back_v = max_v;
    wheel_speed.right_front_v = -max_v;
    wheel_speed.right_back_v = -max_v;
    start_move(wheel_speed);
}

void CenterControl::move_left_front() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = max_v;
    wheel_speed.left_back_v = 0;
    wheel_speed.right_front_v = 0;
    wheel_speed.right_back_v = -max_v;
    start_move(wheel_speed);
}

void CenterControl::move_left_back() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = 0;
    wheel_speed.left_back_v = max_v;
    wheel_speed.right_front_v = -max_v;
    wheel_speed.right_back_v = 0;
    start_move(wheel_speed);
}

void CenterControl::move_right_front() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = 0;
    wheel_speed.left_back_v = -max_v;
    wheel_speed.right_front_v = max_v;
    wheel_speed.right_back_v = 0;
    start_move(wheel_speed);
}

void CenterControl::move_right_back() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = -max_v;
    wheel_speed.left_back_v = 0;
    wheel_speed.right_front_v = 0;
    wheel_speed.right_back_v = max_v;
    start_move(wheel_speed);
}

void CenterControl::turn_left() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = max_v;
    wheel_speed.left_back_v = -max_v;
    wheel_speed.right_front_v = -max_v;
    wheel_speed.right_back_v = max_v;
    start_move(wheel_speed);
}

void CenterControl::turn_right() {
    auto wheel_speed = WheelSpeed();
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }
    wheel_speed.left_front_v = -max_v;
    wheel_speed.left_back_v = max_v;
    wheel_speed.right_front_v = max_v;
    wheel_speed.right_back_v = -max_v;
    start_move(wheel_speed);
}

void CenterControl::start_move(WheelSpeed &target_wheel_speed) {
    running_ = true;
    std::deque<WheelSpeed> speed_deque;

    _fix_speed(target_wheel_speed.left_front_v);
    _fix_speed(target_wheel_speed.left_back_v);
    _fix_speed(target_wheel_speed.right_front_v);
    _fix_speed(target_wheel_speed.right_back_v);

    if (enable_speed_plan_) {
        float MIN_V_CHANGE = 0.001;
        auto changed_left_front_v = target_wheel_speed.left_front_v - current_wheel_v_.left_front_v;
        auto changed_left_back_v = target_wheel_speed.right_front_v - current_wheel_v_.left_back_v;
        auto changed_right_front_v = target_wheel_speed.left_back_v - current_wheel_v_.right_front_v;
        auto changed_right_back_v = target_wheel_speed.right_back_v - current_wheel_v_.right_back_v;

        if (fabs(changed_left_front_v) > MIN_V_CHANGE || fabs(changed_left_back_v) > MIN_V_CHANGE || fabs(changed_right_front_v) > MIN_V_CHANGE || fabs(changed_right_back_v) > MIN_V_CHANGE) {
            std::map<float, int> wheel_change_map;
            wheel_change_map[std::fabs(changed_left_front_v)] = 0;
            wheel_change_map[std::fabs(changed_left_back_v)] = 1;
            wheel_change_map[std::fabs(changed_right_front_v)] = 2;
            wheel_change_map[std::fabs(changed_right_back_v)] = 3;

            auto planned_current_v = 0, planned_target_v = 0, changed_v = 0;
            WheelSpeed wheel_speed;

            if (wheel_change_map.cbegin()->second == 0) {
                planned_current_v = current_wheel_v_.left_front_v;
                planned_target_v = target_wheel_speed.left_front_v;
                changed_v = changed_left_front_v;
            } else if (wheel_change_map.cbegin()->second == 1) {
                planned_current_v = current_wheel_v_.left_back_v;
                planned_target_v = target_wheel_speed.left_back_v;
                changed_v = changed_left_back_v;
            } else if (wheel_change_map.cbegin()->second == 2) {
                planned_current_v = current_wheel_v_.right_front_v;
                planned_target_v = target_wheel_speed.right_front_v;
                changed_v = changed_right_front_v;
            } else if (wheel_change_map.cbegin()->second == 3) {
                planned_current_v = current_wheel_v_.right_back_v;
                planned_target_v = target_wheel_speed.right_back_v;
                changed_v = changed_right_back_v;
            }

            std::deque<float> single_wheel_speed_deque = speedPlan_->plan(planned_current_v, planned_target_v, dt_);
            for (auto value : single_wheel_speed_deque) {
                auto speed_bi = (value - planned_current_v) / changed_v;
                if (fabs(changed_left_front_v) < MIN_V_CHANGE) {
                    wheel_speed.left_front_v = target_wheel_speed.left_front_v;
                } else {
                    wheel_speed.left_front_v = speed_bi * changed_left_front_v + current_wheel_v_.left_front_v;
                }
                if (fabs(changed_left_back_v) < MIN_V_CHANGE) {
                    wheel_speed.left_back_v = target_wheel_speed.left_back_v;
                } else {
                    wheel_speed.left_back_v = speed_bi * changed_left_back_v + current_wheel_v_.left_back_v;
                }
                if (fabs(changed_right_front_v) < MIN_V_CHANGE) {
                    wheel_speed.right_front_v = target_wheel_speed.right_front_v;
                } else {
                    wheel_speed.right_front_v = speed_bi * changed_right_front_v + current_wheel_v_.right_front_v;
                }
                if (fabs(changed_right_back_v) < MIN_V_CHANGE) {
                    wheel_speed.right_back_v = target_wheel_speed.right_back_v;
                } else {
                    wheel_speed.right_back_v = speed_bi * changed_right_back_v + current_wheel_v_.right_back_v;
                }
                speed_deque.push_back(wheel_speed);
            }
        }
    }
    speed_deque.push_back(target_wheel_speed);

    if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
        wheel_speed_deque_ = std::move(speed_deque);
        xSemaphoreGive(mutex_);
    }
}

void CenterControl::start_move(float twist_linear_x, float twist_linear_y, float twist_angular_z) {
    // running_ = true;
    // std::deque<std::pair<float, float>> speed_deque;
    // if (enable_speed_plan_) {
    //     float MIN_V_CHANGE = 0.001;
    //     std::deque<float> single_wheel_speed_deque;
    //     float left_target_v = 0, right_target_v = 0;

    //     auto target_wheels_v = _inverseKinematics(v, w);
    //     auto current_wheels_v = _inverseKinematics(target_v_, target_w_);

    //     _fix_speed(target_wheels_v.first);
    //     _fix_speed(target_wheels_v.second);

    //     float changed_left_v = target_wheels_v.first - current_wheels_v.first;
    //     float changed_right_v = target_wheels_v.second - current_wheels_v.second;

    //     if (fabs(changed_left_v) < MIN_V_CHANGE && fabs(changed_right_v) < MIN_V_CHANGE) {
    //         speed_deque.push_back(std::pair<float, float>(v, w));
    //     } else {
    //         if (fabs(changed_left_v) > fabs(changed_right_v)) {
    //             single_wheel_speed_deque = speedPlan_->plan(current_wheels_v.first, target_wheels_v.first, milliseconds_ / 1000.0);
    //             for (auto value : single_wheel_speed_deque) {
    //                 if (fabs(changed_right_v) < MIN_V_CHANGE) {
    //                     right_target_v = target_wheels_v.second;
    //                 } else {
    //                     right_target_v = (value - current_wheels_v.first) / changed_left_v * changed_right_v + current_wheels_v.second;
    //                 }
    //                 speed_deque.push_back(_forwardKinematics(value, right_target_v));
    //             }
    //         } else {
    //             single_wheel_speed_deque = speedPlan_->plan(current_wheels_v.second, target_wheels_v.second, milliseconds_ / 1000.0);
    //             for (auto value : single_wheel_speed_deque) {
    //                 if (fabs(changed_left_v) < MIN_V_CHANGE) {
    //                     left_target_v = target_wheels_v.first;
    //                 } else {
    //                     left_target_v = (value - current_wheels_v.second) / changed_right_v * changed_left_v + current_wheels_v.first;
    //                 }
    //                 speed_deque.push_back(_forwardKinematics(left_target_v, value));
    //             }
    //         }
    //     }
    // } else {
    //     auto target_wheels_v = _inverseKinematics(v, w);

    //     _fix_speed(target_wheels_v.first);
    //     _fix_speed(target_wheels_v.second);

    //     speed_deque.push_back(_forwardKinematics(target_wheels_v.first, target_wheels_v.second));
    // }

    // if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
    //     target_speed_deque_ = std::move(speed_deque);
    //     xSemaphoreGive(mutex_);
    // }
}

void CenterControl::reset() {
    target_twist_.linear.x = 0;
    target_twist_.linear.y = 0;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;

    period_cnt_ = 0;
    speed_loop_dt_ = 0;

    if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
        wheel_speed_deque_.clear();
        wheel_speed_deque_.push_back(WheelSpeed());
        xSemaphoreGive(mutex_);
    }

    position_loop_->reset();
    line_speed_loop_->reset();
    angle_speed_loop_->reset();
}

void CenterControl::update() {
    if (milliseconds_ <= 0) {
        return;
    }

    time_record_ = esp_timer_get_time();
    dt_ = (time_record_ - last_time_record_) / 1e6;

    // TODO:位置环

    left_front_motor_control_->update(dt_);
    left_back_motor_control_->update(dt_);
    right_front_motor_control_->update(dt_);
    right_back_motor_control_->update(dt_);

    _calculateOdomMsg();

    // if (running_) {
    //     period_cnt_ = (period_cnt_ + 1) % (position_loop_period_cnt_ * speed_loop_period_cnt_);
    //     speed_loop_dt_ += dt_;

    //     if (period_cnt_ % speed_loop_period_cnt_ == 0) {
    //         if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
    //             if (!target_speed_deque_.empty()) {
    //                 auto target_speed = target_speed_deque_.front();
    //                 target_v_ = target_speed.first;
    //                 target_w_ = target_speed.second;
    //                 target_speed_deque_.pop_front();
    //             }
    //             xSemaphoreGive(mutex_);
    //         }

    //         if (motion_mode_ == MotionMode::DynamicBalanceMode) {
    //             target_pitch_ = line_speed_loop_->calculate(current_v_, target_v_, speed_loop_dt_);
    //             adjust_target_w_ = angle_speed_loop_->calculate(current_w_, target_w_, speed_loop_dt_);
    //         } else {
    //             target_pitch_ = 0;
    //             adjust_target_w_ = target_w_;
    //         }
    //         speed_loop_dt_ = 0;
    //     }

    //     if (period_cnt_ % position_loop_period_cnt_ == 0) {
    //         if (motion_mode_ == MotionMode::NoBalanceMode) {
    //             adjust_target_v_ = target_v_;
    //         } else {
    //             if (fabs(mpu6050_control_->pitch_) >= 45) {
    //                 reset();
    //             } else {
    //                 adjust_target_v_ = attitude_p_ * (target_pitch_ - (mpu6050_control_->pitch_ - mpu6050_control_->pitch_offset_)) + attitude_d_ * mpu6050_control_->gyroY_;
    //             }
    //         }
    //     }
    // } else {
    //     reset();
    // }

    // target_wheel_v_ = _inverseKinematics(target_v_, target_w_);

    // left_motor_control_->set_speed(target_wheel_v_.first, dt_, running_);
    // right_motor_control_->set_speed(target_wheel_v_.second, dt_, running_);

    if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
        if (!wheel_speed_deque_.empty()) {
            target_wheel_v_ = wheel_speed_deque_.front();
            Serial.println("----------");
            Serial.println(target_wheel_v_.left_front_v);
            Serial.println(target_wheel_v_.left_back_v);
            Serial.println(target_wheel_v_.right_front_v);
            Serial.println(target_wheel_v_.right_back_v);
            Serial.println("----------");
            Serial.println("");
            wheel_speed_deque_.pop_front();
        }
        xSemaphoreGive(mutex_);
    }

    left_front_motor_control_->set_speed(target_wheel_v_.left_front_v, dt_, running_); // running_
    Serial.println("");
    left_back_motor_control_->set_speed(target_wheel_v_.left_back_v, dt_, running_);
    Serial.println("--------");
    // right_front_motor_control_->set_speed(target_wheel_v_.right_front_v, dt_, running_);
    // right_back_motor_control_->set_speed(target_wheel_v_.right_back_v, dt_, running_);

    left_front_motor_control_->move();
    left_back_motor_control_->move();
    right_front_motor_control_->move();
    right_back_motor_control_->move();

    last_time_record_ = time_record_;

    if (esp_timer_get_time() - time_record_ >= milliseconds_ * 1000) {
        serial_print("控制处理超时(ms): " + std::to_string((esp_timer_get_time() - time_record_) / 1000.0));
    }
}

void CenterControl::_calculateOdomMsg() {
    // auto right_distance = right_motor_control_->get_distance_change();
    // auto left_distance = left_motor_control_->get_distance_change();
    // auto distance = (right_distance + left_distance) / 2;
    // auto angle = (right_distance - left_distance) / track_width_;
    // current_x_ += distance * std::cos(current_angle_ + angle / 2.0);
    // current_y_ += distance * std::sin(current_angle_ + angle / 2.0);
    // current_angle_ += angle;
    // current_angle_ = std::atan2(std::sin(current_angle_), std::cos(current_angle_));

    // auto speed = _forwardKinematics(left_distance / dt_, right_distance / dt_);
    // current_v_ = speed.first;
    // current_w_ = speed.second;

    current_wheel_v_.left_back_v = left_front_motor_control_->get_current_speed();
    current_wheel_v_.left_front_v = left_back_motor_control_->get_current_speed();
    current_wheel_v_.right_back_v = right_front_motor_control_->get_current_speed();
    current_wheel_v_.right_front_v = right_back_motor_control_->get_current_speed();
}

void CenterControl::_fix_speed(float &v) {
    float max_v = 0;
    if (is_mecanum_wheel_) {
        max_v = max_v_ * 2 / sqrt(2);
    } else {
        max_v = max_v_;
    }

    if (v > max_v)
        v = max_v;
    else if (v < -1 * max_v)
        v = -1 * max_v;
}

std::pair<float, float> CenterControl::_forwardKinematics(float left_v, float right_v) {
    return std::pair<float, float>((left_v + right_v) / 2, (right_v - left_v) / track_width_);
}

std::pair<float, float> CenterControl::_inverseKinematics(float v, float w) {
    return std::pair<float, float>(v - w * track_width_ / 2, v + w * track_width_ / 2);
}

void CenterControl::read_params(motion_params_service__srv__MotionParamsService_Response *response) {
    response->milliseconds = milliseconds_;
    response->position_loop_milliseconds_cnt = position_loop_period_cnt_;
    response->speed_loop_milliseconds_cnt = speed_loop_period_cnt_;

    response->enable_speed_plan = enable_speed_plan_;

    response->speed_percent = speed_percent_;
    response->max_v = max_v_;
    response->max_acc = max_acc_;
    response->jerk = jerk_;

    response->position_p = position_loop_->get_pid_params().p;
    response->position_i = position_loop_->get_pid_params().i;
    response->position_d = position_loop_->get_pid_params().d;
    response->position_max_total_integral = position_loop_->get_pid_params().max_total_integral;

    response->line_speed_p = line_speed_loop_->get_pid_params().p;
    response->line_speed_i = line_speed_loop_->get_pid_params().i;
    response->line_speed_d = line_speed_loop_->get_pid_params().d;
    response->line_speed_max_total_integral = line_speed_loop_->get_pid_params().max_total_integral;

    response->angle_speed_p = angle_speed_loop_->get_pid_params().p;
    response->angle_speed_i = angle_speed_loop_->get_pid_params().i;
    response->angle_speed_d = angle_speed_loop_->get_pid_params().d;
    response->angle_speed_max_total_integral = angle_speed_loop_->get_pid_params().max_total_integral;

    response->left_front_motor_p = left_front_motor_control_->get_pid_params().p;
    response->left_front_motor_i = left_front_motor_control_->get_pid_params().i;
    response->left_front_motor_d = left_front_motor_control_->get_pid_params().d;
    response->left_front_motor_max_total_integral = left_front_motor_control_->get_pid_params().max_total_integral;

    response->left_back_motor_p = left_back_motor_control_->get_pid_params().p;
    response->left_back_motor_i = left_back_motor_control_->get_pid_params().i;
    response->left_back_motor_d = left_back_motor_control_->get_pid_params().d;
    response->left_back_motor_max_total_integral = left_back_motor_control_->get_pid_params().max_total_integral;

    response->right_front_motor_p = right_front_motor_control_->get_pid_params().p;
    response->right_front_motor_i = right_front_motor_control_->get_pid_params().i;
    response->right_front_motor_d = right_front_motor_control_->get_pid_params().d;
    response->right_front_motor_max_total_integral = right_front_motor_control_->get_pid_params().max_total_integral;

    response->right_back_motor_p = right_back_motor_control_->get_pid_params().p;
    response->right_back_motor_i = right_back_motor_control_->get_pid_params().i;
    response->right_back_motor_d = right_back_motor_control_->get_pid_params().d;
    response->right_back_motor_max_total_integral = right_back_motor_control_->get_pid_params().max_total_integral;
}

void CenterControl::save_params() {
    preferences_.begin("params", false);
    preferences_.clear();
    Serial.println(0);

    preferences_.putInt("millisec", milliseconds_);

    Serial.println(1);
    preferences_.putInt("posPeCnt", position_loop_period_cnt_);
    Serial.println(2);

    preferences_.putInt("spdPeCnt", speed_loop_period_cnt_);
    Serial.println(3);

    preferences_.putBool("spdPlan", enable_speed_plan_);
    Serial.println(4);

    preferences_.putFloat("maxV", max_v_);
    Serial.println(5);

    preferences_.putFloat("maxAcc", max_acc_);
    Serial.println(6);

    preferences_.putFloat("jerk", jerk_);

    left_front_motor_control_->save_pid_params();
    left_back_motor_control_->save_pid_params();
    right_front_motor_control_->save_pid_params();
    right_back_motor_control_->save_pid_params();

    preferences_.end();
    serial_print("保存 params 完成!");
}

void CenterControl::_load_params() {
    preferences_.begin("params", true); // 只读模式

    milliseconds_ = preferences_.getInt("millisec", milliseconds_);
    position_loop_period_cnt_ = preferences_.getInt("posPeCnt", position_loop_period_cnt_);
    speed_loop_period_cnt_ = preferences_.getInt("spdPeCnt", speed_loop_period_cnt_);
    enable_speed_plan_ = preferences_.getBool("spdPlan", enable_speed_plan_);

    max_v_ = preferences_.getFloat("maxV", max_v_);
    max_acc_ = preferences_.getFloat("maxAcc", max_acc_);
    jerk_ = preferences_.getFloat("jerk", jerk_);

    preferences_.end();

    left_front_motor_control_->load_pid_params();
    left_back_motor_control_->load_pid_params();
    right_front_motor_control_->load_pid_params();
    right_back_motor_control_->load_pid_params();
}

void CenterControl::read_settings(motion_params_service__srv__MotionParamsService_Response *response) {
    response->is_mecanum_wheel = is_mecanum_wheel_;

    response->wheel_width = wheel_width_;
    response->track_width = track_width_;

    response->left_front_motor_pina = left_front_motor_control_->get_motor_params().motor_AIN1;
    response->left_front_motor_pinb = left_front_motor_control_->get_motor_params().motor_AIN2;
    response->left_front_motor_pinpwm = left_front_motor_control_->get_motor_params().motor_pwmPin;
    response->left_front_motor_wheel_diameter = left_front_motor_control_->get_motor_params().wheel_diameter;
    response->left_front_motor_pluses_per_revolution = left_front_motor_control_->get_motor_params().pluses_per_revolution;
    response->left_front_motor_revolutions_per_minute = left_front_motor_control_->get_motor_params().revolutions_per_minute;
    response->left_front_encoder_pina = left_front_motor_control_->get_motor_params().encoder_pinA;
    response->left_front_encoder_pinb = left_front_motor_control_->get_motor_params().encoder_pinB;

    response->left_back_motor_pina = left_back_motor_control_->get_motor_params().motor_AIN1;
    response->left_back_motor_pinb = left_back_motor_control_->get_motor_params().motor_AIN2;
    response->left_back_motor_pinpwm = left_back_motor_control_->get_motor_params().motor_pwmPin;
    response->left_back_motor_wheel_diameter = left_back_motor_control_->get_motor_params().wheel_diameter;
    response->left_back_motor_pluses_per_revolution = left_back_motor_control_->get_motor_params().pluses_per_revolution;
    response->left_back_motor_revolutions_per_minute = left_back_motor_control_->get_motor_params().revolutions_per_minute;
    response->left_back_encoder_pina = left_back_motor_control_->get_motor_params().encoder_pinA;
    response->left_back_encoder_pinb = left_back_motor_control_->get_motor_params().encoder_pinB;

    response->right_front_motor_pina = right_front_motor_control_->get_motor_params().motor_AIN1;
    response->right_front_motor_pinb = right_front_motor_control_->get_motor_params().motor_AIN2;
    response->right_front_motor_pinpwm = right_front_motor_control_->get_motor_params().motor_pwmPin;
    response->right_front_motor_wheel_diameter = right_front_motor_control_->get_motor_params().wheel_diameter;
    response->right_front_motor_pluses_per_revolution = right_front_motor_control_->get_motor_params().pluses_per_revolution;
    response->right_front_motor_revolutions_per_minute = right_front_motor_control_->get_motor_params().revolutions_per_minute;
    response->right_front_encoder_pina = right_front_motor_control_->get_motor_params().encoder_pinA;
    response->right_front_encoder_pinb = right_front_motor_control_->get_motor_params().encoder_pinB;

    response->right_back_motor_pina = right_back_motor_control_->get_motor_params().motor_AIN1;
    response->right_back_motor_pinb = right_back_motor_control_->get_motor_params().motor_AIN2;
    response->right_back_motor_pinpwm = right_back_motor_control_->get_motor_params().motor_pwmPin;
    response->right_back_motor_wheel_diameter = right_back_motor_control_->get_motor_params().wheel_diameter;
    response->right_back_motor_pluses_per_revolution = right_back_motor_control_->get_motor_params().pluses_per_revolution;
    response->right_back_motor_revolutions_per_minute = right_back_motor_control_->get_motor_params().revolutions_per_minute;
    response->right_back_encoder_pina = right_back_motor_control_->get_motor_params().encoder_pinA;
    response->right_back_encoder_pinb = right_back_motor_control_->get_motor_params().encoder_pinB;
}

void CenterControl::save_settings() {
    preferences_.begin("settings", false);
    preferences_.clear();

    preferences_.putBool("isMeWhe", is_mecanum_wheel_);
    preferences_.putFloat("wheWid", wheel_width_);
    preferences_.putFloat("traWid", track_width_);

    preferences_.end();

    left_front_motor_control_->save_motor_params();
    left_back_motor_control_->save_motor_params();
    right_front_motor_control_->save_motor_params();
    right_back_motor_control_->save_motor_params();

    serial_print("保存 settings 完成!");
}

void CenterControl::_load_settings() {
    preferences_.begin("settings", true); // 只读模式

    is_mecanum_wheel_ = preferences_.getBool("isMeWhe", is_mecanum_wheel_);
    wheel_width_ = preferences_.getFloat("wheWid", wheel_width_);
    track_width_ = preferences_.getFloat("traWid", track_width_);

    preferences_.end();

    left_front_motor_control_->load_motor_params();
    left_back_motor_control_->load_motor_params();
    right_front_motor_control_->load_motor_params();
    right_back_motor_control_->load_motor_params();

    update_target_max_speed();
}

void CenterControl::update_target_max_speed() {
    auto left_front_max_wheel_speed = left_front_motor_control_->get_max_speed();
    auto left_back_max_wheel_speed = left_back_motor_control_->get_max_speed();
    auto right_front_max_wheel_speed = right_front_motor_control_->get_max_speed();
    auto right_back_max_wheel_speed = right_back_motor_control_->get_max_speed();

    auto max_v = std::min({left_front_max_wheel_speed, right_front_max_wheel_speed, left_back_max_wheel_speed, right_back_max_wheel_speed});

    if (is_mecanum_wheel_) {
        target_max_v_ = max_v * sqrt(2) / 2.0;

        // target_max_v_ = (left_front_max_wheel_speed + right_front_max_wheel_speed + left_back_max_wheel_speed + right_back_max_wheel_speed) / 4.0;
        // target_max_w_ = (left_front_max_wheel_speed - right_front_max_wheel_speed + left_back_max_wheel_speed - right_back_max_wheel_speed) / (4.0 * (track_width_ + wheel_width_));
    } else {
        target_max_v_ = max_v;
        // target_max_v_ = (left_front_max_wheel_speed + right_front_max_wheel_speed) / 2.0;
        // target_max_w_ = (left_front_max_wheel_speed - right_front_max_wheel_speed) / (2.0 * track_width_);
    }
    speed_percent_ = max_v_ / target_max_v_;
}

// nav_msgs__msg__Odometry &CenterControl::get_odom_msg() {
//     auto stamp = rmw_uros_epoch_millis();
//     odom_msg_.header.stamp.sec = stamp / 1000;
//     odom_msg_.header.stamp.nanosec = (stamp % 1000 * 1e6);

//     odom_msg_.twist.twist = current_twist_;

//     odom_msg_.pose.pose.position.x = current_euler_pose_.x;
//     odom_msg_.pose.pose.position.y = current_euler_pose_.y;
//     odom_msg_.pose.pose.position.z = current_euler_pose_.z;

//     odom_msg_.pose.pose.orientation.x = 0; // 显式设为0
//     odom_msg_.pose.pose.orientation.y = 0;
//     odom_msg_.pose.pose.orientation.w = std::cos(current_euler_pose_.yaw / 2.0);
//     odom_msg_.pose.pose.orientation.z = std::sin(current_euler_pose_.yaw / 2.0);

//     return odom_msg_;
// }

motion_status_msgs__msg__MotionStatus &CenterControl::get_motion_status_msg() {
    motion_status_msg_.left_front_current_v = left_front_motor_control_->get_current_speed();
    motion_status_msg_.left_front_target_v = left_front_motor_control_->get_target_speed();
    motion_status_msg_.left_back_current_v = left_back_motor_control_->get_current_speed();
    motion_status_msg_.left_back_target_v = left_back_motor_control_->get_target_speed();

    motion_status_msg_.right_front_current_v = right_front_motor_control_->get_current_speed();
    motion_status_msg_.right_front_target_v = right_front_motor_control_->get_target_speed();
    motion_status_msg_.right_back_current_v = right_back_motor_control_->get_current_speed();
    motion_status_msg_.right_back_target_v = right_back_motor_control_->get_target_speed();

    motion_status_msg_.twist_current_linear_x = current_twist_.linear.x;
    motion_status_msg_.twist_target_linear_x = target_twist_.linear.x;

    motion_status_msg_.twist_current_linear_y = current_twist_.linear.y;
    motion_status_msg_.twist_target_linear_y = target_twist_.linear.y;

    motion_status_msg_.twist_current_angular_z = current_twist_.angular.z;
    motion_status_msg_.twist_target_angular_z = target_twist_.angular.z;

    motion_status_msg_.twist_current_euler_pose_x = current_euler_pose_.x;
    motion_status_msg_.twist_target_euler_pose_x = target_euler_pose_.x;

    motion_status_msg_.twist_current_euler_pose_y = current_euler_pose_.y;
    motion_status_msg_.twist_target_euler_pose_y = target_euler_pose_.y;

    motion_status_msg_.twist_current_euler_pose_yaw = current_euler_pose_.yaw;
    motion_status_msg_.twist_target_euler_pose_yaw = target_euler_pose_.yaw;

    return motion_status_msg_;
}

String CenterControl::get_http_data() {
    float yaw = 0, pitch = 0, roll = 0, gyro_x = 0, gyro_y = 0, gyro_z = 0;
    String json = "{";
    json += "\"speed_percent\":" + String(speed_percent_, 3) + ",";
    json += "\"twist_linear_x\":" + String(current_twist_.linear.x, 3) + ",";
    json += "\"twist_linear_y\":" + String(current_twist_.linear.y, 3) + ",";
    json += "\"twist_angular_z\":" + String(current_twist_.angular.z, 3) + ",";
    json += "\"euler_pose_x\":" + String(current_euler_pose_.x, 3) + ",";
    json += "\"euler_pose_y\":" + String(current_euler_pose_.y, 3) + ",";
    json += "\"euler_pose_yaw\":" + String(current_euler_pose_.yaw, 3);
    json += "}";

    return json;
}

void control_loop(void *args) {
    auto centerControl = static_cast<CenterControl *>(args);
    centerControl->update();
}