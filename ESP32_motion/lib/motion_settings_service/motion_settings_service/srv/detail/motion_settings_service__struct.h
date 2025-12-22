// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motion_settings_service:srv/MotionSettingsService.idl
// generated code does not contain a copyright notice

#ifndef MOTION_SETTINGS_SERVICE__SRV__DETAIL__MOTION_SETTINGS_SERVICE__STRUCT_H_
#define MOTION_SETTINGS_SERVICE__SRV__DETAIL__MOTION_SETTINGS_SERVICE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/MotionSettingsService in the package motion_settings_service.
typedef struct motion_settings_service__srv__MotionSettingsService_Request
{
  uint64_t id;
  int32_t mode;
  int32_t milliseconds;
  float speed_percent;
  float max_v;
  float max_acc;
  float jerk;
  float wheel_width;
  float track_width;
  int32_t left_front_motor_pina;
  int32_t left_front_motor_pinb;
  int32_t left_front_motor_pinpwm;
  int32_t left_front_encoder_pina;
  int32_t left_front_encoder_pinb;
  float left_front_motor_p;
  float left_front_motor_i;
  float left_front_motor_d;
  float left_front_motor_max_total_integral;
  float left_front_motor_wheel_diameter;
  int32_t left_front_motor_pluses_per_revolution;
  int32_t left_front_motor_revolutions_per_minute;
  int32_t left_back_motor_pina;
  int32_t left_back_motor_pinb;
  int32_t left_back_motor_pinpwm;
  int32_t left_back_encoder_pina;
  int32_t left_back_encoder_pinb;
  float left_back_motor_p;
  float left_back_motor_i;
  float left_back_motor_d;
  float left_back_motor_max_total_integral;
  float left_back_motor_wheel_diameter;
  int32_t left_back_motor_pluses_per_revolution;
  int32_t left_back_motor_revolutions_per_minute;
  int32_t right_front_motor_pina;
  int32_t right_front_motor_pinb;
  int32_t right_front_motor_pinpwm;
  int32_t right_front_encoder_pina;
  int32_t right_front_encoder_pinb;
  float right_front_motor_p;
  float right_front_motor_i;
  float right_front_motor_d;
  float right_front_motor_max_total_integral;
  float right_front_motor_wheel_diameter;
  int32_t right_front_motor_pluses_per_revolution;
  int32_t right_front_motor_revolutions_per_minute;
  int32_t right_back_motor_pina;
  int32_t right_back_motor_pinb;
  int32_t right_back_motor_pinpwm;
  int32_t right_back_encoder_pina;
  int32_t right_back_encoder_pinb;
  float right_back_motor_p;
  float right_back_motor_i;
  float right_back_motor_d;
  float right_back_motor_max_total_integral;
  float right_back_motor_wheel_diameter;
  int32_t right_back_motor_pluses_per_revolution;
  int32_t right_back_motor_revolutions_per_minute;
  int32_t mpu6050_pin_sda;
  int32_t mpu6050_pin_scl;
  int16_t mpu6050_accel_offset_x;
  int16_t mpu6050_accel_offset_y;
  int16_t mpu6050_accel_offset_z;
  int16_t mpu6050_gyro_offset_x;
  int16_t mpu6050_gyro_offset_y;
  int16_t mpu6050_gyro_offset_z;
  uint8_t motor_enable_flags;
  bool enable_speed_plan;
  bool is_mecanum_wheel;
} motion_settings_service__srv__MotionSettingsService_Request;

// Struct for a sequence of motion_settings_service__srv__MotionSettingsService_Request.
typedef struct motion_settings_service__srv__MotionSettingsService_Request__Sequence
{
  motion_settings_service__srv__MotionSettingsService_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motion_settings_service__srv__MotionSettingsService_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/MotionSettingsService in the package motion_settings_service.
typedef struct motion_settings_service__srv__MotionSettingsService_Response
{
  uint64_t id;
  int32_t state;
  int32_t milliseconds;
  float speed_percent;
  float max_v;
  float max_acc;
  float jerk;
  float wheel_width;
  float track_width;
  int32_t left_front_motor_pina;
  int32_t left_front_motor_pinb;
  int32_t left_front_motor_pinpwm;
  int32_t left_front_encoder_pina;
  int32_t left_front_encoder_pinb;
  float left_front_motor_p;
  float left_front_motor_i;
  float left_front_motor_d;
  float left_front_motor_max_total_integral;
  float left_front_motor_wheel_diameter;
  int32_t left_front_motor_pluses_per_revolution;
  int32_t left_front_motor_revolutions_per_minute;
  int32_t left_back_motor_pina;
  int32_t left_back_motor_pinb;
  int32_t left_back_motor_pinpwm;
  int32_t left_back_encoder_pina;
  int32_t left_back_encoder_pinb;
  float left_back_motor_p;
  float left_back_motor_i;
  float left_back_motor_d;
  float left_back_motor_max_total_integral;
  float left_back_motor_wheel_diameter;
  int32_t left_back_motor_pluses_per_revolution;
  int32_t left_back_motor_revolutions_per_minute;
  int32_t right_front_motor_pina;
  int32_t right_front_motor_pinb;
  int32_t right_front_motor_pinpwm;
  int32_t right_front_encoder_pina;
  int32_t right_front_encoder_pinb;
  float right_front_motor_p;
  float right_front_motor_i;
  float right_front_motor_d;
  float right_front_motor_max_total_integral;
  float right_front_motor_wheel_diameter;
  int32_t right_front_motor_pluses_per_revolution;
  int32_t right_front_motor_revolutions_per_minute;
  int32_t right_back_motor_pina;
  int32_t right_back_motor_pinb;
  int32_t right_back_motor_pinpwm;
  int32_t right_back_encoder_pina;
  int32_t right_back_encoder_pinb;
  float right_back_motor_p;
  float right_back_motor_i;
  float right_back_motor_d;
  float right_back_motor_max_total_integral;
  float right_back_motor_wheel_diameter;
  int32_t right_back_motor_pluses_per_revolution;
  int32_t right_back_motor_revolutions_per_minute;
  int32_t mpu6050_pin_sda;
  int32_t mpu6050_pin_scl;
  int16_t mpu6050_accel_offset_x;
  int16_t mpu6050_accel_offset_y;
  int16_t mpu6050_accel_offset_z;
  int16_t mpu6050_gyro_offset_x;
  int16_t mpu6050_gyro_offset_y;
  int16_t mpu6050_gyro_offset_z;
  uint8_t motor_enable_flags;
  bool enable_speed_plan;
  bool is_mecanum_wheel;
} motion_settings_service__srv__MotionSettingsService_Response;

// Struct for a sequence of motion_settings_service__srv__MotionSettingsService_Response.
typedef struct motion_settings_service__srv__MotionSettingsService_Response__Sequence
{
  motion_settings_service__srv__MotionSettingsService_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motion_settings_service__srv__MotionSettingsService_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTION_SETTINGS_SERVICE__SRV__DETAIL__MOTION_SETTINGS_SERVICE__STRUCT_H_
