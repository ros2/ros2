// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Polygon type support

#include "geometry_msgs/msg/polygon.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static const rosidl_typesupport_introspection_c__MessageMembers
geometry_msgs__msg__Polygon__message_members = {
  "geometry_msgs", "Polygon", 0, sizeof(geometry_msgs__msg__Polygon), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)geometry_msgs__msg__Polygon__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)geometry_msgs__msg__Polygon__fini
};

static rosidl_message_type_support_t geometry_msgs__msg__Polygon__type_support = {
  rosidl_typesupport_introspection_c__identifier,
  &geometry_msgs__msg__Polygon__message_members,
  get_message_typesupport_handle_function,
  &geometry_msgs__msg__Polygon__type_support
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, geometry_msgs, msg, Polygon)()
{
  return &geometry_msgs__msg__Polygon__type_support;
}
