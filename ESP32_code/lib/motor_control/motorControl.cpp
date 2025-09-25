#include "motorControl.h"

MotorControl::MotorControl(const std::string &name) : name_(name) {
    motor_ = std::make_shared<Motor>();
    encoder_ = std::make_shared<Encoder>();
    if (name.empty())
        pidControl_ = std::make_shared<PIDControl>();
    else
        pidControl_ = std::make_shared<PIDControl>(name + "pid");
}

bool MotorControl::init_success() {
    return encoder_->init_success() && motor_->init_success();
}

void MotorControl::update(float dt) {
    encoder_->update(dt);
}

void MotorControl::reset() {
}

void MotorControl::set_motor_params(const MotorParams &motorParams) {
    motorParams_ = motorParams;

    _update_max_v();
    _set_pins_params();
}

void MotorControl::set_motor_params(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute) {
    motorParams_.motor_AIN1 = motor_AIN1;
    motorParams_.motor_AIN2 = motor_AIN2;
    motorParams_.motor_pwmPin = motor_pwmPin;
    motorParams_.encoder_pinA = encoder_pinA;
    motorParams_.encoder_pinB = encoder_pinB;
    motorParams_.wheel_diameter = wheel_diameter;
    motorParams_.pluses_per_revolution = pluses_per_revolution;
    motorParams_.revolutions_per_minute = revolutions_per_minute;

    _update_max_v();
    _set_pins_params();
}

const MotorParams &MotorControl::get_motor_params() {
    return motorParams_;
}

void MotorControl::save_motor_params() {
    preferences_.begin(name_.c_str(), false);
    preferences_.clear();
    preferences_.putInt("moPinA", motorParams_.motor_AIN1);
    preferences_.putInt("moPinB", motorParams_.motor_AIN2);
    preferences_.putInt("moPWMPin", motorParams_.motor_pwmPin);
    preferences_.putInt("enPinA", motorParams_.encoder_pinA);
    preferences_.putInt("enPinB", motorParams_.encoder_pinB);
    preferences_.putInt("plPeRe", motorParams_.pluses_per_revolution);
    preferences_.putInt("rePeMi", motorParams_.revolutions_per_minute);
    preferences_.putFloat("wheDia", motorParams_.wheel_diameter);
    preferences_.end();
}

void MotorControl::load_motor_params() {
    preferences_.begin(name_.c_str(), true); // 只读模式
    motorParams_.motor_AIN1 = preferences_.getInt("moPinA", motorParams_.motor_AIN1);
    motorParams_.motor_AIN2 = preferences_.getInt("moPinB", motorParams_.motor_AIN2);
    motorParams_.motor_pwmPin = preferences_.getInt("moPWMPin", motorParams_.motor_pwmPin);
    motorParams_.encoder_pinA = preferences_.getInt("enPinA", motorParams_.encoder_pinA);
    motorParams_.encoder_pinB = preferences_.getInt("enPinB", motorParams_.encoder_pinB);
    motorParams_.pluses_per_revolution = preferences_.getInt("plPeRe", motorParams_.pluses_per_revolution);
    motorParams_.revolutions_per_minute = preferences_.getInt("rePeMi", motorParams_.revolutions_per_minute);
    motorParams_.wheel_diameter = preferences_.getFloat("wheDia", motorParams_.wheel_diameter);
    preferences_.end();

    _update_max_v();
    _set_pins_params();
}

void MotorControl::set_pid_params(float p, float i, float d, float max_total_integral) {
    pidControl_->set_pid_params(p, i, d, max_total_integral);
}

void MotorControl::set_pid_params(const PidParams &pidParams) {
    pidControl_->set_pid_params(pidParams);
}

const PidParams &MotorControl::get_pid_params() {
    return pidControl_->get_pid_params();
}

void MotorControl::save_pid_params() {
    pidControl_->save();
}
void MotorControl::load_pid_params() {
    pidControl_->load();
}

void MotorControl::move() {
    motor_->move();
}

void MotorControl::stop() {
    motor_->stop();
}

void MotorControl::brake() {
    motor_->brake();
}

float MotorControl::get_current_speed() {
    return current_v_;
}

float MotorControl::get_current_acc() {
    return current_acc_;
}

float MotorControl::get_target_speed() {
    return target_v_;
}

float MotorControl::get_target_acc() {
    return target_acc_;
}

float MotorControl::get_distance_change() {
    if (motorParams_.pluses_per_revolution == 0)
        return 0;
    else
        return encoder_->get_count_change() * PI * motorParams_.wheel_diameter / motorParams_.pluses_per_revolution;
}

long MotorControl::get_encoder_count() {
    return encoder_->get_count();
}

void MotorControl::set_speed(float target_v, float dt, bool pid_adjust) {
    target_v_ = target_v;
    latest_current_v_ = get_distance_change() / dt;
    current_acc_ = (latest_current_v_ - current_v_) / dt;
    current_v_ = latest_current_v_;
    if (pid_adjust) {
        pid_value_ = pidControl_->calculate(current_v_ * 1000, target_v_ * 1000, dt) / 100.0;
        if (fabs(current_v_) < 0.001 && fabs(target_v_) < 0.001) {
            pid_value_ = 0;
            pidControl_->reset();
        }
    } else {
        pid_value_ = target_v_ / max_v_;
        pidControl_->reset();
    }
    motor_->set_speed(pid_value_);
}

float MotorControl::get_max_speed() {
    return max_v_;
}

void MotorControl::_set_pins_params() {
    motor_->set_pins(motorParams_.motor_AIN1, motorParams_.motor_AIN2, motorParams_.motor_pwmPin);
    encoder_->set_pins(motorParams_.encoder_pinA, motorParams_.encoder_pinB);
}

void MotorControl::_update_max_v() {
    max_v_ = motorParams_.revolutions_per_minute * PI * motorParams_.wheel_diameter / 60;
}