#pragma once

#include "esp_timer.h"
#include "micro_ros_utilities/string_utilities.h"
#include "motorControl.h"
#include "nav_msgs/msg/odometry.h"
#include "rosidl_runtime_c/string_functions.h"
#include "speedPlan.h"
extern "C" {
#include "motion_settings_service/srv/motion_settings_service.h"
#include "motion_status_msgs/msg/motion_status.h"
}
#include "baseTask.h"
#include "enum.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include <Arduino.h>
#include <Preferences.h>
#include <deque>
#include <geometry_msgs/msg/quaternion.h>
#include <geometry_msgs/msg/twist.h>
#include <map>
#include <memory>
#include <micro_ros_platformio.h>
#include <time.h>
#include <utility>
#include <vector>

struct WheelSpeed {
    float left_front_v = 0;
    float left_back_v = 0;
    float right_front_v = 0;
    float right_back_v = 0;
};

class MotionControl : public BaseTaskSingleton<MotionControl> {

    friend class Singleton<MotionControl>;

protected:
    MotionControl();
    void init_task() override { brake(); };
    void clean_task() override { brake(); };

public:
    void update() override;

    void move(float dt);
    void stop_move();
    void brake();

    void move_front();
    void move_back();
    void move_left();
    void move_right();
    void move_left_front();
    void move_right_front();
    void move_left_back();
    void move_right_back();
    void turn_left();
    void turn_right();

    void set_twist(const geometry_msgs__msg__Twist &twist);
    void set_wheels_speed(const WheelSpeed &target_wheel_speed);

    void update_target_max_speed();

    void get_motion_status(motion_status_msgs__msg__MotionStatus &msg);

    void set_motor_enable_flags(uint8_t flags);
    uint8_t get_motor_enable_flags();

    void set_model_params(float track_width, float wheel_width);

    void set_left_front_motor_config_params(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute);
    void set_left_back_motor_config_params(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute);
    void set_right_front_motor_config_params(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute);
    void set_right_back_motor_config_params(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute);

    void set_left_front_motor_pid_params(float p, float i, float d, float max_total_integral);
    void set_left_back_motor_pid_params(float p, float i, float d, float max_total_integral);
    void set_right_front_motor_pid_params(float p, float i, float d, float max_total_integral);
    void set_right_back_motor_pid_params(float p, float i, float d, float max_total_integral);

    void set_speed_plan_parms(float max_v, float max_acc, float jerk);

    void set_milliseconds(int milliseconds);
    int get_milliseconds();

    void set_wheel_type(bool is_mecanum_wheel);

    void set_speed_percent(float percent);
    float get_speed_percent();
    float get_max_speed();

    void set_speed_plan_state(bool enable);

    void read_config(motion_settings_service__srv__MotionSettingsService_Response *response);
    void save_config();

    void read_params(motion_settings_service__srv__MotionSettingsService_Response *response);
    void save_params();

    void test_motors();

private:
    //---------需要保存配置---------
    float track_width_ = 10, wheel_width_ = 10;

    //---------需要保存参数---------
    volatile int milliseconds_ = 10;

    bool is_mecanum_wheel_ = false;

    float max_acc_ = 10, jerk_ = 1;
    float target_max_v_ = 1.0, max_v_ = 1, max_w_ = 1.0, speed_percent_ = 1.0;

    //---------局部内部参数---------
    uint8_t motor_enable_flags_ = 0xff;

    volatile bool running_ = false, enable_speed_plan_ = false;

    WheelSpeed current_wheel_v_, target_wheel_v_;
    std::deque<WheelSpeed> wheel_speed_deque_;

    Preferences preferences_;

    SemaphoreHandle_t mutex_; // 互斥量句柄

    std::shared_ptr<MotorControl> left_front_motor_control_, left_back_motor_control_, right_front_motor_control_, right_back_motor_control_;
    std::shared_ptr<SpeedPlan> speedPlan_;

    motion_status_msgs__msg__MotionStatus motion_status_msg_;

    float left_pid_value_ = 0, right_pid_value_ = 0;

    geometry_msgs__msg__Twist _forwardKinematics(const WheelSpeed &wheelSpeed);
    WheelSpeed _inverseKinematics(const geometry_msgs__msg__Twist &twist);

    void _load_params();
    void _load_config();

    void _plan_wheel_speed(const WheelSpeed &target_wheel_speed);
};
