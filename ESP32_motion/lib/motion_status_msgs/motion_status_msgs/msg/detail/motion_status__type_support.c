// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motion_status_msgs:msg/MotionStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motion_status_msgs/msg/detail/motion_status__rosidl_typesupport_introspection_c.h"
#include "motion_status_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motion_status_msgs/msg/detail/motion_status__functions.h"
#include "motion_status_msgs/msg/detail/motion_status__struct.h"


// Include directives for member types
// Member `drivers_status`
#include "motion_status_msgs/msg/driver_status.h"
// Member `drivers_status`
#include "motion_status_msgs/msg/detail/driver_status__rosidl_typesupport_introspection_c.h"
// Member `sensor_status`
#include "motion_status_msgs/msg/sensor_status.h"
// Member `sensor_status`
#include "motion_status_msgs/msg/detail/sensor_status__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motion_status_msgs__msg__MotionStatus__init(message_memory);
}

void motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_fini_function(void * message_memory)
{
  motion_status_msgs__msg__MotionStatus__fini(message_memory);
}

size_t motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__size_function__MotionStatus__drivers_status(
  const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__get_const_function__MotionStatus__drivers_status(
  const void * untyped_member, size_t index)
{
  const motion_status_msgs__msg__DriverStatus * member =
    (const motion_status_msgs__msg__DriverStatus *)(untyped_member);
  return &member[index];
}

void * motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__get_function__MotionStatus__drivers_status(
  void * untyped_member, size_t index)
{
  motion_status_msgs__msg__DriverStatus * member =
    (motion_status_msgs__msg__DriverStatus *)(untyped_member);
  return &member[index];
}

void motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__fetch_function__MotionStatus__drivers_status(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const motion_status_msgs__msg__DriverStatus * item =
    ((const motion_status_msgs__msg__DriverStatus *)
    motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__get_const_function__MotionStatus__drivers_status(untyped_member, index));
  motion_status_msgs__msg__DriverStatus * value =
    (motion_status_msgs__msg__DriverStatus *)(untyped_value);
  *value = *item;
}

void motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__assign_function__MotionStatus__drivers_status(
  void * untyped_member, size_t index, const void * untyped_value)
{
  motion_status_msgs__msg__DriverStatus * item =
    ((motion_status_msgs__msg__DriverStatus *)
    motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__get_function__MotionStatus__drivers_status(untyped_member, index));
  const motion_status_msgs__msg__DriverStatus * value =
    (const motion_status_msgs__msg__DriverStatus *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_member_array[4] = {
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_status_msgs__msg__MotionStatus, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "seq",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_status_msgs__msg__MotionStatus, seq),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drivers_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(motion_status_msgs__msg__MotionStatus, drivers_status),  // bytes offset in struct
    NULL,  // default value
    motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__size_function__MotionStatus__drivers_status,  // size() function pointer
    motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__get_const_function__MotionStatus__drivers_status,  // get_const(index) function pointer
    motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__get_function__MotionStatus__drivers_status,  // get(index) function pointer
    motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__fetch_function__MotionStatus__drivers_status,  // fetch(index, &value) function pointer
    motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__assign_function__MotionStatus__drivers_status,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sensor_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_status_msgs__msg__MotionStatus, sensor_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_members = {
  "motion_status_msgs__msg",  // message namespace
  "MotionStatus",  // message name
  4,  // number of fields
  sizeof(motion_status_msgs__msg__MotionStatus),
  motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_member_array,  // message members
  motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_type_support_handle = {
  0,
  &motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motion_status_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_status_msgs, msg, MotionStatus)() {
  motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_status_msgs, msg, DriverStatus)();
  motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_status_msgs, msg, SensorStatus)();
  if (!motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_type_support_handle.typesupport_identifier) {
    motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motion_status_msgs__msg__MotionStatus__rosidl_typesupport_introspection_c__MotionStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
