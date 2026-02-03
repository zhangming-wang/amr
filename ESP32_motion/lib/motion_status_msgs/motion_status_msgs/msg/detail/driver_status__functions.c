// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motion_status_msgs:msg/DriverStatus.idl
// generated code does not contain a copyright notice
#include "motion_status_msgs/msg/detail/driver_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motion_status_msgs__msg__DriverStatus__init(motion_status_msgs__msg__DriverStatus * msg)
{
  if (!msg) {
    return false;
  }
  // total_distance
  // dt_distance
  // current_v
  // target_v
  return true;
}

void
motion_status_msgs__msg__DriverStatus__fini(motion_status_msgs__msg__DriverStatus * msg)
{
  if (!msg) {
    return;
  }
  // total_distance
  // dt_distance
  // current_v
  // target_v
}

bool
motion_status_msgs__msg__DriverStatus__are_equal(const motion_status_msgs__msg__DriverStatus * lhs, const motion_status_msgs__msg__DriverStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // total_distance
  if (lhs->total_distance != rhs->total_distance) {
    return false;
  }
  // dt_distance
  if (lhs->dt_distance != rhs->dt_distance) {
    return false;
  }
  // current_v
  if (lhs->current_v != rhs->current_v) {
    return false;
  }
  // target_v
  if (lhs->target_v != rhs->target_v) {
    return false;
  }
  return true;
}

bool
motion_status_msgs__msg__DriverStatus__copy(
  const motion_status_msgs__msg__DriverStatus * input,
  motion_status_msgs__msg__DriverStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // total_distance
  output->total_distance = input->total_distance;
  // dt_distance
  output->dt_distance = input->dt_distance;
  // current_v
  output->current_v = input->current_v;
  // target_v
  output->target_v = input->target_v;
  return true;
}

motion_status_msgs__msg__DriverStatus *
motion_status_msgs__msg__DriverStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__DriverStatus * msg = (motion_status_msgs__msg__DriverStatus *)allocator.allocate(sizeof(motion_status_msgs__msg__DriverStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motion_status_msgs__msg__DriverStatus));
  bool success = motion_status_msgs__msg__DriverStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motion_status_msgs__msg__DriverStatus__destroy(motion_status_msgs__msg__DriverStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motion_status_msgs__msg__DriverStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motion_status_msgs__msg__DriverStatus__Sequence__init(motion_status_msgs__msg__DriverStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__DriverStatus * data = NULL;

  if (size) {
    data = (motion_status_msgs__msg__DriverStatus *)allocator.zero_allocate(size, sizeof(motion_status_msgs__msg__DriverStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motion_status_msgs__msg__DriverStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motion_status_msgs__msg__DriverStatus__fini(&data[i - 1]);
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
motion_status_msgs__msg__DriverStatus__Sequence__fini(motion_status_msgs__msg__DriverStatus__Sequence * array)
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
      motion_status_msgs__msg__DriverStatus__fini(&array->data[i]);
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

motion_status_msgs__msg__DriverStatus__Sequence *
motion_status_msgs__msg__DriverStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_status_msgs__msg__DriverStatus__Sequence * array = (motion_status_msgs__msg__DriverStatus__Sequence *)allocator.allocate(sizeof(motion_status_msgs__msg__DriverStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motion_status_msgs__msg__DriverStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motion_status_msgs__msg__DriverStatus__Sequence__destroy(motion_status_msgs__msg__DriverStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motion_status_msgs__msg__DriverStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motion_status_msgs__msg__DriverStatus__Sequence__are_equal(const motion_status_msgs__msg__DriverStatus__Sequence * lhs, const motion_status_msgs__msg__DriverStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motion_status_msgs__msg__DriverStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motion_status_msgs__msg__DriverStatus__Sequence__copy(
  const motion_status_msgs__msg__DriverStatus__Sequence * input,
  motion_status_msgs__msg__DriverStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motion_status_msgs__msg__DriverStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motion_status_msgs__msg__DriverStatus * data =
      (motion_status_msgs__msg__DriverStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motion_status_msgs__msg__DriverStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motion_status_msgs__msg__DriverStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motion_status_msgs__msg__DriverStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
