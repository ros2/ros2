// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rosgraph_msgs:msg/Clock.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rosgraph_msgs/msg/detail/clock__functions.h"
#include "rosgraph_msgs/msg/detail/clock__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace rosgraph_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Clock_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rosgraph_msgs::msg::Clock(_init);
}

void Clock_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rosgraph_msgs::msg::Clock *>(message_memory);
  typed_message->~Clock();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Clock_message_member_array[1] = {
  {
    "clock",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rosgraph_msgs::msg::Clock, clock),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Clock_message_members = {
  "rosgraph_msgs::msg",  // message namespace
  "Clock",  // message name
  1,  // number of fields
  sizeof(rosgraph_msgs::msg::Clock),
  false,  // has_any_key_member_
  Clock_message_member_array,  // message members
  Clock_init_function,  // function to initialize message memory (memory has to be allocated)
  Clock_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Clock_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Clock_message_members,
  get_message_typesupport_handle_function,
  &rosgraph_msgs__msg__Clock__get_type_hash,
  &rosgraph_msgs__msg__Clock__get_type_description,
  &rosgraph_msgs__msg__Clock__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rosgraph_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rosgraph_msgs::msg::Clock>()
{
  return &::rosgraph_msgs::msg::rosidl_typesupport_introspection_cpp::Clock_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rosgraph_msgs, msg, Clock)() {
  return &::rosgraph_msgs::msg::rosidl_typesupport_introspection_cpp::Clock_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
