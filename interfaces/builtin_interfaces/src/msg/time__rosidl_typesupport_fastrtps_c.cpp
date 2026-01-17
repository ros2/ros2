// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// builtin_interfaces/msg/Time FastRTPS type support

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>

#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/FastBuffer.h"

#include "builtin_interfaces/msg/time.h"
#include "rosidl_runtime_c/visibility_control.h"

extern "C"
{

static bool _Time__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  const auto * ros_message =
    static_cast<const builtin_interfaces__msg__Time *>(untyped_ros_message);

  // Member: sec
  cdr << ros_message->sec;
  // Member: nanosec
  cdr << ros_message->nanosec;

  return true;
}

static bool _Time__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto * ros_message =
    static_cast<builtin_interfaces__msg__Time *>(untyped_ros_message);

  // Member: sec
  cdr >> ros_message->sec;
  // Member: nanosec
  cdr >> ros_message->nanosec;

  return true;
}

static uint32_t _Time__get_serialized_size(
  const void * untyped_ros_message)
{
  (void)untyped_ros_message;
  return static_cast<uint32_t>(
    4 +  // sec: int32
    4);  // nanosec: uint32
}

static size_t _Time__max_serialized_size()
{
  return 8;  // 4 + 4 bytes
}

static message_type_support_callbacks_t _Time__callbacks = {
  "builtin_interfaces::msg",
  "Time",
  _Time__cdr_serialize,
  _Time__cdr_deserialize,
  _Time__get_serialized_size,
  _Time__max_serialized_size
};

static rosidl_message_type_support_t _Time__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &_Time__callbacks,
  get_message_typesupport_handle_function,
  &_Time__type_support
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time)()
{
  return &_Time__type_support;
}

}  // extern "C"
