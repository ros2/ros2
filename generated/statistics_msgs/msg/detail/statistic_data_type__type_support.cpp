// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from statistics_msgs:msg/StatisticDataType.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "statistics_msgs/msg/detail/statistic_data_type__functions.h"
#include "statistics_msgs/msg/detail/statistic_data_type__struct.hpp"
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

void StatisticDataType_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) statistics_msgs::msg::StatisticDataType(_init);
}

void StatisticDataType_fini_function(void * message_memory)
{
  auto typed_message = static_cast<statistics_msgs::msg::StatisticDataType *>(message_memory);
  typed_message->~StatisticDataType();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember StatisticDataType_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs::msg::StatisticDataType, structure_needs_at_least_one_member),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers StatisticDataType_message_members = {
  "statistics_msgs::msg",  // message namespace
  "StatisticDataType",  // message name
  1,  // number of fields
  sizeof(statistics_msgs::msg::StatisticDataType),
  false,  // has_any_key_member_
  StatisticDataType_message_member_array,  // message members
  StatisticDataType_init_function,  // function to initialize message memory (memory has to be allocated)
  StatisticDataType_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t StatisticDataType_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &StatisticDataType_message_members,
  get_message_typesupport_handle_function,
  &statistics_msgs__msg__StatisticDataType__get_type_hash,
  &statistics_msgs__msg__StatisticDataType__get_type_description,
  &statistics_msgs__msg__StatisticDataType__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace statistics_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<statistics_msgs::msg::StatisticDataType>()
{
  return &::statistics_msgs::msg::rosidl_typesupport_introspection_cpp::StatisticDataType_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, statistics_msgs, msg, StatisticDataType)() {
  return &::statistics_msgs::msg::rosidl_typesupport_introspection_cpp::StatisticDataType_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
