// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lifecycle_msgs:msg/State.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/state.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__STATE__STRUCT_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__lifecycle_msgs__msg__State __attribute__((deprecated))
#else
# define DEPRECATED__lifecycle_msgs__msg__State __declspec(deprecated)
#endif

namespace lifecycle_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct State_
{
  using Type = State_<ContainerAllocator>;

  explicit State_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->label = "";
    }
  }

  explicit State_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : label(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->label = "";
    }
  }

  // field types and members
  using _id_type =
    uint8_t;
  _id_type id;
  using _label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _label_type label;

  // setters for named parameter idiom
  Type & set__id(
    const uint8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->label = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t PRIMARY_STATE_UNKNOWN =
    0u;
  static constexpr uint8_t PRIMARY_STATE_UNCONFIGURED =
    1u;
  static constexpr uint8_t PRIMARY_STATE_INACTIVE =
    2u;
  static constexpr uint8_t PRIMARY_STATE_ACTIVE =
    3u;
  static constexpr uint8_t PRIMARY_STATE_FINALIZED =
    4u;
  static constexpr uint8_t TRANSITION_STATE_CONFIGURING =
    10u;
  static constexpr uint8_t TRANSITION_STATE_CLEANINGUP =
    11u;
  static constexpr uint8_t TRANSITION_STATE_SHUTTINGDOWN =
    12u;
  static constexpr uint8_t TRANSITION_STATE_ACTIVATING =
    13u;
  static constexpr uint8_t TRANSITION_STATE_DEACTIVATING =
    14u;
  static constexpr uint8_t TRANSITION_STATE_ERRORPROCESSING =
    15u;

  // pointer types
  using RawPtr =
    lifecycle_msgs::msg::State_<ContainerAllocator> *;
  using ConstRawPtr =
    const lifecycle_msgs::msg::State_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lifecycle_msgs::msg::State_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lifecycle_msgs::msg::State_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lifecycle_msgs::msg::State_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lifecycle_msgs::msg::State_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lifecycle_msgs::msg::State_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lifecycle_msgs::msg::State_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lifecycle_msgs::msg::State_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lifecycle_msgs::msg::State_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lifecycle_msgs__msg__State
    std::shared_ptr<lifecycle_msgs::msg::State_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lifecycle_msgs__msg__State
    std::shared_ptr<lifecycle_msgs::msg::State_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const State_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->label != other.label) {
      return false;
    }
    return true;
  }
  bool operator!=(const State_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct State_

// alias to use template instance with default allocator
using State =
  lifecycle_msgs::msg::State_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::PRIMARY_STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::PRIMARY_STATE_UNCONFIGURED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::PRIMARY_STATE_INACTIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::PRIMARY_STATE_ACTIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::PRIMARY_STATE_FINALIZED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::TRANSITION_STATE_CONFIGURING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::TRANSITION_STATE_CLEANINGUP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::TRANSITION_STATE_SHUTTINGDOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::TRANSITION_STATE_ACTIVATING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::TRANSITION_STATE_DEACTIVATING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t State_<ContainerAllocator>::TRANSITION_STATE_ERRORPROCESSING;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__STATE__STRUCT_HPP_
