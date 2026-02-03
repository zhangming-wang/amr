#include "motionControlTask.h"

MotionControlTask::MotionControlTask() {
    task_name_ = "motion_control_task";
    priority_ = 12;
    core_id_ = 1;
    stack_size_ = 16384;

    mutex_ = xSemaphoreCreateMutex();

    task_tick_count_ = xTaskGetTickCount();

    speedPlan_ = std::make_shared<SpeedPlan>();
    left_motor_control_ = std::make_shared<MotorControl>("lm");
    right_motor_control_ = std::make_shared<MotorControl>("rm");

    // _load_config();
    // _load_params();

    left_motor_control_->set_motor_config(11, 12, 10, 9, 13, 0.065f, 1320, 310);
    right_motor_control_->set_motor_config(6, 7, 15, 16, 4, 0.065f, 1320, 310);

    _refresh_target_max_v();
}

void MotionControlTask::set_speed_plan_parms(const SpdPlanParams &params) {
    speed_percent_ = params.max_v / target_max_v_;
    speedPlan_->set_params(params);
}
const SpdPlanParams &MotionControlTask::get_speed_plan_parms() {
    return speedPlan_->get_params();
}

void MotionControlTask::set_speed_percent(float percent) {
    percent = fabs(percent);
    if (percent >= 1)
        percent = 1;
    speed_percent_ = percent;
    auto spd_params = speedPlan_->get_params();
    spd_params.max_v = target_max_v_ * speed_percent_;
    speedPlan_->set_params(spd_params);
}

float MotionControlTask::get_speed_percent() {
    return speed_percent_;
}

void MotionControlTask::brake() {
    running_ = false;
    if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
        if (!wheel_speed_deque_.empty()) {
            wheel_speed_deque_.clear();
        }
        xSemaphoreGive(mutex_);
    }
    left_motor_control_->brake();
    right_motor_control_->brake();
}

void MotionControlTask::stop_move() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::move_front() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = speedPlan_->get_params().max_v;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::move_back() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = -speedPlan_->get_params().max_v;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::move_left() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = -speedPlan_->get_params().max_v;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::move_right() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = speedPlan_->get_params().max_v;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::move_left_front() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = -speedPlan_->get_params().max_v;
    target_twist.linear.y = speedPlan_->get_params().max_v;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::move_right_back() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = speedPlan_->get_params().max_v;
    target_twist.linear.y = -speedPlan_->get_params().max_v;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::move_right_front() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = speedPlan_->get_params().max_v;
    target_twist.linear.y = speedPlan_->get_params().max_v;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::move_left_back() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = -speedPlan_->get_params().max_v;
    target_twist.linear.y = -speedPlan_->get_params().max_v;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 0;
    set_twist(target_twist);
}

void MotionControlTask::turn_left() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = 2.0f * speedPlan_->get_params().max_v / wheel_width_;
    set_twist(target_twist);
}

void MotionControlTask::turn_right() {
    geometry_msgs__msg__Twist target_twist;
    target_twist.linear.x = 0;
    target_twist.linear.y = 0;
    target_twist.linear.z = 0;
    target_twist.angular.x = 0;
    target_twist.angular.y = 0;
    target_twist.angular.z = -2.0f * speedPlan_->get_params().max_v / wheel_width_;

    set_twist(target_twist);
}

void MotionControlTask::set_twist(const geometry_msgs__msg__Twist &twist) {
    _plan_wheel_speed(_inverseKinematics(twist));
}

void MotionControlTask::set_wheels_speed(const MotionControlTask::WheelSpeed &target_wheel_speed) {
    _plan_wheel_speed(target_wheel_speed);
}

