#pragma once

#include <cstdint>
#include <deque>
#include <math.h>

struct SpdPlanParams {
    volatile float max_v = 1.0;     // 最大速度 m/s
    volatile float max_acc = 5.0;   // 最大加速度 m/s²
    volatile float jerk = 1.0;      // 最大加 jerk m/s³
    volatile int milliseconds = 20; // 速度规划周期 ms
    volatile bool enable = false;
};

class SpeedPlan {
public:
    SpeedPlan();
    std::deque<float> plan(float current_v, float target_v);
    void set_params(const SpdPlanParams &params);
    void set_params(int milliseconds, float max_v, float max_acc, float jerk, bool enable);
    const SpdPlanParams &get_params();

private:
    SpdPlanParams params_;
    float dt_ = 0.01;

    void _update();
    std::deque<float> _plan_one_way_speed(float current_v, float target_v);
};