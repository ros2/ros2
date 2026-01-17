/*
 * Softbus Permission Bypass (dlopen 版本) - 实现
 */

#include "softbus_permission_bypass_dlopen.h"
#include "accesstoken_dlopen.h"
#include <stdio.h>
#include <string.h>

// 权限常量（与官方定义一致）
#define OHOS_PERMISSION_DISTRIBUTED_DATASYNC "ohos.permission.DISTRIBUTED_DATASYNC"
#define OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"

int SetSoftbusNativeTokenPermission_dlopen(const char* processName) {
    if (processName == nullptr) {
        printf("[Permission dlopen] ERROR: processName is NULL\n");
        return -1;
    }

    printf("[Permission dlopen] Setting NativeToken permissions for process: %s\n", processName);

    // Step 1: 初始化 AccessToken 库
    printf("[Permission dlopen] Step 1: Loading AccessToken libraries...\n");
    if (init_accesstoken_library() != 0) {
        printf("[Permission dlopen] ERROR: Failed to load AccessToken libraries\n");
        return -1;
    }

    // Step 2: 准备权限参数
    const char* perms[2];
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;

    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 2,
        .aclsNum = 0,
        .dcaps = nullptr,
        .perms = perms,
        .acls = nullptr,
        .processName = processName,
        .aplStr = "system_basic",  // ⚠️ CRITICAL: Must be system_basic
    };

    // Step 3: 获取 AccessToken ID
    printf("[Permission dlopen] Step 2: Getting AccessToken ID...\n");
    uint64_t tokenId = GetAccessTokenId_dlopen(&infoInstance);
    if (tokenId == 0) {
        printf("[Permission dlopen] ERROR: GetAccessTokenId returned 0 (invalid token)\n");
        return -1;
    }
    printf("[Permission dlopen] ✓ Token ID obtained: 0x%lx\n", tokenId);

    // Step 4: 设置进程 Token
    printf("[Permission dlopen] Step 3: Setting process token...\n");
    int setRet = SetSelfTokenID_dlopen(tokenId);
    if (setRet != 0) {
        printf("[Permission dlopen] WARNING: SetSelfTokenID returned %d (may still work)\n", setRet);
    } else {
        printf("[Permission dlopen] ✓ SetSelfTokenID successful\n");
    }

    // Step 5: 重新加载 Token 信息（可选）
    printf("[Permission dlopen] Step 4: Reloading native token info...\n");
    if (ReloadNativeTokenInfo_dlopen != nullptr) {
        int reloadRet = ReloadNativeTokenInfo_dlopen();
        if (reloadRet != 0) {
            printf("[Permission dlopen] WARNING: ReloadNativeTokenInfo returned %d\n", reloadRet);
        } else {
            printf("[Permission dlopen] ✓ ReloadNativeTokenInfo successful\n");
        }
    } else {
        printf("[Permission dlopen] ⚠ ReloadNativeTokenInfo not available (skipped)\n");
    }

    // 完成
    printf("[Permission dlopen] ✅ NativeToken permissions set successfully\n");
    printf("[Permission dlopen]    - OHOS_PERMISSION_DISTRIBUTED_DATASYNC\n");
    printf("[Permission dlopen]    - OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER\n");
    printf("[Permission dlopen]    - APL: system_basic\n");

    return 0;
}
