#pragma once

#include "motionControl.h"
#include "serialPrint.h"
#include <WebServer.h>
#include <WiFi.h>

class HttpService {

public:
    static HttpService &get_instance();

    HttpService(const HttpService &) = delete;
    HttpService &operator=(const HttpService &) = delete;

    void init(const int port);
    void start_task();
    void stop_task();

private:
    HttpService();
    ~HttpService();

    WebServer webServer_;
    bool enable_task_run_ = false;
    int port_ = 0;

    MotionControl *motionControl_ = nullptr;

    void begin();
    void stop();
    void handleClient();
    bool is_enable_task_run();

    static void http_serive_task(void *args);
};
