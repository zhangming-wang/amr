#include "motor.h"

int Motor::channel_cnt_ = 0;

Motor::Motor() {
    init_ = false;
    channel_id_ = channel_cnt_;
    channel_cnt_ += 1;
    ledcSetup(channel_id_, 5000, RESOLUTIONBITS);
}

bool Motor::init_success() {
    return init_;
}

void Motor::set_pins(int pin_A, int pin_B, int pin_PWM) {
    if (pin_A_ != pin_A || pin_B_ != pin_B || pin_PWM_ != pin_PWM) {
        pin_A_ = pin_A;
        pin_B_ = pin_B;
        pin_PWM_ = pin_PWM;

        if (pin_A_ >= 0 && pin_B_ >= 0) {
            pinMode(pin_A_, OUTPUT);
            pinMode(pin_B_, OUTPUT);
            init_ = true;
        } else {
            init_ = false;
        }

        if (init_) {
            if (pin_PWM_ > 0) {
                ledcAttachPin(pin_PWM_, channel_id_);
            }
            stop();
        }
    }
}

void Motor::stop() {
    if (!init_)
        return;

    ledcWrite(channel_id_, 0);
}

void Motor::brake() {
    if (!init_)
        return;

    stop();
    if (pin_PWM_ < 0) {
        ledcDetachPin(pin_A_);
        ledcDetachPin(pin_B_);
    }

    digitalWrite(pin_A_, LOW);
    digitalWrite(pin_B_, LOW);
}

void Motor::set_speed(float speed_percent) {
    if (!init_)
        return;

    if (speed_percent < 0) {
        _set_direction(false);
    } else {
        _set_direction(true);
    }

    speed_percent = fabs(speed_percent);
    if (speed_percent > 1)
        speed_percent = 1;

    _set_pwm(uint(speed_percent * pow(2, RESOLUTIONBITS)));
}

void Motor::set_speed(int pwm) {
    if (!init_)
        return;

    if (pwm < 0) {
        _set_direction(false);
    } else {
        _set_direction(true);
    }
    _set_pwm(fabs(pwm));
}

void Motor::_set_pwm(int pwm) {
    if (pwm > pow(2, RESOLUTIONBITS))
        pwm = pow(2, RESOLUTIONBITS);
    if (pwm < MINPWM && pwm != 0)
        pwm = MINPWM;
    pwm_ = pwm;
}

void Motor::_set_direction(bool forward) {
    if (pin_PWM_ > 0) {
        if (forward) {
            digitalWrite(pin_A_, HIGH);
            digitalWrite(pin_B_, LOW);
        } else {
            digitalWrite(pin_A_, LOW);
            digitalWrite(pin_B_, HIGH);
        }
    } else {
        if (forward) {
            ledcDetachPin(pin_B_);
            digitalWrite(pin_B_, LOW);
            ledcAttachPin(pin_A_, channel_id_);
        } else {
            ledcDetachPin(pin_A_);
            digitalWrite(pin_A_, LOW);
            ledcAttachPin(pin_B_, channel_id_);
        }
    }
}

void Motor::move() {
    if (!init_)
        return;

    ledcWrite(channel_id_, pwm_);
}

void Motor::move(int speed_pwm) {
    if (!init_)
        return;

    set_speed(speed_pwm);
    ledcWrite(channel_id_, pwm_);
}

void Motor::move(float speed_percent) {
    if (!init_)
        return;

    set_speed(speed_percent);
    ledcWrite(channel_id_, pwm_);
}