#include "masterTask.h"

MasterTask::MasterTask() {
    task_name_ = "amr_control_task";
    priority_ = 12;
    core_id_ = 1;
    stack_size_ = 16384;

    task_tick_count_ = xTaskGetTickCount();

    mpu6050Control_ = &MPU6050Control::instance();
    motionControl_ = &MotionControl::instance();
    motionNode_ = &MotionNode::instance();
}

void MasterTask::update() {
    static unsigned long last_time = 0, current_time = 0;
    static float dt = 0;
    current_time = millis();
    if (last_time != current_time && last_time != 0) {
        dt = (current_time - last_time) / 1000.0;
        motionControl_->update();
        mpu6050Control_->update();
        motionControl_->move(dt);
    }
    last_time = current_time;

    vTaskDelayUntil(&task_tick_count_, motionControl_->get_milliseconds());
}

void MasterTask::init_task() {
    mpu6050Control_->load_config();
}
