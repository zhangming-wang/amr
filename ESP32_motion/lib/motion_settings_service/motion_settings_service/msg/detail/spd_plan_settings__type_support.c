// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motion_settings_service:msg/SpdPlanSettings.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motion_settings_service/msg/detail/spd_plan_settings__rosidl_typesupport_introspection_c.h"
#include "motion_settings_service/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motion_settings_service/msg/detail/spd_plan_settings__functions.h"
#include "motion_settings_service/msg/detail/spd_plan_settings__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motion_settings_service__msg__SpdPlanSettings__init(message_memory);
}

void motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_fini_function(void * message_memory)
{
  motion_settings_service__msg__SpdPlanSettings__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_message_member_array[6] = {
  {
    "milliseconds",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__msg__SpdPlanSettings, milliseconds),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__msg__SpdPlanSettings, speed_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_v",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__msg__SpdPlanSettings, max_v),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_acc",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__msg__SpdPlanSettings, max_acc),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "jerk",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__msg__SpdPlanSettings, jerk),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "enable",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__msg__SpdPlanSettings, enable),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_message_members = {
  "motion_settings_service__msg",  // message namespace
  "SpdPlanSettings",  // message name
  6,  // number of fields
  sizeof(motion_settings_service__msg__SpdPlanSettings),
  motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_message_member_array,  // message members
  motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_init_function,  // function to initialize message memory (memory has to be allocated)
  motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_message_type_support_handle = {
  0,
  &motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motion_settings_service
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, msg, SpdPlanSettings)() {
  if (!motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_message_type_support_handle.typesupport_identifier) {
    motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motion_settings_service__msg__SpdPlanSettings__rosidl_typesupport_introspection_c__SpdPlanSettings_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
