// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motion_status_msgs:msg/MotionStatus.idl
// generated code does not contain a copyright notice
#include "motion_status_msgs/msg/detail/motion_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motion_status_msgs__msg__MotionStatus__init(motion_status_msgs__msg__MotionStatus * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  // seq
  // left_front_total_distance
  // left_front_dt_distance
  // left_front_current_v
  // left_front_target_v
  // left_back_total_distance
  // left_back_dt_distance
  // left_back_current_v
  // left_back_target_v
  // right_front_total_distance
  // right_front_dt_distance
  // right_front_current_v
  // right_front_target_v
  // right_back_total_distance
  // right_back_dt_distance
  // right_back_current_v
  // right_back_target_v
  // imu_roll
  // imu_pitch
  // imu_yaw
  // imu_gyro_x
  // imu_gyro_y
  // imu_gyro_z
  return true;
}

void
motion_status_msgs__msg__MotionStatus__fini(motion_status_msgs__msg__MotionStatus * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  // seq
  // left_front_total_distance
  // left_front_dt_distance
  // left_front_current_v
  // left_front_target_v
  // left_back_total_distance
  // left_back_dt_distance
  // left_back_current_v
  // left_back_target_v
  // right_front_total_distance
  // right_front_dt_distance
  // right_front_current_v
  // right_front_target_v
  // right_back_total_distance
  // right_back_dt_distance
  // right_back_current_v
  // right_back_target_v
  // imu_roll
  // imu_pitch
  // imu_yaw
  // imu_gyro_x
  // imu_gyro_y
  // imu_gyro_z
}

bool
motion_status_msgs__msg__MotionStatus__are_equal(const motion_status_msgs__msg__MotionStatus * lhs, const motion_status_msgs__msg__MotionStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (lhs->stamp != rhs->stamp) {
    return false;
  }
  // seq
  if (lhs->seq != rhs->seq) {
    return false;
  }
  // left_front_total_distance
  if (lhs->left_front_total_distance != rhs->left_front_total_distance) {
    return false;
  }
  // left_front_dt_distance
  if (lhs->left_front_dt_distance != rhs->left_front_dt_distance) {
    return false;
  }
  // left_front_current_v
  if (lhs->left_front_current_v != rhs->left_front_current_v) {
    return false;
  }
  // left_front_target_v
  if (lhs->left_front_target_v != rhs->left_front_target_v) {
    return false;
  }
  // left_back_total_distance
  if (lhs->left_back_total_distance != rhs->left_back_total_distance) {
    return false;
  }
  // left_back_dt_distance
  if (lhs->left_back_dt_distance != rhs->left_back_dt_distance) {
    return false;
  }
  // left_back_current_v
  if (lhs->left_back_current_v != rhs->left_back_current_v) {
    return false;
  }
  // left_back_target_v
  if (lhs->left_back_target_v != rhs->left_back_target_v) {
    return false;
  }
  // right_front_total_distance
  if (lhs->right_front_total_distance != rhs->right_front_total_distance) {
    return false;
  }
  // right_front_dt_distance
  if (lhs->right_front_dt_distance != rhs->right_front_dt_distance) {
    return false;
  }
  // right_front_current_v
  if (lhs->right_front_current_v != rhs->right_front_current_v) {
    return false;
  }
  // right_front_target_v
  if (lhs->right_front_target_v != rhs->right_front_target_v) {
    return false;
  }
  // right_back_total_distance
  if (lhs->right_back_total_distance != rhs->right_back_total_distance) {
    return false;
  }
  // right_back_dt_distance
  if (lhs->right_back_dt_distance != rhs->right_back_dt_distance) {
    return false;
  }
  // right_back_current_v
  if (lhs->right_back_current_v != rhs->right_back_current_v) {
    return false;
  }
  // right_back_target_v
  if (lhs->right_back_target_v != rhs->right_back_target_v) {
    return false;
  }
  // imu_roll
  if (lhs->imu_roll != rhs->imu_roll) {
    return false;
  }
  // imu_pitch
  if (lhs->imu_pitch != rhs->imu_pitch) {
    return false;
  }
  // imu_yaw
  if (lhs->imu_yaw != rhs->imu_yaw) {
    return false;
  }
  // imu_gyro_x
  if (lhs->imu_gyro_x != rhs->imu_gyro_x) {
    return false;
  }
  // imu_gyro_y
  if (lhs->imu_gyro_y != rhs->imu_gyro_y) {
    return false;
  }
  // imu_gyro_z
  if (lhs->imu_gyro_z != rhs->imu_gyro_z) {
    return false;
  }
  return true;
}

