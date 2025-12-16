#include "masterTask.h"

MasterTask::MasterTask() {
    task_name_ = "master_task";
    priority_ = 9;
    stack_size_ = 16384;
    cameraControl_ = &CameraControl::instance();
    cameraNode_ = &CameraNode::instance();
}

void MasterTask::update() {
    if (cameraNode_->get_enable_series_capture()) {
        cameraNode_->publish_image_msg();
    }
}