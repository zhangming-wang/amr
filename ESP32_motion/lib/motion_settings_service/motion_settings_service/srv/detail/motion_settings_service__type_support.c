// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motion_settings_service:srv/MotionSettingsService.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motion_settings_service/srv/detail/motion_settings_service__rosidl_typesupport_introspection_c.h"
#include "motion_settings_service/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motion_settings_service/srv/detail/motion_settings_service__functions.h"
#include "motion_settings_service/srv/detail/motion_settings_service__struct.h"


// Include directives for member types
// Member `drivers_settings`
#include "motion_settings_service/msg/driver_settings.h"
// Member `drivers_settings`
#include "motion_settings_service/msg/detail/driver_settings__rosidl_typesupport_introspection_c.h"
// Member `sensor_settings`
#include "motion_settings_service/msg/sensor_settings.h"
// Member `sensor_settings`
#include "motion_settings_service/msg/detail/sensor_settings__rosidl_typesupport_introspection_c.h"
// Member `spd_plan_settings`
#include "motion_settings_service/msg/spd_plan_settings.h"
// Member `spd_plan_settings`
#include "motion_settings_service/msg/detail/spd_plan_settings__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motion_settings_service__srv__MotionSettingsService_Request__init(message_memory);
}

void motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_fini_function(void * message_memory)
{
  motion_settings_service__srv__MotionSettingsService_Request__fini(message_memory);
}

size_t motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__size_function__MotionSettingsService_Request__drivers_settings(
  const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__get_const_function__MotionSettingsService_Request__drivers_settings(
  const void * untyped_member, size_t index)
{
  const motion_settings_service__msg__DriverSettings * member =
    (const motion_settings_service__msg__DriverSettings *)(untyped_member);
  return &member[index];
}

void * motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__get_function__MotionSettingsService_Request__drivers_settings(
  void * untyped_member, size_t index)
{
  motion_settings_service__msg__DriverSettings * member =
    (motion_settings_service__msg__DriverSettings *)(untyped_member);
  return &member[index];
}

void motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__fetch_function__MotionSettingsService_Request__drivers_settings(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const motion_settings_service__msg__DriverSettings * item =
    ((const motion_settings_service__msg__DriverSettings *)
    motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__get_const_function__MotionSettingsService_Request__drivers_settings(untyped_member, index));
  motion_settings_service__msg__DriverSettings * value =
    (motion_settings_service__msg__DriverSettings *)(untyped_value);
  *value = *item;
}

void motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__assign_function__MotionSettingsService_Request__drivers_settings(
  void * untyped_member, size_t index, const void * untyped_value)
{
  motion_settings_service__msg__DriverSettings * item =
    ((motion_settings_service__msg__DriverSettings *)
    motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__get_function__MotionSettingsService_Request__drivers_settings(untyped_member, index));
  const motion_settings_service__msg__DriverSettings * value =
    (const motion_settings_service__msg__DriverSettings *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_member_array[9] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "wheel_width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, wheel_width),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "track_width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, track_width),  // bytes offset in struct
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
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, speed_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drivers_settings",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, drivers_settings),  // bytes offset in struct
    NULL,  // default value
    motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__size_function__MotionSettingsService_Request__drivers_settings,  // size() function pointer
    motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__get_const_function__MotionSettingsService_Request__drivers_settings,  // get_const(index) function pointer
    motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__get_function__MotionSettingsService_Request__drivers_settings,  // get(index) function pointer
    motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__fetch_function__MotionSettingsService_Request__drivers_settings,  // fetch(index, &value) function pointer
    motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__assign_function__MotionSettingsService_Request__drivers_settings,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sensor_settings",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, sensor_settings),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "spd_plan_settings",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, spd_plan_settings),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor_enable_flags",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Request, motor_enable_flags),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_members = {
  "motion_settings_service__srv",  // message namespace
  "MotionSettingsService_Request",  // message name
  9,  // number of fields
  sizeof(motion_settings_service__srv__MotionSettingsService_Request),
  motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_member_array,  // message members
  motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_type_support_handle = {
  0,
  &motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motion_settings_service
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, srv, MotionSettingsService_Request)() {
  motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, msg, DriverSettings)();
  motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, msg, SensorSettings)();
  motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_member_array[7].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, msg, SpdPlanSettings)();
  if (!motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_type_support_handle.typesupport_identifier) {
    motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motion_settings_service__srv__MotionSettingsService_Request__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "motion_settings_service/srv/detail/motion_settings_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "motion_settings_service/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "motion_settings_service/srv/detail/motion_settings_service__functions.h"
// already included above
// #include "motion_settings_service/srv/detail/motion_settings_service__struct.h"


// Include directives for member types
// Member `drivers_settings`
// already included above
// #include "motion_settings_service/msg/driver_settings.h"
// Member `drivers_settings`
// already included above
// #include "motion_settings_service/msg/detail/driver_settings__rosidl_typesupport_introspection_c.h"
// Member `sensor_settings`
// already included above
// #include "motion_settings_service/msg/sensor_settings.h"
// Member `sensor_settings`
// already included above
// #include "motion_settings_service/msg/detail/sensor_settings__rosidl_typesupport_introspection_c.h"
// Member `spd_plan_settings`
// already included above
// #include "motion_settings_service/msg/spd_plan_settings.h"
// Member `spd_plan_settings`
// already included above
// #include "motion_settings_service/msg/detail/spd_plan_settings__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motion_settings_service__srv__MotionSettingsService_Response__init(message_memory);
}

void motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_fini_function(void * message_memory)
{
  motion_settings_service__srv__MotionSettingsService_Response__fini(message_memory);
}

size_t motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__size_function__MotionSettingsService_Response__drivers_settings(
  const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__get_const_function__MotionSettingsService_Response__drivers_settings(
  const void * untyped_member, size_t index)
{
  const motion_settings_service__msg__DriverSettings * member =
    (const motion_settings_service__msg__DriverSettings *)(untyped_member);
  return &member[index];
}

void * motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__get_function__MotionSettingsService_Response__drivers_settings(
  void * untyped_member, size_t index)
{
  motion_settings_service__msg__DriverSettings * member =
    (motion_settings_service__msg__DriverSettings *)(untyped_member);
  return &member[index];
}

void motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__fetch_function__MotionSettingsService_Response__drivers_settings(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const motion_settings_service__msg__DriverSettings * item =
    ((const motion_settings_service__msg__DriverSettings *)
    motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__get_const_function__MotionSettingsService_Response__drivers_settings(untyped_member, index));
  motion_settings_service__msg__DriverSettings * value =
    (motion_settings_service__msg__DriverSettings *)(untyped_value);
  *value = *item;
}

void motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__assign_function__MotionSettingsService_Response__drivers_settings(
  void * untyped_member, size_t index, const void * untyped_value)
{
  motion_settings_service__msg__DriverSettings * item =
    ((motion_settings_service__msg__DriverSettings *)
    motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__get_function__MotionSettingsService_Response__drivers_settings(untyped_member, index));
  const motion_settings_service__msg__DriverSettings * value =
    (const motion_settings_service__msg__DriverSettings *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_member_array[9] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "wheel_width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, wheel_width),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "track_width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, track_width),  // bytes offset in struct
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
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, speed_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drivers_settings",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, drivers_settings),  // bytes offset in struct
    NULL,  // default value
    motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__size_function__MotionSettingsService_Response__drivers_settings,  // size() function pointer
    motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__get_const_function__MotionSettingsService_Response__drivers_settings,  // get_const(index) function pointer
    motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__get_function__MotionSettingsService_Response__drivers_settings,  // get(index) function pointer
    motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__fetch_function__MotionSettingsService_Response__drivers_settings,  // fetch(index, &value) function pointer
    motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__assign_function__MotionSettingsService_Response__drivers_settings,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sensor_settings",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, sensor_settings),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "spd_plan_settings",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, spd_plan_settings),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor_enable_flags",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motion_settings_service__srv__MotionSettingsService_Response, motor_enable_flags),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_members = {
  "motion_settings_service__srv",  // message namespace
  "MotionSettingsService_Response",  // message name
  9,  // number of fields
  sizeof(motion_settings_service__srv__MotionSettingsService_Response),
  motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_member_array,  // message members
  motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_type_support_handle = {
  0,
  &motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motion_settings_service
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, srv, MotionSettingsService_Response)() {
  motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, msg, DriverSettings)();
  motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, msg, SensorSettings)();
  motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_member_array[7].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, msg, SpdPlanSettings)();
  if (!motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_type_support_handle.typesupport_identifier) {
    motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motion_settings_service__srv__MotionSettingsService_Response__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "motion_settings_service/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "motion_settings_service/srv/detail/motion_settings_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_service_members = {
  "motion_settings_service__srv",  // service namespace
  "MotionSettingsService",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_Request_message_type_support_handle,
  NULL  // response message
  // motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_Response_message_type_support_handle
};

static rosidl_service_type_support_t motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_service_type_support_handle = {
  0,
  &motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, srv, MotionSettingsService_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, srv, MotionSettingsService_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motion_settings_service
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, srv, MotionSettingsService)() {
  if (!motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_service_type_support_handle.typesupport_identifier) {
    motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, srv, MotionSettingsService_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motion_settings_service, srv, MotionSettingsService_Response)()->data;
  }

  return &motion_settings_service__srv__detail__motion_settings_service__rosidl_typesupport_introspection_c__MotionSettingsService_service_type_support_handle;
}
