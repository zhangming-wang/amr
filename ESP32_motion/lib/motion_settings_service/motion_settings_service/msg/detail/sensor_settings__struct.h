// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motion_settings_service:msg/SensorSettings.idl
// generated code does not contain a copyright notice

#ifndef MOTION_SETTINGS_SERVICE__MSG__DETAIL__SENSOR_SETTINGS__STRUCT_H_
#define MOTION_SETTINGS_SERVICE__MSG__DETAIL__SENSOR_SETTINGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/SensorSettings in the package motion_settings_service.
typedef struct motion_settings_service__msg__SensorSettings
{
  int32_t pin_rx;
  int32_t pin_tx;
  int32_t pin_pwm;
  int32_t pin_sda;
  int32_t pin_scl;
  int16_t accel_offset_x;
  int16_t accel_offset_y;
  int16_t accel_offset_z;
  int16_t gyro_offset_x;
  int16_t gyro_offset_y;
  int16_t gyro_offset_z;
} motion_settings_service__msg__SensorSettings;

// Struct for a sequence of motion_settings_service__msg__SensorSettings.
typedef struct motion_settings_service__msg__SensorSettings__Sequence
{
  motion_settings_service__msg__SensorSettings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motion_settings_service__msg__SensorSettings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTION_SETTINGS_SERVICE__MSG__DETAIL__SENSOR_SETTINGS__STRUCT_H_
