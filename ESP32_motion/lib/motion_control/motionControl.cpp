#include "motionControl.h"

MotionControl::MotionControl() {
    speedPlan_ = std::make_shared<SpeedPlan>();
    left_front_motor_control_ = std::make_shared<MotorControl>("lfm");
    left_back_motor_control_ = std::make_shared<MotorControl>("lbm");
    right_front_motor_control_ = std::make_shared<MotorControl>("rfm");
    right_back_motor_control_ = std::make_shared<MotorControl>("rbm");

    mutex_ = xSemaphoreCreateMutex();

    _load_config();
    _load_params();

    update_target_max_speed();

    set_milliseconds(milliseconds_);
    set_speed_plan_parms(max_v_, max_acc_, jerk_);
}

void MotionControl::set_model_params(float track_width, float wheel_width) {
    track_width_ = track_width;
    wheel_width_ = wheel_width;
}

void MotionControl::set_left_front_motor_config_params(int motor_pinA, int motor_pinB, int encoder_pinA, int encoder_pinB, int motor_pinPWM, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    left_front_motor_control_->set_motor_params(motor_pinA, motor_pinB, encoder_pinA, encoder_pinB, motor_pinPWM, wheel_diameter, pluses_per_revolution, revolutions_per_minute);
}

void MotionControl::set_left_back_motor_config_params(int motor_pinA, int motor_pinB, int encoder_pinA, int encoder_pinB, int motor_pinPWM, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    left_back_motor_control_->set_motor_params(motor_pinA, motor_pinB, encoder_pinA, encoder_pinB, motor_pinPWM, wheel_diameter, pluses_per_revolution, revolutions_per_minute);
}

void MotionControl::set_right_front_motor_config_params(int motor_pinA, int motor_pinB, int encoder_pinA, int encoder_pinB, int motor_pinPWM, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    right_front_motor_control_->set_motor_params(motor_pinA, motor_pinB, encoder_pinA, encoder_pinB, motor_pinPWM, wheel_diameter, pluses_per_revolution, revolutions_per_minute);
}

void MotionControl::set_right_back_motor_config_params(int motor_pinA, int motor_pinB, int encoder_pinA, int encoder_pinB, int motor_pinPWM, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    right_back_motor_control_->set_motor_params(motor_pinA, motor_pinB, encoder_pinA, encoder_pinB, motor_pinPWM, wheel_diameter, pluses_per_revolution, revolutions_per_minute);
}

void MotionControl::set_left_front_motor_pid_params(float p, float i, float d, float max_total_integral) {
    left_front_motor_control_->set_pid_params(p, i, d, max_total_integral);
}

void MotionControl::set_left_back_motor_pid_params(float p, float i, float d, float max_total_integral) {
    left_back_motor_control_->set_pid_params(p, i, d, max_total_integral);
}

void MotionControl::set_right_front_motor_pid_params(float p, float i, float d, float max_total_integral) {
    right_front_motor_control_->set_pid_params(p, i, d, max_total_integral);
}

void MotionControl::set_right_back_motor_pid_params(float p, float i, float d, float max_total_integral) {
    right_back_motor_control_->set_pid_params(p, i, d, max_total_integral);
}

void MotionControl::set_speed_plan_parms(float max_v, float max_acc, float jerk) {
    if (max_v > target_max_v_)
        max_v = target_max_v_;

    max_v_ = max_v;
    max_acc_ = max_acc;
    jerk_ = jerk;

    speed_percent_ = max_v_ / target_max_v_;

    if (is_mecanum_wheel_) {
        max_w_ = 2.0 * max_v_ / (track_width_ + wheel_width_);
    } else {
        max_w_ = 2.0 * max_v_ / wheel_width_;
    }

    speedPlan_->set_maxAcc_and_jerk(max_acc_, jerk_);
}

void MotionControl::set_wheel_type(bool is_mecanum_wheel) {
    is_mecanum_wheel_ = is_mecanum_wheel;
}

void MotionControl::set_milliseconds(int milliseconds) {
    milliseconds_ = milliseconds;
}

int MotionControl::get_milliseconds() {
    return milliseconds_;
}

float MotionControl::get_max_speed() {
    return max_v_;
}

