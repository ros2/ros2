// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/ListNodes type support

#include "composition_interfaces/srv/list_nodes.h"
#include "rosidl_typesupport_c/service_type_support.h"
#include "rosidl_runtime_c/service_type_support_struct.h"

// Request type support
static rosidl_message_type_support_t composition_interfaces__srv__ListNodes__Request__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, composition_interfaces, srv, ListNodes_Request)()
{
  return &composition_interfaces__srv__ListNodes__Request__type_support_handle;
}

// Response type support
static rosidl_message_type_support_t composition_interfaces__srv__ListNodes__Response__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, composition_interfaces, srv, ListNodes_Response)()
{
  return &composition_interfaces__srv__ListNodes__Response__type_support_handle;
}

// Service type support
static rosidl_service_type_support_t composition_interfaces__srv__ListNodes__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c, composition_interfaces, srv, ListNodes)()
{
  return &composition_interfaces__srv__ListNodes__type_support_handle;
}
