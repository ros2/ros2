// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0

#ifndef RMW_MOCK__VISIBILITY_H_
#define RMW_MOCK__VISIBILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

// Symbol visibility macros for shared library
#if defined(_WIN32)
  #ifdef RMW_MOCK_BUILDING_DLL
    #define RMW_MOCK_PUBLIC __declspec(dllexport)
  #else
    #define RMW_MOCK_PUBLIC __declspec(dllimport)
  #endif
  #define RMW_MOCK_LOCAL
#else
  #define RMW_MOCK_PUBLIC __attribute__((visibility("default")))
  #define RMW_MOCK_LOCAL __attribute__((visibility("hidden")))
#endif

#ifdef __cplusplus
}
#endif

#endif  // RMW_MOCK__VISIBILITY_H_