void MotionControl::set_speed_percent(float percent) {
    percent = fabs(percent);
    if (percent >= 1)
        percent = 1;
    speed_percent_ = percent;
    max_v_ = target_max_v_ * speed_percent_;
    if (is_mecanum_wheel_) {
        max_w_ = 2.0 * max_v_ / (track_width_ + wheel_width_);
    } else {
        max_w_ = 2.0 * max_v_ / wheel_width_;
    }
}

float MotionControl::get_speed_percent() {
    return speed_percent_;
}

void MotionControl::set_speed_plan_state(bool enable) {
    enable_speed_plan_ = enable;
}

void MotionControl::set_motor_enable_flags(uint8_t flags) {
    motor_enable_flags_ = flags;
}
uint8_t MotionControl::get_motor_enable_flags() {
    return motor_enable_flags_;
}

void MotionControl::brake() {
    running_ = false;
    if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
        if (!wheel_speed_deque_.empty()) {
            wheel_speed_deque_.clear();
        }
        xSemaphoreGive(mutex_);
    }
    left_front_motor_control_->brake();
    left_back_motor_control_->brake();
    right_front_motor_control_->brake();
    right_back_motor_control_->brake();
}

void MotionControl::stop_move() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::move_front() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = max_v_;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::move_back() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = -max_v_;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::move_left() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = -max_v_;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::move_right() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = max_v_;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::move_left_front() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = -max_v_;
    target_twist.linear.y = max_v_;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::move_right_back() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = max_v_;
    target_twist.linear.y = -max_v_;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::move_right_front() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = max_v_;
    target_twist.linear.y = max_v_;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::move_left_back() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = -max_v_;
    target_twist.linear.y = -max_v_;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControl::turn_left() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = max_w_;
    set_twist(target_twist);
}

void MotionControl::turn_right() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = -max_w_;
    set_twist(target_twist);
}

void MotionControl::set_twist(const geometry_msgs__msg__Twist &twist) {
    _plan_wheel_speed(_inverseKinematics(twist));
}

void MotionControl::set_wheels_speed(const WheelSpeed &target_wheel_speed) {
    _plan_wheel_speed(target_wheel_speed);
}

