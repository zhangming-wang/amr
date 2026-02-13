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

// Include directives for member types
// Member 'drivers_settings'
#include "motion_settings_service/msg/detail/driver_settings__struct.h"
// Member 'sensor_settings'
#include "motion_settings_service/msg/detail/sensor_settings__struct.h"
// Member 'spd_plan_settings'
#include "motion_settings_service/msg/detail/spd_plan_settings__struct.h"

/// Struct defined in srv/MotionSettingsService in the package motion_settings_service.
typedef struct motion_settings_service__srv__MotionSettingsService_Request
{
  uint64_t id;
  int32_t mode;
  float wheel_width;
  float track_width;
  float linear_speed_percent;
  float angular_speed_percent;
  motion_settings_service__msg__DriverSettings drivers_settings[2];
  motion_settings_service__msg__SensorSettings sensor_settings;
  motion_settings_service__msg__SpdPlanSettings spd_plan_settings;
  uint8_t motor_enable_flags;
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

// Include directives for member types
// Member 'drivers_settings'
// already included above
// #include "motion_settings_service/msg/detail/driver_settings__struct.h"
// Member 'sensor_settings'
// already included above
// #include "motion_settings_service/msg/detail/sensor_settings__struct.h"
// Member 'spd_plan_settings'
// already included above
// #include "motion_settings_service/msg/detail/spd_plan_settings__struct.h"

/// Struct defined in srv/MotionSettingsService in the package motion_settings_service.
typedef struct motion_settings_service__srv__MotionSettingsService_Response
{
  uint64_t id;
  int32_t mode;
  float wheel_width;
  float track_width;
  float linear_speed_percent;
  float angular_speed_percent;
  motion_settings_service__msg__DriverSettings drivers_settings[2];
  motion_settings_service__msg__SensorSettings sensor_settings;
  motion_settings_service__msg__SpdPlanSettings spd_plan_settings;
  uint8_t motor_enable_flags;
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
