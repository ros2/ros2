// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from lifecycle_msgs:msg/TransitionEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition_event.h"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__FUNCTIONS_H_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__FUNCTIONS_H_

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
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "lifecycle_msgs/msg/detail/transition_event__struct.h"

/// Initialize msg/TransitionEvent message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * lifecycle_msgs__msg__TransitionEvent
 * )) before or use
 * lifecycle_msgs__msg__TransitionEvent__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool
lifecycle_msgs__msg__TransitionEvent__init(lifecycle_msgs__msg__TransitionEvent * msg);

/// Finalize msg/TransitionEvent message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void
lifecycle_msgs__msg__TransitionEvent__fini(lifecycle_msgs__msg__TransitionEvent * msg);

/// Create msg/TransitionEvent message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * lifecycle_msgs__msg__TransitionEvent__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__TransitionEvent *
lifecycle_msgs__msg__TransitionEvent__create(void);

/// Destroy msg/TransitionEvent message.
/**
 * It calls
 * lifecycle_msgs__msg__TransitionEvent__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void
lifecycle_msgs__msg__TransitionEvent__destroy(lifecycle_msgs__msg__TransitionEvent * msg);

/// Check for msg/TransitionEvent message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool
lifecycle_msgs__msg__TransitionEvent__are_equal(const lifecycle_msgs__msg__TransitionEvent * lhs, const lifecycle_msgs__msg__TransitionEvent * rhs);

/// Copy a msg/TransitionEvent message.
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
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool
lifecycle_msgs__msg__TransitionEvent__copy(
  const lifecycle_msgs__msg__TransitionEvent * input,
  lifecycle_msgs__msg__TransitionEvent * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
const rosidl_type_hash_t *
lifecycle_msgs__msg__TransitionEvent__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
const rosidl_runtime_c__type_description__TypeDescription *
lifecycle_msgs__msg__TransitionEvent__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
const rosidl_runtime_c__type_description__TypeSource *
lifecycle_msgs__msg__TransitionEvent__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
lifecycle_msgs__msg__TransitionEvent__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/TransitionEvent messages.
/**
 * It allocates the memory for the number of elements and calls
 * lifecycle_msgs__msg__TransitionEvent__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool
lifecycle_msgs__msg__TransitionEvent__Sequence__init(lifecycle_msgs__msg__TransitionEvent__Sequence * array, size_t size);

/// Finalize array of msg/TransitionEvent messages.
/**
 * It calls
 * lifecycle_msgs__msg__TransitionEvent__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void
lifecycle_msgs__msg__TransitionEvent__Sequence__fini(lifecycle_msgs__msg__TransitionEvent__Sequence * array);

/// Create array of msg/TransitionEvent messages.
/**
 * It allocates the memory for the array and calls
 * lifecycle_msgs__msg__TransitionEvent__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__TransitionEvent__Sequence *
lifecycle_msgs__msg__TransitionEvent__Sequence__create(size_t size);

/// Destroy array of msg/TransitionEvent messages.
/**
 * It calls
 * lifecycle_msgs__msg__TransitionEvent__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void
lifecycle_msgs__msg__TransitionEvent__Sequence__destroy(lifecycle_msgs__msg__TransitionEvent__Sequence * array);

/// Check for msg/TransitionEvent message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool
lifecycle_msgs__msg__TransitionEvent__Sequence__are_equal(const lifecycle_msgs__msg__TransitionEvent__Sequence * lhs, const lifecycle_msgs__msg__TransitionEvent__Sequence * rhs);

/// Copy an array of msg/TransitionEvent messages.
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
ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool
lifecycle_msgs__msg__TransitionEvent__Sequence__copy(
  const lifecycle_msgs__msg__TransitionEvent__Sequence * input,
  lifecycle_msgs__msg__TransitionEvent__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__FUNCTIONS_H_
