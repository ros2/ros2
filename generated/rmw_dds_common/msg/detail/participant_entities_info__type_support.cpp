// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rmw_dds_common:msg/ParticipantEntitiesInfo.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rmw_dds_common/msg/detail/participant_entities_info__functions.h"
#include "rmw_dds_common/msg/detail/participant_entities_info__struct.hpp"
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

void ParticipantEntitiesInfo_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rmw_dds_common::msg::ParticipantEntitiesInfo(_init);
}

void ParticipantEntitiesInfo_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rmw_dds_common::msg::ParticipantEntitiesInfo *>(message_memory);
  typed_message->~ParticipantEntitiesInfo();
}

size_t size_function__ParticipantEntitiesInfo__node_entities_info_seq(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rmw_dds_common::msg::NodeEntitiesInfo> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParticipantEntitiesInfo__node_entities_info_seq(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rmw_dds_common::msg::NodeEntitiesInfo> *>(untyped_member);
  return &member[index];
}

void * get_function__ParticipantEntitiesInfo__node_entities_info_seq(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rmw_dds_common::msg::NodeEntitiesInfo> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParticipantEntitiesInfo__node_entities_info_seq(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rmw_dds_common::msg::NodeEntitiesInfo *>(
    get_const_function__ParticipantEntitiesInfo__node_entities_info_seq(untyped_member, index));
  auto & value = *reinterpret_cast<rmw_dds_common::msg::NodeEntitiesInfo *>(untyped_value);
  value = item;
}

void assign_function__ParticipantEntitiesInfo__node_entities_info_seq(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rmw_dds_common::msg::NodeEntitiesInfo *>(
    get_function__ParticipantEntitiesInfo__node_entities_info_seq(untyped_member, index));
  const auto & value = *reinterpret_cast<const rmw_dds_common::msg::NodeEntitiesInfo *>(untyped_value);
  item = value;
}

void resize_function__ParticipantEntitiesInfo__node_entities_info_seq(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rmw_dds_common::msg::NodeEntitiesInfo> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ParticipantEntitiesInfo_message_member_array[2] = {
  {
    "gid",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rmw_dds_common::msg::Gid>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rmw_dds_common::msg::ParticipantEntitiesInfo, gid),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "node_entities_info_seq",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rmw_dds_common::msg::NodeEntitiesInfo>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rmw_dds_common::msg::ParticipantEntitiesInfo, node_entities_info_seq),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParticipantEntitiesInfo__node_entities_info_seq,  // size() function pointer
    get_const_function__ParticipantEntitiesInfo__node_entities_info_seq,  // get_const(index) function pointer
    get_function__ParticipantEntitiesInfo__node_entities_info_seq,  // get(index) function pointer
    fetch_function__ParticipantEntitiesInfo__node_entities_info_seq,  // fetch(index, &value) function pointer
    assign_function__ParticipantEntitiesInfo__node_entities_info_seq,  // assign(index, value) function pointer
    resize_function__ParticipantEntitiesInfo__node_entities_info_seq  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ParticipantEntitiesInfo_message_members = {
  "rmw_dds_common::msg",  // message namespace
  "ParticipantEntitiesInfo",  // message name
  2,  // number of fields
  sizeof(rmw_dds_common::msg::ParticipantEntitiesInfo),
  false,  // has_any_key_member_
  ParticipantEntitiesInfo_message_member_array,  // message members
  ParticipantEntitiesInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  ParticipantEntitiesInfo_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ParticipantEntitiesInfo_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ParticipantEntitiesInfo_message_members,
  get_message_typesupport_handle_function,
  &rmw_dds_common__msg__ParticipantEntitiesInfo__get_type_hash,
  &rmw_dds_common__msg__ParticipantEntitiesInfo__get_type_description,
  &rmw_dds_common__msg__ParticipantEntitiesInfo__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rmw_dds_common


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rmw_dds_common::msg::ParticipantEntitiesInfo>()
{
  return &::rmw_dds_common::msg::rosidl_typesupport_introspection_cpp::ParticipantEntitiesInfo_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rmw_dds_common, msg, ParticipantEntitiesInfo)() {
  return &::rmw_dds_common::msg::rosidl_typesupport_introspection_cpp::ParticipantEntitiesInfo_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
