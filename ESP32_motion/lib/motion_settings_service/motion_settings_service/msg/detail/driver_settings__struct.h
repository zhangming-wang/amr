// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motion_settings_service:msg/DriverSettings.idl
// generated code does not contain a copyright notice

#ifndef MOTION_SETTINGS_SERVICE__MSG__DETAIL__DRIVER_SETTINGS__STRUCT_H_
#define MOTION_SETTINGS_SERVICE__MSG__DETAIL__DRIVER_SETTINGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DriverSettings in the package motion_settings_service.
typedef struct motion_settings_service__msg__DriverSettings
{
  int32_t motor_pina;
  int32_t motor_pinb;
  int32_t motor_pinpwm;
  int32_t encoder_pina;
  int32_t encoder_pinb;
  float p;
  float i;
  float d;
  float max_total_i;
  float k;
  float b;
  float wheel_diameter;
  int32_t pluses_per_revolution;
  int32_t revolutions_per_minute;
  uint32_t dead_pwm;
} motion_settings_service__msg__DriverSettings;

// Struct for a sequence of motion_settings_service__msg__DriverSettings.
typedef struct motion_settings_service__msg__DriverSettings__Sequence
{
  motion_settings_service__msg__DriverSettings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motion_settings_service__msg__DriverSettings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTION_SETTINGS_SERVICE__MSG__DETAIL__DRIVER_SETTINGS__STRUCT_H_
