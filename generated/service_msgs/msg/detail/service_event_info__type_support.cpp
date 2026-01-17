// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from service_msgs:msg/ServiceEventInfo.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "service_msgs/msg/detail/service_event_info__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace service_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ServiceEventInfo_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) service_msgs::msg::ServiceEventInfo(_init);
}

void ServiceEventInfo_fini_function(void * message_memory)
{
  auto typed_message = static_cast<service_msgs::msg::ServiceEventInfo *>(message_memory);
  typed_message->~ServiceEventInfo();
}

size_t size_function__ServiceEventInfo__client_gid(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__ServiceEventInfo__client_gid(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__ServiceEventInfo__client_gid(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__ServiceEventInfo__client_gid(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__ServiceEventInfo__client_gid(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__ServiceEventInfo__client_gid(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__ServiceEventInfo__client_gid(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ServiceEventInfo_message_member_array[4] = {
  {
    "event_type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_msgs::msg::ServiceEventInfo, event_type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "stamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_msgs::msg::ServiceEventInfo, stamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "client_gid",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(service_msgs::msg::ServiceEventInfo, client_gid),  // bytes offset in struct
    nullptr,  // default value
    size_function__ServiceEventInfo__client_gid,  // size() function pointer
    get_const_function__ServiceEventInfo__client_gid,  // get_const(index) function pointer
    get_function__ServiceEventInfo__client_gid,  // get(index) function pointer
    fetch_function__ServiceEventInfo__client_gid,  // fetch(index, &value) function pointer
    assign_function__ServiceEventInfo__client_gid,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "sequence_number",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_msgs::msg::ServiceEventInfo, sequence_number),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ServiceEventInfo_message_members = {
  "service_msgs::msg",  // message namespace
  "ServiceEventInfo",  // message name
  4,  // number of fields
  sizeof(service_msgs::msg::ServiceEventInfo),
  false,  // has_any_key_member_
  ServiceEventInfo_message_member_array,  // message members
  ServiceEventInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  ServiceEventInfo_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ServiceEventInfo_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ServiceEventInfo_message_members,
  get_message_typesupport_handle_function,
  &service_msgs__msg__ServiceEventInfo__get_type_hash,
  &service_msgs__msg__ServiceEventInfo__get_type_description,
  &service_msgs__msg__ServiceEventInfo__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace service_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<service_msgs::msg::ServiceEventInfo>()
{
  return &::service_msgs::msg::rosidl_typesupport_introspection_cpp::ServiceEventInfo_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, service_msgs, msg, ServiceEventInfo)() {
  return &::service_msgs::msg::rosidl_typesupport_introspection_cpp::ServiceEventInfo_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
