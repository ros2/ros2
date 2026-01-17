// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from service_msgs:msg/ServiceEventInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "service_msgs/msg/service_event_info.hpp"


#ifndef SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__BUILDER_HPP_
#define SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "service_msgs/msg/detail/service_event_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace service_msgs
{

namespace msg
{

namespace builder
{

class Init_ServiceEventInfo_sequence_number
{
public:
  explicit Init_ServiceEventInfo_sequence_number(::service_msgs::msg::ServiceEventInfo & msg)
  : msg_(msg)
  {}
  ::service_msgs::msg::ServiceEventInfo sequence_number(::service_msgs::msg::ServiceEventInfo::_sequence_number_type arg)
  {
    msg_.sequence_number = std::move(arg);
    return std::move(msg_);
  }

private:
  ::service_msgs::msg::ServiceEventInfo msg_;
};

class Init_ServiceEventInfo_client_gid
{
public:
  explicit Init_ServiceEventInfo_client_gid(::service_msgs::msg::ServiceEventInfo & msg)
  : msg_(msg)
  {}
  Init_ServiceEventInfo_sequence_number client_gid(::service_msgs::msg::ServiceEventInfo::_client_gid_type arg)
  {
    msg_.client_gid = std::move(arg);
    return Init_ServiceEventInfo_sequence_number(msg_);
  }

private:
  ::service_msgs::msg::ServiceEventInfo msg_;
};

class Init_ServiceEventInfo_stamp
{
public:
  explicit Init_ServiceEventInfo_stamp(::service_msgs::msg::ServiceEventInfo & msg)
  : msg_(msg)
  {}
  Init_ServiceEventInfo_client_gid stamp(::service_msgs::msg::ServiceEventInfo::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_ServiceEventInfo_client_gid(msg_);
  }

private:
  ::service_msgs::msg::ServiceEventInfo msg_;
};

class Init_ServiceEventInfo_event_type
{
public:
  Init_ServiceEventInfo_event_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServiceEventInfo_stamp event_type(::service_msgs::msg::ServiceEventInfo::_event_type_type arg)
  {
    msg_.event_type = std::move(arg);
    return Init_ServiceEventInfo_stamp(msg_);
  }

private:
  ::service_msgs::msg::ServiceEventInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::service_msgs::msg::ServiceEventInfo>()
{
  return service_msgs::msg::builder::Init_ServiceEventInfo_event_type();
}

}  // namespace service_msgs

#endif  // SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__BUILDER_HPP_
