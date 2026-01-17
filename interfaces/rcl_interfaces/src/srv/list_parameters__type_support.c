// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/ListParameters type support

#include "rcl_interfaces/srv/list_parameters.h"
#include "rosidl_typesupport_c/service_type_support.h"
#include "rosidl_runtime_c/service_type_support_struct.h"

// Request type support
static rosidl_message_type_support_t rcl_interfaces__srv__ListParameters__Request__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, rcl_interfaces, srv, ListParameters_Request)()
{
  return &rcl_interfaces__srv__ListParameters__Request__type_support_handle;
}

// Response type support
static rosidl_message_type_support_t rcl_interfaces__srv__ListParameters__Response__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, rcl_interfaces, srv, ListParameters_Response)()
{
  return &rcl_interfaces__srv__ListParameters__Response__type_support_handle;
}

// Service type support
static rosidl_service_type_support_t rcl_interfaces__srv__ListParameters__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c, rcl_interfaces, srv, ListParameters)()
{
  return &rcl_interfaces__srv__ListParameters__type_support_handle;
}
