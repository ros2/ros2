// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/PointCloud2 type support

#include "sensor_msgs/msg/point_cloud2.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static const rosidl_typesupport_introspection_c__MessageMembers
sensor_msgs__msg__PointCloud2__message_members = {
  "sensor_msgs", "PointCloud2", 0, sizeof(sensor_msgs__msg__PointCloud2), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)sensor_msgs__msg__PointCloud2__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)sensor_msgs__msg__PointCloud2__fini
};

static rosidl_message_type_support_t sensor_msgs__msg__PointCloud2__type_support = {
  rosidl_typesupport_introspection_c__identifier,
  &sensor_msgs__msg__PointCloud2__message_members,
  get_message_typesupport_handle_function,
  &sensor_msgs__msg__PointCloud2__type_support
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, sensor_msgs, msg, PointCloud2)()
{
  return &sensor_msgs__msg__PointCloud2__type_support;
}
