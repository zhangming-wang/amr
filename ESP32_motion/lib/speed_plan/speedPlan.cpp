#include "speedPlan.h"

SpeedPlan::SpeedPlan() {
    _update();
}

void SpeedPlan::set_params(const SpdPlanParams &params) {
    params_ = params;
    _update();
}

void SpeedPlan::set_params(int milliseconds, float max_v, float max_w, float max_acc, float jerk, bool enable) {
    params_.milliseconds = milliseconds;
    params_.max_v = max_v;
    params_.max_w = max_w;
    params_.max_acc = max_acc;
    params_.jerk = jerk;
    params_.enable = enable;
    _update();
}

const SpdPlanParams &SpeedPlan::get_params() {
    return params_;
}

void SpeedPlan::_update() {
    if (params_.milliseconds <= 0)
        params_.milliseconds = 10;

    dt_ = params_.milliseconds / 1000.0f;
}

std::deque<float> SpeedPlan::plan(float current_v, float target_v) {
    std::deque<float> speed_deque;

    if (params_.enable) {
        if (current_v * target_v < 0) {
            speed_deque = _plan_one_way_speed(current_v, 0);
            auto deque0 = _plan_one_way_speed(0, target_v);
            speed_deque.insert(speed_deque.end(), std::make_move_iterator(deque0.begin()), std::make_move_iterator(deque0.end()));
        } else {
            speed_deque = _plan_one_way_speed(current_v, target_v);
        }
    } else {
        speed_deque.push_back(target_v);
    }
    return speed_deque;
}

std::deque<float> SpeedPlan::_plan_one_way_speed(float current_v, float target_v) {
    std::deque<float> speed_deque;

    float diff_v = target_v - current_v;

    if (params_.jerk * pow(dt_, 2) <= fabs(diff_v)) {
        float t0 = 0, t1 = 0, t2 = 0;
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        float current_acc = 0, next_acc = 0;

        float max_change_v = pow(params_.max_acc, 2) / params_.jerk;

        if (max_change_v > fabs(diff_v)) {
            float acc_ = sqrt(abs(diff_v * params_.jerk));
            t0 = t2 = acc_ / params_.jerk;
        } else {
            t1 = (abs(diff_v) - max_change_v) / params_.max_acc;
            t0 = t2 = params_.max_acc / params_.jerk;
        }

        cnt0 = t0 / dt_;
        cnt1 = t1 / dt_;
        cnt2 = t2 / dt_;

        int dir = diff_v < 0 ? -1 : 1;

        for (int i = 0; i < cnt0 - 1; i++) {
            next_acc = current_acc + dir * params_.jerk * dt_;
            current_v += (current_acc + next_acc) / 2 * dt_;
            current_acc = next_acc;
            speed_deque.push_back(current_v);
        }

        if (cnt0 > 0) {
            next_acc = current_acc + dir * params_.jerk * (t0 - (cnt0 - 1) * dt_);
            current_v += (current_acc + next_acc) / 2 * (t0 - (cnt0 - 1) * dt_);
            current_acc = next_acc;
            speed_deque.push_back(current_v);
        }

        for (int i = 0; i < cnt1 - 1; i++) {
            current_v += (current_acc + next_acc) / 2 * dt_;
            speed_deque.push_back(current_v);
        }

        if (cnt1 > 0) {
            current_v += (current_acc + next_acc) / 2 * (t1 - (cnt1 - 1) * dt_);
            speed_deque.push_back(current_v);
        }

        dir *= -1;
        for (int i = 0; i < cnt2 - 1; i++) {
            next_acc = current_acc + dir * params_.jerk * dt_;
            current_v += (current_acc + next_acc) / 2 * dt_;
            current_acc = next_acc;
            speed_deque.push_back(current_v);
        }
    }

    speed_deque.push_back(target_v);

    return speed_deque;
}