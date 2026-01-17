// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs visibility control

#ifndef LIFECYCLE_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define LIFECYCLE_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #if defined(ROSIDL_GENERATOR_C_BUILDING_DLL_lifecycle_msgs)
    #define ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs __declspec(dllexport)
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs __declspec(dllimport)
  #endif
#else
  #define ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
