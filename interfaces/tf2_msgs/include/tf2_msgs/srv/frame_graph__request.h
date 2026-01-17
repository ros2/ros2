// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/srv/FrameGraph_Request type

#ifndef TF2_MSGS__SRV__FRAMEGRAPH_REQUEST_H_
#define TF2_MSGS__SRV__FRAMEGRAPH_REQUEST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "tf2_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct tf2_msgs__srv__FrameGraph_Request
{
  uint8_t structure_needs_at_least_one_member;
} tf2_msgs__srv__FrameGraph_Request;

typedef struct tf2_msgs__srv__FrameGraph_Request__Sequence
{
  tf2_msgs__srv__FrameGraph_Request * data;
  size_t size;
  size_t capacity;
} tf2_msgs__srv__FrameGraph_Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__srv__FrameGraph_Request__init(tf2_msgs__srv__FrameGraph_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__srv__FrameGraph_Request__fini(tf2_msgs__srv__FrameGraph_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
tf2_msgs__srv__FrameGraph_Request * tf2_msgs__srv__FrameGraph_Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__srv__FrameGraph_Request__destroy(tf2_msgs__srv__FrameGraph_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__srv__FrameGraph_Request__Sequence__init(
  tf2_msgs__srv__FrameGraph_Request__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__srv__FrameGraph_Request__Sequence__fini(
  tf2_msgs__srv__FrameGraph_Request__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TF2_MSGS__SRV__FRAMEGRAPH_REQUEST_H_
