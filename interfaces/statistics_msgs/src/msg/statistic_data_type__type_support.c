// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/StatisticDataType type support

#include "statistics_msgs/msg/statistic_data_type.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t statistics_msgs__msg__StatisticDataType__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, statistics_msgs, msg, StatisticDataType)()
{
  return &statistics_msgs__msg__StatisticDataType__type_support_handle;
}
