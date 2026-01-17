# Phase 3 诊断 - 快速开始指南
**用时**: 5分钟完成快速诊断，15分钟完成完整诊断

---

## 30秒快速概览

**问题**: Device 1 (Server)无法接收Device 2 (Client)的连接
- Server能创建SessionServer，但connectCnt=0
- 没有OnSessionOpened回调
- 需要诊断是Client问题还是Server问题

**解决方案**: 执行诊断脚本，根据输出判断问题根因

---

## 立即执行（现在就做）

### 步骤1: 进入项目目录
```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus
```

### 步骤2: 执行快速诊断
```bash
# 加载诊断工具
source ./DIAGNOSTIC_COMMANDS.sh

# 执行快速诊断（5分钟）
quick_diagnosis
```

### 步骤3: 阅读输出结果

诊断脚本会输出：

```
========================================
1. 收集Server端日志 (Device 1)
========================================
[✓] Server日志已保存到: /tmp/server_log.txt
[INFO] 日志行数: 30
[INFO] 关键搜索词:
[Test] Status: connectCnt=0, outbound=-1, inbound=-1

========================================
6. 检查OpenSession返回值
========================================
[✗] Client的OpenSession返回失败
   OR
[✓] Client的OpenSession返回有效ID (>0)

========================================
7. 检查OnSessionOpened回调
========================================
[✗] Server的OnSessionOpened未被调用
   OR
[✓] Server的OnSessionOpened被调用

========================================
10. 诊断总结
========================================
[✓] ✓ Client的OpenSession返回有效ID
[✗] ✗ Server的OnSessionOpened未被调用
[✗] ✗ connectCnt=0, 没有建立连接

[INFO] 问题数量: 2
[!] 发现多个问题，需要全面诊断
```

---

## 快速判断问题位置

根据诊断输出，找到对应的问题类型：

### 情况1: OpenSession返回失败 ❌
```
[✗] Client的OpenSession返回失败
[✗] Server的OnSessionOpened未被调用
[✗] connectCnt=0, 没有建立连接
```

**问题位置**: Client端参数错误
**最可能原因**:
- NetworkID不匹配
- SessionName拼写错误
- 权限配置不支持

**下一步**:
```bash
# 查看详细信息
verify_network_ids
verify_session_names
```

---

### 情况2: OpenSession成功，OnSessionOpened未被调用 ✓❌
```
[✓] Client的OpenSession返回有效ID (>0)
[✗] Server的OnSessionOpened未被调用
[✗] connectCnt=0, 没有建立连接
```

**问题位置**: Server端回调机制有缺陷
**最可能原因**:
- OnSessionOpened回调未被正确注册
- dsoftbus服务未通知Server
- Session ID追踪机制缺失

**下一步**:
```bash
# 执行完整诊断
full_diagnosis

# 或直接查看日志
cat /tmp/server_log.txt | grep -i "onsession\|callback\|session"
```

---

### 情况3: 所有检查都通过 ✓✓✓
```
[✓] Client的OpenSession返回有效ID
[✓] Server的OnSessionOpened被调用
[✓] connectCnt > 0, 有连接
```

**问题位置**: 问题可能已解决或在更深层
**下一步**:
```bash
# 执行完整诊断
full_diagnosis

# 分析Session ID追踪
analyze_session_tracking
```

---

## 执行完整诊断（15分钟）

如果快速诊断不清楚，执行完整诊断：

```bash
# 加载诊断工具（如果还没有）
source ./DIAGNOSTIC_COMMANDS.sh

# 执行完整诊断
full_diagnosis
```

完整诊断会：
1. ✅ 收集Server日志
2. ✅ 收集Client日志
3. ✅ 验证networkId匹配
4. ✅ 验证sessionName匹配
5. ✅ 检查OpenSession返回值
6. ✅ 检查OnSessionOpened回调
7. ✅ 检查连接计数
8. ✅ 分析Session ID追踪
9. ✅ 生成诊断总结

---

## 查看详细日志

诊断脚本保存的日志文件：

