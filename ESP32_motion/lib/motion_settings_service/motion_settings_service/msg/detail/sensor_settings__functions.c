// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motion_settings_service:msg/SensorSettings.idl
// generated code does not contain a copyright notice
#include "motion_settings_service/msg/detail/sensor_settings__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motion_settings_service__msg__SensorSettings__init(motion_settings_service__msg__SensorSettings * msg)
{
  if (!msg) {
    return false;
  }
  // pin_rx
  // pin_tx
  // pin_pwm
  // pin_sda
  // pin_scl
  // accel_offset_x
  // accel_offset_y
  // accel_offset_z
  // gyro_offset_x
  // gyro_offset_y
  // gyro_offset_z
  return true;
}

void
motion_settings_service__msg__SensorSettings__fini(motion_settings_service__msg__SensorSettings * msg)
{
  if (!msg) {
    return;
  }
  // pin_rx
  // pin_tx
  // pin_pwm
  // pin_sda
  // pin_scl
  // accel_offset_x
  // accel_offset_y
  // accel_offset_z
  // gyro_offset_x
  // gyro_offset_y
  // gyro_offset_z
}

bool
motion_settings_service__msg__SensorSettings__are_equal(const motion_settings_service__msg__SensorSettings * lhs, const motion_settings_service__msg__SensorSettings * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pin_rx
  if (lhs->pin_rx != rhs->pin_rx) {
    return false;
  }
  // pin_tx
  if (lhs->pin_tx != rhs->pin_tx) {
    return false;
  }
  // pin_pwm
  if (lhs->pin_pwm != rhs->pin_pwm) {
    return false;
  }
  // pin_sda
  if (lhs->pin_sda != rhs->pin_sda) {
    return false;
  }
  // pin_scl
  if (lhs->pin_scl != rhs->pin_scl) {
    return false;
  }
  // accel_offset_x
  if (lhs->accel_offset_x != rhs->accel_offset_x) {
    return false;
  }
  // accel_offset_y
  if (lhs->accel_offset_y != rhs->accel_offset_y) {
    return false;
  }
  // accel_offset_z
  if (lhs->accel_offset_z != rhs->accel_offset_z) {
    return false;
  }
  // gyro_offset_x
  if (lhs->gyro_offset_x != rhs->gyro_offset_x) {
    return false;
  }
  // gyro_offset_y
  if (lhs->gyro_offset_y != rhs->gyro_offset_y) {
    return false;
  }
  // gyro_offset_z
  if (lhs->gyro_offset_z != rhs->gyro_offset_z) {
    return false;
  }
  return true;
}

bool
motion_settings_service__msg__SensorSettings__copy(
  const motion_settings_service__msg__SensorSettings * input,
  motion_settings_service__msg__SensorSettings * output)
{
  if (!input || !output) {
    return false;
  }
  // pin_rx
  output->pin_rx = input->pin_rx;
  // pin_tx
  output->pin_tx = input->pin_tx;
  // pin_pwm
  output->pin_pwm = input->pin_pwm;
  // pin_sda
  output->pin_sda = input->pin_sda;
  // pin_scl
  output->pin_scl = input->pin_scl;
  // accel_offset_x
  output->accel_offset_x = input->accel_offset_x;
  // accel_offset_y
  output->accel_offset_y = input->accel_offset_y;
  // accel_offset_z
  output->accel_offset_z = input->accel_offset_z;
  // gyro_offset_x
  output->gyro_offset_x = input->gyro_offset_x;
  // gyro_offset_y
  output->gyro_offset_y = input->gyro_offset_y;
  // gyro_offset_z
  output->gyro_offset_z = input->gyro_offset_z;
  return true;
}

motion_settings_service__msg__SensorSettings *
motion_settings_service__msg__SensorSettings__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__SensorSettings * msg = (motion_settings_service__msg__SensorSettings *)allocator.allocate(sizeof(motion_settings_service__msg__SensorSettings), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motion_settings_service__msg__SensorSettings));
  bool success = motion_settings_service__msg__SensorSettings__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motion_settings_service__msg__SensorSettings__destroy(motion_settings_service__msg__SensorSettings * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motion_settings_service__msg__SensorSettings__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motion_settings_service__msg__SensorSettings__Sequence__init(motion_settings_service__msg__SensorSettings__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__SensorSettings * data = NULL;

  if (size) {
    data = (motion_settings_service__msg__SensorSettings *)allocator.zero_allocate(size, sizeof(motion_settings_service__msg__SensorSettings), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motion_settings_service__msg__SensorSettings__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motion_settings_service__msg__SensorSettings__fini(&data[i - 1]);
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
motion_settings_service__msg__SensorSettings__Sequence__fini(motion_settings_service__msg__SensorSettings__Sequence * array)
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
      motion_settings_service__msg__SensorSettings__fini(&array->data[i]);
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

motion_settings_service__msg__SensorSettings__Sequence *
motion_settings_service__msg__SensorSettings__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__SensorSettings__Sequence * array = (motion_settings_service__msg__SensorSettings__Sequence *)allocator.allocate(sizeof(motion_settings_service__msg__SensorSettings__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motion_settings_service__msg__SensorSettings__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motion_settings_service__msg__SensorSettings__Sequence__destroy(motion_settings_service__msg__SensorSettings__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motion_settings_service__msg__SensorSettings__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motion_settings_service__msg__SensorSettings__Sequence__are_equal(const motion_settings_service__msg__SensorSettings__Sequence * lhs, const motion_settings_service__msg__SensorSettings__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motion_settings_service__msg__SensorSettings__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motion_settings_service__msg__SensorSettings__Sequence__copy(
  const motion_settings_service__msg__SensorSettings__Sequence * input,
  motion_settings_service__msg__SensorSettings__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motion_settings_service__msg__SensorSettings);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motion_settings_service__msg__SensorSettings * data =
      (motion_settings_service__msg__SensorSettings *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motion_settings_service__msg__SensorSettings__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motion_settings_service__msg__SensorSettings__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motion_settings_service__msg__SensorSettings__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
