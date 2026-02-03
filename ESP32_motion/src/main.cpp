#include "motionControlTask.h"
#include "motionNodeTask.h"
#include "sensorsControlTask.h"
#include "settings.h"
#include "system.h"
#include <Arduino.h>

void (*serial_print)(const std::string &) = MotionNodeTask::serial_print;

void setup() {
    Serial.begin(115200);
    delay(500);

    test_ram();

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    auto motionNodeTask = &MotionNodeTask::instance();
    motionNodeTask->start_task();

    auto motionControlTask = &MotionControlTask::instance();
    motionControlTask->start_task();

    auto sensorsControlTask = &SensorsControlTask::instance();
    sensorsControlTask->start_task();
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}