#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include <iostream>
#include <math.h>

struct PidParams {
    PidParams() {}
    PidParams(float p, float i, float d, float max_integral) : p(p), i(i), d(d), max_total_integral(max_total_integral) {}
    PidParams(const PidParams &other) {
        p = other.p;
        i = other.i;
        d = other.d;
        max_total_integral = other.max_total_integral;
    }
    PidParams &operator=(const PidParams &other) {
        if (this != &other) {
            p = other.p;
            i = other.i;
            d = other.d;
            max_total_integral = other.max_total_integral;
        }
        return *this;
    }
    volatile float p = 1, i = 0, d = 0, max_total_integral = 1000;
};

class PIDControl {
public:
    PIDControl(const std::string &name = std::string());

    void load();
    void save();
    void reset();

    float calculate(float current_value, float target_value, float dt, bool debug = false);
    void set_pid_params(const PidParams &pidParams);
    void set_pid_params(float p, float i, float d, float max_total_integral);
    PidParams &get_pid_params();

private:
    std::string name_;

    PidParams pidParams_;
    Preferences preferences_;

    volatile float last_error_ = 0;
    volatile float total_integral_ = 0;
};