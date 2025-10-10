// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from motion_params_service:srv/MotionParamsService.idl
// generated code does not contain a copyright notice

#ifndef MOTION_PARAMS_SERVICE__SRV__DETAIL__MOTION_PARAMS_SERVICE__FUNCTIONS_H_
#define MOTION_PARAMS_SERVICE__SRV__DETAIL__MOTION_PARAMS_SERVICE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "motion_params_service/msg/rosidl_generator_c__visibility_control.h"

#include "motion_params_service/srv/detail/motion_params_service__struct.h"

/// Initialize srv/MotionParamsService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * motion_params_service__srv__MotionParamsService_Request
 * )) before or use
 * motion_params_service__srv__MotionParamsService_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Request__init(motion_params_service__srv__MotionParamsService_Request * msg);

/// Finalize srv/MotionParamsService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
void
motion_params_service__srv__MotionParamsService_Request__fini(motion_params_service__srv__MotionParamsService_Request * msg);

/// Create srv/MotionParamsService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * motion_params_service__srv__MotionParamsService_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
motion_params_service__srv__MotionParamsService_Request *
motion_params_service__srv__MotionParamsService_Request__create();

/// Destroy srv/MotionParamsService message.
/**
 * It calls
 * motion_params_service__srv__MotionParamsService_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
void
motion_params_service__srv__MotionParamsService_Request__destroy(motion_params_service__srv__MotionParamsService_Request * msg);

/// Check for srv/MotionParamsService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Request__are_equal(const motion_params_service__srv__MotionParamsService_Request * lhs, const motion_params_service__srv__MotionParamsService_Request * rhs);

/// Copy a srv/MotionParamsService message.
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
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Request__copy(
  const motion_params_service__srv__MotionParamsService_Request * input,
  motion_params_service__srv__MotionParamsService_Request * output);

/// Initialize array of srv/MotionParamsService messages.
/**
 * It allocates the memory for the number of elements and calls
 * motion_params_service__srv__MotionParamsService_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Request__Sequence__init(motion_params_service__srv__MotionParamsService_Request__Sequence * array, size_t size);

/// Finalize array of srv/MotionParamsService messages.
/**
 * It calls
 * motion_params_service__srv__MotionParamsService_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
void
motion_params_service__srv__MotionParamsService_Request__Sequence__fini(motion_params_service__srv__MotionParamsService_Request__Sequence * array);

/// Create array of srv/MotionParamsService messages.
/**
 * It allocates the memory for the array and calls
 * motion_params_service__srv__MotionParamsService_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
motion_params_service__srv__MotionParamsService_Request__Sequence *
motion_params_service__srv__MotionParamsService_Request__Sequence__create(size_t size);

/// Destroy array of srv/MotionParamsService messages.
/**
 * It calls
 * motion_params_service__srv__MotionParamsService_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
void
motion_params_service__srv__MotionParamsService_Request__Sequence__destroy(motion_params_service__srv__MotionParamsService_Request__Sequence * array);

/// Check for srv/MotionParamsService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Request__Sequence__are_equal(const motion_params_service__srv__MotionParamsService_Request__Sequence * lhs, const motion_params_service__srv__MotionParamsService_Request__Sequence * rhs);

/// Copy an array of srv/MotionParamsService messages.
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
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Request__Sequence__copy(
  const motion_params_service__srv__MotionParamsService_Request__Sequence * input,
  motion_params_service__srv__MotionParamsService_Request__Sequence * output);

/// Initialize srv/MotionParamsService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * motion_params_service__srv__MotionParamsService_Response
 * )) before or use
 * motion_params_service__srv__MotionParamsService_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Response__init(motion_params_service__srv__MotionParamsService_Response * msg);

/// Finalize srv/MotionParamsService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
void
motion_params_service__srv__MotionParamsService_Response__fini(motion_params_service__srv__MotionParamsService_Response * msg);

/// Create srv/MotionParamsService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * motion_params_service__srv__MotionParamsService_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
motion_params_service__srv__MotionParamsService_Response *
motion_params_service__srv__MotionParamsService_Response__create();

/// Destroy srv/MotionParamsService message.
/**
 * It calls
 * motion_params_service__srv__MotionParamsService_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
void
motion_params_service__srv__MotionParamsService_Response__destroy(motion_params_service__srv__MotionParamsService_Response * msg);

/// Check for srv/MotionParamsService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Response__are_equal(const motion_params_service__srv__MotionParamsService_Response * lhs, const motion_params_service__srv__MotionParamsService_Response * rhs);

/// Copy a srv/MotionParamsService message.
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
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Response__copy(
  const motion_params_service__srv__MotionParamsService_Response * input,
  motion_params_service__srv__MotionParamsService_Response * output);

/// Initialize array of srv/MotionParamsService messages.
/**
 * It allocates the memory for the number of elements and calls
 * motion_params_service__srv__MotionParamsService_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Response__Sequence__init(motion_params_service__srv__MotionParamsService_Response__Sequence * array, size_t size);

/// Finalize array of srv/MotionParamsService messages.
/**
 * It calls
 * motion_params_service__srv__MotionParamsService_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
void
motion_params_service__srv__MotionParamsService_Response__Sequence__fini(motion_params_service__srv__MotionParamsService_Response__Sequence * array);

/// Create array of srv/MotionParamsService messages.
/**
 * It allocates the memory for the array and calls
 * motion_params_service__srv__MotionParamsService_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
motion_params_service__srv__MotionParamsService_Response__Sequence *
motion_params_service__srv__MotionParamsService_Response__Sequence__create(size_t size);

/// Destroy array of srv/MotionParamsService messages.
/**
 * It calls
 * motion_params_service__srv__MotionParamsService_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
void
motion_params_service__srv__MotionParamsService_Response__Sequence__destroy(motion_params_service__srv__MotionParamsService_Response__Sequence * array);

/// Check for srv/MotionParamsService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Response__Sequence__are_equal(const motion_params_service__srv__MotionParamsService_Response__Sequence * lhs, const motion_params_service__srv__MotionParamsService_Response__Sequence * rhs);

/// Copy an array of srv/MotionParamsService messages.
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
ROSIDL_GENERATOR_C_PUBLIC_motion_params_service
bool
motion_params_service__srv__MotionParamsService_Response__Sequence__copy(
  const motion_params_service__srv__MotionParamsService_Response__Sequence * input,
  motion_params_service__srv__MotionParamsService_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MOTION_PARAMS_SERVICE__SRV__DETAIL__MOTION_PARAMS_SERVICE__FUNCTIONS_H_
