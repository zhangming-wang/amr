#pragma once

#include "baseTask.h"
#include "pwmControl.h"
#include "settings.h"
#include "system.h"
#include <Arduino.h>
#include <WiFi.h>
#include <vector>

class YdlidarX2 : public BaseTaskSingleton<YdlidarX2> {

    friend class Singleton<YdlidarX2>;

protected:
    YdlidarX2();
    void init_task() override;
    void clean_task() override;

    void motorOn(float speed_percent = 1.0);
    void motorOff();

    int readData();
    void writeData(uint8_t *buffer, int len);

public:
    void update() override;

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