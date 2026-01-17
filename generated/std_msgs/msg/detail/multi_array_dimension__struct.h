// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from std_msgs:msg/MultiArrayDimension.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/multi_array_dimension.h"


#ifndef STD_MSGS__MSG__DETAIL__MULTI_ARRAY_DIMENSION__STRUCT_H_
#define STD_MSGS__MSG__DETAIL__MULTI_ARRAY_DIMENSION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'label'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MultiArrayDimension in the package std_msgs.
/**
  * This was originally provided as an example message.
  * It is deprecated as of Foxy
  * It is recommended to create your own semantically meaningful message.
  * However if you would like to continue using this please use the equivalent in example_msgs.
 */
typedef struct std_msgs__msg__MultiArrayDimension
{
  /// label of given dimension
  rosidl_runtime_c__String label;
  /// size of given dimension (in type units)
  uint32_t size;
  /// stride of given dimension
  uint32_t stride;
} std_msgs__msg__MultiArrayDimension;

// Struct for a sequence of std_msgs__msg__MultiArrayDimension.
typedef struct std_msgs__msg__MultiArrayDimension__Sequence
{
  std_msgs__msg__MultiArrayDimension * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} std_msgs__msg__MultiArrayDimension__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__DETAIL__MULTI_ARRAY_DIMENSION__STRUCT_H_
