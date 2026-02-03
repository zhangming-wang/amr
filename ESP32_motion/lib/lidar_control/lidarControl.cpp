#include "lidarControl.h"

LidarControl::LidarControl() {
    baudrate_ = ydlidar_baudrate;
}
LidarControl::LidarControl(const std::string &name) {
    name_ = name;
    baudrate_ = ydlidar_baudrate;
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

    if (Serial2) {
        Serial2.end();
    }
    Serial2.setRxBufferSize(512);
    Serial2.begin(baudrate_, SERIAL_8N1, pin_tx_, pin_rx_);
    delay(500);
}

void LidarControl::get_pins(int &pin_tx, int &pin_rx, int &pin_pwm) {
    pin_tx = pin_tx_;
    pin_rx = pin_rx_;
    pin_pwm = pin_pwm_;
}

void LidarControl::get_data(uint8_t *data) {
    memcpy(data, data_buffer_[current_buffer_index_], buffer_size_);
}

void LidarControl::motorOn(float speed_percent) {
    pwmControl_.write(float(speed_percent));
}

void LidarControl::motorOff() {
    pwmControl_.write(uint32_t(0));
}

void LidarControl::update() {
    static int synce_State = -1;
    if (synce_State == 1) {
        // 已经同步，读取完整数据包
        if (Serial2.available() >= buffer_size_) {
            auto size = Serial2.readBytes(data_buffer_[1 - current_buffer_index_], buffer_size_);
            if (size != buffer_size_) {
                serial_print("LidarControl read data size error, resyncing.");
                synce_State = -1;
            }
        }
    } else if (synce_State == 0) {
        // 已经同步，读取剩余数据
        if (Serial2.available() >= buffer_size_ - 2) {
            auto size = Serial2.readBytes(data_buffer_[1 - current_buffer_index_] + 2, buffer_size_ - 2);
            if (size != buffer_size_ - 2) {
                serial_print("LidarControl read data size error, resyncing.");
                synce_State = -1;
            } else {
                synce_State = 1;
                serial_print("LidarControl data synced.");
            }
        }
    } else {
        // 寻找同步头 0xAA 0x55
        while (Serial2.available() >= 2) {
            if (Serial2.peek() == 0xAA) {
                data_buffer_[1 - current_buffer_index_][0] = Serial2.read(); // 丢弃 0xAA
                if (Serial2.peek() == 0x55) {
                    data_buffer_[1 - current_buffer_index_][1] = Serial2.read(); // 丢弃 0x55
                    synce_State = 0;
                    break;
                }
            } else {
                Serial2.read(); // 丢弃无效数据
            }
        }
    }
    current_buffer_index_ = 1 - current_buffer_index_;
}