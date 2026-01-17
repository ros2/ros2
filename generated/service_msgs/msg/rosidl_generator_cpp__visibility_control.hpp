#ifndef SERVICE_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
#define SERVICE_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_CPP_EXPORT_service_msgs __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_CPP_IMPORT_service_msgs __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_CPP_EXPORT_service_msgs __declspec(dllexport)
    #define ROSIDL_GENERATOR_CPP_IMPORT_service_msgs __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_CPP_BUILDING_DLL_service_msgs
    #define ROSIDL_GENERATOR_CPP_PUBLIC_service_msgs ROSIDL_GENERATOR_CPP_EXPORT_service_msgs
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_service_msgs ROSIDL_GENERATOR_CPP_IMPORT_service_msgs
  #endif
#else
  #define ROSIDL_GENERATOR_CPP_EXPORT_service_msgs __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_CPP_IMPORT_service_msgs
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_CPP_PUBLIC_service_msgs __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_service_msgs
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif
