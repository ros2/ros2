// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/action/LookupTransform_Goal type support

#include "tf2_msgs/action/lookup_transform__goal.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

// Type support handle
static rosidl_message_type_support_t tf2_msgs__action__LookupTransform_Goal__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, tf2_msgs, action, LookupTransform_Goal)()
{
  return &tf2_msgs__action__LookupTransform_Goal__type_support_handle;
}
