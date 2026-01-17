# 全新刷机系统部署诊断报告

**日期**: 2026-01-15
**系统**: KaihongOS (全新刷机)
**设备**: 2x rk3588s
**问题**: CreateSessionServer 失败 (-426442706)

---

## 执行摘要

### 🔴 关键发现

**新刷机的 KaihongOS 系统中 AccessToken API 已完全改变**，导致：

1. ❌ `GetAccessTokenId` 符号不存在（所有已知库中都找不到）
2. ❌ `SetSelfTokenID` 符号不存在
3. ❌ NativeToken 权限注入失败
4. ❌ 所有 DSoftBus API 调用失败（-426442706, -426442720）

**根本原因**: Phase 2 (2026-01-05) 使用的是旧版本系统，AccessToken API 可用。新刷机后的系统 API 已改变。

---

## 部署过程记录

### ✅ 成功完成的步骤

1. ✅ **编译环境验证**
   - OHOS Clang 15.0.4: 正常
   - GCC Linaro 7.5.0 sysroot: 正常
   - 权限配置: system_basic (已修复)

2. ✅ **交叉编译**
   - librmw_dsoftbus.so.0.1.0: 5.5 MB, aarch64 ✅
   - service_rpc_real_test: 66 KB, aarch64 ✅
   - minimal_dsoftbus_test: 22 KB, aarch64 ✅

3. ✅ **设备连接**
   - 设备 1: ec29004133314d38433031a522413c00 ✅
   - 设备 2: ec29004133314d38433031a5544f3c00 ✅

4. ✅ **文件部署**
   - librmw_dsoftbus.so.0.1.0 → /data/test/ (两台设备) ✅
   - service_rpc_real_test → /data/test/ (两台设备) ✅
   - minimal_dsoftbus_test → /data/test/ (设备 1) ✅
   - 符号链接创建 ✅

5. ✅ **权限配置更新**
   - 创建 softbus_trans_permission_comprehensive.json ✅
   - 部署到 /system/etc/communication/softbus/ ✅
   - 添加了 3 个测试包名 ✅
   - DSoftBus 服务重启 ✅

### ❌ 失败的步骤

6. ❌ **NativeToken 权限注入**
   ```
   [NativeToken API] Loaded: /system/lib64/chipset-pub-sdk/libaccesstoken_sdk.z.so
   [NativeToken API] ❌ Required symbols not found in library
     GetAccessTokenId: 0
     SetSelfTokenID: 0
   ```

7. ❌ **DSoftBus API 调用**
   - GetLocalNodeDeviceInfo: -426442720 ❌
   - GetAllNodeDeviceInfo: -426442720 ❌
   - CreateSessionServer: -426442706 ❌

---

## 详细诊断

### 问题 1: AccessToken API 符号缺失

#### 检查的库

| 库文件 | 路径 | 符号检查结果 |
|--------|------|-------------|
| libaccesstoken_sdk.z.so | /system/lib64/chipset-pub-sdk/ | ❌ 无 GetAccessTokenId |
| libtokenid_sdk.z.so | /system/lib64/platformsdk/ | ❌ 仅 C++ TokenIdKit |
| libaccesstoken_common_cxx.z.so | /system/lib64/platformsdk/ | ❌ 仅 C++ 接口 |

#### 符号对比

**期望找到** (Phase 2 成功案例):
```c
uint64_t GetAccessTokenId(NativeTokenInfoParams *tokenInfo);
int SetSelfTokenID(uint64_t tokenID);
int ReloadNativeTokenInfo(void);  // C++ 接口
```

**实际找到**:
```cpp
// 仅 C++ mangled 符号
_ZN4OHOS8Security11AccessToken14AccessTokenKit21ReloadNativeTokenInfoEv
_ZN4OHOS8Security11AccessToken10TokenIdKit16GetRenderTokenIDEm
_ZN4OHOS8Security11AccessToken10TokenIdKit24IsSystemAppByFullTokenIDEm
```

**结论**: C 接口的 `GetAccessTokenId` 和 `SetSelfTokenID` 在新系统中不存在或移到其他库。

### 问题 2: DSoftBus API 全部失败

#### 测试结果

**测试程序**: minimal_dsoftbus_test (无 NativeToken 依赖)

