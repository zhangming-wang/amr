#include "cameraControl.h"
#include "cameraNode.h"
#include "esp_timer.h"
#include "serialPrint.h"
#include "settings.h"
#include "tools.h"
#include <Arduino.h>

void (*serial_print)(const std::string &) = _serial_print;

void setup() {
    Serial.begin(115200);
    while (!Serial) { // 等待主机连接到 CDC 端口
        delay(10);
    }

    test_ram();

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    CameraControl &cameraControl = CameraControl::get_instance();
    CameraNode &cameraNode = CameraNode::get_instance();

    cameraControl.init(true);
    cameraNode.init(esp32_camera_node_name, esp32_camera_node_namespace, wifi_name, wifi_password, wifi_IP, micro_ros_port);

    cameraNode.start_task();
}

bool connected = false;

void loop() {
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
    }
    delay(1000);
}