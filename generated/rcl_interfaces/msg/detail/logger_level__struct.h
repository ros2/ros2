// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:msg/LoggerLevel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/logger_level.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__STRUCT_H_
#define RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'LOG_LEVEL_UNKNOWN'.
enum
{
  rcl_interfaces__msg__LoggerLevel__LOG_LEVEL_UNKNOWN = 0
};

/// Constant 'LOG_LEVEL_DEBUG'.
enum
{
  rcl_interfaces__msg__LoggerLevel__LOG_LEVEL_DEBUG = 10
};

/// Constant 'LOG_LEVEL_INFO'.
enum
{
  rcl_interfaces__msg__LoggerLevel__LOG_LEVEL_INFO = 20
};

/// Constant 'LOG_LEVEL_WARN'.
enum
{
  rcl_interfaces__msg__LoggerLevel__LOG_LEVEL_WARN = 30
};

/// Constant 'LOG_LEVEL_ERROR'.
enum
{
  rcl_interfaces__msg__LoggerLevel__LOG_LEVEL_ERROR = 40
};

/// Constant 'LOG_LEVEL_FATAL'.
enum
{
  rcl_interfaces__msg__LoggerLevel__LOG_LEVEL_FATAL = 50
};

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/LoggerLevel in the package rcl_interfaces.
/**
  * All available logger levels; these correspond to the enum in rcutils/logger.h
 */
typedef struct rcl_interfaces__msg__LoggerLevel
{
  /// The logger name.
  rosidl_runtime_c__String name;
  /// The logger level
  uint32_t level;
} rcl_interfaces__msg__LoggerLevel;

// Struct for a sequence of rcl_interfaces__msg__LoggerLevel.
typedef struct rcl_interfaces__msg__LoggerLevel__Sequence
{
  rcl_interfaces__msg__LoggerLevel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__msg__LoggerLevel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__STRUCT_H_
