#include "esp32cam.h"

ESP32Cam::ESP32Cam() {
}

ESP32Cam::~ESP32Cam() {
}

ESP32Cam &ESP32Cam::get_instance() {
    static ESP32Cam esp32Cam;
    return esp32Cam;
}

void ESP32Cam::init(bool load) {
    if (sensor_) {
        esp_err_t err = esp_camera_deinit();
        if (err != ESP_OK) {
            Serial.printf("Failed to deinit camera: %d\n", err);
        }
        sensor_ = nullptr;
    }

    if (load)
        load_config();

    esp_err_t err = esp_camera_init(&config_);
    if (err != ESP_OK) {
        sensor_ = nullptr;
        Serial.printf("摄像头初始化失败，错误代码: 0x%x\n", err);
        return;
    }
    sensor_ = esp_camera_sensor_get();
    if (!sensor_) {
        Serial.println("无法获取摄像头传感器");
        return;
    }

    if (load)
        load_params();
    else
        _set_params();

    Serial.println("摄像头初始化成功");
}

bool ESP32Cam::isInit() {
    return sensor_ != nullptr;
}

camera_fb_t *ESP32Cam::capture_photo() {
    if (!sensor_)
        return nullptr; // 摄像头未初始化

    camera_fb_t *fb = esp_camera_fb_get(); // 获取帧缓冲
    if (!fb) {
        Serial.println("Failed to get camera frame!");
        return nullptr;
    }
    return fb;
}
void ESP32Cam::release_photo(camera_fb_t *fb) {
    if (fb) {
        esp_camera_fb_return(fb);
    }
}

const camera_params_t &ESP32Cam::set_params(const camera_params_t &params) {
    if (!sensor_)
        return params_; // 确保摄像头已初始化

    params_ = params;
    _set_params();

    return params_;
}

const camera_params_t &ESP32Cam::get_params() {
    return params_;
}

void ESP32Cam::save_params() {
    preferences_.begin("camSet", false);
    preferences_.putShort("milliseconds", params_.milliseconds);
    // 1. 基础画质参数
    preferences_.putShort("brightness", params_.status.brightness);
    preferences_.putShort("contrast", params_.status.contrast);
    preferences_.putShort("saturation", params_.status.saturation);
    preferences_.putShort("sharpness", params_.status.sharpness);
    preferences_.putShort("denoise", params_.status.denoise);

    // 2. 图像格式与尺寸参数
    preferences_.putShort("pixformat", static_cast<int>(params_.pixformat));
    preferences_.putShort("framesize", static_cast<int>(params_.status.framesize));
    preferences_.putShort("quality", params_.status.quality);

    // 3. 曝光与增益参数
    preferences_.putShort("gainceiling", static_cast<int>(params_.status.gainceiling));
    preferences_.putShort("agc_gain", params_.status.agc_gain);
    preferences_.putShort("aec_value", params_.status.aec_value);
    preferences_.putShort("ae_level", params_.status.ae_level);

    // 4. 白平衡与色彩校正参数（int类型，0=禁用，1=启用）
    preferences_.putShort("awb", params_.status.awb);
    preferences_.putShort("awb_gain", params_.status.awb_gain);
    preferences_.putShort("wb_mode", params_.status.wb_mode);
    preferences_.putShort("dcw", params_.status.dcw);
    preferences_.putShort("bpc", params_.status.bpc);
    preferences_.putShort("wpc", params_.status.wpc);
    preferences_.putShort("raw_gma", params_.status.raw_gma);

    // 5. 图像变换与特效参数（int类型，0=禁用，1=启用）
    preferences_.putShort("hmirror", params_.status.hmirror);
    preferences_.putShort("vflip", params_.status.vflip);
    preferences_.putShort("special_effect", params_.status.special_effect);
    preferences_.putShort("colorbar", params_.status.colorbar);

    // 6. 功能控制开关（int类型，0=禁用，1=启用）
    preferences_.putShort("agc", params_.status.agc);
    preferences_.putShort("aec", params_.status.aec);
    preferences_.putShort("aec2", params_.status.aec2);
    preferences_.putShort("lenc", params_.status.lenc);

    preferences_.end();
}

