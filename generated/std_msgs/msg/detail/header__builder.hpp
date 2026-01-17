// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from std_msgs:msg/Header.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/header.hpp"


#ifndef STD_MSGS__MSG__DETAIL__HEADER__BUILDER_HPP_
#define STD_MSGS__MSG__DETAIL__HEADER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "std_msgs/msg/detail/header__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace std_msgs
{

namespace msg
{

namespace builder
{

class Init_Header_frame_id
{
public:
  explicit Init_Header_frame_id(::std_msgs::msg::Header & msg)
  : msg_(msg)
  {}
  ::std_msgs::msg::Header frame_id(::std_msgs::msg::Header::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::std_msgs::msg::Header msg_;
};

class Init_Header_stamp
{
public:
  Init_Header_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Header_frame_id stamp(::std_msgs::msg::Header::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_Header_frame_id(msg_);
  }

private:
  ::std_msgs::msg::Header msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::std_msgs::msg::Header>()
{
  return std_msgs::msg::builder::Init_Header_stamp();
}

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__HEADER__BUILDER_HPP_
