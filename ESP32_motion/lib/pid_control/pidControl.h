#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include <cstdint>
#include <math.h>

struct PidParams {
    volatile float p = 1;
    volatile float i = 0;
    volatile float d = 0;
    volatile float max_total_integral = 1000;
};

class PIDControl {
public:
    void reset();
    float calculate(float current_value, float target_value, float dt, bool debug = false);
    void set_params(const PidParams &pidParams);
    void set_params(float p, float i, float d, float max_total_integral);
    const PidParams &get_params();

private:
    PidParams pidParams_;

    volatile float last_error_ = 0;
    volatile float total_integral_ = 0;
};