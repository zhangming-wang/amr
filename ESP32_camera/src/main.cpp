#include "cameraControl.h"
#include "cameraNode.h"
#include "esp_timer.h"
#include "masterTask.h"
#include "settings.h"
#include "system.h"
#include <Arduino.h>

void (*serial_print)(const std::string &) = CameraNode::serial_print;

void setup() {
    Serial.begin(115200);
    while (!Serial) { // 等待主机连接到 CDC 端口
        delay(50);
    }

    test_ram();

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    CameraNode &cameraNode = CameraNode::instance();
    MasterTask &masterTask = MasterTask::instance();

    cameraNode.start_task();
    masterTask.start_task();
}

void loop() {
    monitor_wifi();
}