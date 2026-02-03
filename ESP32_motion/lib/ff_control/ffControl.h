#pragma once

#include <Arduino.h>

struct FFParams {
    volatile float k = 1.0f;
    volatile float b = 0.0f;
};

class FFControl {
public:
    float calculate(float target_value);
    void set_params(const FFParams &params);
    void set_params(float k, float b);
    const FFParams &get_params();

private:
    FFParams params_;
};