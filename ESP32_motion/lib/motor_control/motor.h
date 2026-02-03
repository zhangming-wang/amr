#pragma once

#include "encoder.h"
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

    volatile uint32_t pwm_ = 0;
    PWMControl pwmControl_;

    void _set_direction(bool forward);
};
