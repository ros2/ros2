// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/ListNodes type

#ifndef COMPOSITION_INTERFACES__SRV__LIST_NODES_H_
#define COMPOSITION_INTERFACES__SRV__LIST_NODES_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "composition_interfaces/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// ListNodes Request
// =============================================================================

/// Request to list loaded component nodes (empty request)
typedef struct composition_interfaces__srv__ListNodes__Request
{
  uint8_t structure_needs_at_least_one_member;
} composition_interfaces__srv__ListNodes__Request;

typedef struct composition_interfaces__srv__ListNodes__Request__Sequence
{
  composition_interfaces__srv__ListNodes__Request * data;
  size_t size;
  size_t capacity;
} composition_interfaces__srv__ListNodes__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
bool composition_interfaces__srv__ListNodes__Request__init(
  composition_interfaces__srv__ListNodes__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__ListNodes__Request__fini(
  composition_interfaces__srv__ListNodes__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
composition_interfaces__srv__ListNodes__Request *
composition_interfaces__srv__ListNodes__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__ListNodes__Request__destroy(
  composition_interfaces__srv__ListNodes__Request * msg);

// =============================================================================
// ListNodes Response
// =============================================================================

/// Response containing list of loaded component nodes
typedef struct composition_interfaces__srv__ListNodes__Response
{
  /// Full node names of loaded components
  rosidl_runtime_c__String__Sequence full_node_names;
  /// Unique identifiers for each loaded component
  rosidl_runtime_c__uint64__Sequence unique_ids;
} composition_interfaces__srv__ListNodes__Response;

typedef struct composition_interfaces__srv__ListNodes__Response__Sequence
{
  composition_interfaces__srv__ListNodes__Response * data;
  size_t size;
  size_t capacity;
} composition_interfaces__srv__ListNodes__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
bool composition_interfaces__srv__ListNodes__Response__init(
  composition_interfaces__srv__ListNodes__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__ListNodes__Response__fini(
  composition_interfaces__srv__ListNodes__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
composition_interfaces__srv__ListNodes__Response *
composition_interfaces__srv__ListNodes__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__ListNodes__Response__destroy(
  composition_interfaces__srv__ListNodes__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // COMPOSITION_INTERFACES__SRV__LIST_NODES_H_
