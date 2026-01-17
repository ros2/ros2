// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/StatisticDataType C++ type support

#include "statistics_msgs/msg/statistic_data_type.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<statistics_msgs::msg::StatisticDataType>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, statistics_msgs, msg, StatisticDataType)();
}

}  // namespace rosidl_typesupport_cpp