void ESP32Cam::load_params() {
    preferences_.begin("camSet", true);
    params_.milliseconds = preferences_.getShort("milliseconds", params_.milliseconds);

    // 1. 基础画质参数
    params_.status.brightness = preferences_.getShort("brightness", sensor_->status.brightness);
    params_.status.contrast = preferences_.getShort("contrast", sensor_->status.contrast);
    params_.status.saturation = preferences_.getShort("saturation", sensor_->status.saturation);
    params_.status.sharpness = preferences_.getShort("sharpness", sensor_->status.sharpness);
    params_.status.denoise = preferences_.getShort("denoise", sensor_->status.denoise);

    // 2. 图像格式与尺寸参数
    params_.pixformat = static_cast<pixformat_t>(preferences_.getShort("pixformat", sensor_->pixformat));
    params_.status.framesize = static_cast<framesize_t>(preferences_.getShort("framesize", sensor_->status.framesize));
    params_.status.quality = preferences_.getShort("quality", sensor_->status.quality);

    // 3. 曝光与增益参数
    params_.status.gainceiling = static_cast<gainceiling_t>(preferences_.getShort("gainceiling", sensor_->status.gainceiling));
    params_.status.agc_gain = preferences_.getShort("agc_gain", sensor_->status.agc_gain);
    params_.status.aec_value = preferences_.getShort("aec_value", sensor_->status.aec_value);
    params_.status.ae_level = preferences_.getShort("ae_level", sensor_->status.ae_level);

    // 4. 白平衡与色彩校正参数（直接使用int，0=禁用，1=启用）
    params_.status.awb = preferences_.getShort("awb", sensor_->status.awb);
    params_.status.awb_gain = preferences_.getShort("awb_gain", sensor_->status.awb_gain);
    params_.status.wb_mode = preferences_.getShort("wb_mode", sensor_->status.wb_mode);
    params_.status.dcw = preferences_.getShort("dcw", sensor_->status.dcw);
    params_.status.bpc = preferences_.getShort("bpc", sensor_->status.bpc);
    params_.status.wpc = preferences_.getShort("wpc", sensor_->status.wpc);
    params_.status.raw_gma = preferences_.getShort("raw_gma", sensor_->status.raw_gma);

    // 5. 图像变换与特效参数（直接使用int，0=禁用，1=启用）
    params_.status.hmirror = preferences_.getShort("hmirror", sensor_->status.hmirror);
    params_.status.vflip = preferences_.getShort("vflip", sensor_->status.vflip);
    params_.status.special_effect = preferences_.getShort("special_effect", sensor_->status.special_effect);
    params_.status.colorbar = preferences_.getShort("colorbar", sensor_->status.colorbar);

    // 6. 功能控制开关（直接使用int，0=禁用，1=启用）
    params_.status.agc = preferences_.getShort("agc", sensor_->status.agc);
    params_.status.aec = preferences_.getShort("aec", sensor_->status.aec);
    params_.status.aec2 = preferences_.getShort("aec2", sensor_->status.aec2);
    params_.status.lenc = preferences_.getShort("lenc", sensor_->status.lenc);

    preferences_.end();

    _set_params();
}

