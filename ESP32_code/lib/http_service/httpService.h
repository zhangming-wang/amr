#pragma once

#include "centerControl.h"
#include "serial_print.h"
#include <WebServer.h>
#include <WiFi.h>

class HttpService {
    friend void http_serive_task(void *args);

public:
    HttpService(const int port);
    ~HttpService();

    void start_task();
    void stop_task();

private:
    WebServer webServer_;
    bool enable_task_run = false;

    void begin();
    void stop();
    void handleClient();

    void _send_update_ui_data();
};

extern HttpService httpService;

void http_serive_task(void *args);
