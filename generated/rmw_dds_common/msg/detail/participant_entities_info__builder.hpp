// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rmw_dds_common:msg/ParticipantEntitiesInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/participant_entities_info.hpp"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__BUILDER_HPP_
#define RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rmw_dds_common/msg/detail/participant_entities_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rmw_dds_common
{

namespace msg
{

namespace builder
{

class Init_ParticipantEntitiesInfo_node_entities_info_seq
{
public:
  explicit Init_ParticipantEntitiesInfo_node_entities_info_seq(::rmw_dds_common::msg::ParticipantEntitiesInfo & msg)
  : msg_(msg)
  {}
  ::rmw_dds_common::msg::ParticipantEntitiesInfo node_entities_info_seq(::rmw_dds_common::msg::ParticipantEntitiesInfo::_node_entities_info_seq_type arg)
  {
    msg_.node_entities_info_seq = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rmw_dds_common::msg::ParticipantEntitiesInfo msg_;
};

class Init_ParticipantEntitiesInfo_gid
{
public:
  Init_ParticipantEntitiesInfo_gid()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ParticipantEntitiesInfo_node_entities_info_seq gid(::rmw_dds_common::msg::ParticipantEntitiesInfo::_gid_type arg)
  {
    msg_.gid = std::move(arg);
    return Init_ParticipantEntitiesInfo_node_entities_info_seq(msg_);
  }

private:
  ::rmw_dds_common::msg::ParticipantEntitiesInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rmw_dds_common::msg::ParticipantEntitiesInfo>()
{
  return rmw_dds_common::msg::builder::Init_ParticipantEntitiesInfo_gid();
}

}  // namespace rmw_dds_common

#endif  // RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__BUILDER_HPP_
