// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rmw_dds_common:msg/NodeEntitiesInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/node_entities_info.hpp"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__BUILDER_HPP_
#define RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rmw_dds_common/msg/detail/node_entities_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rmw_dds_common
{

namespace msg
{

namespace builder
{

class Init_NodeEntitiesInfo_writer_gid_seq
{
public:
  explicit Init_NodeEntitiesInfo_writer_gid_seq(::rmw_dds_common::msg::NodeEntitiesInfo & msg)
  : msg_(msg)
  {}
  ::rmw_dds_common::msg::NodeEntitiesInfo writer_gid_seq(::rmw_dds_common::msg::NodeEntitiesInfo::_writer_gid_seq_type arg)
  {
    msg_.writer_gid_seq = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rmw_dds_common::msg::NodeEntitiesInfo msg_;
};

class Init_NodeEntitiesInfo_reader_gid_seq
{
public:
  explicit Init_NodeEntitiesInfo_reader_gid_seq(::rmw_dds_common::msg::NodeEntitiesInfo & msg)
  : msg_(msg)
  {}
  Init_NodeEntitiesInfo_writer_gid_seq reader_gid_seq(::rmw_dds_common::msg::NodeEntitiesInfo::_reader_gid_seq_type arg)
  {
    msg_.reader_gid_seq = std::move(arg);
    return Init_NodeEntitiesInfo_writer_gid_seq(msg_);
  }

private:
  ::rmw_dds_common::msg::NodeEntitiesInfo msg_;
};

class Init_NodeEntitiesInfo_node_name
{
public:
  explicit Init_NodeEntitiesInfo_node_name(::rmw_dds_common::msg::NodeEntitiesInfo & msg)
  : msg_(msg)
  {}
  Init_NodeEntitiesInfo_reader_gid_seq node_name(::rmw_dds_common::msg::NodeEntitiesInfo::_node_name_type arg)
  {
    msg_.node_name = std::move(arg);
    return Init_NodeEntitiesInfo_reader_gid_seq(msg_);
  }

private:
  ::rmw_dds_common::msg::NodeEntitiesInfo msg_;
};

class Init_NodeEntitiesInfo_node_namespace
{
public:
  Init_NodeEntitiesInfo_node_namespace()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NodeEntitiesInfo_node_name node_namespace(::rmw_dds_common::msg::NodeEntitiesInfo::_node_namespace_type arg)
  {
    msg_.node_namespace = std::move(arg);
    return Init_NodeEntitiesInfo_node_name(msg_);
  }

private:
  ::rmw_dds_common::msg::NodeEntitiesInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rmw_dds_common::msg::NodeEntitiesInfo>()
{
  return rmw_dds_common::msg::builder::Init_NodeEntitiesInfo_node_namespace();
}

}  // namespace rmw_dds_common

#endif  // RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__BUILDER_HPP_
