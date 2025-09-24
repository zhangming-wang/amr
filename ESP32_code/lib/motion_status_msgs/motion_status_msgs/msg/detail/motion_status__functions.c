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
  // left_front_current_v
  // left_front_target_v
  // left_back_current_v
  // left_back_target_v
  // right_front_current_v
  // right_front_target_v
  // right_back_current_v
  // right_back_target_v
  // twist_current_linear_x
  // twist_current_linear_y
  // twist_current_linear_z
  // twist_current_angular_x
  // twist_current_angular_y
  // twist_current_angular_z
  // twist_target_linear_x
  // twist_target_linear_y
  // twist_target_linear_z
  // twist_target_angular_x
  // twist_target_angular_y
  // twist_target_angular_z
  // twist_current_euler_pose_x
  // twist_current_euler_pose_y
  // twist_current_euler_pose_z
  // twist_current_euler_pose_roll
  // twist_current_euler_pose_pitch
  // twist_current_euler_pose_yaw
  // twist_target_euler_pose_x
  // twist_target_euler_pose_y
  // twist_target_euler_pose_z
  // twist_target_euler_pose_roll
  // twist_target_euler_pose_pitch
  // twist_target_euler_pose_yaw
  return true;
}

void
motion_status_msgs__msg__MotionStatus__fini(motion_status_msgs__msg__MotionStatus * msg)
{
  if (!msg) {
    return;
  }
  // left_front_current_v
  // left_front_target_v
  // left_back_current_v
  // left_back_target_v
  // right_front_current_v
  // right_front_target_v
  // right_back_current_v
  // right_back_target_v
  // twist_current_linear_x
  // twist_current_linear_y
  // twist_current_linear_z
  // twist_current_angular_x
  // twist_current_angular_y
  // twist_current_angular_z
  // twist_target_linear_x
  // twist_target_linear_y
  // twist_target_linear_z
  // twist_target_angular_x
  // twist_target_angular_y
  // twist_target_angular_z
  // twist_current_euler_pose_x
  // twist_current_euler_pose_y
  // twist_current_euler_pose_z
  // twist_current_euler_pose_roll
  // twist_current_euler_pose_pitch
  // twist_current_euler_pose_yaw
  // twist_target_euler_pose_x
  // twist_target_euler_pose_y
  // twist_target_euler_pose_z
  // twist_target_euler_pose_roll
  // twist_target_euler_pose_pitch
  // twist_target_euler_pose_yaw
}

