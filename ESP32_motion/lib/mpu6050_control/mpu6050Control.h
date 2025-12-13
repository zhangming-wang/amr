#pragma once

#include "I2Cdev/I2Cdev.h"
#include "MPU6050/MPU6050_6Axis_MotionApps20.h"
#include "system.h"
#include <Arduino.h>
#include <Preferences.h>
#include <Wire.h>
#include <iostream>
#include <micro_ros_platformio.h>
#include <sensor_msgs/msg/imu.h>

class MotionControlNode {
public:
    void publishImu(const Mpu6050Control &imu);

private:
    sensor_msgs::msg::Imu imu_msg_;
};
class MPU6050Control {

private:
    MPU6050Control();
    ~MPU6050Control();

public:
    MPU6050Control(const MPU6050Control &) = delete;
    MPU6050Control &operator=(const MPU6050Control &) = delete;

    static MPU6050Control &get_instance();
    void init(bool eanble_dmp = true);

    void set_pins(int pin_SDA, int pin_SCL);

    bool isDmpHandle();

    void start_calibration();

    void get_motion_data(float &yaw, float &pitch, float &roll, float &gyroX, float &gyroY, float &gyroZ);
    void get_axisY_data(float &pitch, float &gyroY);

    void update();
    void calculate();
    sensor_msgs__msg__Imu *get_imu_msg();

private:
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

    // calibrate value
    int16_t xAccelOffset_ = 0, yAccelOffset_ = 0, zAccelOffset_ = 0;
    int16_t xGyroOffset_ = 0, yGyroOffset_ = 0, zGyroOffset_ = 0;

    unsigned long last_update_time_ = 0;
    const float ALPHA = 0.98;

    MPU6050 mpu_;
    uint8_t fifoBuffer_[64];

    uint16_t packetSize_;
    uint16_t fifoCount_;

    sensor_msgs__msg__Imu imu_msg_;

    void _loadCalibration();

    bool _manual_init();
    bool _dmp_init();

    void _manual_read();
    void _dmp_read();
};