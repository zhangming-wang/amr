#include "cameraControl.h"
#include "cameraNode.h"
#include "esp_timer.h"
#include "settings.h"
#include "system.h"
#include <Arduino.h>
#include <WiFi.h>

void (*serial_print)(const std::string &) = CameraNode::serial_print;

void setup() {
    Serial.begin(115200);
    while (!Serial) { // 等待主机连接到 CDC 端口
        delay(50);
    }

    test_ram();

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);
    CameraControl &cameraControl = CameraControl::instance();
    cameraControl.init_camera(true);

    CameraNode &cameraNode = CameraNode::instance();
    cameraNode.start_task();
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}