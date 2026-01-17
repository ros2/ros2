# 权限配置审核报告 - Phase 2 对比

**审核日期**: 2026-01-15
**目标**: 检查当前代码权限配置是否符合 Phase 2 成功测试的要求
**方法**: 对比 Phase 2 真实测试代码与当前 Ralph Loop Iteration 2 生成的代码

---

## 执行摘要

### ❌ **审核结果: 不合格 - 发现关键权限配置差异**

**关键问题**: 当前代码 APL 级别设置为 `"system_core"`，与 Phase 2 成功案例的 `"system_basic"` **不一致**。

**影响**: 可能导致 CreateSessionServer 失败，无法建立 DSoftBus Session。

**优先级**: 🔴 **P0 - 阻塞性问题**

---

## 一、权限配置对比

### 1.1 Phase 2 成功配置 (✅ 已验证)

**文件**: `test/softbus_permission_bypass.cpp` (2026-01-05 成功测试)

```cpp
NativeTokenInfoParams infoInstance = {
    .dcapsNum = 0,
    .permsNum = 2,
    .aclsNum = 0,
    .dcaps = nullptr,
    .perms = perms,  // 2个权限
    .acls = nullptr,
    .processName = processName,
    .aplStr = "system_basic",  // ⚠️ CRITICAL: Must be system_basic!
};

const char* perms[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC",
    "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
};
```

**关键参数**:
| 参数 | 值 | 说明 |
|------|-----|------|
| APL | `"system_basic"` | **关键成功因素** |
| 权限数量 | 2 | DATASYNC + SOFTBUS_CENTER |
| ACLs | nullptr | 无 ACLs 配置 |
| dcaps | nullptr | 无分布式能力 |

**验证记录**:
```
[Permission] Token ID obtained: 671437365
[Permission] ✅ NativeToken permissions set successfully
```

**测试结果**:
```
CreateSessionServer# ok: ret=0  ✅
OpenSession succeeded: session_id=1  ✅
```

---

### 1.2 当前代码配置 (❌ 与成功案例不一致)

**文件**: `src/native_token.cpp` (lines 281-300)

```cpp
// Define required permissions for DSoftBus Session operations
const char* perms[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC",
    "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER",
    "ohos.permission.ACCESS_SERVICE_DM"  // ⚠️ 额外权限
};

const char* acls[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC"  // ⚠️ ACL 配置
};

NativeTokenInfoParams params = {
    .dcapsNum = 0,
    .permsNum = 3,  // ⚠️ 3个权限 vs Phase 2 的 2个
    .aclsNum = 1,   // ⚠️ 1个 ACL vs Phase 2 的 0个
    .dcaps = nullptr,
    .perms = perms,
    .acls = acls,
    .processName = process_name,
    .aplStr = "system_core",  // ❌ 错误: 应该是 "system_basic"
};
```

**关键参数对比**:
| 参数 | Phase 2 成功 | 当前代码 | 状态 |
|------|-------------|---------|------|
| APL | `"system_basic"` | `"system_core"` | ❌ **不匹配** |
| 权限数量 | 2 | 3 | ⚠️ 多1个 |
| ACLs 数量 | 0 | 1 | ⚠️ 多1个 |
| DATASYNC | ✅ | ✅ | ✅ 匹配 |
| SOFTBUS_CENTER | ✅ | ✅ | ✅ 匹配 |
| ACCESS_SERVICE_DM | ❌ 无 | ✅ | ⚠️ 额外 |

---

## 二、历史验证数据

### 2.1 Phase 2 成功案例文档证据

#### 证据 1: SUCCESSFUL_METHOD_DOCUMENTATION.md
```markdown
.aplStr = "system_basic",  // ✅ 关键: system_basic

**必须**: `"system_basic"`
```

#### 证据 2: GRAPH_DISCOVERY_REAL_TEST_RESULTS.md
```markdown
| **Phase 2 成功案例** | 0x1000 (4096) | system_basic | ✅ 有 DISTRIBUTED_DATASYNC 权限 |

1. **尝试方案 1**: 修改 APL 为 "system_basic"
   # 改为 .aplStr = "system_basic"
```

#### 证据 3: COMPLETE_INVESTIGATION_SUMMARY.md
```markdown
- ✅ 修复 APL 级别: `"normal"` → `"system_basic"`
```

#### 证据 4: DELIVERY_REPORT.md
```markdown
| APL 级别 | `"normal"` (错误) | `"system_basic"` ✅ |
```

#### 证据 5: FINAL_SUMMARY.md
```markdown
- APL 修复: `"normal"` → `"system_basic"`
```

### 2.2 官方 DSoftBus 测试参考

