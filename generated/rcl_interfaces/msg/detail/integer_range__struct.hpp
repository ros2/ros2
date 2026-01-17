// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:msg/IntegerRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/integer_range.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__STRUCT_HPP_
#define RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__msg__IntegerRange __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__msg__IntegerRange __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct IntegerRange_
{
  using Type = IntegerRange_<ContainerAllocator>;

  explicit IntegerRange_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->from_value = 0ll;
      this->to_value = 0ll;
      this->step = 0ull;
    }
  }

  explicit IntegerRange_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->from_value = 0ll;
      this->to_value = 0ll;
      this->step = 0ull;
    }
  }

  // field types and members
  using _from_value_type =
    int64_t;
  _from_value_type from_value;
  using _to_value_type =
    int64_t;
  _to_value_type to_value;
  using _step_type =
    uint64_t;
  _step_type step;

  // setters for named parameter idiom
  Type & set__from_value(
    const int64_t & _arg)
  {
    this->from_value = _arg;
    return *this;
  }
  Type & set__to_value(
    const int64_t & _arg)
  {
    this->to_value = _arg;
    return *this;
  }
  Type & set__step(
    const uint64_t & _arg)
  {
    this->step = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::msg::IntegerRange_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::msg::IntegerRange_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::msg::IntegerRange_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::msg::IntegerRange_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::IntegerRange_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::IntegerRange_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::IntegerRange_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::IntegerRange_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::msg::IntegerRange_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::msg::IntegerRange_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__msg__IntegerRange
    std::shared_ptr<rcl_interfaces::msg::IntegerRange_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__msg__IntegerRange
    std::shared_ptr<rcl_interfaces::msg::IntegerRange_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const IntegerRange_ & other) const
  {
    if (this->from_value != other.from_value) {
      return false;
    }
    if (this->to_value != other.to_value) {
      return false;
    }
    if (this->step != other.step) {
      return false;
    }
    return true;
  }
  bool operator!=(const IntegerRange_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct IntegerRange_

// alias to use template instance with default allocator
using IntegerRange =
  rcl_interfaces::msg::IntegerRange_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__STRUCT_HPP_
