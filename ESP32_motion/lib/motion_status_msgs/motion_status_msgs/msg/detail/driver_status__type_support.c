// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motion_status_msgs:msg/DriverStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motion_status_msgs/msg/detail/driver_status__rosidl_typesupport_introspection_c.h"
#include "motion_status_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motion_status_msgs/msg/detail/driver_status__functions.h"
#include "motion_status_msgs/msg/detail/driver_status__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motion_status_msgs__msg__DriverStatus__init(message_memory);
}

void motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_fini_function(void * message_memory)
{
  motion_status_msgs__msg__DriverStatus__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_message_member_array[4] = {
  {
    "total_distance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_status_msgs__msg__DriverStatus, total_distance),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dt_distance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_status_msgs__msg__DriverStatus, dt_distance),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_v",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_status_msgs__msg__DriverStatus, current_v),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_v",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_status_msgs__msg__DriverStatus, target_v),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_message_members = {
  "motion_status_msgs__msg",  // message namespace
  "DriverStatus",  // message name
  4,  // number of fields
  sizeof(motion_status_msgs__msg__DriverStatus),
  motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_message_member_array,  // message members
  motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_message_type_support_handle = {
  0,
  &motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motion_status_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_status_msgs, msg, DriverStatus)() {
  if (!motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_message_type_support_handle.typesupport_identifier) {
    motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motion_status_msgs__msg__DriverStatus__rosidl_typesupport_introspection_c__DriverStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
