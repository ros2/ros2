// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from lifecycle_msgs:msg/Transition.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "lifecycle_msgs/msg/detail/transition__functions.h"
#include "lifecycle_msgs/msg/detail/transition__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace lifecycle_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Transition_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) lifecycle_msgs::msg::Transition(_init);
}

void Transition_fini_function(void * message_memory)
{
  auto typed_message = static_cast<lifecycle_msgs::msg::Transition *>(message_memory);
  typed_message->~Transition();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Transition_message_member_array[2] = {
  {
    "id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::Transition, id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "label",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::Transition, label),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Transition_message_members = {
  "lifecycle_msgs::msg",  // message namespace
  "Transition",  // message name
  2,  // number of fields
  sizeof(lifecycle_msgs::msg::Transition),
  false,  // has_any_key_member_
  Transition_message_member_array,  // message members
  Transition_init_function,  // function to initialize message memory (memory has to be allocated)
  Transition_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Transition_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Transition_message_members,
  get_message_typesupport_handle_function,
  &lifecycle_msgs__msg__Transition__get_type_hash,
  &lifecycle_msgs__msg__Transition__get_type_description,
  &lifecycle_msgs__msg__Transition__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace lifecycle_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<lifecycle_msgs::msg::Transition>()
{
  return &::lifecycle_msgs::msg::rosidl_typesupport_introspection_cpp::Transition_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, lifecycle_msgs, msg, Transition)() {
  return &::lifecycle_msgs::msg::rosidl_typesupport_introspection_cpp::Transition_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
