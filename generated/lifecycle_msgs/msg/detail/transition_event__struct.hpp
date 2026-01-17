// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lifecycle_msgs:msg/TransitionEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition_event.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__STRUCT_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'transition'
#include "lifecycle_msgs/msg/detail/transition__struct.hpp"
// Member 'start_state'
// Member 'goal_state'
#include "lifecycle_msgs/msg/detail/state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__lifecycle_msgs__msg__TransitionEvent __attribute__((deprecated))
#else
# define DEPRECATED__lifecycle_msgs__msg__TransitionEvent __declspec(deprecated)
#endif

namespace lifecycle_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TransitionEvent_
{
  using Type = TransitionEvent_<ContainerAllocator>;

  explicit TransitionEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : transition(_init),
    start_state(_init),
    goal_state(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
    }
  }

  explicit TransitionEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : transition(_alloc, _init),
    start_state(_alloc, _init),
    goal_state(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _transition_type =
    lifecycle_msgs::msg::Transition_<ContainerAllocator>;
  _transition_type transition;
  using _start_state_type =
    lifecycle_msgs::msg::State_<ContainerAllocator>;
  _start_state_type start_state;
  using _goal_state_type =
    lifecycle_msgs::msg::State_<ContainerAllocator>;
  _goal_state_type goal_state;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__transition(
    const lifecycle_msgs::msg::Transition_<ContainerAllocator> & _arg)
  {
    this->transition = _arg;
    return *this;
  }
  Type & set__start_state(
    const lifecycle_msgs::msg::State_<ContainerAllocator> & _arg)
  {
    this->start_state = _arg;
    return *this;
  }
  Type & set__goal_state(
    const lifecycle_msgs::msg::State_<ContainerAllocator> & _arg)
  {
    this->goal_state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lifecycle_msgs__msg__TransitionEvent
    std::shared_ptr<lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lifecycle_msgs__msg__TransitionEvent
    std::shared_ptr<lifecycle_msgs::msg::TransitionEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransitionEvent_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->transition != other.transition) {
      return false;
    }
    if (this->start_state != other.start_state) {
      return false;
    }
    if (this->goal_state != other.goal_state) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransitionEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransitionEvent_

// alias to use template instance with default allocator
using TransitionEvent =
  lifecycle_msgs::msg::TransitionEvent_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__STRUCT_HPP_