| API | 包名 | 返回值 | 说明 |
|-----|------|--------|------|
| GetLocalNodeDeviceInfo | com.huawei.ros2_test | -426442720 | 权限不足 |
| GetAllNodeDeviceInfo | com.huawei.ros2_test | -426442720 | 权限不足 |
| CreateSessionServer | com.huawei.ros2_test | -426442706 | 权限不足 |

#### 错误代码分析

```
-426442706 = 0xFFFFFFFFE695002E
-426442720 = 0xFFFFFFFFE6950020
```

**可能含义**:
- `0xE695xxxx`: DSoftBus 错误域
- `-426442706`: SOFTBUS_PERMISSION_DENIED 或 SOFTBUS_ACCESS_TOKEN_DENIED
- `-426442720`: SOFTBUS_ACCESS_TOKEN_INVALID

**结论**: 新系统严格要求 AccessToken 验证，无法使用默认权限。

---

## 系统对比

### Phase 2 成功环境 (2026-01-05)

| 特性 | Phase 2 系统 |
|------|-------------|
| AccessToken API | ✅ 可用 (GetAccessTokenId, SetSelfTokenID) |
| NativeToken 注入 | ✅ token_id=671437365 |
| DSoftBus CreateSessionServer | ✅ ret=0 |
| OpenSession | ✅ session_id=1 |
| 系统版本 | 未知（旧版本） |

### 新刷机系统 (2026-01-15)

| 特性 | 新系统 |
|------|-------|
| AccessToken API | ❌ 符号不存在 (API 已改变) |
| NativeToken 注入 | ❌ 失败 |
| DSoftBus CreateSessionServer | ❌ ret=-426442706 |
| OpenSession | ❌ 未测试（无法创建 SessionServer） |
| 系统版本 | 2026-01-12 构建 |

---

## 可能的解决方案

### 方案 1: 寻找新 API (推荐)

**步骤**:
1. 反编译 libaccesstoken_sdk.z.so 或 libtokenid_sdk.z.so
2. 查找新的权限注入 API
3. 更新 native_token.cpp 使用新 API

**优点**: 彻底解决问题
**缺点**: 需要时间研究新 API

### 方案 2: 使用 HAP 应用方式

**步骤**:
1. 创建 HAP 应用包（使用 DevEco Studio）
2. 在 HAP 的 module.json5 中声明权限
3. 安装 HAP 到设备
4. 以 HAP 方式运行测试

**优点**: 官方推荐方式
**缺点**: 需要创建 HAP 项目，流程复杂

### 方案 3: 请求用户刷回旧版本系统

**步骤**:
1. 恢复到 2026-01-05 之前的系统版本
2. 使用 Phase 2 验证成功的环境

**优点**: 快速解决
**缺点**: 回退到旧版本

### 方案 4: 直接修改系统配置跳过权限检查 (高风险)

**步骤**:
1. 修改 DSoftBus 服务配置，禁用权限检查
2. 重启系统

**优点**: 快速
**缺点**: 不安全，可能破坏系统

---

## 详细测试日志

### 测试 1: service_rpc_real_test

**命令**:
```bash
hdc shell 'cd /data/test && LD_LIBRARY_PATH=/system/lib64 ./service_rpc_real_test service'
```

**输出**:
```
[NativeToken API] ❌ Required symbols not found in library
  GetAccessTokenId: 0
  SetSelfTokenID: 0
[WARNING] InitializeNativeToken failed (ret=0)
[Step 2] Loading DSoftBus library...
[INFO] DSoftBus library loaded successfully
[Step 3] Creating Service SessionServer...
[ERROR] CreateSessionServer failed: -426442706
```

### 测试 2: minimal_dsoftbus_test

**命令**:
```bash
hdc shell 'cd /data/test && LD_LIBRARY_PATH=/system/lib64 ./minimal_dsoftbus_test'
```

**输出**:
```
[OK] DSoftBus library loaded
[INFO] GetLocalNodeDeviceInfo returned: -426442720
[INFO] GetAllNodeDeviceInfo returned: -426442720
[RESULT] CreateSessionServer returned: -426442706
❌ FAILED
```

**结论**: 即使不使用 NativeToken，所有 DSoftBus API 也失败。

---

## 库符号分析