bool
motion_status_msgs__msg__MotionStatus__are_equal(const motion_status_msgs__msg__MotionStatus * lhs, const motion_status_msgs__msg__MotionStatus * rhs)
{
  if (!lhs || !rhs) {
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
  // left_back_current_v
  if (lhs->left_back_current_v != rhs->left_back_current_v) {
    return false;
  }
  // left_back_target_v
  if (lhs->left_back_target_v != rhs->left_back_target_v) {
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
  // right_back_current_v
  if (lhs->right_back_current_v != rhs->right_back_current_v) {
    return false;
  }
  // right_back_target_v
  if (lhs->right_back_target_v != rhs->right_back_target_v) {
    return false;
  }
  // twist_current_linear_x
  if (lhs->twist_current_linear_x != rhs->twist_current_linear_x) {
    return false;
  }
  // twist_current_linear_y
  if (lhs->twist_current_linear_y != rhs->twist_current_linear_y) {
    return false;
  }
  // twist_current_linear_z
  if (lhs->twist_current_linear_z != rhs->twist_current_linear_z) {
    return false;
  }
  // twist_current_angular_x
  if (lhs->twist_current_angular_x != rhs->twist_current_angular_x) {
    return false;
  }
  // twist_current_angular_y
  if (lhs->twist_current_angular_y != rhs->twist_current_angular_y) {
    return false;
  }
  // twist_current_angular_z
  if (lhs->twist_current_angular_z != rhs->twist_current_angular_z) {
    return false;
  }
  // twist_target_linear_x
  if (lhs->twist_target_linear_x != rhs->twist_target_linear_x) {
    return false;
  }
  // twist_target_linear_y
  if (lhs->twist_target_linear_y != rhs->twist_target_linear_y) {
    return false;
  }
  // twist_target_linear_z
  if (lhs->twist_target_linear_z != rhs->twist_target_linear_z) {
    return false;
  }
  // twist_target_angular_x
  if (lhs->twist_target_angular_x != rhs->twist_target_angular_x) {
    return false;
  }
  // twist_target_angular_y
  if (lhs->twist_target_angular_y != rhs->twist_target_angular_y) {
    return false;
  }
  // twist_target_angular_z
  if (lhs->twist_target_angular_z != rhs->twist_target_angular_z) {
    return false;
  }
  // twist_current_euler_pose_x
  if (lhs->twist_current_euler_pose_x != rhs->twist_current_euler_pose_x) {
    return false;
  }
  // twist_current_euler_pose_y
  if (lhs->twist_current_euler_pose_y != rhs->twist_current_euler_pose_y) {
    return false;
  }
  // twist_current_euler_pose_z
  if (lhs->twist_current_euler_pose_z != rhs->twist_current_euler_pose_z) {
    return false;
  }
  // twist_current_euler_pose_roll
  if (lhs->twist_current_euler_pose_roll != rhs->twist_current_euler_pose_roll) {
    return false;
  }
  // twist_current_euler_pose_pitch
  if (lhs->twist_current_euler_pose_pitch != rhs->twist_current_euler_pose_pitch) {
    return false;
  }
  // twist_current_euler_pose_yaw
  if (lhs->twist_current_euler_pose_yaw != rhs->twist_current_euler_pose_yaw) {
    return false;
  }
  // twist_target_euler_pose_x
  if (lhs->twist_target_euler_pose_x != rhs->twist_target_euler_pose_x) {
    return false;
  }
  // twist_target_euler_pose_y
  if (lhs->twist_target_euler_pose_y != rhs->twist_target_euler_pose_y) {
    return false;
  }
  // twist_target_euler_pose_z
  if (lhs->twist_target_euler_pose_z != rhs->twist_target_euler_pose_z) {
    return false;
  }
  // twist_target_euler_pose_roll
  if (lhs->twist_target_euler_pose_roll != rhs->twist_target_euler_pose_roll) {
    return false;
  }
  // twist_target_euler_pose_pitch
  if (lhs->twist_target_euler_pose_pitch != rhs->twist_target_euler_pose_pitch) {
    return false;
  }
  // twist_target_euler_pose_yaw
  if (lhs->twist_target_euler_pose_yaw != rhs->twist_target_euler_pose_yaw) {
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
  // left_front_current_v
  output->left_front_current_v = input->left_front_current_v;
  // left_front_target_v
  output->left_front_target_v = input->left_front_target_v;
  // left_back_current_v
  output->left_back_current_v = input->left_back_current_v;
  // left_back_target_v
  output->left_back_target_v = input->left_back_target_v;
  // right_front_current_v
  output->right_front_current_v = input->right_front_current_v;
  // right_front_target_v
  output->right_front_target_v = input->right_front_target_v;
  // right_back_current_v
  output->right_back_current_v = input->right_back_current_v;
  // right_back_target_v
  output->right_back_target_v = input->right_back_target_v;
  // twist_current_linear_x
  output->twist_current_linear_x = input->twist_current_linear_x;
  // twist_current_linear_y
  output->twist_current_linear_y = input->twist_current_linear_y;
  // twist_current_linear_z
  output->twist_current_linear_z = input->twist_current_linear_z;
  // twist_current_angular_x
  output->twist_current_angular_x = input->twist_current_angular_x;
  // twist_current_angular_y
  output->twist_current_angular_y = input->twist_current_angular_y;
  // twist_current_angular_z
  output->twist_current_angular_z = input->twist_current_angular_z;
  // twist_target_linear_x
  output->twist_target_linear_x = input->twist_target_linear_x;
  // twist_target_linear_y
  output->twist_target_linear_y = input->twist_target_linear_y;
  // twist_target_linear_z
  output->twist_target_linear_z = input->twist_target_linear_z;
  // twist_target_angular_x
  output->twist_target_angular_x = input->twist_target_angular_x;
  // twist_target_angular_y
  output->twist_target_angular_y = input->twist_target_angular_y;
  // twist_target_angular_z
  output->twist_target_angular_z = input->twist_target_angular_z;
  // twist_current_euler_pose_x
  output->twist_current_euler_pose_x = input->twist_current_euler_pose_x;
  // twist_current_euler_pose_y
  output->twist_current_euler_pose_y = input->twist_current_euler_pose_y;
  // twist_current_euler_pose_z
  output->twist_current_euler_pose_z = input->twist_current_euler_pose_z;
  // twist_current_euler_pose_roll
  output->twist_current_euler_pose_roll = input->twist_current_euler_pose_roll;
  // twist_current_euler_pose_pitch
  output->twist_current_euler_pose_pitch = input->twist_current_euler_pose_pitch;
  // twist_current_euler_pose_yaw
  output->twist_current_euler_pose_yaw = input->twist_current_euler_pose_yaw;
  // twist_target_euler_pose_x
  output->twist_target_euler_pose_x = input->twist_target_euler_pose_x;
  // twist_target_euler_pose_y
  output->twist_target_euler_pose_y = input->twist_target_euler_pose_y;
  // twist_target_euler_pose_z
  output->twist_target_euler_pose_z = input->twist_target_euler_pose_z;
  // twist_target_euler_pose_roll
  output->twist_target_euler_pose_roll = input->twist_target_euler_pose_roll;
  // twist_target_euler_pose_pitch
  output->twist_target_euler_pose_pitch = input->twist_target_euler_pose_pitch;
  // twist_target_euler_pose_yaw
  output->twist_target_euler_pose_yaw = input->twist_target_euler_pose_yaw;
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
