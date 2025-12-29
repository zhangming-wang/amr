#include "masterTask.h"

MasterTask::MasterTask() {
    task_name_ = "amr_control_task";
    priority_ = 9;
    stack_size_ = 16384;

    task_tick_count_ = xTaskGetTickCount();

    mpu6050Control_ = &MPU6050Control::instance();
    motionControl_ = &MotionControl::instance();
    motionNode_ = &MotionNode::instance();
}

void MasterTask::update() {
    motionControl_->update();
    mpu6050Control_->update();

    motionControl_->move();

    vTaskDelayUntil(&task_tick_count_, motionControl_->get_milliseconds());
}

void MasterTask::init_task() {
    mpu6050Control_->load_config();
}