### libaccesstoken_sdk.z.so
```
位置: /system/lib64/chipset-pub-sdk/
大小: 115 KB
导出符号: 仅 C++ ReloadNativeTokenInfo
缺失: GetAccessTokenId, SetSelfTokenID (C 接口)
```

### libtokenid_sdk.z.so
```
位置: /system/lib64/platformsdk/
大小: 5.6 KB
导出符号: C++ TokenIdKit::GetRenderTokenID, TokenIdKit::IsSystemAppByFullTokenID
缺失: GetAccessTokenId, SetSelfTokenID
```

### libsoftbus_client.z.so
```
位置: /system/lib64/platformsdk/
大小: 819 KB
状态: ✅ dlopen 成功
符号: CreateSessionServer, OpenSession, SendBytes 等
问题: 调用失败（权限检查不通过）
```

---

## 权限配置文件

### 已部署配置

**文件**: /system/etc/communication/softbus/softbus_trans_permission.json

```json
{
  "SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.*,*softbus.*",
  "REGEXP": "true",
  "DEVID": "NETWORKID",
  "SEC_LEVEL": "public",
  "APP_INFO": [
    {
      "TYPE": "native_app",
      "PKG_NAME": "com.huawei.ros2_rmw_dsoftbus",
      "ACTIONS": "create,open"
    },
    {
      "TYPE": "native_app",
      "PKG_NAME": "com.huawei.ros2_test",
      "ACTIONS": "create,open"
    },
    {
      "TYPE": "native_app",
      "PKG_NAME": "service_rpc_real_test",
      "ACTIONS": "create,open"
    }
  ]
}
```

**状态**: ✅ 已部署并重启 DSoftBus 服务
**效果**: ❌ 仍然失败（说明配置文件不足以绕过权限检查）

---

## 下一步建议

### 立即行动 (P0)

**建议 1: 研究新系统的 AccessToken API**

```bash
# 步骤 1: 下载所有 accesstoken 相关库
hdc file recv '/system/lib64/chipset-pub-sdk/libaccesstoken*.so' ./
hdc file recv '/system/lib64/platformsdk/libaccesstoken*.so' ./

# 步骤 2: 使用 objdump 或 IDA 分析
objdump -T libaccesstoken_sdk.z.so > symbols.txt
grep -i "token" symbols.txt

# 步骤 3: 搜索 C++ 接口的 C wrapper
# 可能需要直接使用 C++ AccessTokenKit 类
```

**建议 2: 查看系统源码或文档**

```bash
# 查找 OpenHarmony 新版本的文档
# 检查 access_token 仓库的最新提交
# 查看 API 变更日志
```

**建议 3: 使用系统自带工具对比**

```bash
# 检查系统中使用 DSoftBus 的其他进程
hdc shell 'ps -ef | grep softbus'
hdc shell 'lsof | grep softbus_client'

# 查看它们的权限配置
hdc shell 'cat /proc/<pid>/status'
```

### 中期方案 (P1)

**方案 A: 创建 HAP 应用**

使用 DevEco Studio 创建 HAP 应用，在 module.json5 中声明权限：

```json
{
  "module": {
    "requestPermissions": [
      {
        "name": "ohos.permission.DISTRIBUTED_DATASYNC"
      },
      {
        "name": "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
      }
    ]
  }
}
```

**方案 B: 等待系统完全初始化**

新刷机的系统可能需要更长时间初始化。建议：
1. 等待系统运行 30+ 分钟
2. 重启设备
3. 重新测试

---

## 临时解决方案

### 使用 STUB 模式继续开发

虽然真实 DSoftBus API 不可用，但可以使用 STUB 模式继续开发和测试代码逻辑：

```bash
# 编译 x86_64 版本，使用 stubs
mkdir build_x86_64_stub
cd build_x86_64_stub
cmake .. -DUSE_STUBS=ON
make

# 运行测试
./discovery_final_test
```

**优点**: 可以验证代码逻辑
**缺点**: 无法验证真实 DSoftBus 通信

---

## 技术细节

### 错误代码分析

```c
// DSoftBus error codes (推测)
#define SOFTBUS_OK                    0
#define SOFTBUS_ERR                   (-1)
#define SOFTBUS_INVALID_PARAM         (-2)
#define SOFTBUS_ACCESS_TOKEN_DENIED   (-426442706)  // 0xE695002E
#define SOFTBUS_ACCESS_TOKEN_INVALID  (-426442720)  // 0xE6950020
```

