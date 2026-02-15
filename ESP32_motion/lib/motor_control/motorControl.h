#pragma once

#include "encoder.h"
#include "ffControl.h"
#include "motor.h"
#include "pidControl.h"
#include <Preferences.h>
#include <cstdint>
#include <deque>
#include <memory>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

struct MotorConfig {
    int motor_AIN1 = -1;
    int motor_AIN2 = -1;
    int motor_pwmPin = -1;
    int encoder_pinA = -1;
    int encoder_pinB = -1;
    int pluses_per_revolution = 1000;
    int revolutions_per_minute = 100;
    float wheel_diameter = 0.1f;
    uint dead_pwm = 0;
};

class MotorControl {
public:
    MotorControl(const std::string &name = std::string());
    bool init_success();

    void update();

    void move();
    void stop();
    void brake();

    void load_config();
    void save_config();

    void load_params();
    void save_params();

    void set_motor_config(const MotorConfig &motorConfig);
    void set_motor_config(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute, uint dead_pwm = 0);
    const MotorConfig &get_motor_config();

    void set_pid_params(const PidParams &pidParams);
    void set_pid_params(float p, float i, float d, float max_total_integral);
    const PidParams &get_pid_params();

    void set_ff_params(const FFParams &ffParams);
    void set_ff_params(float k, float b);
    const FFParams &get_ff_params();

    void set_speed(int pwm);
    void set_speed(float speed_percent);
    void set_speed(float target_v, float dt, bool running = true);

    void calculate(float target_v, float dt, bool running = true);

    float get_max_speed();

    float get_current_speed();
    float get_current_acc();

    float get_target_speed();
    float get_target_acc();

    float get_dt_distance();
    float get_total_distance();

    long get_encoder_count();
    long get_encoder_count_change();

private:
    //-------------保存参数-------------
    const std::string name_;
    MotorConfig motorConfig_;

    //-------------局部参数-------------
    volatile float current_v_ = 0, target_v_ = 0, current_acc_ = 0, target_acc_ = 0;
    volatile float latest_target_v_ = 0, latest_current_v_ = 0, max_v_ = 0;

    float raw_vel_ = 0, smoothed_v_ = 0, alpha_ = 0.25;
    float pid_value_ = 0, ff_value_ = 0;
    int cal_pwm_ = 0;

    std::shared_ptr<Encoder> encoder_;
    std::shared_ptr<Motor> motor_;
    std::shared_ptr<PIDControl> pidControl_;
    std::shared_ptr<FFControl> ffControl_;

    Preferences preferences_;

    void _refresh_config();
};