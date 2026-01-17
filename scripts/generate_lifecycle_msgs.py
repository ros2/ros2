#!/usr/bin/env python3
"""Generate lifecycle_msgs message and service files for OpenHarmony ROS2 port."""

import os

BASE_DIR = "/home/jiusi/M-DDS/ohos_ros2/interfaces/lifecycle_msgs"
PKG = "lifecycle_msgs"

def to_snake_case(name):
    result = []
    for i, c in enumerate(name):
        if c.isupper() and i > 0:
            result.append('_')
        result.append(c.lower())
    return ''.join(result)

def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  Created: {path}")

# ============================================================================
# State message header
# ============================================================================
STATE_HEADER = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/State type

#ifndef LIFECYCLE_MSGS__MSG__STATE_H_
#define LIFECYCLE_MSGS__MSG__STATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// Primary states
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_UNKNOWN ((uint8_t)0)
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_UNCONFIGURED ((uint8_t)1)
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_INACTIVE ((uint8_t)2)
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_ACTIVE ((uint8_t)3)
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_FINALIZED ((uint8_t)4)

// Transition states
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_CONFIGURING ((uint8_t)10)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_CLEANINGUP ((uint8_t)11)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_SHUTTINGDOWN ((uint8_t)12)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_ACTIVATING ((uint8_t)13)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_DEACTIVATING ((uint8_t)14)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_ERRORPROCESSING ((uint8_t)15)

/// Lifecycle state with id and label
typedef struct lifecycle_msgs__msg__State
{
  uint8_t id;
  rosidl_runtime_c__String label;
} lifecycle_msgs__msg__State;

