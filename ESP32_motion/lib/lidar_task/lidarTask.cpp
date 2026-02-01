#include "lidarTask.h"

LidarTask::LidarTask() {
    this->task_name_ = "lidar_task";
    this->core_id_ = 0;
    this->priority_ = 9;
    this->stack_size_ = 8192;

    baudrate_ = ydlidar_baudrate;
    port_ = ydlidar_tcp_client_port;
    pin_tx_ = 18;
    pin_rx_ = -1;
    pin_pwm_ = -1;

    pwmControl_.attachPin(pin_pwm_);
    Serial2.begin(baudrate_, SERIAL_8N1, pin_tx_, pin_rx_);
}

void LidarTask::motorOn(float speed_percent) {
    pwmControl_.write(float(speed_percent));
}

void LidarTask::motorOff() {
    pwmControl_.write(uint32_t(0));
}

void LidarTask::update() {
    if (!client_.connected()) {
        auto ret = client_.connect(host_.c_str(), port_);
        if (!ret) {
            Serial.println("雷达 wifi client 连接失败!");
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            Serial.println("雷达 wifi client 连接成功!");
        }
    } else {
        sendData();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void LidarTask::sendData() {
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