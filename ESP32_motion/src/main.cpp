#include "amrControl.h"
#include "settings.h"
#include "tools.h"
#include "ydlidarX2.h"
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    while (!Serial) { // 等待主机连接到 CDC 端口
        delay(10);
    }

    test_ram();

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    AMRControl &amrControl = AMRControl::instance();
    YdlidarX2 &ydlidarX2 = YdlidarX2::instance();
    AMRNode &amrNode = AMRNode::instance();

    amrControl.start_task();
    ydlidarX2.start_task();
    amrNode.start_task();
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
    delay(500);
}