void ESP32Cam::_set_params() {
    if (!sensor_)
        return;

    // 1. 基础画质参数
    if (params_.status.brightness != sensor_->status.brightness) {
        auto ret = sensor_->set_brightness(sensor_, params_.status.brightness);
        if (ret != 0)
            Serial.printf("Failed to set brightness: %d\n", ret);
    }

    if (params_.status.contrast != sensor_->status.contrast) {
        auto ret = sensor_->set_contrast(sensor_, params_.status.contrast);
        if (ret != 0)
            Serial.printf("Failed to set contrast: %d\n", ret);
    }

    if (params_.status.saturation != sensor_->status.saturation) {
        auto ret = sensor_->set_saturation(sensor_, params_.status.saturation);
        if (ret != 0)
            Serial.printf("Failed to set saturation: %d\n", ret);
    }

    if (params_.status.sharpness != sensor_->status.sharpness) {
        auto ret = sensor_->set_sharpness(sensor_, params_.status.sharpness);
        if (ret != 0)
            Serial.printf("Failed to set sharpness: %d\n", ret);
    }

    if (params_.status.denoise != sensor_->status.denoise) {
        auto ret = sensor_->set_denoise(sensor_, params_.status.denoise);
        if (ret != 0)
            Serial.printf("Failed to set denoise: %d\n", ret);
    }

    // 2. 图像格式与尺寸
    if (static_cast<pixformat_t>(params_.pixformat) != sensor_->pixformat) {
        auto ret = sensor_->set_pixformat(sensor_, static_cast<pixformat_t>(params_.pixformat));
        if (ret != 0)
            Serial.printf("Failed to set pixformat: %d\n", ret);
    }

    if (params_.status.framesize != sensor_->status.framesize) {
        auto ret = sensor_->set_framesize(sensor_, static_cast<framesize_t>(params_.status.framesize));
        if (ret != 0)
            Serial.printf("Failed to set framesize: %d\n", ret);
        else {
            Serial.printf("success to set framesize: %d\n", ret);
        }
    }

    if (params_.status.quality != sensor_->status.quality) {
        auto ret = sensor_->set_quality(sensor_, params_.status.quality);
        if (ret != 0)
            Serial.printf("Failed to set quality: %d\n", ret);
    }

    // 3. 曝光与增益
    if (params_.status.gainceiling != sensor_->status.gainceiling) {
        auto ret = sensor_->set_gainceiling(sensor_, static_cast<gainceiling_t>(params_.status.gainceiling));
        if (ret != 0)
            Serial.printf("Failed to set gainceiling: %d\n", ret);
    }

    if (params_.status.agc != sensor_->status.agc) {
        auto ret = sensor_->set_gain_ctrl(sensor_, params_.status.agc);
        if (ret != 0)
            Serial.printf("Failed to set gain_ctrl: %d\n", ret);
    }

    if (params_.status.aec != sensor_->status.aec) {
        auto ret = sensor_->set_exposure_ctrl(sensor_, params_.status.aec);
        if (ret != 0)
            Serial.printf("Failed to set exposure_ctrl: %d\n", ret);
    }

    if (params_.status.aec2 != sensor_->status.aec2) {
        auto ret = sensor_->set_aec2(sensor_, params_.status.aec2);
        if (ret != 0)
            Serial.printf("Failed to set aec2: %d\n", ret);
    }

    if (params_.status.agc_gain != sensor_->status.agc_gain) {
        auto ret = sensor_->set_agc_gain(sensor_, params_.status.agc_gain);
        if (ret != 0)
            Serial.printf("Failed to set agc_gain: %d\n", ret);
    }

    if (params_.status.aec_value != sensor_->status.aec_value) {
        auto ret = sensor_->set_aec_value(sensor_, params_.status.aec_value);
        if (ret != 0)
            Serial.printf("Failed to set aec_value: %d\n", ret);
    }

    if (params_.status.ae_level != sensor_->status.ae_level) {
        auto ret = sensor_->set_ae_level(sensor_, params_.status.ae_level);
        if (ret != 0)
            Serial.printf("Failed to set ae_level: %d\n", ret);
    }

    // 4. 白平衡与色彩校正
    if (params_.status.awb != sensor_->status.awb) {
        auto ret = sensor_->set_whitebal(sensor_, params_.status.awb);
        if (ret != 0)
            Serial.printf("Failed to set whitebal: %d\n", ret);
    }

    if (params_.status.awb_gain != sensor_->status.awb_gain) {
        auto ret = sensor_->set_awb_gain(sensor_, params_.status.awb_gain);
        if (ret != 0)
            Serial.printf("Failed to set awb_gain: %d\n", ret);
    }

    if (params_.status.wb_mode != sensor_->status.wb_mode) {
        auto ret = sensor_->set_wb_mode(sensor_, params_.status.wb_mode);
        if (ret != 0)
            Serial.printf("Failed to set wb_mode: %d\n", ret);
    }

    if (params_.status.dcw != sensor_->status.dcw) {
        auto ret = sensor_->set_dcw(sensor_, params_.status.dcw);
        if (ret != 0)
            Serial.printf("Failed to set dcw: %d\n", ret);
    }

    if (params_.status.bpc != sensor_->status.bpc) {
        auto ret = sensor_->set_bpc(sensor_, params_.status.bpc);
        if (ret != 0)
            Serial.printf("Failed to set bpc: %d\n", ret);
    }

    if (params_.status.wpc != sensor_->status.wpc) {
        auto ret = sensor_->set_wpc(sensor_, params_.status.wpc);
        if (ret != 0)
            Serial.printf("Failed to set wpc: %d\n", ret);
    }

    if (params_.status.raw_gma != sensor_->status.raw_gma) {
        auto ret = sensor_->set_raw_gma(sensor_, params_.status.raw_gma);
        if (ret != 0)
            Serial.printf("Failed to set raw_gma: %d\n", ret);
    }

    // 5. 图像变换与特效
    if (params_.status.hmirror != sensor_->status.hmirror) {
        auto ret = sensor_->set_hmirror(sensor_, params_.status.hmirror);
        if (ret != 0)
            Serial.printf("Failed to set hmirror: %d\n", ret);
    }

    if (params_.status.vflip != sensor_->status.vflip) {
        auto ret = sensor_->set_vflip(sensor_, params_.status.vflip);
        if (ret != 0)
            Serial.printf("Failed to set vflip: %d\n", ret);
    }

    if (params_.status.special_effect != sensor_->status.special_effect) {
        auto ret = sensor_->set_special_effect(sensor_, params_.status.special_effect);
        if (ret != 0)
            Serial.printf("Failed to set special_effect: %d\n", ret);
    }

    if (params_.status.colorbar != sensor_->status.colorbar) {
        auto ret = sensor_->set_colorbar(sensor_, params_.status.colorbar);
        if (ret != 0)
            Serial.printf("Failed to set colorbar: %d\n", ret);
    }

    // 6. 镜头校正
    if (params_.status.lenc != sensor_->status.lenc) {
        auto ret = sensor_->set_lenc(sensor_, params_.status.lenc);
        if (ret != 0)
            Serial.printf("Failed to set lenc: %d\n", ret);
    }

    params_.status = sensor_->status; // 更新状态
    params_.pixformat = sensor_->pixformat;
}

