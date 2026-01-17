// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// Visibility control for service_msgs

#ifndef SERVICE_MSGS__MSG__VISIBILITY_CONTROL_H_
#define SERVICE_MSGS__MSG__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// Visibility macros for shared library support
#if defined(_WIN32)
  #if defined(ROSIDL_GENERATOR_C_BUILDING_DLL)
    #define SERVICE_MSGS_PUBLIC __declspec(dllexport)
  #else
    #define SERVICE_MSGS_PUBLIC __declspec(dllimport)
  #endif
#else
  #define SERVICE_MSGS_PUBLIC __attribute__((visibility("default")))
#endif

#define SERVICE_MSGS_LOCAL __attribute__((visibility("hidden")))

#ifdef __cplusplus
}
#endif

#endif  // SERVICE_MSGS__MSG__VISIBILITY_CONTROL_H_
