#pragma once

#include <string>

inline std::string constructNodeName(const std::string &ns, const std::string &name) {
    std::string node_name;
    if (ns.empty()) {
        return name;
    } else {
        if (ns.front() != '/') { // 确保命名空间以单斜杠开头
            node_name = "/" + ns;
        } else {
            node_name = ns;
        }
        if (!node_name.empty() && node_name.back() != '/') { // 添加服务名，确保中间只有一个斜杠
            node_name += "/";
        }
        node_name += name;
    }
    return node_name;
}

#if defined(ESP32)

#include <Arduino.h>

inline void test_ram() {
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
    // // 额外：获取Flash芯片型号
    // auto flashModel = ESP.getFlashChipMode();
    // Serial.printf("Flash 型号: %s\n", flashModel);
}
#endif
