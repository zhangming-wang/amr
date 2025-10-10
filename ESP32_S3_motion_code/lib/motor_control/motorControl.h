#pragma once

#include "encoder.h"
#include "motor.h"
#include "pidControl.h"
#include <Preferences.h>
#include <deque>
#include <iostream>
#include <memory>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

struct MotorParams {
    MotorParams() {}
    MotorParams(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute)
        : motor_AIN1(motor_AIN1), motor_AIN2(motor_AIN2), motor_pwmPin(motor_pwmPin), encoder_pinA(encoder_pinA), encoder_pinB(encoder_pinB), wheel_diameter(wheel_diameter),
          pluses_per_revolution(pluses_per_revolution), revolutions_per_minute(revolutions_per_minute) {}
    MotorParams(const MotorParams &other) {
        motor_AIN1 = other.motor_AIN1;
        motor_AIN2 = other.motor_AIN2;
        motor_pwmPin = other.motor_pwmPin;
        encoder_pinA = other.encoder_pinA;
        encoder_pinB = other.encoder_pinB;
        wheel_diameter = other.wheel_diameter;
        pluses_per_revolution = other.pluses_per_revolution;
        revolutions_per_minute = other.revolutions_per_minute;
    }
    MotorParams &operator=(const MotorParams &other) {
        if (this != &other) {
            motor_AIN1 = other.motor_AIN1;
            motor_AIN2 = other.motor_AIN2;
            motor_pwmPin = other.motor_pwmPin;
            encoder_pinA = other.encoder_pinA;
            encoder_pinB = other.encoder_pinB;
            wheel_diameter = other.wheel_diameter;
            pluses_per_revolution = other.pluses_per_revolution;
            revolutions_per_minute = other.revolutions_per_minute;
        }
        return *this;
    }
    int motor_AIN1 = -1, motor_AIN2 = -1, motor_pwmPin = -1;
    int encoder_pinA = -1, encoder_pinB = -1;
    float wheel_diameter = 0;
    int pluses_per_revolution = 0, revolutions_per_minute = 0;
};

class MotorControl {
public:
    MotorControl(const std::string &name = std::string());
    bool init_success();

    void update(float dt);
    void reset();

    void move();
    void stop();
    void brake();

    void set_motor_params(const MotorParams &motorParams);
    void set_motor_params(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute);
    const MotorParams &get_motor_params();
    void save_motor_params();
    void load_motor_params();

    void set_pid_params(const PidParams &pidParams);
    void set_pid_params(float p, float i, float d, float max_total_integral);
    const PidParams &get_pid_params();
    void save_pid_params();
    void load_pid_params();

    void set_speed(float speed, float dt, bool pid_adjust = false);

    float get_max_speed();

    float get_current_speed();
    float get_current_acc();

    float get_target_speed();
    float get_target_acc();

    float get_distance_change();
    long get_encoder_count();

private:
    //-------------保存参数-------------
    const std::string name_;
    MotorParams motorParams_;

    //-------------局部参数-------------
    volatile float current_v_ = 0, target_v_ = 0, current_acc_ = 0, target_acc_ = 0;
    volatile float latest_target_v_ = 0, latest_current_v_ = 0, max_v_ = 0;

    float pid_value_ = 0;

    std::shared_ptr<Encoder> encoder_;
    std::shared_ptr<Motor> motor_;
    std::shared_ptr<PIDControl> pidControl_;

    Preferences preferences_;

    void _set_pins_params();
    void _update_max_v();
};