#include "pwmServoControl.h"

PwmServoControl::PwmServoControl(int pin_pwm, int periodHertz, int min, int max) {
    servo_.setPeriodHertz(periodHertz);
    servo_.attach(pin_pwm, min, max);
}
PwmServoControl::~PwmServoControl() {}

void PwmServoControl::move(int angle) {
    if (!servo_.attached()) { // ESP32Servo 有 attached() 方法
        Serial.println("ERROR: Servo not attached, cannot move!");
        return;
    }
    servo_.write(angle);
}
const Servo &PwmServoControl::get_servo() {
    return servo_;
}