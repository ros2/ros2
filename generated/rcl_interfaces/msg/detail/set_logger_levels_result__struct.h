// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:msg/SetLoggerLevelsResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/set_logger_levels_result.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__STRUCT_H_
#define RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'reason'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SetLoggerLevelsResult in the package rcl_interfaces.
/**
  * True when succeed, false when failed.
 */
typedef struct rcl_interfaces__msg__SetLoggerLevelsResult
{
  bool successful;
  /// Reason why the setting was either successful or a failure.
  rosidl_runtime_c__String reason;
} rcl_interfaces__msg__SetLoggerLevelsResult;

// Struct for a sequence of rcl_interfaces__msg__SetLoggerLevelsResult.
typedef struct rcl_interfaces__msg__SetLoggerLevelsResult__Sequence
{
  rcl_interfaces__msg__SetLoggerLevelsResult * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__msg__SetLoggerLevelsResult__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__STRUCT_H_
