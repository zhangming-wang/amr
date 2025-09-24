#pragma once

#include "serial_print.h"
#include <Arduino.h>
#include <ESP32Encoder.h>

class Encoder {

public:
    Encoder();
    void set_pins(int pin_A, int pin_B);
    void update(float dt);
    void reset();

    bool init_success();

    long get_count();
    long get_count_change();

private:
    bool init_ = false;
    int pin_A_ = -1, pin_B_ = -1;
    volatile long count_ = 0, last_count_ = 0, count_change_ = 0;
    ESP32Encoder encoder_;
};