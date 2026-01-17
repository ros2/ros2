# Graph Discovery 真实 DSoftBus 测试结果报告

**日期**: 2026-01-14
**测试类型**: 真实 dsoftbus API 调用验证
**测试程序**: `real_dsoftbus_graph_test.cpp`
**测试状态**: ⚠️ **部分成功（Stub模式通过，真实API遇到权限问题）**

---

## 📊 执行摘要

### 成功项 ✅

1. **编译和部署**: aarch64 交叉编译成功，HDC部署成功
2. **动态链接器修复**: 创建 `/lib/ld-linux-aarch64.so.1` → `/lib/ld-musl-aarch64.so.1` 符号链接
3. **Stub模式测试**: DiscoveryManager + GraphCache 初始化和本地功能验证成功
4. **基础功能验证**:
   - 节点注册正常
   - 端点注册正常
   - GraphCache 查询正常
   - Discovery 统计数据正常

### 问题项 ⚠️

1. **权限阻塞**: 真实 dsoftbus API 调用因 `DISTRIBUTED_DATASYNC` 权限不足失败
2. **库版本差异**:
   - `build-phase3` 库使用 stub 实现（非真实 API）
   - Device 3 库有 dlopen shim 但遇到权限问题

---

## 🔬 详细测试结果

### 测试 1: Device 1 - Stub 模式成功

**设备**: `ec29004133314d38433031a522413c00`
**库版本**: `build-phase3/librmw_dsoftbus.so` (2.2M, 2026-01-05)
**结果**: ✅ **成功（Stub模式）**

```
=================================================
Real DSoftBus Graph Discovery Test
=================================================

[Config] Test duration: 10 seconds

[Step 1] Initializing DiscoveryManager...
[DiscoveryManager] Initializing discovery subsystem
[rmw_dsoftbus] NativeToken: set token_id=671361873 (verify=671361873)
[STUB] GetLocalNodeDeviceInfo: networkId=local_stub_pid_2612
[DiscoveryManager] Got network_id from dsoftbus: local_stub_pid_2612
[DiscoveryManager] Local identity: network_id=local_stub_pid_2612, instance_id=1609522010597005614
[DiscoveryManager] Creating SessionServer: name=com.huawei.dmsdp.ros2_discovery
[STUB] CreateSessionServer: com.huawei.dmsdp.ros2_discovery
[DiscoveryManager] SessionServer created: id=0 name=com.huawei.dmsdp.ros2_discovery
[OK] DiscoveryManager initialized

[Step 2] Initializing GraphCache...
[GraphCache] Initializing local graph cache
[OK] GraphCache initialized

[Step 3] Registering test node and endpoint...
[GraphCache] Registered node: test_talker
[GraphCache] Registered publisher: /chatter

[Step 4] Running discovery loop for 10 seconds...
[Progress] 5/10 seconds
[GraphCache] Total nodes: 1
[Progress] 10/10 seconds
[GraphCache] Total nodes: 1

[Step 5] Final Statistics
=================================================

[GraphCache]
  Total nodes:  1
  Total topics: 1

[All Nodes]
  - /::test_talker

[All Topics]
  - /chatter
    Publishers: 1, Subscribers: 0

[DiscoveryManager Statistics]
  Messages RX: 0
  Messages TX: 0
  Drops:       0
  Query sent:  0
```

**分析**:
- ✅ 所有模块初始化成功
- ✅ 本地节点和端点注册正常
- ✅ GraphCache 统计正确
- ⚠️ 使用 `[STUB]` 函数，非真实 dsoftbus API
- ⚠️ 无跨设备 Discovery（stub 模式不支持）

---

### 测试 2: Device 3 - 真实 API 权限失败

**设备**: `ec29004133314d38433031a751c63c00`
**库版本**: `librmw_dsoftbus.so.0.1.0` (2.1M, 2026-01-06)
**结果**: ❌ **失败（权限错误）**

