#include "centerControl.h"
#include "esp_timer.h"
#include "httpService.h"
#include "microRos.h"
#include "motorControl.h"
#include "serialPrint.h"
#include "settings.h"
#include <Arduino.h>
#include <ESP32Encoder.h>

void (*serial_print)(const std::string &) = _serial_print;

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

    CenterControl &centerControl = CenterControl::get_instance();
    MicroRos &microRos = MicroRos::get_instance();
    HttpService &httpService = HttpService::get_instance();

    centerControl.init();
    microRos.init("micro_ros_node", wifi_name, wifi_password, wifi_IP, micro_ros_port);
    httpService.init(http_port);

    centerControl.start_task();
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