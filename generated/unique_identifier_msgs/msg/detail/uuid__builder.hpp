// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from unique_identifier_msgs:msg/UUID.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unique_identifier_msgs/msg/uuid.hpp"


#ifndef UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__BUILDER_HPP_
#define UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace unique_identifier_msgs
{

namespace msg
{

namespace builder
{

class Init_UUID_uuid
{
public:
  Init_UUID_uuid()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::unique_identifier_msgs::msg::UUID uuid(::unique_identifier_msgs::msg::UUID::_uuid_type arg)
  {
    msg_.uuid = std::move(arg);
    return std::move(msg_);
  }

private:
  ::unique_identifier_msgs::msg::UUID msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::unique_identifier_msgs::msg::UUID>()
{
  return unique_identifier_msgs::msg::builder::Init_UUID_uuid();
}

}  // namespace unique_identifier_msgs

#endif  // UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__BUILDER_HPP_
