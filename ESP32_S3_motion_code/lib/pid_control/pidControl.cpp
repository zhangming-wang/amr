#include "pidControl.h"

PIDControl::PIDControl(const std::string &name) {
    name_ = name;
}

void PIDControl::save() {
    if (!name_.empty()) {
        preferences_.begin(name_.c_str(), false);
        preferences_.clear();
        preferences_.putFloat("p", pidParams_.p);
        preferences_.putFloat("i", pidParams_.i);
        preferences_.putFloat("d", pidParams_.d);
        preferences_.putFloat("maxI", pidParams_.max_total_integral);
        preferences_.end();
    }
}

void PIDControl::load() {
    if (!name_.empty()) {
        preferences_.begin(name_.c_str(), true); // 只读模式
        pidParams_.p = preferences_.getFloat("p", pidParams_.p);
        pidParams_.i = preferences_.getFloat("i", pidParams_.i);
        pidParams_.d = preferences_.getFloat("d", pidParams_.d);
        pidParams_.max_total_integral = preferences_.getFloat("maxI", pidParams_.max_total_integral);
        preferences_.end();
    }
    reset();
}

void PIDControl::reset() {
    last_error_ = 0;
    total_integral_ = 0;
}

float PIDControl::calculate(float current_value, float target_value, float dt, bool debug) {
    float current_error = target_value - current_value;
    float output_value = 0;

    total_integral_ += current_error * dt;

    if (total_integral_ > 0 && total_integral_ > pidParams_.max_total_integral)
        total_integral_ = pidParams_.max_total_integral;

    if (total_integral_ < 0 && total_integral_ < (-1.0 * pidParams_.max_total_integral))
        total_integral_ = -1.0 * pidParams_.max_total_integral;

    output_value = pidParams_.p * current_error + pidParams_.i * total_integral_ + pidParams_.d * (current_error - last_error_) / dt;
    last_error_ = current_error;

    return output_value;
}

void PIDControl::set_pid_params(const PidParams &pidParams) {
    pidParams_ = pidParams;
    reset();
}

void PIDControl::set_pid_params(float p, float i, float d, float max_total_integral) {
    pidParams_.p = p;
    pidParams_.i = i;
    pidParams_.d = d;
    pidParams_.max_total_integral = max_total_integral;
    reset();
}

PidParams &PIDControl::get_pid_params() {
    return pidParams_;
}