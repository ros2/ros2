// Mock RMW error handling for standalone compilation

#ifndef RMW__ERROR_HANDLING_H_
#define RMW__ERROR_HANDLING_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RMW_SET_ERROR_MSG(msg) fprintf(stderr, "[RMW_ERROR] %s\n", msg)
#define RMW_SET_ERROR_MSG_WITH_FORMAT_STRING(format, ...) \
    fprintf(stderr, "[RMW_ERROR] " format "\n", ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif  // RMW__ERROR_HANDLING_H_
