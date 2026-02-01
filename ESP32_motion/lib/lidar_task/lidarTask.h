#pragma once

#include "baseTask.h"
#include "pwmControl.h"
#include "settings.h"
#include <Arduino.h>
#include <WiFi.h>
#include <vector>

class LidarTask : public BaseTaskSingleton<LidarTask> {

    friend class Singleton<LidarTask>;

protected:
    LidarTask();
    void update() override;

    void motorOn(float speed_percent = 1.0);
    void motorOff();

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