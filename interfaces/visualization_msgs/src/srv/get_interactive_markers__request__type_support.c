// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/srv/GetInteractiveMarkers_Request type support

#include "visualization_msgs/srv/get_interactive_markers__request.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t visualization_msgs__srv__GetInteractiveMarkers_Request__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, visualization_msgs, srv, GetInteractiveMarkers_Request)()
{
  return &visualization_msgs__srv__GetInteractiveMarkers_Request__type_support_handle;
}
