#include "lidarTask.h"
#include "motionNode.h"
#include "motionTask.h"
#include "settings.h"
#include "system.h"
#include <Arduino.h>

void (*serial_print)(const std::string &) = MotionNode::serial_print;

MotionTask *motionTask = nullptr;
MotionNode *motionNode = nullptr;
LidarTask *lidarTask = nullptr;

void setup() {
    Serial.begin(115200);
    while (!Serial) { // 等待主机连接到 CDC 端口
        delay(50);
    }

    test_ram();

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    motionNode = &MotionNode::instance();
    motionNode->start_task();

    motionTask = &MotionTask::instance();
    motionTask->start_task();

    lidarTask = &LidarTask::instance();
    lidarTask->start_task();
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}