// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from std_msgs:msg/ByteMultiArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/byte_multi_array.hpp"


#ifndef STD_MSGS__MSG__DETAIL__BYTE_MULTI_ARRAY__BUILDER_HPP_
#define STD_MSGS__MSG__DETAIL__BYTE_MULTI_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "std_msgs/msg/detail/byte_multi_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace std_msgs
{

namespace msg
{

namespace builder
{

class Init_ByteMultiArray_data
{
public:
  explicit Init_ByteMultiArray_data(::std_msgs::msg::ByteMultiArray & msg)
  : msg_(msg)
  {}
  ::std_msgs::msg::ByteMultiArray data(::std_msgs::msg::ByteMultiArray::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::std_msgs::msg::ByteMultiArray msg_;
};

class Init_ByteMultiArray_layout
{
public:
  Init_ByteMultiArray_layout()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ByteMultiArray_data layout(::std_msgs::msg::ByteMultiArray::_layout_type arg)
  {
    msg_.layout = std::move(arg);
    return Init_ByteMultiArray_data(msg_);
  }

private:
  ::std_msgs::msg::ByteMultiArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::std_msgs::msg::ByteMultiArray>()
{
  return std_msgs::msg::builder::Init_ByteMultiArray_layout();
}

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__BYTE_MULTI_ARRAY__BUILDER_HPP_
