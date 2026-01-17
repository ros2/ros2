// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetAvailableStates C++ type support

#include "lifecycle_msgs/srv/getavailablestates.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_service_type_support_t *
get_service_type_support_handle<lifecycle_msgs::srv::GetAvailableStates>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, lifecycle_msgs, srv, GetAvailableStates)();
}

}  // namespace rosidl_typesupport_cpp
