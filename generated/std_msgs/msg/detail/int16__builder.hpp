// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from std_msgs:msg/Int16.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/int16.hpp"


#ifndef STD_MSGS__MSG__DETAIL__INT16__BUILDER_HPP_
#define STD_MSGS__MSG__DETAIL__INT16__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "std_msgs/msg/detail/int16__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace std_msgs
{

namespace msg
{

namespace builder
{

class Init_Int16_data
{
public:
  Init_Int16_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::std_msgs::msg::Int16 data(::std_msgs::msg::Int16::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::std_msgs::msg::Int16 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::std_msgs::msg::Int16>()
{
  return std_msgs::msg::builder::Init_Int16_data();
}

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__INT16__BUILDER_HPP_