void MotionControlTask::_plan_wheel_speed(const MotionControlTask::WheelSpeed &target_wheel_speed) { // MotionControlTask::WheelSpeed &target_wheel_speed
    running_ = true;
    std::deque<MotionControlTask::WheelSpeed> speed_deque;

    if (speedPlan_->get_params().enable) {
        float MIN_V_CHANGE = 0.001;
        auto changed_left_v = target_wheel_speed.left_v - target_wheel_v_.left_v;
        auto changed_right_v = target_wheel_speed.right_v - target_wheel_v_.right_v;

        if (fabs(changed_left_v) > MIN_V_CHANGE || fabs(changed_right_v) > MIN_V_CHANGE) {
            std::map<float, int> wheel_change_map;
            wheel_change_map[std::fabs(changed_left_v)] = 0;
            wheel_change_map[std::fabs(changed_right_v)] = 1;

            float planned_current_v = 0, planned_target_v = 0, changed_v = 0;
            MotionControlTask::WheelSpeed wheel_speed;

            if (wheel_change_map.rbegin()->second == 0) {
                planned_current_v = target_wheel_v_.left_v;
                planned_target_v = target_wheel_speed.left_v;
                changed_v = changed_left_v;
            } else if (wheel_change_map.rbegin()->second == 1) {
                planned_current_v = target_wheel_v_.right_v;
                planned_target_v = target_wheel_speed.right_v;
                changed_v = changed_right_v;
            }

            std::deque<float> single_wheel_speed_deque = speedPlan_->plan(planned_current_v, planned_target_v);
            for (auto value : single_wheel_speed_deque) {
                auto speed_bi = (value - planned_current_v) / changed_v;
                if (fabs(changed_left_v) < MIN_V_CHANGE) {
                    wheel_speed.left_v = target_wheel_speed.left_v;
                } else {
                    wheel_speed.left_v = speed_bi * changed_left_v + target_wheel_v_.left_v;
                }
                if (fabs(changed_right_v) < MIN_V_CHANGE) {
                    wheel_speed.right_v = target_wheel_speed.right_v;
                } else {
                    wheel_speed.right_v = speed_bi * changed_right_v + target_wheel_v_.right_v;
                }
                speed_deque.push_back(wheel_speed);
            }
        }
    } else {
        speed_deque.push_back(target_wheel_speed);
    }

    if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
        wheel_speed_deque_ = std::move(speed_deque);
        xSemaphoreGive(mutex_);
    }
}

void MotionControlTask::update() {
    static unsigned long last_time = 0, current_time = 0;
    current_time = millis();
    if (last_time != current_time && last_time != 0) {
        dt_ = (current_time - last_time) / 1000.0;
        left_motor_control_->update();
        right_motor_control_->update();

        if (running_) {
            if (xSemaphoreTake(mutex_, portMAX_DELAY) == pdTRUE) {
                if (!wheel_speed_deque_.empty()) {
                    target_wheel_v_ = wheel_speed_deque_.front();
                    wheel_speed_deque_.pop_front();
                }
                xSemaphoreGive(mutex_);

                if (!(motor_enable_flags_ & 0x01))
                    target_wheel_v_.left_v = 0;
                if (!(motor_enable_flags_ & 0x02))
                    target_wheel_v_.right_v = 0;
            }
        } else {
            target_wheel_v_.left_v = 0;
            target_wheel_v_.right_v = 0;
        }

        left_motor_control_->set_speed(target_wheel_v_.left_v, dt_, running_);
        right_motor_control_->set_speed(target_wheel_v_.right_v, dt_, running_);

        left_motor_control_->move();
        right_motor_control_->move();
    }
    last_time = current_time;
    // test_motors();
    vTaskDelayUntil(&task_tick_count_, speedPlan_->get_params().milliseconds);
}

void MotionControlTask::get_data(motion_status_msgs__msg__MotionStatus &msg) {
    msg.drivers_status[0].current_v = left_motor_control_->get_current_speed();
    msg.drivers_status[0].target_v = left_motor_control_->get_target_speed();
    msg.drivers_status[0].total_distance = left_motor_control_->get_total_distance();
    msg.drivers_status[0].dt_distance = left_motor_control_->get_dt_distance();

    msg.drivers_status[1].current_v = right_motor_control_->get_current_speed();
    msg.drivers_status[1].target_v = right_motor_control_->get_target_speed();
    msg.drivers_status[1].total_distance = right_motor_control_->get_total_distance();
    msg.drivers_status[1].dt_distance = right_motor_control_->get_dt_distance();
}

