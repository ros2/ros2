// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from rmw_dds_common:msg/ParticipantEntitiesInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/participant_entities_info.h"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__FUNCTIONS_H_
#define RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__FUNCTIONS_H_

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

#include "rmw_dds_common/msg/detail/participant_entities_info__struct.h"

/// Initialize msg/ParticipantEntitiesInfo message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * rmw_dds_common__msg__ParticipantEntitiesInfo
 * )) before or use
 * rmw_dds_common__msg__ParticipantEntitiesInfo__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__ParticipantEntitiesInfo__init(rmw_dds_common__msg__ParticipantEntitiesInfo * msg);

/// Finalize msg/ParticipantEntitiesInfo message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
void
rmw_dds_common__msg__ParticipantEntitiesInfo__fini(rmw_dds_common__msg__ParticipantEntitiesInfo * msg);

/// Create msg/ParticipantEntitiesInfo message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * rmw_dds_common__msg__ParticipantEntitiesInfo__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
rmw_dds_common__msg__ParticipantEntitiesInfo *
rmw_dds_common__msg__ParticipantEntitiesInfo__create(void);

/// Destroy msg/ParticipantEntitiesInfo message.
/**
 * It calls
 * rmw_dds_common__msg__ParticipantEntitiesInfo__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
void
rmw_dds_common__msg__ParticipantEntitiesInfo__destroy(rmw_dds_common__msg__ParticipantEntitiesInfo * msg);

/// Check for msg/ParticipantEntitiesInfo message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__ParticipantEntitiesInfo__are_equal(const rmw_dds_common__msg__ParticipantEntitiesInfo * lhs, const rmw_dds_common__msg__ParticipantEntitiesInfo * rhs);

/// Copy a msg/ParticipantEntitiesInfo message.
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
rmw_dds_common__msg__ParticipantEntitiesInfo__copy(
  const rmw_dds_common__msg__ParticipantEntitiesInfo * input,
  rmw_dds_common__msg__ParticipantEntitiesInfo * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
const rosidl_type_hash_t *
rmw_dds_common__msg__ParticipantEntitiesInfo__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
const rosidl_runtime_c__type_description__TypeDescription *
rmw_dds_common__msg__ParticipantEntitiesInfo__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
const rosidl_runtime_c__type_description__TypeSource *
rmw_dds_common__msg__ParticipantEntitiesInfo__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
const rosidl_runtime_c__type_description__TypeSource__Sequence *
rmw_dds_common__msg__ParticipantEntitiesInfo__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/ParticipantEntitiesInfo messages.
/**
 * It allocates the memory for the number of elements and calls
 * rmw_dds_common__msg__ParticipantEntitiesInfo__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence__init(rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence * array, size_t size);

/// Finalize array of msg/ParticipantEntitiesInfo messages.
/**
 * It calls
 * rmw_dds_common__msg__ParticipantEntitiesInfo__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
void
rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence__fini(rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence * array);

/// Create array of msg/ParticipantEntitiesInfo messages.
/**
 * It allocates the memory for the array and calls
 * rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence *
rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence__create(size_t size);

/// Destroy array of msg/ParticipantEntitiesInfo messages.
/**
 * It calls
 * rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
void
rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence__destroy(rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence * array);

/// Check for msg/ParticipantEntitiesInfo message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
bool
rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence__are_equal(const rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence * lhs, const rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence * rhs);

/// Copy an array of msg/ParticipantEntitiesInfo messages.
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
rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence__copy(
  const rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence * input,
  rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__FUNCTIONS_H_
