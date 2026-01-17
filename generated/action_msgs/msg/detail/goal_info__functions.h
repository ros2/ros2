// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from action_msgs:msg/GoalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_info.h"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_INFO__FUNCTIONS_H_
#define ACTION_MSGS__MSG__DETAIL__GOAL_INFO__FUNCTIONS_H_

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

#include "action_msgs/msg/detail/goal_info__struct.h"

/// Initialize msg/GoalInfo message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * action_msgs__msg__GoalInfo
 * )) before or use
 * action_msgs__msg__GoalInfo__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalInfo__init(action_msgs__msg__GoalInfo * msg);

/// Finalize msg/GoalInfo message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void
action_msgs__msg__GoalInfo__fini(action_msgs__msg__GoalInfo * msg);

/// Create msg/GoalInfo message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * action_msgs__msg__GoalInfo__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__msg__GoalInfo *
action_msgs__msg__GoalInfo__create(void);

/// Destroy msg/GoalInfo message.
/**
 * It calls
 * action_msgs__msg__GoalInfo__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void
action_msgs__msg__GoalInfo__destroy(action_msgs__msg__GoalInfo * msg);

/// Check for msg/GoalInfo message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalInfo__are_equal(const action_msgs__msg__GoalInfo * lhs, const action_msgs__msg__GoalInfo * rhs);

/// Copy a msg/GoalInfo message.
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
action_msgs__msg__GoalInfo__copy(
  const action_msgs__msg__GoalInfo * input,
  action_msgs__msg__GoalInfo * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
const rosidl_type_hash_t *
action_msgs__msg__GoalInfo__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
const rosidl_runtime_c__type_description__TypeDescription *
action_msgs__msg__GoalInfo__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
const rosidl_runtime_c__type_description__TypeSource *
action_msgs__msg__GoalInfo__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
action_msgs__msg__GoalInfo__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/GoalInfo messages.
/**
 * It allocates the memory for the number of elements and calls
 * action_msgs__msg__GoalInfo__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalInfo__Sequence__init(action_msgs__msg__GoalInfo__Sequence * array, size_t size);

/// Finalize array of msg/GoalInfo messages.
/**
 * It calls
 * action_msgs__msg__GoalInfo__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void
action_msgs__msg__GoalInfo__Sequence__fini(action_msgs__msg__GoalInfo__Sequence * array);

/// Create array of msg/GoalInfo messages.
/**
 * It allocates the memory for the array and calls
 * action_msgs__msg__GoalInfo__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__msg__GoalInfo__Sequence *
action_msgs__msg__GoalInfo__Sequence__create(size_t size);

/// Destroy array of msg/GoalInfo messages.
/**
 * It calls
 * action_msgs__msg__GoalInfo__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void
action_msgs__msg__GoalInfo__Sequence__destroy(action_msgs__msg__GoalInfo__Sequence * array);

/// Check for msg/GoalInfo message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool
action_msgs__msg__GoalInfo__Sequence__are_equal(const action_msgs__msg__GoalInfo__Sequence * lhs, const action_msgs__msg__GoalInfo__Sequence * rhs);

/// Copy an array of msg/GoalInfo messages.
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
action_msgs__msg__GoalInfo__Sequence__copy(
  const action_msgs__msg__GoalInfo__Sequence * input,
  action_msgs__msg__GoalInfo__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_INFO__FUNCTIONS_H_
