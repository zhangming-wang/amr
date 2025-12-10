#include "esp_timer.h"
#include "motionControl.h"
#include "motionNode.h"
#include "serialPrint.h"
#include "settings.h"
#include "tools.h"
#include "ydlidarX2.h"
#include <Arduino.h>
#include <ESP32Encoder.h>

void (*serial_print)(const std::string &) = _serial_print;

void setup() {
    Serial.begin(115200);
    while (!Serial) { // 等待主机连接到 CDC 端口
        delay(10);
    }

    test_ram();

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    MotionControl &motionControl = MotionControl::get_instance();
    MotionNode &motionNode = MotionNode::get_instance();
    YdlidarX2 &ydlidarX2 = YdlidarX2::get_instance();

    motionControl.init();
    ydlidarX2.init(wifi_IP, tcp_client_port, 14, 25, -1, ydlidar_baudrate);
    motionNode.init(esp32_motion_node_name, esp32_motion_node_namespace, wifi_name, wifi_password, wifi_IP, micro_ros_port);

    motionControl.start_task();
    ydlidarX2.start_task();
    motionNode.start_task();
}

bool connected = false;
bool initialized = false;

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