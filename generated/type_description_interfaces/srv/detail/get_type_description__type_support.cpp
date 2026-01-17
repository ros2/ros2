// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from type_description_interfaces:srv/GetTypeDescription.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "type_description_interfaces/srv/detail/get_type_description__functions.h"
#include "type_description_interfaces/srv/detail/get_type_description__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace type_description_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetTypeDescription_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) type_description_interfaces::srv::GetTypeDescription_Request(_init);
}

void GetTypeDescription_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<type_description_interfaces::srv::GetTypeDescription_Request *>(message_memory);
  typed_message->~GetTypeDescription_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetTypeDescription_Request_message_member_array[3] = {
  {
    "type_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Request, type_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "type_hash",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Request, type_hash),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "include_type_sources",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Request, include_type_sources),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetTypeDescription_Request_message_members = {
  "type_description_interfaces::srv",  // message namespace
  "GetTypeDescription_Request",  // message name
  3,  // number of fields
  sizeof(type_description_interfaces::srv::GetTypeDescription_Request),
  false,  // has_any_key_member_
  GetTypeDescription_Request_message_member_array,  // message members
  GetTypeDescription_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetTypeDescription_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetTypeDescription_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetTypeDescription_Request_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__srv__GetTypeDescription_Request__get_type_hash,
  &type_description_interfaces__srv__GetTypeDescription_Request__get_type_description,
  &type_description_interfaces__srv__GetTypeDescription_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace type_description_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::srv::GetTypeDescription_Request>()
{
  return &::type_description_interfaces::srv::rosidl_typesupport_introspection_cpp::GetTypeDescription_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, type_description_interfaces, srv, GetTypeDescription_Request)() {
  return &::type_description_interfaces::srv::rosidl_typesupport_introspection_cpp::GetTypeDescription_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__functions.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace type_description_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetTypeDescription_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) type_description_interfaces::srv::GetTypeDescription_Response(_init);
}

void GetTypeDescription_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<type_description_interfaces::srv::GetTypeDescription_Response *>(message_memory);
  typed_message->~GetTypeDescription_Response();
}

