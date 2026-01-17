// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from service_msgs:msg/ServiceEventInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "service_msgs/msg/service_event_info.h"


#ifndef SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__STRUCT_H_
#define SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'REQUEST_SENT'.
enum
{
  service_msgs__msg__ServiceEventInfo__REQUEST_SENT = 0
};

/// Constant 'REQUEST_RECEIVED'.
enum
{
  service_msgs__msg__ServiceEventInfo__REQUEST_RECEIVED = 1
};

/// Constant 'RESPONSE_SENT'.
enum
{
  service_msgs__msg__ServiceEventInfo__RESPONSE_SENT = 2
};

/// Constant 'RESPONSE_RECEIVED'.
enum
{
  service_msgs__msg__ServiceEventInfo__RESPONSE_RECEIVED = 3
};

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/ServiceEventInfo in the package service_msgs.
typedef struct service_msgs__msg__ServiceEventInfo
{
  /// The type of event this message represents
  uint8_t event_type;
  /// Timestamp for when the event occurred (sent or received time)
  builtin_interfaces__msg__Time stamp;
  /// Unique identifier for the client that sent the service request
  /// Note, this is only unique for the current session.
  /// The size here has to match the size of rmw_dds_common/msg/Gid,
  /// but unfortunately we cannot use that message directly due to a
  /// circular dependency.
  uint8_t client_gid[16];
  /// Sequence number for the request
  /// Combined with the client ID, this creates a unique ID for the service transaction
  int64_t sequence_number;
} service_msgs__msg__ServiceEventInfo;

// Struct for a sequence of service_msgs__msg__ServiceEventInfo.
typedef struct service_msgs__msg__ServiceEventInfo__Sequence
{
  service_msgs__msg__ServiceEventInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_msgs__msg__ServiceEventInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__STRUCT_H_