typedef struct lifecycle_msgs__msg__State__Sequence
{
  lifecycle_msgs__msg__State * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__msg__State__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__State__init(lifecycle_msgs__msg__State * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__State__fini(lifecycle_msgs__msg__State * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__State * lifecycle_msgs__msg__State__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__State__destroy(lifecycle_msgs__msg__State * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__State__Sequence__init(
  lifecycle_msgs__msg__State__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__State__Sequence__fini(
  lifecycle_msgs__msg__State__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__STATE_H_
'''

# ============================================================================
# Transition message header
# ============================================================================
TRANSITION_HEADER = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/Transition type

#ifndef LIFECYCLE_MSGS__MSG__TRANSITION_H_
#define LIFECYCLE_MSGS__MSG__TRANSITION_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// Transition constants
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CREATE ((uint8_t)0)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CONFIGURE ((uint8_t)1)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CLEANUP ((uint8_t)2)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ACTIVATE ((uint8_t)3)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_DEACTIVATE ((uint8_t)4)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_UNCONFIGURED_SHUTDOWN ((uint8_t)5)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_INACTIVE_SHUTDOWN ((uint8_t)6)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ACTIVE_SHUTDOWN ((uint8_t)7)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_DESTROY ((uint8_t)8)

// Callback return codes
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CALLBACK_SUCCESS ((uint8_t)97)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CALLBACK_FAILURE ((uint8_t)98)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CALLBACK_ERROR ((uint8_t)99)

// On error transitions
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CONFIGURE_SUCCESS ((uint8_t)10)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CONFIGURE_FAILURE ((uint8_t)11)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CONFIGURE_ERROR ((uint8_t)12)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CLEANUP_SUCCESS ((uint8_t)20)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CLEANUP_FAILURE ((uint8_t)21)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CLEANUP_ERROR ((uint8_t)22)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ACTIVATE_SUCCESS ((uint8_t)30)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ACTIVATE_FAILURE ((uint8_t)31)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ACTIVATE_ERROR ((uint8_t)32)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_DEACTIVATE_SUCCESS ((uint8_t)40)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_DEACTIVATE_FAILURE ((uint8_t)41)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_DEACTIVATE_ERROR ((uint8_t)42)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_SHUTDOWN_SUCCESS ((uint8_t)50)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_SHUTDOWN_FAILURE ((uint8_t)51)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_SHUTDOWN_ERROR ((uint8_t)52)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ERROR_SUCCESS ((uint8_t)60)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ERROR_FAILURE ((uint8_t)61)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ERROR_ERROR ((uint8_t)62)

/// Lifecycle transition with id and label
typedef struct lifecycle_msgs__msg__Transition
{
  uint8_t id;
  rosidl_runtime_c__String label;
} lifecycle_msgs__msg__Transition;

typedef struct lifecycle_msgs__msg__Transition__Sequence
{
  lifecycle_msgs__msg__Transition * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__msg__Transition__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__Transition__init(lifecycle_msgs__msg__Transition * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__Transition__fini(lifecycle_msgs__msg__Transition * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__Transition * lifecycle_msgs__msg__Transition__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__Transition__destroy(lifecycle_msgs__msg__Transition * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__Transition__Sequence__init(
  lifecycle_msgs__msg__Transition__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__Transition__Sequence__fini(
  lifecycle_msgs__msg__Transition__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__TRANSITION_H_
'''

# ============================================================================
# TransitionDescription message header
# ============================================================================
TRANSITION_DESC_HEADER = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/TransitionDescription type

#ifndef LIFECYCLE_MSGS__MSG__TRANSITION_DESCRIPTION_H_
#define LIFECYCLE_MSGS__MSG__TRANSITION_DESCRIPTION_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "lifecycle_msgs/msg/state.h"
#include "lifecycle_msgs/msg/transition.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Full description of a lifecycle transition
typedef struct lifecycle_msgs__msg__TransitionDescription
{
  lifecycle_msgs__msg__Transition transition;
  lifecycle_msgs__msg__State start_state;
  lifecycle_msgs__msg__State goal_state;
} lifecycle_msgs__msg__TransitionDescription;

typedef struct lifecycle_msgs__msg__TransitionDescription__Sequence
{
  lifecycle_msgs__msg__TransitionDescription * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__msg__TransitionDescription__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__TransitionDescription__init(lifecycle_msgs__msg__TransitionDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionDescription__fini(lifecycle_msgs__msg__TransitionDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__TransitionDescription * lifecycle_msgs__msg__TransitionDescription__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionDescription__destroy(lifecycle_msgs__msg__TransitionDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__TransitionDescription__Sequence__init(
  lifecycle_msgs__msg__TransitionDescription__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionDescription__Sequence__fini(
  lifecycle_msgs__msg__TransitionDescription__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__TRANSITION_DESCRIPTION_H_
'''

# ============================================================================
# TransitionEvent message header
# ============================================================================
TRANSITION_EVENT_HEADER = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/TransitionEvent type

#ifndef LIFECYCLE_MSGS__MSG__TRANSITION_EVENT_H_
#define LIFECYCLE_MSGS__MSG__TRANSITION_EVENT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "builtin_interfaces/msg/time.h"
#include "lifecycle_msgs/msg/state.h"
#include "lifecycle_msgs/msg/transition.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Event when a lifecycle transition occurs
typedef struct lifecycle_msgs__msg__TransitionEvent
{
  builtin_interfaces__msg__Time timestamp;
  lifecycle_msgs__msg__Transition transition;
  lifecycle_msgs__msg__State start_state;
  lifecycle_msgs__msg__State goal_state;
} lifecycle_msgs__msg__TransitionEvent;

typedef struct lifecycle_msgs__msg__TransitionEvent__Sequence
{
  lifecycle_msgs__msg__TransitionEvent * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__msg__TransitionEvent__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__TransitionEvent__init(lifecycle_msgs__msg__TransitionEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionEvent__fini(lifecycle_msgs__msg__TransitionEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__TransitionEvent * lifecycle_msgs__msg__TransitionEvent__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionEvent__destroy(lifecycle_msgs__msg__TransitionEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__TransitionEvent__Sequence__init(
  lifecycle_msgs__msg__TransitionEvent__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionEvent__Sequence__fini(
  lifecycle_msgs__msg__TransitionEvent__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__TRANSITION_EVENT_H_
'''

# ============================================================================
# Service headers
# ============================================================================
CHANGE_STATE_HEADER = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/ChangeState type

#ifndef LIFECYCLE_MSGS__SRV__CHANGE_STATE_H_
#define LIFECYCLE_MSGS__SRV__CHANGE_STATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "lifecycle_msgs/msg/transition.h"

#ifdef __cplusplus
extern "C" {
#endif

// Request
typedef struct lifecycle_msgs__srv__ChangeState__Request
{
  lifecycle_msgs__msg__Transition transition;
} lifecycle_msgs__srv__ChangeState__Request;

typedef struct lifecycle_msgs__srv__ChangeState__Request__Sequence
{
  lifecycle_msgs__srv__ChangeState__Request * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__ChangeState__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__ChangeState__Request__init(lifecycle_msgs__srv__ChangeState__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__ChangeState__Request__fini(lifecycle_msgs__srv__ChangeState__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__ChangeState__Request * lifecycle_msgs__srv__ChangeState__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__ChangeState__Request__destroy(lifecycle_msgs__srv__ChangeState__Request * msg);

// Response
typedef struct lifecycle_msgs__srv__ChangeState__Response
{
  bool success;
} lifecycle_msgs__srv__ChangeState__Response;

typedef struct lifecycle_msgs__srv__ChangeState__Response__Sequence
{
  lifecycle_msgs__srv__ChangeState__Response * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__ChangeState__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__ChangeState__Response__init(lifecycle_msgs__srv__ChangeState__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__ChangeState__Response__fini(lifecycle_msgs__srv__ChangeState__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__ChangeState__Response * lifecycle_msgs__srv__ChangeState__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__ChangeState__Response__destroy(lifecycle_msgs__srv__ChangeState__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__SRV__CHANGE_STATE_H_
'''

GET_AVAILABLE_STATES_HEADER = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetAvailableStates type

#ifndef LIFECYCLE_MSGS__SRV__GET_AVAILABLE_STATES_H_
#define LIFECYCLE_MSGS__SRV__GET_AVAILABLE_STATES_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "lifecycle_msgs/msg/state.h"

#ifdef __cplusplus
extern "C" {
#endif

// Request (empty)
typedef struct lifecycle_msgs__srv__GetAvailableStates__Request
{
  uint8_t structure_needs_at_least_one_member;
} lifecycle_msgs__srv__GetAvailableStates__Request;

typedef struct lifecycle_msgs__srv__GetAvailableStates__Request__Sequence
{
  lifecycle_msgs__srv__GetAvailableStates__Request * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__GetAvailableStates__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__GetAvailableStates__Request__init(lifecycle_msgs__srv__GetAvailableStates__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetAvailableStates__Request__fini(lifecycle_msgs__srv__GetAvailableStates__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__GetAvailableStates__Request * lifecycle_msgs__srv__GetAvailableStates__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetAvailableStates__Request__destroy(lifecycle_msgs__srv__GetAvailableStates__Request * msg);

// Response
typedef struct lifecycle_msgs__srv__GetAvailableStates__Response
{
  lifecycle_msgs__msg__State__Sequence available_states;
} lifecycle_msgs__srv__GetAvailableStates__Response;

typedef struct lifecycle_msgs__srv__GetAvailableStates__Response__Sequence
{
  lifecycle_msgs__srv__GetAvailableStates__Response * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__GetAvailableStates__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__GetAvailableStates__Response__init(lifecycle_msgs__srv__GetAvailableStates__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetAvailableStates__Response__fini(lifecycle_msgs__srv__GetAvailableStates__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__GetAvailableStates__Response * lifecycle_msgs__srv__GetAvailableStates__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetAvailableStates__Response__destroy(lifecycle_msgs__srv__GetAvailableStates__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__SRV__GET_AVAILABLE_STATES_H_
'''

GET_AVAILABLE_TRANSITIONS_HEADER = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetAvailableTransitions type

#ifndef LIFECYCLE_MSGS__SRV__GET_AVAILABLE_TRANSITIONS_H_
#define LIFECYCLE_MSGS__SRV__GET_AVAILABLE_TRANSITIONS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "lifecycle_msgs/msg/transition_description.h"

#ifdef __cplusplus
extern "C" {
#endif

// Request (empty)
typedef struct lifecycle_msgs__srv__GetAvailableTransitions__Request
{
  uint8_t structure_needs_at_least_one_member;
} lifecycle_msgs__srv__GetAvailableTransitions__Request;

typedef struct lifecycle_msgs__srv__GetAvailableTransitions__Request__Sequence
{
  lifecycle_msgs__srv__GetAvailableTransitions__Request * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__GetAvailableTransitions__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__GetAvailableTransitions__Request__init(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetAvailableTransitions__Request__fini(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__GetAvailableTransitions__Request * lifecycle_msgs__srv__GetAvailableTransitions__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetAvailableTransitions__Request__destroy(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg);

// Response
typedef struct lifecycle_msgs__srv__GetAvailableTransitions__Response
{
  lifecycle_msgs__msg__TransitionDescription__Sequence available_transitions;
} lifecycle_msgs__srv__GetAvailableTransitions__Response;

typedef struct lifecycle_msgs__srv__GetAvailableTransitions__Response__Sequence
{
  lifecycle_msgs__srv__GetAvailableTransitions__Response * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__GetAvailableTransitions__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__GetAvailableTransitions__Response__init(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetAvailableTransitions__Response__fini(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__GetAvailableTransitions__Response * lifecycle_msgs__srv__GetAvailableTransitions__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetAvailableTransitions__Response__destroy(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__SRV__GET_AVAILABLE_TRANSITIONS_H_
'''

GET_STATE_HEADER = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetState type

#ifndef LIFECYCLE_MSGS__SRV__GET_STATE_H_
#define LIFECYCLE_MSGS__SRV__GET_STATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "lifecycle_msgs/msg/state.h"

#ifdef __cplusplus
extern "C" {
#endif

// Request (empty)
typedef struct lifecycle_msgs__srv__GetState__Request
{
  uint8_t structure_needs_at_least_one_member;
} lifecycle_msgs__srv__GetState__Request;

typedef struct lifecycle_msgs__srv__GetState__Request__Sequence
{
  lifecycle_msgs__srv__GetState__Request * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__GetState__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__GetState__Request__init(lifecycle_msgs__srv__GetState__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetState__Request__fini(lifecycle_msgs__srv__GetState__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__GetState__Request * lifecycle_msgs__srv__GetState__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetState__Request__destroy(lifecycle_msgs__srv__GetState__Request * msg);

// Response
typedef struct lifecycle_msgs__srv__GetState__Response
{
  lifecycle_msgs__msg__State current_state;
} lifecycle_msgs__srv__GetState__Response;

typedef struct lifecycle_msgs__srv__GetState__Response__Sequence
{
  lifecycle_msgs__srv__GetState__Response * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__GetState__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__GetState__Response__init(lifecycle_msgs__srv__GetState__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetState__Response__fini(lifecycle_msgs__srv__GetState__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__GetState__Response * lifecycle_msgs__srv__GetState__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetState__Response__destroy(lifecycle_msgs__srv__GetState__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__SRV__GET_STATE_H_
'''

def main():
    print(f"Generating {PKG} interface files...")
    
    # Write message headers
    print("\nWriting message headers:")
    write_file(f"{BASE_DIR}/include/{PKG}/msg/state.h", STATE_HEADER)
    write_file(f"{BASE_DIR}/include/{PKG}/msg/transition.h", TRANSITION_HEADER)
    write_file(f"{BASE_DIR}/include/{PKG}/msg/transition_description.h", TRANSITION_DESC_HEADER)
    write_file(f"{BASE_DIR}/include/{PKG}/msg/transition_event.h", TRANSITION_EVENT_HEADER)
    
    # Write service headers
    print("\nWriting service headers:")
    write_file(f"{BASE_DIR}/include/{PKG}/srv/change_state.h", CHANGE_STATE_HEADER)
    write_file(f"{BASE_DIR}/include/{PKG}/srv/get_available_states.h", GET_AVAILABLE_STATES_HEADER)
    write_file(f"{BASE_DIR}/include/{PKG}/srv/get_available_transitions.h", GET_AVAILABLE_TRANSITIONS_HEADER)
    write_file(f"{BASE_DIR}/include/{PKG}/srv/get_state.h", GET_STATE_HEADER)
    
    print(f"\nGeneration complete!")


if __name__ == "__main__":
    main()
