#pragma once

#include "encoder.h"
#include "pidControl.h"
#include "pwmControl.h"
#include <Arduino.h>
#include <ESP32Encoder.h>
#include <cstdint>

class Motor {
public:
    Motor();
    bool init_success();

    void set_pins(int pin_A, int pin_B, int pin_PWM = -1);

    void move();
    void move(float speed_percent); // 速度比例
    void move(int speed_pwm);       // PWM占空比

    void set_speed(float speed_percent); // 速度比例
    void set_speed(int pwm);             // PWM占空比

    void stop();
    void brake();

private:
    bool init_ = false;
    int pin_A_ = -1, pin_B_ = -1, pin_PWM_ = -1;
    // static int channel_cnt_;
    // int channel_id_ = 0;
    volatile uint32_t pwm_ = 0;

    // static const int RESOLUTIONBITS = 12;
    // static const int MINPWM = 0;

    PWMControl pwmControl_;

    void _set_direction(bool forward);
    void _set_pwm(int pwm);
};
