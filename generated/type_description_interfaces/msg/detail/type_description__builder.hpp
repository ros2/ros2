// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from type_description_interfaces:msg/TypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/type_description.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__BUILDER_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "type_description_interfaces/msg/detail/type_description__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace type_description_interfaces
{

namespace msg
{

namespace builder
{

class Init_TypeDescription_referenced_type_descriptions
{
public:
  explicit Init_TypeDescription_referenced_type_descriptions(::type_description_interfaces::msg::TypeDescription & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::msg::TypeDescription referenced_type_descriptions(::type_description_interfaces::msg::TypeDescription::_referenced_type_descriptions_type arg)
  {
    msg_.referenced_type_descriptions = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::msg::TypeDescription msg_;
};

class Init_TypeDescription_type_description
{
public:
  Init_TypeDescription_type_description()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TypeDescription_referenced_type_descriptions type_description(::type_description_interfaces::msg::TypeDescription::_type_description_type arg)
  {
    msg_.type_description = std::move(arg);
    return Init_TypeDescription_referenced_type_descriptions(msg_);
  }

private:
  ::type_description_interfaces::msg::TypeDescription msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::msg::TypeDescription>()
{
  return type_description_interfaces::msg::builder::Init_TypeDescription_type_description();
}

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__BUILDER_HPP_
