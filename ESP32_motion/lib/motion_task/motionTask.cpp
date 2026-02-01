#include "motionTask.h"

MotionTask::MotionTask() {
    task_name_ = "motion_task";
    priority_ = 12;
    core_id_ = 1;
    stack_size_ = 16384;

    task_tick_count_ = xTaskGetTickCount();

    mpu6050Control_ = &MPU6050Control::instance();
    diffDriverControl_ = &DiffDriverControl::instance();
}

void MotionTask::update() {
    static unsigned long last_time = 0, current_time = 0;
    static float dt = 0;
    current_time = millis();
    if (last_time != current_time && last_time != 0) {
        dt = (current_time - last_time) / 1000.0;
        diffDriverControl_->update();
        mpu6050Control_->update();

        diffDriverControl_->move(dt);
    }
    last_time = current_time;

    vTaskDelayUntil(&task_tick_count_, diffDriverControl_->get_milliseconds());

    // diffDriverControl_->test_motors();
}

void MotionTask::init_task() {
    mpu6050Control_->load_config();
}
