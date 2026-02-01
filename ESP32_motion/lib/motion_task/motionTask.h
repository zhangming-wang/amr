#pragma once

#include "baseTask.h"
#include "diffDriverControl.h"
#include "mpu6050Control.h"
#include "singleton.h"
#include <Arduino.h>
#include <micro_ros_platformio.h>

class MotionTask : public BaseTaskSingleton<MotionTask> {

    friend class Singleton<MotionTask>;

protected:
    MotionTask();
    ~MotionTask() = default;

    void init_task() override;

public:
    void update() override;

private:
    DiffDriverControl *diffDriverControl_ = nullptr;
    MPU6050Control *mpu6050Control_ = nullptr;

    TickType_t task_tick_count_;
};