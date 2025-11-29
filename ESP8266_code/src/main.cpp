#include "esp_tools.h"
#include "settings.h"
#include "ydlidarX2.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <vector>

YdlidarX2 *ydlidarX2 = nullptr;

void setup() {
    ydlidarX2 = &YdlidarX2::get_instance();
    ydlidarX2->init(wifi_IP, tcp_client_port, D7, ydlidar_baudrate);

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_name, wifi_password);

    Serial.printf("\nConnecting to WiFi...");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 30000) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
}

bool connected = false;

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        connected = false;
        Serial.println("WiFi Disconnected, reconnecting...");
        WiFi.reconnect();
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
        } else {
            ydlidarX2->sendData();
        }
    }
}