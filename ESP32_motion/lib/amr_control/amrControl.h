#pragma once
#include "amrNode.h"
#include "baseTask.h"
#include "motionControl.h"
#include "mpu6050Control.h"
#include "singleton.h"
#include <Arduino.h>
#include <micro_ros_platformio.h>

class AMRControl : public BaseTaskSingleton<AMRControl> {

    friend class Singleton<AMRControl>;

public:
    void update() override;

protected:
    AMRControl();
    void sleep() override { vTaskDelay(pdMS_TO_TICKS(motionControl_->get_milliseconds())); }

private:
    MotionControl *motionControl_ = nullptr;
    AMRNode *amrNode_ = nullptr;
    MPU6050Control *mpu6050Control_ = nullptr;
};