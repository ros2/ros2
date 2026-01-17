// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from std_msgs:msg/Int8MultiArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/int8_multi_array.hpp"


#ifndef STD_MSGS__MSG__DETAIL__INT8_MULTI_ARRAY__BUILDER_HPP_
#define STD_MSGS__MSG__DETAIL__INT8_MULTI_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "std_msgs/msg/detail/int8_multi_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace std_msgs
{

namespace msg
{

namespace builder
{

class Init_Int8MultiArray_data
{
public:
  explicit Init_Int8MultiArray_data(::std_msgs::msg::Int8MultiArray & msg)
  : msg_(msg)
  {}
  ::std_msgs::msg::Int8MultiArray data(::std_msgs::msg::Int8MultiArray::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::std_msgs::msg::Int8MultiArray msg_;
};

class Init_Int8MultiArray_layout
{
public:
  Init_Int8MultiArray_layout()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Int8MultiArray_data layout(::std_msgs::msg::Int8MultiArray::_layout_type arg)
  {
    msg_.layout = std::move(arg);
    return Init_Int8MultiArray_data(msg_);
  }

private:
  ::std_msgs::msg::Int8MultiArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::std_msgs::msg::Int8MultiArray>()
{
  return std_msgs::msg::builder::Init_Int8MultiArray_layout();
}

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__INT8_MULTI_ARRAY__BUILDER_HPP_
