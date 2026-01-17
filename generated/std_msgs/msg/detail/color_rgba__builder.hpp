// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from std_msgs:msg/ColorRGBA.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/color_rgba.hpp"


#ifndef STD_MSGS__MSG__DETAIL__COLOR_RGBA__BUILDER_HPP_
#define STD_MSGS__MSG__DETAIL__COLOR_RGBA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "std_msgs/msg/detail/color_rgba__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace std_msgs
{

namespace msg
{

namespace builder
{

class Init_ColorRGBA_a
{
public:
  explicit Init_ColorRGBA_a(::std_msgs::msg::ColorRGBA & msg)
  : msg_(msg)
  {}
  ::std_msgs::msg::ColorRGBA a(::std_msgs::msg::ColorRGBA::_a_type arg)
  {
    msg_.a = std::move(arg);
    return std::move(msg_);
  }

private:
  ::std_msgs::msg::ColorRGBA msg_;
};

class Init_ColorRGBA_b
{
public:
  explicit Init_ColorRGBA_b(::std_msgs::msg::ColorRGBA & msg)
  : msg_(msg)
  {}
  Init_ColorRGBA_a b(::std_msgs::msg::ColorRGBA::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_ColorRGBA_a(msg_);
  }

private:
  ::std_msgs::msg::ColorRGBA msg_;
};

class Init_ColorRGBA_g
{
public:
  explicit Init_ColorRGBA_g(::std_msgs::msg::ColorRGBA & msg)
  : msg_(msg)
  {}
  Init_ColorRGBA_b g(::std_msgs::msg::ColorRGBA::_g_type arg)
  {
    msg_.g = std::move(arg);
    return Init_ColorRGBA_b(msg_);
  }

private:
  ::std_msgs::msg::ColorRGBA msg_;
};

class Init_ColorRGBA_r
{
public:
  Init_ColorRGBA_r()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ColorRGBA_g r(::std_msgs::msg::ColorRGBA::_r_type arg)
  {
    msg_.r = std::move(arg);
    return Init_ColorRGBA_g(msg_);
  }

private:
  ::std_msgs::msg::ColorRGBA msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::std_msgs::msg::ColorRGBA>()
{
  return std_msgs::msg::builder::Init_ColorRGBA_r();
}

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__COLOR_RGBA__BUILDER_HPP_
