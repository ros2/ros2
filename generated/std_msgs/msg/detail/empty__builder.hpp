// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from std_msgs:msg/Empty.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/empty.hpp"


#ifndef STD_MSGS__MSG__DETAIL__EMPTY__BUILDER_HPP_
#define STD_MSGS__MSG__DETAIL__EMPTY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "std_msgs/msg/detail/empty__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace std_msgs
{

namespace msg
{


}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::std_msgs::msg::Empty>()
{
  return ::std_msgs::msg::Empty(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__EMPTY__BUILDER_HPP_
