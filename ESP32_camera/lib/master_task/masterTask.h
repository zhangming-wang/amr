#pragma once

#include "baseTask.h"
#include "cameraControl.h"
#include "cameraNode.h"

class MasterTask : public BaseTaskSingleton<MasterTask> {

    friend class Singleton<MasterTask>;

protected:
    MasterTask();
    void sleep() override { vTaskDelay(pdMS_TO_TICKS(cameraControl_->get_params().milliseconds)); }

public:
    void update() override;

private:
    CameraControl *cameraControl_;
    CameraNode *cameraNode_;
};