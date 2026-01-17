# Phase 2 Graph Discovery - Permission Bypass Analysis

**Date**: 2026-01-08
**Status**: Research & Testing Plan Complete
**Session**: Permission Injection Investigation

---

## Executive Summary

通过调查 OpenHarmony 的 `khdeviceauth_tool` 和 `softbus_socket_tool`，我们发现了一个关键的权限绕过方法：**使用 NativeToken 系统在运行时为当前进程注入权限**。

这个方法允许 dsoftbus session 创建和连接无需传统的权限配置文件验证。

---

## 1. 权限绕过核心机制

### 1.1 NativeToken 系统概览

OpenHarmony 使用 **Native Token** 系统来管理原生应用的权限。关键接口：

```cpp
// From accesstoken_kit.h
struct NativeTokenInfoParams {
    int dcapsNum;                    // Distributed capabilities count
    int permsNum;                    // Permissions count
    int aclsNum;                     // Access control list count
    const char **dcaps;              // Distributed capabilities
    const char **perms;              // Permission strings
    const char **acls;               // ACL rules
    const char *processName;         // Process identifier
    const char *aplStr;              // Application privilege level ("normal", "system", "core")
};

// 获取访问令牌 ID
uint64_t GetAccessTokenId(NativeTokenInfoParams *infoInstance);

// 设置当前进程的令牌 ID
void SetSelfTokenID(uint64_t tokenId);
```

### 1.2 权限注入源码（来自 softbus_socket_tool）

**文件**: `OpenHarmony/foundation/communication/dsoftbus/tools/softbus_socket_tool/src/softbus_socket_tool_access_token.cpp`

```cpp
void ToolAddPermission()
{
    uint64_t tokenId;
    const char *perms[3];

    // 三个关键权限
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;
    perms[2] = DM_SERVICE_ACCESS_PERMISSION;  // "ohos.permission.ACCESS_SERVICE_DM"

    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 3,
        .aclsNum = 0,
        .dcaps = NULL,
        .perms = perms,
        .acls = NULL,
        .processName = "com.softbus_socket.tool",  // 可自定义
        .aplStr = "normal",
    };

    // 生成权限令牌
    tokenId = GetAccessTokenId(&infoInstance);

    // 设置当前进程的令牌
    SetSelfTokenID(tokenId);

    // 刷新权限信息
    OHOS::Security::AccessToken::AccessTokenKit::ReloadNativeTokenInfo();
}
```

### 1.3 关键发现

| 组件 | 作用 | 来源 |
|------|------|------|
| `GetAccessTokenId()` | 生成权限令牌 | accesstoken_kit.h |
| `SetSelfTokenID()` | 设置进程权限 | nativetoken_kit.h |
| `ReloadNativeTokenInfo()` | 刷新权限缓存 | accesstoken_kit.h (C++) |
| **OHOS_PERMISSION_DISTRIBUTED_DATASYNC** | 分布式数据同步权限 | 常量定义 |
| **OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER** | SoftBus 中心权限 | 常量定义 |
| **ACCESS_SERVICE_DM** | 设备管理服务访问 | 常量定义 |

---

## 2. Session 创建流程（权限绕过后）

### 2.1 Bus Center 初始化

权限注入后，调用 Bus Center 初始化：

```cpp
// 注册设备状态回调
int ret = RegNodeDeviceStateCb(PKG_NAME, &g_nodeStateCallback);

// 获取本地设备信息
NodeBasicInfo localInfo;
ret = GetLocalNodeDeviceInfo(PKG_NAME, &localInfo);

// 获取所有在线设备
NodeBasicInfo *onlineInfo = NULL;
int32_t onlineNum = 0;
ret = GetAllNodeDeviceInfo(PKG_NAME, &onlineInfo, &onlineNum);
```

### 2.2 Session 创建和打开

```cpp
// 创建会话服务器（监听来自其他设备的连接）
int ret = CreateSessionServer(
    "com.softbus_graph_discovery.test",    // pkgName
    "com.huawei.ros2.graph.discovery.server", // sessionName
    &g_sessionListener                    // 回调处理器
);

// 打开连接到对端设备的会话
SessionAttribute attr = {0};
attr.dataType = DATA_TYPE_BYTES;
attr.linkTypeNum = 1;
attr.linkType[0] = LINK_TYPE_WIFI | LINK_TYPE_BR;

int sessionId = OpenSession(
    "com.huawei.ros2.graph.discovery.server",    // mySessionName
    "com.huawei.ros2.graph.discovery.client",    // peerSessionName
    peerNetworkId,                               // 对端 network ID
    NULL,                                        // groupId
    &attr                                        // 会话属性
);

// 发送消息
SendBytes(sessionId, data, dataLen);

// 关闭会话
CloseSession(sessionId);
RemoveSessionServer(PKG_NAME, sessionName);
```

