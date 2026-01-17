// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:srv/GetParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/get_parameters.h"


#ifndef RCL_INTERFACES__SRV__DETAIL__GET_PARAMETERS__STRUCT_H_
#define RCL_INTERFACES__SRV__DETAIL__GET_PARAMETERS__STRUCT_H_

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

/// Struct defined in srv/GetParameters in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__GetParameters_Request
{
  /// A list of parameter names to get.
  rosidl_runtime_c__String__Sequence names;
} rcl_interfaces__srv__GetParameters_Request;

// Struct for a sequence of rcl_interfaces__srv__GetParameters_Request.
typedef struct rcl_interfaces__srv__GetParameters_Request__Sequence
{
  rcl_interfaces__srv__GetParameters_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__GetParameters_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'values'
#include "rcl_interfaces/msg/detail/parameter_value__struct.h"

/// Struct defined in srv/GetParameters in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__GetParameters_Response
{
  rcl_interfaces__msg__ParameterValue__Sequence values;
} rcl_interfaces__srv__GetParameters_Response;

// Struct for a sequence of rcl_interfaces__srv__GetParameters_Response.
typedef struct rcl_interfaces__srv__GetParameters_Response__Sequence
{
  rcl_interfaces__srv__GetParameters_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__GetParameters_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  rcl_interfaces__srv__GetParameters_Event__request__MAX_SIZE = 1
};
// response
enum
{
  rcl_interfaces__srv__GetParameters_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/GetParameters in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__GetParameters_Event
{
  service_msgs__msg__ServiceEventInfo info;
  rcl_interfaces__srv__GetParameters_Request__Sequence request;
  rcl_interfaces__srv__GetParameters_Response__Sequence response;
} rcl_interfaces__srv__GetParameters_Event;

// Struct for a sequence of rcl_interfaces__srv__GetParameters_Event.
typedef struct rcl_interfaces__srv__GetParameters_Event__Sequence
{
  rcl_interfaces__srv__GetParameters_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__GetParameters_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__DETAIL__GET_PARAMETERS__STRUCT_H_
