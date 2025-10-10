#pragma once
#include "esp_camera.h"
#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>

#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 15
#define SIOD_GPIO_NUM 4
#define SIOC_GPIO_NUM 5

#define Y2_GPIO_NUM 11
#define Y3_GPIO_NUM 9
#define Y4_GPIO_NUM 8
#define Y5_GPIO_NUM 10
#define Y6_GPIO_NUM 12
#define Y7_GPIO_NUM 18
#define Y8_GPIO_NUM 17
#define Y9_GPIO_NUM 16

#define VSYNC_GPIO_NUM 6
#define HREF_GPIO_NUM 7
#define PCLK_GPIO_NUM 13
#define XCLK_FREQ_HZ 20000000

// 摄像头运行时参数（可动态修改）

typedef struct {
    // int milliseconds;
    // pixformat_t pixformat;     // 像素格式（直接使用驱动定义的枚举）
    // framesize_t framesize;     // 帧大小（直接使用驱动定义的枚举）
    // int contrast;              // 对比度（-2 到 +2）
    // int brightness;            // 亮度（-2 到 +2）
    // int saturation;            // 饱和度（-2 到 +2）
    // int sharpness;             // 锐度（-2 到 +2）
    // int denoise;               // 降噪等级（0-6）
    // gainceiling_t gainceiling; // 增益上限（使用驱动定义的枚举）
    // int quality;               // 图像质量（0-63）
    // int colorbar;              // 彩条测试（0=禁用，1=启用）
    // int whitebal;              // 白平衡（0=禁用，1=启用）
    // int gain_ctrl;             // 增益控制（0=禁用，1=启用）
    // int exposure_ctrl;         // 曝光控制（0=禁用，1=启用）
    // int hmirror;               // 水平镜像（0=禁用，1=启用）
    // int vflip;                 // 垂直翻转（0=禁用，1=启用）
    // int aec2;                  // 高级曝光控制（0=禁用，1=启用）
    // int awb_gain;              // 白平衡增益（0=禁用，1=启用）
    // int agc_gain;              // 自动增益值（0-31）
    // int aec_value;             // 自动曝光值（0-1200）
    // int special_effect;        // 特殊效果（0-6，如 0=正常、1=负片）
    // int wb_mode;               // 白平衡模式（0-4）
    // int ae_level;              // 曝光补偿（-2 到 +2）
    // int dcw;                   // 数字裁剪白平衡（0=禁用，1=启用）
    // int bpc;                   // 坏点校正（0=禁用，1=启用）
    // int wpc;                   // 白点校正（0=禁用，1=启用）
    // int raw_gma;               // 原始图像 GMA（0=禁用，1=启用）
    // int lenc;                  // 镜头校正（0=禁用，1=启用）
    int16_t milliseconds = 40; // 延时毫秒数（用于定时拍照）
    camera_status_t status;
    pixformat_t pixformat; // 像素格式

} camera_params_t;

class ESP32Cam {
private:
    ESP32Cam();
    ~ESP32Cam();

public:
    ESP32Cam(const ESP32Cam &) = delete;
    ESP32Cam &operator=(const ESP32Cam &) = delete;

    static ESP32Cam &get_instance();
    void init(bool load = true);
    bool isInit();

    camera_fb_t *capture_photo();
    void release_photo(camera_fb_t *fb);

    const camera_params_t &set_params(const camera_params_t &params);
    const camera_params_t &get_params();
    void save_params();
    void load_params();

    void set_config(const camera_config_t &config);
    const camera_config_t &get_config();
    void save_config();
    void load_config();

private:
    camera_config_t config_;
    camera_params_t params_;

    Preferences preferences_;

    void _set_params();
    void _set_config();

    sensor_t *sensor_ = nullptr;
};