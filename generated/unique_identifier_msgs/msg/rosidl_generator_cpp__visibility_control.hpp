#ifndef UNIQUE_IDENTIFIER_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
#define UNIQUE_IDENTIFIER_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_CPP_EXPORT_unique_identifier_msgs __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_CPP_IMPORT_unique_identifier_msgs __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_CPP_EXPORT_unique_identifier_msgs __declspec(dllexport)
    #define ROSIDL_GENERATOR_CPP_IMPORT_unique_identifier_msgs __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_CPP_BUILDING_DLL_unique_identifier_msgs
    #define ROSIDL_GENERATOR_CPP_PUBLIC_unique_identifier_msgs ROSIDL_GENERATOR_CPP_EXPORT_unique_identifier_msgs
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_unique_identifier_msgs ROSIDL_GENERATOR_CPP_IMPORT_unique_identifier_msgs
  #endif
#else
  #define ROSIDL_GENERATOR_CPP_EXPORT_unique_identifier_msgs __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_CPP_IMPORT_unique_identifier_msgs
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_CPP_PUBLIC_unique_identifier_msgs __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_unique_identifier_msgs
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif
