# DSoftBus 权限绕过完整指南

**最后更新**: 2026-01-14
**状态**: ✅ 推荐使用 (基于 dsoftbus 官方测试方法)

---

## 📋 概述

本指南提供了绕过 OpenHarmony dsoftbus 权限检查的正确方法，用于开发和测试阶段。

**关键发现**: rmw_dsoftbus 之前的实现使用了错误的 APL 级别 (`normal`)，导致权限不足。官方 dsoftbus 测试使用 `system_basic` APL，这是访问系统服务的必要条件。

---

## ⚠️ 重要差异对比

### ❌ 旧方法 (不推荐)

**文件**: `test/phase2_graph_discovery_with_permission_bypass.cpp`

```cpp
void InjectNativeTokenPermissions() {
    const char *perms[3];
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;
    perms[2] = DM_SERVICE_ACCESS_PERMISSION;  // ❌ 不需要

    NativeTokenInfoParams infoInstance = {
        .permsNum = 3,
        .perms = perms,
        .aplStr = "normal",  // ❌ 错误！应该是 system_basic
        // ...
    };
}
```

**问题**:
1. ❌ APL 级别使用 `"normal"` → 权限不足，无法访问系统服务
2. ❌ 包含不必要的第三个权限 `DM_SERVICE_ACCESS_PERMISSION`
3. ❌ 与 dsoftbus 官方测试方法不一致

### ✅ 新方法 (推荐)

**文件**: `test/softbus_permission_bypass.cpp`

```cpp
int SetSoftbusNativeTokenPermission(const char* processName) {
    const char** perms = new const char*[2];
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;

    NativeTokenInfoParams infoInstance = {
        .permsNum = 2,  // ✅ 只需要 2 个权限
        .perms = perms,
        .aplStr = "system_basic",  // ✅ 关键！必须是 system_basic
        // ...
    };

    tokenId = GetAccessTokenId(&infoInstance);
    SetSelfTokenID(tokenId);
    OHOS::Security::AccessToken::AccessTokenKit::ReloadNativeTokenInfo();
}
```

**优点**:
1. ✅ APL 级别使用 `"system_basic"` → 可以访问 dsoftbus 系统服务
2. ✅ 只请求必要的 2 个权限 (与官方测试一致)
3. ✅ 100% 复制 dsoftbus 官方测试方法 (`tests/sdk/common/src/softbus_access_token_test.cpp`)

---

## 🛠️ 快速开始

### 方法 1: 使用 permission_bypass_demo (推荐)

这是一个完整的示例程序，演示了正确的权限绕过方法。

#### 编译

在 OHOS 源码树中执行：

```bash
# 编译权限绕过演示程序
./build.sh --product-name rk3588 --ccache --target-cpu arm64 \
  --build-target //foundation/communication/rmw_dsoftbus:permission_bypass_demo
```

或使用 hb:

```bash
hb build -f -T //foundation/communication/rmw_dsoftbus:permission_bypass_demo
```

#### 部署到开发板

```bash
# 1. 将编译产物复制到 Windows 中转目录
mkdir -p /mnt/c/tmp/hdc_transfer
cp out/rk3588/communication/rmw_dsoftbus/permission_bypass_demo /mnt/c/tmp/hdc_transfer/

# 2. 获取设备 ID (多设备环境)
DEVICE_ID=$(powershell.exe -NoProfile -Command "hdc list targets" | grep device | head -1 | awk '{print $1}' | tr -d '\r\n')

# 3. 传输到设备
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\permission_bypass_demo' '/data/local/tmp/'"

# 4. 设置执行权限
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/local/tmp/permission_bypass_demo'"
```

#### 运行测试

```bash
# 执行测试
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'cd /data/local/tmp && ./permission_bypass_demo'"
```

**预期输出**:

```
========================================
DSoftBus Permission Bypass Demo
Using official dsoftbus test approach
========================================

[Step 1] Setting NativeToken permissions...
[Permission] Setting NativeToken permissions for process: com.rmw_dsoftbus.permission_demo
[Permission] Token ID obtained: 537411619
[Permission] ✅ NativeToken permissions set successfully
[Permission]    - OHOS_PERMISSION_DISTRIBUTED_DATASYNC
[Permission]    - OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER
[Permission]    - APL: system_basic

[Step 2] Testing Bus Center APIs (with permission bypass)...
[Step 2.1] Registering device state callback...
✅ Success! Permission bypass is working!

[Step 2.2] Getting local device info...
✅ Local Device: rk3588_device_1
   NetworkId: 7e5a3f1b2c4d...

[Step 3] Testing Session APIs...
[Step 3.1] Creating session server: com.rmw_dsoftbus.test_session
✅ Session server created successfully!

...

✅ Test Completed Successfully!
```

**如果看到权限错误**:

```
❌ ERROR: RegNodeDeviceStateCb failed: -4
   Expected: 0 (success) if permission bypass worked
   Got: -4 (likely SOFTBUS_PERMISSION_DENIED)
```

这表示权限绕过**没有生效**，原因可能是：
- 使用了 `"normal"` APL 而不是 `"system_basic"`
- 没有调用 `SetSoftbusNativeTokenPermission()`
- Token 库加载失败

---

### 方法 2: 集成到现有测试代码

#### 步骤 1: 包含头文件

```cpp
#include "softbus_permission_bypass.h"
```

#### 步骤 2: 在测试初始化时调用

**GTest 示例**:

```cpp
class MyDSoftBusTest : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        // 在所有测试开始前设置权限
        if (SetSoftbusNativeTokenPermission("com.myapp.test") != 0) {
            printf("Failed to set dsoftbus permissions\n");
            // 可以选择是否继续测试
        }
    }
};

TEST_F(MyDSoftBusTest, TestDiscovery) {
    // 现在可以调用 dsoftbus API 而不会遇到权限错误
    int ret = RegNodeDeviceStateCb("com.myapp.test", &callback);
    EXPECT_EQ(ret, 0);  // 应该成功
}
```

**普通 main() 示例**:

```cpp
int main(int argc, char **argv) {
    // 第一件事：设置权限
    if (SetSoftbusNativeTokenPermission("com.myapp.test") != 0) {
        printf("Permission setup failed\n");
        return 1;
    }

    // 现在可以安全调用 dsoftbus API
    int ret = CreateSessionServer("com.myapp.test", "session1", &listener);
    // ...
}
```

#### 步骤 3: 更新 BUILD.gn

```gn
executable("my_dsoftbus_test") {
  sources = [
    "test/my_test.cpp",
    "test/softbus_permission_bypass.cpp",  # 添加权限绕过源文件
  ]

  include_dirs = [
    "test",  # 确保可以找到 softbus_permission_bypass.h
  ]

  # 必须链接这些 AccessToken 库
  external_deps = [
    "access_token:libaccesstoken_sdk",
    "access_token:libnativetoken",
    "access_token:libtoken_setproc",
    "dsoftbus:softbus_client",
  ]
}
```

---

## 📝 技术细节

### APL (Ability Privilege Level) 说明

OpenHarmony 使用 APL 来控制不同级别的权限访问：

| APL 级别 | 权限范围 | 用途 | DSoftBus 可用性 |
|---------|---------|------|---------------|
| `normal` | 普通应用权限 | 第三方应用 | ❌ **不可用** (权限不足) |
| `system_basic` | 系统基础权限 | 系统应用、系统服务 | ✅ **可用** |
| `system_core` | 系统核心权限 | 核心系统服务 | ✅ 可用 (过度) |

**关键发现**: DSoftBus 是系统级服务，需要至少 `system_basic` APL 才能访问其 API。使用 `normal` APL 会导致 `SOFTBUS_PERMISSION_DENIED (-4)` 错误。

### 必需权限列表

```cpp
// 权限 1: 数据同步权限 (必需)
OHOS_PERMISSION_DISTRIBUTED_DATASYNC = "ohos.permission.DISTRIBUTED_DATASYNC"

// 权限 2: DSoftBus 中心访问权限 (必需)
OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER = "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
```

**注意**:
- ✅ 只需要这 2 个权限即可访问所有 dsoftbus API
- ❌ `DM_SERVICE_ACCESS_PERMISSION` 不是必需的

### NativeToken 工作原理

```
用户代码调用 SetSoftbusNativeTokenPermission()
    ↓
1. 构建 NativeTokenInfoParams (包含权限列表和 APL)
    ↓
2. GetAccessTokenId() → 向 AccessToken 服务请求 token ID
    ↓
3. SetSelfTokenID() → 将 token ID 设置到当前进程
    ↓
4. ReloadNativeTokenInfo() → 通知系统重新加载权限
    ↓
DSoftBus API 调用时检查当前进程的 token → ✅ 权限验证通过
```

---

## 🔄 迁移指南

如果你的代码使用了旧的 `InjectNativeTokenPermissions()`:

### Before (旧代码)

```cpp
void InjectNativeTokenPermissions() {
    const char *perms[3];
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;
    perms[2] = DM_SERVICE_ACCESS_PERMISSION;

    NativeTokenInfoParams infoInstance = {
        .permsNum = 3,
        .perms = perms,
        .processName = PKG_NAME,
        .aplStr = "normal",  // ❌
    };
    // ...
}

int main() {
    InjectNativeTokenPermissions();
    // ...
}
```

### After (新代码)

```cpp
#include "softbus_permission_bypass.h"

int main() {
    // 替换为官方测试方法
    if (SetSoftbusNativeTokenPermission("com.myapp.test") != 0) {
        printf("Permission setup failed\n");
        return 1;
    }
    // ...
}
```

