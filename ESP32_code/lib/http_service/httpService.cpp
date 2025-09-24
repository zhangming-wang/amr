#include "httpService.h"

HttpService::HttpService(int port) : webServer_(port) {
}

HttpService::~HttpService() {
}

void HttpService::begin() {
    webServer_.on("/ping", [this]() {
        webServer_.sendHeader("Access-Control-Allow-Origin", "*");
        webServer_.send(200, "text/plain", "connected");
    });
    webServer_.on("/restart", [this]() {
        centerControl.restart();
    });
    webServer_.on("/brake", [this]() {
        centerControl.brake();
    });
    webServer_.on("/stop_move", [this]() {
        centerControl.stop_move();
    });
    webServer_.on("/move_front", [this]() {
        centerControl.move_front();
    });
    webServer_.on("/move_back", [this]() {
        centerControl.move_back();
    });
    webServer_.on("/move_left", [this]() {
        centerControl.move_left();
    });
    webServer_.on("/move_right", [this]() {
        centerControl.move_right();
    });
    webServer_.on("/move_left_front", [this]() {
        centerControl.move_left_front();
    });
    webServer_.on("/move_right_front", [this]() {
        centerControl.move_right_front();
    });
    webServer_.on("/move_left_back", [this]() {
        centerControl.move_left_back();
    });
    webServer_.on("/move_right_back", [this]() {
        centerControl.move_right_back();
    });
    webServer_.on("/turn_left", [this]() {
        centerControl.turn_left();
    });
    webServer_.on("/turn_right", [this]() {
        centerControl.turn_right();
    });
    webServer_.on("/save", [this]() {
        centerControl.save_params();
        centerControl.save_settings();
    });
    webServer_.on("/set_speed_percent", [this]() {
        auto percent = webServer_.arg("value").toFloat();
        centerControl.set_speed_percent(percent);
    });
    webServer_.on("/get_data", [this]() {
        webServer_.send(200, "application/json", centerControl.get_http_data());
    });
    webServer_.onNotFound([this]() {
        if (webServer_.method() == HTTP_OPTIONS) {
            webServer_.sendHeader("Access-Control-Allow-Origin", "*");
            webServer_.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
            webServer_.sendHeader("Access-Control-Allow-Headers", "*");
            webServer_.send(204); // No Content
        } else {
            webServer_.sendHeader("Access-Control-Allow-Origin", "*");
            webServer_.send(404, "text/plain", "404 Not Found");
        }
    });

    webServer_.begin();
}

void HttpService::stop() {
    webServer_.stop();
}

void HttpService::start_task() {
    if (enable_task_run == false) {
        enable_task_run = true;
        xTaskCreate(http_serive_task, "http_serive_task", 8192, this, 1, NULL);
    }
}

void HttpService::stop_task() {
    if (enable_task_run) {
        enable_task_run = false;
    }
}

void HttpService::handleClient() {
    webServer_.handleClient();
}

void http_serive_task(void *args) {
    HttpService *httpService = static_cast<HttpService *>(args);
    bool connected = false;
    while (httpService->enable_task_run) {
        if (WiFi.status() == WL_CONNECTED) {
            if (connected == false) {
                connected = true;
                httpService->begin();
                serial_print("HTTP Server started!");
            }
            httpService->handleClient(); // 处理HTTP请求
        } else {
            if (connected) {
                connected = false;
                httpService->stop();
                serial_print("HTTP Server stopped due to Wi-Fi disconnect");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(centerControl.get_milliseconds()));
    }
    if (connected) {
        httpService->stop();
        serial_print("HTTP Server stopped on task exit");
    }
    vTaskDelete(NULL);
}