void ESP32Cam::set_config(const camera_config_t &config) {
    if (!sensor_)
        return; // 确保摄像头已初始化

    config_ = config;
    _set_config();
}

const camera_config_t &ESP32Cam::get_config() {
    return config_;
}

void ESP32Cam::save_config() {
    preferences_.begin("camCfg", false);
    preferences_.putInt("pin_pwdn", config_.pin_pwdn);
    preferences_.putInt("pin_reset", config_.pin_reset);
    preferences_.putInt("pin_xclk", config_.pin_xclk);
    preferences_.putInt("pin_sccb_sda", config_.pin_sccb_sda);
    preferences_.putInt("pin_sccb_scl", config_.pin_sccb_scl);
    preferences_.putInt("pin_d7", config_.pin_d7);
    preferences_.putInt("pin_d6", config_.pin_d6);
    preferences_.putInt("pin_d5", config_.pin_d5);
    preferences_.putInt("pin_d4", config_.pin_d4);
    preferences_.putInt("pin_d3", config_.pin_d3);
    preferences_.putInt("pin_d2", config_.pin_d2);
    preferences_.putInt("pin_d1", config_.pin_d1);
    preferences_.putInt("pin_d0", config_.pin_d0);
    preferences_.putInt("pin_vsync", config_.pin_vsync);
    preferences_.putInt("pin_href", config_.pin_href);
    preferences_.putInt("pin_pclk", config_.pin_pclk);
    preferences_.putInt("xclk_freq_hz", config_.xclk_freq_hz);
    preferences_.putInt("ledc_timer", config_.ledc_timer);
    preferences_.putInt("ledc_channel", config_.ledc_channel);
    preferences_.putInt("pixel_format", config_.pixel_format);
    preferences_.putInt("frame_size", config_.frame_size);
    preferences_.putInt("jpeg_quality", config_.jpeg_quality);
    preferences_.putInt("fb_count", config_.fb_count);
    preferences_.putInt("fb_location", config_.fb_location);
    preferences_.putInt("grab_mode", config_.grab_mode);
#if CONFIG_CAMERA_CONVERTER_ENABLED
    preferences_.putInt("conv_mode", config_.conv_mode);
#endif
    preferences_.putInt("sccb_i2c_port", config_.sccb_i2c_port);
    preferences_.end();
}