geometry_msgs__msg__Twist MotionControlTask::_forwardKinematics(const MotionControlTask::WheelSpeed &wheelSpeed) {
    geometry_msgs__msg__Twist twist;
    double v_left = wheelSpeed.left_v;
    double v_right = wheelSpeed.right_v;

    twist.linear.x = 0.0f; // 非麦克纳姆没有侧向速度
    twist.linear.y = (v_left + v_right) / 2.0f;
    twist.angular.z = (v_right - v_left) / wheel_width_;
    return twist;
}

MotionControlTask::WheelSpeed MotionControlTask::_inverseKinematics(const geometry_msgs__msg__Twist &twist) {
    MotionControlTask::WheelSpeed wheelSpeed;
    float v = twist.linear.y;  // 前进线速度
    float w = twist.angular.z; // 角速度（绕 z 轴）

    // 左右轮速度
    float v_left = v - w * wheel_width_ / 2.0f;
    float v_right = v + w * wheel_width_ / 2.0f;

    // 赋值给四个轮子（左右分别相等）
    wheelSpeed.left_v = v_left;
    wheelSpeed.right_v = v_right;

    // 限幅（跟麦克纳姆分支同样处理）
    auto max_v = std::max({fabs(wheelSpeed.left_v), fabs(wheelSpeed.right_v)});
    if (max_v > speedPlan_->get_params().max_v) {
        auto scale = speedPlan_->get_params().max_v / max_v;
        wheelSpeed.left_v *= scale;
        wheelSpeed.right_v *= scale;
    }
    return wheelSpeed;
}

void MotionControlTask::write_params(const motion_settings_service__srv__MotionSettingsService_Request *request) {
    motor_enable_flags_ = request->motor_enable_flags;

    left_motor_control_->set_pid_params(request->drivers_settings[0].p,
                                        request->drivers_settings[0].i,
                                        request->drivers_settings[0].d,
                                        request->drivers_settings[0].max_total_i);
    left_motor_control_->set_ff_params(request->drivers_settings[0].k,
                                       request->drivers_settings[0].b);

    right_motor_control_->set_pid_params(request->drivers_settings[1].p,
                                         request->drivers_settings[1].i,
                                         request->drivers_settings[1].d,
                                         request->drivers_settings[1].max_total_i);
    right_motor_control_->set_ff_params(request->drivers_settings[1].k,
                                        request->drivers_settings[1].b);

    speedPlan_->set_params(request->spd_plan_settings.milliseconds,
                           request->spd_plan_settings.max_v,
                           request->spd_plan_settings.max_acc,
                           request->spd_plan_settings.jerk,
                           request->spd_plan_settings.enable);

    speed_percent_ = speedPlan_->get_params().max_v / target_max_v_;
}

void MotionControlTask::read_params(motion_settings_service__srv__MotionSettingsService_Response *response) {
    response->motor_enable_flags = motor_enable_flags_;
    response->speed_percent = speed_percent_;

    response->spd_plan_settings.milliseconds = speedPlan_->get_params().milliseconds;
    response->spd_plan_settings.enable = speedPlan_->get_params().enable;
    response->spd_plan_settings.max_v = speedPlan_->get_params().max_v;
    response->spd_plan_settings.max_acc = speedPlan_->get_params().max_acc;
    response->spd_plan_settings.jerk = speedPlan_->get_params().jerk;

    response->drivers_settings[0].p = left_motor_control_->get_pid_params().p;
    response->drivers_settings[0].i = left_motor_control_->get_pid_params().i;
    response->drivers_settings[0].d = left_motor_control_->get_pid_params().d;
    response->drivers_settings[0].max_total_i = left_motor_control_->get_pid_params().max_total_integral;

    response->drivers_settings[0].k = left_motor_control_->get_ff_params().k;
    response->drivers_settings[0].b = left_motor_control_->get_ff_params().b;

    response->drivers_settings[1].p = right_motor_control_->get_pid_params().p;
    response->drivers_settings[1].i = right_motor_control_->get_pid_params().i;
    response->drivers_settings[1].d = right_motor_control_->get_pid_params().d;
    response->drivers_settings[1].max_total_i = right_motor_control_->get_pid_params().max_total_integral;

    response->drivers_settings[1].k = right_motor_control_->get_ff_params().k;
    response->drivers_settings[1].b = right_motor_control_->get_ff_params().b;
}

