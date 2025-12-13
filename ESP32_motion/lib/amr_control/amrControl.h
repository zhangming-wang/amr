#pragma once
#include "amrNode.h"
#include "esp_timer.h"
#include "motionControl.h"
#include "mpu6050Control.h"
#include <Arduino.h>
#include <micro_ros_platformio.h>

class AMRControl {
private:
    AMRControl();
    ~AMRControl();

public:
    AMRControl(const AMRControl &) = delete;
    AMRControl &operator=(const AMRControl &) = delete;
    static AMRControl &get_instance();

    void init();
    void update();

    void start_task();
    void stop_task();
    void restart_task();

private:
    float dt_ = 0.0;

    esp_timer_handle_t control_timer_ = nullptr;
    SemaphoreHandle_t mutex_; // 互斥量句柄
    QueueHandle_t control_queue_;

    MotionControl *motionControl_ = nullptr;
    AMRNode *amrNode_ = nullptr;
    MPU6050Control *mpu6050Control_ = nullptr;

    void _start_control_timer();
    void _stop_control_timer();

    QueueHandle_t &get_control_deque();

    static void control_loop(void *args);
    static void control_timer_callback(void *args);
};