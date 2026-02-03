#include "pwmControl.h"

uint8_t PWMControl::channel_cnt_ = 0;

PWMControl::PWMControl() {
    _init();
}

PWMControl::PWMControl(int pin_pwm, uint8_t resolution_bits, uint32_t frequency) {
    requency_ = frequency;
    resolution_bits_ = resolution_bits;
    _init();
    attachPin(pin_pwm);
}

uint32_t PWMControl::get_max_pwm() {
    return pow(2, resolution_bits_);
}

void PWMControl::_init() {
    channel_id_ = channel_cnt_;
    channel_cnt_ += 1;
    ledcSetup(channel_id_, requency_, resolution_bits_);
}

bool PWMControl::attachPin(int pin_pwm) {
    if (pin_pwm >= 0) {
        if (pin_pwm_ >= 0) {
            ledcDetachPin(pin_pwm_);
        }
        pin_pwm_ = pin_pwm;
        ledcAttachPin(pin_pwm_, channel_id_);
        return true;
    } else {
        return false;
    }
}

bool PWMControl::write(uint32_t pwm) {
    return _write(pwm);
}

bool PWMControl::write(float percent) {
    uint32_t pwm = fabs(percent * pow(2, resolution_bits_));
    return _write(pwm);
}

bool PWMControl::_write(uint32_t pwm) {
    if (pin_pwm_ >= 0) {
        ledcWrite(channel_id_, std::min(pwm, uint32_t(pow(2, resolution_bits_))));
        return true;
    } else {
        return false;
    }
}
