// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from unique_identifier_msgs:msg/UUID.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unique_identifier_msgs/msg/uuid.h"


#ifndef UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__FUNCTIONS_H_
#define UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__FUNCTIONS_H_

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
#include "unique_identifier_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Initialize msg/UUID message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * unique_identifier_msgs__msg__UUID
 * )) before or use
 * unique_identifier_msgs__msg__UUID__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
bool
unique_identifier_msgs__msg__UUID__init(unique_identifier_msgs__msg__UUID * msg);

/// Finalize msg/UUID message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
void
unique_identifier_msgs__msg__UUID__fini(unique_identifier_msgs__msg__UUID * msg);

/// Create msg/UUID message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * unique_identifier_msgs__msg__UUID__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
unique_identifier_msgs__msg__UUID *
unique_identifier_msgs__msg__UUID__create(void);

/// Destroy msg/UUID message.
/**
 * It calls
 * unique_identifier_msgs__msg__UUID__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
void
unique_identifier_msgs__msg__UUID__destroy(unique_identifier_msgs__msg__UUID * msg);

/// Check for msg/UUID message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
bool
unique_identifier_msgs__msg__UUID__are_equal(const unique_identifier_msgs__msg__UUID * lhs, const unique_identifier_msgs__msg__UUID * rhs);

/// Copy a msg/UUID message.
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
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
bool
unique_identifier_msgs__msg__UUID__copy(
  const unique_identifier_msgs__msg__UUID * input,
  unique_identifier_msgs__msg__UUID * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
const rosidl_type_hash_t *
unique_identifier_msgs__msg__UUID__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
const rosidl_runtime_c__type_description__TypeDescription *
unique_identifier_msgs__msg__UUID__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
const rosidl_runtime_c__type_description__TypeSource *
unique_identifier_msgs__msg__UUID__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
unique_identifier_msgs__msg__UUID__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/UUID messages.
/**
 * It allocates the memory for the number of elements and calls
 * unique_identifier_msgs__msg__UUID__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
bool
unique_identifier_msgs__msg__UUID__Sequence__init(unique_identifier_msgs__msg__UUID__Sequence * array, size_t size);

/// Finalize array of msg/UUID messages.
/**
 * It calls
 * unique_identifier_msgs__msg__UUID__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
void
unique_identifier_msgs__msg__UUID__Sequence__fini(unique_identifier_msgs__msg__UUID__Sequence * array);

/// Create array of msg/UUID messages.
/**
 * It allocates the memory for the array and calls
 * unique_identifier_msgs__msg__UUID__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
unique_identifier_msgs__msg__UUID__Sequence *
unique_identifier_msgs__msg__UUID__Sequence__create(size_t size);

/// Destroy array of msg/UUID messages.
/**
 * It calls
 * unique_identifier_msgs__msg__UUID__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
void
unique_identifier_msgs__msg__UUID__Sequence__destroy(unique_identifier_msgs__msg__UUID__Sequence * array);

/// Check for msg/UUID message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
bool
unique_identifier_msgs__msg__UUID__Sequence__are_equal(const unique_identifier_msgs__msg__UUID__Sequence * lhs, const unique_identifier_msgs__msg__UUID__Sequence * rhs);

/// Copy an array of msg/UUID messages.
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
ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
bool
unique_identifier_msgs__msg__UUID__Sequence__copy(
  const unique_identifier_msgs__msg__UUID__Sequence * input,
  unique_identifier_msgs__msg__UUID__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__FUNCTIONS_H_
