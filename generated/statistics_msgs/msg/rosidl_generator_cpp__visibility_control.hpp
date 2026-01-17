#ifndef STATISTICS_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
#define STATISTICS_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_CPP_EXPORT_statistics_msgs __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_CPP_IMPORT_statistics_msgs __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_CPP_EXPORT_statistics_msgs __declspec(dllexport)
    #define ROSIDL_GENERATOR_CPP_IMPORT_statistics_msgs __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_CPP_BUILDING_DLL_statistics_msgs
    #define ROSIDL_GENERATOR_CPP_PUBLIC_statistics_msgs ROSIDL_GENERATOR_CPP_EXPORT_statistics_msgs
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_statistics_msgs ROSIDL_GENERATOR_CPP_IMPORT_statistics_msgs
  #endif
#else
  #define ROSIDL_GENERATOR_CPP_EXPORT_statistics_msgs __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_CPP_IMPORT_statistics_msgs
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_CPP_PUBLIC_statistics_msgs __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_statistics_msgs
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif
