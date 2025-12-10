#include "ydlidarX2.h"

YdlidarX2::YdlidarX2() {}

YdlidarX2::~YdlidarX2() {}

YdlidarX2 &YdlidarX2::get_instance() {
    static YdlidarX2 instance;
    return instance;
}

void YdlidarX2::init(const std::string &host, int port, int pin_pwm, unsigned long baudrate) {
    host_ = host;
    port_ = port;
    pin_pwm_ = pin_pwm;
    baudrate_ = baudrate;

    Serial.begin(baudrate_);
    while (!Serial) { // 等待主机连接到 CDC 端口
        delay(10);
    }
    if (pin_pwm_ > 0) {
        pinMode(pin_pwm_, OUTPUT);
        analogWriteFreq(pwm_freq_);
    }
    motorOn();
}

void YdlidarX2::motorOn(float speed_percent) {
    if (pin_pwm_ > 0) {
        if (speed_percent < 0)
            speed_percent = 0;
        if (speed_percent > 1)
            speed_percent = 1; // 限制在 0~1
        uint32_t duty = uint32_t(pwm_freq_ * speed_percent);
        analogWrite(pin_pwm_, duty);
    }
}

void YdlidarX2::motorOff() {
    if (pin_pwm_ > 0) {
        analogWrite(pin_pwm_, 0);
    }
}

void YdlidarX2::sendData() {
    if (!client_.connected()) {
        auto ret = client_.connect(host_.c_str(), port_);
        if (!ret) {
            Serial.printf("雷达 wifi client 连接失败: %d\n", ret);
            delay(500);
        } else {
            Serial.println("雷达 wifi client 连接成功!");
        }
    } else {
        readData();
    }
}

void YdlidarX2::writeData(uint8_t *buffer, int len) {
    if (pin_rx_ > 0) {
        Serial.write(buffer, len);
    }
}

void YdlidarX2::readData() {
    if (Serial.available()) {
        while (Serial.available()) {
            current_data_ = Serial.read();
            if (current_data_ == 0xaa) {
                is_data_begin_sig_ = true;
            } else if (current_data_ == 0x55) {
                if (is_data_begin_sig_) {
                    data_vector_.pop_back();
                    if (data_vector_.size() > 0) {
                        // Serial.println("----------雷达数据信息-----");
                        // for (auto data : data_vector_) {
                        //     Serial.printf("%x ", data);
                        // }
                        // Serial.println("");
                        if (client_.write(data_vector_.data(), data_vector_.size()) != data_vector_.size()) {
                            // Serial.println("----------雷达数据信息-----");
                            // for (auto data : data_vector_) {
                            //     Serial.printf("%x ", data);
                            // }
                            // Serial.println("");
                            Serial.printf("雷达数据发送失败，总共数据大小:%d\n", data_vector_.size());
                        }
                        data_vector_.clear();
                    }
                    data_vector_.push_back(0xaa);
                    is_data_begin_sig_ = false;
                }
            } else {
                is_data_begin_sig_ = false;
            }

            if (current_data_ == 0xa5) {
                is_power_begin_ = true;
            } else if (current_data_ == 0x5a) {
                if (is_power_begin_) {
                    data_vector_.pop_back();
                    if (data_vector_.size() > 0) {
                        // Serial.println("----------雷达上电信息-----");
                        // for (auto data : data_vector_) {
                        //     Serial.printf("%x ", data);
                        // }
                        // Serial.println("");
                        if (client_.write(data_vector_.data(), data_vector_.size()) != data_vector_.size()) {
                            Serial.printf("雷达上电信息发送失败，总共数据大小:%d\n", data_vector_.size());
                        }
                        data_vector_.clear();
                    }
                    data_vector_.push_back(0xa5);
                    is_power_begin_ = false;
                }
            } else {
                is_power_begin_ = false;
            }
            data_vector_.push_back(current_data_);
        }
    }
}
