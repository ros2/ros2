// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/GetParameters type support

#include "rcl_interfaces/srv/get_parameters.h"
#include "rosidl_typesupport_c/service_type_support.h"
#include "rosidl_runtime_c/service_type_support_struct.h"

// Request type support
static rosidl_message_type_support_t rcl_interfaces__srv__GetParameters__Request__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, rcl_interfaces, srv, GetParameters_Request)()
{
  return &rcl_interfaces__srv__GetParameters__Request__type_support_handle;
}

// Response type support
static rosidl_message_type_support_t rcl_interfaces__srv__GetParameters__Response__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, rcl_interfaces, srv, GetParameters_Response)()
{
  return &rcl_interfaces__srv__GetParameters__Response__type_support_handle;
}

// Service type support
static rosidl_service_type_support_t rcl_interfaces__srv__GetParameters__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c, rcl_interfaces, srv, GetParameters)()
{
  return &rcl_interfaces__srv__GetParameters__type_support_handle;
}
