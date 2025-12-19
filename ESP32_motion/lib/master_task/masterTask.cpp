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

    // Serial.print("\n\nMasterTask update dt: ");
    // Serial.println(millis() - time_count);
    // time_count = millis();

    motionControl_->calculate();
    mpu6050Control_->calculate();

    // Serial.print("MasterTask calculate dt: ");
    // Serial.println(millis() - time_count);
    // time_count = millis();

    motionNode_->publish_msgs();

    // Serial.print("MasterTask publish_msgs dt: ");
    // Serial.println(millis() - time_count);
    // time_count = millis();

    motionControl_->move();

    // Serial.print("MasterTask move dt: ");
    // Serial.println(millis() - time_count);
    // time_count = millis();

    vTaskDelayUntil(&task_tick_count_, pdMS_TO_TICKS(20));

    // Serial.print("MasterTask total dt: ");
    // Serial.println(millis() - begin_time);
    // Serial.println("-----------------------------\n");

    // vTaskDelay(pdMS_TO_TICKS(10));
}