#include "amrControl.h"

AMRControl::AMRControl() {
    task_name_ = "amr_control_task";
    core_id_ = 1;
    priority_ = 9;

    motionControl_ = &MotionControl::instance();
    amrNode_ = &AMRNode::instance();
    mpu6050Control_ = &MPU6050Control::instance();
}

void AMRControl::update() {
    motionControl_->update();
    mpu6050Control_->update();

    motionControl_->calculate();
    mpu6050Control_->calculate();

    amrNode_->publish_msgs();

    motionControl_->move();
}