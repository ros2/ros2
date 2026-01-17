// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/MultiDOFJointTrajectory type support

#include "trajectory_msgs/msg/multi_dof_joint_trajectory.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t trajectory_msgs__msg__MultiDOFJointTrajectory__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, trajectory_msgs, msg, MultiDOFJointTrajectory)()
{
  return &trajectory_msgs__msg__MultiDOFJointTrajectory__type_support_handle;
}
