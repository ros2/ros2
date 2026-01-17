// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from std_msgs:msg/MultiArrayLayout.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "std_msgs/msg/detail/multi_array_layout__functions.h"
#include "std_msgs/msg/detail/multi_array_layout__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace std_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void MultiArrayLayout_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) std_msgs::msg::MultiArrayLayout(_init);
}

void MultiArrayLayout_fini_function(void * message_memory)
{
  auto typed_message = static_cast<std_msgs::msg::MultiArrayLayout *>(message_memory);
  typed_message->~MultiArrayLayout();
}

size_t size_function__MultiArrayLayout__dim(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std_msgs::msg::MultiArrayDimension> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MultiArrayLayout__dim(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std_msgs::msg::MultiArrayDimension> *>(untyped_member);
  return &member[index];
}

void * get_function__MultiArrayLayout__dim(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std_msgs::msg::MultiArrayDimension> *>(untyped_member);
  return &member[index];
}

void fetch_function__MultiArrayLayout__dim(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std_msgs::msg::MultiArrayDimension *>(
    get_const_function__MultiArrayLayout__dim(untyped_member, index));
  auto & value = *reinterpret_cast<std_msgs::msg::MultiArrayDimension *>(untyped_value);
  value = item;
}

void assign_function__MultiArrayLayout__dim(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std_msgs::msg::MultiArrayDimension *>(
    get_function__MultiArrayLayout__dim(untyped_member, index));
  const auto & value = *reinterpret_cast<const std_msgs::msg::MultiArrayDimension *>(untyped_value);
  item = value;
}

void resize_function__MultiArrayLayout__dim(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std_msgs::msg::MultiArrayDimension> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MultiArrayLayout_message_member_array[2] = {
  {
    "dim",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::MultiArrayDimension>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(std_msgs::msg::MultiArrayLayout, dim),  // bytes offset in struct
    nullptr,  // default value
    size_function__MultiArrayLayout__dim,  // size() function pointer
    get_const_function__MultiArrayLayout__dim,  // get_const(index) function pointer
    get_function__MultiArrayLayout__dim,  // get(index) function pointer
    fetch_function__MultiArrayLayout__dim,  // fetch(index, &value) function pointer
    assign_function__MultiArrayLayout__dim,  // assign(index, value) function pointer
    resize_function__MultiArrayLayout__dim  // resize(index) function pointer
  },
  {
    "data_offset",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(std_msgs::msg::MultiArrayLayout, data_offset),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MultiArrayLayout_message_members = {
  "std_msgs::msg",  // message namespace
  "MultiArrayLayout",  // message name
  2,  // number of fields
  sizeof(std_msgs::msg::MultiArrayLayout),
  false,  // has_any_key_member_
  MultiArrayLayout_message_member_array,  // message members
  MultiArrayLayout_init_function,  // function to initialize message memory (memory has to be allocated)
  MultiArrayLayout_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MultiArrayLayout_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MultiArrayLayout_message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__MultiArrayLayout__get_type_hash,
  &std_msgs__msg__MultiArrayLayout__get_type_description,
  &std_msgs__msg__MultiArrayLayout__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace std_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<std_msgs::msg::MultiArrayLayout>()
{
  return &::std_msgs::msg::rosidl_typesupport_introspection_cpp::MultiArrayLayout_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, std_msgs, msg, MultiArrayLayout)() {
  return &::std_msgs::msg::rosidl_typesupport_introspection_cpp::MultiArrayLayout_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
