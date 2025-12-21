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

/// Struct defined in msg/MotionStatus in the package motion_status_msgs.
typedef struct motion_status_msgs__msg__MotionStatus
{
  uint64_t stamp;
  uint64_t seq;
  float left_front_total_distance;
  float left_front_dt_distance;
  float left_front_current_v;
  float left_front_target_v;
  float left_back_total_distance;
  float left_back_dt_distance;
  float left_back_current_v;
  float left_back_target_v;
  float right_front_total_distance;
  float right_front_dt_distance;
  float right_front_current_v;
  float right_front_target_v;
  float right_back_total_distance;
  float right_back_dt_distance;
  float right_back_current_v;
  float right_back_target_v;
  float imu_roll;
  float imu_pitch;
  float imu_yaw;
  float imu_gyro_x;
  float imu_gyro_y;
  float imu_gyro_z;
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
