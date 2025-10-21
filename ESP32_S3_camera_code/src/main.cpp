#include "esp32cam.h"
#include "esp_tools.h"
#include "microRos.h"
#include "settings.h"
#include <Arduino.h>
#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    delay(1000); // 等待串口稳定

    test_ram();

    WiFi.begin(wifi_name, wifi_password);
    delay(1000);

    ESP32Cam &esp32Cam = ESP32Cam::get_instance();
    MicroRos &microRos = MicroRos::get_instance();

    esp32Cam.init(true); // 初始化摄像头并加载配置
    microRos.init(esp32_camera_node_name, esp32_camera_node_namespace, wifi_name, wifi_password, wifi_IP, micro_ros_port);
    microRos.start_task();
}

bool connected = false;

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        connected = false;
        Serial.printf("WiFi Disconnected status=%d, reconnecting...\n", WiFi.status());
        WiFi.reconnect();
    } else {
        if (connected == false) {
            connected = true;
            Serial.println("WiFi connect success!");
        }
    }
    delay(1000);
}