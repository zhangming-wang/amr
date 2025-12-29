#pragma once

#include "I2Cdev/I2Cdev.h"
#include "MPU6050/MPU6050_6Axis_MotionApps20.h"
#include "baseTask.h"
#include "motion_settings_service/srv/motion_settings_service.h"
#include "motion_status_msgs/msg/motion_status.h"
#include "rosidl_runtime_c/string_functions.h"
#include "system.h"
#include <Arduino.h>
#include <Preferences.h>
#include <Wire.h>
#include <atomic>
#include <cstdint>
#include <micro_ros_platformio.h>

class MPU6050Control : public BaseTaskSingleton<MPU6050Control> {

    friend class Singleton<MPU6050Control>;

protected:
    MPU6050Control();
    virtual ~MPU6050Control() = default;

public:
    void update() override;

    void set_pins(int pin_SDA, int pin_SCL);
    void set_offset(int16_t xAccOffset, int16_t yAccOffset, int16_t zAccOffset,
                    int16_t xGyroOffset, int16_t yGyroOffset, int16_t zGyroOffset);

    void start_calibration();

    void get_motion_status(motion_status_msgs__msg__MotionStatus &msg);

    void read_params(motion_settings_service__srv__MotionSettingsService_Response *response);
    void save_params();
    void load_params();

    void read_config(motion_settings_service__srv__MotionSettingsService_Response *response);
    void save_config();
    void load_config();

private:
    int pin_SDA_ = -1, pin_SCL_ = -1;

    bool is_dmp_handle_ = true;
    std::atomic<bool> init_success_{false};
    std::atomic<bool> is_calibrating_{false};

    Preferences preferences_;

    // manual
    uint8_t data_[14];
    volatile float temperature_ = 0;
    volatile float axg_ = 0, ayg_ = 0, azg_ = 0;
    volatile float gx_dps_ = 0, gy_dps_ = 0, gz_dps_ = 0;

    // dmp
    volatile float yaw_ = 0, pitch_ = 0, roll_ = 0;
    volatile float gyroX_ = 0, gyroY_ = 0, gyroZ_ = 0;

    // calibrate value
    int16_t xAccelOffset_ = 0, yAccelOffset_ = 0, zAccelOffset_ = 0;
    int16_t xGyroOffset_ = 0, yGyroOffset_ = 0, zGyroOffset_ = 0;

    unsigned long last_update_time_ = 0;
    const float ALPHA = 0.98;

    MPU6050 mpu_;
    uint8_t fifoBuffer_[64];

    uint16_t packetSize_;
    uint16_t fifoCount_;

    void _start_calibration_task();

    bool _manual_init();
    bool _dmp_init();

    void _manual_read();
    void _dmp_read();
};