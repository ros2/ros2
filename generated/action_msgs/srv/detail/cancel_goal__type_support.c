// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from action_msgs:srv/CancelGoal.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "action_msgs/srv/detail/cancel_goal__rosidl_typesupport_introspection_c.h"
#include "action_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "action_msgs/srv/detail/cancel_goal__functions.h"
#include "action_msgs/srv/detail/cancel_goal__struct.h"


// Include directives for member types
// Member `goal_info`
#include "action_msgs/msg/goal_info.h"
// Member `goal_info`
#include "action_msgs/msg/detail/goal_info__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  action_msgs__srv__CancelGoal_Request__init(message_memory);
}

void action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_fini_function(void * message_memory)
{
  action_msgs__srv__CancelGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_member_array[1] = {
  {
    "goal_info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(action_msgs__srv__CancelGoal_Request, goal_info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_members = {
  "action_msgs__srv",  // message namespace
  "CancelGoal_Request",  // message name
  1,  // number of fields
  sizeof(action_msgs__srv__CancelGoal_Request),
  false,  // has_any_key_member_
  action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_member_array,  // message members
  action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_type_support_handle = {
  0,
  &action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_members,
  get_message_typesupport_handle_function,
  &action_msgs__srv__CancelGoal_Request__get_type_hash,
  &action_msgs__srv__CancelGoal_Request__get_type_description,
  &action_msgs__srv__CancelGoal_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_action_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Request)() {
  action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, msg, GoalInfo)();
  if (!action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_type_support_handle.typesupport_identifier) {
    action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "action_msgs/srv/detail/cancel_goal__rosidl_typesupport_introspection_c.h"
// already included above
// #include "action_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "action_msgs/srv/detail/cancel_goal__functions.h"
// already included above
// #include "action_msgs/srv/detail/cancel_goal__struct.h"


// Include directives for member types
// Member `goals_canceling`
// already included above
// #include "action_msgs/msg/goal_info.h"
// Member `goals_canceling`
// already included above
// #include "action_msgs/msg/detail/goal_info__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  action_msgs__srv__CancelGoal_Response__init(message_memory);
}

void action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_fini_function(void * message_memory)
{
  action_msgs__srv__CancelGoal_Response__fini(message_memory);
}

size_t action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__size_function__CancelGoal_Response__goals_canceling(
  const void * untyped_member)
{
  const action_msgs__msg__GoalInfo__Sequence * member =
    (const action_msgs__msg__GoalInfo__Sequence *)(untyped_member);
  return member->size;
}

const void * action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Response__goals_canceling(
  const void * untyped_member, size_t index)
{
  const action_msgs__msg__GoalInfo__Sequence * member =
    (const action_msgs__msg__GoalInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void * action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__get_function__CancelGoal_Response__goals_canceling(
  void * untyped_member, size_t index)
{
  action_msgs__msg__GoalInfo__Sequence * member =
    (action_msgs__msg__GoalInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__fetch_function__CancelGoal_Response__goals_canceling(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const action_msgs__msg__GoalInfo * item =
    ((const action_msgs__msg__GoalInfo *)
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Response__goals_canceling(untyped_member, index));
  action_msgs__msg__GoalInfo * value =
    (action_msgs__msg__GoalInfo *)(untyped_value);
  *value = *item;
}

void action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__assign_function__CancelGoal_Response__goals_canceling(
  void * untyped_member, size_t index, const void * untyped_value)
{
  action_msgs__msg__GoalInfo * item =
    ((action_msgs__msg__GoalInfo *)
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__get_function__CancelGoal_Response__goals_canceling(untyped_member, index));
  const action_msgs__msg__GoalInfo * value =
    (const action_msgs__msg__GoalInfo *)(untyped_value);
  *item = *value;
}

bool action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__resize_function__CancelGoal_Response__goals_canceling(
  void * untyped_member, size_t size)
{
  action_msgs__msg__GoalInfo__Sequence * member =
    (action_msgs__msg__GoalInfo__Sequence *)(untyped_member);
  action_msgs__msg__GoalInfo__Sequence__fini(member);
  return action_msgs__msg__GoalInfo__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_member_array[2] = {
  {
    "return_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(action_msgs__srv__CancelGoal_Response, return_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goals_canceling",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(action_msgs__srv__CancelGoal_Response, goals_canceling),  // bytes offset in struct
    NULL,  // default value
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__size_function__CancelGoal_Response__goals_canceling,  // size() function pointer
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Response__goals_canceling,  // get_const(index) function pointer
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__get_function__CancelGoal_Response__goals_canceling,  // get(index) function pointer
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__fetch_function__CancelGoal_Response__goals_canceling,  // fetch(index, &value) function pointer
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__assign_function__CancelGoal_Response__goals_canceling,  // assign(index, value) function pointer
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__resize_function__CancelGoal_Response__goals_canceling  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_members = {
  "action_msgs__srv",  // message namespace
  "CancelGoal_Response",  // message name
  2,  // number of fields
  sizeof(action_msgs__srv__CancelGoal_Response),
  false,  // has_any_key_member_
  action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_member_array,  // message members
  action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_type_support_handle = {
  0,
  &action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_members,
  get_message_typesupport_handle_function,
  &action_msgs__srv__CancelGoal_Response__get_type_hash,
  &action_msgs__srv__CancelGoal_Response__get_type_description,
  &action_msgs__srv__CancelGoal_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_action_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Response)() {
  action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, msg, GoalInfo)();
  if (!action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_type_support_handle.typesupport_identifier) {
    action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "action_msgs/srv/detail/cancel_goal__rosidl_typesupport_introspection_c.h"
// already included above
// #include "action_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "action_msgs/srv/detail/cancel_goal__functions.h"
// already included above
// #include "action_msgs/srv/detail/cancel_goal__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "action_msgs/srv/cancel_goal.h"
// Member `request`
// Member `response`
// already included above
// #include "action_msgs/srv/detail/cancel_goal__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  action_msgs__srv__CancelGoal_Event__init(message_memory);
}

void action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_fini_function(void * message_memory)
{
  action_msgs__srv__CancelGoal_Event__fini(message_memory);
}

size_t action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__size_function__CancelGoal_Event__request(
  const void * untyped_member)
{
  const action_msgs__srv__CancelGoal_Request__Sequence * member =
    (const action_msgs__srv__CancelGoal_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Event__request(
  const void * untyped_member, size_t index)
{
  const action_msgs__srv__CancelGoal_Request__Sequence * member =
    (const action_msgs__srv__CancelGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_function__CancelGoal_Event__request(
  void * untyped_member, size_t index)
{
  action_msgs__srv__CancelGoal_Request__Sequence * member =
    (action_msgs__srv__CancelGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__fetch_function__CancelGoal_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const action_msgs__srv__CancelGoal_Request * item =
    ((const action_msgs__srv__CancelGoal_Request *)
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Event__request(untyped_member, index));
  action_msgs__srv__CancelGoal_Request * value =
    (action_msgs__srv__CancelGoal_Request *)(untyped_value);
  *value = *item;
}

void action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__assign_function__CancelGoal_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  action_msgs__srv__CancelGoal_Request * item =
    ((action_msgs__srv__CancelGoal_Request *)
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_function__CancelGoal_Event__request(untyped_member, index));
  const action_msgs__srv__CancelGoal_Request * value =
    (const action_msgs__srv__CancelGoal_Request *)(untyped_value);
  *item = *value;
}

bool action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__resize_function__CancelGoal_Event__request(
  void * untyped_member, size_t size)
{
  action_msgs__srv__CancelGoal_Request__Sequence * member =
    (action_msgs__srv__CancelGoal_Request__Sequence *)(untyped_member);
  action_msgs__srv__CancelGoal_Request__Sequence__fini(member);
  return action_msgs__srv__CancelGoal_Request__Sequence__init(member, size);
}

size_t action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__size_function__CancelGoal_Event__response(
  const void * untyped_member)
{
  const action_msgs__srv__CancelGoal_Response__Sequence * member =
    (const action_msgs__srv__CancelGoal_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Event__response(
  const void * untyped_member, size_t index)
{
  const action_msgs__srv__CancelGoal_Response__Sequence * member =
    (const action_msgs__srv__CancelGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_function__CancelGoal_Event__response(
  void * untyped_member, size_t index)
{
  action_msgs__srv__CancelGoal_Response__Sequence * member =
    (action_msgs__srv__CancelGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__fetch_function__CancelGoal_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const action_msgs__srv__CancelGoal_Response * item =
    ((const action_msgs__srv__CancelGoal_Response *)
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Event__response(untyped_member, index));
  action_msgs__srv__CancelGoal_Response * value =
    (action_msgs__srv__CancelGoal_Response *)(untyped_value);
  *value = *item;
}

void action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__assign_function__CancelGoal_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  action_msgs__srv__CancelGoal_Response * item =
    ((action_msgs__srv__CancelGoal_Response *)
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_function__CancelGoal_Event__response(untyped_member, index));
  const action_msgs__srv__CancelGoal_Response * value =
    (const action_msgs__srv__CancelGoal_Response *)(untyped_value);
  *item = *value;
}

bool action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__resize_function__CancelGoal_Event__response(
  void * untyped_member, size_t size)
{
  action_msgs__srv__CancelGoal_Response__Sequence * member =
    (action_msgs__srv__CancelGoal_Response__Sequence *)(untyped_member);
  action_msgs__srv__CancelGoal_Response__Sequence__fini(member);
  return action_msgs__srv__CancelGoal_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(action_msgs__srv__CancelGoal_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(action_msgs__srv__CancelGoal_Event, request),  // bytes offset in struct
    NULL,  // default value
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__size_function__CancelGoal_Event__request,  // size() function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Event__request,  // get_const(index) function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_function__CancelGoal_Event__request,  // get(index) function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__fetch_function__CancelGoal_Event__request,  // fetch(index, &value) function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__assign_function__CancelGoal_Event__request,  // assign(index, value) function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__resize_function__CancelGoal_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(action_msgs__srv__CancelGoal_Event, response),  // bytes offset in struct
    NULL,  // default value
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__size_function__CancelGoal_Event__response,  // size() function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_const_function__CancelGoal_Event__response,  // get_const(index) function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__get_function__CancelGoal_Event__response,  // get(index) function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__fetch_function__CancelGoal_Event__response,  // fetch(index, &value) function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__assign_function__CancelGoal_Event__response,  // assign(index, value) function pointer
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__resize_function__CancelGoal_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_members = {
  "action_msgs__srv",  // message namespace
  "CancelGoal_Event",  // message name
  3,  // number of fields
  sizeof(action_msgs__srv__CancelGoal_Event),
  false,  // has_any_key_member_
  action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_member_array,  // message members
  action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_type_support_handle = {
  0,
  &action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_members,
  get_message_typesupport_handle_function,
  &action_msgs__srv__CancelGoal_Event__get_type_hash,
  &action_msgs__srv__CancelGoal_Event__get_type_description,
  &action_msgs__srv__CancelGoal_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_action_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Event)() {
  action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Request)();
  action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Response)();
  if (!action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_type_support_handle.typesupport_identifier) {
    action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "action_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "action_msgs/srv/detail/cancel_goal__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_service_members = {
  "action_msgs__srv",  // service namespace
  "CancelGoal",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_Request_message_type_support_handle,
  NULL,  // response message
  // action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_Response_message_type_support_handle
  NULL  // event_message
  // action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_Response_message_type_support_handle
};


static rosidl_service_type_support_t action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_service_type_support_handle = {
  0,
  &action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_service_members,
  get_service_typesupport_handle_function,
  &action_msgs__srv__CancelGoal_Request__rosidl_typesupport_introspection_c__CancelGoal_Request_message_type_support_handle,
  &action_msgs__srv__CancelGoal_Response__rosidl_typesupport_introspection_c__CancelGoal_Response_message_type_support_handle,
  &action_msgs__srv__CancelGoal_Event__rosidl_typesupport_introspection_c__CancelGoal_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    action_msgs,
    srv,
    CancelGoal
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    action_msgs,
    srv,
    CancelGoal
  ),
  &action_msgs__srv__CancelGoal__get_type_hash,
  &action_msgs__srv__CancelGoal__get_type_description,
  &action_msgs__srv__CancelGoal__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_action_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal)(void) {
  if (!action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_service_type_support_handle.typesupport_identifier) {
    action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, srv, CancelGoal_Event)()->data;
  }

  return &action_msgs__srv__detail__cancel_goal__rosidl_typesupport_introspection_c__CancelGoal_service_type_support_handle;
}
