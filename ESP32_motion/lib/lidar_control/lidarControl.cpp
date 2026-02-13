#include "lidarControl.h"

LidarControl::LidarControl() {
}

LidarControl::LidarControl(const std::string &name) {
    name_ = name;
}

void LidarControl::save_config() {
    if (name_.empty()) {
        serial_print("LidarControl name is empty, cannot save config.");
        return;
    }

    preferences_.begin(std::string(name_ + "config").c_str(), false);
    preferences_.clear();
    preferences_.putInt("pinRX", pin_rx_);
    preferences_.putInt("pinTX", pin_tx_);
    preferences_.putInt("pinPWM", pin_pwm_);
    preferences_.end();
}

void LidarControl::load_config() {
    if (name_.empty()) {
        serial_print("LidarControl name is empty, cannot load config.");
        return;
    }
    preferences_.begin(std::string(name_ + "config").c_str(), true); // 只读模式
    auto pin_RX = preferences_.getInt("pinRX", pin_rx_);
    auto pin_TX = preferences_.getInt("pinTX", pin_tx_);
    auto pin_PWM = preferences_.getInt("pinPWM", pin_pwm_);
    preferences_.end();

    set_pins(pin_TX, pin_RX, pin_PWM);
}

void LidarControl::set_pins(int pin_tx, int pin_rx, int pin_pwm) {
    pin_pwm_ = pin_pwm;
    pwmControl_.attachPin(pin_pwm_);

    if (pin_rx_ == pin_rx_ && pin_tx == pin_tx_) {
        serial_print("LidarControl pins not changed, skip reinit.");
        return;
    }

    pin_tx_ = pin_tx;
    pin_rx_ = pin_rx;

    serial_print("LidarControl set pins: tx=" + std::to_string(pin_tx_) + ", rx=" + std::to_string(pin_rx_) + ", pwm=" + std::to_string(pin_pwm_));

    if (Serial2) {
        Serial2.end();
    }
    Serial2.setRxBufferSize(512);
    Serial2.begin(baudrate_, SERIAL_8N1, pin_tx_, pin_rx_);
    delay(500);

    motorOn(1.0f);
}

void LidarControl::get_pins(int &pin_tx, int &pin_rx, int &pin_pwm) {
    pin_tx = pin_tx_;
    pin_rx = pin_rx_;
    pin_pwm = pin_pwm_;
}

void LidarControl::get_data(uint8_t *data, uint8_t &size) {
    size = data_buffer_[ready_buffer_index_].size;
    if (size > 0) {
        memcpy(data, data_buffer_[ready_buffer_index_].data_buffer, data_buffer_[ready_buffer_index_].size);
        data_buffer_[ready_buffer_index_].size = 0;
        data_buffer_[ready_buffer_index_].data_buffer[0] = 0x00;
    }
}

void LidarControl::motorOn(float speed_percent) {
    pwmControl_.write(float(speed_percent));
}

void LidarControl::motorOff() {
    pwmControl_.write(uint32_t(0));
}

void LidarControl::update() {
    while (Serial2.available()) {
        current_data_ = Serial2.read();
        if (current_data_ == 0xaa) {
            is_data_begin_sig_ = true;
        } else if (current_data_ == 0x55) {
            if (is_data_begin_sig_) {
                if (data_buffer_[using_buffer_index_].data_buffer[0] == 0xaa && data_buffer_[using_buffer_index_].data_buffer[1] == 0x55) {
                    data_buffer_[using_buffer_index_].size--;
                    using_buffer_index_ = 1 - using_buffer_index_;
                    ready_buffer_index_ = 1 - ready_buffer_index_;
                }
                data_buffer_[using_buffer_index_].size = 2;
                data_buffer_[using_buffer_index_].data_buffer[0] = 0xaa;
                data_buffer_[using_buffer_index_].data_buffer[1] = 0x55;
                is_data_begin_sig_ = false;
                break;
            }
        } else {
            is_data_begin_sig_ = false;
        }
        data_buffer_[using_buffer_index_].data_buffer[data_buffer_[using_buffer_index_].size++] = current_data_;
    }
}