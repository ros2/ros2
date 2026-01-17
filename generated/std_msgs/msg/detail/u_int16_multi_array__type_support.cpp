// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from std_msgs:msg/UInt16MultiArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "std_msgs/msg/detail/u_int16_multi_array__functions.h"
#include "std_msgs/msg/detail/u_int16_multi_array__struct.hpp"
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

void UInt16MultiArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) std_msgs::msg::UInt16MultiArray(_init);
}

void UInt16MultiArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<std_msgs::msg::UInt16MultiArray *>(message_memory);
  typed_message->~UInt16MultiArray();
}

size_t size_function__UInt16MultiArray__data(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uint16_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__UInt16MultiArray__data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uint16_t> *>(untyped_member);
  return &member[index];
}

void * get_function__UInt16MultiArray__data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uint16_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__UInt16MultiArray__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint16_t *>(
    get_const_function__UInt16MultiArray__data(untyped_member, index));
  auto & value = *reinterpret_cast<uint16_t *>(untyped_value);
  value = item;
}

void assign_function__UInt16MultiArray__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint16_t *>(
    get_function__UInt16MultiArray__data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint16_t *>(untyped_value);
  item = value;
}

void resize_function__UInt16MultiArray__data(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uint16_t> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember UInt16MultiArray_message_member_array[2] = {
  {
    "layout",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::MultiArrayLayout>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(std_msgs::msg::UInt16MultiArray, layout),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(std_msgs::msg::UInt16MultiArray, data),  // bytes offset in struct
    nullptr,  // default value
    size_function__UInt16MultiArray__data,  // size() function pointer
    get_const_function__UInt16MultiArray__data,  // get_const(index) function pointer
    get_function__UInt16MultiArray__data,  // get(index) function pointer
    fetch_function__UInt16MultiArray__data,  // fetch(index, &value) function pointer
    assign_function__UInt16MultiArray__data,  // assign(index, value) function pointer
    resize_function__UInt16MultiArray__data  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers UInt16MultiArray_message_members = {
  "std_msgs::msg",  // message namespace
  "UInt16MultiArray",  // message name
  2,  // number of fields
  sizeof(std_msgs::msg::UInt16MultiArray),
  false,  // has_any_key_member_
  UInt16MultiArray_message_member_array,  // message members
  UInt16MultiArray_init_function,  // function to initialize message memory (memory has to be allocated)
  UInt16MultiArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t UInt16MultiArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &UInt16MultiArray_message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__UInt16MultiArray__get_type_hash,
  &std_msgs__msg__UInt16MultiArray__get_type_description,
  &std_msgs__msg__UInt16MultiArray__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace std_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<std_msgs::msg::UInt16MultiArray>()
{
  return &::std_msgs::msg::rosidl_typesupport_introspection_cpp::UInt16MultiArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, std_msgs, msg, UInt16MultiArray)() {
  return &::std_msgs::msg::rosidl_typesupport_introspection_cpp::UInt16MultiArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
