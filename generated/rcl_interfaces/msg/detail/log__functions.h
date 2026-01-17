// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from rcl_interfaces:msg/Log.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/log.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__LOG__FUNCTIONS_H_
#define RCL_INTERFACES__MSG__DETAIL__LOG__FUNCTIONS_H_

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

#include "rcl_interfaces/msg/detail/log__struct.h"

/// Initialize msg/Log message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * rcl_interfaces__msg__Log
 * )) before or use
 * rcl_interfaces__msg__Log__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__Log__init(rcl_interfaces__msg__Log * msg);

/// Finalize msg/Log message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__Log__fini(rcl_interfaces__msg__Log * msg);

/// Create msg/Log message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * rcl_interfaces__msg__Log__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__Log *
rcl_interfaces__msg__Log__create(void);

/// Destroy msg/Log message.
/**
 * It calls
 * rcl_interfaces__msg__Log__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__Log__destroy(rcl_interfaces__msg__Log * msg);

/// Check for msg/Log message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__Log__are_equal(const rcl_interfaces__msg__Log * lhs, const rcl_interfaces__msg__Log * rhs);

/// Copy a msg/Log message.
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
rcl_interfaces__msg__Log__copy(
  const rcl_interfaces__msg__Log * input,
  rcl_interfaces__msg__Log * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_type_hash_t *
rcl_interfaces__msg__Log__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
rcl_interfaces__msg__Log__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_runtime_c__type_description__TypeSource *
rcl_interfaces__msg__Log__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
rcl_interfaces__msg__Log__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/Log messages.
/**
 * It allocates the memory for the number of elements and calls
 * rcl_interfaces__msg__Log__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__Log__Sequence__init(rcl_interfaces__msg__Log__Sequence * array, size_t size);

/// Finalize array of msg/Log messages.
/**
 * It calls
 * rcl_interfaces__msg__Log__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__Log__Sequence__fini(rcl_interfaces__msg__Log__Sequence * array);

/// Create array of msg/Log messages.
/**
 * It allocates the memory for the array and calls
 * rcl_interfaces__msg__Log__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__Log__Sequence *
rcl_interfaces__msg__Log__Sequence__create(size_t size);

/// Destroy array of msg/Log messages.
/**
 * It calls
 * rcl_interfaces__msg__Log__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__Log__Sequence__destroy(rcl_interfaces__msg__Log__Sequence * array);

/// Check for msg/Log message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool
rcl_interfaces__msg__Log__Sequence__are_equal(const rcl_interfaces__msg__Log__Sequence * lhs, const rcl_interfaces__msg__Log__Sequence * rhs);

/// Copy an array of msg/Log messages.
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
rcl_interfaces__msg__Log__Sequence__copy(
  const rcl_interfaces__msg__Log__Sequence * input,
  rcl_interfaces__msg__Log__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__LOG__FUNCTIONS_H_
