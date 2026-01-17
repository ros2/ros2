// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/SetLoggerLevels FastRTPS C type support

#include "rcl_interfaces/srv/set_logger_levels.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

// Request type support
static const rosidl_message_type_support_t rcl_interfaces__srv__SetLoggerLevels__Request__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, rcl_interfaces, srv, SetLoggerLevels_Request)()
{
  return &rcl_interfaces__srv__SetLoggerLevels__Request__fastrtps_type_support;
}

// Response type support
static const rosidl_message_type_support_t rcl_interfaces__srv__SetLoggerLevels__Response__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, rcl_interfaces, srv, SetLoggerLevels_Response)()
{
  return &rcl_interfaces__srv__SetLoggerLevels__Response__fastrtps_type_support;
}

// Service type support
static const rosidl_service_type_support_t rcl_interfaces__srv__SetLoggerLevels__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, rcl_interfaces, srv, SetLoggerLevels)()
{
  return &rcl_interfaces__srv__SetLoggerLevels__fastrtps_type_support;
}

}  // extern "C"
