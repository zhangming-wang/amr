#include "bluetoothSlave.h"

BluetoothSlave &BluetoothSlave::get_instance() {
    static BluetoothSlave instance; // C++11 保证线程安全初始化
    return instance;
}

BluetoothSlave::BluetoothSlave() {
    SerialBT_ = std::make_shared<BluetoothSerial>();
    if (SerialBT_ == nullptr) {
        Serial.println("BluetoothSerial 创建失败！");
    } else {
        Serial.println("BluetoothSerial 创建成功！");
    }
}
BluetoothSlave::~BluetoothSlave() {}

void BluetoothSlave::init(const std::string &name) {
    if (SerialBT_) {
        SerialBT_->begin(String(name.c_str()));
        Serial.println("蓝牙已启动，等待连接...");
    }
}

void BluetoothSlave::start_task() {
    if (enable_task_run == false) {
        enable_task_run = true;
        xTaskCreatePinnedToCore(bluetooth_slave_loop, "bluetooth_slave_loop", 8192, this, 0, NULL, 0);
    }
}

void BluetoothSlave::stop_task() {
    if (enable_task_run) {
        enable_task_run = false;
    }
}

void BluetoothSlave::read_cmd() {
    if (SerialBT_->available()) {
        String cmd = SerialBT_->readStringUntil('\n');
        SerialBT_->flush(); // 清空缓冲区
        cmd.trim();         // 去除空格/换行 读取单个指令字符
        Serial.print("收到控制指令：");
        Serial.println(cmd);
    }
}

void bluetooth_slave_loop(void *args) {
    BluetoothSlave *bluetoothSlave = static_cast<BluetoothSlave *>(args);
    while (bluetoothSlave->enable_task_run) {
        if (bluetoothSlave->SerialBT_->connected()) {
            if (bluetoothSlave->is_connected == false) {
                bluetoothSlave->is_connected = true;
                Serial.println("蓝牙设备已连接");
            }
            bluetoothSlave->read_cmd();
            vTaskDelay(pdMS_TO_TICKS(10));
        } else {
            if (bluetoothSlave->is_connected == true) {
                bluetoothSlave->is_connected = false;
                Serial.println("蓝牙设备已断开连接");
            }
            vTaskDelay(pdMS_TO_TICKS(500)); // 等待500ms再检查连接状态
        }
    }
    vTaskDelete(NULL);
}