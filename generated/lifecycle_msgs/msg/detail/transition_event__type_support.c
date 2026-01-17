// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from lifecycle_msgs:msg/TransitionEvent.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "lifecycle_msgs/msg/detail/transition_event__rosidl_typesupport_introspection_c.h"
#include "lifecycle_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "lifecycle_msgs/msg/detail/transition_event__functions.h"
#include "lifecycle_msgs/msg/detail/transition_event__struct.h"


// Include directives for member types
// Member `transition`
#include "lifecycle_msgs/msg/transition.h"
// Member `transition`
#include "lifecycle_msgs/msg/detail/transition__rosidl_typesupport_introspection_c.h"
// Member `start_state`
// Member `goal_state`
#include "lifecycle_msgs/msg/state.h"
// Member `start_state`
// Member `goal_state`
#include "lifecycle_msgs/msg/detail/state__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lifecycle_msgs__msg__TransitionEvent__init(message_memory);
}

void lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_fini_function(void * message_memory)
{
  lifecycle_msgs__msg__TransitionEvent__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_member_array[4] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs__msg__TransitionEvent, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "transition",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs__msg__TransitionEvent, transition),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "start_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs__msg__TransitionEvent, start_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs__msg__TransitionEvent, goal_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_members = {
  "lifecycle_msgs__msg",  // message namespace
  "TransitionEvent",  // message name
  4,  // number of fields
  sizeof(lifecycle_msgs__msg__TransitionEvent),
  false,  // has_any_key_member_
  lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_member_array,  // message members
  lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_init_function,  // function to initialize message memory (memory has to be allocated)
  lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_type_support_handle = {
  0,
  &lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_members,
  get_message_typesupport_handle_function,
  &lifecycle_msgs__msg__TransitionEvent__get_type_hash,
  &lifecycle_msgs__msg__TransitionEvent__get_type_description,
  &lifecycle_msgs__msg__TransitionEvent__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lifecycle_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, msg, TransitionEvent)() {
  lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, msg, Transition)();
  lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, msg, State)();
  lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, msg, State)();
  if (!lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_type_support_handle.typesupport_identifier) {
    lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &lifecycle_msgs__msg__TransitionEvent__rosidl_typesupport_introspection_c__TransitionEvent_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