根据 `softbus_permission_bypass.cpp` 注释：
```cpp
/**
 * Reference: dsoftbus/tests/sdk/common/src/softbus_access_token_test.cpp
 *
 * Key differences from previous implementation:
 * - Uses "system_basic" APL instead of "normal" (critical for system service access)
 * - Only requests 2 essential permissions (DATASYNC + SOFTBUS_CENTER)
 * - Matches dsoftbus official test configuration exactly
 */
```

**官方测试结论**:
- ✅ APL 必须是 `"system_basic"`
- ✅ 只需要 2 个权限
- ✅ 不需要 ACLs

---

## 三、APL 级别详细分析

### 3.1 APL 级别定义 (OpenHarmony 权限系统)

| APL 级别 | 数值 | 说明 | 适用场景 |
|---------|------|------|---------|
| `normal` | 1 | 普通应用 | 第三方应用 |
| `system_basic` | 2 | 基础系统应用 | **系统服务、DSoftBus 客户端** ✅ |
| `system_core` | 3 | 核心系统服务 | 系统核心组件 |

### 3.2 为什么 Phase 2 使用 system_basic？

**原因分析**:
1. **DSoftBus 客户端定位**: rmw_dsoftbus 作为 DSoftBus 客户端，应该使用 `system_basic`
2. **官方测试标准**: OpenHarmony dsoftbus 官方测试工具都使用 `system_basic`
3. **权限范围匹配**: `system_basic` 足以访问 DSoftBus Session API
4. **避免过度权限**: `system_core` 权限过高，可能触发额外的安全检查

### 3.3 system_core 的潜在问题

**风险**:
1. ❌ 权限级别不匹配 DSoftBus 客户端定位
2. ❌ 可能触发系统核心服务保护机制
3. ❌ 与成功验证的 Phase 2 配置不一致
4. ❌ 未经设备验证，存在失败风险

---

## 四、额外权限分析

### 4.1 ACCESS_SERVICE_DM 权限

**当前代码添加**:
```cpp
"ohos.permission.ACCESS_SERVICE_DM"  // Device Manager 访问权限
```

**Phase 2 成功案例**: 未使用此权限

**影响评估**:
- ⚠️ **可能无害**: 额外权限通常不会导致失败
- ⚠️ **未验证**: Phase 2 测试未包含此权限，行为未知
- ✅ **建议**: 遵循 Phase 2 最小权限原则，移除此权限

### 4.2 ACL 配置

**当前代码添加**:
```cpp
const char* acls[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC"
};
.aclsNum = 1,
```

**Phase 2 成功案例**:
```cpp
.aclsNum = 0,
.acls = nullptr,
```

**影响评估**:
- ⚠️ **可能无害**: ACL 通常用于权限委托
- ⚠️ **未验证**: Phase 2 未使用 ACL
- ✅ **建议**: 遵循 Phase 2 配置，移除 ACL

---

## 五、修复建议

### 5.1 关键修复 (P0 - 必须修复)

**文件**: `src/native_token.cpp` (lines 280-300)

#### 修改前 (当前代码)
```cpp
const char* perms[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC",
    "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER",
    "ohos.permission.ACCESS_SERVICE_DM"
};

const char* acls[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC"
};

NativeTokenInfoParams params = {
    .dcapsNum = 0,
    .permsNum = 3,
    .aclsNum = 1,
    .dcaps = nullptr,
    .perms = perms,
    .acls = acls,
    .processName = process_name,
    .aplStr = "system_core",  // ❌ 错误
};
```

#### 修改后 (符合 Phase 2)
```cpp
// Define required permissions for DSoftBus Session operations
// Based on Phase 2 successful configuration (2026-01-05)
const char* perms[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC",
    "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
    // Removed: ACCESS_SERVICE_DM (not required by Phase 2)
};

// No ACLs required (Phase 2 verified)
// const char* acls[] = { ... };  // ❌ Removed

NativeTokenInfoParams params = {
    .dcapsNum = 0,
    .permsNum = 2,  // ✅ 2 permissions (Phase 2 verified)
    .aclsNum = 0,   // ✅ No ACLs (Phase 2 verified)
    .dcaps = nullptr,
    .perms = perms,
    .acls = nullptr,  // ✅ Phase 2 verified
    .processName = process_name,
    .aplStr = "system_basic",  // ✅ CRITICAL FIX: system_basic (Phase 2 verified)
};
```

### 5.2 完整修复 Patch

**文件**: `src/native_token.cpp`

