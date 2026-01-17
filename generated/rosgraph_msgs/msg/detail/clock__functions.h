// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from rosgraph_msgs:msg/Clock.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosgraph_msgs/msg/clock.h"


#ifndef ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__FUNCTIONS_H_
#define ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__FUNCTIONS_H_

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
#include "rosgraph_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "rosgraph_msgs/msg/detail/clock__struct.h"

/// Initialize msg/Clock message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * rosgraph_msgs__msg__Clock
 * )) before or use
 * rosgraph_msgs__msg__Clock__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
bool
rosgraph_msgs__msg__Clock__init(rosgraph_msgs__msg__Clock * msg);

/// Finalize msg/Clock message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
void
rosgraph_msgs__msg__Clock__fini(rosgraph_msgs__msg__Clock * msg);

/// Create msg/Clock message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * rosgraph_msgs__msg__Clock__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
rosgraph_msgs__msg__Clock *
rosgraph_msgs__msg__Clock__create(void);

/// Destroy msg/Clock message.
/**
 * It calls
 * rosgraph_msgs__msg__Clock__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
void
rosgraph_msgs__msg__Clock__destroy(rosgraph_msgs__msg__Clock * msg);

/// Check for msg/Clock message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
bool
rosgraph_msgs__msg__Clock__are_equal(const rosgraph_msgs__msg__Clock * lhs, const rosgraph_msgs__msg__Clock * rhs);

/// Copy a msg/Clock message.
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
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
bool
rosgraph_msgs__msg__Clock__copy(
  const rosgraph_msgs__msg__Clock * input,
  rosgraph_msgs__msg__Clock * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
const rosidl_type_hash_t *
rosgraph_msgs__msg__Clock__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
const rosidl_runtime_c__type_description__TypeDescription *
rosgraph_msgs__msg__Clock__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
const rosidl_runtime_c__type_description__TypeSource *
rosgraph_msgs__msg__Clock__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
rosgraph_msgs__msg__Clock__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/Clock messages.
/**
 * It allocates the memory for the number of elements and calls
 * rosgraph_msgs__msg__Clock__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
bool
rosgraph_msgs__msg__Clock__Sequence__init(rosgraph_msgs__msg__Clock__Sequence * array, size_t size);

/// Finalize array of msg/Clock messages.
/**
 * It calls
 * rosgraph_msgs__msg__Clock__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
void
rosgraph_msgs__msg__Clock__Sequence__fini(rosgraph_msgs__msg__Clock__Sequence * array);

/// Create array of msg/Clock messages.
/**
 * It allocates the memory for the array and calls
 * rosgraph_msgs__msg__Clock__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
rosgraph_msgs__msg__Clock__Sequence *
rosgraph_msgs__msg__Clock__Sequence__create(size_t size);

/// Destroy array of msg/Clock messages.
/**
 * It calls
 * rosgraph_msgs__msg__Clock__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
void
rosgraph_msgs__msg__Clock__Sequence__destroy(rosgraph_msgs__msg__Clock__Sequence * array);

/// Check for msg/Clock message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
bool
rosgraph_msgs__msg__Clock__Sequence__are_equal(const rosgraph_msgs__msg__Clock__Sequence * lhs, const rosgraph_msgs__msg__Clock__Sequence * rhs);

/// Copy an array of msg/Clock messages.
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
ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
bool
rosgraph_msgs__msg__Clock__Sequence__copy(
  const rosgraph_msgs__msg__Clock__Sequence * input,
  rosgraph_msgs__msg__Clock__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__FUNCTIONS_H_
