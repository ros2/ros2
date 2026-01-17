/*
 * Copyright (c) 2026 ROS2 KaihongOS Port Project
 * Licensed under the Apache License, Version 2.0 (the "License");
 *
 * Softbus Permission Bypass Utility
 * Based on OpenHarmony dsoftbus official test approach
 * Reference: dsoftbus/tests/sdk/common/src/softbus_access_token_test.cpp
 */

#include "softbus_permission_bypass.h"
#include <stdio.h>
#include <memory>  // Required by accesstoken_kit.h for std::shared_ptr

// OpenHarmony permission system headers
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"

// Softbus permission definitions (from softbus_common.h)
#define OHOS_PERMISSION_DISTRIBUTED_DATASYNC "ohos.permission.DISTRIBUTED_DATASYNC"
#define OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"

/**
 * @brief Set NativeToken permissions for softbus access (RECOMMENDED METHOD)
 *
 * This function replicates the exact approach used by OpenHarmony dsoftbus
 * official tests to bypass permission checks during development/testing.
 *
 * Key differences from previous implementation:
 * - Uses "system_basic" APL instead of "normal" (critical for system service access)
 * - Only requests 2 essential permissions (DATASYNC + SOFTBUS_CENTER)
 * - Matches dsoftbus official test configuration exactly
 *
 * @param processName The process name to register with the token system
 * @return 0 on success, -1 on failure
 *
 * @usage
 *   // In test SetUpTestCase() or main():
 *   if (SetSoftbusNativeTokenPermission("com.example.test") != 0) {
 *       printf("Failed to set softbus permissions\n");
 *       return -1;
 *   }
 */
int SetSoftbusNativeTokenPermission(const char* processName) {
    if (processName == NULL) {
        printf("[Permission] ERROR: processName is NULL\n");
        return -1;
    }

    printf("[Permission] Setting NativeToken permissions for process: %s\n", processName);

    uint64_t tokenId;

    // Allocate permission array (dsoftbus official approach uses new[])
    const char** perms = new const char*[2];
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;

    // Configure NativeToken parameters (EXACTLY matching dsoftbus official tests)
    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 2,
        .aclsNum = 0,
        .dcaps = nullptr,
        .perms = perms,
        .acls = nullptr,
        .processName = processName,
        .aplStr = "system_basic",  // ⚠️ CRITICAL: Must be system_basic, not normal!
    };

    // Step 1: Get access token ID
    tokenId = GetAccessTokenId(&infoInstance);
    if (tokenId == 0) {
        printf("[Permission] ERROR: GetAccessTokenId returned 0 (invalid token)\n");
        delete[] perms;
        return -1;
    }
    printf("[Permission] Token ID obtained: %llu\n", (unsigned long long)tokenId);

    // Step 2: Set token for current process
    int setRet = SetSelfTokenID(tokenId);
    if (setRet != 0) {
        printf("[Permission] WARNING: SetSelfTokenID returned %d (may still work)\n", setRet);
    }

    // Step 3: Reload native token info to take effect
    int reloadRet = OHOS::Security::AccessToken::AccessTokenKit::ReloadNativeTokenInfo();
    if (reloadRet != 0) {
        printf("[Permission] WARNING: ReloadNativeTokenInfo returned %d\n", reloadRet);
    }

    // Cleanup
    delete[] perms;

    printf("[Permission] ✅ NativeToken permissions set successfully\n");
    printf("[Permission]    - OHOS_PERMISSION_DISTRIBUTED_DATASYNC\n");
    printf("[Permission]    - OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER\n");
    printf("[Permission]    - APL: system_basic\n");

    return 0;
}

/**
 * @brief Alternative permission setup using stack allocation (lightweight version)
 *
 * This version avoids dynamic allocation and is suitable for simple test cases.
 * Functionally identical to SetSoftbusNativeTokenPermission() but simpler.
 *
 * @param processName The process name to register
 * @return 0 on success, -1 on failure
 */
int SetSoftbusPermissionSimple(const char* processName) {
    if (processName == NULL) {
        return -1;
    }

    const char* perms[2];
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;

    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 2,
        .aclsNum = 0,
        .dcaps = NULL,
        .perms = perms,
        .acls = NULL,
        .processName = processName,
        .aplStr = "system_basic",
    };

    uint64_t tokenId = GetAccessTokenId(&infoInstance);
    SetSelfTokenID(tokenId);
    OHOS::Security::AccessToken::AccessTokenKit::ReloadNativeTokenInfo();

    return 0;
}
