// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lifecycle_msgs:msg/TransitionDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition_description.h"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__STRUCT_H_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'transition'
#include "lifecycle_msgs/msg/detail/transition__struct.h"
// Member 'start_state'
// Member 'goal_state'
#include "lifecycle_msgs/msg/detail/state__struct.h"

/// Struct defined in msg/TransitionDescription in the package lifecycle_msgs.
/**
  * The transition id and label of this description.
 */
typedef struct lifecycle_msgs__msg__TransitionDescription
{
  lifecycle_msgs__msg__Transition transition;
  /// The current state from which this transition transitions.
  lifecycle_msgs__msg__State start_state;
  /// The desired target state of this transition.
  lifecycle_msgs__msg__State goal_state;
} lifecycle_msgs__msg__TransitionDescription;

// Struct for a sequence of lifecycle_msgs__msg__TransitionDescription.
typedef struct lifecycle_msgs__msg__TransitionDescription__Sequence
{
  lifecycle_msgs__msg__TransitionDescription * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__msg__TransitionDescription__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__STRUCT_H_
