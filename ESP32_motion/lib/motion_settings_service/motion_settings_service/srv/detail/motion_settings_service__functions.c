// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motion_settings_service:srv/MotionSettingsService.idl
// generated code does not contain a copyright notice
#include "motion_settings_service/srv/detail/motion_settings_service__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `drivers_settings`
#include "motion_settings_service/msg/detail/driver_settings__functions.h"
// Member `sensor_settings`
#include "motion_settings_service/msg/detail/sensor_settings__functions.h"
// Member `spd_plan_settings`
#include "motion_settings_service/msg/detail/spd_plan_settings__functions.h"

bool
motion_settings_service__srv__MotionSettingsService_Request__init(motion_settings_service__srv__MotionSettingsService_Request * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // mode
  // wheel_width
  // linear_speed_percent
  // angular_speed_percent
  // drivers_settings
  for (size_t i = 0; i < 2; ++i) {
    if (!motion_settings_service__msg__DriverSettings__init(&msg->drivers_settings[i])) {
      motion_settings_service__srv__MotionSettingsService_Request__fini(msg);
      return false;
    }
  }
  // sensor_settings
  if (!motion_settings_service__msg__SensorSettings__init(&msg->sensor_settings)) {
    motion_settings_service__srv__MotionSettingsService_Request__fini(msg);
    return false;
  }
  // spd_plan_settings
  if (!motion_settings_service__msg__SpdPlanSettings__init(&msg->spd_plan_settings)) {
    motion_settings_service__srv__MotionSettingsService_Request__fini(msg);
    return false;
  }
  // motor_enable_flags
  return true;
}

void
motion_settings_service__srv__MotionSettingsService_Request__fini(motion_settings_service__srv__MotionSettingsService_Request * msg)
{
  if (!msg) {
    return;
  }
  // id
  // mode
  // wheel_width
  // linear_speed_percent
  // angular_speed_percent
  // drivers_settings
  for (size_t i = 0; i < 2; ++i) {
    motion_settings_service__msg__DriverSettings__fini(&msg->drivers_settings[i]);
  }
  // sensor_settings
  motion_settings_service__msg__SensorSettings__fini(&msg->sensor_settings);
  // spd_plan_settings
  motion_settings_service__msg__SpdPlanSettings__fini(&msg->spd_plan_settings);
  // motor_enable_flags
}

bool
motion_settings_service__srv__MotionSettingsService_Request__are_equal(const motion_settings_service__srv__MotionSettingsService_Request * lhs, const motion_settings_service__srv__MotionSettingsService_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // wheel_width
  if (lhs->wheel_width != rhs->wheel_width) {
    return false;
  }
  // linear_speed_percent
  if (lhs->linear_speed_percent != rhs->linear_speed_percent) {
    return false;
  }
  // angular_speed_percent
  if (lhs->angular_speed_percent != rhs->angular_speed_percent) {
    return false;
  }
  // drivers_settings
  for (size_t i = 0; i < 2; ++i) {
    if (!motion_settings_service__msg__DriverSettings__are_equal(
        &(lhs->drivers_settings[i]), &(rhs->drivers_settings[i])))
    {
      return false;
    }
  }
  // sensor_settings
  if (!motion_settings_service__msg__SensorSettings__are_equal(
      &(lhs->sensor_settings), &(rhs->sensor_settings)))
  {
    return false;
  }
  // spd_plan_settings
  if (!motion_settings_service__msg__SpdPlanSettings__are_equal(
      &(lhs->spd_plan_settings), &(rhs->spd_plan_settings)))
  {
    return false;
  }
  // motor_enable_flags
  if (lhs->motor_enable_flags != rhs->motor_enable_flags) {
    return false;
  }
  return true;
}

bool
motion_settings_service__srv__MotionSettingsService_Request__copy(
  const motion_settings_service__srv__MotionSettingsService_Request * input,
  motion_settings_service__srv__MotionSettingsService_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // mode
  output->mode = input->mode;
  // wheel_width
  output->wheel_width = input->wheel_width;
  // linear_speed_percent
  output->linear_speed_percent = input->linear_speed_percent;
  // angular_speed_percent
  output->angular_speed_percent = input->angular_speed_percent;
  // drivers_settings
  for (size_t i = 0; i < 2; ++i) {
    if (!motion_settings_service__msg__DriverSettings__copy(
        &(input->drivers_settings[i]), &(output->drivers_settings[i])))
    {
      return false;
    }
  }
  // sensor_settings
  if (!motion_settings_service__msg__SensorSettings__copy(
      &(input->sensor_settings), &(output->sensor_settings)))
  {
    return false;
  }
  // spd_plan_settings
  if (!motion_settings_service__msg__SpdPlanSettings__copy(
      &(input->spd_plan_settings), &(output->spd_plan_settings)))
  {
    return false;
  }
  // motor_enable_flags
  output->motor_enable_flags = input->motor_enable_flags;
  return true;
}

