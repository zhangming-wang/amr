#include "cameraControl.h"
#include "cameraNode.h"
#include "esp_timer.h"
#include "esp_tools.h"
#include "httpService.h"
#include "motionControl.h"
#include "motionNode.h"
#include "serialPrint.h"
#include "settings.h"
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

    WiFi.mode(WIFI_STA); // 仅启用 STA 模式，大幅降低射频资源占用
    WiFi.persistent(false);

    // IPAddress ESP32_IP = IPAddress(), ESP32_gateway = IPAddress(), ESP32_subnet = IPAddress();
    // ESP32_IP.fromString(esp32_ip);
    // ESP32_gateway.fromString(esp32_gateway);
    // ESP32_subnet.fromString(esp32_subnet);
    // WiFi.config(ESP32_IP, ESP32_gateway, ESP32_subnet);
    // WiFi.config(0U, 0U, 0U);

#if defined(esp32_wroom_motion) || defined(esp32_s3_motion)
    MotionControl &motionControl = MotionControl::get_instance();
    MotionNode &motionNode = MotionNode::get_instance();
    // HttpService &httpService = HttpService::get_instance();

    motionControl.init();
    motionNode.init(esp32_motion_node_name, esp32_motion_node_namespace, wifi_name, wifi_password, wifi_IP, micro_ros_port);
    // httpService.init(http_port);

    motionControl.start_task();
    motionNode.start_task();
    // httpService.start_task();

#elif defined(esp32_wroom_camera) || defined(esp32_s3_camera)
    CameraControl &cameraControl = CameraControl::get_instance();
    CameraNode &cameraNode = CameraNode::get_instance();

    cameraControl.init(true);
    cameraNode.init(esp32_camera_node_name, esp32_camera_node_namespace, wifi_name, wifi_password, wifi_IP, micro_ros_port);
    cameraNode.start_task();

#elif defined(esp32_wroom_ydlidarX2)
    YdlidarX2 &ydlidarX2 = YdlidarX2::get_instance();
    ydlidarX2.init(wifi_IP, tcp_client_port, 14, 25, -1, ydlidar_baudrate);
    ydlidarX2.start_task();

#else
    Serial.println("env is invalid!")
#endif
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