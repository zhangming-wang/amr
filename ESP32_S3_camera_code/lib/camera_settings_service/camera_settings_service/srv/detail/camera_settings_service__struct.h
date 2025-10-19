// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from camera_settings_service:srv/CameraSettingsService.idl
// generated code does not contain a copyright notice

#ifndef CAMERA_SETTINGS_SERVICE__SRV__DETAIL__CAMERA_SETTINGS_SERVICE__STRUCT_H_
#define CAMERA_SETTINGS_SERVICE__SRV__DETAIL__CAMERA_SETTINGS_SERVICE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/CameraSettingsService in the package camera_settings_service.
typedef struct camera_settings_service__srv__CameraSettingsService_Request
{
  int64_t id;
  /// XCLK时钟频率（Hz）
  int32_t xclk_freq_hz;
  /// 延时参数（毫秒）
  int16_t milliseconds;
  /// 自动曝光值（0-1200）
  int16_t aec_value;
  int8_t mode;
  /// 摄像头硬件配置参数（初始化时生效）
  /// GPIO引脚：摄像头电源关闭线
  int8_t pin_pwdn;
  /// GPIO引脚：摄像头复位线
  int8_t pin_reset;
  /// GPIO引脚：摄像头XCLK时钟线
  int8_t pin_xclk;
  /// GPIO引脚：摄像头SDA线（I2C数据）
  int8_t pin_sccb_sda;
  /// GPIO引脚：摄像头SCL线（I2C时钟）
  int8_t pin_sccb_scl;
  /// GPIO引脚：摄像头D7数据线
  int8_t pin_d7;
  /// GPIO引脚：摄像头D6数据线
  int8_t pin_d6;
  /// GPIO引脚：摄像头D5数据线
  int8_t pin_d5;
  /// GPIO引脚：摄像头D4数据线
  int8_t pin_d4;
  /// GPIO引脚：摄像头D3数据线
  int8_t pin_d3;
  /// GPIO引脚：摄像头D2数据线
  int8_t pin_d2;
  /// GPIO引脚：摄像头D1数据线
  int8_t pin_d1;
  /// GPIO引脚：摄像头D0数据线
  int8_t pin_d0;
  /// GPIO引脚：摄像头VSYNC线
  int8_t pin_vsync;
  /// GPIO引脚：摄像头HREF线
  int8_t pin_href;
  /// GPIO引脚：摄像头PCLK线
  int8_t pin_pclk;
  /// 用于生成XCLK的LEDC定时器（枚举值转int）
  int8_t ledc_timer;
  /// 用于生成XCLK的LEDC通道（枚举值转int）
  int8_t ledc_channel;
  /// 像素格式（PIXFORMAT_*枚举值转int）
  int8_t pixel_format;
  /// 输出图像尺寸（FRAMESIZE_*枚举值转int）
  int8_t frame_size;
  /// JPEG输出质量（0-63，值越小质量越高）
  int8_t jpeg_quality;
  /// 帧缓冲区数量
  int8_t fb_count;
  /// 帧缓冲区分配位置（camera_fb_location_t枚举值转int）
  int8_t fb_location;
  /// 缓冲区填充时机（camera_grab_mode_t枚举值转int）
  int8_t grab_mode;
  /// RGB<->YUV转换模式（camera_conv_mode_t枚举值转int，可选）
  int8_t conv_mode;
  /// SCCB I2C总线端口号（若pin_sccb_sda为-1时使用）
  int8_t sccb_i2c_port;
  /// 摄像头运行时参数（可动态调节）
  /// 像素格式（PIXFORMAT_*枚举值转int）
  int8_t pixformat;
  /// 帧大小（FRAMESIZE_*枚举值转int）
  int8_t framesize;
  /// 图像质量（0-63）
  int8_t quality;
  /// 亮度（-2到+2）
  int8_t brightness;
  /// 对比度（-2到+2）
  int8_t contrast;
  /// 饱和度（-2到+2）
  int8_t saturation;
  /// 锐度（-2到+2）
  int8_t sharpness;
  /// 降噪等级（0-6）
  int8_t denoise;
  /// 特殊效果（0-6，如0=正常、1=负片）
  int8_t special_effect;
  /// 白平衡模式（0-4）
  int8_t wb_mode;
  /// 白平衡（0=禁用，1=启用）
  int8_t awb;
  /// 白平衡增益（0=禁用，1=启用）
  int8_t awb_gain;
  /// 曝光控制（0=禁用，1=启用）
  int8_t aec;
  /// 高级曝光控制（0=禁用，1=启用）
  int8_t aec2;
  /// 曝光补偿（-2到+2）
  int8_t ae_level;
  /// 增益控制（0=禁用，1=启用）
  int8_t agc;
  /// 自动增益值（0-31）
  int8_t agc_gain;
  /// 增益上限（gainceiling_t枚举值转int）
  int8_t gainceiling;
  /// 坏点校正（0=禁用，1=启用）
  int8_t bpc;
  /// 白点校正（0=禁用，1=启用）
  int8_t wpc;
  /// 原始图像GMA（0=禁用，1=启用）
  int8_t raw_gma;
  /// 镜头校正（0=禁用，1=启用）
  int8_t lenc;
  /// 水平镜像（0=禁用，1=启用）
  int8_t hmirror;
  /// 垂直翻转（0=禁用，1=启用）
  int8_t vflip;
  /// 数字裁剪白平衡（0=禁用，1=启用）
  int8_t dcw;
  /// 彩条测试（0=禁用，1=启用）
  int8_t colorbar;
  /// 是否启用连续拍摄模式
  bool enable_series_capture;
} camera_settings_service__srv__CameraSettingsService_Request;