```
[SoftBus Shim] Successfully loaded /system/lib64/platformsdk/libsoftbus_client.z.so
[SoftBus Shim] Loaded symbol: GetLocalNodeDeviceInfo
[SoftBus Shim] Loaded symbol: CreateSessionServer
[SoftBus Shim] Loaded symbol: OpenSession
[SoftBus Shim] All symbols loaded successfully
=================================================
Real DSoftBus Graph Discovery Test
=================================================

[Config] Test duration: 10 seconds

[Step 1] Initializing DiscoveryManager...
[DiscoveryManager] Initializing discovery subsystem
[rmw_dsoftbus] NativeToken: set token_id=671361873 (verify=671361873)
[DiscoveryManager] Got network_id from dsoftbus: f37e6b08ed12a327451117a980c6e3fb446728d544468b3af98e7c88ef386860
[DiscoveryManager] Creating SessionServer: name=com.huawei.dmsdp.ros2_discovery
[DiscoveryManager] CreateSessionServer failed: -426442743
[DiscoveryManager] Hint: need AccessToken permission (ohos.permission.DISTRIBUTED_DATASYNC);
                    native ELF must set NativeToken (/dev/access_token_id) or run via HAP 'com.huawei.ros2_rmw_dsoftbus'
[ERROR] DiscoveryManager initialization failed
```

**分析**:
- ✅ dlopen 成功加载真实 libsoftbus_client.z.so
- ✅ 所有 dsoftbus 符号加载成功
- ✅ 获取真实 network_id 成功 (f37e6b08ed...)
- ❌ CreateSessionServer 失败: `-426442743` (SOFTBUS_PERMISSION_DENIED)
- ❌ NativeToken (671361873) 缺少 DISTRIBUTED_DATASYNC 权限

---

## 🔍 根本原因分析

### 1. NativeToken 权限机制差异

| Method | Token ID | APL Level | Result |
|--------|----------|-----------|--------|
| **当前实现** (ioctl fallback) | 671361873 | 未知 | ❌ 无 DISTRIBUTED_DATASYNC 权限 |
| **Phase 2 成功案例** | 0x1000 (4096) | system_basic | ✅ 有 DISTRIBUTED_DATASYNC 权限 |
| **期望实现** (AccessToken API) | 动态生成 | system_core | ⚠️ 符号未加载，fallback to ioctl |

### 2. 库版本依赖关系

| 库来源 | 大小 | dlopen Shim | 真实API | 权限处理 |
|-------|------|-------------|---------|---------|
| `build-phase3` | 2.2M | ❌ 无 | ❌ Stub | ioctl (671361873) |
| Device 3 | 2.1M | ✅ 有 | ✅ 真实 | ioctl (671361873) + 失败 |
| Phase 2 测试库 | 543K | ✅ 有 | ✅ 真实 | 自定义注入 (0x1000) + 成功 |

### 3. AccessToken API 加载失败

**预期流程**:
```cpp
// src/discovery_manager.cpp:191
bool token_ok = InitializeNativeToken("rmw_discovery_daemon");
if (!token_ok) {
    (void)try_init_native_token();  // Fallback to ioctl
}
```

**实际情况**:
- Device 3 库尝试加载 AccessToken 库但符号未找到
- Fallback 到 ioctl 方法，使用硬编码 token 671361873
- 该 token 没有 DISTRIBUTED_DATASYNC 权限

**根本原因** (`src/native_token.cpp`):
```cpp
// Line 96-102: dlsym 失败
_GetAccessTokenId = (GetAccessTokenId_t)dlsym(handle_native, "GetAccessTokenId");
_SetSelfTokenID = (SetSelfTokenID_t)dlsym(handle_native, "SetSelfTokenID");

if (!_GetAccessTokenId || !_SetSelfTokenID) {
    // ❌ 符号未找到，API 不可用
    return false;
}
```

---

## 💡 解决方案建议

### 方案 1: 修改 APL 等级（推荐）

**修改**: `src/native_token.cpp:299`

```cpp
// 当前
.aplStr = "system_core",  // APL=3

// 改为
.aplStr = "system_basic",  // APL=2 (与 Phase 2 成功案例一致)
```

**优点**:
- 与 Phase 2 成功案例对齐
- 不需要设备重启
- 符合权限最小化原则

**缺点**:
- 需要重新编译库

### 方案 2: 使用环境变量覆盖 Token ID

**步骤**:
```bash
# 查找有权限的 token ID
cat /system/etc/accesstoken/nativetoken.json | grep -A 10 "DISTRIBUTED_DATASYNC"

# 设置环境变量
export RMW_DSOFTBUS_TOKEN_ID=<valid_token_id>

# 运行测试
/data/test/real_dsoftbus_graph_test 10
```

**优点**:
- 不需要重新编译
- 可以快速尝试不同 token

**缺点**:
- 需要找到有效的 token ID

### 方案 3: 设备重启（可能有效）

**步骤**:
```bash
# 重启设备以重新加载权限配置
powershell.exe -Command "hdc -t $DEVICE_ID shell reboot"
```

