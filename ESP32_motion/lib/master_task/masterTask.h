#pragma once
#include "baseTask.h"
#include "motionControl.h"
#include "motionNode.h"
#include "mpu6050Control.h"
#include "singleton.h"
#include <Arduino.h>
#include <micro_ros_platformio.h>

class MasterTask : public BaseTaskSingleton<MasterTask> {

    friend class Singleton<MasterTask>;

protected:
    MasterTask();

public:
    void update() override;

private:
    MotionControl *motionControl_ = nullptr;
    MotionNode *motionNode_ = nullptr;
    MPU6050Control *mpu6050Control_ = nullptr;

    TickType_t task_tick_count_;
};