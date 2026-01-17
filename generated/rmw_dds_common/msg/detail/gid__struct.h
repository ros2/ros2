// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rmw_dds_common:msg/Gid.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/gid.h"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__GID__STRUCT_H_
#define RMW_DDS_COMMON__MSG__DETAIL__GID__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Gid in the package rmw_dds_common.
typedef struct rmw_dds_common__msg__Gid
{
  uint8_t data[16];
} rmw_dds_common__msg__Gid;

// Struct for a sequence of rmw_dds_common__msg__Gid.
typedef struct rmw_dds_common__msg__Gid__Sequence
{
  rmw_dds_common__msg__Gid * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rmw_dds_common__msg__Gid__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RMW_DDS_COMMON__MSG__DETAIL__GID__STRUCT_H_
