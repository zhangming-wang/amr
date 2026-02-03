#include "ffControl.h"

void FFControl::set_params(const FFParams &params) {
    params_ = params;
}

void FFControl::set_params(float k, float b) {
    params_.k = k;
    params_.b = b;
}

const FFParams &FFControl::get_params() {
    return params_;
}

float FFControl::calculate(float target_value) {
    return params_.k * target_value + params_.b;
}