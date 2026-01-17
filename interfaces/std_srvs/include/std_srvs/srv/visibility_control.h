// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// Visibility control for std_srvs

#ifndef STD_SRVS__SRV__VISIBILITY_CONTROL_H_
#define STD_SRVS__SRV__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// Visibility macros for shared library support
#if defined(_WIN32)
  #if defined(ROSIDL_GENERATOR_C_BUILDING_DLL)
    #define STD_SRVS_PUBLIC __declspec(dllexport)
  #else
    #define STD_SRVS_PUBLIC __declspec(dllimport)
  #endif
#else
  #define STD_SRVS_PUBLIC __attribute__((visibility("default")))
#endif

#define STD_SRVS_LOCAL __attribute__((visibility("hidden")))

#ifdef __cplusplus
}
#endif

#endif  // STD_SRVS__SRV__VISIBILITY_CONTROL_H_
