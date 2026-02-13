#include "sensorsControlTask.h"

SensorsControlTask::SensorsControlTask() {
    task_name_ = "sensors_control_task";
    priority_ = 9;
    core_id_ = 0;
    stack_size_ = 8192;

    task_tick_count_ = xTaskGetTickCount();

    mpu6050Control_ = std::make_shared<MPU6050Control>("mpu");
    lidarControl_ = std::make_shared<LidarControl>("lidar");

    _load_config();
    _load_params();
}

void SensorsControlTask::update() {
    lidarControl_->update();
    vTaskDelayUntil(&task_tick_count_, 10 / portTICK_PERIOD_MS);
}

std::shared_ptr<MPU6050Control> SensorsControlTask::get_mpu6050_control() {
    return mpu6050Control_;
}

std::shared_ptr<LidarControl> SensorsControlTask::get_lidar_control() {
    return lidarControl_;
}

void SensorsControlTask::write_params(const motion_settings_service__srv__MotionSettingsService_Request *request) {
    mpu6050Control_->set_offset(request->sensor_settings.accel_offset_x, request->sensor_settings.accel_offset_y, request->sensor_settings.accel_offset_z,
                                request->sensor_settings.gyro_offset_x, request->sensor_settings.gyro_offset_y, request->sensor_settings.gyro_offset_z);
}

void SensorsControlTask::get_data(motion_status_msgs__msg__MotionStatus &msg) {
    mpu6050Control_->get_data(msg.sensor_status.gyro_x, msg.sensor_status.gyro_y, msg.sensor_status.gyro_z, msg.sensor_status.yaw, msg.sensor_status.pitch, msg.sensor_status.roll);
    lidarControl_->get_data(msg.sensor_status.data, msg.sensor_status.size);
}

void SensorsControlTask::read_params(motion_settings_service__srv__MotionSettingsService_Response *response) {
    mpu6050Control_->get_offset(response->sensor_settings.accel_offset_x, response->sensor_settings.accel_offset_y, response->sensor_settings.accel_offset_z,
                                response->sensor_settings.gyro_offset_x, response->sensor_settings.gyro_offset_y, response->sensor_settings.gyro_offset_z);
}

void SensorsControlTask::save_params() {
    mpu6050Control_->save_params();
}

void SensorsControlTask::_load_params() {
    mpu6050Control_->load_params();
}

void SensorsControlTask::write_config(const motion_settings_service__srv__MotionSettingsService_Request *request) {
    mpu6050Control_->set_pins(request->sensor_settings.pin_sda, request->sensor_settings.pin_scl);
    lidarControl_->set_pins(request->sensor_settings.pin_tx, request->sensor_settings.pin_rx, request->sensor_settings.pin_pwm);
}

void SensorsControlTask::read_config(motion_settings_service__srv__MotionSettingsService_Response *response) {
    mpu6050Control_->get_pins(response->sensor_settings.pin_sda, response->sensor_settings.pin_scl);
    lidarControl_->get_pins(response->sensor_settings.pin_tx, response->sensor_settings.pin_rx, response->sensor_settings.pin_pwm);
}

void SensorsControlTask::save_config() {
    mpu6050Control_->save_config();
    lidarControl_->save_config();
}

void SensorsControlTask::_load_config() {
    mpu6050Control_->load_config();
    lidarControl_->load_config();
}