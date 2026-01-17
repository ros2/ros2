// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from std_msgs:msg/Float64MultiArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/float64_multi_array.h"


#ifndef STD_MSGS__MSG__DETAIL__FLOAT64_MULTI_ARRAY__STRUCT_H_
#define STD_MSGS__MSG__DETAIL__FLOAT64_MULTI_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'layout'
#include "std_msgs/msg/detail/multi_array_layout__struct.h"
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/Float64MultiArray in the package std_msgs.
/**
  * This was originally provided as an example message.
  * It is deprecated as of Foxy
  * It is recommended to create your own semantically meaningful message.
  * However if you would like to continue using this please use the equivalent in example_msgs.
 */
typedef struct std_msgs__msg__Float64MultiArray
{
  /// Please look at the MultiArrayLayout message definition for
  /// documentation on all multiarrays.
  /// specification of data layout
  std_msgs__msg__MultiArrayLayout layout;
  /// array of data
  rosidl_runtime_c__double__Sequence data;
} std_msgs__msg__Float64MultiArray;

// Struct for a sequence of std_msgs__msg__Float64MultiArray.
typedef struct std_msgs__msg__Float64MultiArray__Sequence
{
  std_msgs__msg__Float64MultiArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} std_msgs__msg__Float64MultiArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__DETAIL__FLOAT64_MULTI_ARRAY__STRUCT_H_
