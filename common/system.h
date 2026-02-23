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

inline void restart_task(void *param) {
    vTaskDelay(pdMS_TO_TICKS(500)); // 等待 500ms，确保当前逻辑跑完
    ESP.restart();
}

inline void restart_device_async() {
    xTaskCreate(
        restart_task,
        "restart_task",
        2048,
        nullptr,
        1,
        nullptr);
}

inline void restart_device() {
    restart_device_async();
}

inline bool monitor_wifi() {
    static unsigned long connect_time = -20000;
    static bool connected = false;
    if (WiFi.status() != WL_CONNECTED) {
        connected = false;
        if (millis() - connect_time > 5000) {
            auto res = WiFi.begin(wifi_name, wifi_password);
            if (res == WL_CONNECTED) {
                connect_time = millis();
                Serial.printf("\nConnecting to WiFi...");
            } else {
                connect_time = -10000;
                Serial.printf("WiFi begin failed with error code: %d\n", res);
            }
        }
    } else {
        if (connected == false) {
            Serial.println();
            Serial.println("===== WiFi Info =====");
            Serial.printf("IP      : %s\n", WiFi.localIP().toString().c_str());
            Serial.printf("RSSI    : %d dBm\n", WiFi.RSSI());
            Serial.printf("MAC     : %s\n", WiFi.macAddress().c_str());
            Serial.printf("SSID    : %s\n", WiFi.SSID().c_str());
            Serial.println("=====================");
            Serial.println("WiFi connect success!");
            connected = true;
        }
    }
    return connected;
}

#endif // ARDUINO_ARCH_ESP32