/*
 * Softbus Permission Bypass (dlopen 版本)
 * 用途: 使用 dlopen 动态加载 AccessToken 库，绕过编译时链接问题
 */

#ifndef SOFTBUS_PERMISSION_BYPASS_DLOPEN_H
#define SOFTBUS_PERMISSION_BYPASS_DLOPEN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设置 Softbus NativeToken 权限（dlopen 版本）
 *
 * 此函数使用 dlopen 动态加载 AccessToken 库，避免编译时链接依赖。
 * 完全对齐 dsoftbus 官方测试方法（system_basic APL + 2 权限）。
 *
 * @param processName 进程名称
 * @return 0 成功，-1 失败
 */
int SetSoftbusNativeTokenPermission_dlopen(const char* processName);

#ifdef __cplusplus
}
#endif

#endif // SOFTBUS_PERMISSION_BYPASS_DLOPEN_H
