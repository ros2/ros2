// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from action_msgs:msg/GoalStatusArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_status_array.h"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__FUNCTIONS_H_
#define ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__FUNCTIONS_H_

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
#include "action_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "action_msgs/msg/detail/goal_status_array__struct.h"

/// Initialize msg/GoalStatusArray message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * action_msgs__msg__GoalStatusArray
 * )) before or use
 * action_msgs__msg__GoalStatusArray__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalStatusArray__init(action_msgs__msg__GoalStatusArray * msg);

/// Finalize msg/GoalStatusArray message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void
action_msgs__msg__GoalStatusArray__fini(action_msgs__msg__GoalStatusArray * msg);

/// Create msg/GoalStatusArray message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * action_msgs__msg__GoalStatusArray__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__msg__GoalStatusArray *
action_msgs__msg__GoalStatusArray__create(void);

/// Destroy msg/GoalStatusArray message.
/**
 * It calls
 * action_msgs__msg__GoalStatusArray__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void
action_msgs__msg__GoalStatusArray__destroy(action_msgs__msg__GoalStatusArray * msg);

/// Check for msg/GoalStatusArray message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalStatusArray__are_equal(const action_msgs__msg__GoalStatusArray * lhs, const action_msgs__msg__GoalStatusArray * rhs);

/// Copy a msg/GoalStatusArray message.
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
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalStatusArray__copy(
  const action_msgs__msg__GoalStatusArray * input,
  action_msgs__msg__GoalStatusArray * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
const rosidl_type_hash_t *
action_msgs__msg__GoalStatusArray__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
const rosidl_runtime_c__type_description__TypeDescription *
action_msgs__msg__GoalStatusArray__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
const rosidl_runtime_c__type_description__TypeSource *
action_msgs__msg__GoalStatusArray__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
action_msgs__msg__GoalStatusArray__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/GoalStatusArray messages.
/**
 * It allocates the memory for the number of elements and calls
 * action_msgs__msg__GoalStatusArray__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalStatusArray__Sequence__init(action_msgs__msg__GoalStatusArray__Sequence * array, size_t size);

/// Finalize array of msg/GoalStatusArray messages.
/**
 * It calls
 * action_msgs__msg__GoalStatusArray__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void
action_msgs__msg__GoalStatusArray__Sequence__fini(action_msgs__msg__GoalStatusArray__Sequence * array);

/// Create array of msg/GoalStatusArray messages.
/**
 * It allocates the memory for the array and calls
 * action_msgs__msg__GoalStatusArray__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__msg__GoalStatusArray__Sequence *
action_msgs__msg__GoalStatusArray__Sequence__create(size_t size);

/// Destroy array of msg/GoalStatusArray messages.
/**
 * It calls
 * action_msgs__msg__GoalStatusArray__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void
action_msgs__msg__GoalStatusArray__Sequence__destroy(action_msgs__msg__GoalStatusArray__Sequence * array);

/// Check for msg/GoalStatusArray message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalStatusArray__Sequence__are_equal(const action_msgs__msg__GoalStatusArray__Sequence * lhs, const action_msgs__msg__GoalStatusArray__Sequence * rhs);

/// Copy an array of msg/GoalStatusArray messages.
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
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalStatusArray__Sequence__copy(
  const action_msgs__msg__GoalStatusArray__Sequence * input,
  action_msgs__msg__GoalStatusArray__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__FUNCTIONS_H_
