// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:srv/SetParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/set_parameters.h"


#ifndef RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS__STRUCT_H_
#define RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'parameters'
#include "rcl_interfaces/msg/detail/parameter__struct.h"

/// Struct defined in srv/SetParameters in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__SetParameters_Request
{
  rcl_interfaces__msg__Parameter__Sequence parameters;
} rcl_interfaces__srv__SetParameters_Request;

// Struct for a sequence of rcl_interfaces__srv__SetParameters_Request.
typedef struct rcl_interfaces__srv__SetParameters_Request__Sequence
{
  rcl_interfaces__srv__SetParameters_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__SetParameters_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'results'
#include "rcl_interfaces/msg/detail/set_parameters_result__struct.h"

/// Struct defined in srv/SetParameters in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__SetParameters_Response
{
  rcl_interfaces__msg__SetParametersResult__Sequence results;
} rcl_interfaces__srv__SetParameters_Response;

// Struct for a sequence of rcl_interfaces__srv__SetParameters_Response.
typedef struct rcl_interfaces__srv__SetParameters_Response__Sequence
{
  rcl_interfaces__srv__SetParameters_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__SetParameters_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  rcl_interfaces__srv__SetParameters_Event__request__MAX_SIZE = 1
};
// response
enum
{
  rcl_interfaces__srv__SetParameters_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SetParameters in the package rcl_interfaces.
typedef struct rcl_interfaces__srv__SetParameters_Event
{
  service_msgs__msg__ServiceEventInfo info;
  rcl_interfaces__srv__SetParameters_Request__Sequence request;
  rcl_interfaces__srv__SetParameters_Response__Sequence response;
} rcl_interfaces__srv__SetParameters_Event;

// Struct for a sequence of rcl_interfaces__srv__SetParameters_Event.
typedef struct rcl_interfaces__srv__SetParameters_Event__Sequence
{
  rcl_interfaces__srv__SetParameters_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__srv__SetParameters_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS__STRUCT_H_
