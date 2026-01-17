// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from unique_identifier_msgs:msg/UUID.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace unique_identifier_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void UUID_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) unique_identifier_msgs::msg::UUID(_init);
}

void UUID_fini_function(void * message_memory)
{
  auto typed_message = static_cast<unique_identifier_msgs::msg::UUID *>(message_memory);
  typed_message->~UUID();
}

size_t size_function__UUID__uuid(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__UUID__uuid(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__UUID__uuid(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__UUID__uuid(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__UUID__uuid(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__UUID__uuid(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__UUID__uuid(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember UUID_message_member_array[1] = {
  {
    "uuid",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(unique_identifier_msgs::msg::UUID, uuid),  // bytes offset in struct
    nullptr,  // default value
    size_function__UUID__uuid,  // size() function pointer
    get_const_function__UUID__uuid,  // get_const(index) function pointer
    get_function__UUID__uuid,  // get(index) function pointer
    fetch_function__UUID__uuid,  // fetch(index, &value) function pointer
    assign_function__UUID__uuid,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers UUID_message_members = {
  "unique_identifier_msgs::msg",  // message namespace
  "UUID",  // message name
  1,  // number of fields
  sizeof(unique_identifier_msgs::msg::UUID),
  false,  // has_any_key_member_
  UUID_message_member_array,  // message members
  UUID_init_function,  // function to initialize message memory (memory has to be allocated)
  UUID_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t UUID_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &UUID_message_members,
  get_message_typesupport_handle_function,
  &unique_identifier_msgs__msg__UUID__get_type_hash,
  &unique_identifier_msgs__msg__UUID__get_type_description,
  &unique_identifier_msgs__msg__UUID__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace unique_identifier_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<unique_identifier_msgs::msg::UUID>()
{
  return &::unique_identifier_msgs::msg::rosidl_typesupport_introspection_cpp::UUID_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, unique_identifier_msgs, msg, UUID)() {
  return &::unique_identifier_msgs::msg::rosidl_typesupport_introspection_cpp::UUID_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
