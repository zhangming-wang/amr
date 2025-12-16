#include "ydlidarX2.h"

YdlidarX2::YdlidarX2() {
    task_name_ = "ydlidar_x2_task";
    core_id_ = 0;
    priority_ = 3;
    host_ = wifi_IP;
    port_ = ydlidar_tcp_client_port;
    pin_pwm_ = 14;
    pin_tx_ = 25;
    pin_rx_ = -1;
    baudrate_ = ydlidar_baudrate;
}

void YdlidarX2::update() {
    if (!client_.connected()) {
        auto ret = client_.connect(host_.c_str(), port_);
        if (!ret) {
            serial_print("雷达 wifi client 连接失败!");
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            serial_print("雷达 wifi client 连接成功!");
        }
    } else {
        sendData();
    }
}

void YdlidarX2::init_task() {
    pwmControl_.attachPin(pin_pwm_);
    motorOn();
    Serial2.begin(baudrate_, SERIAL_8N1, pin_tx_, pin_rx_);
}

void YdlidarX2::clean_task() {
    motorOff();
    Serial2.end();
}

void YdlidarX2::motorOn(float speed_percent) {
    pwmControl_.write(float(speed_percent));
}

void YdlidarX2::motorOff() {
    pwmControl_.write(uint32_t(0));
}

int YdlidarX2::readData() {
    if (Serial2.available()) {
        return Serial2.read();
    } else {
        return 0;
    }
}

void YdlidarX2::writeData(uint8_t *buffer, int len) {
    if (pin_rx_ > 0) {
        Serial2.write(buffer, len);
    }
}

void YdlidarX2::sendData() {
    if (Serial2.available()) {
        while (Serial2.available()) {
            current_data_ = Serial2.read();
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
                        // else {
                        //     Serial.printf("时间: %d\n", millis() - current_time_);
                        //     current_time_ = millis();
                        //     Serial.printf("大小:%d\n", data_vector_.data());
                        // }
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