// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:srv/SetLoggerLevels.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/set_logger_levels.h"


#ifndef RCL_INTERFACES__SRV__DETAIL__SET_LOGGER_LEVELS__STRUCT_H_
#define RCL_INTERFACES__SRV__DETAIL__SET_LOGGER_LEVELS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'levels'
#include "rcl_interfaces/msg/detail/logger_level__struct.h"

/// Struct defined in srv/SetLoggerLevels in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__SetLoggerLevels_Request
{
  rcl_interfaces__msg__LoggerLevel__Sequence levels;
} rcl_interfaces__srv__SetLoggerLevels_Request;

// Struct for a sequence of rcl_interfaces__srv__SetLoggerLevels_Request.
typedef struct rcl_interfaces__srv__SetLoggerLevels_Request__Sequence
{
  rcl_interfaces__srv__SetLoggerLevels_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__SetLoggerLevels_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'results'
#include "rcl_interfaces/msg/detail/set_logger_levels_result__struct.h"

/// Struct defined in srv/SetLoggerLevels in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__SetLoggerLevels_Response
{
  rcl_interfaces__msg__SetLoggerLevelsResult__Sequence results;
} rcl_interfaces__srv__SetLoggerLevels_Response;

// Struct for a sequence of rcl_interfaces__srv__SetLoggerLevels_Response.
typedef struct rcl_interfaces__srv__SetLoggerLevels_Response__Sequence
{
  rcl_interfaces__srv__SetLoggerLevels_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__SetLoggerLevels_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  rcl_interfaces__srv__SetLoggerLevels_Event__request__MAX_SIZE = 1
};
// response
enum
{
  rcl_interfaces__srv__SetLoggerLevels_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SetLoggerLevels in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__SetLoggerLevels_Event
{
  service_msgs__msg__ServiceEventInfo info;
  rcl_interfaces__srv__SetLoggerLevels_Request__Sequence request;
  rcl_interfaces__srv__SetLoggerLevels_Response__Sequence response;
} rcl_interfaces__srv__SetLoggerLevels_Event;

// Struct for a sequence of rcl_interfaces__srv__SetLoggerLevels_Event.
typedef struct rcl_interfaces__srv__SetLoggerLevels_Event__Sequence
{
  rcl_interfaces__srv__SetLoggerLevels_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__SetLoggerLevels_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__DETAIL__SET_LOGGER_LEVELS__STRUCT_H_
