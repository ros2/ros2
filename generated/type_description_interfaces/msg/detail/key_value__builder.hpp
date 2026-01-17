// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from type_description_interfaces:msg/KeyValue.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/key_value.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__BUILDER_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "type_description_interfaces/msg/detail/key_value__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace type_description_interfaces
{

namespace msg
{

namespace builder
{

class Init_KeyValue_value
{
public:
  explicit Init_KeyValue_value(::type_description_interfaces::msg::KeyValue & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::msg::KeyValue value(::type_description_interfaces::msg::KeyValue::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::msg::KeyValue msg_;
};

class Init_KeyValue_key
{
public:
  Init_KeyValue_key()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_KeyValue_value key(::type_description_interfaces::msg::KeyValue::_key_type arg)
  {
    msg_.key = std::move(arg);
    return Init_KeyValue_value(msg_);
  }

private:
  ::type_description_interfaces::msg::KeyValue msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::msg::KeyValue>()
{
  return type_description_interfaces::msg::builder::Init_KeyValue_key();
}

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__BUILDER_HPP_
