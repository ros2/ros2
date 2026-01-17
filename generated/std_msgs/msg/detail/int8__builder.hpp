// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from std_msgs:msg/Int8.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/int8.hpp"


#ifndef STD_MSGS__MSG__DETAIL__INT8__BUILDER_HPP_
#define STD_MSGS__MSG__DETAIL__INT8__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "std_msgs/msg/detail/int8__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace std_msgs
{

namespace msg
{

namespace builder
{

class Init_Int8_data
{
public:
  Init_Int8_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::std_msgs::msg::Int8 data(::std_msgs::msg::Int8::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::std_msgs::msg::Int8 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::std_msgs::msg::Int8>()
{
  return std_msgs::msg::builder::Init_Int8_data();
}

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__INT8__BUILDER_HPP_
