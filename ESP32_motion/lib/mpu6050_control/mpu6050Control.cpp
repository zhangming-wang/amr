#include "mpu6050Control.h"

MPU6050Control::MPU6050Control() {
    if (is_dmp_handle_) {
        init_success_ = _dmp_init();
    } else {
        init_success_ = _manual_init();
    }

    rosidl_runtime_c__String__assign(&imu_msg_.header.frame_id, "imu_link");
}

void MPU6050Control::update() {
    if (init_success_ && !is_calibrating_.load()) {
        if (is_dmp_handle_) {
            _dmp_read();
        } else {
            _manual_read();
        }
    }
}

void MPU6050Control::set_pins(int pin_SDA, int pin_SCL) {
    if (pin_SDA != pin_SDA_ || pin_SCL != pin_SCL_) {
        pin_SDA_ = pin_SDA;
        pin_SCL_ = pin_SCL;
    }
}

bool MPU6050Control::_manual_init() {
    if (pin_SDA_ <= 0 || pin_SCL_ <= 0)
        return false;

    Wire.begin(pin_SDA_, pin_SCL_);
    Wire.beginTransmission(0x68);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0x00); // set to zero (wakes up the MPU-6050)

    if (Wire.endTransmission() == 0) {
        serial_print("手动初始化MPU6050成功.");
        return true;
    } else {
        serial_print("手动初始化MPU6050失败.");
        return false;
    }
}

bool MPU6050Control::_dmp_init() {
    if (pin_SDA_ <= 0 || pin_SCL_ <= 0)
        return false;

    Wire.begin(pin_SDA_, pin_SCL_);
    Wire.setClock(400000); // I2C 400kHz
    delay(500);

    mpu_.reset(); // 重置 MPU6050 的所有寄存器
    delay(100);
    mpu_.resetFIFO(); // 清空 FIFO 缓冲区
    mpu_.setSleepEnabled(false);
    mpu_.initialize();

    uint8_t devStatus = mpu_.dmpInitialize();
    if (devStatus == 0) {
        // 进行校准（保持静止）
        _loadCalibration();
        // 启用 DMP
        mpu_.setRate(4);
        mpu_.setDMPEnabled(true);
        packetSize_ = mpu_.dmpGetFIFOPacketSize();
        serial_print("DMP 初始化成功！");
    } else {
        serial_print("DMP 初始化失败，错误代码: " + std::to_string(devStatus));
        return false;
    }

    return true;
}

void MPU6050Control::start_calibration() {
    if (!init_success_) {
        serial_print("MPU6050模块初始化失败，校准失败.");
        return;
    }

    xTaskCreate(
        [](void *param) {
            MPU6050Control *self = static_cast<MPU6050Control *>(param);
            self->_start_calibration_task();
            vTaskDelete(NULL);
        },
        "mpu6050_calibration_task",
        4096,
        this,
        1,
        NULL);
}

void MPU6050Control::_start_calibration_task() {
    serial_print("校准中，请保持模块静止...");

    is_calibrating_.store(true);
    delay(500); // 确保在调用此函数时模块已稳定

    mpu_.resetFIFO();          // 🧹 清空 FIFO
    mpu_.setDMPEnabled(false); // ❌ 暂时关闭 DMP

    mpu_.CalibrateGyro(6);
    mpu_.CalibrateAccel(6);

    xAccelOffset_ = mpu_.getXAccelOffset();
    yAccelOffset_ = mpu_.getYAccelOffset();
    zAccelOffset_ = mpu_.getZAccelOffset();
    xGyroOffset_ = mpu_.getXGyroOffset();
    yGyroOffset_ = mpu_.getYGyroOffset();
    zGyroOffset_ = mpu_.getZGyroOffset();

    preferences_.begin("mpu", false);
    preferences_.clear();
    preferences_.putShort("xAccffset", xAccelOffset_);
    preferences_.putShort("yAccOffset", yAccelOffset_);
    preferences_.putShort("zAccOffset", zAccelOffset_);
    preferences_.putShort("xGyroOffset", xGyroOffset_);
    preferences_.putShort("yGyroOffset", yGyroOffset_);
    preferences_.putShort("zGyroOffset", zGyroOffset_);

    preferences_.end();

    mpu_.setDMPEnabled(true); // ✅ 最后再重新开启 DMP
    mpu_.resetFIFO();         // 🧹 再次清空，防止旧数据残留

    serial_print("校准完成!");

    is_calibrating_.store(false);
}

void MPU6050Control::_loadCalibration() {
    preferences_.begin("mpu", true); // 只读模式
    // 如果没保存过，会返回0，或你也可以判断是否存在
    xAccelOffset_ = preferences_.getShort("xAccffset", 0);
    yAccelOffset_ = preferences_.getShort("yAccOffset", 0);
    zAccelOffset_ = preferences_.getShort("zAccOffset", 0);
    xGyroOffset_ = preferences_.getShort("xGyroOffset", 0);
    yGyroOffset_ = preferences_.getShort("yGyroOffset", 0);
    zGyroOffset_ = preferences_.getShort("zGyroOffset", 0);
    preferences_.end();

    mpu_.setXAccelOffset(xAccelOffset_);
    mpu_.setYAccelOffset(yAccelOffset_);
    mpu_.setZAccelOffset(zAccelOffset_);
    mpu_.setXGyroOffset(xGyroOffset_);
    mpu_.setYGyroOffset(yGyroOffset_);
    mpu_.setZGyroOffset(zGyroOffset_);

    // 简单判断：如果都为0，可能没保存过
    if (xAccelOffset_ == 0 && yAccelOffset_ == 0 && zAccelOffset_ == 0 &&
        xGyroOffset_ == 0 && yGyroOffset_ == 0 && zGyroOffset_ == 0) {
        serial_print("未进行校准过，加载默认初始值");
    } else {
        serial_print("加载mpu校准值完成");
    }
}