bool
motion_status_msgs__msg__MotionStatus__copy(
  const motion_status_msgs__msg__MotionStatus * input,
  motion_status_msgs__msg__MotionStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  output->stamp = input->stamp;
  // seq
  output->seq = input->seq;
  // left_front_total_distance
  output->left_front_total_distance = input->left_front_total_distance;
  // left_front_dt_distance
  output->left_front_dt_distance = input->left_front_dt_distance;
  // left_front_current_v
  output->left_front_current_v = input->left_front_current_v;
  // left_front_target_v
  output->left_front_target_v = input->left_front_target_v;
  // left_back_total_distance
  output->left_back_total_distance = input->left_back_total_distance;
  // left_back_dt_distance
  output->left_back_dt_distance = input->left_back_dt_distance;
  // left_back_current_v
  output->left_back_current_v = input->left_back_current_v;
  // left_back_target_v
  output->left_back_target_v = input->left_back_target_v;
  // right_front_total_distance
  output->right_front_total_distance = input->right_front_total_distance;
  // right_front_dt_distance
  output->right_front_dt_distance = input->right_front_dt_distance;
  // right_front_current_v
  output->right_front_current_v = input->right_front_current_v;
  // right_front_target_v
  output->right_front_target_v = input->right_front_target_v;
  // right_back_total_distance
  output->right_back_total_distance = input->right_back_total_distance;
  // right_back_dt_distance
  output->right_back_dt_distance = input->right_back_dt_distance;
  // right_back_current_v
  output->right_back_current_v = input->right_back_current_v;
  // right_back_target_v
  output->right_back_target_v = input->right_back_target_v;
  // imu_roll
  output->imu_roll = input->imu_roll;
  // imu_pitch
  output->imu_pitch = input->imu_pitch;
  // imu_yaw
  output->imu_yaw = input->imu_yaw;
  // imu_gyro_x
  output->imu_gyro_x = input->imu_gyro_x;
  // imu_gyro_y
  output->imu_gyro_y = input->imu_gyro_y;
  // imu_gyro_z
  output->imu_gyro_z = input->imu_gyro_z;
  return true;
}

motion_status_msgs__msg__MotionStatus *
motion_status_msgs__msg__MotionStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__MotionStatus * msg = (motion_status_msgs__msg__MotionStatus *)allocator.allocate(sizeof(motion_status_msgs__msg__MotionStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motion_status_msgs__msg__MotionStatus));
  bool success = motion_status_msgs__msg__MotionStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motion_status_msgs__msg__MotionStatus__destroy(motion_status_msgs__msg__MotionStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motion_status_msgs__msg__MotionStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motion_status_msgs__msg__MotionStatus__Sequence__init(motion_status_msgs__msg__MotionStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__MotionStatus * data = NULL;

  if (size) {
    data = (motion_status_msgs__msg__MotionStatus *)allocator.zero_allocate(size, sizeof(motion_status_msgs__msg__MotionStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motion_status_msgs__msg__MotionStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motion_status_msgs__msg__MotionStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
motion_status_msgs__msg__MotionStatus__Sequence__fini(motion_status_msgs__msg__MotionStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      motion_status_msgs__msg__MotionStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

motion_status_msgs__msg__MotionStatus__Sequence *
motion_status_msgs__msg__MotionStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__MotionStatus__Sequence * array = (motion_status_msgs__msg__MotionStatus__Sequence *)allocator.allocate(sizeof(motion_status_msgs__msg__MotionStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motion_status_msgs__msg__MotionStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motion_status_msgs__msg__MotionStatus__Sequence__destroy(motion_status_msgs__msg__MotionStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motion_status_msgs__msg__MotionStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motion_status_msgs__msg__MotionStatus__Sequence__are_equal(const motion_status_msgs__msg__MotionStatus__Sequence * lhs, const motion_status_msgs__msg__MotionStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motion_status_msgs__msg__MotionStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motion_status_msgs__msg__MotionStatus__Sequence__copy(
  const motion_status_msgs__msg__MotionStatus__Sequence * input,
  motion_status_msgs__msg__MotionStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motion_status_msgs__msg__MotionStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motion_status_msgs__msg__MotionStatus * data =
      (motion_status_msgs__msg__MotionStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motion_status_msgs__msg__MotionStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motion_status_msgs__msg__MotionStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motion_status_msgs__msg__MotionStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
