#pragma once

#include <Arduino.h>

inline void test_ram() {
#if defined(ESP32)
    // 使用Arduino框架提供的PSRAM相关函数
    if (ESP.getPsramSize() > 0) {
        Serial.printf("检测到PSRAM，容量: %d KB\n", ESP.getPsramSize() / 1024);
    } else {
        Serial.println("未检测到PSRAM");
    }

    unsigned long flashSize = ESP.getFlashChipSize();
    unsigned long flashSpeed = ESP.getFlashChipSpeed();

    // 转换为更易读的单位（MB）
    float flashSizeMB = flashSize / (1024.0 * 1024.0);

    Serial.printf("Flash 总容量: %.2f MB\n", flashSizeMB);
    Serial.printf("Flash 速度: %lu Hz\n", flashSpeed);
#endif
    // // 额外：获取Flash芯片型号
    // auto flashModel = ESP.getFlashChipMode();
    // Serial.printf("Flash 型号: %s\n", flashModel);
}