---

## 3. 权限注入的工作原理

### 3.1 权限链检查规避

传统流程：
```
应用请求 CreateSessionServer
    ↓
权限检查器读取 softbus_trans_permission.json
    ↓
验证应用权限是否在 allowlist 中
    ↓
拒绝未授权应用
```

**权限注入方式规避权限检查**：
```
应用调用 GetAccessTokenId() 和 SetSelfTokenID()
    ↓
注入 NativeToken 权限令牌
    ↓
权限检查器发现应用已拥有权限令牌
    ↓
跳过 JSON 配置文件验证
    ↓
允许 CreateSessionServer / OpenSession
```

### 3.2 重要注意事项

- **权限令牌作用域**: 设置后影响整个进程的权限检查
- **无需 JSON 修改**: 不需要修改 `softbus_trans_permission.json`
- **运行时生效**: 在应用启动时注入，无需重启系统
- **可访问性**: 需要能够链接 `accesstoken_kit.h` 和 `nativetoken_kit.h`

---

## 4. Phase 2 Graph Discovery 测试方案

### 4.1 测试要求

- ✅ **2 设备发现**: Device A 和 Device B 相互发现
- ✅ **Session 建立**: 两设备间建立 dsoftbus session
- ✅ **消息交换**: 双向发送和接收消息
- ✅ **权限绕过**: 使用 NativeToken 方法绕过权限检查

### 4.2 测试实现方式

**方式 1: 编译 + 部署（推荐）**

编译包含权限注入的可执行程序：

```bash
# 步骤 1: 编译
g++ -std=c++17 \
    phase2_graph_discovery_with_permission_bypass.cpp \
    softbus_dlopen_shim.cpp \
    -I include -I mock_includes \
    -I OpenHarmony/foundation/communication/dsoftbus/interfaces/kits \
    -I OpenHarmony/foundation/communication/dsoftbus/interfaces/kits/bus_center \
    -I OpenHarmony/foundation/communication/dsoftbus/interfaces/kits/transport \
    -o phase2_discovery_test \
    -ldl -lpthread -static-libstdc++ -static-libgcc

# 步骤 2: 部署到两台开发板
hdc -t DEVICE_ID1 file send phase2_discovery_test /data/local/tmp/
hdc -t DEVICE_ID2 file send phase2_discovery_test /data/local/tmp/

# 步骤 3: 在 DEVICE_ID2 上运行（作为服务器）
hdc -t DEVICE_ID2 shell '/data/local/tmp/phase2_discovery_test'

# 步骤 4: 在 DEVICE_ID1 上运行（作为客户端）
hdc -t DEVICE_ID1 shell '/data/local/tmp/phase2_discovery_test'

# 步骤 5: 查看输出
```

**方式 2: 手动 Shell 测试（快速验证）**

```bash
# 在 Device 1 上
hdc -t DEVICE_ID1 shell 'cd /system/lib64/platformsdk && cat libsoftbus_client.z.so | wc -c'

# 在 Device 2 上
hdc -t DEVICE_ID2 shell 'ls -l /system/etc/communication/softbus/'
```

### 4.3 测试输出预期

```
=========================================
Phase 2 Graph Discovery Test
With Permission Bypass (khdeviceauth_tool approach)
=========================================

[Main] Step 1: Injecting NativeToken permissions...
[Permission] Injecting NativeToken permissions...
[Permission] NativeToken permissions injected successfully

[Main] Step 2: Device discovery phase...
[Phase2] === Testing Device Discovery ===
[Phase2] Registering device state callback...
[Phase2] Getting local device info...
[Phase2] Local Device: KaihongOS-Device-1 (NetworkId: ec290041xxxxx)
[Phase2] Waiting for peer devices (timeout: 10 seconds)...
[Phase2] Discovery wait: 1/10 seconds
...
[Discovery] === OnNodeOnline ===
[Discovery] Device: KaihongOS-Device-2 (NetworkId: ec290041yyyyy)
[Phase2] Found 1 peer device(s)

[Main] Step 3: Session connection phase...
[Phase2] === Testing Session Connection ===
[Phase2] Connecting to peer: KaihongOS-Device-2 (NetworkId: ec290041yyyyy)
[Phase2] Creating session server...
[Phase2] Session server created: com.huawei.ros2.graph.discovery.server
[Phase2] Opening session to peer...
[Session] OnSessionOpened: sessionId=1, result=0
[Phase2] Session opened successfully: sessionId=1
[Phase2] Sending discovery message...
[Session] OnBytesReceived: sessionId=1, len=26
[Session] Data: PHASE2_DISCOVERY_TEST_MSG
[Phase2] Discovery message sent successfully

=========================================
Phase 2 Test Completed Successfully
=========================================
```