```diff
--- a/src/native_token.cpp
+++ b/src/native_token.cpp
@@ -277,26 +277,23 @@ bool InitializeNativeToken(const char* process_name) {
     return false;
   }

-  // Define required permissions for DSoftBus Session operations
+  // Define required permissions for DSoftBus Session operations (Phase 2 verified)
   const char* perms[] = {
       "ohos.permission.DISTRIBUTED_DATASYNC",
       "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER",
-      "ohos.permission.ACCESS_SERVICE_DM"
   };

-  const char* acls[] = {
-      "ohos.permission.DISTRIBUTED_DATASYNC"
-  };
-
   NativeTokenInfoParams params = {
       .dcapsNum = 0,
-      .permsNum = 3,
-      .aclsNum = 1,
+      .permsNum = 2,
+      .aclsNum = 0,
       .dcaps = nullptr,
       .perms = perms,
-      .acls = acls,
+      .acls = nullptr,
       .processName = process_name,
-      .aplStr = "system_core",  // APL=3: system core service level
+      .aplStr = "system_basic",  // APL=2: system basic level (Phase 2 verified)
+      // Reference: test/softbus_permission_bypass.cpp (2026-01-05 success)
+      // Reference: dsoftbus/tests/sdk/common/src/softbus_access_token_test.cpp
   };

   // Step 1: Acquire AccessToken ID
```

---

## 六、验证计划

### 6.1 修复后验证步骤

1. **编译验证**
   ```bash
   ./cross_compile_ohos.sh
   # 检查编译成功
   ```

2. **部署验证**
   ```bash
   # 部署到设备
   hdc -t <device_id> file send librmw_dsoftbus.so.0.1.0 /data/test/
   ```

3. **功能验证**
   ```bash
   # 运行 Phase 2 同款测试
   hdc -t <device_id> shell "cd /data/test && LD_LIBRARY_PATH=/system/lib64 ./phase2_test"

   # 预期输出:
   # [Permission] ✅ NativeToken permissions set successfully
   # CreateSessionServer# ok: ret=0
   # OpenSession succeeded: session_id=1
   ```

### 6.2 验收标准

| 检查项 | 标准 | 验证方法 |
|--------|------|---------|
| APL 级别 | `"system_basic"` | 代码审查 |
| 权限数量 | 2 | 代码审查 |
| ACLs 配置 | nullptr | 代码审查 |
| CreateSessionServer | ret=0 | 设备测试 |
| OpenSession | session_id > 0 | 设备测试 |
| 消息传输 | SendBytes 成功 | 设备测试 |

---

## 七、审核结论

### 7.1 问题汇总

| 问题编号 | 严重性 | 问题描述 | 影响 |
|---------|--------|---------|------|
| PERM-001 | 🔴 P0 | APL 级别错误 (system_core vs system_basic) | 可能导致 CreateSessionServer 失败 |
| PERM-002 | 🟡 P1 | 额外权限 ACCESS_SERVICE_DM | 偏离 Phase 2 验证配置 |
| PERM-003 | 🟡 P1 | 额外 ACL 配置 | 偏离 Phase 2 验证配置 |

### 7.2 修复优先级

1. **P0 (立即修复)**: APL 级别修改为 `"system_basic"`
2. **P1 (建议修复)**: 移除 ACCESS_SERVICE_DM 权限
3. **P1 (建议修复)**: 移除 ACL 配置

### 7.3 最终建议

✅ **强烈建议**: 应用完整修复 Patch，使权限配置完全符合 Phase 2 成功案例

**理由**:
1. Phase 2 配置已在真实设备上验证成功 (2026-01-05)
2. 当前配置与成功案例存在关键差异
3. APL 级别错误是高风险问题
4. 最小权限原则符合安全最佳实践

---

## 八、参考文献

### 8.1 成功案例代码
- `test/softbus_permission_bypass.cpp` - Phase 2 权限配置 (已验证)
- `test/phase2_graph_discovery_with_permission_bypass.cpp` - 成功测试案例

### 8.2 验证文档
- `test/PHASE2_CROSS_DEVICE_TEST_RESULTS.md` - Phase 2 测试结果
- `SUCCESSFUL_METHOD_DOCUMENTATION.md` - 成功方法总结
- `GRAPH_DISCOVERY_REAL_TEST_RESULTS.md` - 图发现测试结果
- `SESSION_SUCCESS_HISTORY.md` - Session 成功历史记录 (本次生成)

### 8.3 官方参考
- OpenHarmony dsoftbus 官方测试: `dsoftbus/tests/sdk/common/src/softbus_access_token_test.cpp`

---

**审核完成时间**: 2026-01-15
**审核员**: Claude Code
**审核方法**: 对比分析 + 历史验证
**审核结论**: ❌ **不合格 - 需要修复 APL 配置**
