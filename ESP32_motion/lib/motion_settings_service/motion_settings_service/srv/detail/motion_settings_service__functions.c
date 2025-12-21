// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motion_settings_service:srv/MotionSettingsService.idl
// generated code does not contain a copyright notice
#include "motion_settings_service/srv/detail/motion_settings_service__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
motion_settings_service__srv__MotionSettingsService_Request__init(motion_settings_service__srv__MotionSettingsService_Request * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // mode
  // milliseconds
  // speed_percent
  // max_v
  // max_acc
  // jerk
  // wheel_width
  // track_width
  // left_front_motor_pina
  // left_front_motor_pinb
  // left_front_motor_pinpwm
  // left_front_encoder_pina
  // left_front_encoder_pinb
  // left_front_motor_p
  // left_front_motor_i
  // left_front_motor_d
  // left_front_motor_max_total_integral
  // left_front_motor_wheel_diameter
  // left_front_motor_pluses_per_revolution
  // left_front_motor_revolutions_per_minute
  // left_back_motor_pina
  // left_back_motor_pinb
  // left_back_motor_pinpwm
  // left_back_encoder_pina
  // left_back_encoder_pinb
  // left_back_motor_p
  // left_back_motor_i
  // left_back_motor_d
  // left_back_motor_max_total_integral
  // left_back_motor_wheel_diameter
  // left_back_motor_pluses_per_revolution
  // left_back_motor_revolutions_per_minute
  // right_front_motor_pina
  // right_front_motor_pinb
  // right_front_motor_pinpwm
  // right_front_encoder_pina
  // right_front_encoder_pinb
  // right_front_motor_p
  // right_front_motor_i
  // right_front_motor_d
  // right_front_motor_max_total_integral
  // right_front_motor_wheel_diameter
  // right_front_motor_pluses_per_revolution
  // right_front_motor_revolutions_per_minute
  // right_back_motor_pina
  // right_back_motor_pinb
  // right_back_motor_pinpwm
  // right_back_encoder_pina
  // right_back_encoder_pinb
  // right_back_motor_p
  // right_back_motor_i
  // right_back_motor_d
  // right_back_motor_max_total_integral
  // right_back_motor_wheel_diameter
  // right_back_motor_pluses_per_revolution
  // right_back_motor_revolutions_per_minute
  // motor_enable_flags
  // enable_speed_plan
  // is_mecanum_wheel
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
  // milliseconds
  // speed_percent
  // max_v
  // max_acc
  // jerk
  // wheel_width
  // track_width
  // left_front_motor_pina
  // left_front_motor_pinb
  // left_front_motor_pinpwm
  // left_front_encoder_pina
  // left_front_encoder_pinb
  // left_front_motor_p
  // left_front_motor_i
  // left_front_motor_d
  // left_front_motor_max_total_integral
  // left_front_motor_wheel_diameter
  // left_front_motor_pluses_per_revolution
  // left_front_motor_revolutions_per_minute
  // left_back_motor_pina
  // left_back_motor_pinb
  // left_back_motor_pinpwm
  // left_back_encoder_pina
  // left_back_encoder_pinb
  // left_back_motor_p
  // left_back_motor_i
  // left_back_motor_d
  // left_back_motor_max_total_integral
  // left_back_motor_wheel_diameter
  // left_back_motor_pluses_per_revolution
  // left_back_motor_revolutions_per_minute
  // right_front_motor_pina
  // right_front_motor_pinb
  // right_front_motor_pinpwm
  // right_front_encoder_pina
  // right_front_encoder_pinb
  // right_front_motor_p
  // right_front_motor_i
  // right_front_motor_d
  // right_front_motor_max_total_integral
  // right_front_motor_wheel_diameter
  // right_front_motor_pluses_per_revolution
  // right_front_motor_revolutions_per_minute
  // right_back_motor_pina
  // right_back_motor_pinb
  // right_back_motor_pinpwm
  // right_back_encoder_pina
  // right_back_encoder_pinb
  // right_back_motor_p
  // right_back_motor_i
  // right_back_motor_d
  // right_back_motor_max_total_integral
  // right_back_motor_wheel_diameter
  // right_back_motor_pluses_per_revolution
  // right_back_motor_revolutions_per_minute
  // motor_enable_flags
  // enable_speed_plan
  // is_mecanum_wheel
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
  // max_acc
  if (lhs->max_acc != rhs->max_acc) {
    return false;
  }
  // jerk
  if (lhs->jerk != rhs->jerk) {
    return false;
  }
  // wheel_width
  if (lhs->wheel_width != rhs->wheel_width) {
    return false;
  }
  // track_width
  if (lhs->track_width != rhs->track_width) {
    return false;
  }
  // left_front_motor_pina
  if (lhs->left_front_motor_pina != rhs->left_front_motor_pina) {
    return false;
  }
  // left_front_motor_pinb
  if (lhs->left_front_motor_pinb != rhs->left_front_motor_pinb) {
    return false;
  }
  // left_front_motor_pinpwm
  if (lhs->left_front_motor_pinpwm != rhs->left_front_motor_pinpwm) {
    return false;
  }
  // left_front_encoder_pina
  if (lhs->left_front_encoder_pina != rhs->left_front_encoder_pina) {
    return false;
  }
  // left_front_encoder_pinb
  if (lhs->left_front_encoder_pinb != rhs->left_front_encoder_pinb) {
    return false;
  }
  // left_front_motor_p
  if (lhs->left_front_motor_p != rhs->left_front_motor_p) {
    return false;
  }
  // left_front_motor_i
  if (lhs->left_front_motor_i != rhs->left_front_motor_i) {
    return false;
  }
  // left_front_motor_d
  if (lhs->left_front_motor_d != rhs->left_front_motor_d) {
    return false;
  }
  // left_front_motor_max_total_integral
  if (lhs->left_front_motor_max_total_integral != rhs->left_front_motor_max_total_integral) {
    return false;
  }
  // left_front_motor_wheel_diameter
  if (lhs->left_front_motor_wheel_diameter != rhs->left_front_motor_wheel_diameter) {
    return false;
  }
  // left_front_motor_pluses_per_revolution
  if (lhs->left_front_motor_pluses_per_revolution != rhs->left_front_motor_pluses_per_revolution) {
    return false;
  }
  // left_front_motor_revolutions_per_minute
  if (lhs->left_front_motor_revolutions_per_minute != rhs->left_front_motor_revolutions_per_minute) {
    return false;
  }
  // left_back_motor_pina
  if (lhs->left_back_motor_pina != rhs->left_back_motor_pina) {
    return false;
  }
  // left_back_motor_pinb
  if (lhs->left_back_motor_pinb != rhs->left_back_motor_pinb) {
    return false;
  }
  // left_back_motor_pinpwm
  if (lhs->left_back_motor_pinpwm != rhs->left_back_motor_pinpwm) {
    return false;
  }
  // left_back_encoder_pina
  if (lhs->left_back_encoder_pina != rhs->left_back_encoder_pina) {
    return false;
  }
  // left_back_encoder_pinb
  if (lhs->left_back_encoder_pinb != rhs->left_back_encoder_pinb) {
    return false;
  }
  // left_back_motor_p
  if (lhs->left_back_motor_p != rhs->left_back_motor_p) {
    return false;
  }
  // left_back_motor_i
  if (lhs->left_back_motor_i != rhs->left_back_motor_i) {
    return false;
  }
  // left_back_motor_d
  if (lhs->left_back_motor_d != rhs->left_back_motor_d) {
    return false;
  }
  // left_back_motor_max_total_integral
  if (lhs->left_back_motor_max_total_integral != rhs->left_back_motor_max_total_integral) {
    return false;
  }
  // left_back_motor_wheel_diameter
  if (lhs->left_back_motor_wheel_diameter != rhs->left_back_motor_wheel_diameter) {
    return false;
  }
  // left_back_motor_pluses_per_revolution
  if (lhs->left_back_motor_pluses_per_revolution != rhs->left_back_motor_pluses_per_revolution) {
    return false;
  }
  // left_back_motor_revolutions_per_minute
  if (lhs->left_back_motor_revolutions_per_minute != rhs->left_back_motor_revolutions_per_minute) {
    return false;
  }
  // right_front_motor_pina
  if (lhs->right_front_motor_pina != rhs->right_front_motor_pina) {
    return false;
  }
  // right_front_motor_pinb
  if (lhs->right_front_motor_pinb != rhs->right_front_motor_pinb) {
    return false;
  }
  // right_front_motor_pinpwm
  if (lhs->right_front_motor_pinpwm != rhs->right_front_motor_pinpwm) {
    return false;
  }
  // right_front_encoder_pina
  if (lhs->right_front_encoder_pina != rhs->right_front_encoder_pina) {
    return false;
  }
  // right_front_encoder_pinb
  if (lhs->right_front_encoder_pinb != rhs->right_front_encoder_pinb) {
    return false;
  }
  // right_front_motor_p
  if (lhs->right_front_motor_p != rhs->right_front_motor_p) {
    return false;
  }
  // right_front_motor_i
  if (lhs->right_front_motor_i != rhs->right_front_motor_i) {
    return false;
  }
  // right_front_motor_d
  if (lhs->right_front_motor_d != rhs->right_front_motor_d) {
    return false;
  }
  // right_front_motor_max_total_integral
  if (lhs->right_front_motor_max_total_integral != rhs->right_front_motor_max_total_integral) {
    return false;
  }
  // right_front_motor_wheel_diameter
  if (lhs->right_front_motor_wheel_diameter != rhs->right_front_motor_wheel_diameter) {
    return false;
  }
  // right_front_motor_pluses_per_revolution
  if (lhs->right_front_motor_pluses_per_revolution != rhs->right_front_motor_pluses_per_revolution) {
    return false;
  }
  // right_front_motor_revolutions_per_minute
  if (lhs->right_front_motor_revolutions_per_minute != rhs->right_front_motor_revolutions_per_minute) {
    return false;
  }
  // right_back_motor_pina
  if (lhs->right_back_motor_pina != rhs->right_back_motor_pina) {
    return false;
  }
  // right_back_motor_pinb
  if (lhs->right_back_motor_pinb != rhs->right_back_motor_pinb) {
    return false;
  }
  // right_back_motor_pinpwm
  if (lhs->right_back_motor_pinpwm != rhs->right_back_motor_pinpwm) {
    return false;
  }
  // right_back_encoder_pina
  if (lhs->right_back_encoder_pina != rhs->right_back_encoder_pina) {
    return false;
  }
  // right_back_encoder_pinb
  if (lhs->right_back_encoder_pinb != rhs->right_back_encoder_pinb) {
    return false;
  }
  // right_back_motor_p
  if (lhs->right_back_motor_p != rhs->right_back_motor_p) {
    return false;
  }
  // right_back_motor_i
  if (lhs->right_back_motor_i != rhs->right_back_motor_i) {
    return false;
  }
  // right_back_motor_d
  if (lhs->right_back_motor_d != rhs->right_back_motor_d) {
    return false;
  }
  // right_back_motor_max_total_integral
  if (lhs->right_back_motor_max_total_integral != rhs->right_back_motor_max_total_integral) {
    return false;
  }
  // right_back_motor_wheel_diameter
  if (lhs->right_back_motor_wheel_diameter != rhs->right_back_motor_wheel_diameter) {
    return false;
  }
  // right_back_motor_pluses_per_revolution
  if (lhs->right_back_motor_pluses_per_revolution != rhs->right_back_motor_pluses_per_revolution) {
    return false;
  }
  // right_back_motor_revolutions_per_minute
  if (lhs->right_back_motor_revolutions_per_minute != rhs->right_back_motor_revolutions_per_minute) {
    return false;
  }
  // motor_enable_flags
  if (lhs->motor_enable_flags != rhs->motor_enable_flags) {
    return false;
  }
  // enable_speed_plan
  if (lhs->enable_speed_plan != rhs->enable_speed_plan) {
    return false;
  }
  // is_mecanum_wheel
  if (lhs->is_mecanum_wheel != rhs->is_mecanum_wheel) {
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
  // milliseconds
  output->milliseconds = input->milliseconds;
  // speed_percent
  output->speed_percent = input->speed_percent;
  // max_v
  output->max_v = input->max_v;
  // max_acc
  output->max_acc = input->max_acc;
  // jerk
  output->jerk = input->jerk;
  // wheel_width
  output->wheel_width = input->wheel_width;
  // track_width
  output->track_width = input->track_width;
  // left_front_motor_pina
  output->left_front_motor_pina = input->left_front_motor_pina;
  // left_front_motor_pinb
  output->left_front_motor_pinb = input->left_front_motor_pinb;
  // left_front_motor_pinpwm
  output->left_front_motor_pinpwm = input->left_front_motor_pinpwm;
  // left_front_encoder_pina
  output->left_front_encoder_pina = input->left_front_encoder_pina;
  // left_front_encoder_pinb
  output->left_front_encoder_pinb = input->left_front_encoder_pinb;
  // left_front_motor_p
  output->left_front_motor_p = input->left_front_motor_p;
  // left_front_motor_i
  output->left_front_motor_i = input->left_front_motor_i;
  // left_front_motor_d
  output->left_front_motor_d = input->left_front_motor_d;
  // left_front_motor_max_total_integral
  output->left_front_motor_max_total_integral = input->left_front_motor_max_total_integral;
  // left_front_motor_wheel_diameter
  output->left_front_motor_wheel_diameter = input->left_front_motor_wheel_diameter;
  // left_front_motor_pluses_per_revolution
  output->left_front_motor_pluses_per_revolution = input->left_front_motor_pluses_per_revolution;
  // left_front_motor_revolutions_per_minute
  output->left_front_motor_revolutions_per_minute = input->left_front_motor_revolutions_per_minute;
  // left_back_motor_pina
  output->left_back_motor_pina = input->left_back_motor_pina;
  // left_back_motor_pinb
  output->left_back_motor_pinb = input->left_back_motor_pinb;
  // left_back_motor_pinpwm
  output->left_back_motor_pinpwm = input->left_back_motor_pinpwm;
  // left_back_encoder_pina
  output->left_back_encoder_pina = input->left_back_encoder_pina;
  // left_back_encoder_pinb
  output->left_back_encoder_pinb = input->left_back_encoder_pinb;
  // left_back_motor_p
  output->left_back_motor_p = input->left_back_motor_p;
  // left_back_motor_i
  output->left_back_motor_i = input->left_back_motor_i;
  // left_back_motor_d
  output->left_back_motor_d = input->left_back_motor_d;
  // left_back_motor_max_total_integral
  output->left_back_motor_max_total_integral = input->left_back_motor_max_total_integral;
  // left_back_motor_wheel_diameter
  output->left_back_motor_wheel_diameter = input->left_back_motor_wheel_diameter;
  // left_back_motor_pluses_per_revolution
  output->left_back_motor_pluses_per_revolution = input->left_back_motor_pluses_per_revolution;
  // left_back_motor_revolutions_per_minute
  output->left_back_motor_revolutions_per_minute = input->left_back_motor_revolutions_per_minute;
  // right_front_motor_pina
  output->right_front_motor_pina = input->right_front_motor_pina;
  // right_front_motor_pinb
  output->right_front_motor_pinb = input->right_front_motor_pinb;
  // right_front_motor_pinpwm
  output->right_front_motor_pinpwm = input->right_front_motor_pinpwm;
  // right_front_encoder_pina
  output->right_front_encoder_pina = input->right_front_encoder_pina;
  // right_front_encoder_pinb
  output->right_front_encoder_pinb = input->right_front_encoder_pinb;
  // right_front_motor_p
  output->right_front_motor_p = input->right_front_motor_p;
  // right_front_motor_i
  output->right_front_motor_i = input->right_front_motor_i;
  // right_front_motor_d
  output->right_front_motor_d = input->right_front_motor_d;
  // right_front_motor_max_total_integral
  output->right_front_motor_max_total_integral = input->right_front_motor_max_total_integral;
  // right_front_motor_wheel_diameter
  output->right_front_motor_wheel_diameter = input->right_front_motor_wheel_diameter;
  // right_front_motor_pluses_per_revolution
  output->right_front_motor_pluses_per_revolution = input->right_front_motor_pluses_per_revolution;
  // right_front_motor_revolutions_per_minute
  output->right_front_motor_revolutions_per_minute = input->right_front_motor_revolutions_per_minute;
  // right_back_motor_pina
  output->right_back_motor_pina = input->right_back_motor_pina;
  // right_back_motor_pinb
  output->right_back_motor_pinb = input->right_back_motor_pinb;
  // right_back_motor_pinpwm
  output->right_back_motor_pinpwm = input->right_back_motor_pinpwm;
  // right_back_encoder_pina
  output->right_back_encoder_pina = input->right_back_encoder_pina;
  // right_back_encoder_pinb
  output->right_back_encoder_pinb = input->right_back_encoder_pinb;
  // right_back_motor_p
  output->right_back_motor_p = input->right_back_motor_p;
  // right_back_motor_i
  output->right_back_motor_i = input->right_back_motor_i;
  // right_back_motor_d
  output->right_back_motor_d = input->right_back_motor_d;
  // right_back_motor_max_total_integral
  output->right_back_motor_max_total_integral = input->right_back_motor_max_total_integral;
  // right_back_motor_wheel_diameter
  output->right_back_motor_wheel_diameter = input->right_back_motor_wheel_diameter;
  // right_back_motor_pluses_per_revolution
  output->right_back_motor_pluses_per_revolution = input->right_back_motor_pluses_per_revolution;
  // right_back_motor_revolutions_per_minute
  output->right_back_motor_revolutions_per_minute = input->right_back_motor_revolutions_per_minute;
  // motor_enable_flags
  output->motor_enable_flags = input->motor_enable_flags;
  // enable_speed_plan
  output->enable_speed_plan = input->enable_speed_plan;
  // is_mecanum_wheel
  output->is_mecanum_wheel = input->is_mecanum_wheel;
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


bool
motion_settings_service__srv__MotionSettingsService_Response__init(motion_settings_service__srv__MotionSettingsService_Response * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // state
  // milliseconds
  // speed_percent
  // max_v
  // max_acc
  // jerk
  // wheel_width
  // track_width
  // left_front_motor_pina
  // left_front_motor_pinb
  // left_front_motor_pinpwm
  // left_front_encoder_pina
  // left_front_encoder_pinb
  // left_front_motor_p
  // left_front_motor_i
  // left_front_motor_d
  // left_front_motor_max_total_integral
  // left_front_motor_wheel_diameter
  // left_front_motor_pluses_per_revolution
  // left_front_motor_revolutions_per_minute
  // left_back_motor_pina
  // left_back_motor_pinb
  // left_back_motor_pinpwm
  // left_back_encoder_pina
  // left_back_encoder_pinb
  // left_back_motor_p
  // left_back_motor_i
  // left_back_motor_d
  // left_back_motor_max_total_integral
  // left_back_motor_wheel_diameter
  // left_back_motor_pluses_per_revolution
  // left_back_motor_revolutions_per_minute
  // right_front_motor_pina
  // right_front_motor_pinb
  // right_front_motor_pinpwm
  // right_front_encoder_pina
  // right_front_encoder_pinb
  // right_front_motor_p
  // right_front_motor_i
  // right_front_motor_d
  // right_front_motor_max_total_integral
  // right_front_motor_wheel_diameter
  // right_front_motor_pluses_per_revolution
  // right_front_motor_revolutions_per_minute
  // right_back_motor_pina
  // right_back_motor_pinb
  // right_back_motor_pinpwm
  // right_back_encoder_pina
  // right_back_encoder_pinb
  // right_back_motor_p
  // right_back_motor_i
  // right_back_motor_d
  // right_back_motor_max_total_integral
  // right_back_motor_wheel_diameter
  // right_back_motor_pluses_per_revolution
  // right_back_motor_revolutions_per_minute
  // motor_enable_flags
  // enable_speed_plan
  // is_mecanum_wheel
  return true;
}

void
motion_settings_service__srv__MotionSettingsService_Response__fini(motion_settings_service__srv__MotionSettingsService_Response * msg)
{
  if (!msg) {
    return;
  }
  // id
  // state
  // milliseconds
  // speed_percent
  // max_v
  // max_acc
  // jerk
  // wheel_width
  // track_width
  // left_front_motor_pina
  // left_front_motor_pinb
  // left_front_motor_pinpwm
  // left_front_encoder_pina
  // left_front_encoder_pinb
  // left_front_motor_p
  // left_front_motor_i
  // left_front_motor_d
  // left_front_motor_max_total_integral
  // left_front_motor_wheel_diameter
  // left_front_motor_pluses_per_revolution
  // left_front_motor_revolutions_per_minute
  // left_back_motor_pina
  // left_back_motor_pinb
  // left_back_motor_pinpwm
  // left_back_encoder_pina
  // left_back_encoder_pinb
  // left_back_motor_p
  // left_back_motor_i
  // left_back_motor_d
  // left_back_motor_max_total_integral
  // left_back_motor_wheel_diameter
  // left_back_motor_pluses_per_revolution
  // left_back_motor_revolutions_per_minute
  // right_front_motor_pina
  // right_front_motor_pinb
  // right_front_motor_pinpwm
  // right_front_encoder_pina
  // right_front_encoder_pinb
  // right_front_motor_p
  // right_front_motor_i
  // right_front_motor_d
  // right_front_motor_max_total_integral
  // right_front_motor_wheel_diameter
  // right_front_motor_pluses_per_revolution
  // right_front_motor_revolutions_per_minute
  // right_back_motor_pina
  // right_back_motor_pinb
  // right_back_motor_pinpwm
  // right_back_encoder_pina
  // right_back_encoder_pinb
  // right_back_motor_p
  // right_back_motor_i
  // right_back_motor_d
  // right_back_motor_max_total_integral
  // right_back_motor_wheel_diameter
  // right_back_motor_pluses_per_revolution
  // right_back_motor_revolutions_per_minute
  // motor_enable_flags
  // enable_speed_plan
  // is_mecanum_wheel
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
  // state
  if (lhs->state != rhs->state) {
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
  // max_acc
  if (lhs->max_acc != rhs->max_acc) {
    return false;
  }
  // jerk
  if (lhs->jerk != rhs->jerk) {
    return false;
  }
  // wheel_width
  if (lhs->wheel_width != rhs->wheel_width) {
    return false;
  }
  // track_width
  if (lhs->track_width != rhs->track_width) {
    return false;
  }
  // left_front_motor_pina
  if (lhs->left_front_motor_pina != rhs->left_front_motor_pina) {
    return false;
  }
  // left_front_motor_pinb
  if (lhs->left_front_motor_pinb != rhs->left_front_motor_pinb) {
    return false;
  }
  // left_front_motor_pinpwm
  if (lhs->left_front_motor_pinpwm != rhs->left_front_motor_pinpwm) {
    return false;
  }
  // left_front_encoder_pina
  if (lhs->left_front_encoder_pina != rhs->left_front_encoder_pina) {
    return false;
  }
  // left_front_encoder_pinb
  if (lhs->left_front_encoder_pinb != rhs->left_front_encoder_pinb) {
    return false;
  }
  // left_front_motor_p
  if (lhs->left_front_motor_p != rhs->left_front_motor_p) {
    return false;
  }
  // left_front_motor_i
  if (lhs->left_front_motor_i != rhs->left_front_motor_i) {
    return false;
  }
  // left_front_motor_d
  if (lhs->left_front_motor_d != rhs->left_front_motor_d) {
    return false;
  }
  // left_front_motor_max_total_integral
  if (lhs->left_front_motor_max_total_integral != rhs->left_front_motor_max_total_integral) {
    return false;
  }
  // left_front_motor_wheel_diameter
  if (lhs->left_front_motor_wheel_diameter != rhs->left_front_motor_wheel_diameter) {
    return false;
  }
  // left_front_motor_pluses_per_revolution
  if (lhs->left_front_motor_pluses_per_revolution != rhs->left_front_motor_pluses_per_revolution) {
    return false;
  }
  // left_front_motor_revolutions_per_minute
  if (lhs->left_front_motor_revolutions_per_minute != rhs->left_front_motor_revolutions_per_minute) {
    return false;
  }
  // left_back_motor_pina
  if (lhs->left_back_motor_pina != rhs->left_back_motor_pina) {
    return false;
  }
  // left_back_motor_pinb
  if (lhs->left_back_motor_pinb != rhs->left_back_motor_pinb) {
    return false;
  }
  // left_back_motor_pinpwm
  if (lhs->left_back_motor_pinpwm != rhs->left_back_motor_pinpwm) {
    return false;
  }
  // left_back_encoder_pina
  if (lhs->left_back_encoder_pina != rhs->left_back_encoder_pina) {
    return false;
  }
  // left_back_encoder_pinb
  if (lhs->left_back_encoder_pinb != rhs->left_back_encoder_pinb) {
    return false;
  }
  // left_back_motor_p
  if (lhs->left_back_motor_p != rhs->left_back_motor_p) {
    return false;
  }
  // left_back_motor_i
  if (lhs->left_back_motor_i != rhs->left_back_motor_i) {
    return false;
  }
  // left_back_motor_d
  if (lhs->left_back_motor_d != rhs->left_back_motor_d) {
    return false;
  }
  // left_back_motor_max_total_integral
  if (lhs->left_back_motor_max_total_integral != rhs->left_back_motor_max_total_integral) {
    return false;
  }
  // left_back_motor_wheel_diameter
  if (lhs->left_back_motor_wheel_diameter != rhs->left_back_motor_wheel_diameter) {
    return false;
  }
  // left_back_motor_pluses_per_revolution
  if (lhs->left_back_motor_pluses_per_revolution != rhs->left_back_motor_pluses_per_revolution) {
    return false;
  }
  // left_back_motor_revolutions_per_minute
  if (lhs->left_back_motor_revolutions_per_minute != rhs->left_back_motor_revolutions_per_minute) {
    return false;
  }
  // right_front_motor_pina
  if (lhs->right_front_motor_pina != rhs->right_front_motor_pina) {
    return false;
  }
  // right_front_motor_pinb
  if (lhs->right_front_motor_pinb != rhs->right_front_motor_pinb) {
    return false;
  }
  // right_front_motor_pinpwm
  if (lhs->right_front_motor_pinpwm != rhs->right_front_motor_pinpwm) {
    return false;
  }
  // right_front_encoder_pina
  if (lhs->right_front_encoder_pina != rhs->right_front_encoder_pina) {
    return false;
  }
  // right_front_encoder_pinb
  if (lhs->right_front_encoder_pinb != rhs->right_front_encoder_pinb) {
    return false;
  }
  // right_front_motor_p
  if (lhs->right_front_motor_p != rhs->right_front_motor_p) {
    return false;
  }
  // right_front_motor_i
  if (lhs->right_front_motor_i != rhs->right_front_motor_i) {
    return false;
  }
  // right_front_motor_d
  if (lhs->right_front_motor_d != rhs->right_front_motor_d) {
    return false;
  }
  // right_front_motor_max_total_integral
  if (lhs->right_front_motor_max_total_integral != rhs->right_front_motor_max_total_integral) {
    return false;
  }
  // right_front_motor_wheel_diameter
  if (lhs->right_front_motor_wheel_diameter != rhs->right_front_motor_wheel_diameter) {
    return false;
  }
  // right_front_motor_pluses_per_revolution
  if (lhs->right_front_motor_pluses_per_revolution != rhs->right_front_motor_pluses_per_revolution) {
    return false;
  }
  // right_front_motor_revolutions_per_minute
  if (lhs->right_front_motor_revolutions_per_minute != rhs->right_front_motor_revolutions_per_minute) {
    return false;
  }
  // right_back_motor_pina
  if (lhs->right_back_motor_pina != rhs->right_back_motor_pina) {
    return false;
  }
  // right_back_motor_pinb
  if (lhs->right_back_motor_pinb != rhs->right_back_motor_pinb) {
    return false;
  }
  // right_back_motor_pinpwm
  if (lhs->right_back_motor_pinpwm != rhs->right_back_motor_pinpwm) {
    return false;
  }
  // right_back_encoder_pina
  if (lhs->right_back_encoder_pina != rhs->right_back_encoder_pina) {
    return false;
  }
  // right_back_encoder_pinb
  if (lhs->right_back_encoder_pinb != rhs->right_back_encoder_pinb) {
    return false;
  }
  // right_back_motor_p
  if (lhs->right_back_motor_p != rhs->right_back_motor_p) {
    return false;
  }
  // right_back_motor_i
  if (lhs->right_back_motor_i != rhs->right_back_motor_i) {
    return false;
  }
  // right_back_motor_d
  if (lhs->right_back_motor_d != rhs->right_back_motor_d) {
    return false;
  }
  // right_back_motor_max_total_integral
  if (lhs->right_back_motor_max_total_integral != rhs->right_back_motor_max_total_integral) {
    return false;
  }
  // right_back_motor_wheel_diameter
  if (lhs->right_back_motor_wheel_diameter != rhs->right_back_motor_wheel_diameter) {
    return false;
  }
  // right_back_motor_pluses_per_revolution
  if (lhs->right_back_motor_pluses_per_revolution != rhs->right_back_motor_pluses_per_revolution) {
    return false;
  }
  // right_back_motor_revolutions_per_minute
  if (lhs->right_back_motor_revolutions_per_minute != rhs->right_back_motor_revolutions_per_minute) {
    return false;
  }
  // motor_enable_flags
  if (lhs->motor_enable_flags != rhs->motor_enable_flags) {
    return false;
  }
  // enable_speed_plan
  if (lhs->enable_speed_plan != rhs->enable_speed_plan) {
    return false;
  }
  // is_mecanum_wheel
  if (lhs->is_mecanum_wheel != rhs->is_mecanum_wheel) {
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
  // state
  output->state = input->state;
  // milliseconds
  output->milliseconds = input->milliseconds;
  // speed_percent
  output->speed_percent = input->speed_percent;
  // max_v
  output->max_v = input->max_v;
  // max_acc
  output->max_acc = input->max_acc;
  // jerk
  output->jerk = input->jerk;
  // wheel_width
  output->wheel_width = input->wheel_width;
  // track_width
  output->track_width = input->track_width;
  // left_front_motor_pina
  output->left_front_motor_pina = input->left_front_motor_pina;
  // left_front_motor_pinb
  output->left_front_motor_pinb = input->left_front_motor_pinb;
  // left_front_motor_pinpwm
  output->left_front_motor_pinpwm = input->left_front_motor_pinpwm;
  // left_front_encoder_pina
  output->left_front_encoder_pina = input->left_front_encoder_pina;
  // left_front_encoder_pinb
  output->left_front_encoder_pinb = input->left_front_encoder_pinb;
  // left_front_motor_p
  output->left_front_motor_p = input->left_front_motor_p;
  // left_front_motor_i
  output->left_front_motor_i = input->left_front_motor_i;
  // left_front_motor_d
  output->left_front_motor_d = input->left_front_motor_d;
  // left_front_motor_max_total_integral
  output->left_front_motor_max_total_integral = input->left_front_motor_max_total_integral;
  // left_front_motor_wheel_diameter
  output->left_front_motor_wheel_diameter = input->left_front_motor_wheel_diameter;
  // left_front_motor_pluses_per_revolution
  output->left_front_motor_pluses_per_revolution = input->left_front_motor_pluses_per_revolution;
  // left_front_motor_revolutions_per_minute
  output->left_front_motor_revolutions_per_minute = input->left_front_motor_revolutions_per_minute;
  // left_back_motor_pina
  output->left_back_motor_pina = input->left_back_motor_pina;
  // left_back_motor_pinb
  output->left_back_motor_pinb = input->left_back_motor_pinb;
  // left_back_motor_pinpwm
  output->left_back_motor_pinpwm = input->left_back_motor_pinpwm;
  // left_back_encoder_pina
  output->left_back_encoder_pina = input->left_back_encoder_pina;
  // left_back_encoder_pinb
  output->left_back_encoder_pinb = input->left_back_encoder_pinb;
  // left_back_motor_p
  output->left_back_motor_p = input->left_back_motor_p;
  // left_back_motor_i
  output->left_back_motor_i = input->left_back_motor_i;
  // left_back_motor_d
  output->left_back_motor_d = input->left_back_motor_d;
  // left_back_motor_max_total_integral
  output->left_back_motor_max_total_integral = input->left_back_motor_max_total_integral;
  // left_back_motor_wheel_diameter
  output->left_back_motor_wheel_diameter = input->left_back_motor_wheel_diameter;
  // left_back_motor_pluses_per_revolution
  output->left_back_motor_pluses_per_revolution = input->left_back_motor_pluses_per_revolution;
  // left_back_motor_revolutions_per_minute
  output->left_back_motor_revolutions_per_minute = input->left_back_motor_revolutions_per_minute;
  // right_front_motor_pina
  output->right_front_motor_pina = input->right_front_motor_pina;
  // right_front_motor_pinb
  output->right_front_motor_pinb = input->right_front_motor_pinb;
  // right_front_motor_pinpwm
  output->right_front_motor_pinpwm = input->right_front_motor_pinpwm;
  // right_front_encoder_pina
  output->right_front_encoder_pina = input->right_front_encoder_pina;
  // right_front_encoder_pinb
  output->right_front_encoder_pinb = input->right_front_encoder_pinb;
  // right_front_motor_p
  output->right_front_motor_p = input->right_front_motor_p;
  // right_front_motor_i
  output->right_front_motor_i = input->right_front_motor_i;
  // right_front_motor_d
  output->right_front_motor_d = input->right_front_motor_d;
  // right_front_motor_max_total_integral
  output->right_front_motor_max_total_integral = input->right_front_motor_max_total_integral;
  // right_front_motor_wheel_diameter
  output->right_front_motor_wheel_diameter = input->right_front_motor_wheel_diameter;
  // right_front_motor_pluses_per_revolution
  output->right_front_motor_pluses_per_revolution = input->right_front_motor_pluses_per_revolution;
  // right_front_motor_revolutions_per_minute
  output->right_front_motor_revolutions_per_minute = input->right_front_motor_revolutions_per_minute;
  // right_back_motor_pina
  output->right_back_motor_pina = input->right_back_motor_pina;
  // right_back_motor_pinb
  output->right_back_motor_pinb = input->right_back_motor_pinb;
  // right_back_motor_pinpwm
  output->right_back_motor_pinpwm = input->right_back_motor_pinpwm;
  // right_back_encoder_pina
  output->right_back_encoder_pina = input->right_back_encoder_pina;
  // right_back_encoder_pinb
  output->right_back_encoder_pinb = input->right_back_encoder_pinb;
  // right_back_motor_p
  output->right_back_motor_p = input->right_back_motor_p;
  // right_back_motor_i
  output->right_back_motor_i = input->right_back_motor_i;
  // right_back_motor_d
  output->right_back_motor_d = input->right_back_motor_d;
  // right_back_motor_max_total_integral
  output->right_back_motor_max_total_integral = input->right_back_motor_max_total_integral;
  // right_back_motor_wheel_diameter
  output->right_back_motor_wheel_diameter = input->right_back_motor_wheel_diameter;
  // right_back_motor_pluses_per_revolution
  output->right_back_motor_pluses_per_revolution = input->right_back_motor_pluses_per_revolution;
  // right_back_motor_revolutions_per_minute
  output->right_back_motor_revolutions_per_minute = input->right_back_motor_revolutions_per_minute;
  // motor_enable_flags
  output->motor_enable_flags = input->motor_enable_flags;
  // enable_speed_plan
  output->enable_speed_plan = input->enable_speed_plan;
  // is_mecanum_wheel
  output->is_mecanum_wheel = input->is_mecanum_wheel;
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
