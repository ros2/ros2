// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/LoadNode type support

#include "composition_interfaces/srv/load_node.h"
#include "rosidl_typesupport_c/service_type_support.h"
#include "rosidl_runtime_c/service_type_support_struct.h"

// Request type support
static rosidl_message_type_support_t composition_interfaces__srv__LoadNode__Request__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, composition_interfaces, srv, LoadNode_Request)()
{
  return &composition_interfaces__srv__LoadNode__Request__type_support_handle;
}

// Response type support
static rosidl_message_type_support_t composition_interfaces__srv__LoadNode__Response__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, composition_interfaces, srv, LoadNode_Response)()
{
  return &composition_interfaces__srv__LoadNode__Response__type_support_handle;
}

// Service type support
static rosidl_service_type_support_t composition_interfaces__srv__LoadNode__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c, composition_interfaces, srv, LoadNode)()
{
  return &composition_interfaces__srv__LoadNode__type_support_handle;
}
