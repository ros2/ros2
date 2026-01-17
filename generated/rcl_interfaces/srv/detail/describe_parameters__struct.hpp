// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:srv/DescribeParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/describe_parameters.hpp"


#ifndef RCL_INTERFACES__SRV__DETAIL__DESCRIBE_PARAMETERS__STRUCT_HPP_
#define RCL_INTERFACES__SRV__DETAIL__DESCRIBE_PARAMETERS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__srv__DescribeParameters_Request __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__srv__DescribeParameters_Request __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DescribeParameters_Request_
{
  using Type = DescribeParameters_Request_<ContainerAllocator>;

  explicit DescribeParameters_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit DescribeParameters_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _names_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _names_type names;

  // setters for named parameter idiom
  Type & set__names(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->names = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__srv__DescribeParameters_Request
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__srv__DescribeParameters_Request
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DescribeParameters_Request_ & other) const
  {
    if (this->names != other.names) {
      return false;
    }
    return true;
  }
  bool operator!=(const DescribeParameters_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DescribeParameters_Request_

// alias to use template instance with default allocator
using DescribeParameters_Request =
  rcl_interfaces::srv::DescribeParameters_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rcl_interfaces


// Include directives for member types
// Member 'descriptors'
#include "rcl_interfaces/msg/detail/parameter_descriptor__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__srv__DescribeParameters_Response __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__srv__DescribeParameters_Response __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DescribeParameters_Response_
{
  using Type = DescribeParameters_Response_<ContainerAllocator>;

  explicit DescribeParameters_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit DescribeParameters_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _descriptors_type =
    std::vector<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>>;
  _descriptors_type descriptors;

  // setters for named parameter idiom
  Type & set__descriptors(
    const std::vector<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>> & _arg)
  {
    this->descriptors = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__srv__DescribeParameters_Response
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__srv__DescribeParameters_Response
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DescribeParameters_Response_ & other) const
  {
    if (this->descriptors != other.descriptors) {
      return false;
    }
    return true;
  }
  bool operator!=(const DescribeParameters_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DescribeParameters_Response_

// alias to use template instance with default allocator
using DescribeParameters_Response =
  rcl_interfaces::srv::DescribeParameters_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rcl_interfaces


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__srv__DescribeParameters_Event __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__srv__DescribeParameters_Event __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DescribeParameters_Event_
{
  using Type = DescribeParameters_Event_<ContainerAllocator>;

  explicit DescribeParameters_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit DescribeParameters_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::srv::DescribeParameters_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::srv::DescribeParameters_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__srv__DescribeParameters_Event
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__srv__DescribeParameters_Event
    std::shared_ptr<rcl_interfaces::srv::DescribeParameters_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DescribeParameters_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const DescribeParameters_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DescribeParameters_Event_

// alias to use template instance with default allocator
using DescribeParameters_Event =
  rcl_interfaces::srv::DescribeParameters_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rcl_interfaces

namespace rcl_interfaces
{

namespace srv
{

struct DescribeParameters
{
  using Request = rcl_interfaces::srv::DescribeParameters_Request;
  using Response = rcl_interfaces::srv::DescribeParameters_Response;
  using Event = rcl_interfaces::srv::DescribeParameters_Event;
};

}  // namespace srv

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__SRV__DETAIL__DESCRIBE_PARAMETERS__STRUCT_HPP_
