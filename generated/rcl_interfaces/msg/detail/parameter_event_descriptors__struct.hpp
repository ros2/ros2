// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:msg/ParameterEventDescriptors.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_event_descriptors.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__STRUCT_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'new_parameters'
// Member 'changed_parameters'
// Member 'deleted_parameters'
#include "rcl_interfaces/msg/detail/parameter_descriptor__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__msg__ParameterEventDescriptors __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__msg__ParameterEventDescriptors __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ParameterEventDescriptors_
{
  using Type = ParameterEventDescriptors_<ContainerAllocator>;

  explicit ParameterEventDescriptors_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit ParameterEventDescriptors_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _new_parameters_type =
    std::vector<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>>;
  _new_parameters_type new_parameters;
  using _changed_parameters_type =
    std::vector<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>>;
  _changed_parameters_type changed_parameters;
  using _deleted_parameters_type =
    std::vector<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>>;
  _deleted_parameters_type deleted_parameters;

  // setters for named parameter idiom
  Type & set__new_parameters(
    const std::vector<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>> & _arg)
  {
    this->new_parameters = _arg;
    return *this;
  }
  Type & set__changed_parameters(
    const std::vector<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>> & _arg)
  {
    this->changed_parameters = _arg;
    return *this;
  }
  Type & set__deleted_parameters(
    const std::vector<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>> & _arg)
  {
    this->deleted_parameters = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__msg__ParameterEventDescriptors
    std::shared_ptr<rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__msg__ParameterEventDescriptors
    std::shared_ptr<rcl_interfaces::msg::ParameterEventDescriptors_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ParameterEventDescriptors_ & other) const
  {
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
  bool operator!=(const ParameterEventDescriptors_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ParameterEventDescriptors_

// alias to use template instance with default allocator
using ParameterEventDescriptors =
  rcl_interfaces::msg::ParameterEventDescriptors_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__STRUCT_HPP_
