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
#include "enum.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "mpu6050Control.h"
#include <Arduino.h>
#include <Preferences.h>
#include <deque>
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

struct EulerPose {
    float x = 0;
    float y = 0;
    float z = 0;
    float roll = 0;
    float pitch = 0;
    float yaw = 0;
};

class MotionControl {

private:
    MotionControl();
    ~MotionControl();

public:
    static MotionControl &get_instance();

    MotionControl(const MotionControl &) = delete;
    MotionControl &operator=(const MotionControl &) = delete;

    void init();
    void move();
    void update(float dt);

    void start_move(WheelSpeed &target_wheel_speed);
    void start_move(const geometry_msgs__msg__Twist &twist);
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

    void move_absolute_euler_pose(const EulerPose &eulerPose);
    void move_relative_euler_pose(const EulerPose &eulerPose);

    void update_target_max_speed();

    void calculate();
    nav_msgs__msg__Odometry &get_odom_msg();
    motion_status_msgs__msg__MotionStatus &get_motion_status_msg();

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

    void set_position_pid_params(float p, float i, float d, float max_total_integral);
    void set_line_speed_pid_params(float p, float i, float d, float max_total_integral);
    void set_angle_speed_pid_params(float p, float i, float d, float max_total_integral);

    void set_speed_plan_parms(float max_v, float max_acc, float jerk);

    void set_milliseconds(int milliseconds);
    int get_milliseconds();

    void set_loop_period_cnt(int position_loop_period_cnt, int speed_loop_period_cnt_);

    void set_wheel_type(bool is_mecanum_wheel);

    void set_speed_percent(float percent);
    float get_speed_percent();
    float get_max_speed();

    void set_speed_plan_state(bool enable);

    void read_config(motion_settings_service__srv__MotionSettingsService_Response *response);
    void save_config();

    void read_params(motion_settings_service__srv__MotionSettingsService_Response *response);
    void save_params();

private:
    //---------需要保存配置---------
    float track_width_ = 10, wheel_width_ = 0;

    //---------需要保存参数---------
    volatile int milliseconds_ = 10, position_loop_period_cnt_ = 2, speed_loop_period_cnt_ = 5;
    bool is_mecanum_wheel_ = false;

    float max_acc_ = 10, jerk_ = 1;
    float target_max_v_ = 0, max_v_ = 1, max_w_ = 0, speed_percent_ = 0;

    //---------局部内部参数---------
    uint8_t motor_enable_flags_ = 0xff;

    int period_cnt_ = 0;
    volatile bool running_ = false, enable_speed_plan_ = false;

    float dt_ = 0, position_loop_dt_ = 0, speed_loop_dt_ = 0;

    EulerPose current_euler_pose_, target_euler_pose_;

    WheelSpeed current_wheel_v_, target_wheel_v_;
    geometry_msgs__msg__Twist last_twist_, current_twist_, target_twist_;

    std::deque<WheelSpeed> wheel_speed_deque_;

    Preferences preferences_;

    std::shared_ptr<MotorControl> left_front_motor_control_, left_back_motor_control_, right_front_motor_control_, right_back_motor_control_;
    std::shared_ptr<PIDControl> position_loop_, line_speed_loop_, angle_speed_loop_;
    std::shared_ptr<SpeedPlan> speedPlan_;

    motion_status_msgs__msg__MotionStatus motion_status_msg_;
    nav_msgs__msg__Odometry odom_msg_;

    geometry_msgs__msg__Twist _forwardKinematics(const WheelSpeed &wheelSpeed);
    WheelSpeed _inverseKinematics(const geometry_msgs__msg__Twist &twist);

    void _load_params();
    void _load_config();

    void _plan_wheel_speed(); // WheelSpeed &target_wheel_speed

    // void reset();
};
