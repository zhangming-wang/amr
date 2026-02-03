// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motion_status_msgs:msg/MotionStatus.idl
// generated code does not contain a copyright notice

#ifndef MOTION_STATUS_MSGS__MSG__DETAIL__MOTION_STATUS__STRUCT_H_
#define MOTION_STATUS_MSGS__MSG__DETAIL__MOTION_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'drivers_status'
#include "motion_status_msgs/msg/detail/driver_status__struct.h"
// Member 'sensor_status'
#include "motion_status_msgs/msg/detail/sensor_status__struct.h"

/// Struct defined in msg/MotionStatus in the package motion_status_msgs.
typedef struct motion_status_msgs__msg__MotionStatus
{
  uint64_t stamp;
  uint64_t seq;
  motion_status_msgs__msg__DriverStatus drivers_status[2];
  motion_status_msgs__msg__SensorStatus sensor_status;
} motion_status_msgs__msg__MotionStatus;

// Struct for a sequence of motion_status_msgs__msg__MotionStatus.
typedef struct motion_status_msgs__msg__MotionStatus__Sequence
{
  motion_status_msgs__msg__MotionStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motion_status_msgs__msg__MotionStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTION_STATUS_MSGS__MSG__DETAIL__MOTION_STATUS__STRUCT_H_