motion_settings_service__srv__MotionSettingsService_Request *
motion_settings_service__srv__MotionSettingsService_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__srv__MotionSettingsService_Request * msg = (motion_settings_service__srv__MotionSettingsService_Request *)allocator.allocate(sizeof(motion_settings_service__srv__MotionSettingsService_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motion_settings_service__srv__MotionSettingsService_Request));
  bool success = motion_settings_service__srv__MotionSettingsService_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motion_settings_service__srv__MotionSettingsService_Request__destroy(motion_settings_service__srv__MotionSettingsService_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motion_settings_service__srv__MotionSettingsService_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motion_settings_service__srv__MotionSettingsService_Request__Sequence__init(motion_settings_service__srv__MotionSettingsService_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__srv__MotionSettingsService_Request * data = NULL;

  if (size) {
    data = (motion_settings_service__srv__MotionSettingsService_Request *)allocator.zero_allocate(size, sizeof(motion_settings_service__srv__MotionSettingsService_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motion_settings_service__srv__MotionSettingsService_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motion_settings_service__srv__MotionSettingsService_Request__fini(&data[i - 1]);
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
motion_settings_service__srv__MotionSettingsService_Request__Sequence__fini(motion_settings_service__srv__MotionSettingsService_Request__Sequence * array)
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
      motion_settings_service__srv__MotionSettingsService_Request__fini(&array->data[i]);
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

motion_settings_service__srv__MotionSettingsService_Request__Sequence *
motion_settings_service__srv__MotionSettingsService_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__srv__MotionSettingsService_Request__Sequence * array = (motion_settings_service__srv__MotionSettingsService_Request__Sequence *)allocator.allocate(sizeof(motion_settings_service__srv__MotionSettingsService_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motion_settings_service__srv__MotionSettingsService_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motion_settings_service__srv__MotionSettingsService_Request__Sequence__destroy(motion_settings_service__srv__MotionSettingsService_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motion_settings_service__srv__MotionSettingsService_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motion_settings_service__srv__MotionSettingsService_Request__Sequence__are_equal(const motion_settings_service__srv__MotionSettingsService_Request__Sequence * lhs, const motion_settings_service__srv__MotionSettingsService_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motion_settings_service__srv__MotionSettingsService_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motion_settings_service__srv__MotionSettingsService_Request__Sequence__copy(
  const motion_settings_service__srv__MotionSettingsService_Request__Sequence * input,
  motion_settings_service__srv__MotionSettingsService_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motion_settings_service__srv__MotionSettingsService_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motion_settings_service__srv__MotionSettingsService_Request * data =
      (motion_settings_service__srv__MotionSettingsService_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motion_settings_service__srv__MotionSettingsService_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motion_settings_service__srv__MotionSettingsService_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motion_settings_service__srv__MotionSettingsService_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `drivers_settings`
// already included above
// #include "motion_settings_service/msg/detail/driver_settings__functions.h"
// Member `sensor_settings`
// already included above
// #include "motion_settings_service/msg/detail/sensor_settings__functions.h"
// Member `spd_plan_settings`
// already included above
// #include "motion_settings_service/msg/detail/spd_plan_settings__functions.h"

bool
motion_settings_service__srv__MotionSettingsService_Response__init(motion_settings_service__srv__MotionSettingsService_Response * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // mode
  // wheel_width
  // linear_speed_percent
  // angular_speed_percent
  // drivers_settings
  for (size_t i = 0; i < 2; ++i) {
    if (!motion_settings_service__msg__DriverSettings__init(&msg->drivers_settings[i])) {
      motion_settings_service__srv__MotionSettingsService_Response__fini(msg);
      return false;
    }
  }
  // sensor_settings
  if (!motion_settings_service__msg__SensorSettings__init(&msg->sensor_settings)) {
    motion_settings_service__srv__MotionSettingsService_Response__fini(msg);
    return false;
  }
  // spd_plan_settings
  if (!motion_settings_service__msg__SpdPlanSettings__init(&msg->spd_plan_settings)) {
    motion_settings_service__srv__MotionSettingsService_Response__fini(msg);
    return false;
  }
  // motor_enable_flags
  return true;
}

void
motion_settings_service__srv__MotionSettingsService_Response__fini(motion_settings_service__srv__MotionSettingsService_Response * msg)
{
  if (!msg) {
    return;
  }
  // id
  // mode
  // wheel_width
  // linear_speed_percent
  // angular_speed_percent
  // drivers_settings
  for (size_t i = 0; i < 2; ++i) {
    motion_settings_service__msg__DriverSettings__fini(&msg->drivers_settings[i]);
  }
  // sensor_settings
  motion_settings_service__msg__SensorSettings__fini(&msg->sensor_settings);
  // spd_plan_settings
  motion_settings_service__msg__SpdPlanSettings__fini(&msg->spd_plan_settings);
  // motor_enable_flags
}

bool
motion_settings_service__srv__MotionSettingsService_Response__are_equal(const motion_settings_service__srv__MotionSettingsService_Response * lhs, const motion_settings_service__srv__MotionSettingsService_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // wheel_width
  if (lhs->wheel_width != rhs->wheel_width) {
    return false;
  }
  // linear_speed_percent
  if (lhs->linear_speed_percent != rhs->linear_speed_percent) {
    return false;
  }
  // angular_speed_percent
  if (lhs->angular_speed_percent != rhs->angular_speed_percent) {
    return false;
  }
  // drivers_settings
  for (size_t i = 0; i < 2; ++i) {
    if (!motion_settings_service__msg__DriverSettings__are_equal(
        &(lhs->drivers_settings[i]), &(rhs->drivers_settings[i])))
    {
      return false;
    }
  }
  // sensor_settings
  if (!motion_settings_service__msg__SensorSettings__are_equal(
      &(lhs->sensor_settings), &(rhs->sensor_settings)))
  {
    return false;
  }
  // spd_plan_settings
  if (!motion_settings_service__msg__SpdPlanSettings__are_equal(
      &(lhs->spd_plan_settings), &(rhs->spd_plan_settings)))
  {
    return false;
  }
  // motor_enable_flags
  if (lhs->motor_enable_flags != rhs->motor_enable_flags) {
    return false;
  }
  return true;
}

bool
motion_settings_service__srv__MotionSettingsService_Response__copy(
  const motion_settings_service__srv__MotionSettingsService_Response * input,
  motion_settings_service__srv__MotionSettingsService_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // mode
  output->mode = input->mode;
  // wheel_width
  output->wheel_width = input->wheel_width;
  // linear_speed_percent
  output->linear_speed_percent = input->linear_speed_percent;
  // angular_speed_percent
  output->angular_speed_percent = input->angular_speed_percent;
  // drivers_settings
  for (size_t i = 0; i < 2; ++i) {
    if (!motion_settings_service__msg__DriverSettings__copy(
        &(input->drivers_settings[i]), &(output->drivers_settings[i])))
    {
      return false;
    }
  }
  // sensor_settings
  if (!motion_settings_service__msg__SensorSettings__copy(
      &(input->sensor_settings), &(output->sensor_settings)))
  {
    return false;
  }
  // spd_plan_settings
  if (!motion_settings_service__msg__SpdPlanSettings__copy(
      &(input->spd_plan_settings), &(output->spd_plan_settings)))
  {
    return false;
  }
  // motor_enable_flags
  output->motor_enable_flags = input->motor_enable_flags;
  return true;
}

motion_settings_service__srv__MotionSettingsService_Response *
motion_settings_service__srv__MotionSettingsService_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__srv__MotionSettingsService_Response * msg = (motion_settings_service__srv__MotionSettingsService_Response *)allocator.allocate(sizeof(motion_settings_service__srv__MotionSettingsService_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motion_settings_service__srv__MotionSettingsService_Response));
  bool success = motion_settings_service__srv__MotionSettingsService_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motion_settings_service__srv__MotionSettingsService_Response__destroy(motion_settings_service__srv__MotionSettingsService_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motion_settings_service__srv__MotionSettingsService_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motion_settings_service__srv__MotionSettingsService_Response__Sequence__init(motion_settings_service__srv__MotionSettingsService_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__srv__MotionSettingsService_Response * data = NULL;

  if (size) {
    data = (motion_settings_service__srv__MotionSettingsService_Response *)allocator.zero_allocate(size, sizeof(motion_settings_service__srv__MotionSettingsService_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motion_settings_service__srv__MotionSettingsService_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motion_settings_service__srv__MotionSettingsService_Response__fini(&data[i - 1]);
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
motion_settings_service__srv__MotionSettingsService_Response__Sequence__fini(motion_settings_service__srv__MotionSettingsService_Response__Sequence * array)
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
      motion_settings_service__srv__MotionSettingsService_Response__fini(&array->data[i]);
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

motion_settings_service__srv__MotionSettingsService_Response__Sequence *
motion_settings_service__srv__MotionSettingsService_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__srv__MotionSettingsService_Response__Sequence * array = (motion_settings_service__srv__MotionSettingsService_Response__Sequence *)allocator.allocate(sizeof(motion_settings_service__srv__MotionSettingsService_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motion_settings_service__srv__MotionSettingsService_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motion_settings_service__srv__MotionSettingsService_Response__Sequence__destroy(motion_settings_service__srv__MotionSettingsService_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motion_settings_service__srv__MotionSettingsService_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motion_settings_service__srv__MotionSettingsService_Response__Sequence__are_equal(const motion_settings_service__srv__MotionSettingsService_Response__Sequence * lhs, const motion_settings_service__srv__MotionSettingsService_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motion_settings_service__srv__MotionSettingsService_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motion_settings_service__srv__MotionSettingsService_Response__Sequence__copy(
  const motion_settings_service__srv__MotionSettingsService_Response__Sequence * input,
  motion_settings_service__srv__MotionSettingsService_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motion_settings_service__srv__MotionSettingsService_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motion_settings_service__srv__MotionSettingsService_Response * data =
      (motion_settings_service__srv__MotionSettingsService_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motion_settings_service__srv__MotionSettingsService_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motion_settings_service__srv__MotionSettingsService_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motion_settings_service__srv__MotionSettingsService_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
