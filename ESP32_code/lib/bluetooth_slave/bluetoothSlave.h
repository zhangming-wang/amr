#pragma once

#include "BluetoothSerial.h"
#include <Arduino.h>
#include <memory>
#include <string>

class BluetoothSlave {
    friend void bluetooth_slave_loop(void *args);

private:
    BluetoothSlave();
    ~BluetoothSlave();

public:
    BluetoothSlave(const BluetoothSlave &) = delete;
    BluetoothSlave &operator=(const BluetoothSlave &) = delete;

    static BluetoothSlave &get_instance();
    void init(const std::string &name);
    void start_task();
    void stop_task();

private:
    std::shared_ptr<BluetoothSerial> SerialBT_;
    bool enable_task_run = false;
    bool is_connected = false;

    void read_cmd();
};

void bluetooth_slave_loop(void *args);