void MPU6050Control::_dmp_read() {
    fifoCount_ = mpu_.getFIFOCount();

    if (fifoCount_ >= 1024) { // FIFO溢出，清空缓冲区
        mpu_.resetFIFO();
        return;
    } else if (fifoCount_ < packetSize_) {
        return;
    } else if (fifoCount_ > packetSize_) { // 只保留 FIFO 中最后一帧，丢弃其余数据
        uint8_t discard[packetSize_];
        while (fifoCount_ > packetSize_) {
            mpu_.getFIFOBytes(discard, packetSize_);
            fifoCount_ = mpu_.getFIFOCount();
        }
    }

    mpu_.getFIFOBytes(fifoBuffer_, packetSize_); // 读取最新的一帧

    Quaternion q;
    VectorFloat gravity;
    float ypr[3];
    VectorInt16 gyro;

    mpu_.dmpGetQuaternion(&q, fifoBuffer_);
    mpu_.dmpGetGravity(&gravity, &q);
    mpu_.dmpGetYawPitchRoll(ypr, &q, &gravity);
    mpu_.dmpGetGyro(&gyro, fifoBuffer_);

    yaw_ = ypr[0] * 180 / M_PI;
    pitch_ = ypr[1] * 180 / M_PI;
    roll_ = ypr[2] * 180 / M_PI;

    gyroX_ = gyro.x / 131.0;
    gyroY_ = gyro.y / 131.0;
    gyroZ_ = gyro.z / 131.0;
}

void MPU6050Control::_manual_read() {
    // 1. 读取原始数据
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    if (Wire.endTransmission(false) != 0)
        return;
    if (Wire.requestFrom(0x68, 14) != 14)
        return;

    for (int i = 0; i < 14; i++) {
        data_[i] = Wire.read();
    }

    // 2. 转换物理量
    float ax = (int16_t)((data_[0] << 8) | data_[1]) / 16384.0;
    float ay = (int16_t)((data_[2] << 8) | data_[3]) / 16384.0;
    float az = (int16_t)((data_[4] << 8) | data_[5]) / 16384.0;

    gyroX_ = (int16_t)((data_[8] << 8) | data_[9]) / 131.0; // °/s
    gyroY_ = (int16_t)((data_[10] << 8) | data_[11]) / 131.0;
    gyroZ_ = (int16_t)((data_[12] << 8) | data_[13]) / 131.0;

    // 3. 计算时间差
    unsigned long now = micros();
    float dt = (now - last_update_time_) / 1e6; // 秒
    last_update_time_ = now;

    // 5. 陀螺仪积分更新欧拉角
    pitch_ += gyroY_ * dt; // Y轴角速度 → pitch
    roll_ += gyroX_ * dt;  // X轴角速度 → roll
    yaw_ += gyroZ_ * dt;   // Z轴角速度 → yaw（会漂移）

    // 6. 互补滤波融合加速度计（修正漂移）
    pitch_ = ALPHA * pitch_ + (1 - ALPHA) * atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / M_PI;
    roll_ = ALPHA * roll_ + (1 - ALPHA) * atan2(ay, az) * 180.0 / M_PI;
}

sensor_msgs__msg__Imu &MPU6050Control::get_imu_msg() {
    return imu_msg_;
}

void MPU6050Control::calculate() {
    double cy = cos(yaw_ * 0.5);
    double sy = sin(yaw_ * 0.5);
    double cp = cos(pitch_ * 0.5);
    double sp = sin(pitch_ * 0.5);
    double cr = cos(roll_ * 0.5);
    double sr = sin(roll_ * 0.5);

    imu_msg_.orientation.w = cr * cp * cy + sr * sp * sy;
    imu_msg_.orientation.x = sr * cp * cy - cr * sp * sy;
    imu_msg_.orientation.y = cr * sp * cy + sr * cp * sy;
    imu_msg_.orientation.z = cr * cp * sy - sr * sp * cy;

    imu_msg_.orientation_covariance[0] = 0.0025;
    imu_msg_.orientation_covariance[4] = 0.0025;
    imu_msg_.orientation_covariance[8] = 0.0025;

    imu_msg_.angular_velocity.x = gyroX_ * M_PI / 180.0;
    imu_msg_.angular_velocity.y = gyroY_ * M_PI / 180.0;
    imu_msg_.angular_velocity.z = gyroZ_ * M_PI / 180.0;

    imu_msg_.angular_velocity_covariance[0] = 0.02;
    imu_msg_.angular_velocity_covariance[4] = 0.02;
    imu_msg_.angular_velocity_covariance[8] = 0.02;

    imu_msg_.linear_acceleration.x = 0.0;
    imu_msg_.linear_acceleration.y = 0.0;
    imu_msg_.linear_acceleration.z = 0.0;

    imu_msg_.linear_acceleration_covariance[0] = -1.0;
}
