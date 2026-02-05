// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motion_status_msgs:msg/SensorStatus.idl
// generated code does not contain a copyright notice
#include "motion_status_msgs/msg/detail/sensor_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motion_status_msgs__msg__SensorStatus__init(motion_status_msgs__msg__SensorStatus * msg)
{
  if (!msg) {
    return false;
  }
  // roll
  // pitch
  // yaw
  // gyro_x
  // gyro_y
  // gyro_z
  // data
  // size
  return true;
}

void
motion_status_msgs__msg__SensorStatus__fini(motion_status_msgs__msg__SensorStatus * msg)
{
  if (!msg) {
    return;
  }
  // roll
  // pitch
  // yaw
  // gyro_x
  // gyro_y
  // gyro_z
  // data
  // size
}

bool
motion_status_msgs__msg__SensorStatus__are_equal(const motion_status_msgs__msg__SensorStatus * lhs, const motion_status_msgs__msg__SensorStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // roll
  if (lhs->roll != rhs->roll) {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // gyro_x
  if (lhs->gyro_x != rhs->gyro_x) {
    return false;
  }
  // gyro_y
  if (lhs->gyro_y != rhs->gyro_y) {
    return false;
  }
  // gyro_z
  if (lhs->gyro_z != rhs->gyro_z) {
    return false;
  }
  // data
  for (size_t i = 0; i < 128; ++i) {
    if (lhs->data[i] != rhs->data[i]) {
      return false;
    }
  }
  // size
  if (lhs->size != rhs->size) {
    return false;
  }
  return true;
}

bool
motion_status_msgs__msg__SensorStatus__copy(
  const motion_status_msgs__msg__SensorStatus * input,
  motion_status_msgs__msg__SensorStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // roll
  output->roll = input->roll;
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  // gyro_x
  output->gyro_x = input->gyro_x;
  // gyro_y
  output->gyro_y = input->gyro_y;
  // gyro_z
  output->gyro_z = input->gyro_z;
  // data
  for (size_t i = 0; i < 128; ++i) {
    output->data[i] = input->data[i];
  }
  // size
  output->size = input->size;
  return true;
}

motion_status_msgs__msg__SensorStatus *
motion_status_msgs__msg__SensorStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__SensorStatus * msg = (motion_status_msgs__msg__SensorStatus *)allocator.allocate(sizeof(motion_status_msgs__msg__SensorStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motion_status_msgs__msg__SensorStatus));
  bool success = motion_status_msgs__msg__SensorStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motion_status_msgs__msg__SensorStatus__destroy(motion_status_msgs__msg__SensorStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motion_status_msgs__msg__SensorStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motion_status_msgs__msg__SensorStatus__Sequence__init(motion_status_msgs__msg__SensorStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__SensorStatus * data = NULL;

  if (size) {
    data = (motion_status_msgs__msg__SensorStatus *)allocator.zero_allocate(size, sizeof(motion_status_msgs__msg__SensorStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motion_status_msgs__msg__SensorStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motion_status_msgs__msg__SensorStatus__fini(&data[i - 1]);
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
motion_status_msgs__msg__SensorStatus__Sequence__fini(motion_status_msgs__msg__SensorStatus__Sequence * array)
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
      motion_status_msgs__msg__SensorStatus__fini(&array->data[i]);
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

motion_status_msgs__msg__SensorStatus__Sequence *
motion_status_msgs__msg__SensorStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__SensorStatus__Sequence * array = (motion_status_msgs__msg__SensorStatus__Sequence *)allocator.allocate(sizeof(motion_status_msgs__msg__SensorStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motion_status_msgs__msg__SensorStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motion_status_msgs__msg__SensorStatus__Sequence__destroy(motion_status_msgs__msg__SensorStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motion_status_msgs__msg__SensorStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motion_status_msgs__msg__SensorStatus__Sequence__are_equal(const motion_status_msgs__msg__SensorStatus__Sequence * lhs, const motion_status_msgs__msg__SensorStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motion_status_msgs__msg__SensorStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motion_status_msgs__msg__SensorStatus__Sequence__copy(
  const motion_status_msgs__msg__SensorStatus__Sequence * input,
  motion_status_msgs__msg__SensorStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motion_status_msgs__msg__SensorStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motion_status_msgs__msg__SensorStatus * data =
      (motion_status_msgs__msg__SensorStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motion_status_msgs__msg__SensorStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motion_status_msgs__msg__SensorStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motion_status_msgs__msg__SensorStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
