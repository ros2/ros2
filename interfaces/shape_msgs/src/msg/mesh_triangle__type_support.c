// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/MeshTriangle type support

#include "shape_msgs/msg/mesh_triangle.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t shape_msgs__msg__MeshTriangle__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, shape_msgs, msg, MeshTriangle)()
{
  return &shape_msgs__msg__MeshTriangle__type_support_handle;
}
