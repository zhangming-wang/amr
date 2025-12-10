

#include "encoder.h"

Encoder::Encoder() {
}

bool Encoder::init_success() {
    return init_;
}

void Encoder::set_pins(int pin_A, int pin_B) {
    if (pin_A_ != pin_A || pin_B_ != pin_B) {
        pin_A_ = pin_A;
        pin_B_ = pin_B;

        if (pin_A_ >= 0 && pin_B_ >= 0) {
            init_ = true;
            if (encoder_.isAttached()) {
                encoder_.detach();
            }
            encoder_.attachFullQuad(pin_A, pin_B);
        } else {
            init_ = false;
        }
    }
}

void Encoder::reset() {
    if (!init_)
        return;

    encoder_.clearCount();
}

void Encoder::update(float dt) {
    if (!init_)
        return;

    count_ = encoder_.getCount() / 4;
    count_change_ = count_ - last_count_;
    last_count_ = count_;
}

long Encoder::get_count() {
    return count_;
}

long Encoder::get_count_change() {
    return count_change_;
}