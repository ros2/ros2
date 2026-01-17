// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/srv/GetMap_Response type support

#include "nav_msgs/srv/get_map__response.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

// Type support handle
static rosidl_message_type_support_t nav_msgs__srv__GetMap_Response__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, nav_msgs, srv, GetMap_Response)()
{
  return &nav_msgs__srv__GetMap_Response__type_support_handle;
}
