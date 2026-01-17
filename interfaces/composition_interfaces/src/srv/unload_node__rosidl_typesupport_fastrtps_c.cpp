// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/UnloadNode FastRTPS C type support

#include "composition_interfaces/srv/unload_node.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

// Request type support
static const rosidl_message_type_support_t composition_interfaces__srv__UnloadNode__Request__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, composition_interfaces, srv, UnloadNode_Request)()
{
  return &composition_interfaces__srv__UnloadNode__Request__fastrtps_type_support;
}

// Response type support
static const rosidl_message_type_support_t composition_interfaces__srv__UnloadNode__Response__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, composition_interfaces, srv, UnloadNode_Response)()
{
  return &composition_interfaces__srv__UnloadNode__Response__fastrtps_type_support;
}

// Service type support
static const rosidl_service_type_support_t composition_interfaces__srv__UnloadNode__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, composition_interfaces, srv, UnloadNode)()
{
  return &composition_interfaces__srv__UnloadNode__fastrtps_type_support;
}

}  // extern "C"
