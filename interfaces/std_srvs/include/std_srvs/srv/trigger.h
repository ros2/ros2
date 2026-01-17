// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/Trigger - Service to trigger an action

#ifndef STD_SRVS__SRV__TRIGGER_H_
#define STD_SRVS__SRV__TRIGGER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_typesupport_interface/macros.h"
#include "std_srvs/srv/visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

// =============================================================================
// Trigger_Request
// =============================================================================

/// Request: empty - Trigger has no request parameters
typedef struct std_srvs__srv__Trigger_Request
{
  uint8_t structure_needs_at_least_one_member;
} std_srvs__srv__Trigger_Request;

typedef struct std_srvs__srv__Trigger_Request__Sequence
{
  std_srvs__srv__Trigger_Request * data;
  size_t size;
  size_t capacity;
} std_srvs__srv__Trigger_Request__Sequence;

STD_SRVS_PUBLIC
bool std_srvs__srv__Trigger_Request__init(std_srvs__srv__Trigger_Request * msg);

STD_SRVS_PUBLIC
void std_srvs__srv__Trigger_Request__fini(std_srvs__srv__Trigger_Request * msg);

STD_SRVS_PUBLIC
std_srvs__srv__Trigger_Request * std_srvs__srv__Trigger_Request__create(void);

STD_SRVS_PUBLIC
void std_srvs__srv__Trigger_Request__destroy(std_srvs__srv__Trigger_Request * msg);

STD_SRVS_PUBLIC
bool std_srvs__srv__Trigger_Request__Sequence__init(
  std_srvs__srv__Trigger_Request__Sequence * array, size_t size);

STD_SRVS_PUBLIC
void std_srvs__srv__Trigger_Request__Sequence__fini(
  std_srvs__srv__Trigger_Request__Sequence * array);

// =============================================================================
// Trigger_Response
// =============================================================================

/// Response: bool success - Whether the trigger succeeded
///           string message - Informational message
typedef struct std_srvs__srv__Trigger_Response
{
  bool success;
  rosidl_runtime_c__String message;
} std_srvs__srv__Trigger_Response;

typedef struct std_srvs__srv__Trigger_Response__Sequence
{
  std_srvs__srv__Trigger_Response * data;
  size_t size;
  size_t capacity;
} std_srvs__srv__Trigger_Response__Sequence;

STD_SRVS_PUBLIC
bool std_srvs__srv__Trigger_Response__init(std_srvs__srv__Trigger_Response * msg);

STD_SRVS_PUBLIC
void std_srvs__srv__Trigger_Response__fini(std_srvs__srv__Trigger_Response * msg);

STD_SRVS_PUBLIC
std_srvs__srv__Trigger_Response * std_srvs__srv__Trigger_Response__create(void);

STD_SRVS_PUBLIC
void std_srvs__srv__Trigger_Response__destroy(std_srvs__srv__Trigger_Response * msg);

STD_SRVS_PUBLIC
bool std_srvs__srv__Trigger_Response__Sequence__init(
  std_srvs__srv__Trigger_Response__Sequence * array, size_t size);

STD_SRVS_PUBLIC
void std_srvs__srv__Trigger_Response__Sequence__fini(
  std_srvs__srv__Trigger_Response__Sequence * array);

// =============================================================================
// Trigger (Service)
// =============================================================================

typedef struct std_srvs__srv__Trigger
{
  std_srvs__srv__Trigger_Request request;
  std_srvs__srv__Trigger_Response response;
} std_srvs__srv__Trigger;

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Trigger)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Trigger)

// Request type support
ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Trigger_Request)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Trigger_Request)

// Response type support
ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Trigger_Response)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Trigger_Response)

#ifdef __cplusplus
}
#endif

// C++ namespace declaration
#ifdef __cplusplus
namespace std_srvs
{
namespace srv
{
using Trigger = std_srvs__srv__Trigger;
using Trigger_Request = std_srvs__srv__Trigger_Request;
using Trigger_Response = std_srvs__srv__Trigger_Response;
}  // namespace srv
}  // namespace std_srvs
#endif

#endif  // STD_SRVS__SRV__TRIGGER_H_
