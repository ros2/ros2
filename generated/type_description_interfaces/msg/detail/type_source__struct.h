// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from type_description_interfaces:msg/TypeSource.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/type_source.h"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__STRUCT_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__STRUCT_H_

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
// Member 'encoding'
// Member 'raw_file_contents'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/TypeSource in the package type_description_interfaces.
/**
  * Represents the original source of a ROS 2 interface definition.
 */
typedef struct type_description_interfaces__msg__TypeSource
{
  /// ROS interface type name, in PACKAGE/NAMESPACE/TYPENAME format.
  rosidl_runtime_c__String type_name;
  /// The type of the original source file, typically matching the file extension.
  /// Well-known encodings: "idl", "msg", "srv", "action", "dynamic", "implicit".
  /// "dynamic" specifies a type created programmatically by a user, thus having no source.
  /// "implicit" specifies a type created automatically as a subtype of a
  /// complex type (service or action) - such as the request message for a service.
  /// Implicit types will have no contents, the full source will be available on the parent srv/action.
  rosidl_runtime_c__String encoding;
  /// Dumped contents of the interface definition source file.
  /// If `encoding` is "dynamic" or "implicit", this field will be empty.
  rosidl_runtime_c__String raw_file_contents;
} type_description_interfaces__msg__TypeSource;

// Struct for a sequence of type_description_interfaces__msg__TypeSource.
typedef struct type_description_interfaces__msg__TypeSource__Sequence
{
  type_description_interfaces__msg__TypeSource * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} type_description_interfaces__msg__TypeSource__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__STRUCT_H_
