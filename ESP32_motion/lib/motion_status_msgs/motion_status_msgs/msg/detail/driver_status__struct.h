// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motion_status_msgs:msg/DriverStatus.idl
// generated code does not contain a copyright notice

#ifndef MOTION_STATUS_MSGS__MSG__DETAIL__DRIVER_STATUS__STRUCT_H_
#define MOTION_STATUS_MSGS__MSG__DETAIL__DRIVER_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DriverStatus in the package motion_status_msgs.
typedef struct motion_status_msgs__msg__DriverStatus
{
  float total_distance;
  float dt_distance;
  float current_v;
  float target_v;
} motion_status_msgs__msg__DriverStatus;

// Struct for a sequence of motion_status_msgs__msg__DriverStatus.
typedef struct motion_status_msgs__msg__DriverStatus__Sequence
{
  motion_status_msgs__msg__DriverStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motion_status_msgs__msg__DriverStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTION_STATUS_MSGS__MSG__DETAIL__DRIVER_STATUS__STRUCT_H_
