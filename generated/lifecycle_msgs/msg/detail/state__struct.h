// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lifecycle_msgs:msg/State.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/state.h"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__STATE__STRUCT_H_
#define LIFECYCLE_MSGS__MSG__DETAIL__STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'PRIMARY_STATE_UNKNOWN'.
/**
  * These are the primary states. State changes can only be requested when the
  * node is in one of these states.
  * Indicates state has not yet been set.
 */
enum
{
  lifecycle_msgs__msg__State__PRIMARY_STATE_UNKNOWN = 0
};

/// Constant 'PRIMARY_STATE_UNCONFIGURED'.
/**
  * This is the life cycle state the node is in immediately after being
  * instantiated.
 */
enum
{
  lifecycle_msgs__msg__State__PRIMARY_STATE_UNCONFIGURED = 1
};

/// Constant 'PRIMARY_STATE_INACTIVE'.
/**
  * This state represents a node that is not currently performing any processing.
 */
enum
{
  lifecycle_msgs__msg__State__PRIMARY_STATE_INACTIVE = 2
};

/// Constant 'PRIMARY_STATE_ACTIVE'.
/**
  * This is the main state of the node's life cycle. While in this state, the node
  * performs any processing, responds to service requests, reads and processes
  * data, produces output, etc.
 */
enum
{
  lifecycle_msgs__msg__State__PRIMARY_STATE_ACTIVE = 3
};

/// Constant 'PRIMARY_STATE_FINALIZED'.
/**
  * The finalized state is the state in which the node ends immediately before
  * being destroyed.
 */
enum
{
  lifecycle_msgs__msg__State__PRIMARY_STATE_FINALIZED = 4
};

/// Constant 'TRANSITION_STATE_CONFIGURING'.
/**
  * Temporary intermediate states. When a transition is requested, the node
  * changes its state into one of these states.
  * In this transition state the node's onConfigure callback will be called to
  * allow the node to load its configuration and conduct any required setup.
 */
enum
{
  lifecycle_msgs__msg__State__TRANSITION_STATE_CONFIGURING = 10
};

/// Constant 'TRANSITION_STATE_CLEANINGUP'.
/**
  * In this transition state the node's callback onCleanup will be called to clear
  * all state and return the node to a functionally equivalent state as when
  * first created.
 */
enum
{
  lifecycle_msgs__msg__State__TRANSITION_STATE_CLEANINGUP = 11
};

/// Constant 'TRANSITION_STATE_SHUTTINGDOWN'.
/**
  * In this transition state the callback onShutdown will be executed to do any
  * cleanup necessary before destruction.
 */
enum
{
  lifecycle_msgs__msg__State__TRANSITION_STATE_SHUTTINGDOWN = 12
};

/// Constant 'TRANSITION_STATE_ACTIVATING'.
/**
  * In this transition state the callback onActivate will be executed to do any
  * final preparations to start executing.
 */
enum
{
  lifecycle_msgs__msg__State__TRANSITION_STATE_ACTIVATING = 13
};

/// Constant 'TRANSITION_STATE_DEACTIVATING'.
/**
  * In this transition state the callback onDeactivate will be executed to do any
  * cleanup to start executing, and reverse the onActivate changes.
 */
enum
{
  lifecycle_msgs__msg__State__TRANSITION_STATE_DEACTIVATING = 14
};

/// Constant 'TRANSITION_STATE_ERRORPROCESSING'.
/**
  * This transition state is where any error may be cleaned up.
 */
enum
{
  lifecycle_msgs__msg__State__TRANSITION_STATE_ERRORPROCESSING = 15
};

// Include directives for member types
// Member 'label'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/State in the package lifecycle_msgs.
/**
  * Primary state definitions as depicted in:
  * http://design.ros2.org/articles/node_lifecycle.html
 */
typedef struct lifecycle_msgs__msg__State
{
  /// The state id value from the above definitions.
  uint8_t id;
  /// A text label of the state.
  rosidl_runtime_c__String label;
} lifecycle_msgs__msg__State;

// Struct for a sequence of lifecycle_msgs__msg__State.
typedef struct lifecycle_msgs__msg__State__Sequence
{
  lifecycle_msgs__msg__State * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lifecycle_msgs__msg__State__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__STATE__STRUCT_H_
