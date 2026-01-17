// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from type_description_interfaces:msg/IndividualTypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/individual_type_description.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__INDIVIDUAL_TYPE_DESCRIPTION__BUILDER_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__INDIVIDUAL_TYPE_DESCRIPTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "type_description_interfaces/msg/detail/individual_type_description__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace type_description_interfaces
{

namespace msg
{

namespace builder
{

class Init_IndividualTypeDescription_fields
{
public:
  explicit Init_IndividualTypeDescription_fields(::type_description_interfaces::msg::IndividualTypeDescription & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::msg::IndividualTypeDescription fields(::type_description_interfaces::msg::IndividualTypeDescription::_fields_type arg)
  {
    msg_.fields = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::msg::IndividualTypeDescription msg_;
};

class Init_IndividualTypeDescription_type_name
{
public:
  Init_IndividualTypeDescription_type_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IndividualTypeDescription_fields type_name(::type_description_interfaces::msg::IndividualTypeDescription::_type_name_type arg)
  {
    msg_.type_name = std::move(arg);
    return Init_IndividualTypeDescription_fields(msg_);
  }

private:
  ::type_description_interfaces::msg::IndividualTypeDescription msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::msg::IndividualTypeDescription>()
{
  return type_description_interfaces::msg::builder::Init_IndividualTypeDescription_type_name();
}

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__INDIVIDUAL_TYPE_DESCRIPTION__BUILDER_HPP_
