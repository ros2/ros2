# RMW DSoftBus 1:N 路由和 QoS 手动测试指南

**测试目标**:
- ✅ 验证 1:N 路由功能（一个 Publisher → 多个 Subscriber）
- ✅ 验证 QoS 配置（RELIABLE vs BEST_EFFORT）
- ✅ 真实 dsoftbus API（无 stub/mock）
- ✅ 无 ROS2 依赖

**测试设备**: 2-3 台 rk3588s 开发板

---

## 快速开始

### 设备 ID 参考

```bash
# 查看设备列表
powershell.exe -Command "hdc list targets"
```

示例输出：
```
ec29004133314d38433031a522413c00    # Device 1
ec29004133314d38433031a5544f3c00    # Device 2
```

### 设置环境变量

```bash
# 设备 ID
export DEVICE1=ec29004133314d38433031a522413c00
export DEVICE2=ec29004133314d38433031a5544f3c00
```

---

## 测试场景 1: 1:1 基础通信测试

**目的**: 验证基本的 Publisher → Subscriber 通信

### Terminal 1 - Device 1 (Publisher)

```bash
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --topic=/test --count=30'"
```

**预期输出**:
```
╔════════════════════════════════════════════════════════════╗
║   RMW DSoftBus 1:N Routing & QoS Test                     ║
╚════════════════════════════════════════════════════════════╝
  Mode:         Publisher
  Topic:        /test
  QoS:          RELIABLE (depth=10)
  Message Count: 30
════════════════════════════════════════════════════════════

[Info] RMW Implementation: rmw_dsoftbus

[QoS] Configured:
  - History: KEEP_LAST
  - Depth: 10
  - Reliability: RELIABLE
  - Durability: VOLATILE

[Publisher] Starting...

Waiting 5 seconds for subscribers to connect...
  5...
  4...
  3...
  2...
  1...

[Publishing] Sending 30 messages...

[  1] ✅ Published: Message #0 from Publisher (QoS: RELIABLE)
[  2] ✅ Published: Message #1 from Publisher (QoS: RELIABLE)
...
```

### Terminal 2 - Device 2 (Subscriber)

```bash
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1 --topic=/test'"
```

**预期输出**:
```
╔════════════════════════════════════════════════════════════╗
║   RMW DSoftBus 1:N Routing & QoS Test                     ║
╚════════════════════════════════════════════════════════════╝
  Mode:         Subscriber 1
  Topic:        /test
  QoS:          RELIABLE (depth=10)
════════════════════════════════════════════════════════════

[Info] RMW Implementation: rmw_dsoftbus

[Subscriber 1] Starting...

[Listening] Waiting for messages (timeout: 30s)...

[  1] ✅ Received: Message #0 from Publisher (QoS: RELIABLE)
[  2] ✅ Received: Message #1 from Publisher (QoS: RELIABLE)
...

[Subscriber 1] Statistics:
  Total received: 30 messages
  Runtime: 10 seconds
  Status: ✅ PASS
```

---

## 测试场景 2: 1:N 路由测试

**目的**: 验证一个 Publisher 能够同时发送到多个 Subscriber

### Terminal 1 - Device 1 (Publisher)

```bash
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --topic=/multicast --count=50'"
```

### Terminal 2 - Device 2 (Subscriber 1)

```bash
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1 --topic=/multicast'"
```

### Terminal 3 - Device 1 (Subscriber 2，同一设备)

**注意**: 可以在同一设备上运行多个 Subscriber

```bash
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub2 --topic=/multicast'"
```

### 验证点

**1:N 路由成功标准**:
- [ ] Publisher 发送 50 条消息
- [ ] Subscriber 1 接收到 50 条消息
- [ ] Subscriber 2 接收到 50 条消息
- [ ] 所有 Subscriber 接收到的消息内容一致

---

## 测试场景 3: QoS RELIABLE vs BEST_EFFORT

**目的**: 验证不同 QoS 策略的行为差异

### Test 3.1 - RELIABLE QoS

**Terminal 1** (Publisher):
```bash
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --qos=reliable --depth=20 --count=40'"
```

**Terminal 2** (Subscriber):
```bash
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1 --qos=reliable --depth=20'"
```

**预期**: 所有 40 条消息都应被接收

### Test 3.2 - BEST_EFFORT QoS

