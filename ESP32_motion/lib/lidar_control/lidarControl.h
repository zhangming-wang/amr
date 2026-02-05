#pragma once

#include "pwmControl.h"
#include "settings.h"
#include "system.h"
#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <vector>

struct LidarData {
    uint8_t data_buffer[128];
    uint8_t size = 0;
};

class LidarControl {

public:
    LidarControl();
    LidarControl(const std::string &name);
    ~LidarControl() = default;

    void update();

    void set_pins(int pin_tx, int pin_rx, int pin_pwm);
    void get_pins(int &pin_tx, int &pin_rx, int &pin_pwm);

    void motorOn(float speed_percent = 1.0);
    void motorOff();

    void get_data(uint8_t *data, uint8_t &size);

    void save_config();
    void load_config();

private:
    Preferences preferences_;

    std::string name_;
    int pin_pwm_ = -1, pin_tx_ = -1, pin_rx_ = -1;
    unsigned long baudrate_ = ydlidar_baudrate;

    LidarData data_buffer_[2];
    volatile int using_buffer_index_ = 0, ready_buffer_index_ = 1;

    uint8_t current_data_;
    bool is_data_begin_sig_ = false;

    PWMControl pwmControl_;
};