// Struct for a sequence of camera_settings_service__srv__CameraSettingsService_Request.
typedef struct camera_settings_service__srv__CameraSettingsService_Request__Sequence
{
  camera_settings_service__srv__CameraSettingsService_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} camera_settings_service__srv__CameraSettingsService_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/CameraSettingsService in the package camera_settings_service.
typedef struct camera_settings_service__srv__CameraSettingsService_Response
{
  /// 响应部分（Response）
  /// 执行结果状态
  int64_t id;
  /// 当前XCLK时钟频率（Hz）
  int32_t xclk_freq_hz;
  /// 延时参数（毫秒）
  int16_t milliseconds;
  /// 自动曝光值（0-1200）
  int16_t aec_value;
  int8_t state;
  /// 当前使用的电源关闭线引脚
  int8_t pin_pwdn;
  /// 当前使用的复位线引脚
  int8_t pin_reset;
  /// 当前使用的XCLK时钟线引脚
  int8_t pin_xclk;
  /// 当前使用的SDA线引脚
  int8_t pin_sccb_sda;
  /// 当前使用的SCL线引脚
  int8_t pin_sccb_scl;
  /// 当前使用的D7数据线引脚
  int8_t pin_d7;
  /// 当前使用的D6数据线引脚
  int8_t pin_d6;
  /// 当前使用的D5数据线引脚
  int8_t pin_d5;
  /// 当前使用的D4数据线引脚
  int8_t pin_d4;
  /// 当前使用的D3数据线引脚
  int8_t pin_d3;
  /// 当前使用的D2数据线引脚
  int8_t pin_d2;
  /// 当前使用的D1数据线引脚
  int8_t pin_d1;
  /// 当前使用的D0数据线引脚
  int8_t pin_d0;
  /// 当前使用的VSYNC线引脚
  int8_t pin_vsync;
  /// 当前使用的HREF线引脚
  int8_t pin_href;
  /// 当前使用的PCLK线引脚
  int8_t pin_pclk;
  /// 当前使用的LEDC定时器
  int8_t ledc_timer;
  /// 当前使用的LEDC通道
  int8_t ledc_channel;
  /// 当前像素格式
  int8_t pixel_format;
  /// 当前输出图像尺寸
  int8_t frame_size;
  /// 当前JPEG输出质量
  int8_t jpeg_quality;
  /// 当前帧缓冲区数量
  int8_t fb_count;
  /// 当前帧缓冲区分配位置
  int8_t fb_location;
  /// 当前缓冲区填充时机
  int8_t grab_mode;
  /// 当前RGB<->YUV转换模式
  int8_t conv_mode;
  /// 当前SCCB I2C总线端口号
  int8_t sccb_i2c_port;
  /// 像素格式（PIXFORMAT_*枚举值转int）
  int8_t pixformat;
  /// 帧大小（FRAMESIZE_*枚举值转int）
  int8_t framesize;
  /// 图像质量（0-63）
  int8_t quality;
  /// 亮度（-2到+2）
  int8_t brightness;
  /// 对比度（-2到+2）
  int8_t contrast;
  /// 饱和度（-2到+2）
  int8_t saturation;
  /// 锐度（-2到+2）
  int8_t sharpness;
  /// 降噪等级（0-6）
  int8_t denoise;
  /// 特殊效果（0-6，如0=正常、1=负片）
  int8_t special_effect;
  /// 白平衡模式（0-4）
  int8_t wb_mode;
  /// 白平衡（0=禁用，1=启用）
  int8_t awb;
  /// 白平衡增益（0=禁用，1=启用）
  int8_t awb_gain;
  /// 曝光控制（0=禁用，1=启用）
  int8_t aec;
  /// 高级曝光控制（0=禁用，1=启用）
  int8_t aec2;
  /// 曝光补偿（-2到+2）
  int8_t ae_level;
  /// 增益控制（0=禁用，1=启用）
  int8_t agc;
  /// 自动增益值（0-31）
  int8_t agc_gain;
  /// 增益上限（gainceiling_t枚举值转int）
  int8_t gainceiling;
  /// 坏点校正（0=禁用，1=启用）
  int8_t bpc;
  /// 白点校正（0=禁用，1=启用）
  int8_t wpc;
  /// 原始图像GMA（0=禁用，1=启用）
  int8_t raw_gma;
  /// 镜头校正（0=禁用，1=启用）
  int8_t lenc;
  /// 水平镜像（0=禁用，1=启用）
  int8_t hmirror;
  /// 垂直翻转（0=禁用，1=启用）
  int8_t vflip;
  /// 数字裁剪白平衡（0=禁用，1=启用）
  int8_t dcw;
  /// 彩条测试（0=禁用，1=启用）
  int8_t colorbar;
  /// 当前连续拍摄模式状态
  bool enable_series_capture;
} camera_settings_service__srv__CameraSettingsService_Response;

// Struct for a sequence of camera_settings_service__srv__CameraSettingsService_Response.
typedef struct camera_settings_service__srv__CameraSettingsService_Response__Sequence
{
  camera_settings_service__srv__CameraSettingsService_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} camera_settings_service__srv__CameraSettingsService_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAMERA_SETTINGS_SERVICE__SRV__DETAIL__CAMERA_SETTINGS_SERVICE__STRUCT_H_
