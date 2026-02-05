// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motion_settings_service:msg/SpdPlanSettings.idl
// generated code does not contain a copyright notice

#ifndef MOTION_SETTINGS_SERVICE__MSG__DETAIL__SPD_PLAN_SETTINGS__STRUCT_H_
#define MOTION_SETTINGS_SERVICE__MSG__DETAIL__SPD_PLAN_SETTINGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/SpdPlanSettings in the package motion_settings_service.
typedef struct motion_settings_service__msg__SpdPlanSettings
{
  int32_t milliseconds;
  float speed_percent;
  float max_v;
  float max_w;
  float max_acc;
  float jerk;
  bool enable;
} motion_settings_service__msg__SpdPlanSettings;

// Struct for a sequence of motion_settings_service__msg__SpdPlanSettings.
typedef struct motion_settings_service__msg__SpdPlanSettings__Sequence
{
  motion_settings_service__msg__SpdPlanSettings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motion_settings_service__msg__SpdPlanSettings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTION_SETTINGS_SERVICE__MSG__DETAIL__SPD_PLAN_SETTINGS__STRUCT_H_
