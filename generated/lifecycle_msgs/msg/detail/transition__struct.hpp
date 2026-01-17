// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lifecycle_msgs:msg/Transition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION__STRUCT_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__lifecycle_msgs__msg__Transition __attribute__((deprecated))
#else
# define DEPRECATED__lifecycle_msgs__msg__Transition __declspec(deprecated)
#endif

namespace lifecycle_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Transition_
{
  using Type = Transition_<ContainerAllocator>;

  explicit Transition_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->label = "";
    }
  }

  explicit Transition_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
  static constexpr uint8_t TRANSITION_CREATE =
    0u;
  static constexpr uint8_t TRANSITION_CONFIGURE =
    1u;
  static constexpr uint8_t TRANSITION_CLEANUP =
    2u;
  static constexpr uint8_t TRANSITION_ACTIVATE =
    3u;
  static constexpr uint8_t TRANSITION_DEACTIVATE =
    4u;
  static constexpr uint8_t TRANSITION_UNCONFIGURED_SHUTDOWN =
    5u;
  static constexpr uint8_t TRANSITION_INACTIVE_SHUTDOWN =
    6u;
  static constexpr uint8_t TRANSITION_ACTIVE_SHUTDOWN =
    7u;
  static constexpr uint8_t TRANSITION_DESTROY =
    8u;
  static constexpr uint8_t TRANSITION_ON_CONFIGURE_SUCCESS =
    10u;
  static constexpr uint8_t TRANSITION_ON_CONFIGURE_FAILURE =
    11u;
  static constexpr uint8_t TRANSITION_ON_CONFIGURE_ERROR =
    12u;
  static constexpr uint8_t TRANSITION_ON_CLEANUP_SUCCESS =
    20u;
  static constexpr uint8_t TRANSITION_ON_CLEANUP_FAILURE =
    21u;
  static constexpr uint8_t TRANSITION_ON_CLEANUP_ERROR =
    22u;
  static constexpr uint8_t TRANSITION_ON_ACTIVATE_SUCCESS =
    30u;
  static constexpr uint8_t TRANSITION_ON_ACTIVATE_FAILURE =
    31u;
  static constexpr uint8_t TRANSITION_ON_ACTIVATE_ERROR =
    32u;
  static constexpr uint8_t TRANSITION_ON_DEACTIVATE_SUCCESS =
    40u;
  static constexpr uint8_t TRANSITION_ON_DEACTIVATE_FAILURE =
    41u;
  static constexpr uint8_t TRANSITION_ON_DEACTIVATE_ERROR =
    42u;
  static constexpr uint8_t TRANSITION_ON_SHUTDOWN_SUCCESS =
    50u;
  static constexpr uint8_t TRANSITION_ON_SHUTDOWN_FAILURE =
    51u;
  static constexpr uint8_t TRANSITION_ON_SHUTDOWN_ERROR =
    52u;
  static constexpr uint8_t TRANSITION_ON_ERROR_SUCCESS =
    60u;
  static constexpr uint8_t TRANSITION_ON_ERROR_FAILURE =
    61u;
  static constexpr uint8_t TRANSITION_ON_ERROR_ERROR =
    62u;
  static constexpr uint8_t TRANSITION_CALLBACK_SUCCESS =
    97u;
  static constexpr uint8_t TRANSITION_CALLBACK_FAILURE =
    98u;
  static constexpr uint8_t TRANSITION_CALLBACK_ERROR =
    99u;

  // pointer types
  using RawPtr =
    lifecycle_msgs::msg::Transition_<ContainerAllocator> *;
  using ConstRawPtr =
    const lifecycle_msgs::msg::Transition_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lifecycle_msgs::msg::Transition_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lifecycle_msgs::msg::Transition_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lifecycle_msgs::msg::Transition_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lifecycle_msgs::msg::Transition_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lifecycle_msgs::msg::Transition_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lifecycle_msgs::msg::Transition_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lifecycle_msgs::msg::Transition_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lifecycle_msgs::msg::Transition_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lifecycle_msgs__msg__Transition
    std::shared_ptr<lifecycle_msgs::msg::Transition_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lifecycle_msgs__msg__Transition
    std::shared_ptr<lifecycle_msgs::msg::Transition_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Transition_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->label != other.label) {
      return false;
    }
    return true;
  }
  bool operator!=(const Transition_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Transition_

// alias to use template instance with default allocator
using Transition =
  lifecycle_msgs::msg::Transition_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_CREATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_CONFIGURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_CLEANUP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ACTIVATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_DEACTIVATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_UNCONFIGURED_SHUTDOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_INACTIVE_SHUTDOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ACTIVE_SHUTDOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_DESTROY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_CONFIGURE_SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_CONFIGURE_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_CONFIGURE_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_CLEANUP_SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_CLEANUP_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_CLEANUP_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_ACTIVATE_SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_ACTIVATE_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_ACTIVATE_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_DEACTIVATE_SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_DEACTIVATE_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_DEACTIVATE_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_SHUTDOWN_SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_SHUTDOWN_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_SHUTDOWN_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_ERROR_SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_ERROR_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_ON_ERROR_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_CALLBACK_SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_CALLBACK_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Transition_<ContainerAllocator>::TRANSITION_CALLBACK_ERROR;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION__STRUCT_HPP_
