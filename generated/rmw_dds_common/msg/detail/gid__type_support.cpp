// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rmw_dds_common:msg/Gid.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rmw_dds_common/msg/detail/gid__functions.h"
#include "rmw_dds_common/msg/detail/gid__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace rmw_dds_common
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Gid_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rmw_dds_common::msg::Gid(_init);
}

void Gid_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rmw_dds_common::msg::Gid *>(message_memory);
  typed_message->~Gid();
}

size_t size_function__Gid__data(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__Gid__data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__Gid__data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__Gid__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__Gid__data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__Gid__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__Gid__data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Gid_message_member_array[1] = {
  {
    "data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(rmw_dds_common::msg::Gid, data),  // bytes offset in struct
    nullptr,  // default value
    size_function__Gid__data,  // size() function pointer
    get_const_function__Gid__data,  // get_const(index) function pointer
    get_function__Gid__data,  // get(index) function pointer
    fetch_function__Gid__data,  // fetch(index, &value) function pointer
    assign_function__Gid__data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Gid_message_members = {
  "rmw_dds_common::msg",  // message namespace
  "Gid",  // message name
  1,  // number of fields
  sizeof(rmw_dds_common::msg::Gid),
  false,  // has_any_key_member_
  Gid_message_member_array,  // message members
  Gid_init_function,  // function to initialize message memory (memory has to be allocated)
  Gid_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Gid_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Gid_message_members,
  get_message_typesupport_handle_function,
  &rmw_dds_common__msg__Gid__get_type_hash,
  &rmw_dds_common__msg__Gid__get_type_description,
  &rmw_dds_common__msg__Gid__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rmw_dds_common


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rmw_dds_common::msg::Gid>()
{
  return &::rmw_dds_common::msg::rosidl_typesupport_introspection_cpp::Gid_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rmw_dds_common, msg, Gid)() {
  return &::rmw_dds_common::msg::rosidl_typesupport_introspection_cpp::Gid_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
