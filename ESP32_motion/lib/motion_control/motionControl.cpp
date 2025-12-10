#include "motionControl.h"

MotionControl::MotionControl() {
    speedPlan_ = std::make_shared<SpeedPlan>();
    left_front_motor_control_ = std::make_shared<MotorControl>("lfm");
    left_back_motor_control_ = std::make_shared<MotorControl>("lbm");
    right_front_motor_control_ = std::make_shared<MotorControl>("rfm");
    right_back_motor_control_ = std::make_shared<MotorControl>("rbm");

    line_speed_loop_ = std::make_shared<PIDControl>("lsl");
    angle_speed_loop_ = std::make_shared<PIDControl>("asl");
    position_loop_ = std::make_shared<PIDControl>("pl");

    mutex_ = xSemaphoreCreateMutex();
    control_queue_ = xQueueCreate(10, sizeof(int));
}

MotionControl::~MotionControl() {}

MotionControl &MotionControl::get_instance() {
    static MotionControl instance; // C++11 保证线程安全初始化
    return instance;
}

void MotionControl::init() {
    _load_config();
    _load_params();

    update_target_max_speed();

    set_milliseconds(milliseconds_);
    set_speed_plan_parms(max_v_, max_acc_, jerk_);

    xTaskCreatePinnedToCore(control_loop, "control_loop", 8192, this, 0, NULL, 1);
}

void MotionControl::start_task() {
    _start_control_timer();
}

void MotionControl::stop_task() {
    stop_move();
    _stop_control_timer();
}

