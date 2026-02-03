// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from motion_status_msgs:msg/DriverStatus.idl
// generated code does not contain a copyright notice

#ifndef MOTION_STATUS_MSGS__MSG__DETAIL__DRIVER_STATUS__FUNCTIONS_H_
#define MOTION_STATUS_MSGS__MSG__DETAIL__DRIVER_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "motion_status_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "motion_status_msgs/msg/detail/driver_status__struct.h"

/// Initialize msg/DriverStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * motion_status_msgs__msg__DriverStatus
 * )) before or use
 * motion_status_msgs__msg__DriverStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
bool
motion_status_msgs__msg__DriverStatus__init(motion_status_msgs__msg__DriverStatus * msg);

/// Finalize msg/DriverStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
void
motion_status_msgs__msg__DriverStatus__fini(motion_status_msgs__msg__DriverStatus * msg);

/// Create msg/DriverStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * motion_status_msgs__msg__DriverStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
motion_status_msgs__msg__DriverStatus *
motion_status_msgs__msg__DriverStatus__create();

/// Destroy msg/DriverStatus message.
/**
 * It calls
 * motion_status_msgs__msg__DriverStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
void
motion_status_msgs__msg__DriverStatus__destroy(motion_status_msgs__msg__DriverStatus * msg);

/// Check for msg/DriverStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
bool
motion_status_msgs__msg__DriverStatus__are_equal(const motion_status_msgs__msg__DriverStatus * lhs, const motion_status_msgs__msg__DriverStatus * rhs);

/// Copy a msg/DriverStatus message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
bool
motion_status_msgs__msg__DriverStatus__copy(
  const motion_status_msgs__msg__DriverStatus * input,
  motion_status_msgs__msg__DriverStatus * output);

/// Initialize array of msg/DriverStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * motion_status_msgs__msg__DriverStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
bool
motion_status_msgs__msg__DriverStatus__Sequence__init(motion_status_msgs__msg__DriverStatus__Sequence * array, size_t size);

/// Finalize array of msg/DriverStatus messages.
/**
 * It calls
 * motion_status_msgs__msg__DriverStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
void
motion_status_msgs__msg__DriverStatus__Sequence__fini(motion_status_msgs__msg__DriverStatus__Sequence * array);

/// Create array of msg/DriverStatus messages.
/**
 * It allocates the memory for the array and calls
 * motion_status_msgs__msg__DriverStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
motion_status_msgs__msg__DriverStatus__Sequence *
motion_status_msgs__msg__DriverStatus__Sequence__create(size_t size);

/// Destroy array of msg/DriverStatus messages.
/**
 * It calls
 * motion_status_msgs__msg__DriverStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
void
motion_status_msgs__msg__DriverStatus__Sequence__destroy(motion_status_msgs__msg__DriverStatus__Sequence * array);

/// Check for msg/DriverStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
bool
motion_status_msgs__msg__DriverStatus__Sequence__are_equal(const motion_status_msgs__msg__DriverStatus__Sequence * lhs, const motion_status_msgs__msg__DriverStatus__Sequence * rhs);

/// Copy an array of msg/DriverStatus messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_status_msgs
bool
motion_status_msgs__msg__DriverStatus__Sequence__copy(
  const motion_status_msgs__msg__DriverStatus__Sequence * input,
  motion_status_msgs__msg__DriverStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MOTION_STATUS_MSGS__MSG__DETAIL__DRIVER_STATUS__FUNCTIONS_H_
