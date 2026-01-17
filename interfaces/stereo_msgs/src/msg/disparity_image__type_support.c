// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// stereo_msgs/msg/DisparityImage type support

#include "stereo_msgs/msg/disparity_image.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t stereo_msgs__msg__DisparityImage__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, stereo_msgs, msg, DisparityImage)()
{
  return &stereo_msgs__msg__DisparityImage__type_support_handle;
}
