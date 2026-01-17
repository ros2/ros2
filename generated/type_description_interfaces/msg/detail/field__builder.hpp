// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from type_description_interfaces:msg/Field.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/field.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__BUILDER_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "type_description_interfaces/msg/detail/field__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace type_description_interfaces
{

namespace msg
{

namespace builder
{

class Init_Field_default_value
{
public:
  explicit Init_Field_default_value(::type_description_interfaces::msg::Field & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::msg::Field default_value(::type_description_interfaces::msg::Field::_default_value_type arg)
  {
    msg_.default_value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::msg::Field msg_;
};

class Init_Field_type
{
public:
  explicit Init_Field_type(::type_description_interfaces::msg::Field & msg)
  : msg_(msg)
  {}
  Init_Field_default_value type(::type_description_interfaces::msg::Field::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_Field_default_value(msg_);
  }

private:
  ::type_description_interfaces::msg::Field msg_;
};

class Init_Field_name
{
public:
  Init_Field_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Field_type name(::type_description_interfaces::msg::Field::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Field_type(msg_);
  }

private:
  ::type_description_interfaces::msg::Field msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::msg::Field>()
{
  return type_description_interfaces::msg::builder::Init_Field_name();
}

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__BUILDER_HPP_
