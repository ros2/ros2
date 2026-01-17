// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from service_msgs:msg/ServiceEventInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "service_msgs/msg/service_event_info.hpp"


#ifndef SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__STRUCT_HPP_
#define SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__service_msgs__msg__ServiceEventInfo __attribute__((deprecated))
#else
# define DEPRECATED__service_msgs__msg__ServiceEventInfo __declspec(deprecated)
#endif

namespace service_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServiceEventInfo_
{
  using Type = ServiceEventInfo_<ContainerAllocator>;

  explicit ServiceEventInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->event_type = 0;
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->client_gid.begin(), this->client_gid.end(), 0);
      this->sequence_number = 0ll;
    }
  }

  explicit ServiceEventInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    client_gid(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->event_type = 0;
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->client_gid.begin(), this->client_gid.end(), 0);
      this->sequence_number = 0ll;
    }
  }

  // field types and members
  using _event_type_type =
    uint8_t;
  _event_type_type event_type;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _client_gid_type =
    std::array<uint8_t, 16>;
  _client_gid_type client_gid;
  using _sequence_number_type =
    int64_t;
  _sequence_number_type sequence_number;

  // setters for named parameter idiom
  Type & set__event_type(
    const uint8_t & _arg)
  {
    this->event_type = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__client_gid(
    const std::array<uint8_t, 16> & _arg)
  {
    this->client_gid = _arg;
    return *this;
  }
  Type & set__sequence_number(
    const int64_t & _arg)
  {
    this->sequence_number = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t REQUEST_SENT =
    0u;
  static constexpr uint8_t REQUEST_RECEIVED =
    1u;
  static constexpr uint8_t RESPONSE_SENT =
    2u;
  static constexpr uint8_t RESPONSE_RECEIVED =
    3u;

  // pointer types
  using RawPtr =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<service_msgs::msg::ServiceEventInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<service_msgs::msg::ServiceEventInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      service_msgs::msg::ServiceEventInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<service_msgs::msg::ServiceEventInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      service_msgs::msg::ServiceEventInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<service_msgs::msg::ServiceEventInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<service_msgs::msg::ServiceEventInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<service_msgs::msg::ServiceEventInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__service_msgs__msg__ServiceEventInfo
    std::shared_ptr<service_msgs::msg::ServiceEventInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__service_msgs__msg__ServiceEventInfo
    std::shared_ptr<service_msgs::msg::ServiceEventInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServiceEventInfo_ & other) const
  {
    if (this->event_type != other.event_type) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->client_gid != other.client_gid) {
      return false;
    }
    if (this->sequence_number != other.sequence_number) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServiceEventInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServiceEventInfo_

// alias to use template instance with default allocator
using ServiceEventInfo =
  service_msgs::msg::ServiceEventInfo_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ServiceEventInfo_<ContainerAllocator>::REQUEST_SENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ServiceEventInfo_<ContainerAllocator>::REQUEST_RECEIVED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ServiceEventInfo_<ContainerAllocator>::RESPONSE_SENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ServiceEventInfo_<ContainerAllocator>::RESPONSE_RECEIVED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace service_msgs

#endif  // SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__STRUCT_HPP_
