#include "motorControl.h"

MotorControl::MotorControl(const std::string &name) : name_(name) {
    motor_ = std::make_shared<Motor>();
    encoder_ = std::make_shared<Encoder>();
    pidControl_ = std::make_shared<PIDControl>();
    ffControl_ = std::make_shared<FFControl>();
}

bool MotorControl::init_success() {
    return encoder_->init_success() && motor_->init_success();
}

void MotorControl::update() {
    encoder_->update();
}

void MotorControl::load_config() {
    preferences_.begin((name_ + "config").c_str(), true); // 只读模式
    motorConfig_.motor_AIN1 = preferences_.getInt("moPinA", motorConfig_.motor_AIN1);
    motorConfig_.motor_AIN2 = preferences_.getInt("moPinB", motorConfig_.motor_AIN2);
    motorConfig_.motor_pwmPin = preferences_.getInt("moPWMPin", motorConfig_.motor_pwmPin);
    motorConfig_.encoder_pinA = preferences_.getInt("enPinA", motorConfig_.encoder_pinA);
    motorConfig_.encoder_pinB = preferences_.getInt("enPinB", motorConfig_.encoder_pinB);
    motorConfig_.pluses_per_revolution = preferences_.getInt("plPeRe", motorConfig_.pluses_per_revolution);
    motorConfig_.revolutions_per_minute = preferences_.getInt("rePeMi", motorConfig_.revolutions_per_minute);
    motorConfig_.wheel_diameter = preferences_.getFloat("wheDia", motorConfig_.wheel_diameter);
    motorConfig_.dead_pwm = preferences_.getUInt("deadPWM", motorConfig_.dead_pwm);
    preferences_.end();

    _refresh_config();
}
void MotorControl::save_config() {
    preferences_.begin((name_ + "config").c_str(), false);
    preferences_.clear();
    preferences_.putInt("moPinA", motorConfig_.motor_AIN1);
    preferences_.putInt("moPinB", motorConfig_.motor_AIN2);
    preferences_.putInt("moPWMPin", motorConfig_.motor_pwmPin);
    preferences_.putInt("enPinA", motorConfig_.encoder_pinA);
    preferences_.putInt("enPinB", motorConfig_.encoder_pinB);
    preferences_.putInt("plPeRe", motorConfig_.pluses_per_revolution);
    preferences_.putInt("rePeMi", motorConfig_.revolutions_per_minute);
    preferences_.putFloat("wheDia", motorConfig_.wheel_diameter);
    preferences_.putUInt("deadPWM", motorConfig_.dead_pwm);
    preferences_.end();
}

void MotorControl::load_params() {
    PidParams pidParams = pidControl_->get_params();
    FFParams ffParams = ffControl_->get_params();

    preferences_.begin((name_ + "params").c_str(), true); // 只读模式

    pidParams.p = preferences_.getFloat("p", pidParams.p);
    pidParams.i = preferences_.getFloat("i", pidParams.i);
    pidParams.d = preferences_.getFloat("d", pidParams.d);
    pidParams.max_total_integral = preferences_.getFloat("maxI", pidParams.max_total_integral);

    ffParams.k = preferences_.getFloat("k", ffParams.k);
    ffParams.b = preferences_.getFloat("b", ffParams.b);
    preferences_.end();

    pidControl_->set_params(pidParams);
    ffControl_->set_params(ffParams);
}

void MotorControl::save_params() {
    preferences_.begin((name_ + "params").c_str(), false);
    preferences_.clear();
    preferences_.putFloat("p", pidControl_->get_params().p);
    preferences_.putFloat("i", pidControl_->get_params().i);
    preferences_.putFloat("d", pidControl_->get_params().d);
    preferences_.putFloat("maxI", pidControl_->get_params().max_total_integral);

    preferences_.putFloat("k", ffControl_->get_params().k);
    preferences_.putFloat("b", ffControl_->get_params().b);
    preferences_.end();
}

void MotorControl::set_motor_config(const MotorConfig &motorConfig) {
    motorConfig_ = motorConfig;

    _refresh_config();
}

