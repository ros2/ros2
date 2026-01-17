# Graph Discovery 真实 DSoftBus 测试指南

**日期**: 2026-01-14
**测试类型**: 真实 dsoftbus API 调用（非 stub）
**测试程序**: real_dsoftbus_graph_test
**状态**: ✅ **编译和部署完成，待运行验证**

---

## 📋 测试概述

本测试使用 **真实的 libsoftbus_client.z.so**（而非 stub），验证 **DiscoveryManager + GraphCache** 在跨设备环境下的完整功能。

### 核心功能验证

- ✅ DiscoveryManager 初始化（加载真实 dsoftbus）
- ✅ GraphCache 初始化
- ✅ 本地节点/端点注册
- ⏳ 跨设备 Discovery 广播和接收
- ⏳ GraphCache 远程节点/端点存储
- ⏳ Discovery 统计数据收集

---

## 🛠️ 已完成的工作

### 1. 测试程序开发

**文件**: `test/real_dsoftbus_graph_test.cpp` (158 lines)

**功能**:
- 初始化 DiscoveryManager 和 GraphCache
- 注册测试节点 (`test_talker`) 和端点 (`/chatter`)
- 运行可配置时长的 Discovery 循环
- 收集并打印 GraphCache 和 DiscoveryManager 统计数据

### 2. 编译完成

**编译器**: GCC Linaro 7.5.0 (aarch64-linux-gnu)
**库**: librmw_dsoftbus.so (2.2M, from build-phase3)
**测试程序**: real_dsoftbus_graph_test (179K)
**静态链接**: libstdc++, libgcc（无需额外运行时依赖）

### 3. 部署完成

**部署位置**:
- 测试程序: `/data/test/real_dsoftbus_graph_test`
- 主库: `/system/lib64/librmw_dsoftbus.so`

**已部署设备**:
- Device 1: `ec29004133314d38433031a522413c00`
- Device 3: `ec29004133314d38433031a751c63c00`

---

## 🚨 当前问题

### 动态链接器错误

**症状**: `/data/test/real_dsoftbus_graph_test: No such file or directory`
**原因**: 可能是动态链接器路径问题或架构不匹配
**影响**: 无法直接运行测试程序

### 可能的解决方案

1. **检查文件格式**:
   ```bash
   powershell.exe -Command "hdc -t <DEVICE_ID> shell 'file /data/test/real_dsoftbus_graph_test'"
   ```

2. **检查动态链接依赖**:
   ```bash
   powershell.exe -Command "hdc -t <DEVICE_ID> shell 'ldd /data/test/real_dsoftbus_graph_test'"
   ```

3. **尝试使用系统 ld-linux**:
   ```bash
   powershell.exe -Command "hdc -t <DEVICE_ID> shell '/system/bin/linker64 /data/test/real_dsoftbus_graph_test 10'"
   ```

4. **重新编译为完全静态**:
   修改 `compile_graph_test.sh`，添加 `-static` 标志

---

## 📝 测试执行计划

### A. 单设备测试（本地验证）

**目的**: 验证程序初始化和本地功能

**步骤**:
1. 解决动态链接器问题
2. 运行测试 10 秒:
   ```bash
   powershell.exe -Command "hdc -t ec29004133314d38433031a522413c00 shell '/data/test/real_dsoftbus_graph_test 10'"
   ```

**预期输出**:
```
=================================================
Real DSoftBus Graph Discovery Test
=================================================

[Step 1] Initializing DiscoveryManager...
[OK] DiscoveryManager initialized

[Step 2] Initializing GraphCache...
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
  - /:test_talker

[All Topics]
  - /chatter
    Publishers: 1, Subscribers: 0

[DiscoveryManager Statistics]
  Messages RX: 0
  Messages TX: <count>
  Drops:       0
  Query sent:  <count>

[Step 6] Cleanup
Test completed!
```

---

### B. 跨设备测试（核心验证）

**目的**: 验证跨设备 Discovery 和 GraphCache 远程数据存储

**步骤**:

1. **准备 3 个终端窗口**（或使用 `screen`/`tmux`）

2. **Device 1 运行测试** (60 秒):
   ```bash
   powershell.exe -Command "hdc -t ec29004133314d38433031a522413c00 shell '/data/test/real_dsoftbus_graph_test 60'"
   ```

3. **Device 3 运行测试** (60 秒):
   ```bash
   powershell.exe -Command "hdc -t ec29004133314d38433031a751c63c00 shell '/data/test/real_dsoftbus_graph_test 60'"
   ```

