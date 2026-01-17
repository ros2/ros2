// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/SetBool - Service to set a boolean value

#ifndef STD_SRVS__SRV__SET_BOOL_H_
#define STD_SRVS__SRV__SET_BOOL_H_

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
// SetBool_Request
// =============================================================================

/// Request: bool data - The boolean value to set
typedef struct std_srvs__srv__SetBool_Request
{
  bool data;
} std_srvs__srv__SetBool_Request;

typedef struct std_srvs__srv__SetBool_Request__Sequence
{
  std_srvs__srv__SetBool_Request * data;
  size_t size;
  size_t capacity;
} std_srvs__srv__SetBool_Request__Sequence;

STD_SRVS_PUBLIC
bool std_srvs__srv__SetBool_Request__init(std_srvs__srv__SetBool_Request * msg);

STD_SRVS_PUBLIC
void std_srvs__srv__SetBool_Request__fini(std_srvs__srv__SetBool_Request * msg);

STD_SRVS_PUBLIC
std_srvs__srv__SetBool_Request * std_srvs__srv__SetBool_Request__create(void);

STD_SRVS_PUBLIC
void std_srvs__srv__SetBool_Request__destroy(std_srvs__srv__SetBool_Request * msg);

STD_SRVS_PUBLIC
bool std_srvs__srv__SetBool_Request__Sequence__init(
  std_srvs__srv__SetBool_Request__Sequence * array, size_t size);

STD_SRVS_PUBLIC
void std_srvs__srv__SetBool_Request__Sequence__fini(
  std_srvs__srv__SetBool_Request__Sequence * array);

// =============================================================================
// SetBool_Response
// =============================================================================

/// Response: bool success - Whether the operation succeeded
///           string message - Informational message
typedef struct std_srvs__srv__SetBool_Response
{
  bool success;
  rosidl_runtime_c__String message;
} std_srvs__srv__SetBool_Response;

typedef struct std_srvs__srv__SetBool_Response__Sequence
{
  std_srvs__srv__SetBool_Response * data;
  size_t size;
  size_t capacity;
} std_srvs__srv__SetBool_Response__Sequence;

STD_SRVS_PUBLIC
bool std_srvs__srv__SetBool_Response__init(std_srvs__srv__SetBool_Response * msg);

STD_SRVS_PUBLIC
void std_srvs__srv__SetBool_Response__fini(std_srvs__srv__SetBool_Response * msg);

STD_SRVS_PUBLIC
std_srvs__srv__SetBool_Response * std_srvs__srv__SetBool_Response__create(void);

STD_SRVS_PUBLIC
void std_srvs__srv__SetBool_Response__destroy(std_srvs__srv__SetBool_Response * msg);

STD_SRVS_PUBLIC
bool std_srvs__srv__SetBool_Response__Sequence__init(
  std_srvs__srv__SetBool_Response__Sequence * array, size_t size);

STD_SRVS_PUBLIC
void std_srvs__srv__SetBool_Response__Sequence__fini(
  std_srvs__srv__SetBool_Response__Sequence * array);

// =============================================================================
// SetBool (Service)
// =============================================================================

typedef struct std_srvs__srv__SetBool
{
  std_srvs__srv__SetBool_Request request;
  std_srvs__srv__SetBool_Response response;
} std_srvs__srv__SetBool;

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, SetBool)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, SetBool)

// Request type support
ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, SetBool_Request)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, SetBool_Request)

// Response type support
ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, SetBool_Response)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, SetBool_Response)

#ifdef __cplusplus
}
#endif

// C++ namespace declaration
#ifdef __cplusplus
namespace std_srvs
{
namespace srv
{
using SetBool = std_srvs__srv__SetBool;
using SetBool_Request = std_srvs__srv__SetBool_Request;
using SetBool_Response = std_srvs__srv__SetBool_Response;
}  // namespace srv
}  // namespace std_srvs
#endif

#endif  // STD_SRVS__SRV__SET_BOOL_H_
