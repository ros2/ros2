// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from statistics_msgs:msg/MetricsMessage.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "statistics_msgs/msg/detail/metrics_message__functions.h"
#include "statistics_msgs/msg/detail/metrics_message__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace statistics_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void MetricsMessage_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) statistics_msgs::msg::MetricsMessage(_init);
}

void MetricsMessage_fini_function(void * message_memory)
{
  auto typed_message = static_cast<statistics_msgs::msg::MetricsMessage *>(message_memory);
  typed_message->~MetricsMessage();
}

size_t size_function__MetricsMessage__statistics(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<statistics_msgs::msg::StatisticDataPoint> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MetricsMessage__statistics(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<statistics_msgs::msg::StatisticDataPoint> *>(untyped_member);
  return &member[index];
}

void * get_function__MetricsMessage__statistics(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<statistics_msgs::msg::StatisticDataPoint> *>(untyped_member);
  return &member[index];
}

void fetch_function__MetricsMessage__statistics(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const statistics_msgs::msg::StatisticDataPoint *>(
    get_const_function__MetricsMessage__statistics(untyped_member, index));
  auto & value = *reinterpret_cast<statistics_msgs::msg::StatisticDataPoint *>(untyped_value);
  value = item;
}

void assign_function__MetricsMessage__statistics(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<statistics_msgs::msg::StatisticDataPoint *>(
    get_function__MetricsMessage__statistics(untyped_member, index));
  const auto & value = *reinterpret_cast<const statistics_msgs::msg::StatisticDataPoint *>(untyped_value);
  item = value;
}

void resize_function__MetricsMessage__statistics(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<statistics_msgs::msg::StatisticDataPoint> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MetricsMessage_message_member_array[6] = {
  {
    "measurement_source_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs::msg::MetricsMessage, measurement_source_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "metrics_source",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs::msg::MetricsMessage, metrics_source),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "unit",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs::msg::MetricsMessage, unit),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "window_start",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs::msg::MetricsMessage, window_start),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "window_stop",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs::msg::MetricsMessage, window_stop),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "statistics",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<statistics_msgs::msg::StatisticDataPoint>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs::msg::MetricsMessage, statistics),  // bytes offset in struct
    nullptr,  // default value
    size_function__MetricsMessage__statistics,  // size() function pointer
    get_const_function__MetricsMessage__statistics,  // get_const(index) function pointer
    get_function__MetricsMessage__statistics,  // get(index) function pointer
    fetch_function__MetricsMessage__statistics,  // fetch(index, &value) function pointer
    assign_function__MetricsMessage__statistics,  // assign(index, value) function pointer
    resize_function__MetricsMessage__statistics  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MetricsMessage_message_members = {
  "statistics_msgs::msg",  // message namespace
  "MetricsMessage",  // message name
  6,  // number of fields
  sizeof(statistics_msgs::msg::MetricsMessage),
  false,  // has_any_key_member_
  MetricsMessage_message_member_array,  // message members
  MetricsMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  MetricsMessage_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MetricsMessage_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MetricsMessage_message_members,
  get_message_typesupport_handle_function,
  &statistics_msgs__msg__MetricsMessage__get_type_hash,
  &statistics_msgs__msg__MetricsMessage__get_type_description,
  &statistics_msgs__msg__MetricsMessage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace statistics_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<statistics_msgs::msg::MetricsMessage>()
{
  return &::statistics_msgs::msg::rosidl_typesupport_introspection_cpp::MetricsMessage_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, statistics_msgs, msg, MetricsMessage)() {
  return &::statistics_msgs::msg::rosidl_typesupport_introspection_cpp::MetricsMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
