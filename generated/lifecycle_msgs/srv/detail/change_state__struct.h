// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lifecycle_msgs:srv/ChangeState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/srv/change_state.h"


#ifndef LIFECYCLE_MSGS__SRV__DETAIL__CHANGE_STATE__STRUCT_H_
#define LIFECYCLE_MSGS__SRV__DETAIL__CHANGE_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'transition'
#include "lifecycle_msgs/msg/detail/transition__struct.h"

/// Struct defined in srv/ChangeState in the package lifecycle_msgs.
typedef struct lifecycle_msgs__srv__ChangeState_Request
{
  lifecycle_msgs__msg__Transition transition;
} lifecycle_msgs__srv__ChangeState_Request;

// Struct for a sequence of lifecycle_msgs__srv__ChangeState_Request.
typedef struct lifecycle_msgs__srv__ChangeState_Request__Sequence
{
  lifecycle_msgs__srv__ChangeState_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__srv__ChangeState_Request__Sequence;

// Constants defined in the message

/// Struct defined in srv/ChangeState in the package lifecycle_msgs.
typedef struct lifecycle_msgs__srv__ChangeState_Response
{
  /// Indicates whether the service was able to initiate the state transition
  bool success;
} lifecycle_msgs__srv__ChangeState_Response;

// Struct for a sequence of lifecycle_msgs__srv__ChangeState_Response.
typedef struct lifecycle_msgs__srv__ChangeState_Response__Sequence
{
  lifecycle_msgs__srv__ChangeState_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__srv__ChangeState_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  lifecycle_msgs__srv__ChangeState_Event__request__MAX_SIZE = 1
};
// response
enum
{
  lifecycle_msgs__srv__ChangeState_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/ChangeState in the package lifecycle_msgs.
typedef struct lifecycle_msgs__srv__ChangeState_Event
{
  service_msgs__msg__ServiceEventInfo info;
  lifecycle_msgs__srv__ChangeState_Request__Sequence request;
  lifecycle_msgs__srv__ChangeState_Response__Sequence response;
} lifecycle_msgs__srv__ChangeState_Event;

// Struct for a sequence of lifecycle_msgs__srv__ChangeState_Event.
typedef struct lifecycle_msgs__srv__ChangeState_Event__Sequence
{
  lifecycle_msgs__srv__ChangeState_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__srv__ChangeState_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__SRV__DETAIL__CHANGE_STATE__STRUCT_H_
