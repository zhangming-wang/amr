// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motion_status_msgs:msg/SensorStatus.idl
// generated code does not contain a copyright notice

#ifndef MOTION_STATUS_MSGS__MSG__DETAIL__SENSOR_STATUS__STRUCT_H_
#define MOTION_STATUS_MSGS__MSG__DETAIL__SENSOR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/SensorStatus in the package motion_status_msgs.
typedef struct motion_status_msgs__msg__SensorStatus
{
  float roll;
  float pitch;
  float yaw;
  float gyro_x;
  float gyro_y;
  float gyro_z;
  uint8_t data[128];
  uint8_t size;
} motion_status_msgs__msg__SensorStatus;

// Struct for a sequence of motion_status_msgs__msg__SensorStatus.
typedef struct motion_status_msgs__msg__SensorStatus__Sequence
{
  motion_status_msgs__msg__SensorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motion_status_msgs__msg__SensorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTION_STATUS_MSGS__MSG__DETAIL__SENSOR_STATUS__STRUCT_H_
