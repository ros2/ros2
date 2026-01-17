// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs visibility control

#ifndef TRAJECTORY_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define TRAJECTORY_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #if defined(ROSIDL_GENERATOR_C_BUILDING_DLL_trajectory_msgs)
    #define ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs __declspec(dllexport)
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs __declspec(dllimport)
  #endif
#else
  #define ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
}
#endif

#endif  // TRAJECTORY_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
