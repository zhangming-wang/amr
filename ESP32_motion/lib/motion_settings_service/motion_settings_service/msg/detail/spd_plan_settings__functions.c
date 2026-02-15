// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motion_settings_service:msg/SpdPlanSettings.idl
// generated code does not contain a copyright notice
#include "motion_settings_service/msg/detail/spd_plan_settings__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motion_settings_service__msg__SpdPlanSettings__init(motion_settings_service__msg__SpdPlanSettings * msg)
{
  if (!msg) {
    return false;
  }
  // milliseconds
  // speed_percent
  // max_v
  // min_v
  // max_w
  // min_w
  // max_acc
  // jerk
  // enable
  return true;
}

void
motion_settings_service__msg__SpdPlanSettings__fini(motion_settings_service__msg__SpdPlanSettings * msg)
{
  if (!msg) {
    return;
  }
  // milliseconds
  // speed_percent
  // max_v
  // min_v
  // max_w
  // min_w
  // max_acc
  // jerk
  // enable
}

bool
motion_settings_service__msg__SpdPlanSettings__are_equal(const motion_settings_service__msg__SpdPlanSettings * lhs, const motion_settings_service__msg__SpdPlanSettings * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // milliseconds
  if (lhs->milliseconds != rhs->milliseconds) {
    return false;
  }
  // speed_percent
  if (lhs->speed_percent != rhs->speed_percent) {
    return false;
  }
  // max_v
  if (lhs->max_v != rhs->max_v) {
    return false;
  }
  // min_v
  if (lhs->min_v != rhs->min_v) {
    return false;
  }
  // max_w
  if (lhs->max_w != rhs->max_w) {
    return false;
  }
  // min_w
  if (lhs->min_w != rhs->min_w) {
    return false;
  }
  // max_acc
  if (lhs->max_acc != rhs->max_acc) {
    return false;
  }
  // jerk
  if (lhs->jerk != rhs->jerk) {
    return false;
  }
  // enable
  if (lhs->enable != rhs->enable) {
    return false;
  }
  return true;
}

bool
motion_settings_service__msg__SpdPlanSettings__copy(
  const motion_settings_service__msg__SpdPlanSettings * input,
  motion_settings_service__msg__SpdPlanSettings * output)
{
  if (!input || !output) {
    return false;
  }
  // milliseconds
  output->milliseconds = input->milliseconds;
  // speed_percent
  output->speed_percent = input->speed_percent;
  // max_v
  output->max_v = input->max_v;
  // min_v
  output->min_v = input->min_v;
  // max_w
  output->max_w = input->max_w;
  // min_w
  output->min_w = input->min_w;
  // max_acc
  output->max_acc = input->max_acc;
  // jerk
  output->jerk = input->jerk;
  // enable
  output->enable = input->enable;
  return true;
}

motion_settings_service__msg__SpdPlanSettings *
motion_settings_service__msg__SpdPlanSettings__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__SpdPlanSettings * msg = (motion_settings_service__msg__SpdPlanSettings *)allocator.allocate(sizeof(motion_settings_service__msg__SpdPlanSettings), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motion_settings_service__msg__SpdPlanSettings));
  bool success = motion_settings_service__msg__SpdPlanSettings__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motion_settings_service__msg__SpdPlanSettings__destroy(motion_settings_service__msg__SpdPlanSettings * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motion_settings_service__msg__SpdPlanSettings__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motion_settings_service__msg__SpdPlanSettings__Sequence__init(motion_settings_service__msg__SpdPlanSettings__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__SpdPlanSettings * data = NULL;

  if (size) {
    data = (motion_settings_service__msg__SpdPlanSettings *)allocator.zero_allocate(size, sizeof(motion_settings_service__msg__SpdPlanSettings), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motion_settings_service__msg__SpdPlanSettings__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motion_settings_service__msg__SpdPlanSettings__fini(&data[i - 1]);
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
motion_settings_service__msg__SpdPlanSettings__Sequence__fini(motion_settings_service__msg__SpdPlanSettings__Sequence * array)
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
      motion_settings_service__msg__SpdPlanSettings__fini(&array->data[i]);
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

motion_settings_service__msg__SpdPlanSettings__Sequence *
motion_settings_service__msg__SpdPlanSettings__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__SpdPlanSettings__Sequence * array = (motion_settings_service__msg__SpdPlanSettings__Sequence *)allocator.allocate(sizeof(motion_settings_service__msg__SpdPlanSettings__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motion_settings_service__msg__SpdPlanSettings__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motion_settings_service__msg__SpdPlanSettings__Sequence__destroy(motion_settings_service__msg__SpdPlanSettings__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motion_settings_service__msg__SpdPlanSettings__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motion_settings_service__msg__SpdPlanSettings__Sequence__are_equal(const motion_settings_service__msg__SpdPlanSettings__Sequence * lhs, const motion_settings_service__msg__SpdPlanSettings__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motion_settings_service__msg__SpdPlanSettings__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motion_settings_service__msg__SpdPlanSettings__Sequence__copy(
  const motion_settings_service__msg__SpdPlanSettings__Sequence * input,
  motion_settings_service__msg__SpdPlanSettings__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motion_settings_service__msg__SpdPlanSettings);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motion_settings_service__msg__SpdPlanSettings * data =
      (motion_settings_service__msg__SpdPlanSettings *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motion_settings_service__msg__SpdPlanSettings__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motion_settings_service__msg__SpdPlanSettings__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motion_settings_service__msg__SpdPlanSettings__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