**变更清单**:
1. ✅ 包含 `softbus_permission_bypass.h`
2. ✅ 替换 `InjectNativeTokenPermissions()` 为 `SetSoftbusNativeTokenPermission()`
3. ✅ 在 BUILD.gn 中添加 `test/softbus_permission_bypass.cpp`
4. ✅ 确保链接 AccessToken 库

---

## 🧪 验证权限绕过是否生效

### 方法 1: 检查返回值

```cpp
int ret = RegNodeDeviceStateCb("com.test", &callback);
if (ret == -4) {
    printf("❌ Permission bypass FAILED (SOFTBUS_PERMISSION_DENIED)\n");
} else if (ret == 0) {
    printf("✅ Permission bypass SUCCESS\n");
} else {
    printf("⚠️ Other error: %d\n", ret);
}
```

### 方法 2: 查看日志

```bash
# 在设备上查看 hilog
powershell.exe -Command "hdc -t $DEVICE_ID shell 'hilog | grep -i permission'"
```

**成功时日志**:
```
[SoftBus] CheckPermission: process=com.myapp.test, permission granted
```

**失败时日志**:
```
[SoftBus] CheckPermission: process=com.myapp.test, permission denied (APL=normal)
```

---

## 📚 参考资料

### OpenHarmony 官方文档

- **dsoftbus 测试代码权限设置**:
  `dsoftbus/tests/sdk/common/src/softbus_access_token_test.cpp`

- **dsoftbus 测试示例**:
  - `dsoftbus/tests/sdk/connection/service/client_connection_test.cpp`
  - `dsoftbus/tests/sdk/bus_center/benchmarktest/bus_center_test.cpp`
  - `dsoftbus/tests/sdk/discovery/benchmarktest/discovery_test.cpp`

### rmw_dsoftbus 项目文件

- **权限绕过工具**: `test/softbus_permission_bypass.{h,cpp}`
- **演示程序**: `test/permission_bypass_demo.cpp`
- **构建配置**: `BUILD.gn` (搜索 `permission_bypass_demo`)

---

## ❓ 常见问题

### Q1: 为什么需要权限绕过？

**A**: OpenHarmony 的 dsoftbus 需要系统级权限才能访问。在开发测试阶段，我们的测试程序不是系统应用，无法通过正常途径获得权限。NativeToken 机制允许我们在测试时临时注入权限。

### Q2: 权限绕过在生产环境安全吗？

**A**: ⚠️ **不安全**！这个方法**仅用于开发和测试**。生产环境应该：
1. 将应用签名为系统应用
2. 在应用配置 (`config.json`) 中声明权限
3. 通过正常的权限申请流程获得授权

### Q3: 为什么 `"normal"` APL 不行？

**A**: DSoftBus 是系统服务，其 API 受系统级权限保护。`"normal"` APL 只能访问普通应用级 API，无法调用系统服务。必须使用至少 `system_basic` APL。

### Q4: 权限绕过失败怎么办？

**A**: 检查以下几点：
1. ✅ 确认使用了 `"system_basic"` APL (不是 `"normal"`)
2. ✅ 确认在调用任何 dsoftbus API **之前**调用了 `SetSoftbusNativeTokenPermission()`
3. ✅ 确认 BUILD.gn 中链接了所有 AccessToken 库
4. ✅ 确认设备上的 dsoftbus 服务正在运行 (`ps -A | grep softbus`)

### Q5: 可以只用一个权限吗？

**A**: ❌ 不推荐。虽然某些 API 可能只检查其中一个权限，但 dsoftbus 官方测试同时使用两个权限。为了兼容性和完整性，建议始终使用两个权限。

---

## ✅ 总结

### 关键要点

1. ✅ **使用 `system_basic` APL** (不是 `normal`)
2. ✅ **只需 2 个权限** (DATASYNC + SOFTBUS_CENTER)
3. ✅ **在 dsoftbus API 调用前设置权限**
4. ✅ **复制 dsoftbus 官方测试方法**

### 推荐工作流

```
1. 包含 softbus_permission_bypass.h
   ↓
2. 在测试开始时调用 SetSoftbusNativeTokenPermission()
   ↓
3. 验证返回值 (应该返回 0)
   ↓
4. 调用 dsoftbus API (不再遇到权限错误)
   ↓
5. 使用 permission_bypass_demo 验证方法正确性
```

### 下一步

- 运行 `permission_bypass_demo` 验证权限绕过是否工作
- 更新现有测试代码使用新的权限绕过方法
- 在 Phase 2/3 测试中使用此方法绕过权限检查
- 记录测试结果到 `docs/progress.md`

---

**版本**: 1.0
**作者**: ROS2 KaihongOS Port Team
**日期**: 2026-01-14
