#pragma once

#include "pwmControl.h"
#include <Arduino.h>
#include <WiFi.h>
#include <vector>

class YdlidarX2 {
private:
    YdlidarX2();
    ~YdlidarX2();

public:
    YdlidarX2(const YdlidarX2 &) = delete;
    YdlidarX2 &operator=(const YdlidarX2 &) = delete;

    static YdlidarX2 &get_instance();
    void init(const std::string &host, int port, int pin_pwm, int pin_tx, int pin_rx = -1, unsigned long baudrate = 115200);

    void motorOn(float speed_percent = 1.0);
    void motorOff();

    void start_task();
    void stop_task();

    int readData();
    void writeData(uint8_t *buffer, int len);

private:
    int pin_pwm_ = -1, pin_tx_ = -1, pin_rx_ = -1;
    unsigned long baudrate_ = 115200;
    int port_ = 8889;
    std::string host_;
    WiFiClient client_;
    std::vector<uint8_t> data_vector_;

    bool is_power_begin_ = false, is_data_begin_sig_ = false;
    uint8_t current_data_;

    PWMControl pwmControl_;

    volatile bool enable_task_run = false;

    void sendData();
    static void sendDataLoop(void *args);
};