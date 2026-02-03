#pragma once

#include "pwmControl.h"
#include "settings.h"
#include <Arduino.h>
#include <WiFi.h>
#include <vector>

class LidarControl {

public:
    LidarControl();
    ~LidarControl() = default;

    void update();

    void set_pins(int pin_tx, int pin_rx, int pin_pwm);

    void motorOn(float speed_percent = 1.0);
    void motorOff();

    void get_data(uint8_t *data);

    void save_config();
    void load_config();

    void save_params();
    void load_params();

private:
    int pin_pwm_ = -1, pin_tx_ = -1, pin_rx_ = -1;
    unsigned long baudrate_ = 115200;

    uint8_t data_buffer_[2][ydlidar_data_size];
    const int buffer_size_ = ydlidar_data_size;
    volatile int current_buffer_index_ = 0;
    PWMControl pwmControl_;
};