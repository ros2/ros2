// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/StatisticDataPoint FastRTPS C type support

#include "statistics_msgs/msg/statistic_data_point.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

static const rosidl_message_type_support_t statistics_msgs__msg__StatisticDataPoint__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, statistics_msgs, msg, StatisticDataPoint)()
{
  return &statistics_msgs__msg__StatisticDataPoint__fastrtps_type_support;
}

}  // extern "C"
