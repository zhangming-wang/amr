#pragma once

#include <ESP32Servo.h>

class PwmServoControl {
public:
    PwmServoControl(int pin_pwm, int periodHertz = 50, int min = 500, int max = 2500);
    ~PwmServoControl();

    void move(int angle);
    const Servo &get_servo();

private:
    Servo servo_;
};
