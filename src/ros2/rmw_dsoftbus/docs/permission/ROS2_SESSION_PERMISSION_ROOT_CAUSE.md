---
doc_id: analysis_session_permission
category: rmw_dsoftbus设计文档
title: CreateSession 权限失败根本原因分析
description: ROS2 CreateSession 权限失败的详细根本原因分析和解决方案
priority: HIGH
last_updated: 2026-01-06
tags: [CreateSession, 权限, 根本原因分析]
use_cases:
  - 理解 CreateSession 权限问题的根本原因
  - 学习如何配置权限以支持 ROS2 会话
---

# CreateSession 权限失败根本原因分析

## 问题现象

```
CreateSessionServer failed: -426442706
send request failed! ret=-426442742
pkgName=com.huawei.ros2_rmw_dsoftbus, sessionName=*.ros2_discovery
```

## 根本原因：SessionName 不匹配权限配置

### 1. 权限配置 (softbus_trans_permission.json)

```json
{
  "SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.*",  // REGEXP pattern
  "REGEXP": "true",
  "PKG_NAME": "com.huawei.ros2_rmw_dsoftbus",
  "TYPE": "native_app",
  "ACTIONS": "create,open"
}
```

### 2. 代码中的 SessionName 定义

**DiscoveryManager（discovery_manager.h:69）**:
```cpp
static constexpr const char* DISCOVERY_SESSION_NAME = "com.huawei.dmsdp.ros2_discovery";
```

**SessionManager（types.h:66）**:
```cpp
#define RMW_DSOFTBUS_SESSION_PREFIX "com.huawei.ros2_rmw_dsoftbus."
```

### 3. 为什么权限检查失败

| 组件 | 使用的 SessionName | 权限配置中的模式 | 匹配? |
|------|-------------------|-----------------|-------|
| DiscoveryManager | `com.huawei.dmsdp.ros2_discovery` | `com.huawei.ros2_rmw_dsoftbus.*` | ❌ 不匹配 |
| SessionManager | `com.huawei.ros2_rmw_dsoftbus.*` | `com.huawei.ros2_rmw_dsoftbus.*` | ✅ 匹配 |

**权限检查流程**：
1. CreateSessionServer(pkgName="com.huawei.ros2_rmw_dsoftbus", sessionName="com.huawei.dmsdp.ros2_discovery")
2. dsoftbus 权限引擎查找匹配的规则
3. 检查 PKG_NAME: ✅ 匹配 "com.huawei.ros2_rmw_dsoftbus"
4. 检查 SESSION_NAME 正则: ❌ "com.huawei.dmsdp.ros2_discovery" 不匹配 "com.huawei.ros2_rmw_dsoftbus.*"
5. 权限拒绝！返回 SOFTBUS_PERMISSION_DENIED (-426442706)

## 修复方案

### 方案 A（推荐）：统一使用 "com.huawei.ros2_rmw_dsoftbus.*" 前缀

**修改 discovery_manager.h:69**:
```cpp
// 从
static constexpr const char* DISCOVERY_SESSION_NAME = "com.huawei.dmsdp.ros2_discovery";

// 改为
static constexpr const char* DISCOVERY_SESSION_NAME = "com.huawei.ros2_rmw_dsoftbus.discovery";
```

**优点**：
- 所有 RMW 相关的 session 使用统一的命名空间
- 权限配置保持不变
- 符合 pkgName 命名规范

### 方案 B：扩展权限配置

**修改 config/softbus_trans_permission.json**:
```json
{
  "SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.*|com.huawei.dmsdp.*",
  "REGEXP": "true",
  ...
}
```

**缺点**：
- 引入额外的 dmsdp 命名空间
- 增加权限配置复杂度

## 推荐修复步骤

1. ✅ 修改 `discovery_manager.h:69`
2. ✅ 重新编译 rmw_dsoftbus
3. ✅ 重新部署到设备
4. ✅ 测试 CreateSessionServer

## 验证

运行测试后查看日志：
```bash
[DiscoveryManager] Creating SessionServer: name=com.huawei.ros2_rmw_dsoftbus.discovery
[DiscoveryManager] SessionServer created: id=X name=com.huawei.ros2_rmw_dsoftbus.discovery
```

如果 SessionServer created 返回 >= 0，则权限检查成功！
