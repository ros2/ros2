// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/ChangeState type support

#include "lifecycle_msgs/srv/changestate.h"
#include "rosidl_typesupport_c/service_type_support.h"
#include "rosidl_runtime_c/service_type_support_struct.h"

// Request type support
static rosidl_message_type_support_t lifecycle_msgs__srv__ChangeState__Request__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, lifecycle_msgs, srv, ChangeState_Request)()
{
  return &lifecycle_msgs__srv__ChangeState__Request__type_support_handle;
}

// Response type support
static rosidl_message_type_support_t lifecycle_msgs__srv__ChangeState__Response__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, lifecycle_msgs, srv, ChangeState_Response)()
{
  return &lifecycle_msgs__srv__ChangeState__Response__type_support_handle;
}

// Service type support
static rosidl_service_type_support_t lifecycle_msgs__srv__ChangeState__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c, lifecycle_msgs, srv, ChangeState)()
{
  return &lifecycle_msgs__srv__ChangeState__type_support_handle;
}
