#pragma once

#include "baseTask.h"
#include "lidarControl.h"
#include "mpu6050Control.h"
#include "settings.h"
#include "system.h"
#include <Arduino.h>
extern "C" {
#include "motion_settings_service/srv/motion_settings_service.h"
#include "motion_status_msgs/msg/motion_status.h"
}

class SensorsControlTask : public BaseTaskSingleton<SensorsControlTask> {

    friend class Singleton<SensorsControlTask>;

protected:
    SensorsControlTask();

public:
    void update() override;
    std::shared_ptr<MPU6050Control> get_mpu6050_control();
    std::shared_ptr<LidarControl> get_lidar_control();

    void get_data(motion_status_msgs__msg__MotionStatus &msg);
    void read_params(motion_settings_service__srv__MotionSettingsService_Response *response);
    void save_params();

    void read_config(motion_settings_service__srv__MotionSettingsService_Response *response);
    void save_config();

private:
    std::shared_ptr<MPU6050Control> mpu6050Control_;
    std::shared_ptr<LidarControl> lidarControl_;

    TickType_t task_tick_count_;

    void _load_config();
    void _load_params();
};