void MotionControlTask::save_params() {
    preferences_.begin("mctparams", false);
    preferences_.clear();

    preferences_.putInt("millisec", speedPlan_->get_params().milliseconds);
    preferences_.putBool("spdPlan", speedPlan_->get_params().enable);

    preferences_.putFloat("maxV", speedPlan_->get_params().max_v);
    preferences_.putFloat("maxAcc", speedPlan_->get_params().max_acc);
    preferences_.putFloat("jerk", speedPlan_->get_params().jerk);

    preferences_.end();

    left_motor_control_->save_params();
    right_motor_control_->save_params();
}

void MotionControlTask::_load_params() {
    SpdPlanParams params = speedPlan_->get_params();

    preferences_.begin("mctparams", true); // 只读模式
    params.milliseconds = preferences_.getInt("millisec", params.milliseconds);
    params.enable = preferences_.getBool("spdPlan", params.enable);
    params.max_v = preferences_.getFloat("maxV", params.max_v);
    params.max_acc = preferences_.getFloat("maxAcc", params.max_acc);
    params.jerk = preferences_.getFloat("jerk", params.jerk);
    preferences_.end();

    speedPlan_->set_params(params);

    left_motor_control_->load_params();
    right_motor_control_->load_params();
}

void MotionControlTask::write_config(const motion_settings_service__srv__MotionSettingsService_Request *request) {
    wheel_width_ = request->wheel_width;
    track_width_ = request->track_width;

    left_motor_control_->set_motor_config(request->drivers_settings[0].motor_pina,
                                          request->drivers_settings[0].motor_pinb,
                                          request->drivers_settings[0].encoder_pina,
                                          request->drivers_settings[0].encoder_pinb,
                                          request->drivers_settings[0].motor_pinpwm,
                                          request->drivers_settings[0].wheel_diameter,
                                          request->drivers_settings[0].pluses_per_revolution,
                                          request->drivers_settings[0].revolutions_per_minute);

    right_motor_control_->set_motor_config(request->drivers_settings[1].motor_pina,
                                           request->drivers_settings[1].motor_pinb,
                                           request->drivers_settings[1].encoder_pina,
                                           request->drivers_settings[1].encoder_pinb,
                                           request->drivers_settings[1].motor_pinpwm,
                                           request->drivers_settings[1].wheel_diameter,
                                           request->drivers_settings[1].pluses_per_revolution,
                                           request->drivers_settings[1].revolutions_per_minute);

    _refresh_target_max_v();
}

void MotionControlTask::read_config(motion_settings_service__srv__MotionSettingsService_Response *response) {
    response->wheel_width = wheel_width_;
    response->track_width = track_width_;

    response->drivers_settings[0].motor_pina = left_motor_control_->get_motor_config().motor_AIN1;
    response->drivers_settings[0].motor_pinb = left_motor_control_->get_motor_config().motor_AIN2;
    response->drivers_settings[0].motor_pinpwm = left_motor_control_->get_motor_config().motor_pwmPin;
    response->drivers_settings[0].wheel_diameter = left_motor_control_->get_motor_config().wheel_diameter;
    response->drivers_settings[0].pluses_per_revolution = left_motor_control_->get_motor_config().pluses_per_revolution;
    response->drivers_settings[0].revolutions_per_minute = left_motor_control_->get_motor_config().revolutions_per_minute;
    response->drivers_settings[0].encoder_pina = left_motor_control_->get_motor_config().encoder_pinA;
    response->drivers_settings[0].encoder_pinb = left_motor_control_->get_motor_config().encoder_pinB;

    response->drivers_settings[1].motor_pina = right_motor_control_->get_motor_config().motor_AIN1;
    response->drivers_settings[1].motor_pinb = right_motor_control_->get_motor_config().motor_AIN2;
    response->drivers_settings[1].motor_pinpwm = right_motor_control_->get_motor_config().motor_pwmPin;
    response->drivers_settings[1].wheel_diameter = right_motor_control_->get_motor_config().wheel_diameter;
    response->drivers_settings[1].pluses_per_revolution = right_motor_control_->get_motor_config().pluses_per_revolution;
    response->drivers_settings[1].revolutions_per_minute = right_motor_control_->get_motor_config().revolutions_per_minute;
    response->drivers_settings[1].encoder_pina = right_motor_control_->get_motor_config().encoder_pinA;
    response->drivers_settings[1].encoder_pinb = right_motor_control_->get_motor_config().encoder_pinB;
}

