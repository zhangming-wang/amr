#pragma once

#include "I2Cdev/I2Cdev.h"
#include "MPU6050/MPU6050_6Axis_MotionApps20.h"
#include "serialPrint.h"
#include <Arduino.h>
#include <Preferences.h>
#include <Wire.h>
#include <iostream>
#include <micro_ros_platformio.h>

class MPU6050Control {
    friend void mpu_read_task(void *args);

public:
    MPU6050Control();
    void init();

    int get_milliseconds();
    void set_milliseconds(int milliseconds);

    void update();
    void set_pins(int pin_SDA, int pin_SCL);
    void set_offset();

    bool isDmpHandle();
    void setDmpHandle(bool isDmpHandle);

    void start_calibration();

    void start_task();
    void stop_task();

    void get_offset(int16_t &xAccelOffset, int16_t &yAccelOffset, int16_t &zAccelOffset, int16_t &xGyroOffset, int16_t &yGyroOffset, int16_t &zGyroOffset);
    void get_motion_data(float &yaw, float &pitch, float &roll, float &gyroX, float &gyroY, float &gyroZ);
    void get_axisY_data(float &pitch, float &gyroY);

private:
    volatile int milliseconds_ = 20;
    int pin_SDA_ = -1, pin_SCL_ = -1;

    bool isDmpHandle_ = true;
    bool init_success_ = false;

    Preferences preferences_;

    // manual
    uint8_t data_[14];
    volatile float temperature_ = 0;
    volatile float axg_ = 0, ayg_ = 0, azg_ = 0;
    volatile float gx_dps_ = 0, gy_dps_ = 0, gz_dps_ = 0;

    // dmp
    volatile float yaw_ = 0, pitch_ = 0, roll_ = 0;
    volatile float gyroX_ = 0, gyroY_ = 0, gyroZ_ = 0;

    float yaw_offset_ = 0, pitch_offset_ = 0, roll_offset_ = 0;
    // float gyroX__offset_ = 0, gyroY_offset_ = 0, gyroZ_offset_ = 0;

    // calibrate value
    int16_t xAccelOffset_ = 0, yAccelOffset_ = 0, zAccelOffset_ = 0;
    int16_t xGyroOffset_ = 0, yGyroOffset_ = 0, zGyroOffset_ = 0;

    unsigned long last_update_time_ = 0;
    const float ALPHA = 0.98;

    MPU6050 mpu_;
    uint8_t fifoBuffer_[64];

    uint16_t packetSize_;
    uint16_t fifoCount_;

    void _loadCalibration();

    bool _manual_init();
    bool _dmp_init();

    void _manual_read();
    void _dmp_read();

    bool enable_task_run = false;
};

void mpu_read_task(void *args);
