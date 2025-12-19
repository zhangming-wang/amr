#include "masterTask.h"
#include "motionNode.h"
#include "settings.h"
#include "system.h"
#include "ydlidarX2.h"
#include <Arduino.h>

void (*serial_print)(const std::string &) = MotionNode::serial_print;

MasterTask *masterTask = nullptr;
MotionNode *motionNode = nullptr;

void setup() {
    Serial.begin(115200);
    while (!Serial) { // 等待主机连接到 CDC 端口
        delay(50);
    }

    test_ram();

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    masterTask = &MasterTask::instance();
    // YdlidarX2 &ydlidarX2 = YdlidarX2::instance();
    motionNode = &MotionNode::instance();

    masterTask->start_task();
    // ydlidarX2.start_task();
    motionNode->start_task();
}

void loop() {
    monitor_wifi();
}