// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:msg/ParameterEventDescriptors.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_event_descriptors.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__STRUCT_H_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'new_parameters'
// Member 'changed_parameters'
// Member 'deleted_parameters'
#include "rcl_interfaces/msg/detail/parameter_descriptor__struct.h"

/// Struct defined in msg/ParameterEventDescriptors in the package rcl_interfaces.
/**
  * This message contains descriptors of a parameter event.
  * It was an atomic update.
  * A specific parameter name can only be in one of the three sets.
 */
typedef struct rcl_interfaces__msg__ParameterEventDescriptors
{
  rcl_interfaces__msg__ParameterDescriptor__Sequence new_parameters;
  rcl_interfaces__msg__ParameterDescriptor__Sequence changed_parameters;
  rcl_interfaces__msg__ParameterDescriptor__Sequence deleted_parameters;
} rcl_interfaces__msg__ParameterEventDescriptors;

// Struct for a sequence of rcl_interfaces__msg__ParameterEventDescriptors.
typedef struct rcl_interfaces__msg__ParameterEventDescriptors__Sequence
{
  rcl_interfaces__msg__ParameterEventDescriptors * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__msg__ParameterEventDescriptors__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__STRUCT_H_
