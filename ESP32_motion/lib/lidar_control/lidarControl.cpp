#include "lidarControl.h"

LidarControl::LidarControl() {
    baudrate_ = ydlidar_baudrate;
    pin_tx_ = 18;
    pin_rx_ = -1;
    pin_pwm_ = -1;

    pwmControl_.attachPin(pin_pwm_);
    Serial2.begin(baudrate_, SERIAL_8N1, pin_tx_, pin_rx_);
}

void LidarControl::get_data(uint8_t *data) {
    memcpy(data, data_buffer[current_buffer_index_], buffer_size_);
}

void LidarControl::motorOn(float speed_percent) {
    pwmControl_.write(float(speed_percent));
}

void LidarControl::motorOff() {
    pwmControl_.write(uint32_t(0));
}

void LidarControl::update() {
    current_buffer_index_ = 1 - current_buffer_index_;
}