void MotorControl::set_motor_config(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute, uint dead_pwm) {
    motorConfig_.motor_AIN1 = motor_AIN1;
    motorConfig_.motor_AIN2 = motor_AIN2;
    motorConfig_.motor_pwmPin = motor_pwmPin;
    motorConfig_.encoder_pinA = encoder_pinA;
    motorConfig_.encoder_pinB = encoder_pinB;
    motorConfig_.wheel_diameter = wheel_diameter;
    motorConfig_.pluses_per_revolution = pluses_per_revolution;
    motorConfig_.revolutions_per_minute = revolutions_per_minute;
    motorConfig_.dead_pwm = dead_pwm;

    _refresh_config();
}

const MotorConfig &MotorControl::get_motor_config() {
    return motorConfig_;
}

void MotorControl::set_pid_params(float p, float i, float d, float max_total_integral) {
    pidControl_->set_params(p, i, d, max_total_integral);
}

void MotorControl::set_pid_params(const PidParams &pidParams) {
    pidControl_->set_params(pidParams);
}

const PidParams &MotorControl::get_pid_params() {
    return pidControl_->get_params();
}

void MotorControl::set_ff_params(const FFParams &ffParams) {
    ffControl_->set_params(ffParams);
}

void MotorControl::set_ff_params(float k, float b) {
    ffControl_->set_params(k, b);
}

const FFParams &MotorControl::get_ff_params() {
    return ffControl_->get_params();
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

float MotorControl::get_total_distance() {
    if (motorConfig_.pluses_per_revolution == 0)
        return 0;
    else
        return encoder_->get_count() * PI * motorConfig_.wheel_diameter / motorConfig_.pluses_per_revolution;
}

float MotorControl::get_dt_distance() {
    if (motorConfig_.pluses_per_revolution == 0)
        return 0;
    else
        return encoder_->get_count_change() * PI * motorConfig_.wheel_diameter / motorConfig_.pluses_per_revolution;
}

long MotorControl::get_encoder_count() {
    return encoder_->get_count();
}

long MotorControl::get_encoder_count_change() {
    return encoder_->get_count_change();
}

void MotorControl::calculate(float target_v, float dt, bool running) {
    target_v_ = target_v;

    raw_vel_ = get_dt_distance() / dt;
    smoothed_v_ = (alpha_ * raw_vel_) + ((1.0f - alpha_) * smoothed_v_);
    current_acc_ = (smoothed_v_ - current_v_) / dt;
    current_v_ = smoothed_v_;

    if (running) {
        pid_value_ = pidControl_->calculate(current_v_, target_v_, dt);
        ff_value_ = ffControl_->calculate(target_v_ * motorConfig_.pluses_per_revolution / (PI * motorConfig_.wheel_diameter));
    } else {
        pid_value_ = 0;
        ff_value_ = 0;
    }
    cal_pwm_ = pid_value_ + ff_value_;

    if (fabs(cal_pwm_) < motorConfig_.dead_pwm) {
        cal_pwm_ = 0;
        pidControl_->reset();
    } else {
        Serial.printf("pid: %f, ff: %f, pwm: %d\n", pid_value_, ff_value_, cal_pwm_);
    }
}

void MotorControl::set_speed(float target_v, float dt, bool running) {
    calculate(target_v, dt, running);
    motor_->set_speed(cal_pwm_);
}

void MotorControl::set_speed(int pwm) {
    motor_->set_speed(pwm);
}

void MotorControl::set_speed(float speed_percent) {
    motor_->set_speed(speed_percent);
}

float MotorControl::get_max_speed() {
    return max_v_;
}

void MotorControl::_refresh_config() {
    motor_->set_pins(motorConfig_.motor_AIN1, motorConfig_.motor_AIN2, motorConfig_.motor_pwmPin);
    encoder_->set_pins(motorConfig_.encoder_pinA, motorConfig_.encoder_pinB);

    max_v_ = motorConfig_.revolutions_per_minute * PI * motorConfig_.wheel_diameter / 60;
}