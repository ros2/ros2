#ifndef BUILTIN_INTERFACES__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
#define BUILTIN_INTERFACES__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_CPP_EXPORT_builtin_interfaces __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_CPP_IMPORT_builtin_interfaces __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_CPP_EXPORT_builtin_interfaces __declspec(dllexport)
    #define ROSIDL_GENERATOR_CPP_IMPORT_builtin_interfaces __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_CPP_BUILDING_DLL_builtin_interfaces
    #define ROSIDL_GENERATOR_CPP_PUBLIC_builtin_interfaces ROSIDL_GENERATOR_CPP_EXPORT_builtin_interfaces
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_builtin_interfaces ROSIDL_GENERATOR_CPP_IMPORT_builtin_interfaces
  #endif
#else
  #define ROSIDL_GENERATOR_CPP_EXPORT_builtin_interfaces __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_CPP_IMPORT_builtin_interfaces
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_CPP_PUBLIC_builtin_interfaces __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_builtin_interfaces
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif
