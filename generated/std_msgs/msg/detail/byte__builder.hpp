// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from std_msgs:msg/Byte.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/byte.hpp"


#ifndef STD_MSGS__MSG__DETAIL__BYTE__BUILDER_HPP_
#define STD_MSGS__MSG__DETAIL__BYTE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "std_msgs/msg/detail/byte__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace std_msgs
{

namespace msg
{

namespace builder
{

class Init_Byte_data
{
public:
  Init_Byte_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::std_msgs::msg::Byte data(::std_msgs::msg::Byte::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::std_msgs::msg::Byte msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::std_msgs::msg::Byte>()
{
  return std_msgs::msg::builder::Init_Byte_data();
}

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__BYTE__BUILDER_HPP_
