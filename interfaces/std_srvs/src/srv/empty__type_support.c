// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/Empty type support

#include "std_srvs/srv/empty.h"
#include "rosidl_typesupport_c/service_type_support.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

// Request type support
static rosidl_message_type_support_t std_srvs__srv__Empty_Request__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Empty_Request)()
{
  return &std_srvs__srv__Empty_Request__type_support_handle;
}

// Response type support
static rosidl_message_type_support_t std_srvs__srv__Empty_Response__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Empty_Response)()
{
  return &std_srvs__srv__Empty_Response__type_support_handle;
}

// Service type support
static rosidl_service_type_support_t std_srvs__srv__Empty__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c, std_srvs, srv, Empty)()
{
  return &std_srvs__srv__Empty__type_support_handle;
}