void MotionControlTask::save_config() {
    preferences_.begin("mctsettings", false);
    preferences_.clear();

    preferences_.putFloat("wheWid", wheel_width_);
    preferences_.putFloat("traWid", track_width_);

    preferences_.end();

    left_motor_control_->save_config();
    right_motor_control_->save_config();
}

void MotionControlTask::_load_config() {
    preferences_.begin("mctsettings", true); // 只读模式

    wheel_width_ = preferences_.getFloat("wheWid", wheel_width_);
    track_width_ = preferences_.getFloat("traWid", track_width_);

    preferences_.end();

    left_motor_control_->load_config();
    right_motor_control_->load_config();
}

void MotionControlTask::_refresh_target_max_v() {
    auto left_max_wheel_speed = left_motor_control_->get_max_speed();
    auto right_max_wheel_speed = right_motor_control_->get_max_speed();

    target_max_v_ = std::min({left_max_wheel_speed, right_max_wheel_speed});
    auto spd_params = speedPlan_->get_params();
    if (spd_params.max_v > target_max_v_) {
        spd_params.max_v = target_max_v_;
        speedPlan_->set_params(spd_params);
    }
    speed_percent_ = speedPlan_->get_params().max_v / target_max_v_;
}

void MotionControlTask::test_motors() {
    long left_current = 0;
    long right_current = 0;

    int left_pwm = 0;
    int right_pwm = 0;

    uint left_dead_pwm = 200;
    uint right_dead_pwm = 300;

    // left_motor_control_->set_dead_pwm(left_dead_pwm);
    // right_motor_control_->set_dead_pwm(right_dead_pwm);

    long current_time = millis();
    long previous_time = current_time;

    float dt = 0.0f;

    // for (float target_y = 1500; target_y <= 3000; target_y += 50) {
    //     left_pwm = (target_y + 1234.3) / 6.3719f;
    //     right_pwm = (target_y + 839.27) / 5.0709f;

    //     left_motor_control_->set_speed(left_pwm);
    //     right_motor_control_->set_speed(right_pwm);
    //     // }

    for (int pwm = 400; pwm <= 768; pwm += 4) {
        left_pwm = pwm * -1;
        right_pwm = pwm * -1;

        left_motor_control_->set_speed(left_pwm);
        right_motor_control_->set_speed(right_pwm);

        left_motor_control_->move();
        right_motor_control_->move();

        vTaskDelay(3000 / portTICK_PERIOD_MS);

        left_motor_control_->update();
        right_motor_control_->update();

        current_time = millis();
        dt = (current_time - previous_time) / 1000.0;
        previous_time = current_time;

        left_motor_control_->calculate(0.0f, dt, false);
        right_motor_control_->calculate(0.0f, dt, false);

        left_current = left_motor_control_->get_encoder_count_change();
        right_current = right_motor_control_->get_encoder_count_change();

        Serial.printf(" %d, %d, %d, %d,  %f, %f\n", left_pwm, right_pwm, left_current, right_current, left_motor_control_->get_current_speed(), right_motor_control_->get_current_speed());
    }

    left_motor_control_->set_speed(0);
    right_motor_control_->set_speed(0);
}