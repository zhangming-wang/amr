#include "masterTask.h"

MasterTask::MasterTask() {
    task_name_ = "amr_control_task";
    priority_ = 9;
    stack_size_ = 16384;

    task_tick_count_ = xTaskGetTickCount();

    motionControl_ = &MotionControl::instance();
    motionNode_ = &MotionNode::instance();
    mpu6050Control_ = &MPU6050Control::instance();
    mpu6050Control_->set_pins(8, 9);
}

void MasterTask::update() {
    motionControl_->update();
    mpu6050Control_->update();

    motionControl_->move();

    vTaskDelayUntil(&task_tick_count_, motionControl_->get_milliseconds());
}