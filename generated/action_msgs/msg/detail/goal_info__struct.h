// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from action_msgs:msg/GoalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_info.h"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_INFO__STRUCT_H_
#define ACTION_MSGS__MSG__DETAIL__GOAL_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/GoalInfo in the package action_msgs.
/**
  * Goal ID
 */
typedef struct action_msgs__msg__GoalInfo
{
  unique_identifier_msgs__msg__UUID goal_id;
  /// Time when the goal was accepted
  builtin_interfaces__msg__Time stamp;
} action_msgs__msg__GoalInfo;

// Struct for a sequence of action_msgs__msg__GoalInfo.
typedef struct action_msgs__msg__GoalInfo__Sequence
{
  action_msgs__msg__GoalInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} action_msgs__msg__GoalInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_INFO__STRUCT_H_
