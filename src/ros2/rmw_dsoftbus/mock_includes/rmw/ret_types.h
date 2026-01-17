// Minimal mock for rmw/ret_types.h
#ifndef RMW__RET_TYPES_H_
#define RMW__RET_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

// RMW return type (alias for rmw_ret_t from types.h)
typedef int rmw_ret_t;

// Already defined in rmw/types.h, this file is for compatibility
// with code that includes ret_types.h directly

#ifdef __cplusplus
}
#endif

#endif  // RMW__RET_TYPES_H_
