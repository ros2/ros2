// Minimal mock for rosidl_runtime_c/sequence_bound.h
#ifndef ROSIDL_RUNTIME_C__SEQUENCE_BOUND_H_
#define ROSIDL_RUNTIME_C__SEQUENCE_BOUND_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Sequence bound structure for bounded sequences.
 */
typedef struct rosidl_runtime_c__Sequence__bound {
    size_t upper_bound;
} rosidl_runtime_c__Sequence__bound;

#ifdef __cplusplus
}
#endif

#endif  // ROSIDL_RUNTIME_C__SEQUENCE_BOUND_H_
