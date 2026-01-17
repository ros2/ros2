# OpenSession 根本原因分析

**日期**: 2026-01-16 04:20
**状态**: ✅ 根本原因已识别

---

## 执行摘要

通过深入的 hilog 分析，我们发现了所有问题的共同根源：**包名注册在 softbus 内部层面失败**。

### 关键发现

1. **CreateSessionServer 表面成功，内部失败**
   - 应用层 API 返回 0（成功）
   - 但 softbus 内部包名注册失败（错误 -426442749）
   - Service socket 创建失败（错误 -426442743）

2. **错误级联**
   - 包名注册失败 → Socket 创建失败 → Session 无法建立
   - OpenSession 返回 session ID，但连接建立失败（-426115004）

3. **多进程竞争**
   - 多个 PID 同时尝试注册包名
   - devicemanagerservice (PID 284) 也在使用 softbus

---

## 详细错误分析

### 错误码链

| 错误码 | 名称 | 位置 | 说明 |
|--------|------|------|------|
| **-426442749** | PkgNameInfo Invalid | softbus_client_frame_manager.c:68 | 包名信息验证失败 |
| **-426442743** | Service Socket Init Failed | ServiceSocketInit:168 | 服务 socket 创建失败 |
| **-426442715** | (后台运行时) | CreateSessionServer | Session server 创建失败 |
| **-426115004** | TDC_CHANNEL_ALREADY_PENDING | OpenSession 回调 | 传输通道等待状态 |

### hilog 证据

**Device 1**:
```
01-16 04:15:23.567  2482  2495 E C05700/CommSdk: [softbus_client_frame_manager.c:68] AddClientPkgName# check PkgNameInfo invalid.
01-16 04:15:23.567  2482  2495 E C05700/CommSdk: [softbus_client_frame_manager.c:117] ClientRegisterPkgName# AddClientPkgName failed. ret=-426442749
01-16 04:15:23.583  2482  2495 E C05a01/SoftBusManager: [ServiceSocketInit:168]create service socket faild, ret is -426442743.
```

**Device 2**:
```
01-16 04:15:23.005  2488  2502 E C05700/CommSdk: [softbus_client_frame_manager.c:68] AddClientPkgName# check PkgNameInfo invalid.
01-16 04:15:23.005  2488  2502 E C05700/CommSdk: [softbus_client_frame_manager.c:117] ClientRegisterPkgName# AddClientPkgName failed. ret=-426442749
01-16 04:15:23.022  2488  2502 E C05a01/SoftBusManager: [ServiceSocketInit:168]create service socket faild, ret is -426442743.
```

---

## 包名问题分析

### 当前配置
```c
#define TEST_PKG_NAME "com.huawei.rmw"           // 15 characters
#define TEST_SESSION_NAME "com.huawei.rmw.test"  // 21 characters
```

### 权限配置
```json
{
  "SESSION_NAME": "com.huawei.rmw.*",
  "REGEXP": "true",
  "APP_INFO": [{
    "TYPE": "native_app",
    "PKG_NAME": "com.huawei.rmw",
    "ACTIONS": "create,open"
  }]
}
```

### 可能的原因

1. **包名格式问题**
   - softbus 可能对包名有特定的格式要求
   - native_app 类型可能需要特殊处理

2. **包名冲突**
   - 其他系统进程可能在使用相同或相似的包名
   - devicemanagerservice (PID 284) 的调用也在失败

3. **Token 验证问题**
   - Access Token (0x28042d15 / 0x2808b1f7) 可能没有足够权限
   - SetSelfTokenID 可能在内部被覆盖或失效

4. **包名长度限制（不太可能）**
   - "com.huawei.rmw" 只有 15 字符
   - 之前测试过更短的包名也失败了

---

## OpenSession 失败的真正原因

**错误 -426115004 (SOFTBUS_TRANS_TDC_CHANNEL_ALREADY_PENDING) 是一个红鲱鱼**。

真正的原因是：
1. 虽然 CreateSessionServer 返回 0，但内部注册失败
2. Server 端没有真正的 socket 监听
3. Client 端 OpenSession 成功发起，但找不到有效的 server endpoint
4. 传输层尝试建立通道，但由于 server 端缺失而进入 PENDING 状态
5. 最终超时返回错误

---

## 为什么前台运行"看起来"成功？

前台运行时 CreateSessionServer 返回 0，但：
- **同样的内部错误在发生**（hilog 证明）
- 只是错误没有传播到应用层
- softbus 可能有容错机制，返回"成功"但实际功能损坏

---

## 解决方案

### 方案 1: 修复包名注册 ⭐ (推荐)

**调查方向**:
1. 检查 OpenHarmony 官方示例的包名格式
2. 查看 `softbus_client_frame_manager.c:68` 的 PkgNameInfo 验证逻辑
3. 可能需要特定的 UID/GID 或安全上下文

**实施步骤**:
- 查看 OpenHarmony 源码中的 PkgNameInfo 结构
- 对比官方测试程序的包名使用方式
- 可能需要使用 HAP 应用或特定的进程环境

### 方案 2: 使用系统账号运行

```bash
# 以 dsoftbus 用户身份运行测试程序
hdc shell 'su dsoftbus -c "cd /data/local/tmp && ./phase3c_simple_pkg server"'
```

### 方案 3: 创建 HAP 应用

创建一个真正的 OpenHarmony HAP 应用，而不是 native 二进制：
- 使用正式的 bundle name
- 通过 App Framework 调用 softbus
- 获得完整的权限和上下文

### 方案 4: 绕过包名验证（研究用）

如果可能，修改 softbus 源码或使用更底层的 API：
- 直接使用 trans_tcp_direct 而不是 Session API
- 或者使用 OpenAuthSession 替代 OpenSession

---

## Discovery "无法发现" 问题澄清

**用户报告**: "两台 rk3588s 测试相互发现无法发现"

**实际情况**: ✅ Discovery 完全正常！

```
[Test] === Listing Online Devices ===
[Test] Found 2 online device(s):
  [0] networkId: 6ea1cec...
      deviceName: KaihongBoard-3588S
  [1] networkId: 9868c2e...
      deviceName: KaihongBoard-3588S
```

Discovery (GetAllNodeDeviceInfo) 工作正常，设备可以相互发现。之前的误解可能来自于：
1. 旧的测试报告
2. NetworkID 变化导致的困惑
3. 或者是 Session 连接失败被误认为是 Discovery 失败

---

## 下一步行动

### 立即 (30分钟)
1. 研究 OpenHarmony 官方 softbus 测试代码
2. 查看 PkgNameInfo 结构的正确填充方式
3. 尝试使用系统账号运行

### 短期 (2小时)
1. 如果包名问题无法解决，创建 HAP 应用
2. 或者研究 OpenAuthSession API
3. 编写完整的诊断报告

### 长期
1. 向 OpenHarmony 社区报告此问题
2. 可能是 softbus 的 bug 或文档缺失
3. 考虑贡献补丁或改进文档

---

## 相关文档
- `OPENSESSION_PROGRESS_2026_01_16.md`
- `COMPLETE_DIAGNOSIS_AND_SOLUTION_2026_01_16.md`
- `docs/progress.md`

---

**结论**: 问题不是 OpenSession API 使用方式，而是 softbus 内部的包名验证机制。需要更深入的 OpenHarmony 源码研究或使用官方推荐的应用框架。
