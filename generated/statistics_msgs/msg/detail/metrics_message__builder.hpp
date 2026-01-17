// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from statistics_msgs:msg/MetricsMessage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statistics_msgs/msg/metrics_message.hpp"


#ifndef STATISTICS_MSGS__MSG__DETAIL__METRICS_MESSAGE__BUILDER_HPP_
#define STATISTICS_MSGS__MSG__DETAIL__METRICS_MESSAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "statistics_msgs/msg/detail/metrics_message__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace statistics_msgs
{

namespace msg
{

namespace builder
{

class Init_MetricsMessage_statistics
{
public:
  explicit Init_MetricsMessage_statistics(::statistics_msgs::msg::MetricsMessage & msg)
  : msg_(msg)
  {}
  ::statistics_msgs::msg::MetricsMessage statistics(::statistics_msgs::msg::MetricsMessage::_statistics_type arg)
  {
    msg_.statistics = std::move(arg);
    return std::move(msg_);
  }

private:
  ::statistics_msgs::msg::MetricsMessage msg_;
};

class Init_MetricsMessage_window_stop
{
public:
  explicit Init_MetricsMessage_window_stop(::statistics_msgs::msg::MetricsMessage & msg)
  : msg_(msg)
  {}
  Init_MetricsMessage_statistics window_stop(::statistics_msgs::msg::MetricsMessage::_window_stop_type arg)
  {
    msg_.window_stop = std::move(arg);
    return Init_MetricsMessage_statistics(msg_);
  }

private:
  ::statistics_msgs::msg::MetricsMessage msg_;
};

class Init_MetricsMessage_window_start
{
public:
  explicit Init_MetricsMessage_window_start(::statistics_msgs::msg::MetricsMessage & msg)
  : msg_(msg)
  {}
  Init_MetricsMessage_window_stop window_start(::statistics_msgs::msg::MetricsMessage::_window_start_type arg)
  {
    msg_.window_start = std::move(arg);
    return Init_MetricsMessage_window_stop(msg_);
  }

private:
  ::statistics_msgs::msg::MetricsMessage msg_;
};

class Init_MetricsMessage_unit
{
public:
  explicit Init_MetricsMessage_unit(::statistics_msgs::msg::MetricsMessage & msg)
  : msg_(msg)
  {}
  Init_MetricsMessage_window_start unit(::statistics_msgs::msg::MetricsMessage::_unit_type arg)
  {
    msg_.unit = std::move(arg);
    return Init_MetricsMessage_window_start(msg_);
  }

private:
  ::statistics_msgs::msg::MetricsMessage msg_;
};

class Init_MetricsMessage_metrics_source
{
public:
  explicit Init_MetricsMessage_metrics_source(::statistics_msgs::msg::MetricsMessage & msg)
  : msg_(msg)
  {}
  Init_MetricsMessage_unit metrics_source(::statistics_msgs::msg::MetricsMessage::_metrics_source_type arg)
  {
    msg_.metrics_source = std::move(arg);
    return Init_MetricsMessage_unit(msg_);
  }

private:
  ::statistics_msgs::msg::MetricsMessage msg_;
};

class Init_MetricsMessage_measurement_source_name
{
public:
  Init_MetricsMessage_measurement_source_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MetricsMessage_metrics_source measurement_source_name(::statistics_msgs::msg::MetricsMessage::_measurement_source_name_type arg)
  {
    msg_.measurement_source_name = std::move(arg);
    return Init_MetricsMessage_metrics_source(msg_);
  }

private:
  ::statistics_msgs::msg::MetricsMessage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::statistics_msgs::msg::MetricsMessage>()
{
  return statistics_msgs::msg::builder::Init_MetricsMessage_measurement_source_name();
}

}  // namespace statistics_msgs

#endif  // STATISTICS_MSGS__MSG__DETAIL__METRICS_MESSAGE__BUILDER_HPP_