```bash
# Server日志
cat /tmp/server_log.txt

# Client日志
cat /tmp/client2_log.txt

# 搜索特定信息
grep "OpenSession" /tmp/client2_log.txt
grep "OnSessionOpened" /tmp/server_log.txt
grep "connectCnt" /tmp/server_log.txt
```

---

## 常见输出模式

### 模式1: 完全失败（最可能）
```
✗ OpenSession: NO (or error)
✗ OnSessionOpened: NO
✗ connectCnt: 0
→ 问题在Client或权限
```

### 模式2: 部分成功
```
✓ OpenSession: YES
✗ OnSessionOpened: NO
✗ connectCnt: 0
→ 问题在Server回调或ID映射
```

### 模式3: 全部成功
```
✓ OpenSession: YES
✓ OnSessionOpened: YES
✓ connectCnt: >0
→ 问题可能已解决，检查消息传输
```

---

## 诊断工具参考

快速诊断脚本提供的主要函数：

```bash
# 信息收集
collect_server_logs          # 获取Server端日志
collect_client_logs          # 获取Client端日志
collect_device3_logs         # 获取Device 3日志（如果有）

# 验证
verify_network_ids           # 检查networkId匹配
verify_session_names         # 检查sessionName匹配

# 检查
check_opensession_result     # 检查OpenSession返回值
check_onsessionopened_callback   # 检查回调是否被触发
check_connection_count       # 检查connectCnt值

# 分析
analyze_session_tracking     # 分析Session ID追踪
generate_summary             # 生成诊断总结

# 完整诊断
quick_diagnosis              # 快速诊断（5分钟）
full_diagnosis               # 完整诊断（15分钟）

# 帮助
show_help                    # 显示所有命令
```

---

## 自定义诊断

根据需要运行单个诊断：

```bash
# 只收集日志
collect_server_logs
collect_client_logs

# 只检查关键项
check_opensession_result
check_onsessionopened_callback
check_connection_count

# 只查看某项
verify_network_ids
analyze_session_tracking
```

---

## 后续步骤

### 基于诊断结果：

1. **如果发现Client问题** (OpenSession失败)
   - [ ] 查看Device 2/3的测试程序源代码
   - [ ] 修正networkId或sessionName参数
   - [ ] 重新编译部署
   - [ ] 重新运行诊断

2. **如果发现Server问题** (OnSessionOpened未被调用)
   - [ ] 查看rmw_dsoftbus/src/listener.cpp
   - [ ] 检查回调函数注册代码
   - [ ] 添加调试日志
   - [ ] 重新编译部署
   - [ ] 重新运行诊断

3. **如果问题不清楚** (诊断结果不确定)
   - [ ] 运行完整诊断: `full_diagnosis`
   - [ ] 查看PHASE3_SESSION_TRACKING_ACTION_PLAN.md
   - [ ] 按照更详细的步骤逐项排查

---

## 获取帮助

### 诊断工具使用
```bash
show_help     # 显示所有可用命令
```

### 查看完整文档
- `PHASE3_DIAGNOSTICS_SUMMARY.md` - 完整诊断总结
- `PHASE3_SESSION_TRACKING_ACTION_PLAN.md` - 详细行动计划
- `DEVICE1_SERVER_DIAGNOSTIC_REPORT.md` - Server端诊断报告

### 查看相关代码
- `rmw_dsoftbus/src/listener.cpp` - Server实现
- `rmw_dsoftbus/src/publisher.cpp` - Client实现

---

## 时间估计

| 步骤 | 时间 |
|------|------|
| 快速诊断 | 5分钟 |
| 理解结果 | 5分钟 |
| 识别问题 | 5分钟 |
| **快速诊断总计** | **15分钟** |
| 完整诊断 | 10分钟 |
| 深入分析 | 10分钟 |
| **完整诊断总计** | **25分钟** |

---

## 现在就开始！

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus
source ./DIAGNOSTIC_COMMANDS.sh
quick_diagnosis
```

预期输出中会显示问题的根本原因。根据输出结果，参考上面的"快速判断问题位置"部分确定后续行动。

---

**最后更新**: 2026-01-15
**文件位置**: `/home/jiusi/M-DDS/rmw_dsoftbus/QUICK_START_DIAGNOSIS.md`
