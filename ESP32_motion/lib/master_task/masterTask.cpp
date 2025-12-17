#include "masterTask.h"

MasterTask::MasterTask() {
    task_name_ = "amr_control_task";
    priority_ = 9;
    stack_size_ = 16384;

    task_tick_count_ = xTaskGetTickCount();

    motionControl_ = &MotionControl::instance();
    motionNode_ = &MotionNode::instance();
    mpu6050Control_ = &MPU6050Control::instance();
}

void MasterTask::update() {
    motionControl_->update();
    mpu6050Control_->update();

    motionControl_->calculate();
    mpu6050Control_->calculate();

    motionNode_->publish_msgs();

    motionControl_->move();

    vTaskDelayUntil(&task_tick_count_, pdMS_TO_TICKS(motionControl_->get_milliseconds()));
}