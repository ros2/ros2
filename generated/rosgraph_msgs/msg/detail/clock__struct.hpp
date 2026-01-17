// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rosgraph_msgs:msg/Clock.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosgraph_msgs/msg/clock.hpp"


#ifndef ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__STRUCT_HPP_
#define ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'clock'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rosgraph_msgs__msg__Clock __attribute__((deprecated))
#else
# define DEPRECATED__rosgraph_msgs__msg__Clock __declspec(deprecated)
#endif

namespace rosgraph_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Clock_
{
  using Type = Clock_<ContainerAllocator>;

  explicit Clock_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : clock(_init)
  {
    (void)_init;
  }

  explicit Clock_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : clock(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _clock_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _clock_type clock;

  // setters for named parameter idiom
  Type & set__clock(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->clock = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rosgraph_msgs::msg::Clock_<ContainerAllocator> *;
  using ConstRawPtr =
    const rosgraph_msgs::msg::Clock_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rosgraph_msgs::msg::Clock_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rosgraph_msgs::msg::Clock_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rosgraph_msgs::msg::Clock_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rosgraph_msgs::msg::Clock_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rosgraph_msgs::msg::Clock_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rosgraph_msgs::msg::Clock_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rosgraph_msgs::msg::Clock_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rosgraph_msgs::msg::Clock_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rosgraph_msgs__msg__Clock
    std::shared_ptr<rosgraph_msgs::msg::Clock_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rosgraph_msgs__msg__Clock
    std::shared_ptr<rosgraph_msgs::msg::Clock_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Clock_ & other) const
  {
    if (this->clock != other.clock) {
      return false;
    }
    return true;
  }
  bool operator!=(const Clock_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Clock_

// alias to use template instance with default allocator
using Clock =
  rosgraph_msgs::msg::Clock_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rosgraph_msgs

#endif  // ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__STRUCT_HPP_
