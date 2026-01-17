// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from rmw_dds_common:msg/Gid.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/gid.h"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__GID__FUNCTIONS_H_
#define RMW_DDS_COMMON__MSG__DETAIL__GID__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rmw_dds_common/msg/rosidl_generator_c__visibility_control.h"

#include "rmw_dds_common/msg/detail/gid__struct.h"

/// Initialize msg/Gid message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * rmw_dds_common__msg__Gid
 * )) before or use
 * rmw_dds_common__msg__Gid__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__Gid__init(rmw_dds_common__msg__Gid * msg);

/// Finalize msg/Gid message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
void
rmw_dds_common__msg__Gid__fini(rmw_dds_common__msg__Gid * msg);

/// Create msg/Gid message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * rmw_dds_common__msg__Gid__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
rmw_dds_common__msg__Gid *
rmw_dds_common__msg__Gid__create(void);

/// Destroy msg/Gid message.
/**
 * It calls
 * rmw_dds_common__msg__Gid__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
void
rmw_dds_common__msg__Gid__destroy(rmw_dds_common__msg__Gid * msg);

/// Check for msg/Gid message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__Gid__are_equal(const rmw_dds_common__msg__Gid * lhs, const rmw_dds_common__msg__Gid * rhs);

/// Copy a msg/Gid message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__Gid__copy(
  const rmw_dds_common__msg__Gid * input,
  rmw_dds_common__msg__Gid * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
const rosidl_type_hash_t *
rmw_dds_common__msg__Gid__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
const rosidl_runtime_c__type_description__TypeDescription *
rmw_dds_common__msg__Gid__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
const rosidl_runtime_c__type_description__TypeSource *
rmw_dds_common__msg__Gid__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
const rosidl_runtime_c__type_description__TypeSource__Sequence *
rmw_dds_common__msg__Gid__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/Gid messages.
/**
 * It allocates the memory for the number of elements and calls
 * rmw_dds_common__msg__Gid__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__Gid__Sequence__init(rmw_dds_common__msg__Gid__Sequence * array, size_t size);

/// Finalize array of msg/Gid messages.
/**
 * It calls
 * rmw_dds_common__msg__Gid__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
void
rmw_dds_common__msg__Gid__Sequence__fini(rmw_dds_common__msg__Gid__Sequence * array);

/// Create array of msg/Gid messages.
/**
 * It allocates the memory for the array and calls
 * rmw_dds_common__msg__Gid__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
rmw_dds_common__msg__Gid__Sequence *
rmw_dds_common__msg__Gid__Sequence__create(size_t size);

/// Destroy array of msg/Gid messages.
/**
 * It calls
 * rmw_dds_common__msg__Gid__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
void
rmw_dds_common__msg__Gid__Sequence__destroy(rmw_dds_common__msg__Gid__Sequence * array);

/// Check for msg/Gid message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__Gid__Sequence__are_equal(const rmw_dds_common__msg__Gid__Sequence * lhs, const rmw_dds_common__msg__Gid__Sequence * rhs);

/// Copy an array of msg/Gid messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__Gid__Sequence__copy(
  const rmw_dds_common__msg__Gid__Sequence * input,
  rmw_dds_common__msg__Gid__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // RMW_DDS_COMMON__MSG__DETAIL__GID__FUNCTIONS_H_
