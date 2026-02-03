#pragma once

#include <Arduino.h>
#include <cstdint>

class PWMControl {
public:
    PWMControl();
    PWMControl(int pin_pwm, uint8_t resolution_bits = 12, uint32_t requency = 5000);
    ~PWMControl() = default;

    bool attachPin(int pin_pwm);
    bool write(uint32_t pwm);
    bool write(float percent);
    uint32_t get_max_pwm();

private:
    int pin_pwm_ = -1;
    static uint8_t channel_cnt_;
    uint8_t channel_id_ = 0;
    uint8_t resolution_bits_ = 12;
    uint32_t requency_ = 5000;

    void _init();
    bool _write(uint32_t pwm);
};
