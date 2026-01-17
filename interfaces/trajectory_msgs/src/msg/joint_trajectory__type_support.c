// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/JointTrajectory type support

#include "trajectory_msgs/msg/joint_trajectory.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t trajectory_msgs__msg__JointTrajectory__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, trajectory_msgs, msg, JointTrajectory)()
{
  return &trajectory_msgs__msg__JointTrajectory__type_support_handle;
}
