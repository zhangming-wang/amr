#pragma once

#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "singleton.h"
#include <atomic>
#include <cstdint>
#include <string>

class BaseTask {

protected:
    BaseTask() = default;
    virtual ~BaseTask() = default;

    virtual void clean_task() {}
    virtual void init_task() {}
    virtual void sleep() { vTaskDelay(pdMS_TO_TICKS(10)); }

    std::atomic_bool enable_task_run_{false};
    std::atomic<TaskHandle_t> task_handle_{nullptr};
    uint32_t stack_size_{8192};
    int8_t priority_{1}, core_id_{-1};

    std::string task_name_{"BaseTask"};

public:
    BaseTask(const BaseTask &) = delete;
    BaseTask &operator=(const BaseTask &) = delete;

    virtual void update() = 0;

    void start_task() {
        if (task_handle_.load()) {
            return;
        }

        enable_task_run_.store(true);

        BaseType_t ret;
        TaskHandle_t handle;
        if (core_id_ == -1) {
            ret = xTaskCreate(task_loop, task_name_.c_str(), stack_size_, this, priority_, &handle);
        } else {
            ret = xTaskCreatePinnedToCore(task_loop, task_name_.c_str(), stack_size_, this, priority_, &handle, core_id_);
        }

        if (ret == pdPASS) {
            task_handle_.store(handle);
        }
    }
    void stop_task() {
        if (!task_handle_.load()) {
            return;
        }

        enable_task_run_.store(false);
    }
    void restart_task() {
        stop_task();

        uint32_t timeout = 100; // 最大等待 1000 ms
        while (task_handle_.load() && timeout-- >= 0) {
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        start_task();
    }

private:
    static inline void task_loop(void *args) {
        auto *self = static_cast<BaseTask *>(args);

        self->init_task();
        while (self->enable_task_run_.load()) {
            self->update();
            self->sleep();
        }
        self->clean_task();

        self->task_handle_.store(nullptr);
        vTaskDelete(nullptr);
    }
};

template <typename T>
class BaseTaskSingleton : public BaseTask, public Singleton<T> {
protected:
    BaseTaskSingleton() = default;
    ~BaseTaskSingleton() = default;
};

#endif // ARDUINO_ARCH_ESP32