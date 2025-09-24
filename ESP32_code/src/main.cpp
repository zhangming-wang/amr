#include "centerControl.h"
#include "esp_timer.h"
#include "httpService.h"
#include "microRos.h"
#include "motorControl.h"
#include "serial_print.h"
#include <Arduino.h>
#include <ESP32Encoder.h>

// put function declarations here:

const char *wifi_name = "TP-LINK_403";
const char *wifi_password = "403123456";
const char *wifi_IP = "192.168.1.101";

IPAddress ESP32_IP = IPAddress(192, 168, 1, 190);

void (*serial_print)(const std::string &) = _serial_print;

CenterControl centerControl;
MicroRos microRos("micro_ros_node", wifi_name, wifi_password, wifi_IP, 8888);
HttpService httpService(80);

void setup() {
    Serial.begin(115200);
    delay(1000); // 等串口稳定

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);
    WiFi.config(ESP32_IP, IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
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

// Motor left_front_motor = Motor();
// Motor left_back_motor = Motor();

// void setup() {
//     Serial.begin(115200);
//     delay(1000); // 等串口稳定
//     left_front_motor.set_pins(21, 22, 23);
//     left_back_motor.set_pins(19, 18, 17);
// }

// void loop() {
//     left_front_motor.set_speed((float)1.0);
//     left_back_motor.set_speed((float)1.0);
//     left_front_motor.move();
//     left_back_motor.move();
//     delay(1000);
//     left_front_motor.set_speed((float)-1.0);
//     left_back_motor.set_speed((float)-1.0);
//     left_front_motor.move();
//     left_back_motor.move();
//     delay(1000);
// }