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
    static uint time_count = 0, begin_time = 0;

    begin_time = millis();
    time_count = begin_time;

    motionControl_->update();
    mpu6050Control_->update();

    motionNode_->publish_msgs();

    motionControl_->move();

    vTaskDelayUntil(&task_tick_count_, motionControl_->get_milliseconds());

    // Serial.print("MasterTask total dt: ");
    // Serial.println(millis() - begin_time);
    // Serial.println("-----------------------------\n");

    // vTaskDelay(pdMS_TO_TICKS(10));
}