#include "pidControl.h"

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

    if (total_integral_ < 0 && total_integral_ < (-1.0f * pidParams_.max_total_integral))
        total_integral_ = -1.0f * pidParams_.max_total_integral;

    output_value = pidParams_.p * current_error + pidParams_.i * total_integral_ + pidParams_.d * (current_error - last_error_) / dt;
    last_error_ = current_error;

    return output_value;
}

void PIDControl::set_params(const PidParams &pidParams) {
    pidParams_ = pidParams;
    reset();
}

void PIDControl::set_params(float p, float i, float d, float max_total_integral) {
    pidParams_.p = p;
    pidParams_.i = i;
    pidParams_.d = d;
    pidParams_.max_total_integral = max_total_integral;
    reset();
}

const PidParams &PIDControl::get_params() {
    return pidParams_;
}