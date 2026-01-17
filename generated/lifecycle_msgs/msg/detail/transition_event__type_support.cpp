// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from lifecycle_msgs:msg/TransitionEvent.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "lifecycle_msgs/msg/detail/transition_event__functions.h"
#include "lifecycle_msgs/msg/detail/transition_event__struct.hpp"
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

void TransitionEvent_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) lifecycle_msgs::msg::TransitionEvent(_init);
}

void TransitionEvent_fini_function(void * message_memory)
{
  auto typed_message = static_cast<lifecycle_msgs::msg::TransitionEvent *>(message_memory);
  typed_message->~TransitionEvent();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember TransitionEvent_message_member_array[4] = {
  {
    "timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::TransitionEvent, timestamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "transition",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<lifecycle_msgs::msg::Transition>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::TransitionEvent, transition),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "start_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<lifecycle_msgs::msg::State>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::TransitionEvent, start_state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "goal_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<lifecycle_msgs::msg::State>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::TransitionEvent, goal_state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers TransitionEvent_message_members = {
  "lifecycle_msgs::msg",  // message namespace
  "TransitionEvent",  // message name
  4,  // number of fields
  sizeof(lifecycle_msgs::msg::TransitionEvent),
  false,  // has_any_key_member_
  TransitionEvent_message_member_array,  // message members
  TransitionEvent_init_function,  // function to initialize message memory (memory has to be allocated)
  TransitionEvent_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t TransitionEvent_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &TransitionEvent_message_members,
  get_message_typesupport_handle_function,
  &lifecycle_msgs__msg__TransitionEvent__get_type_hash,
  &lifecycle_msgs__msg__TransitionEvent__get_type_description,
  &lifecycle_msgs__msg__TransitionEvent__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace lifecycle_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<lifecycle_msgs::msg::TransitionEvent>()
{
  return &::lifecycle_msgs::msg::rosidl_typesupport_introspection_cpp::TransitionEvent_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, lifecycle_msgs, msg, TransitionEvent)() {
  return &::lifecycle_msgs::msg::rosidl_typesupport_introspection_cpp::TransitionEvent_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