---

## 5. 关键代码位置参考

| 功能 | 文件位置 | 行号 |
|------|--------|------|
| 权限注入函数 | `OpenHarmony/foundation/communication/dsoftbus/tools/softbus_socket_tool/src/softbus_socket_tool_access_token.cpp` | 17-37 |
| 主函数调用权限注入 | `OpenHarmony/foundation/communication/dsoftbus/tools/softbus_socket_tool/main.c` | 59 |
| Bus Center 初始化 | `OpenHarmony/foundation/communication/dsoftbus/tools/softbus_socket_tool/src/bus_center.c` | 107-122 |
| Session 创建和打开 | `OpenHarmony/foundation/communication/dsoftbus/tools/softbus_socket_tool/src/softbus_socket_test.c` | 107-254 |
| 权限令牌头文件 | `OpenHarmony/.../security/accesstoken/interfaces/innerkits/accesstoken_kit.h` | - |
| Native Token 头文件 | `OpenHarmony/.../security/nativetoken/interfaces/innerkits/nativetoken_kit.h` | - |

---

## 6. 已验证信息

✅ **从设备配置**:
- 三个设备已连接（Device 1, 2, 3）
- OpenHarmony 版本: KaihongOS
- 权限配置文件位置: `/system/etc/communication/softbus/softbus_trans_permission.json`
- SoftBus 库位置: `/system/lib64/platformsdk/libsoftbus_client.z.so`

✅ **权限注入代码验证**:
- 源码位置: `/home/jiusi/M-DDS/OpenHarmony/foundation/communication/dsoftbus/tools/softbus_socket_tool/`
- 关键文件已读取和验证
- 权限常量已确认

---

## 7. 下一步行动

### 立即可做的事情

1. **编译修复** (30 分钟):
   - 添加缺失的头文件包含
   - 修复编译错误
   - 生成可执行程序

2. **部署测试** (15 分钟):
   - 将可执行程序部署到 2 个开发板
   - 在设备上设置 IPC 权限（如需要）

3. **测试执行** (10 分钟):
   - 在 Device 1 和 Device 2 上运行测试
   - 收集输出和日志
   - 验证发现和连接成功

### 诊断清单

运行测试前的检查:

- [ ] 确认两台开发板已连接: `hdc list targets`
- [ ] 检查 softbus 库: `hdc -t ID shell 'ls /system/lib64/platformsdk/libsoftbus*'`
- [ ] 检查权限配置: `hdc -t ID shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json'`
- [ ] 验证网络连通性: `hdc -t ID shell 'ping <peer_ip>'`
- [ ] 检查 dsoftbus 进程: `hdc -t ID shell 'ps | grep softbus'`

---

## 8. 常见问题排查

### Q: OpenSession 返回错误代码
**A**: 检查:
1. 权限令牌是否成功注入
2. 对端网络 ID 是否正确
3. 权限配置中是否包含会话名前缀
4. 两台设备是否在同一网络

### Q: Session 无法建立但没有错误
**A**: 检查:
1. CreateSessionServer 是否成功（检查返回值）
2. 设备发现回调是否被调用
3. dsoftbus 服务是否正在运行
4. 防火墙是否允许通信

### Q: 编译缺少头文件
**A**:
- 确保包含了所有 dsoftbus kit 头文件目录
- 手动添加缺失的常量定义
- 参考 `OpenHarmony/foundation/communication/dsoftbus/interfaces/kits/` 中的头文件

---

## 总结

通过 NativeToken 权限注入方法，我们可以在运行时为 dsoftbus 应用授予必要的权限，绕过静态权限配置文件的限制。这对于 Phase 2 Graph Discovery 的测试至关重要，特别是在两台设备间进行发现和通信时。

该方法已在 OpenHarmony 官方工具（softbus_socket_tool）中验证，是可靠的、受支持的方法。

