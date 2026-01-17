// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerUpdate type support

#include "visualization_msgs/msg/interactive_marker_update.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t visualization_msgs__msg__InteractiveMarkerUpdate__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, visualization_msgs, msg, InteractiveMarkerUpdate)()
{
  return &visualization_msgs__msg__InteractiveMarkerUpdate__type_support_handle;
}
