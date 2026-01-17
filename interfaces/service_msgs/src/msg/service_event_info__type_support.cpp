// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// service_msgs/msg/ServiceEventInfo C++ type support

#include "service_msgs/msg/service_event_info.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<service_msgs::msg::ServiceEventInfo>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, service_msgs, msg, ServiceEventInfo)();
}

}  // namespace rosidl_typesupport_cpp
