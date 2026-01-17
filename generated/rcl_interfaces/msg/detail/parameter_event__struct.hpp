// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:msg/ParameterEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_event.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__STRUCT_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'new_parameters'
// Member 'changed_parameters'
// Member 'deleted_parameters'
#include "rcl_interfaces/msg/detail/parameter__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__msg__ParameterEvent __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__msg__ParameterEvent __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ParameterEvent_
{
  using Type = ParameterEvent_<ContainerAllocator>;

  explicit ParameterEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->node = "";
    }
  }

  explicit ParameterEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    node(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->node = "";
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _node_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _node_type node;
  using _new_parameters_type =
    std::vector<rcl_interfaces::msg::Parameter_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::Parameter_<ContainerAllocator>>>;
  _new_parameters_type new_parameters;
  using _changed_parameters_type =
    std::vector<rcl_interfaces::msg::Parameter_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::Parameter_<ContainerAllocator>>>;
  _changed_parameters_type changed_parameters;
  using _deleted_parameters_type =
    std::vector<rcl_interfaces::msg::Parameter_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::Parameter_<ContainerAllocator>>>;
  _deleted_parameters_type deleted_parameters;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__node(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->node = _arg;
    return *this;
  }
  Type & set__new_parameters(
    const std::vector<rcl_interfaces::msg::Parameter_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::Parameter_<ContainerAllocator>>> & _arg)
  {
    this->new_parameters = _arg;
    return *this;
  }
  Type & set__changed_parameters(
    const std::vector<rcl_interfaces::msg::Parameter_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::Parameter_<ContainerAllocator>>> & _arg)
  {
    this->changed_parameters = _arg;
    return *this;
  }
  Type & set__deleted_parameters(
    const std::vector<rcl_interfaces::msg::Parameter_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::Parameter_<ContainerAllocator>>> & _arg)
  {
    this->deleted_parameters = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::msg::ParameterEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::msg::ParameterEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__msg__ParameterEvent
    std::shared_ptr<rcl_interfaces::msg::ParameterEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__msg__ParameterEvent
    std::shared_ptr<rcl_interfaces::msg::ParameterEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ParameterEvent_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->node != other.node) {
      return false;
    }
    if (this->new_parameters != other.new_parameters) {
      return false;
    }
    if (this->changed_parameters != other.changed_parameters) {
      return false;
    }
    if (this->deleted_parameters != other.deleted_parameters) {
      return false;
    }
    return true;
  }
  bool operator!=(const ParameterEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ParameterEvent_

// alias to use template instance with default allocator
using ParameterEvent =
  rcl_interfaces::msg::ParameterEvent_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__STRUCT_HPP_