**Terminal 1** (Publisher):
```bash
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --qos=best-effort --count=40'"
```

**Terminal 2** (Subscriber):
```bash
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1 --qos=best-effort'"
```

**预期**: 可能丢失部分消息（但 dsoftbus 默认 RELIABLE，实际可能全收到）

---

## 测试场景 4: History Depth 测试

**目的**: 验证 history depth 限制

### Test 4.1 - Small Depth (depth=5)

**Publisher** (快速发送 20 条消息):
```bash
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --depth=5 --count=20'"
```

**Subscriber** (延迟启动，10 秒后启动):
```bash
sleep 10
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1 --depth=5'"
```

**预期**: Subscriber 可能只收到最后 5 条消息（受 depth 限制）

### Test 4.2 - Large Depth (depth=50)

```bash
# Publisher
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --depth=50 --count=20'"

# Subscriber (延迟启动)
sleep 10
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1 --depth=50'"
```

**预期**: Subscriber 应接收到所有 20 条消息

---

## 参数说明

| 参数 | 说明 | 示例 |
|------|------|------|
| `--mode=pub` | Publisher 模式 | `--mode=pub` |
| `--mode=sub1` | Subscriber 1 模式 | `--mode=sub1` |
| `--mode=sub2` | Subscriber 2 模式 | `--mode=sub2` |
| `--mode=sub3` | Subscriber 3 模式 | `--mode=sub3` |
| `--topic=NAME` | Topic 名称 | `--topic=/chatter` |
| `--qos=reliable` | RELIABLE QoS | `--qos=reliable` |
| `--qos=best-effort` | BEST_EFFORT QoS | `--qos=best-effort` |
| `--depth=N` | History depth | `--depth=20` |
| `--count=N` | 消息数量（Publisher） | `--count=50` |

---

## 验证清单

### 1:N 路由测试

- [ ] Publisher 能成功创建
- [ ] 多个 Subscriber 能同时订阅同一 Topic
- [ ] 所有 Subscriber 都能接收到消息
- [ ] 消息内容在所有 Subscriber 上一致
- [ ] 消息序号连续（无丢失）

### QoS 测试

- [ ] RELIABLE QoS: 所有消息都被接收
- [ ] BEST_EFFORT QoS: 允许丢失但大部分接收
- [ ] History depth 生效: 限制队列大小
- [ ] 不同 QoS 参数能正常工作

---

## 故障排查

### 问题 1: 找不到库

**症状**:
```
Error loading shared library librmw_dsoftbus.so.0
```

**解决**:
```bash
# 检查库是否部署
powershell.exe -Command "hdc -t $DEVICE1 shell 'ls -lh /data/librmw_dsoftbus.so.0*'"

# 创建符号链接
powershell.exe -Command "hdc -t $DEVICE1 shell 'cd /data && ln -sf librmw_dsoftbus.so.0.1.0 librmw_dsoftbus.so.0'"
```

### 问题 2: Subscriber 收不到消息

**原因可能是**:
1. Publisher 和 Subscriber 启动顺序问题
2. Topic 名称不匹配
3. QoS 不兼容
4. 网络连接问题

**调试**:
```bash
# 检查 hilog
powershell.exe -Command "hdc -t $DEVICE1 shell 'hilog | grep -i rmw'"

# 检查 dsoftbus 日志
powershell.exe -Command "hdc -t $DEVICE1 shell 'hilog | grep -i softbus'"
```

### 问题 3: QoS 不生效

**检查**:
```bash
# 查看测试程序输出中的 QoS 配置
# 应显示正确的 RELIABLE/BEST_EFFORT
```

---

## 测试数据收集

### 收集日志

**Publisher 日志**:
```bash
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --count=30'" > publisher_log.txt 2>&1
```

**Subscriber 日志**:
```bash
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1'" > subscriber_log.txt 2>&1
```

### 性能指标

记录以下数据：
- 消息发送速率（msg/s）
- 消息接收延迟（ms）
- 丢包率（%）
- 内存使用（MB）

---

## 完整测试脚本

创建 `run_1n_test.sh`:

