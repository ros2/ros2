// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lifecycle_msgs:msg/TransitionEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition_event.h"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__STRUCT_H_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__STRUCT_H_

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

/// Struct defined in msg/TransitionEvent in the package lifecycle_msgs.
/**
  * The time point at which this event occurred.
 */
typedef struct lifecycle_msgs__msg__TransitionEvent
{
  uint64_t timestamp;
  /// The id and label of this transition event.
  lifecycle_msgs__msg__Transition transition;
  /// The starting state from which this event transitioned.
  lifecycle_msgs__msg__State start_state;
  /// The end state of this transition event.
  lifecycle_msgs__msg__State goal_state;
} lifecycle_msgs__msg__TransitionEvent;

// Struct for a sequence of lifecycle_msgs__msg__TransitionEvent.
typedef struct lifecycle_msgs__msg__TransitionEvent__Sequence
{
  lifecycle_msgs__msg__TransitionEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__msg__TransitionEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__STRUCT_H_