void ESP32Cam::load_config() {
    config_.ledc_channel = LEDC_CHANNEL_0;
    config_.ledc_timer = LEDC_TIMER_0;

    // 数_据引脚配置
    config_.pin_d0 = Y2_GPIO_NUM; // D0
    config_.pin_d1 = Y3_GPIO_NUM; // D1
    config_.pin_d2 = Y4_GPIO_NUM; // D2
    config_.pin_d3 = Y5_GPIO_NUM; // D3
    config_.pin_d4 = Y6_GPIO_NUM; // D4
    config_.pin_d5 = Y7_GPIO_NUM; // D5
    config_.pin_d6 = Y8_GPIO_NUM; // D6
    config_.pin_d7 = Y9_GPIO_NUM; // D7

    // 控_制引脚配置
    config_.pin_xclk = XCLK_GPIO_NUM;
    config_.pin_pclk = PCLK_GPIO_NUM;
    config_.pin_vsync = VSYNC_GPIO_NUM;
    config_.pin_href = HREF_GPIO_NUM;
    config_.pin_sccb_sda = SIOD_GPIO_NUM; // SDA
    config_.pin_sccb_scl = SIOC_GPIO_NUM; // SCL
    config_.pin_pwdn = PWDN_GPIO_NUM;
    config_.pin_reset = RESET_GPIO_NUM;
    config_.xclk_freq_hz = XCLK_FREQ_HZ;

    preferences_.begin("camCfg", true);
    config_.pin_pwdn = preferences_.getInt("pin_pwdn", config_.pin_pwdn);
    config_.pin_reset = preferences_.getInt("pin_reset", config_.pin_reset);
    config_.pin_xclk = preferences_.getInt("pin_xclk", config_.pin_xclk);
    config_.pin_sccb_sda = preferences_.getInt("pin_sccb_sda", config_.pin_sccb_sda);
    config_.pin_sccb_scl = preferences_.getInt("pin_sccb_scl", config_.pin_sccb_scl);
    config_.pin_d7 = preferences_.getInt("pin_d7", config_.pin_d7);
    config_.pin_d6 = preferences_.getInt("pin_d6", config_.pin_d6);
    config_.pin_d5 = preferences_.getInt("pin_d5", config_.pin_d5);
    config_.pin_d4 = preferences_.getInt("pin_d4", config_.pin_d4);
    config_.pin_d3 = preferences_.getInt("pin_d3", config_.pin_d3);
    config_.pin_d2 = preferences_.getInt("pin_d2", config_.pin_d2);
    config_.pin_d1 = preferences_.getInt("pin_d1", config_.pin_d1);
    config_.pin_d0 = preferences_.getInt("pin_d0", config_.pin_d0);
    config_.pin_vsync = preferences_.getInt("pin_vsync", config_.pin_vsync);
    config_.pin_href = preferences_.getInt("pin_href", config_.pin_href);
    config_.pin_pclk = preferences_.getInt("pin_pclk", config_.pin_pclk);
    config_.xclk_freq_hz = preferences_.getInt("xclk_freq_hz", config_.xclk_freq_hz);
    config_.ledc_timer = static_cast<ledc_timer_t>(preferences_.getInt("ledc_timer", LEDC_TIMER_0));
    config_.ledc_channel = static_cast<ledc_channel_t>(preferences_.getInt("ledc_channel", LEDC_CHANNEL_0));
    config_.pixel_format = static_cast<pixformat_t>(preferences_.getInt("pixel_format", PIXFORMAT_JPEG));
    config_.frame_size = static_cast<framesize_t>(preferences_.getInt("frame_size", FRAMESIZE_240X240));
    config_.jpeg_quality = preferences_.getInt("jpeg_quality", 15);

    if (psramFound()) {
        // 打印PSRAM总大小
        Serial.printf("PSRAM总大小: %.2f MB\n", ESP.getPsramSize() / (1024.0 * 1024.0));

        // 打印当前可用PSRAM大小
        size_t free_psram = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
        Serial.printf("可用PSRAM大小: %.2f MB\n", free_psram / (1024.0 * 1024.0));

        config_.fb_count = 3;
        config_.fb_location = CAMERA_FB_IN_PSRAM; // 如果PSRAM可用，使用PSRAM
        config_.grab_mode = CAMERA_GRAB_LATEST;
        Serial.println("PSRAM found, using PSRAM for frame buffer.");
    } else {
        config_.fb_count = 1;
        config_.fb_location = CAMERA_FB_IN_DRAM;
        config_.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
        Serial.println("No PSRAM found, using internal DRAM for frame buffer.");
    }
    config_.fb_count = preferences_.getInt("fb_count", config_.fb_count);
    config_.fb_location = static_cast<camera_fb_location_t>(preferences_.getInt("fb_location", config_.fb_location));
    config_.grab_mode = static_cast<camera_grab_mode_t>(preferences_.getInt("grab_mode", config_.grab_mode));
#if CONFIG_CAMERA_CONVERTER_ENABLED
    config_.conv_mode = static_cast<camera_conv_mode_t>(preferences_.getInt("conv_mode", CONV_DISABLE));
#endif
    config_.sccb_i2c_port = preferences_.getInt("sccb_i2c_port", 0);
    preferences_.end();
}

void ESP32Cam::_set_config() {
    if (!sensor_)
        return; // 确保摄像头已初始化

    init(false);
}