```bash
#!/bin/bash

DEVICE1=ec29004133314d38433031a522413c00
DEVICE2=ec29004133314d38433031a5544f3c00

echo "════════════════════════════════════════"
echo "  1:N Routing Test"
echo "════════════════════════════════════════"
echo ""

# Start Subscriber 1 on Device 2
echo "[1/3] Starting Subscriber 1 on Device 2..."
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1 --topic=/test'" > sub1_log.txt 2>&1 &
SUB1_PID=$!
sleep 2

# Start Subscriber 2 on Device 1
echo "[2/3] Starting Subscriber 2 on Device 1..."
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub2 --topic=/test'" > sub2_log.txt 2>&1 &
SUB2_PID=$!
sleep 2

# Start Publisher on Device 1
echo "[3/3] Starting Publisher on Device 1..."
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --topic=/test --count=30'" > pub_log.txt 2>&1

echo ""
echo "Test completed. Check logs:"
echo "  - pub_log.txt"
echo "  - sub1_log.txt"
echo "  - sub2_log.txt"

# Kill subscribers
kill $SUB1_PID $SUB2_PID 2>/dev/null
```

---

## 测试矩阵

| 测试 | Publisher | Subscriber 1 | Subscriber 2 | Topic | QoS | 预期结果 |
|------|-----------|--------------|--------------|-------|-----|----------|
| 1:1 基础 | Device 1 | Device 2 | - | /test | RELIABLE | 30/30 消息 |
| 1:2 路由 | Device 1 | Device 2 | Device 1 | /test | RELIABLE | 各 30/30 |
| 1:3 路由 | Device 1 | Device 2 | Device 3 | /test | RELIABLE | 各 30/30 |
| QoS RELIABLE | Device 1 | Device 2 | - | /qos | RELIABLE | 40/40 |
| QoS BEST_EFFORT | Device 1 | Device 2 | - | /qos | BEST_EFFORT | ≈40/40 |
| Depth Small | Device 1 | Device 2 (延迟) | - | /depth | depth=5 | ≤5 |
| Depth Large | Device 1 | Device 2 (延迟) | - | /depth | depth=50 | 20/20 |

---

## 关键命令速查

### 部署

```bash
# 编译
cd /home/jiusi/M-DDS/rmw_dsoftbus/test
make -f Makefile.standalone pubsub

# 准备文件
cp build-standalone/rmw_pubsub_real_test /mnt/c/tmp/hdc_transfer/

# 部署到设备
powershell.exe -Command "hdc -t $DEVICE1 file send C:\tmp\hdc_transfer\rmw_pubsub_real_test /data/test/"
powershell.exe -Command "hdc -t $DEVICE1 shell 'chmod +x /data/test/rmw_pubsub_real_test'"
```

### 运行

```bash
# Publisher
powershell.exe -Command "hdc -t $DEVICE1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub'"

# Subscriber
powershell.exe -Command "hdc -t $DEVICE2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1'"
```

### 调试

```bash
# 查看实时日志
powershell.exe -Command "hdc -t $DEVICE1 shell 'hilog | grep rmw'"

# 检查进程
powershell.exe -Command "hdc -t $DEVICE1 shell 'ps -ef | grep rmw'"

# 杀死进程
powershell.exe -Command "hdc -t $DEVICE1 shell 'killall rmw_pubsub_real_test'"
```

---

## 预期结果

### 成功标准

- ✅ Publisher 成功发送所有消息
- ✅ 所有 Subscriber 接收到消息
- ✅ 消息数量匹配（RELIABLE QoS）
- ✅ 消息内容正确
- ✅ 无崩溃或错误

### 性能目标

| 指标 | 目标 | 验证方法 |
|------|------|----------|
| 消息延迟 | < 100ms | 对比时间戳 |
| 吞吐量 | > 100 msg/s | 计算发送速率 |
| 丢包率 (RELIABLE) | 0% | 对比发送/接收数 |
| 内存占用 | < 50MB | 查看进程内存 |

---

## 下一步

测试通过后：

1. **记录结果** - 保存所有日志和统计数据
2. **性能测试** - 测试大量消息和高频率
3. **压力测试** - 长时间运行和多节点
4. **集成测试** - 与 ROS2 环境集成

---

**创建时间**: 2026-01-17
**测试程序**: `/home/jiusi/M-DDS/rmw_dsoftbus/test/rmw_pubsub_real_test`
**部署位置**: `/data/test/rmw_pubsub_real_test` (rk3588s)
