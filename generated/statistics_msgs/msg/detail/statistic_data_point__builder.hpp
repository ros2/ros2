// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from statistics_msgs:msg/StatisticDataPoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statistics_msgs/msg/statistic_data_point.hpp"


#ifndef STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__BUILDER_HPP_
#define STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "statistics_msgs/msg/detail/statistic_data_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace statistics_msgs
{

namespace msg
{

namespace builder
{

class Init_StatisticDataPoint_data
{
public:
  explicit Init_StatisticDataPoint_data(::statistics_msgs::msg::StatisticDataPoint & msg)
  : msg_(msg)
  {}
  ::statistics_msgs::msg::StatisticDataPoint data(::statistics_msgs::msg::StatisticDataPoint::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::statistics_msgs::msg::StatisticDataPoint msg_;
};

class Init_StatisticDataPoint_data_type
{
public:
  Init_StatisticDataPoint_data_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StatisticDataPoint_data data_type(::statistics_msgs::msg::StatisticDataPoint::_data_type_type arg)
  {
    msg_.data_type = std::move(arg);
    return Init_StatisticDataPoint_data(msg_);
  }

private:
  ::statistics_msgs::msg::StatisticDataPoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::statistics_msgs::msg::StatisticDataPoint>()
{
  return statistics_msgs::msg::builder::Init_StatisticDataPoint_data_type();
}

}  // namespace statistics_msgs

#endif  // STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__BUILDER_HPP_
