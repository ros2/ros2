/*
 * Copyright (c) 2026 ROS2 KaihongOS Port Project
 * Licensed under the Apache License, Version 2.0 (the "License");
 *
 * Softbus Permission Bypass Utility - Header
 */

#ifndef SOFTBUS_PERMISSION_BYPASS_H
#define SOFTBUS_PERMISSION_BYPASS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set NativeToken permissions for softbus access
 *
 * This function uses OpenHarmony's NativeToken system to bypass permission
 * checks during testing. It grants the following permissions:
 * - OHOS_PERMISSION_DISTRIBUTED_DATASYNC
 * - OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER
 *
 * IMPORTANT: Uses APL level "system_basic" (required for dsoftbus system service access)
 *
 * @param processName Process name to register (e.g., "com.example.test")
 * @return 0 on success, -1 on failure
 *
 * @usage Example in GTest:
 *   class MyTest : public ::testing::Test {
 *   protected:
 *       static void SetUpTestCase() {
 *           if (SetSoftbusNativeTokenPermission("com.myapp.test") != 0) {
 *               printf("Failed to set permissions\n");
 *           }
 *       }
 *   };
 */
int SetSoftbusNativeTokenPermission(const char* processName);

/**
 * @brief Simplified version using stack allocation
 *
 * Lightweight alternative to SetSoftbusNativeTokenPermission().
 * Same functionality but simpler implementation.
 *
 * @param processName Process name to register
 * @return 0 on success, -1 on failure
 */
int SetSoftbusPermissionSimple(const char* processName);

#ifdef __cplusplus
}
#endif

#endif // SOFTBUS_PERMISSION_BYPASS_H