size_t size_function__GetTypeDescription_Response__type_sources(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<type_description_interfaces::msg::TypeSource> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetTypeDescription_Response__type_sources(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<type_description_interfaces::msg::TypeSource> *>(untyped_member);
  return &member[index];
}

void * get_function__GetTypeDescription_Response__type_sources(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<type_description_interfaces::msg::TypeSource> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetTypeDescription_Response__type_sources(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const type_description_interfaces::msg::TypeSource *>(
    get_const_function__GetTypeDescription_Response__type_sources(untyped_member, index));
  auto & value = *reinterpret_cast<type_description_interfaces::msg::TypeSource *>(untyped_value);
  value = item;
}

void assign_function__GetTypeDescription_Response__type_sources(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<type_description_interfaces::msg::TypeSource *>(
    get_function__GetTypeDescription_Response__type_sources(untyped_member, index));
  const auto & value = *reinterpret_cast<const type_description_interfaces::msg::TypeSource *>(untyped_value);
  item = value;
}

void resize_function__GetTypeDescription_Response__type_sources(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<type_description_interfaces::msg::TypeSource> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetTypeDescription_Response__extra_information(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<type_description_interfaces::msg::KeyValue> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetTypeDescription_Response__extra_information(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<type_description_interfaces::msg::KeyValue> *>(untyped_member);
  return &member[index];
}

void * get_function__GetTypeDescription_Response__extra_information(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<type_description_interfaces::msg::KeyValue> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetTypeDescription_Response__extra_information(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const type_description_interfaces::msg::KeyValue *>(
    get_const_function__GetTypeDescription_Response__extra_information(untyped_member, index));
  auto & value = *reinterpret_cast<type_description_interfaces::msg::KeyValue *>(untyped_value);
  value = item;
}

void assign_function__GetTypeDescription_Response__extra_information(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<type_description_interfaces::msg::KeyValue *>(
    get_function__GetTypeDescription_Response__extra_information(untyped_member, index));
  const auto & value = *reinterpret_cast<const type_description_interfaces::msg::KeyValue *>(untyped_value);
  item = value;
}

void resize_function__GetTypeDescription_Response__extra_information(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<type_description_interfaces::msg::KeyValue> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetTypeDescription_Response_message_member_array[5] = {
  {
    "successful",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Response, successful),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "failure_reason",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Response, failure_reason),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "type_description",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::msg::TypeDescription>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Response, type_description),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "type_sources",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::msg::TypeSource>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Response, type_sources),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetTypeDescription_Response__type_sources,  // size() function pointer
    get_const_function__GetTypeDescription_Response__type_sources,  // get_const(index) function pointer
    get_function__GetTypeDescription_Response__type_sources,  // get(index) function pointer
    fetch_function__GetTypeDescription_Response__type_sources,  // fetch(index, &value) function pointer
    assign_function__GetTypeDescription_Response__type_sources,  // assign(index, value) function pointer
    resize_function__GetTypeDescription_Response__type_sources  // resize(index) function pointer
  },
  {
    "extra_information",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::msg::KeyValue>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Response, extra_information),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetTypeDescription_Response__extra_information,  // size() function pointer
    get_const_function__GetTypeDescription_Response__extra_information,  // get_const(index) function pointer
    get_function__GetTypeDescription_Response__extra_information,  // get(index) function pointer
    fetch_function__GetTypeDescription_Response__extra_information,  // fetch(index, &value) function pointer
    assign_function__GetTypeDescription_Response__extra_information,  // assign(index, value) function pointer
    resize_function__GetTypeDescription_Response__extra_information  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetTypeDescription_Response_message_members = {
  "type_description_interfaces::srv",  // message namespace
  "GetTypeDescription_Response",  // message name
  5,  // number of fields
  sizeof(type_description_interfaces::srv::GetTypeDescription_Response),
  false,  // has_any_key_member_
  GetTypeDescription_Response_message_member_array,  // message members
  GetTypeDescription_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetTypeDescription_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetTypeDescription_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetTypeDescription_Response_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__srv__GetTypeDescription_Response__get_type_hash,
  &type_description_interfaces__srv__GetTypeDescription_Response__get_type_description,
  &type_description_interfaces__srv__GetTypeDescription_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace type_description_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::srv::GetTypeDescription_Response>()
{
  return &::type_description_interfaces::srv::rosidl_typesupport_introspection_cpp::GetTypeDescription_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, type_description_interfaces, srv, GetTypeDescription_Response)() {
  return &::type_description_interfaces::srv::rosidl_typesupport_introspection_cpp::GetTypeDescription_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__functions.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace type_description_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetTypeDescription_Event_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) type_description_interfaces::srv::GetTypeDescription_Event(_init);
}

void GetTypeDescription_Event_fini_function(void * message_memory)
{
  auto typed_message = static_cast<type_description_interfaces::srv::GetTypeDescription_Event *>(message_memory);
  typed_message->~GetTypeDescription_Event();
}

size_t size_function__GetTypeDescription_Event__request(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<type_description_interfaces::srv::GetTypeDescription_Request> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetTypeDescription_Event__request(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<type_description_interfaces::srv::GetTypeDescription_Request> *>(untyped_member);
  return &member[index];
}

void * get_function__GetTypeDescription_Event__request(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<type_description_interfaces::srv::GetTypeDescription_Request> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetTypeDescription_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const type_description_interfaces::srv::GetTypeDescription_Request *>(
    get_const_function__GetTypeDescription_Event__request(untyped_member, index));
  auto & value = *reinterpret_cast<type_description_interfaces::srv::GetTypeDescription_Request *>(untyped_value);
  value = item;
}

void assign_function__GetTypeDescription_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<type_description_interfaces::srv::GetTypeDescription_Request *>(
    get_function__GetTypeDescription_Event__request(untyped_member, index));
  const auto & value = *reinterpret_cast<const type_description_interfaces::srv::GetTypeDescription_Request *>(untyped_value);
  item = value;
}

void resize_function__GetTypeDescription_Event__request(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<type_description_interfaces::srv::GetTypeDescription_Request> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetTypeDescription_Event__response(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<type_description_interfaces::srv::GetTypeDescription_Response> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetTypeDescription_Event__response(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<type_description_interfaces::srv::GetTypeDescription_Response> *>(untyped_member);
  return &member[index];
}

void * get_function__GetTypeDescription_Event__response(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<type_description_interfaces::srv::GetTypeDescription_Response> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetTypeDescription_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const type_description_interfaces::srv::GetTypeDescription_Response *>(
    get_const_function__GetTypeDescription_Event__response(untyped_member, index));
  auto & value = *reinterpret_cast<type_description_interfaces::srv::GetTypeDescription_Response *>(untyped_value);
  value = item;
}

void assign_function__GetTypeDescription_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<type_description_interfaces::srv::GetTypeDescription_Response *>(
    get_function__GetTypeDescription_Event__response(untyped_member, index));
  const auto & value = *reinterpret_cast<const type_description_interfaces::srv::GetTypeDescription_Response *>(untyped_value);
  item = value;
}

void resize_function__GetTypeDescription_Event__response(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<type_description_interfaces::srv::GetTypeDescription_Response> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetTypeDescription_Event_message_member_array[3] = {
  {
    "info",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<service_msgs::msg::ServiceEventInfo>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Event, info),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "request",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::srv::GetTypeDescription_Request>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Event, request),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetTypeDescription_Event__request,  // size() function pointer
    get_const_function__GetTypeDescription_Event__request,  // get_const(index) function pointer
    get_function__GetTypeDescription_Event__request,  // get(index) function pointer
    fetch_function__GetTypeDescription_Event__request,  // fetch(index, &value) function pointer
    assign_function__GetTypeDescription_Event__request,  // assign(index, value) function pointer
    resize_function__GetTypeDescription_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::srv::GetTypeDescription_Response>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(type_description_interfaces::srv::GetTypeDescription_Event, response),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetTypeDescription_Event__response,  // size() function pointer
    get_const_function__GetTypeDescription_Event__response,  // get_const(index) function pointer
    get_function__GetTypeDescription_Event__response,  // get(index) function pointer
    fetch_function__GetTypeDescription_Event__response,  // fetch(index, &value) function pointer
    assign_function__GetTypeDescription_Event__response,  // assign(index, value) function pointer
    resize_function__GetTypeDescription_Event__response  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetTypeDescription_Event_message_members = {
  "type_description_interfaces::srv",  // message namespace
  "GetTypeDescription_Event",  // message name
  3,  // number of fields
  sizeof(type_description_interfaces::srv::GetTypeDescription_Event),
  false,  // has_any_key_member_
  GetTypeDescription_Event_message_member_array,  // message members
  GetTypeDescription_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  GetTypeDescription_Event_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetTypeDescription_Event_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetTypeDescription_Event_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__srv__GetTypeDescription_Event__get_type_hash,
  &type_description_interfaces__srv__GetTypeDescription_Event__get_type_description,
  &type_description_interfaces__srv__GetTypeDescription_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace type_description_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::srv::GetTypeDescription_Event>()
{
  return &::type_description_interfaces::srv::rosidl_typesupport_introspection_cpp::GetTypeDescription_Event_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, type_description_interfaces, srv, GetTypeDescription_Event)() {
  return &::type_description_interfaces::srv::rosidl_typesupport_introspection_cpp::GetTypeDescription_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__functions.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace type_description_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers GetTypeDescription_service_members = {
  "type_description_interfaces::srv",  // service namespace
  "GetTypeDescription",  // service name
  // the following fields are initialized below on first access
  // see get_service_type_support_handle<type_description_interfaces::srv::GetTypeDescription>()
  nullptr,  // request message
  nullptr,  // response message
  nullptr,  // event message
};

static const rosidl_service_type_support_t GetTypeDescription_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetTypeDescription_service_members,
  get_service_typesupport_handle_function,
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::srv::GetTypeDescription_Request>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::srv::GetTypeDescription_Response>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::srv::GetTypeDescription_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<type_description_interfaces::srv::GetTypeDescription>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<type_description_interfaces::srv::GetTypeDescription>,
  &type_description_interfaces__srv__GetTypeDescription__get_type_hash,
  &type_description_interfaces__srv__GetTypeDescription__get_type_description,
  &type_description_interfaces__srv__GetTypeDescription__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace type_description_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<type_description_interfaces::srv::GetTypeDescription>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::type_description_interfaces::srv::rosidl_typesupport_introspection_cpp::GetTypeDescription_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure all of the service_members are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr ||
    service_members->event_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::type_description_interfaces::srv::GetTypeDescription_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::type_description_interfaces::srv::GetTypeDescription_Response
      >()->data
      );
    // initialize the event_members_ with the static function from the external library
    service_members->event_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::type_description_interfaces::srv::GetTypeDescription_Event
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, type_description_interfaces, srv, GetTypeDescription)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<type_description_interfaces::srv::GetTypeDescription>();
}

#ifdef __cplusplus
}
#endif
