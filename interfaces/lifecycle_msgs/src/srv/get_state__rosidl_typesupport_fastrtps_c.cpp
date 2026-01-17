// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetState FastRTPS C type support

#include "lifecycle_msgs/srv/getstate.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

// Request type support
static const rosidl_message_type_support_t lifecycle_msgs__srv__GetState__Request__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, lifecycle_msgs, srv, GetState_Request)()
{
  return &lifecycle_msgs__srv__GetState__Request__fastrtps_type_support;
}

// Response type support
static const rosidl_message_type_support_t lifecycle_msgs__srv__GetState__Response__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, lifecycle_msgs, srv, GetState_Response)()
{
  return &lifecycle_msgs__srv__GetState__Response__fastrtps_type_support;
}

// Service type support
static const rosidl_service_type_support_t lifecycle_msgs__srv__GetState__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, lifecycle_msgs, srv, GetState)()
{
  return &lifecycle_msgs__srv__GetState__fastrtps_type_support;
}

}  // extern "C"
