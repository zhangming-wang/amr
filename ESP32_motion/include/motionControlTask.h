#pragma once

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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Arduino.h>
#include <Preferences.h>
#include <geometry_msgs/msg/quaternion.h>
#include <geometry_msgs/msg/twist.h>
#include <map>
#include <memory>
#include <micro_ros_platformio.h>
#include <time.h>
#include <utility>
#include <vector>

class MotionControlTask : public BaseTaskSingleton<MotionControlTask> {

    friend class Singleton<MotionControlTask>;

    struct WheelSpeed {
        float left_v = 0;
        float right_v = 0;
    };

protected:
    MotionControlTask();
    void init_task() override { brake(); };
    void clean_task() override { brake(); };

public:
    void update() override;

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

    void set_motor_enable_flags(uint8_t flags);
    uint8_t get_motor_enable_flags();

    void set_model_params(float track_width, float wheel_width);

    void set_left_motor_config_params(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute);
    void set_right_motor_config_params(int motor_AIN1, int motor_AIN2, int encoder_pinA, int encoder_pinB, int motor_pwmPin, float wheel_diameter, int pluses_per_revolution, int revolutions_per_minute);

    void set_left_motor_pid_params(float p, float i, float d, float max_total_integral);
    void set_right_motor_pid_params(float p, float i, float d, float max_total_integral);

    void set_speed_plan_parms(float max_v, float max_acc, float jerk);

    void set_milliseconds(int milliseconds);
    int get_milliseconds();

    void set_speed_percent(float percent);
    float get_speed_percent();
    float get_max_speed();

    void set_speed_plan_state(bool enable);

    void get_data(motion_status_msgs__msg__MotionStatus &msg);

    void read_config(motion_settings_service__srv__MotionSettingsService_Response *response);
    void load_config();
    void save_config();

    void read_params(motion_settings_service__srv__MotionSettingsService_Response *response);
    void load_params();
    void save_params();

    void test_motors();

private:
    //---------需要保存配置---------
    float wheel_width_ = 10, track_width_ = 20;

    //---------需要保存参数---------
    volatile int milliseconds_ = 10;

    float max_acc_ = 10, jerk_ = 1;
    float target_max_v_ = 1.0, max_v_ = 1, max_w_ = 1.0, speed_percent_ = 1.0;

    //---------局部内部参数---------
    uint8_t motor_enable_flags_ = 0xff;

    volatile bool running_ = false, enable_speed_plan_ = false;
    volatile float dt_ = 0;

    WheelSpeed current_wheel_v_, target_wheel_v_;
    std::deque<WheelSpeed> wheel_speed_deque_;

    Preferences preferences_;

    SemaphoreHandle_t mutex_; // 互斥量句柄
    TickType_t task_tick_count_;

    std::shared_ptr<MotorControl> left_motor_control_, right_motor_control_;
    std::shared_ptr<SpeedPlan> speedPlan_;

    motion_status_msgs__msg__MotionStatus motion_status_msg_;

    geometry_msgs__msg__Twist _forwardKinematics(const WheelSpeed &wheelSpeed);
    WheelSpeed _inverseKinematics(const geometry_msgs__msg__Twist &twist);

    void _plan_wheel_speed(const WheelSpeed &target_wheel_speed);
};
