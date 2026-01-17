// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from type_description_interfaces:msg/Field.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/field.h"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__FUNCTIONS_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__FUNCTIONS_H_

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
#include "type_description_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "type_description_interfaces/msg/detail/field__struct.h"

/// Initialize msg/Field message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * type_description_interfaces__msg__Field
 * )) before or use
 * type_description_interfaces__msg__Field__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool
type_description_interfaces__msg__Field__init(type_description_interfaces__msg__Field * msg);

/// Finalize msg/Field message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void
type_description_interfaces__msg__Field__fini(type_description_interfaces__msg__Field * msg);

/// Create msg/Field message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * type_description_interfaces__msg__Field__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
type_description_interfaces__msg__Field *
type_description_interfaces__msg__Field__create(void);

/// Destroy msg/Field message.
/**
 * It calls
 * type_description_interfaces__msg__Field__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void
type_description_interfaces__msg__Field__destroy(type_description_interfaces__msg__Field * msg);

/// Check for msg/Field message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool
type_description_interfaces__msg__Field__are_equal(const type_description_interfaces__msg__Field * lhs, const type_description_interfaces__msg__Field * rhs);

/// Copy a msg/Field message.
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
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool
type_description_interfaces__msg__Field__copy(
  const type_description_interfaces__msg__Field * input,
  type_description_interfaces__msg__Field * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
const rosidl_type_hash_t *
type_description_interfaces__msg__Field__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
type_description_interfaces__msg__Field__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
const rosidl_runtime_c__type_description__TypeSource *
type_description_interfaces__msg__Field__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
type_description_interfaces__msg__Field__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/Field messages.
/**
 * It allocates the memory for the number of elements and calls
 * type_description_interfaces__msg__Field__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool
type_description_interfaces__msg__Field__Sequence__init(type_description_interfaces__msg__Field__Sequence * array, size_t size);

/// Finalize array of msg/Field messages.
/**
 * It calls
 * type_description_interfaces__msg__Field__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void
type_description_interfaces__msg__Field__Sequence__fini(type_description_interfaces__msg__Field__Sequence * array);

/// Create array of msg/Field messages.
/**
 * It allocates the memory for the array and calls
 * type_description_interfaces__msg__Field__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
type_description_interfaces__msg__Field__Sequence *
type_description_interfaces__msg__Field__Sequence__create(size_t size);

/// Destroy array of msg/Field messages.
/**
 * It calls
 * type_description_interfaces__msg__Field__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void
type_description_interfaces__msg__Field__Sequence__destroy(type_description_interfaces__msg__Field__Sequence * array);

/// Check for msg/Field message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool
type_description_interfaces__msg__Field__Sequence__are_equal(const type_description_interfaces__msg__Field__Sequence * lhs, const type_description_interfaces__msg__Field__Sequence * rhs);

/// Copy an array of msg/Field messages.
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
ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool
type_description_interfaces__msg__Field__Sequence__copy(
  const type_description_interfaces__msg__Field__Sequence * input,
  type_description_interfaces__msg__Field__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__FUNCTIONS_H_
