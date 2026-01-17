// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// service_msgs/msg/ServiceEventInfo - Service event metadata (ROS2 Humble+)

#ifndef SERVICE_MSGS__MSG__SERVICE_EVENT_INFO_H_
#define SERVICE_MSGS__MSG__SERVICE_EVENT_INFO_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "builtin_interfaces/msg/time.h"
#include "service_msgs/msg/visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

// =============================================================================
// ServiceEventInfo Constants
// =============================================================================

/// Event type: Request sent by client
#define SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__REQUEST_SENT ((uint8_t)0)

/// Event type: Request received by server
#define SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__REQUEST_RECEIVED ((uint8_t)1)

/// Event type: Response sent by server
#define SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__RESPONSE_SENT ((uint8_t)2)

/// Event type: Response received by client
#define SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__RESPONSE_RECEIVED ((uint8_t)3)

/// Size of GID (Global Identifier) array
#define SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__GID_SIZE ((size_t)16)

// =============================================================================
// ServiceEventInfo
// =============================================================================

/// ServiceEventInfo provides metadata about service call events
/// Used for service introspection and debugging
typedef struct service_msgs__msg__ServiceEventInfo
{
  /// Type of event (REQUEST_SENT, REQUEST_RECEIVED, RESPONSE_SENT, RESPONSE_RECEIVED)
  uint8_t event_type;

  /// Timestamp when the event occurred
  builtin_interfaces__msg__Time stamp;

  /// Global identifier of the client (16 bytes)
  uint8_t client_gid[16];

  /// Sequence number assigned by the client
  int64_t sequence_number;
} service_msgs__msg__ServiceEventInfo;

typedef struct service_msgs__msg__ServiceEventInfo__Sequence
{
  service_msgs__msg__ServiceEventInfo * data;
  size_t size;
  size_t capacity;
} service_msgs__msg__ServiceEventInfo__Sequence;

// =============================================================================
// ServiceEventInfo Functions
// =============================================================================

SERVICE_MSGS_PUBLIC
bool service_msgs__msg__ServiceEventInfo__init(service_msgs__msg__ServiceEventInfo * msg);

SERVICE_MSGS_PUBLIC
void service_msgs__msg__ServiceEventInfo__fini(service_msgs__msg__ServiceEventInfo * msg);

SERVICE_MSGS_PUBLIC
service_msgs__msg__ServiceEventInfo * service_msgs__msg__ServiceEventInfo__create(void);

SERVICE_MSGS_PUBLIC
void service_msgs__msg__ServiceEventInfo__destroy(service_msgs__msg__ServiceEventInfo * msg);

SERVICE_MSGS_PUBLIC
bool service_msgs__msg__ServiceEventInfo__Sequence__init(
  service_msgs__msg__ServiceEventInfo__Sequence * array, size_t size);

SERVICE_MSGS_PUBLIC
void service_msgs__msg__ServiceEventInfo__Sequence__fini(
  service_msgs__msg__ServiceEventInfo__Sequence * array);

// =============================================================================
// Type Support
// =============================================================================

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, service_msgs, msg, ServiceEventInfo)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, service_msgs, msg, ServiceEventInfo)

#ifdef __cplusplus
}
#endif

// C++ namespace declaration
#ifdef __cplusplus
namespace service_msgs
{
namespace msg
{

using ServiceEventInfo = service_msgs__msg__ServiceEventInfo;

// Event type constants
constexpr uint8_t ServiceEventInfo__REQUEST_SENT = SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__REQUEST_SENT;
constexpr uint8_t ServiceEventInfo__REQUEST_RECEIVED = SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__REQUEST_RECEIVED;
constexpr uint8_t ServiceEventInfo__RESPONSE_SENT = SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__RESPONSE_SENT;
constexpr uint8_t ServiceEventInfo__RESPONSE_RECEIVED = SERVICE_MSGS__MSG__SERVICE_EVENT_INFO__RESPONSE_RECEIVED;

}  // namespace msg
}  // namespace service_msgs
#endif

#endif  // SERVICE_MSGS__MSG__SERVICE_EVENT_INFO_H_
