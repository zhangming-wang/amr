#pragma once

#include "settings.h"
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

#if defined(ARDUINO_ARCH_ESP32)

#include <Arduino.h>
#include <WiFi.h>
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

extern void (*serial_print)(const std::string &);

inline void restart_device() {
    ESP.restart();
}

inline void monitor_wifi() {
    static bool connected = false;

    if (WiFi.status() != WL_CONNECTED) {
        connected = false;
        WiFi.begin(wifi_name, wifi_password);
        Serial.printf("\nConnecting to WiFi...");
        unsigned long start = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
            delay(500);
            Serial.print(".");
        }
        Serial.println();
        delay(500);
    } else {
        if (connected == false) {
            connected = true;
            Serial.println("===== WiFi Info =====");
            Serial.printf("IP      : %s\n", WiFi.localIP().toString().c_str());
            Serial.printf("RSSI    : %d dBm\n", WiFi.RSSI());
            Serial.printf("MAC     : %s\n", WiFi.macAddress().c_str());
            Serial.printf("SSID    : %s\n", WiFi.SSID().c_str());
            Serial.println("=====================");
            Serial.println("WiFi connect success!");
        }
        delay(1000);
    }
}

#endif // ARDUINO_ARCH_ESP32