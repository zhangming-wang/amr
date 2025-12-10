#pragma once

#include <deque>
#include <iostream>
#include <math.h>

class SpeedPlan {
public:
    std::deque<float> plan(float current_v, float target_v, float dt);
    void set_maxAcc_and_jerk(float max_acc, float jerk);

private:
    volatile float max_acc_ = 5;
    volatile float jerk_ = 1;

    std::deque<float> _plan_one_way_speed(float current_v, float target_v, float dt);
};