void MotionControl::_plan_wheel_speed(const WheelSpeed &target_wheel_speed) { // WheelSpeed &target_wheel_speed
    running_ = true;
    std::deque<WheelSpeed> speed_deque;

    if (enable_speed_plan_) {
        float MIN_V_CHANGE = 0.001;
        auto changed_left_front_v = target_wheel_speed.left_front_v - target_wheel_v_.left_front_v;
        auto changed_left_back_v = target_wheel_speed.left_back_v - target_wheel_v_.left_back_v;
        auto changed_right_front_v = target_wheel_speed.right_front_v - target_wheel_v_.right_front_v;
        auto changed_right_back_v = target_wheel_speed.right_back_v - target_wheel_v_.right_back_v;

        if (fabs(changed_left_front_v) > MIN_V_CHANGE || fabs(changed_left_back_v) > MIN_V_CHANGE || fabs(changed_right_front_v) > MIN_V_CHANGE || fabs(changed_right_back_v) > MIN_V_CHANGE) {
            std::map<float, int> wheel_change_map;
            wheel_change_map[std::fabs(changed_left_front_v)] = 0;
            wheel_change_map[std::fabs(changed_left_back_v)] = 1;
            wheel_change_map[std::fabs(changed_right_front_v)] = 2;
            wheel_change_map[std::fabs(changed_right_back_v)] = 3;

            float planned_current_v = 0, planned_target_v = 0, changed_v = 0;
            WheelSpeed wheel_speed;

            if (wheel_change_map.rbegin()->second == 0) {
                planned_current_v = target_wheel_v_.left_front_v;
                planned_target_v = target_wheel_speed.left_front_v;
                changed_v = changed_left_front_v;
            } else if (wheel_change_map.rbegin()->second == 1) {
                planned_current_v = target_wheel_v_.left_back_v;
                planned_target_v = target_wheel_speed.left_back_v;
                changed_v = changed_left_back_v;
            } else if (wheel_change_map.rbegin()->second == 2) {
                planned_current_v = target_wheel_v_.right_front_v;
                planned_target_v = target_wheel_speed.right_front_v;
                changed_v = changed_right_front_v;
            } else if (wheel_change_map.rbegin()->second == 3) {
                planned_current_v = target_wheel_v_.right_back_v;
                planned_target_v = target_wheel_speed.right_back_v;
                changed_v = changed_right_back_v;
            }

            std::deque<float> single_wheel_speed_deque = speedPlan_->plan(planned_current_v, planned_target_v, milliseconds_ / 1000.0f);
            for (auto value : single_wheel_speed_deque) {
                auto speed_bi = (value - planned_current_v) / changed_v;
                if (fabs(changed_left_front_v) < MIN_V_CHANGE) {
                    wheel_speed.left_front_v = target_wheel_speed.left_front_v;
                } else {
                    wheel_speed.left_front_v = speed_bi * changed_left_front_v + target_wheel_v_.left_front_v;
                }
                if (fabs(changed_left_back_v) < MIN_V_CHANGE) {
                    wheel_speed.left_back_v = target_wheel_speed.left_back_v;
                } else {
                    wheel_speed.left_back_v = speed_bi * changed_left_back_v + target_wheel_v_.left_back_v;
                }
                if (fabs(changed_right_front_v) < MIN_V_CHANGE) {
                    wheel_speed.right_front_v = target_wheel_speed.right_front_v;
                } else {
                    wheel_speed.right_front_v = speed_bi * changed_right_front_v + target_wheel_v_.right_front_v;
                }
                if (fabs(changed_right_back_v) < MIN_V_CHANGE) {
                    wheel_speed.right_back_v = target_wheel_speed.right_back_v;
                } else {
                    wheel_speed.right_back_v = speed_bi * changed_right_back_v + target_wheel_v_.right_back_v;
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

void MotionControl::move(float dt) {
    if (running_) {
        if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
            if (!wheel_speed_deque_.empty()) {
                target_wheel_v_ = wheel_speed_deque_.front();
                wheel_speed_deque_.pop_front();
            }
            xSemaphoreGive(mutex_);

            if (!(motor_enable_flags_ & 0x01))
                target_wheel_v_.left_front_v = 0;
            if (!(motor_enable_flags_ & 0x02))
                target_wheel_v_.left_back_v = 0;
            if (!(motor_enable_flags_ & 0x04))
                target_wheel_v_.right_front_v = 0;
            if (!(motor_enable_flags_ & 0x08))
                target_wheel_v_.right_back_v = 0;
        }
    } else {
        target_wheel_v_.left_front_v = 0;
        target_wheel_v_.left_back_v = 0;
        target_wheel_v_.right_front_v = 0;
        target_wheel_v_.right_back_v = 0;
    }

    if (is_mecanum_wheel_) {
        left_pid_value_ = left_front_motor_control_->calculate(target_wheel_v_.left_front_v, dt, running_);
        right_pid_value_ = right_front_motor_control_->calculate(target_wheel_v_.right_front_v, dt, running_);

        left_front_motor_control_->set_speed(left_pid_value_);
        left_back_motor_control_->set_speed(left_pid_value_);
        right_front_motor_control_->set_speed(right_pid_value_);
        right_back_motor_control_->set_speed(right_pid_value_);
    } else {
        left_front_motor_control_->set_speed(target_wheel_v_.left_front_v, dt, running_);
        left_back_motor_control_->set_speed(target_wheel_v_.left_back_v, dt, running_);
        right_front_motor_control_->set_speed(target_wheel_v_.right_front_v, dt, running_);
        right_back_motor_control_->set_speed(target_wheel_v_.right_back_v, dt, running_);
    }

    left_front_motor_control_->move();
    left_back_motor_control_->move();
    right_front_motor_control_->move();
    right_back_motor_control_->move();
}

void MotionControl::update() {
    left_front_motor_control_->update();
    left_back_motor_control_->update();
    right_front_motor_control_->update();
    right_back_motor_control_->update();
}

void MotionControl::get_motion_status(motion_status_msgs__msg__MotionStatus &msg) {
    msg.left_front_current_v = left_front_motor_control_->get_current_speed();
    msg.left_front_target_v = left_front_motor_control_->get_target_speed();
    msg.left_back_current_v = left_back_motor_control_->get_current_speed();
    msg.left_back_target_v = left_back_motor_control_->get_target_speed();
    msg.right_front_current_v = right_front_motor_control_->get_current_speed();
    msg.right_front_target_v = right_front_motor_control_->get_target_speed();
    msg.right_back_current_v = right_back_motor_control_->get_current_speed();
    msg.right_back_target_v = right_back_motor_control_->get_target_speed();

    msg.left_front_total_distance = left_front_motor_control_->get_total_distance();
    msg.left_front_dt_distance = left_front_motor_control_->get_dt_distance();
    msg.left_back_total_distance = left_back_motor_control_->get_total_distance();
    msg.left_back_dt_distance = left_back_motor_control_->get_dt_distance();
    msg.right_front_total_distance = right_front_motor_control_->get_total_distance();
    msg.right_front_dt_distance = right_front_motor_control_->get_dt_distance();
    msg.right_back_total_distance = right_back_motor_control_->get_total_distance();
    msg.right_back_dt_distance = right_back_motor_control_->get_dt_distance();
}

geometry_msgs__msg__Twist MotionControl::_forwardKinematics(const WheelSpeed &wheelSpeed) {
    geometry_msgs__msg__Twist twist;
    if (is_mecanum_wheel_) {
        twist.linear.x = (wheelSpeed.left_front_v - wheelSpeed.left_back_v - wheelSpeed.right_front_v + wheelSpeed.right_back_v) / 4.0;
        twist.linear.y = (wheelSpeed.left_front_v + wheelSpeed.left_back_v + wheelSpeed.right_front_v + wheelSpeed.right_back_v) / 4.0;
        twist.linear.z = 0;
        twist.angular.x = 0;
        twist.angular.y = 0;
        twist.angular.z = (-wheelSpeed.left_front_v - wheelSpeed.left_back_v + wheelSpeed.right_front_v + wheelSpeed.right_back_v) / (2.0 * (track_width_ + wheel_width_));
    } else {
        double v_left = (wheelSpeed.left_front_v + wheelSpeed.left_back_v) / 2.0;
        double v_right = (wheelSpeed.right_front_v + wheelSpeed.right_back_v) / 2.0;

        twist.linear.x = 0.0; // 非麦克纳姆没有侧向速度
        twist.linear.y = (v_left + v_right) / 2.0;
        twist.angular.z = (v_right - v_left) / wheel_width_;
    }
    return twist;
}

WheelSpeed MotionControl::_inverseKinematics(const geometry_msgs__msg__Twist &twist) {
    WheelSpeed wheelSpeed;
    if (is_mecanum_wheel_) {
        wheelSpeed.left_front_v = twist.linear.x + twist.linear.y - twist.angular.z * (track_width_ + wheel_width_) / 2.0;
        wheelSpeed.left_back_v = -twist.linear.x + twist.linear.y - twist.angular.z * (track_width_ + wheel_width_) / 2.0;
        wheelSpeed.right_front_v = -twist.linear.x + twist.linear.y + twist.angular.z * (track_width_ + wheel_width_) / 2.0;
        wheelSpeed.right_back_v = twist.linear.x + twist.linear.y + twist.angular.z * (track_width_ + wheel_width_) / 2.0;

        auto max_v = std::max({fabs(wheelSpeed.left_front_v), fabs(wheelSpeed.left_back_v), fabs(wheelSpeed.right_front_v), fabs(wheelSpeed.right_back_v)});
        if (max_v > max_v_) {
            auto scale = max_v_ / max_v;
            wheelSpeed.left_front_v *= scale;
            wheelSpeed.left_back_v *= scale;
            wheelSpeed.right_front_v *= scale;
            wheelSpeed.right_back_v *= scale;
        }
    } else {
        float v = twist.linear.y;  // 前进线速度
        float w = twist.angular.z; // 角速度（绕 z 轴）

        // 左右轮速度
        float v_left = v - w * wheel_width_ / 2.0;
        float v_right = v + w * wheel_width_ / 2.0;

        // 赋值给四个轮子（左右分别相等）
        wheelSpeed.left_front_v = v_left;
        wheelSpeed.left_back_v = v_left;
        wheelSpeed.right_front_v = v_right;
        wheelSpeed.right_back_v = v_right;

        // 限幅（跟麦克纳姆分支同样处理）
        auto max_v = std::max({fabs(wheelSpeed.left_front_v), fabs(wheelSpeed.left_back_v), fabs(wheelSpeed.right_front_v), fabs(wheelSpeed.right_back_v)});
        if (max_v > max_v_) {
            auto scale = max_v_ / max_v;
            wheelSpeed.left_front_v *= scale;
            wheelSpeed.left_back_v *= scale;
            wheelSpeed.right_front_v *= scale;
            wheelSpeed.right_back_v *= scale;
        }
    }
    return wheelSpeed;
}

void MotionControl::read_params(motion_settings_service__srv__MotionSettingsService_Response *response) {
    response->milliseconds = milliseconds_;

    response->motor_enable_flags = motor_enable_flags_;
    response->enable_speed_plan = enable_speed_plan_;

    response->speed_percent = speed_percent_;
    response->max_v = max_v_;
    response->max_acc = max_acc_;
    response->jerk = jerk_;

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

void MotionControl::save_params() {
    preferences_.begin("params", false);
    preferences_.clear();

    preferences_.putInt("millisec", milliseconds_);
    preferences_.putBool("spdPlan", enable_speed_plan_);

    preferences_.putFloat("maxV", max_v_);
    preferences_.putFloat("maxAcc", max_acc_);
    preferences_.putFloat("jerk", jerk_);

    preferences_.end();

    left_front_motor_control_->save_pid_params();
    left_back_motor_control_->save_pid_params();
    right_front_motor_control_->save_pid_params();
    right_back_motor_control_->save_pid_params();
}

void MotionControl::_load_params() {
    preferences_.begin("params", true); // 只读模式

    milliseconds_ = preferences_.getInt("millisec", milliseconds_);
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

void MotionControl::read_config(motion_settings_service__srv__MotionSettingsService_Response *response) {
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

void MotionControl::save_config() {
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
}

void MotionControl::_load_config() {
    preferences_.begin("settings", true); // 只读模式

    is_mecanum_wheel_ = preferences_.getBool("isMeWhe", is_mecanum_wheel_);
    wheel_width_ = preferences_.getFloat("wheWid", wheel_width_);
    track_width_ = preferences_.getFloat("traWid", track_width_);

    preferences_.end();

    left_front_motor_control_->load_motor_params();
    left_back_motor_control_->load_motor_params();
    right_front_motor_control_->load_motor_params();
    right_back_motor_control_->load_motor_params();
}

void MotionControl::update_target_max_speed() {
    auto left_front_max_wheel_speed = left_front_motor_control_->get_max_speed();
    auto left_back_max_wheel_speed = left_back_motor_control_->get_max_speed();
    auto right_front_max_wheel_speed = right_front_motor_control_->get_max_speed();
    auto right_back_max_wheel_speed = right_back_motor_control_->get_max_speed();

    target_max_v_ = std::min({left_front_max_wheel_speed, right_front_max_wheel_speed, left_back_max_wheel_speed, right_back_max_wheel_speed});
    speed_percent_ = max_v_ / target_max_v_;
}

void MotionControl::test_motors() {
    for (int pwm = 0; pwm <= 1024; pwm += 25) {
        left_front_motor_control_->set_speed(pwm);
        left_back_motor_control_->set_speed(pwm);
        right_front_motor_control_->set_speed(pwm);
        right_back_motor_control_->set_speed(pwm);

        vTaskDelay(3000 / portTICK_PERIOD_MS);

        auto left_front_current = left_front_motor_control_->get_encoder_count_change();
        auto left_back_current = left_back_motor_control_->get_encoder_count_change();
        auto right_front_current = right_front_motor_control_->get_encoder_count_change();
        auto right_back_current = right_back_motor_control_->get_encoder_count_change();
        Serial.printf("%d, %d, %d, %d, %d\n", pwm, left_front_current, left_back_current, right_front_current, right_back_current);
    }

    left_front_motor_control_->set_speed(0);
    left_back_motor_control_->set_speed(0);
    right_front_motor_control_->set_speed(0);
    right_back_motor_control_->set_speed(0);
}