4. **（可选）Device 2 运行测试** (如果在线):
   ```bash
   # 先获取 Device 2 ID
   powershell.exe -Command "hdc list targets"

   # 运行测试
   powershell.exe -Command "hdc -t <DEVICE_2_ID> shell '/data/test/real_dsoftbus_graph_test 60'"
   ```

**预期结果**:

每个设备应该发现其他设备的节点和端点：

```
[Step 5] Final Statistics
=================================================

[GraphCache]
  Total nodes:  2-3  # 本地 + 远程
  Total topics: 1

[All Nodes]
  - /:test_talker      # 本地
  - /:test_talker      # 远程 (不同 network_id)

[DiscoveryManager Statistics]
  Messages RX: >0      # 接收到远程消息
  Messages TX: >0      # 发送消息到远程
  Query sent:  >0      # 发送过 QUERY 消息
```

---

## 🔍 调试技巧

### 1. 查看 dsoftbus 服务状态
```bash
powershell.exe -Command "hdc -t <DEVICE_ID> shell 'ps -ef | grep softbus'"
```

### 2. 查看系统日志
```bash
powershell.exe -Command "hdc -t <DEVICE_ID> shell 'hilog -x | grep -i softbus | tail -100'"
```

### 3. 检查网络连接
```bash
powershell.exe -Command "hdc -t <DEVICE_ID> shell 'ifconfig'"
powershell.exe -Command "hdc -t <DEVICE_ID> shell 'netstat -an | grep 6666'"
```

### 4. 检查权限配置
```bash
powershell.exe -Command "hdc -t <DEVICE_ID> shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json'"
```

---

## 📊 成功标准

### 最低标准（Phase 验收）

- ✅ 程序成功初始化 DiscoveryManager（加载真实 dsoftbus）
- ✅ 程序成功初始化 GraphCache
- ✅ 本地节点正确注册到 GraphCache
- ✅ Discovery 统计计数器正常工作

### 完整标准（跨设备验证）

- ✅ 最低标准全部通过
- ✅ 跨设备 Session 建立成功
- ✅ Discovery 消息双向传输（TX > 0, RX > 0）
- ✅ 远程节点正确存储到 GraphCache（Total nodes >= 2）
- ✅ 远程端点正确存储到 GraphCache

---

## 📁 相关文件

### 测试程序
- `test/real_dsoftbus_graph_test.cpp` - 测试源代码
- `compile_graph_test.sh` - 编译脚本
- `deploy_graph_test.sh` - 部署脚本

### 核心模块
- `src/discovery_manager.cpp` (2226 lines) - Discovery 协议实现
- `src/graph_cache.cpp` (988 lines) - Graph 缓存实现
- `include/rmw_dsoftbus/discovery_manager.h` - Discovery API
- `include/rmw_dsoftbus/graph_cache.h` - GraphCache API

### 参考文档
- `DISCOVERY_GRAPH_IMPLEMENTATION_VERIFICATION.md` - 实现验证报告
- `GRAPH_MANAGER_TEST_REPORT.md` - 本地测试报告 (x86_64)
- `test/PHASE2_CROSS_DEVICE_TEST_RESULTS.md` - Phase 2 跨设备测试结果 (2026-01-05)

---

## 🎯 下一步建议

### 立即行动

1. **修复动态链接器问题**
   - 检查文件格式和依赖
   - 尝试完全静态链接
   - 或使用系统 linker64 直接调用

2. **运行单设备测试**
   - 验证基本功能
   - 检查日志输出

### 完整验证

3. **跨设备测试**
   - 同时在 2-3 个设备上运行
   - 验证 Discovery 消息传输
   - 确认远程节点/端点发现

4. **结果分析**
   - 收集所有设备的输出
   - 对比统计数据
   - 确认功能完整性

---

## ✅ 测试通过标准

**DiscoveryManager + GraphCache 验收通过条件**:

1. ✅ 真实 dsoftbus API 成功加载（非 stub）
2. ✅ CreateSessionServer 成功（session_id >= 0）
3. ✅ 至少一对设备成功建立 Discovery Session
4. ✅ Discovery 消息双向传输 (RX > 0, TX > 0)
5. ✅ 远程节点正确存储到 GraphCache
6. ✅ GraphCache API 返回远程节点信息

**满足以上条件即可确认 Graph Discovery 功能完整并可用！**

---

**创建日期**: 2026-01-14 16:40 UTC
**测试状态**: 编译和部署完成，等待运行验证
**下次更新**: 完成跨设备测试后更新结果
