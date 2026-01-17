/*
 * AccessToken API dlopen 封装实现
 */

#include "accesstoken_dlopen.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

// ============================================================================
// 全局变量
// ============================================================================

static void* g_tokenid_handle = nullptr;
static void* g_accesstoken_handle = nullptr;

// 函数指针（初始化为 NULL）
GetAccessTokenId_t GetAccessTokenId_dlopen = nullptr;
SetSelfTokenID_t SetSelfTokenID_dlopen = nullptr;
ReloadNativeTokenInfo_t ReloadNativeTokenInfo_dlopen = nullptr;

// ============================================================================
// 库路径配置
// ============================================================================

// 优先尝试的库路径（按优先级排序）
static const char* TOKENID_PATHS[] = {
    "/system/lib64/platformsdk/libtokenid_sdk.z.so",
    "/system/lib64/platformsdk/libtokenid_sdk.so",
    nullptr
};

static const char* ACCESSTOKEN_PATHS[] = {
    "/system/lib64/chipset-pub-sdk/libaccesstoken_sdk.z.so",
    "/system/lib64/chipset-pub-sdk/libaccesstoken_sdk.so",
    "/system/lib64/platformsdk/libaccesstoken_common_cxx.z.so",
    nullptr
};

// ============================================================================
// 辅助函数
// ============================================================================

static void* try_load_library(const char** paths, const char* lib_name) {
    for (int i = 0; paths[i] != nullptr; i++) {
        void* handle = dlopen(paths[i], RTLD_NOW | RTLD_GLOBAL);
        if (handle != nullptr) {
            printf("[AccessToken dlopen] ✓ Loaded %s from %s\n", lib_name, paths[i]);
            return handle;
        } else {
            printf("[AccessToken dlopen]   Failed to load %s: %s\n", paths[i], dlerror());
        }
    }
    printf("[AccessToken dlopen] ✗ Could not load %s from any path\n", lib_name);
    return nullptr;
}

// ============================================================================
// API 实现
// ============================================================================

int init_accesstoken_library(void) {
    printf("[AccessToken dlopen] Initializing AccessToken libraries...\n");

    // 1. 加载 libtokenid_sdk
    g_tokenid_handle = try_load_library(TOKENID_PATHS, "libtokenid_sdk");
    if (g_tokenid_handle == nullptr) {
        return -1;
    }

    // 2. 解析 tokenid_sdk 符号
    GetAccessTokenId_dlopen = (GetAccessTokenId_t)dlsym(g_tokenid_handle, "GetAccessTokenId");
    if (GetAccessTokenId_dlopen == nullptr) {
        printf("[AccessToken dlopen] ✗ GetAccessTokenId not found: %s\n", dlerror());
        cleanup_accesstoken_library();
        return -1;
    }
    printf("[AccessToken dlopen] ✓ GetAccessTokenId loaded\n");

    SetSelfTokenID_dlopen = (SetSelfTokenID_t)dlsym(g_tokenid_handle, "SetSelfTokenID");
    if (SetSelfTokenID_dlopen == nullptr) {
        printf("[AccessToken dlopen] ✗ SetSelfTokenID not found: %s\n", dlerror());
        cleanup_accesstoken_library();
        return -1;
    }
    printf("[AccessToken dlopen] ✓ SetSelfTokenID loaded\n");

    // 3. 尝试加载 AccessTokenKit (可选，用于 ReloadNativeTokenInfo)
    g_accesstoken_handle = try_load_library(ACCESSTOKEN_PATHS, "libaccesstoken_sdk");

    if (g_accesstoken_handle != nullptr) {
        // 尝试解析 C++ 符号 (name mangled)
        // _ZN4OHOS8Security11AccessToken14AccessTokenKit21ReloadNativeTokenInfoEv
        ReloadNativeTokenInfo_dlopen = (ReloadNativeTokenInfo_t)dlsym(
            g_accesstoken_handle,
            "_ZN4OHOS8Security11AccessToken14AccessTokenKit21ReloadNativeTokenInfoEv"
        );

        if (ReloadNativeTokenInfo_dlopen != nullptr) {
            printf("[AccessToken dlopen] ✓ ReloadNativeTokenInfo loaded\n");
        } else {
            printf("[AccessToken dlopen] ⚠ ReloadNativeTokenInfo not found (non-critical): %s\n", dlerror());
            // 非关键，继续
        }
    }

    printf("[AccessToken dlopen] ✅ AccessToken library initialization complete\n");
    return 0;
}

void cleanup_accesstoken_library(void) {
    if (g_accesstoken_handle != nullptr) {
        dlclose(g_accesstoken_handle);
        g_accesstoken_handle = nullptr;
    }

    if (g_tokenid_handle != nullptr) {
        dlclose(g_tokenid_handle);
        g_tokenid_handle = nullptr;
    }

    GetAccessTokenId_dlopen = nullptr;
    SetSelfTokenID_dlopen = nullptr;
    ReloadNativeTokenInfo_dlopen = nullptr;

    printf("[AccessToken dlopen] Cleaned up\n");
}

bool is_accesstoken_loaded(void) {
    return (g_tokenid_handle != nullptr) &&
           (GetAccessTokenId_dlopen != nullptr) &&
           (SetSelfTokenID_dlopen != nullptr);
}
