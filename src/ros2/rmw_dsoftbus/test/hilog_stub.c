/*
 * HiLog Stub Implementation
 * 用途: 提供 hilog 符号的 stub 实现，避免链接错误
 */

#include <stdio.h>
#include <stdarg.h>

// HiLog 函数类型和常量
#define LOG_CORE 3
#define LOG_APP 0

typedef enum {
    LOG_DEBUG = 3,
    LOG_INFO = 4,
    LOG_WARN = 5,
    LOG_ERROR = 6,
    LOG_FATAL = 7
} LogLevel;

typedef struct {
    unsigned short type;
    unsigned short level;
    unsigned int domain;
    const char* tag;
    const char* fmt;
} HiLogLabel;

// HiLog 函数 stub 实现
int HiLogPrint(int type, int level, unsigned int domain, const char *tag, const char *fmt, ...) {
    // Stub: 不做任何操作，或打印到 stderr
    #ifdef DEBUG_HILOG_STUB
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[HiLog Stub] [%s] ", tag ? tag : "NULL");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    #endif

    return 0;
}

int HiLogIsLoggable(unsigned int domain, const char *tag, int level) {
    // Stub: 总是返回不记录（0）
    return 0;
}

// 其他可能需要的 hilog 函数
void OH_LOG_Print(int type, int level, unsigned int domain, const char *tag, const char *fmt, ...) {
    // Stub: 不做任何操作
}
