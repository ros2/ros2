/*
 * AccessToken API dlopen 封装
 * 用途: 运行时动态加载 OpenHarmony AccessToken 库
 * 解决: 交叉编译时符号解析问题（.z.so vs .so）
 */

#ifndef ACCESSTOKEN_DLOPEN_H
#define ACCESSTOKEN_DLOPEN_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// AccessToken 类型定义（与官方头文件一致）
// ============================================================================

typedef struct {
    int dcapsNum;
    int permsNum;
    int aclsNum;
    const char **dcaps;
    const char **perms;
    const char **acls;
    const char *processName;
    const char *aplStr;
} NativeTokenInfoParams;

// ============================================================================
// dlopen 函数指针类型定义
// ============================================================================

typedef uint64_t (*GetAccessTokenId_t)(NativeTokenInfoParams *infoInstance);
typedef int (*SetSelfTokenID_t)(uint64_t tokenId);
typedef int (*ReloadNativeTokenInfo_t)(void);

// ============================================================================
// 全局函数指针（运行时赋值）
// ============================================================================

extern GetAccessTokenId_t GetAccessTokenId_dlopen;
extern SetSelfTokenID_t SetSelfTokenID_dlopen;
extern ReloadNativeTokenInfo_t ReloadNativeTokenInfo_dlopen;

// ============================================================================
// API 函数
// ============================================================================

/**
 * @brief 初始化 AccessToken 库（dlopen 方式）
 * @return 0 成功，-1 失败
 */
int init_accesstoken_library(void);

/**
 * @brief 卸载 AccessToken 库
 */
void cleanup_accesstoken_library(void);

/**
 * @brief 检查 AccessToken 库是否已加载
 * @return true 已加载，false 未加载
 */
bool is_accesstoken_loaded(void);

#ifdef __cplusplus
}
#endif

#endif // ACCESSTOKEN_DLOPEN_H