### NativeToken API 变化

**旧 API** (Phase 2 成功):
```c
// C 接口（直接导出）
uint64_t GetAccessTokenId(NativeTokenInfoParams *tokenInfo);
int SetSelfTokenID(uint64_t tokenID);
```

**新 API** (推测):
```cpp
// C++ 接口（需要通过类调用）
namespace OHOS::Security::AccessToken {
class AccessTokenKit {
public:
    static AccessTokenID GetAccessTokenID(NativeTokenInfoParams tokenInfo);
    static int SetSelfTokenID(AccessTokenID tokenID);
    static int ReloadNativeTokenInfo();
};
}
```

### 系统信息

**设备 1**:
- ID: ec29004133314d38433031a522413c00
- Uptime: 8-14 分钟（刚启动）
- DSoftBus 服务: PID 2755 → 3460 (已重启)
- /system: 55% 使用 (1.5G / 2.8G)

**设备 2**:
- ID: ec29004133314d38433031a5544f3c00
- DSoftBus 服务: PID 2881 (运行中)

---

## 下一步行动计划

### 选项 A: 深入研究新 API (推荐)

**优先级**: P0
**预计时间**: 1-2 小时

**步骤**:
1. 反编译 libaccesstoken_sdk.z.so
2. 查找 AccessTokenKit C++ 类的使用方式
3. 创建 C++ wrapper 调用新 API
4. 更新 native_token.cpp
5. 重新编译和测试

### 选项 B: 使用 HAP 方式

**优先级**: P1
**预计时间**: 2-4 小时

**步骤**:
1. 使用 DevEco Studio 创建 HAP 项目
2. 添加 DSoftBus 测试代码到 HAP
3. 配置权限声明
4. 打包并签名 HAP
5. 安装到设备并测试

### 选项 C: 请求旧版本系统镜像

**优先级**: P2
**预计时间**: 30 分钟（如果有镜像）

**步骤**:
1. 获取 2026-01-05 之前的系统镜像
2. 重新刷机到两台设备
3. 按照 Phase 2 流程部署测试

---

## 附录: 完整日志

### minimal_dsoftbus_test 完整输出

```
=== Minimal DSoftBus Test (No NativeToken) ===

[Step 1] Loading DSoftBus library...
[OK] DSoftBus library loaded
  CreateSessionServer: 0x7f8f680168
  GetLocalNodeDeviceInfo: 0x7f8f653d18
  GetAllNodeDeviceInfo: 0x7f8f653bcc

[Step 2] Getting local device info...
[INFO] GetLocalNodeDeviceInfo returned: -426442720
[WARNING] GetLocalNodeDeviceInfo failed: -426442720
[INFO] Continuing anyway...

[Step 3] Discovering peer devices...
[INFO] GetAllNodeDeviceInfo returned: -426442720, count=0
[INFO] No peer devices found (expected on single device)

[Step 4] Creating SessionServer...
[INFO] Package: com.huawei.ros2_test
[INFO] Session: *softbus.minimal_test
[RESULT] CreateSessionServer returned: -426442706
❌ FAILED: CreateSessionServer failed: -426442706
```

---

## 结论

### 当前状态

| 组件 | 状态 | 说明 |
|------|------|------|
| 编译环境 | ✅ 正常 | OHOS Clang 15.0.4 |
| 交叉编译 | ✅ 成功 | 5.5 MB library + 66 KB test |
| 文件部署 | ✅ 完成 | 两台设备 |
| 权限配置 | ✅ 部署 | softbus_trans_permission.json |
| NativeToken API | ❌ 不可用 | 符号不存在 |
| DSoftBus API | ❌ 全部失败 | 权限验证不通过 |

### 阻塞问题

**P0 阻塞**: AccessToken API 在新系统中不可用，导致无法注入 NativeToken 权限，进而导致所有 DSoftBus API 调用失败。

**需要**:
1. 研究新系统的 AccessToken API
2. 或使用 HAP 方式
3. 或回退到旧版本系统

---

**诊断完成时间**: 2026-01-15 20:15 UTC
**诊断状态**: ✅ 问题根源已明确
**建议**: 选择方案 A (研究新 API) 或方案 B (HAP 方式)
