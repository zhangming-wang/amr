#include "speedPlan.h"
std::deque<float> SpeedPlan::plan(float current_v, float target_v, float dt) {
    std::deque<float> speed_deque;
    if (current_v * target_v < 0) {
        speed_deque = _plan_one_way_speed(current_v, 0, dt);
        auto deque0 = _plan_one_way_speed(0, target_v, dt);
        speed_deque.insert(speed_deque.end(), std::make_move_iterator(deque0.begin()), std::make_move_iterator(deque0.end()));
    } else {
        speed_deque = _plan_one_way_speed(current_v, target_v, dt);
    }
    return speed_deque;
}

void SpeedPlan::set_maxAcc_and_jerk(float max_acc, float jerk) {
    if (max_acc > 0)
        max_acc_ = max_acc;
    if (jerk > 0)
        jerk_ = jerk;
}

std::deque<float> SpeedPlan::_plan_one_way_speed(float current_v, float target_v, float dt) {
    std::deque<float> speed_deque;

    float diff_v = target_v - current_v;

    if (jerk_ * pow(dt, 2) <= fabs(diff_v)) {
        float t0 = 0, t1 = 0, t2 = 0;
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        float current_acc = 0, next_acc = 0;

        float max_change_v = pow(max_acc_, 2) / jerk_;

        if (max_change_v > fabs(diff_v)) {
            float acc_ = sqrt(abs(diff_v * jerk_));
            t0 = t2 = acc_ / jerk_;
        } else {
            t1 = (abs(diff_v) - max_change_v) / max_acc_;
            t0 = t2 = max_acc_ / jerk_;
        }

        cnt0 = t0 / dt;
        cnt1 = t1 / dt;
        cnt2 = t2 / dt;

        int dir = diff_v < 0 ? -1 : 1;

        for (int i = 0; i < cnt0 - 1; i++) {
            next_acc = current_acc + dir * jerk_ * dt;
            current_v += (current_acc + next_acc) / 2 * dt;
            current_acc = next_acc;
            speed_deque.push_back(current_v);
        }

        if (cnt0 > 0) {
            next_acc = current_acc + dir * jerk_ * (t0 - (cnt0 - 1) * dt);
            current_v += (current_acc + next_acc) / 2 * (t0 - (cnt0 - 1) * dt);
            current_acc = next_acc;
            speed_deque.push_back(current_v);
        }

        for (int i = 0; i < cnt1 - 1; i++) {
            current_v += (current_acc + next_acc) / 2 * dt;
            speed_deque.push_back(current_v);
        }

        if (cnt1 > 0) {
            current_v += (current_acc + next_acc) / 2 * (t1 - (cnt1 - 1) * dt);
            speed_deque.push_back(current_v);
        }

        dir *= -1;
        for (int i = 0; i < cnt2 - 1; i++) {
            next_acc = current_acc + dir * jerk_ * dt;
            current_v += (current_acc + next_acc) / 2 * dt;
            current_acc = next_acc;
            speed_deque.push_back(current_v);
        }
    }

    speed_deque.push_back(target_v);

    return speed_deque;
}