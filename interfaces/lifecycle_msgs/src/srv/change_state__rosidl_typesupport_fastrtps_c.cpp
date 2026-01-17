// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/ChangeState FastRTPS C type support

#include "lifecycle_msgs/srv/changestate.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

// Request type support
static const rosidl_message_type_support_t lifecycle_msgs__srv__ChangeState__Request__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, lifecycle_msgs, srv, ChangeState_Request)()
{
  return &lifecycle_msgs__srv__ChangeState__Request__fastrtps_type_support;
}

// Response type support
static const rosidl_message_type_support_t lifecycle_msgs__srv__ChangeState__Response__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, lifecycle_msgs, srv, ChangeState_Response)()
{
  return &lifecycle_msgs__srv__ChangeState__Response__fastrtps_type_support;
}

// Service type support
static const rosidl_service_type_support_t lifecycle_msgs__srv__ChangeState__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, lifecycle_msgs, srv, ChangeState)()
{
  return &lifecycle_msgs__srv__ChangeState__fastrtps_type_support;
}

}  // extern "C"
