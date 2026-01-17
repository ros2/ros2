// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from action_msgs:msg/GoalStatusArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_status_array.h"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__STRUCT_H_
#define ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'status_list'
#include "action_msgs/msg/detail/goal_status__struct.h"

/// Struct defined in msg/GoalStatusArray in the package action_msgs.
/**
  * An array of goal statuses.
 */
typedef struct action_msgs__msg__GoalStatusArray
{
  action_msgs__msg__GoalStatus__Sequence status_list;
} action_msgs__msg__GoalStatusArray;

// Struct for a sequence of action_msgs__msg__GoalStatusArray.
typedef struct action_msgs__msg__GoalStatusArray__Sequence
{
  action_msgs__msg__GoalStatusArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} action_msgs__msg__GoalStatusArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__STRUCT_H_
