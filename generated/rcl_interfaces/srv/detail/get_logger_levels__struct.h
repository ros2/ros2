// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:srv/GetLoggerLevels.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/get_logger_levels.h"


#ifndef RCL_INTERFACES__SRV__DETAIL__GET_LOGGER_LEVELS__STRUCT_H_
#define RCL_INTERFACES__SRV__DETAIL__GET_LOGGER_LEVELS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'names'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetLoggerLevels in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__GetLoggerLevels_Request
{
  rosidl_runtime_c__String__Sequence names;
} rcl_interfaces__srv__GetLoggerLevels_Request;

// Struct for a sequence of rcl_interfaces__srv__GetLoggerLevels_Request.
typedef struct rcl_interfaces__srv__GetLoggerLevels_Request__Sequence
{
  rcl_interfaces__srv__GetLoggerLevels_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__GetLoggerLevels_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'levels'
#include "rcl_interfaces/msg/detail/logger_level__struct.h"

/// Struct defined in srv/GetLoggerLevels in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__GetLoggerLevels_Response
{
  rcl_interfaces__msg__LoggerLevel__Sequence levels;
} rcl_interfaces__srv__GetLoggerLevels_Response;

// Struct for a sequence of rcl_interfaces__srv__GetLoggerLevels_Response.
typedef struct rcl_interfaces__srv__GetLoggerLevels_Response__Sequence
{
  rcl_interfaces__srv__GetLoggerLevels_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__GetLoggerLevels_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  rcl_interfaces__srv__GetLoggerLevels_Event__request__MAX_SIZE = 1
};
// response
enum
{
  rcl_interfaces__srv__GetLoggerLevels_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/GetLoggerLevels in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__GetLoggerLevels_Event
{
  service_msgs__msg__ServiceEventInfo info;
  rcl_interfaces__srv__GetLoggerLevels_Request__Sequence request;
  rcl_interfaces__srv__GetLoggerLevels_Response__Sequence response;
} rcl_interfaces__srv__GetLoggerLevels_Event;

// Struct for a sequence of rcl_interfaces__srv__GetLoggerLevels_Event.
typedef struct rcl_interfaces__srv__GetLoggerLevels_Event__Sequence
{
  rcl_interfaces__srv__GetLoggerLevels_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__GetLoggerLevels_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__DETAIL__GET_LOGGER_LEVELS__STRUCT_H_
