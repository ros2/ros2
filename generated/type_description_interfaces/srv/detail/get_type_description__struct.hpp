// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from type_description_interfaces:srv/GetTypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/srv/get_type_description.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__STRUCT_HPP_
#define TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Request __attribute__((deprecated))
#else
# define DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Request __declspec(deprecated)
#endif

namespace type_description_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetTypeDescription_Request_
{
  using Type = GetTypeDescription_Request_<ContainerAllocator>;

  explicit GetTypeDescription_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->include_type_sources = true;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->type_name = "";
      this->type_hash = "";
      this->include_type_sources = false;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type_name = "";
      this->type_hash = "";
    }
  }

  explicit GetTypeDescription_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : type_name(_alloc),
    type_hash(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->include_type_sources = true;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->type_name = "";
      this->type_hash = "";
      this->include_type_sources = false;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type_name = "";
      this->type_hash = "";
    }
  }

  // field types and members
  using _type_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _type_name_type type_name;
  using _type_hash_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _type_hash_type type_hash;
  using _include_type_sources_type =
    bool;
  _include_type_sources_type include_type_sources;

  // setters for named parameter idiom
  Type & set__type_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->type_name = _arg;
    return *this;
  }
  Type & set__type_hash(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->type_hash = _arg;
    return *this;
  }
  Type & set__include_type_sources(
    const bool & _arg)
  {
    this->include_type_sources = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Request
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Request
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetTypeDescription_Request_ & other) const
  {
    if (this->type_name != other.type_name) {
      return false;
    }
    if (this->type_hash != other.type_hash) {
      return false;
    }
    if (this->include_type_sources != other.include_type_sources) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetTypeDescription_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetTypeDescription_Request_

// alias to use template instance with default allocator
using GetTypeDescription_Request =
  type_description_interfaces::srv::GetTypeDescription_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace type_description_interfaces


// Include directives for member types
// Member 'type_description'
#include "type_description_interfaces/msg/detail/type_description__struct.hpp"
// Member 'type_sources'
#include "type_description_interfaces/msg/detail/type_source__struct.hpp"
// Member 'extra_information'
#include "type_description_interfaces/msg/detail/key_value__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Response __attribute__((deprecated))
#else
# define DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Response __declspec(deprecated)
#endif

namespace type_description_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetTypeDescription_Response_
{
  using Type = GetTypeDescription_Response_<ContainerAllocator>;

  explicit GetTypeDescription_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : type_description(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->successful = false;
      this->failure_reason = "";
    }
  }

  explicit GetTypeDescription_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : failure_reason(_alloc),
    type_description(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->successful = false;
      this->failure_reason = "";
    }
  }

  // field types and members
  using _successful_type =
    bool;
  _successful_type successful;
  using _failure_reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _failure_reason_type failure_reason;
  using _type_description_type =
    type_description_interfaces::msg::TypeDescription_<ContainerAllocator>;
  _type_description_type type_description;
  using _type_sources_type =
    std::vector<type_description_interfaces::msg::TypeSource_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::msg::TypeSource_<ContainerAllocator>>>;
  _type_sources_type type_sources;
  using _extra_information_type =
    std::vector<type_description_interfaces::msg::KeyValue_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::msg::KeyValue_<ContainerAllocator>>>;
  _extra_information_type extra_information;

  // setters for named parameter idiom
  Type & set__successful(
    const bool & _arg)
  {
    this->successful = _arg;
    return *this;
  }
  Type & set__failure_reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->failure_reason = _arg;
    return *this;
  }
  Type & set__type_description(
    const type_description_interfaces::msg::TypeDescription_<ContainerAllocator> & _arg)
  {
    this->type_description = _arg;
    return *this;
  }
  Type & set__type_sources(
    const std::vector<type_description_interfaces::msg::TypeSource_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::msg::TypeSource_<ContainerAllocator>>> & _arg)
  {
    this->type_sources = _arg;
    return *this;
  }
  Type & set__extra_information(
    const std::vector<type_description_interfaces::msg::KeyValue_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::msg::KeyValue_<ContainerAllocator>>> & _arg)
  {
    this->extra_information = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Response
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Response
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetTypeDescription_Response_ & other) const
  {
    if (this->successful != other.successful) {
      return false;
    }
    if (this->failure_reason != other.failure_reason) {
      return false;
    }
    if (this->type_description != other.type_description) {
      return false;
    }
    if (this->type_sources != other.type_sources) {
      return false;
    }
    if (this->extra_information != other.extra_information) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetTypeDescription_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetTypeDescription_Response_

// alias to use template instance with default allocator
using GetTypeDescription_Response =
  type_description_interfaces::srv::GetTypeDescription_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace type_description_interfaces


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Event __attribute__((deprecated))
#else
# define DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Event __declspec(deprecated)
#endif

namespace type_description_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetTypeDescription_Event_
{
  using Type = GetTypeDescription_Event_<ContainerAllocator>;

  explicit GetTypeDescription_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit GetTypeDescription_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::srv::GetTypeDescription_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::srv::GetTypeDescription_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Event
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__type_description_interfaces__srv__GetTypeDescription_Event
    std::shared_ptr<type_description_interfaces::srv::GetTypeDescription_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetTypeDescription_Event_ & other) const
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
  bool operator!=(const GetTypeDescription_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetTypeDescription_Event_

// alias to use template instance with default allocator
using GetTypeDescription_Event =
  type_description_interfaces::srv::GetTypeDescription_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace type_description_interfaces

namespace type_description_interfaces
{

namespace srv
{

struct GetTypeDescription
{
  using Request = type_description_interfaces::srv::GetTypeDescription_Request;
  using Response = type_description_interfaces::srv::GetTypeDescription_Response;
  using Event = type_description_interfaces::srv::GetTypeDescription_Event;
};

}  // namespace srv

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__STRUCT_HPP_
