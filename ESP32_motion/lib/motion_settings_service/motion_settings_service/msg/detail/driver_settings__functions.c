// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motion_settings_service:msg/DriverSettings.idl
// generated code does not contain a copyright notice
#include "motion_settings_service/msg/detail/driver_settings__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motion_settings_service__msg__DriverSettings__init(motion_settings_service__msg__DriverSettings * msg)
{
  if (!msg) {
    return false;
  }
  // motor_pina
  // motor_pinb
  // motor_pinpwm
  // encoder_pina
  // encoder_pinb
  // p
  // i
  // d
  // max_total_i
  // k
  // b
  // wheel_diameter
  // pluses_per_revolution
  // revolutions_per_minute
  // dead_pwm
  return true;
}

void
motion_settings_service__msg__DriverSettings__fini(motion_settings_service__msg__DriverSettings * msg)
{
  if (!msg) {
    return;
  }
  // motor_pina
  // motor_pinb
  // motor_pinpwm
  // encoder_pina
  // encoder_pinb
  // p
  // i
  // d
  // max_total_i
  // k
  // b
  // wheel_diameter
  // pluses_per_revolution
  // revolutions_per_minute
  // dead_pwm
}

bool
motion_settings_service__msg__DriverSettings__are_equal(const motion_settings_service__msg__DriverSettings * lhs, const motion_settings_service__msg__DriverSettings * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // motor_pina
  if (lhs->motor_pina != rhs->motor_pina) {
    return false;
  }
  // motor_pinb
  if (lhs->motor_pinb != rhs->motor_pinb) {
    return false;
  }
  // motor_pinpwm
  if (lhs->motor_pinpwm != rhs->motor_pinpwm) {
    return false;
  }
  // encoder_pina
  if (lhs->encoder_pina != rhs->encoder_pina) {
    return false;
  }
  // encoder_pinb
  if (lhs->encoder_pinb != rhs->encoder_pinb) {
    return false;
  }
  // p
  if (lhs->p != rhs->p) {
    return false;
  }
  // i
  if (lhs->i != rhs->i) {
    return false;
  }
  // d
  if (lhs->d != rhs->d) {
    return false;
  }
  // max_total_i
  if (lhs->max_total_i != rhs->max_total_i) {
    return false;
  }
  // k
  if (lhs->k != rhs->k) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  // wheel_diameter
  if (lhs->wheel_diameter != rhs->wheel_diameter) {
    return false;
  }
  // pluses_per_revolution
  if (lhs->pluses_per_revolution != rhs->pluses_per_revolution) {
    return false;
  }
  // revolutions_per_minute
  if (lhs->revolutions_per_minute != rhs->revolutions_per_minute) {
    return false;
  }
  // dead_pwm
  if (lhs->dead_pwm != rhs->dead_pwm) {
    return false;
  }
  return true;
}

bool
motion_settings_service__msg__DriverSettings__copy(
  const motion_settings_service__msg__DriverSettings * input,
  motion_settings_service__msg__DriverSettings * output)
{
  if (!input || !output) {
    return false;
  }
  // motor_pina
  output->motor_pina = input->motor_pina;
  // motor_pinb
  output->motor_pinb = input->motor_pinb;
  // motor_pinpwm
  output->motor_pinpwm = input->motor_pinpwm;
  // encoder_pina
  output->encoder_pina = input->encoder_pina;
  // encoder_pinb
  output->encoder_pinb = input->encoder_pinb;
  // p
  output->p = input->p;
  // i
  output->i = input->i;
  // d
  output->d = input->d;
  // max_total_i
  output->max_total_i = input->max_total_i;
  // k
  output->k = input->k;
  // b
  output->b = input->b;
  // wheel_diameter
  output->wheel_diameter = input->wheel_diameter;
  // pluses_per_revolution
  output->pluses_per_revolution = input->pluses_per_revolution;
  // revolutions_per_minute
  output->revolutions_per_minute = input->revolutions_per_minute;
  // dead_pwm
  output->dead_pwm = input->dead_pwm;
  return true;
}

motion_settings_service__msg__DriverSettings *
motion_settings_service__msg__DriverSettings__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__DriverSettings * msg = (motion_settings_service__msg__DriverSettings *)allocator.allocate(sizeof(motion_settings_service__msg__DriverSettings), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motion_settings_service__msg__DriverSettings));
  bool success = motion_settings_service__msg__DriverSettings__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motion_settings_service__msg__DriverSettings__destroy(motion_settings_service__msg__DriverSettings * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motion_settings_service__msg__DriverSettings__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motion_settings_service__msg__DriverSettings__Sequence__init(motion_settings_service__msg__DriverSettings__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__DriverSettings * data = NULL;

  if (size) {
    data = (motion_settings_service__msg__DriverSettings *)allocator.zero_allocate(size, sizeof(motion_settings_service__msg__DriverSettings), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motion_settings_service__msg__DriverSettings__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motion_settings_service__msg__DriverSettings__fini(&data[i - 1]);
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
motion_settings_service__msg__DriverSettings__Sequence__fini(motion_settings_service__msg__DriverSettings__Sequence * array)
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
      motion_settings_service__msg__DriverSettings__fini(&array->data[i]);
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

motion_settings_service__msg__DriverSettings__Sequence *
motion_settings_service__msg__DriverSettings__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motion_settings_service__msg__DriverSettings__Sequence * array = (motion_settings_service__msg__DriverSettings__Sequence *)allocator.allocate(sizeof(motion_settings_service__msg__DriverSettings__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motion_settings_service__msg__DriverSettings__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motion_settings_service__msg__DriverSettings__Sequence__destroy(motion_settings_service__msg__DriverSettings__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motion_settings_service__msg__DriverSettings__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motion_settings_service__msg__DriverSettings__Sequence__are_equal(const motion_settings_service__msg__DriverSettings__Sequence * lhs, const motion_settings_service__msg__DriverSettings__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motion_settings_service__msg__DriverSettings__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motion_settings_service__msg__DriverSettings__Sequence__copy(
  const motion_settings_service__msg__DriverSettings__Sequence * input,
  motion_settings_service__msg__DriverSettings__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motion_settings_service__msg__DriverSettings);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motion_settings_service__msg__DriverSettings * data =
      (motion_settings_service__msg__DriverSettings *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motion_settings_service__msg__DriverSettings__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motion_settings_service__msg__DriverSettings__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motion_settings_service__msg__DriverSettings__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
