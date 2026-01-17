// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rmw_dds_common:msg/Gid.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/gid.hpp"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__GID__BUILDER_HPP_
#define RMW_DDS_COMMON__MSG__DETAIL__GID__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rmw_dds_common/msg/detail/gid__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rmw_dds_common
{

namespace msg
{

namespace builder
{

class Init_Gid_data
{
public:
  Init_Gid_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rmw_dds_common::msg::Gid data(::rmw_dds_common::msg::Gid::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rmw_dds_common::msg::Gid msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rmw_dds_common::msg::Gid>()
{
  return rmw_dds_common::msg::builder::Init_Gid_data();
}

}  // namespace rmw_dds_common

#endif  // RMW_DDS_COMMON__MSG__DETAIL__GID__BUILDER_HPP_
