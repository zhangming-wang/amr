#include "mpu6050Control.h"

MPU6050Control::MPU6050Control() {
}

MPU6050Control::MPU6050Control(const std::string &name) {
    name_ = name;
}

void MPU6050Control::update() {
    if (init_success_.load() && !is_calibrating_.load()) {
        if (is_dmp_handle_) {
            _dmp_read();
        } else {
            _manual_read();
        }
    }
}

void MPU6050Control::get_pins(int &pin_SDA, int &pin_SCL) {
    pin_SDA = pin_SDA_;
    pin_SCL = pin_SCL_;
}

void MPU6050Control::set_pins(int pin_SDA, int pin_SCL) {
    if (pin_SDA <= 0 || pin_SCL <= 0) {
        serial_print("设置MPU6050引脚失败，SDA和SCL引脚号必须大于0.");
        return;
    }

    if (init_success_.load() && pin_SDA == pin_SDA_ && pin_SCL == pin_SCL_) {
        serial_print("MPU6050引脚未更改，跳过初始化.");
        return;
    }

    Wire.end(); // 关闭（即使没 init 也安全）
    delay(100);

    init_success_.store(false);

    pin_SDA_ = pin_SDA;
    pin_SCL_ = pin_SCL;

    serial_print("MPU6050Control set pins: SDA=" + std::to_string(pin_SDA_) + ", SCL=" + std::to_string(pin_SCL_));

    if (is_dmp_handle_) {
        init_success_.store(_dmp_init());
    } else {
        init_success_.store(_manual_init());
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
    if (pin_SDA_ < 0 || pin_SCL_ < 0) {
        serial_print("MPU6050 引脚未设置，初始化失败.");
        return false;
    }

    if (!Wire.begin(pin_SDA_, pin_SCL_, 400000)) {
        serial_print("初始化 I2C 总线失败.");
        return false;
    }
    delay(100);

    mpu_.initialize();
    delay(100);

    if (!mpu_.testConnection()) {
        serial_print("MPU6050 not connected!");
        return false;
    }

    mpu_.setSleepEnabled(false);

    uint8_t devStatus = mpu_.dmpInitialize();
    if (devStatus != 0) {
        serial_print("DMP 初始化失败，错误代码: " + std::to_string(devStatus));
        return false;
    }

    // ⚠️ DMP 固件加载完成后
    load_params(); // 保持静止

    mpu_.setDMPEnabled(true);
    mpu_.resetFIFO(); // ✅ 只在这里 reset

    packetSize_ = mpu_.dmpGetFIFOPacketSize();
    serial_print("MPU6050 DMP 初始化成功, 包的大小: " + std::to_string(packetSize_));

    return true;
}

void MPU6050Control::start_calibration() {
    if (!init_success_.load()) {
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

    mpu_.setDMPEnabled(true); // ✅ 最后再重新开启 DMP
    mpu_.resetFIFO();         // 🧹 再次清空，防止旧数据残留

    save_params();

    serial_print("校准完成,请重新读取参数！");

    is_calibrating_.store(false);
}

void MPU6050Control::get_offset(int16_t &xAccOffset, int16_t &yAccOffset, int16_t &zAccOffset,
                                int16_t &xGyroOffset, int16_t &yGyroOffset, int16_t &zGyroOffset) {
    xAccOffset = xAccelOffset_;
    yAccOffset = yAccelOffset_;
    zAccOffset = zAccelOffset_;
    xGyroOffset = xGyroOffset_;
    yGyroOffset = yGyroOffset_;
    zGyroOffset = zGyroOffset_;
}

void MPU6050Control::set_offset(int16_t xAccOffset, int16_t yAccOffset, int16_t zAccOffset, int16_t xGyroOffset, int16_t yGyroOffset, int16_t zGyroOffset) {
    if (!init_success_.load()) {
        serial_print("MPU6050模块未初始化，无法设置偏移量.");
        return;
    }

    xAccelOffset_ = xAccOffset;
    yAccelOffset_ = yAccOffset;
    zAccelOffset_ = zAccOffset;
    xGyroOffset_ = xGyroOffset;
    yGyroOffset_ = yGyroOffset;
    zGyroOffset_ = zGyroOffset;

    mpu_.setXAccelOffset(xAccelOffset_);
    mpu_.setYAccelOffset(yAccelOffset_);
    mpu_.setZAccelOffset(zAccelOffset_);
    mpu_.setXGyroOffset(xGyroOffset_);
    mpu_.setYGyroOffset(yGyroOffset_);
    mpu_.setZGyroOffset(zGyroOffset_);
}

void MPU6050Control::save_params() {
    if (name_.empty()) {
        serial_print("MPU6050Control name is empty, cannot save params.");
        return;
    }

    preferences_.begin(std::string(name_ + "params").c_str(), false);
    preferences_.clear();
    preferences_.putShort("xAccelOffset", xAccelOffset_);
    preferences_.putShort("yAccelOffset", yAccelOffset_);
    preferences_.putShort("zAccelOffset", zAccelOffset_);
    preferences_.putShort("xGyroOffset", xGyroOffset_);
    preferences_.putShort("yGyroOffset", yGyroOffset_);
    preferences_.putShort("zGyroOffset", zGyroOffset_);
    preferences_.end();
}

void MPU6050Control::load_params() {
    if (name_.empty()) {
        serial_print("MPU6050Control name is empty, cannot load params.");
        return;
    }

    preferences_.begin(std::string(name_ + "params").c_str(), true); // 只读模式
    // 如果没保存过，会返回0，或你也可以判断是否存在
    xAccelOffset_ = preferences_.getShort("xAccelOffset", xAccelOffset_);
    yAccelOffset_ = preferences_.getShort("yAccelOffset", yAccelOffset_);
    zAccelOffset_ = preferences_.getShort("zAccelOffset", zAccelOffset_);
    xGyroOffset_ = preferences_.getShort("xGyroOffset", xGyroOffset_);
    yGyroOffset_ = preferences_.getShort("yGyroOffset", yGyroOffset_);
    zGyroOffset_ = preferences_.getShort("zGyroOffset", zGyroOffset_);
    preferences_.end();

    mpu_.setXAccelOffset(xAccelOffset_);
    mpu_.setYAccelOffset(yAccelOffset_);
    mpu_.setZAccelOffset(zAccelOffset_);
    mpu_.setXGyroOffset(xGyroOffset_);
    mpu_.setYGyroOffset(yGyroOffset_);
    mpu_.setZGyroOffset(zGyroOffset_);
}

void MPU6050Control::save_config() {
    if (name_.empty()) {
        serial_print("MPU6050Control name is empty, cannot save config.");
        return;
    }

    preferences_.begin(std::string(name_ + "config").c_str(), false);
    preferences_.clear();
    preferences_.putInt("pinSDA", pin_SDA_);
    preferences_.putInt("pinSCL", pin_SCL_);
    preferences_.end();
}

void MPU6050Control::load_config() {
    if (name_.empty()) {
        serial_print("MPU6050Control name is empty, cannot load config.");
        return;
    }

    preferences_.begin(std::string(name_ + "config").c_str(), true); // 只读模式
    auto pin_SDA = preferences_.getInt("pinSDA", pin_SDA_);
    auto pin_SCL = preferences_.getInt("pinSCL", pin_SCL_);
    preferences_.end();

    set_pins(pin_SDA, pin_SCL);
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

    yaw_ = -ypr[0];
    pitch_ = ypr[1];
    roll_ = ypr[2];

    gyroX_ = gyro.x / 131.0f * M_PI / 180.0f; // 转为弧度制
    gyroY_ = gyro.y / 131.0f * M_PI / 180.0f;
    gyroZ_ = -gyro.z / 131.0f * M_PI / 180.0f;
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
    float ax = (int16_t)((data_[0] << 8) | data_[1]) / 16384.0f;
    float ay = (int16_t)((data_[2] << 8) | data_[3]) / 16384.0f;
    float az = (int16_t)((data_[4] << 8) | data_[5]) / 16384.0f;

    gyroX_ = (int16_t)((data_[8] << 8) | data_[9]) / 131.0f; // °/s
    gyroY_ = (int16_t)((data_[10] << 8) | data_[11]) / 131.0f;
    gyroZ_ = (int16_t)((data_[12] << 8) | data_[13]) / 131.0f;

    // 3. 计算时间差
    unsigned long now = micros();
    float dt = (now - last_update_time_) / 1e6f; // 秒
    last_update_time_ = now;

    // 5. 陀螺仪积分更新欧拉角
    pitch_ += gyroY_ * dt; // Y轴角速度 → pitch
    roll_ += gyroX_ * dt;  // X轴角速度 → roll
    yaw_ += gyroZ_ * dt;   // Z轴角速度 → yaw（会漂移）

    // 6. 互补滤波融合加速度计（修正漂移）
    pitch_ = ALPHA * pitch_ + (1 - ALPHA) * atan2(-ax, sqrt(ay * ay + az * az)) * 180.0f / M_PI;
    roll_ = ALPHA * roll_ + (1 - ALPHA) * atan2(ay, az) * 180.0f / M_PI;
}

void MPU6050Control::get_data(float &gyroX, float &gyroY, float &gyroZ, float &yaw, float &pitch, float &roll) {
    gyroX = gyroX_;
    gyroY = gyroY_;
    gyroZ = gyroZ_;
    yaw = yaw_;
    pitch = pitch_;
    roll = roll_;
}
