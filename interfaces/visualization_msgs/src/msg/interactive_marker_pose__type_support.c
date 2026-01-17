// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerPose type support

#include "visualization_msgs/msg/interactive_marker_pose.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t visualization_msgs__msg__InteractiveMarkerPose__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, visualization_msgs, msg, InteractiveMarkerPose)()
{
  return &visualization_msgs__msg__InteractiveMarkerPose__type_support_handle;
}
