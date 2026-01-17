// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from type_description_interfaces:srv/GetTypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/srv/get_type_description.h"


#ifndef TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__STRUCT_H_
#define TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'type_name'
// Member 'type_hash'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetTypeDescription in the package type_description_interfaces.
typedef struct type_description_interfaces__srv__GetTypeDescription_Request
{
  rosidl_runtime_c__String type_name;
  /// REP-2011 RIHS hash string.
  rosidl_runtime_c__String type_hash;
  /// Whether to return the original idl/msg/etc. source file(s) in the response.
  bool include_type_sources;
} type_description_interfaces__srv__GetTypeDescription_Request;

// Struct for a sequence of type_description_interfaces__srv__GetTypeDescription_Request.
typedef struct type_description_interfaces__srv__GetTypeDescription_Request__Sequence
{
  type_description_interfaces__srv__GetTypeDescription_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} type_description_interfaces__srv__GetTypeDescription_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'failure_reason'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'type_description'
#include "type_description_interfaces/msg/detail/type_description__struct.h"
// Member 'type_sources'
#include "type_description_interfaces/msg/detail/type_source__struct.h"
// Member 'extra_information'
#include "type_description_interfaces/msg/detail/key_value__struct.h"

/// Struct defined in srv/GetTypeDescription in the package type_description_interfaces.
typedef struct type_description_interfaces__srv__GetTypeDescription_Response
{
  bool successful;
  /// If `successful` is false, contains a reason for failure.
  /// If `successful` is true, this is left empty.
  rosidl_runtime_c__String failure_reason;
  /// The parsed type description which can be used programmatically.
  type_description_interfaces__msg__TypeDescription type_description;
  /// A list containing the interface definition source text of the requested type,
  /// plus all types it recursively depends on.
  /// Each source text is a copy of the original contents of the
  /// .msg, .srv, .action, .idl, or other file if it exists, including comments and whitespace.
  /// Sources can be matched with IndividualTypeDescriptions by their `type_name`.
  /// The `encoding` field of each entry informs how to interpret its contents.
  type_description_interfaces__msg__TypeSource__Sequence type_sources;
  /// Key-value pairs of extra information.
  type_description_interfaces__msg__KeyValue__Sequence extra_information;
} type_description_interfaces__srv__GetTypeDescription_Response;

// Struct for a sequence of type_description_interfaces__srv__GetTypeDescription_Response.
typedef struct type_description_interfaces__srv__GetTypeDescription_Response__Sequence
{
  type_description_interfaces__srv__GetTypeDescription_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} type_description_interfaces__srv__GetTypeDescription_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  type_description_interfaces__srv__GetTypeDescription_Event__request__MAX_SIZE = 1
};
// response
enum
{
  type_description_interfaces__srv__GetTypeDescription_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/GetTypeDescription in the package type_description_interfaces.
typedef struct type_description_interfaces__srv__GetTypeDescription_Event
{
  service_msgs__msg__ServiceEventInfo info;
  type_description_interfaces__srv__GetTypeDescription_Request__Sequence request;
  type_description_interfaces__srv__GetTypeDescription_Response__Sequence response;
} type_description_interfaces__srv__GetTypeDescription_Event;

// Struct for a sequence of type_description_interfaces__srv__GetTypeDescription_Event.
typedef struct type_description_interfaces__srv__GetTypeDescription_Event__Sequence
{
  type_description_interfaces__srv__GetTypeDescription_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} type_description_interfaces__srv__GetTypeDescription_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__STRUCT_H_
