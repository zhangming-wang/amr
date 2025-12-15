#pragma once

#include "pwmControl.h"
#include "singleton.h"
#include <Arduino.h>
#include <WiFi.h>
#include <vector>

class YdlidarX2 : public Singleton<YdlidarX2> {

    friend class Singleton<YdlidarX2>;

public:
    YdlidarX2();
    void update() override;

    void motorOn(float speed_percent = 1.0);
    void motorOff();

    int readData();
    void writeData(uint8_t *buffer, int len);

protected:
    void init_task() override;
    void clean_task() override;

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

    void sendData();
};