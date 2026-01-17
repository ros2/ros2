// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/Empty - Service with empty request and response

#ifndef STD_SRVS__SRV__EMPTY_H_
#define STD_SRVS__SRV__EMPTY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "std_srvs/srv/visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

// =============================================================================
// Empty_Request
// =============================================================================

typedef struct std_srvs__srv__Empty_Request
{
  uint8_t structure_needs_at_least_one_member;
} std_srvs__srv__Empty_Request;

typedef struct std_srvs__srv__Empty_Request__Sequence
{
  std_srvs__srv__Empty_Request * data;
  size_t size;
  size_t capacity;
} std_srvs__srv__Empty_Request__Sequence;

STD_SRVS_PUBLIC
bool std_srvs__srv__Empty_Request__init(std_srvs__srv__Empty_Request * msg);

STD_SRVS_PUBLIC
void std_srvs__srv__Empty_Request__fini(std_srvs__srv__Empty_Request * msg);

STD_SRVS_PUBLIC
std_srvs__srv__Empty_Request * std_srvs__srv__Empty_Request__create(void);

STD_SRVS_PUBLIC
void std_srvs__srv__Empty_Request__destroy(std_srvs__srv__Empty_Request * msg);

STD_SRVS_PUBLIC
bool std_srvs__srv__Empty_Request__Sequence__init(
  std_srvs__srv__Empty_Request__Sequence * array, size_t size);

STD_SRVS_PUBLIC
void std_srvs__srv__Empty_Request__Sequence__fini(
  std_srvs__srv__Empty_Request__Sequence * array);

// =============================================================================
// Empty_Response
// =============================================================================

typedef struct std_srvs__srv__Empty_Response
{
  uint8_t structure_needs_at_least_one_member;
} std_srvs__srv__Empty_Response;

typedef struct std_srvs__srv__Empty_Response__Sequence
{
  std_srvs__srv__Empty_Response * data;
  size_t size;
  size_t capacity;
} std_srvs__srv__Empty_Response__Sequence;

STD_SRVS_PUBLIC
bool std_srvs__srv__Empty_Response__init(std_srvs__srv__Empty_Response * msg);

STD_SRVS_PUBLIC
void std_srvs__srv__Empty_Response__fini(std_srvs__srv__Empty_Response * msg);

STD_SRVS_PUBLIC
std_srvs__srv__Empty_Response * std_srvs__srv__Empty_Response__create(void);

STD_SRVS_PUBLIC
void std_srvs__srv__Empty_Response__destroy(std_srvs__srv__Empty_Response * msg);

STD_SRVS_PUBLIC
bool std_srvs__srv__Empty_Response__Sequence__init(
  std_srvs__srv__Empty_Response__Sequence * array, size_t size);

STD_SRVS_PUBLIC
void std_srvs__srv__Empty_Response__Sequence__fini(
  std_srvs__srv__Empty_Response__Sequence * array);

// =============================================================================
// Empty (Service)
// =============================================================================

typedef struct std_srvs__srv__Empty
{
  std_srvs__srv__Empty_Request request;
  std_srvs__srv__Empty_Response response;
} std_srvs__srv__Empty;

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Empty)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Empty)

// Request type support
ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Empty_Request)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Empty_Request)

// Response type support
ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Empty_Response)

ROSIDL_TYPESUPPORT_INTERFACE__DECLARE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Empty_Response)

#ifdef __cplusplus
}
#endif

// C++ namespace declaration
#ifdef __cplusplus
namespace std_srvs
{
namespace srv
{
using Empty = std_srvs__srv__Empty;
using Empty_Request = std_srvs__srv__Empty_Request;
using Empty_Response = std_srvs__srv__Empty_Response;
}  // namespace srv
}  // namespace std_srvs
#endif

#endif  // STD_SRVS__SRV__EMPTY_H_
