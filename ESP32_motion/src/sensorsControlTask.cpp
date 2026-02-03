#include "sensorsControlTask.h"

SensorsControlTask::SensorsControlTask() {
    task_name_ = "sensors_control_task";
    priority_ = 10;
    core_id_ = 0;
    stack_size_ = 8192;

    task_tick_count_ = xTaskGetTickCount();

    mpu6050Control_ = std::make_shared<MPU6050Control>("mpu");
    lidarControl_ = std::make_shared<LidarControl>();

    // _load_config();
    // _load_params();

    mpu6050Control_->set_pins(1, 2);
    lidarControl_->set_pins(18, -1, -1);
}

void SensorsControlTask::update() {
    mpu6050Control_->update();
    lidarControl_->update();

    vTaskDelayUntil(&task_tick_count_, 10 / portTICK_PERIOD_MS);
}

std::shared_ptr<MPU6050Control> SensorsControlTask::get_mpu6050_control() {
    return mpu6050Control_;
}

std::shared_ptr<LidarControl> SensorsControlTask::get_lidar_control() {
    return lidarControl_;
}

void SensorsControlTask::get_data(motion_status_msgs__msg__MotionStatus &msg) {
    mpu6050Control_->get_data(msg.imu_gyro_x, msg.imu_gyro_y, msg.imu_gyro_z, msg.imu_yaw, msg.imu_pitch, msg.imu_roll);
}

void SensorsControlTask::read_params(motion_settings_service__srv__MotionSettingsService_Response *response) {
    mpu6050Control_->get_offset(response->mpu6050_accel_offset_x, response->mpu6050_accel_offset_y, response->mpu6050_accel_offset_z,
                                response->mpu6050_gyro_offset_x, response->mpu6050_gyro_offset_y, response->mpu6050_gyro_offset_z);
}

void SensorsControlTask::save_params() {
    mpu6050Control_->save_params();
}

void SensorsControlTask::read_config(motion_settings_service__srv__MotionSettingsService_Response *response) {
    mpu6050Control_->get_pins(response->mpu6050_pin_sda, response->mpu6050_pin_scl);
}

void SensorsControlTask::save_config() {
    mpu6050Control_->save_config();
}

void SensorsControlTask::_load_config() {
    mpu6050Control_->load_config();
    lidarControl_->load_config();
}

void SensorsControlTask::_load_params() {
    mpu6050Control_->load_params();
    lidarControl_->load_params();
}