void MotionControl::restart_task() {
    stop_task();
    delay(100);
    start_task();
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

void MotionControl::set_position_pid_params(float p, float i, float d, float max_total_integral) {
    position_loop_->set_pid_params(p, i, d, max_total_integral);
}

void MotionControl::set_line_speed_pid_params(float p, float i, float d, float max_total_integral) {
    line_speed_loop_->set_pid_params(p, i, d, max_total_integral);
}

void MotionControl::set_angle_speed_pid_params(float p, float i, float d, float max_total_integral) {
    angle_speed_loop_->set_pid_params(p, i, d, max_total_integral);
}

void MotionControl::set_speed_plan_parms(float max_v, float max_acc, float jerk) {
    if (max_v > target_max_v_)
        max_v = target_max_v_;

    max_v_ = max_v;
    max_acc_ = max_acc;
    jerk_ = jerk;

    speed_percent_ = max_v_ / target_max_v_;
    max_w_ = 2.0 * max_v_ / (track_width_ + wheel_width_);

    speedPlan_->set_maxAcc_and_jerk(max_acc_, jerk_);
}

void MotionControl::set_wheel_type(bool is_mecanum_wheel) {
    is_mecanum_wheel_ = is_mecanum_wheel;
}

void MotionControl::set_milliseconds(int milliseconds) {
    int milliseconds_tmp = milliseconds_;
    milliseconds_ = milliseconds;

    if (esp_timer_is_active(control_timer_) && milliseconds_tmp != milliseconds_) {
        _stop_control_timer();
    }
    _start_control_timer();
}

int MotionControl::get_milliseconds() {
    return milliseconds_;
}

void MotionControl::set_loop_period_cnt(int position_loop_period_cnt, int speed_loop_period_cnt) {
    position_loop_period_cnt_ = position_loop_period_cnt;
    speed_loop_period_cnt_ = speed_loop_period_cnt;
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
    max_w_ = 2.0 * max_v_ / (track_width_ + wheel_width_);
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

void MotionControl::_start_control_timer() {
    if (!control_timer_) {
        esp_timer_create_args_t timer_args = {
            .callback = &control_timer_callback,
            .arg = NULL,
            .name = "control_timer_callback"};
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

void MotionControl::_stop_control_timer() {
    stop_move();
    if (control_timer_ && esp_timer_is_active(control_timer_)) {
        esp_timer_stop(control_timer_);
    }
}

void MotionControl::move_relative_euler_pose(const EulerPose &eulerPose) {
    target_euler_pose_.x = current_euler_pose_.x + eulerPose.x;
    target_euler_pose_.y = current_euler_pose_.y + eulerPose.y;
    target_euler_pose_.yaw = current_euler_pose_.yaw + eulerPose.yaw;

    while (target_euler_pose_.yaw > PI) {
        target_euler_pose_.yaw -= 2.0 * PI;
    }
    while (target_euler_pose_.yaw < -PI) {
        target_euler_pose_.yaw += 2.0 * PI;
    }
}

void MotionControl::move_absolute_euler_pose(const EulerPose &eulerPose) {
    target_euler_pose_.x = eulerPose.x;
    target_euler_pose_.y = eulerPose.y;
    target_euler_pose_.yaw = eulerPose.yaw;

    while (target_euler_pose_.yaw > PI) {
        target_euler_pose_.yaw -= 2.0 * PI;
    }
    while (target_euler_pose_.yaw < -PI) {
        target_euler_pose_.yaw += 2.0 * PI;
    }
}

void MotionControl::brake() {
    if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
        if (!wheel_speed_deque_.empty()) {
            wheel_speed_deque_.clear();
            target_wheel_v_.left_back_v = 0;
            target_wheel_v_.left_front_v = 0;
            target_wheel_v_.right_back_v = 0;
            target_wheel_v_.right_front_v = 0;
        }
        xSemaphoreGive(mutex_);
    }
    running_ = false;
    left_front_motor_control_->brake();
    left_back_motor_control_->brake();
    right_front_motor_control_->brake();
    right_back_motor_control_->brake();
}

void MotionControl::stop_move() {
    // auto wheel_speed = WheelSpeed();
    // wheel_speed.left_front_v = 0;
    // wheel_speed.left_back_v = 0;
    // wheel_speed.right_front_v = 0;
    // wheel_speed.right_back_v = 0;
    // start_move(wheel_speed);

    target_twist_.linear.x = 0;
    target_twist_.linear.y = 0;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::move_front() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = max_v;
    // wheel_speed.left_back_v = max_v;
    // wheel_speed.right_front_v = max_v;
    // wheel_speed.right_back_v = max_v;

    target_twist_.linear.x = 0;
    target_twist_.linear.y = max_v_;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::move_back() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = -max_v;
    // wheel_speed.left_back_v = -max_v;
    // wheel_speed.right_front_v = -max_v;
    // wheel_speed.right_back_v = -max_v;
    // start_move(wheel_speed);

    target_twist_.linear.x = 0;
    target_twist_.linear.y = -max_v_;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::move_left() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = -max_v;
    // wheel_speed.left_back_v = max_v;
    // wheel_speed.right_front_v = max_v;
    // wheel_speed.right_back_v = -max_v;
    // start_move(wheel_speed);

    target_twist_.linear.x = -max_v_;
    target_twist_.linear.y = 0;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::move_right() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = max_v;
    // wheel_speed.left_back_v = -max_v;
    // wheel_speed.right_front_v = -max_v;
    // wheel_speed.right_back_v = max_v;
    // start_move(wheel_speed);

    target_twist_.linear.x = max_v_;
    target_twist_.linear.y = 0;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::move_left_front() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = 0;
    // wheel_speed.left_back_v = max_v;
    // wheel_speed.right_front_v = max_v;
    // wheel_speed.right_back_v = 0;
    // start_move(wheel_speed);

    target_twist_.linear.x = -max_v_;
    target_twist_.linear.y = max_v_;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::move_right_back() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = 0;
    // wheel_speed.left_back_v = -max_v;
    // wheel_speed.right_front_v = -max_v;
    // wheel_speed.right_back_v = 0;
    // start_move(wheel_speed);

    target_twist_.linear.x = max_v_;
    target_twist_.linear.y = -max_v_;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::move_right_front() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = max_v;
    // wheel_speed.left_back_v = 0;
    // wheel_speed.right_front_v = 0;
    // wheel_speed.right_back_v = max_v;
    // start_move(wheel_speed);

    target_twist_.linear.x = max_v_;
    target_twist_.linear.y = max_v_;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::move_left_back() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = -max_v;
    // wheel_speed.left_back_v = 0;
    // wheel_speed.right_front_v = 0;
    // wheel_speed.right_back_v = -max_v;
    // start_move(wheel_speed);

    target_twist_.linear.x = -max_v_;
    target_twist_.linear.y = -max_v_;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = 0;
    start_move(target_twist_);
}

void MotionControl::turn_left() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = -max_v;
    // wheel_speed.left_back_v = -max_v;
    // wheel_speed.right_front_v = max_v;
    // wheel_speed.right_back_v = max_v;
    // start_move(wheel_speed);

    target_twist_.linear.x = 0;
    target_twist_.linear.y = 0;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = max_w_;
    start_move(target_twist_);
}

void MotionControl::turn_right() {
    // auto wheel_speed = WheelSpeed();
    // float max_v = 0;
    // if (is_mecanum_wheel_) {
    //     max_v = max_v_ * 2 / sqrt(2);
    // } else {
    //     max_v = max_v_;
    // }
    // wheel_speed.left_front_v = max_v;
    // wheel_speed.left_back_v = max_v;
    // wheel_speed.right_front_v = -max_v;
    // wheel_speed.right_back_v = -max_v;
    // start_move(wheel_speed);

    target_twist_.linear.x = 0;
    target_twist_.linear.y = 0;
    target_twist_.linear.z = 0;
    target_twist_.angular.x = 0;
    target_twist_.angular.y = 0;
    target_twist_.angular.z = -max_w_;
    start_move(target_twist_);
}

void MotionControl::start_move(const geometry_msgs__msg__Twist &twist) {
    target_twist_ = twist;
    _plan_wheel_speed();
}

void MotionControl::start_move(WheelSpeed &target_wheel_speed) {
    target_twist_ = _forwardKinematics(target_wheel_speed);
    _plan_wheel_speed();
}

void MotionControl::_plan_wheel_speed() { // WheelSpeed &target_wheel_speed
    running_ = true;
    std::deque<WheelSpeed> speed_deque;

    auto target_wheel_speed = _inverseKinematics(target_twist_);

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

            std::deque<float> single_wheel_speed_deque = speedPlan_->plan(planned_current_v, planned_target_v, dt_);
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

// void MotionControl::reset() {
//     period_cnt_ = 0;
//     speed_loop_dt_ = 0;

//     if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
//         wheel_speed_deque_.clear();
//         wheel_speed_deque_.push_back(WheelSpeed());
//         xSemaphoreGive(mutex_);
//     }

//     position_loop_->reset();
//     line_speed_loop_->reset();
//     angle_speed_loop_->reset();
// }

void MotionControl::update() {
    if (milliseconds_ <= 0) {
        return;
    }

    time_record_ = esp_timer_get_time();
    dt_ = (time_record_ - last_time_record_) / 1e6;

    left_front_motor_control_->update(dt_);
    left_back_motor_control_->update(dt_);
    right_front_motor_control_->update(dt_);
    right_back_motor_control_->update(dt_);

    if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
        if (!wheel_speed_deque_.empty()) {
            target_wheel_v_ = wheel_speed_deque_.front();
            wheel_speed_deque_.pop_front();
        }
        xSemaphoreGive(mutex_);
    }

    current_wheel_v_.left_back_v = left_front_motor_control_->get_current_speed();
    current_wheel_v_.left_front_v = left_back_motor_control_->get_current_speed();
    current_wheel_v_.right_back_v = right_front_motor_control_->get_current_speed();
    current_wheel_v_.right_front_v = right_back_motor_control_->get_current_speed();

    current_twist_ = _forwardKinematics(current_wheel_v_);

    current_euler_pose_.x += (current_twist_.linear.x + last_twist_.linear.x) / 2.0 * dt_;
    current_euler_pose_.y += (current_twist_.linear.y + last_twist_.linear.y) / 2.0 * dt_;
    current_euler_pose_.yaw += (current_twist_.angular.z + last_twist_.angular.z) / 2.0 * dt_;
    while (current_euler_pose_.yaw > PI) {
        current_euler_pose_.yaw -= 2.0 * PI;
    }
    while (current_euler_pose_.yaw < -PI) {
        current_euler_pose_.yaw += 2.0 * PI;
    }

    last_twist_ = current_twist_;

    if (running_) {
        if (motor_enable_flags_ & 0x01) {
            left_front_motor_control_->set_speed(target_wheel_v_.left_front_v, dt_, true); // running_
        } else {
            left_front_motor_control_->set_speed(0, dt_, false);
        }
        if (motor_enable_flags_ & 0x02) {
            left_back_motor_control_->set_speed(target_wheel_v_.left_back_v, dt_, true);
        } else {
            left_back_motor_control_->set_speed(0, dt_, false);
        }
        if (motor_enable_flags_ & 0x04) {
            right_front_motor_control_->set_speed(target_wheel_v_.right_front_v, dt_, true);
        } else {
            right_front_motor_control_->set_speed(0, dt_, false);
        }
        if (motor_enable_flags_ & 0x08) {
            right_back_motor_control_->set_speed(target_wheel_v_.right_back_v, dt_, true);
        } else {
            right_back_motor_control_->set_speed(0, dt_, false);
        }
    } else {
        left_front_motor_control_->set_speed(0, dt_, false);
        left_back_motor_control_->set_speed(0, dt_, false);
        right_front_motor_control_->set_speed(0, dt_, false);
        right_back_motor_control_->set_speed(0, dt_, false);
    }
    left_front_motor_control_->move();
    left_back_motor_control_->move();
    right_front_motor_control_->move();
    right_back_motor_control_->move();

    last_time_record_ = time_record_;

    if (esp_timer_get_time() - time_record_ >= milliseconds_ * 1000) {
        serial_print("控制处理超时(ms): " + std::to_string((esp_timer_get_time() - time_record_) / 1000.0));
    }
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
    }
    return wheelSpeed;
}

void MotionControl::read_params(motion_settings_service__srv__MotionSettingsService_Response *response) {
    response->milliseconds = milliseconds_;
    response->position_loop_milliseconds_cnt = position_loop_period_cnt_;
    response->speed_loop_milliseconds_cnt = speed_loop_period_cnt_;

    response->motor_enable_flags = motor_enable_flags_;
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

void MotionControl::save_params() {
    preferences_.begin("params", false);
    preferences_.clear();

    preferences_.putInt("millisec", milliseconds_);
    preferences_.putInt("posPeCnt", position_loop_period_cnt_);
    preferences_.putInt("spdPeCnt", speed_loop_period_cnt_);
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

motion_status_msgs__msg__MotionStatus &MotionControl::get_motion_status_msg() {
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

String MotionControl::get_http_data() {
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

QueueHandle_t &MotionControl::get_control_deque() {
    return control_queue_;
}

void MotionControl::control_loop(void *args) {
    auto control = static_cast<MotionControl *>(args);
    while (1) {
        int msg;
        if (xQueueReceive(control->get_control_deque(), &msg, portMAX_DELAY)) {
            control->update();
        }
    }
    vTaskDelete(NULL);
}

void MotionControl::control_timer_callback(void *args) {
    int trigger = 1;
    xQueueSendFromISR(MotionControl::get_instance().get_control_deque(), &trigger, NULL);
}