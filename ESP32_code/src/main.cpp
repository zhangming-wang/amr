#include "centerControl.h"
#include "esp_timer.h"
#include "httpService.h"
#include "microRos.h"
#include "motorControl.h"
#include "serial_print.h"
#include "settings.h"
#include <Arduino.h>
#include <ESP32Encoder.h>

// const char *wifi_name = "TP-LINK_403";
// const char *wifi_password = "403123456";
// const char *wifi_IP = "192.168.1.101";

void (*serial_print)(const std::string &) = _serial_print;

CenterControl centerControl;
MicroRos microRos("micro_ros_node", wifi_name, wifi_password, wifi_IP, micro_ros_port);
HttpService httpService(http_port);

void setup() {
    Serial.begin(115200);
    delay(1000); // 等串口稳定

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);

    IPAddress ESP32_IP = IPAddress(), ESP32_gateway = IPAddress(), ESP32_subnet = IPAddress();
    ESP32_IP.fromString(esp32_ip);
    ESP32_gateway.fromString(esp32_gateway);
    ESP32_subnet.fromString(esp32_subnet);

    WiFi.config(ESP32_IP, ESP32_gateway, ESP32_subnet);
    WiFi.begin(wifi_name, wifi_password);
    delay(1000);

    centerControl.init_and_start();
    microRos.start_task();
    httpService.start_task();
}

bool connected = false;

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        connected = false;
        serial_print("WiFi Disconnected, reconnecting...");
        WiFi.reconnect();
    } else {
        if (connected == false) {
            connected = true;
            serial_print("WiFi connect success!");
        }
    }
    delay(1000);
}