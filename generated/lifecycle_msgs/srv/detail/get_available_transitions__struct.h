// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lifecycle_msgs:srv/GetAvailableTransitions.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/srv/get_available_transitions.h"


#ifndef LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__STRUCT_H_
#define LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetAvailableTransitions in the package lifecycle_msgs.
typedef struct lifecycle_msgs__srv__GetAvailableTransitions_Request
{
  uint8_t structure_needs_at_least_one_member;
} lifecycle_msgs__srv__GetAvailableTransitions_Request;

// Struct for a sequence of lifecycle_msgs__srv__GetAvailableTransitions_Request.
typedef struct lifecycle_msgs__srv__GetAvailableTransitions_Request__Sequence
{
  lifecycle_msgs__srv__GetAvailableTransitions_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__srv__GetAvailableTransitions_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'available_transitions'
#include "lifecycle_msgs/msg/detail/transition_description__struct.h"

/// Struct defined in srv/GetAvailableTransitions in the package lifecycle_msgs.
typedef struct lifecycle_msgs__srv__GetAvailableTransitions_Response
{
  lifecycle_msgs__msg__TransitionDescription__Sequence available_transitions;
} lifecycle_msgs__srv__GetAvailableTransitions_Response;

// Struct for a sequence of lifecycle_msgs__srv__GetAvailableTransitions_Response.
typedef struct lifecycle_msgs__srv__GetAvailableTransitions_Response__Sequence
{
  lifecycle_msgs__srv__GetAvailableTransitions_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__srv__GetAvailableTransitions_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  lifecycle_msgs__srv__GetAvailableTransitions_Event__request__MAX_SIZE = 1
};
// response
enum
{
  lifecycle_msgs__srv__GetAvailableTransitions_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/GetAvailableTransitions in the package lifecycle_msgs.
typedef struct lifecycle_msgs__srv__GetAvailableTransitions_Event
{
  service_msgs__msg__ServiceEventInfo info;
  lifecycle_msgs__srv__GetAvailableTransitions_Request__Sequence request;
  lifecycle_msgs__srv__GetAvailableTransitions_Response__Sequence response;
} lifecycle_msgs__srv__GetAvailableTransitions_Event;

// Struct for a sequence of lifecycle_msgs__srv__GetAvailableTransitions_Event.
typedef struct lifecycle_msgs__srv__GetAvailableTransitions_Event__Sequence
{
  lifecycle_msgs__srv__GetAvailableTransitions_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__srv__GetAvailableTransitions_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__STRUCT_H_
