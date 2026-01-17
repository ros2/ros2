// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:msg/ParameterEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_event.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__STRUCT_H_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'node'
#include "rosidl_runtime_c/string.h"
// Member 'new_parameters'
// Member 'changed_parameters'
// Member 'deleted_parameters'
#include "rcl_interfaces/msg/detail/parameter__struct.h"

/// Struct defined in msg/ParameterEvent in the package rcl_interfaces.
/**
  * This message contains a parameter event.
  * Because the parameter event was an atomic update, a specific parameter name
  * can only be in one of the three sets.
 */
typedef struct rcl_interfaces__msg__ParameterEvent
{
  /// The time stamp when this parameter event occurred.
  builtin_interfaces__msg__Time stamp;
  /// Fully qualified ROS path to node.
  rosidl_runtime_c__String node;
  /// New parameters that have been set for this node.
  rcl_interfaces__msg__Parameter__Sequence new_parameters;
  /// Parameters that have been changed during this event.
  rcl_interfaces__msg__Parameter__Sequence changed_parameters;
  /// Parameters that have been deleted during this event.
  rcl_interfaces__msg__Parameter__Sequence deleted_parameters;
} rcl_interfaces__msg__ParameterEvent;

// Struct for a sequence of rcl_interfaces__msg__ParameterEvent.
typedef struct rcl_interfaces__msg__ParameterEvent__Sequence
{
  rcl_interfaces__msg__ParameterEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__msg__ParameterEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__STRUCT_H_
