// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:msg/LoggerLevel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/logger_level.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__STRUCT_HPP_
#define RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__msg__LoggerLevel __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__msg__LoggerLevel __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LoggerLevel_
{
  using Type = LoggerLevel_<ContainerAllocator>;

  explicit LoggerLevel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->level = 0ul;
    }
  }

  explicit LoggerLevel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->level = 0ul;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _level_type =
    uint32_t;
  _level_type level;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__level(
    const uint32_t & _arg)
  {
    this->level = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t LOG_LEVEL_UNKNOWN =
    0u;
  static constexpr uint8_t LOG_LEVEL_DEBUG =
    10u;
  static constexpr uint8_t LOG_LEVEL_INFO =
    20u;
  static constexpr uint8_t LOG_LEVEL_WARN =
    30u;
  static constexpr uint8_t LOG_LEVEL_ERROR =
    40u;
  static constexpr uint8_t LOG_LEVEL_FATAL =
    50u;

  // pointer types
  using RawPtr =
    rcl_interfaces::msg::LoggerLevel_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::msg::LoggerLevel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::msg::LoggerLevel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::msg::LoggerLevel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::LoggerLevel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::LoggerLevel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::LoggerLevel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::LoggerLevel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::msg::LoggerLevel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::msg::LoggerLevel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__msg__LoggerLevel
    std::shared_ptr<rcl_interfaces::msg::LoggerLevel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__msg__LoggerLevel
    std::shared_ptr<rcl_interfaces::msg::LoggerLevel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LoggerLevel_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->level != other.level) {
      return false;
    }
    return true;
  }
  bool operator!=(const LoggerLevel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LoggerLevel_

// alias to use template instance with default allocator
using LoggerLevel =
  rcl_interfaces::msg::LoggerLevel_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LoggerLevel_<ContainerAllocator>::LOG_LEVEL_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LoggerLevel_<ContainerAllocator>::LOG_LEVEL_DEBUG;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LoggerLevel_<ContainerAllocator>::LOG_LEVEL_INFO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LoggerLevel_<ContainerAllocator>::LOG_LEVEL_WARN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LoggerLevel_<ContainerAllocator>::LOG_LEVEL_ERROR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LoggerLevel_<ContainerAllocator>::LOG_LEVEL_FATAL;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__STRUCT_HPP_
