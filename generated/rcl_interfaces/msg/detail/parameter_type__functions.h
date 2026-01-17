// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from rcl_interfaces:msg/ParameterType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_type.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__FUNCTIONS_H_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rcl_interfaces/msg/detail/parameter_type__struct.h"

/// Initialize msg/ParameterType message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * rcl_interfaces__msg__ParameterType
 * )) before or use
 * rcl_interfaces__msg__ParameterType__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__ParameterType__init(rcl_interfaces__msg__ParameterType * msg);

/// Finalize msg/ParameterType message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__ParameterType__fini(rcl_interfaces__msg__ParameterType * msg);

/// Create msg/ParameterType message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * rcl_interfaces__msg__ParameterType__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__ParameterType *
rcl_interfaces__msg__ParameterType__create(void);

/// Destroy msg/ParameterType message.
/**
 * It calls
 * rcl_interfaces__msg__ParameterType__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__ParameterType__destroy(rcl_interfaces__msg__ParameterType * msg);

/// Check for msg/ParameterType message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__ParameterType__are_equal(const rcl_interfaces__msg__ParameterType * lhs, const rcl_interfaces__msg__ParameterType * rhs);

/// Copy a msg/ParameterType message.
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
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__ParameterType__copy(
  const rcl_interfaces__msg__ParameterType * input,
  rcl_interfaces__msg__ParameterType * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_type_hash_t *
rcl_interfaces__msg__ParameterType__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
rcl_interfaces__msg__ParameterType__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_runtime_c__type_description__TypeSource *
rcl_interfaces__msg__ParameterType__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
rcl_interfaces__msg__ParameterType__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/ParameterType messages.
/**
 * It allocates the memory for the number of elements and calls
 * rcl_interfaces__msg__ParameterType__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__ParameterType__Sequence__init(rcl_interfaces__msg__ParameterType__Sequence * array, size_t size);

/// Finalize array of msg/ParameterType messages.
/**
 * It calls
 * rcl_interfaces__msg__ParameterType__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__ParameterType__Sequence__fini(rcl_interfaces__msg__ParameterType__Sequence * array);

/// Create array of msg/ParameterType messages.
/**
 * It allocates the memory for the array and calls
 * rcl_interfaces__msg__ParameterType__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__ParameterType__Sequence *
rcl_interfaces__msg__ParameterType__Sequence__create(size_t size);

/// Destroy array of msg/ParameterType messages.
/**
 * It calls
 * rcl_interfaces__msg__ParameterType__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__ParameterType__Sequence__destroy(rcl_interfaces__msg__ParameterType__Sequence * array);

/// Check for msg/ParameterType message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__ParameterType__Sequence__are_equal(const rcl_interfaces__msg__ParameterType__Sequence * lhs, const rcl_interfaces__msg__ParameterType__Sequence * rhs);

/// Copy an array of msg/ParameterType messages.
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
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__ParameterType__Sequence__copy(
  const rcl_interfaces__msg__ParameterType__Sequence * input,
  rcl_interfaces__msg__ParameterType__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__FUNCTIONS_H_
