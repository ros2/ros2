// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/Empty FastRTPS C type support

#include "std_srvs/srv/empty.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

// Request FastRTPS type support
static const rosidl_message_type_support_t std_srvs__srv__Empty_Request__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Empty_Request)()
{
  return &std_srvs__srv__Empty_Request__fastrtps_type_support;
}

// Response FastRTPS type support
static const rosidl_message_type_support_t std_srvs__srv__Empty_Response__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Empty_Response)()
{
  return &std_srvs__srv__Empty_Response__fastrtps_type_support;
}

// Service FastRTPS type support
static const rosidl_service_type_support_t std_srvs__srv__Empty__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, std_srvs, srv, Empty)()
{
  return &std_srvs__srv__Empty__fastrtps_type_support;
}

}  // extern "C"
