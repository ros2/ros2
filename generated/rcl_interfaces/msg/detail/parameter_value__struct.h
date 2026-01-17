// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:msg/ParameterValue.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_value.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__STRUCT_H_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'string_value'
// Member 'string_array_value'
#include "rosidl_runtime_c/string.h"
// Member 'byte_array_value'
// Member 'bool_array_value'
// Member 'integer_array_value'
// Member 'double_array_value'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/ParameterValue in the package rcl_interfaces.
/**
  * Used to determine which of the next *_value fields are set.
  * ParameterType.PARAMETER_NOT_SET indicates that the parameter was not set
  * (if gotten) or is uninitialized.
  * Values are enumerated in `ParameterType.msg`.
 */
typedef struct rcl_interfaces__msg__ParameterValue
{
  /// The type of this parameter, which corresponds to the appropriate field below.
  uint8_t type;
  /// "Variant" style storage of the parameter value. Only the value corresponding
  /// the type field will have valid information.
  /// Boolean value, can be either true or false.
  bool bool_value;
  /// Integer value ranging from -9,223,372,036,854,775,808 to
  /// 9,223,372,036,854,775,807.
  int64_t integer_value;
  /// A double precision floating point value following IEEE 754.
  double double_value;
  /// A textual value with no practical length limit.
  rosidl_runtime_c__String string_value;
  /// An array of bytes, used for non-textual information.
  rosidl_runtime_c__octet__Sequence byte_array_value;
  /// An array of boolean values.
  rosidl_runtime_c__boolean__Sequence bool_array_value;
  /// An array of 64-bit integer values.
  rosidl_runtime_c__int64__Sequence integer_array_value;
  /// An array of 64-bit floating point values.
  rosidl_runtime_c__double__Sequence double_array_value;
  /// An array of string values.
  rosidl_runtime_c__String__Sequence string_array_value;
} rcl_interfaces__msg__ParameterValue;

// Struct for a sequence of rcl_interfaces__msg__ParameterValue.
typedef struct rcl_interfaces__msg__ParameterValue__Sequence
{
  rcl_interfaces__msg__ParameterValue * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__msg__ParameterValue__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__STRUCT_H_
