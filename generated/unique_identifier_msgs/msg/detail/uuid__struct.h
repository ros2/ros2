// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from unique_identifier_msgs:msg/UUID.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unique_identifier_msgs/msg/uuid.h"


#ifndef UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__STRUCT_H_
#define UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/UUID in the package unique_identifier_msgs.
/**
  * A universally unique identifier (UUID).
  *
  *  http://en.wikipedia.org/wiki/Universally_unique_identifier
  *  http://tools.ietf.org/html/rfc4122.html
 */
typedef struct unique_identifier_msgs__msg__UUID
{
  uint8_t uuid[16];
} unique_identifier_msgs__msg__UUID;

// Struct for a sequence of unique_identifier_msgs__msg__UUID.
typedef struct unique_identifier_msgs__msg__UUID__Sequence
{
  unique_identifier_msgs__msg__UUID * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} unique_identifier_msgs__msg__UUID__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__STRUCT_H_
