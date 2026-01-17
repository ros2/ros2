// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from type_description_interfaces:msg/KeyValue.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/key_value.h"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__STRUCT_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'key'
// Member 'value'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/KeyValue in the package type_description_interfaces.
/**
  * Represents an arbitrary key-value pair for application-specific information.
 */
typedef struct type_description_interfaces__msg__KeyValue
{
  rosidl_runtime_c__String key;
  rosidl_runtime_c__String value;
} type_description_interfaces__msg__KeyValue;

// Struct for a sequence of type_description_interfaces__msg__KeyValue.
typedef struct type_description_interfaces__msg__KeyValue__Sequence
{
  type_description_interfaces__msg__KeyValue * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} type_description_interfaces__msg__KeyValue__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__STRUCT_H_