**优点**:
- 可能解决权限配置未生效问题

**缺点**:
- HDC 连接中断
- 耗时较长

### 方案 4: HAP 封装（生产级方案）

**步骤**:
1. 创建 HAP 应用 `com.huawei.ros2_rmw_dsoftbus`
2. 在 `config.json` 中申请 `DISTRIBUTED_DATASYNC` 权限
3. HAP 内调用 native 测试程序

**优点**:
- 符合 OpenHarmony 规范
- 权限管理正规化

**缺点**:
- 开发周期长
- 需要签名证书

---

## ✅ 已验证功能

### DiscoveryManager

- ✅ 初始化（Stub模式）
- ✅ SessionServer 创建（Stub模式）
- ✅ 本地 network_id 获取
- ✅ 统计数据收集
- ⚠️ CreateSessionServer（真实API，权限阻塞）

### GraphCache

- ✅ 初始化
- ✅ 本地节点注册
- ✅ 端点注册（Publisher）
- ✅ `get_all_nodes()` 查询
- ✅ `get_topic_names_and_types()` 查询
- ✅ `count_publishers()` / `count_subscribers()` 查询
- ⏳ 远程节点注册（需跨设备环境）
- ⏳ 远程端点查询（需跨设备环境）

---

## 📁 相关文件

### 测试程序
- `test/real_dsoftbus_graph_test.cpp` (158 lines)
- `compile_graph_test.sh` - 编译脚本
- `deploy_graph_test.sh` - 部署脚本
- `GRAPH_DISCOVERY_TEST_GUIDE.md` - 测试指南

### 核心实现
- `src/discovery_manager.cpp:186-199` - NativeToken 初始化
- `src/native_token.cpp:262-347` - `InitializeNativeToken()` 实现
- `src/native_token.cpp:184-260` - `try_init_native_token()` 实现

### 部署产物
- `/data/test/real_dsoftbus_graph_test` (179K) - 测试程序
- `/system/lib64/librmw_dsoftbus.so` (2.1M/2.2M) - 主库
- `/lib/ld-linux-aarch64.so.1` → `/lib/ld-musl-aarch64.so.1` - Linker 符号链接

---

## 🎯 下一步行动

### 立即可行（推荐）

1. **尝试方案 1**: 修改 APL 为 "system_basic"
   ```bash
   # 编辑 src/native_token.cpp:299
   vim src/native_token.cpp
   # 改为 .aplStr = "system_basic"

   # 重新编译
   make -f Makefile.aarch64 clean all

   # 部署并测试
   ./deploy_graph_test.sh
   ```

2. **验证权限配置**
   ```bash
   # 检查当前权限配置
   hdc shell cat /system/etc/communication/softbus/softbus_trans_permission.json

   # 检查 token 配置
   hdc shell cat /system/etc/accesstoken/nativetoken.json
   ```

### 长期解决（完整方案）

3. **创建 HAP 封装**（参考 `docs/02_dsoftbus诊断体系/HAP制作与调试报告.md`）

4. **完善 AccessToken API 加载**
   - 调试为何符号加载失败
   - 验证库路径和版本兼容性

---

## 📊 测试矩阵

| 测试场景 | Device 1 | Device 3 | 状态 |
|---------|---------|---------|------|
| 编译部署 | ✅ | ✅ | 完成 |
| Linker 修复 | ✅ | ✅ | 完成 |
| Stub 模式 | ✅ 成功 | ⏸️ | 完成 |
| 真实 API | ⏸️ | ❌ 权限阻塞 | 阻塞中 |
| 单设备验证 | ✅ | ⏸️ | 部分完成 |
| 跨设备验证 | ⏸️ | ⏸️ | 等待权限修复 |

---

## 🔗 参考文档

- `rmw_dsoftbus/test/PHASE2_CROSS_DEVICE_TEST_RESULTS.md` - Phase 2 成功案例 (2026-01-05)
- `docs/02_dsoftbus诊断体系/dsoftbus权限问题快速修复指南.md` - 权限修复指南
- `docs/00_核心技术文档/OPENHARMONY_PERMISSION_SYSTEM_GUIDE.md` - 权限系统详解
- `GRAPH_DISCOVERY_TEST_GUIDE.md` - 原始测试指南

---

**报告生成时间**: 2026-01-14 22:20 UTC
**测试执行人**: Claude (M-DDS ROS2 移植项目)
**状态**: Stub 模式验证完成，真实 API 需权限修复后继续
