// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/TransitionEvent type support

#include "lifecycle_msgs/msg/transitionevent.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t lifecycle_msgs__msg__TransitionEvent__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, lifecycle_msgs, msg, TransitionEvent)()
{
  return &lifecycle_msgs__msg__TransitionEvent__type_support_handle;
}
