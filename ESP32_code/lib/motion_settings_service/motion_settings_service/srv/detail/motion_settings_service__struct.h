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
  int32_t mode;
  int64_t id;
  uint8_t motor_enable_flags;
  int32_t milliseconds;
  int32_t position_loop_milliseconds_cnt;
  int32_t speed_loop_milliseconds_cnt;
  bool enable_speed_plan;
  bool is_mecanum_wheel;
  bool enable_pub_motion_status;
  float speed_percent;
  float max_v;
  float max_acc;
  float jerk;
  float wheel_width;
  float track_width;
  float position_p;
  float position_i;
  float position_d;
  float position_max_total_integral;
  float line_speed_p;
  float line_speed_i;
  float line_speed_d;
  float line_speed_max_total_integral;
  float angle_speed_p;
  float angle_speed_i;
  float angle_speed_d;
  float angle_speed_max_total_integral;
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
  int32_t state;
  int64_t id;
  uint8_t motor_enable_flags;
  int32_t milliseconds;
  int32_t position_loop_milliseconds_cnt;
  int32_t speed_loop_milliseconds_cnt;
  bool enable_speed_plan;
  bool is_mecanum_wheel;
  bool enable_pub_motion_status;
  float speed_percent;
  float max_v;
  float max_acc;
  float jerk;
  float wheel_width;
  float track_width;
  float position_p;
  float position_i;
  float position_d;
  float position_max_total_integral;
  float line_speed_p;
  float line_speed_i;
  float line_speed_d;
  float line_speed_max_total_integral;
  float angle_speed_p;
  float angle_speed_i;
  float angle_speed_d;
  float angle_speed_max_total_integral;
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
