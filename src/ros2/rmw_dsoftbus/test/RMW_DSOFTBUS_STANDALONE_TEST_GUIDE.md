# RMW DSoftBus Standalone Test Guide

**目的**: 在 rk3588s 开发板上测试 rmw_dsoftbus 核心功能，不依赖 ROS2 环境

**要求**:
- ✅ 真实 dsoftbus API（无 stub/mock）
- ✅ 直接调用 rmw_dsoftbus 库
- ✅ 跨设备通信测试

---

## 快速开始

### 方法 1: 自动化脚本（推荐）

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus/test
chmod +x deploy_and_test.sh
./deploy_and_test.sh
```

脚本会自动：
1. 编译测试程序
2. 检测设备
3. 部署到 rk3588s
4. 运行测试

### 方法 2: 手动步骤

#### Step 1: 编译测试程序

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus/test
make -f Makefile.standalone clean all
```

输出：
- `build-standalone/rmw_dsoftbus_standalone_test` (测试程序)

#### Step 2: 准备文件

```bash
mkdir -p /mnt/c/tmp/hdc_transfer
cp build-standalone/rmw_dsoftbus_standalone_test /mnt/c/tmp/hdc_transfer/
cp ../build-aarch64/lib/librmw_dsoftbus.so.0.1.0 /mnt/c/tmp/hdc_transfer/
```

#### Step 3: 获取设备 ID

```bash
powershell.exe -Command "hdc list targets"
```

示例输出：
```
ec29004133314d38433031a522413c00    device
ec29004133314d38433031a5544f3c00    device
```

#### Step 4: 部署到设备

```bash
# 设置设备 ID
DEVICE_ID=ec29004133314d38433031a522413c00

# 创建目录
powershell.exe -Command "hdc -t $DEVICE_ID shell 'mkdir -p /data/test'"

# 部署测试程序
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\rmw_dsoftbus_standalone_test /data/test/"

# 部署库
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0 /data/"

# 设置权限
powershell.exe -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/test/rmw_dsoftbus_standalone_test'"
```

#### Step 5: 运行测试

**单设备测试**（测试初始化和 API 调用）:

```bash
# Publisher 模式
powershell.exe -Command "hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=pub'"

# Subscriber 模式
powershell.exe -Command "hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=sub'"
```

**跨设备测试**（测试真实通信）:

Terminal 1 - Device 1 (Publisher):
```bash
DEVICE1_ID=ec29004133314d38433031a522413c00
powershell.exe -Command "hdc -t $DEVICE1_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=pub --topic=/test'"
```

Terminal 2 - Device 2 (Subscriber):
```bash
DEVICE2_ID=ec29004133314d38433031a5544f3c00
powershell.exe -Command "hdc -t $DEVICE2_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=sub --topic=/test'"
```

---

## 测试程序功能

### 支持的参数

| 参数 | 说明 | 示例 |
|------|------|------|
| `--mode=pub` | Publisher 模式 | `--mode=pub` |
| `--mode=sub` | Subscriber 模式 | `--mode=sub` |
| `--topic=NAME` | Topic 名称 | `--topic=/chatter` |
| `--help` | 显示帮助 | `--help` |

### 测试内容

测试程序会依次执行：

1. **RMW 初始化**
   - 调用 `rmw_init_options_init()`
   - 调用 `rmw_init()`
   - 验证 context 创建成功

2. **节点创建**
   - 调用 `rmw_create_node()`
   - 验证节点创建成功

3. **Publisher/Subscriber 创建**
   - Publisher 模式：调用 `rmw_create_publisher()`
   - Subscriber 模式：调用 `rmw_create_subscription()`

4. **消息收发**
   - Publisher: 发布 10 条消息
   - Subscriber: 接收消息

5. **Graph Discovery**
   - 调用 `rmw_get_node_names()`
   - 显示发现的节点列表

6. **清理**
   - 销毁 Publisher/Subscriber
   - 销毁节点
   - 关闭 context

---

## 预期输出

### 成功案例

```
╔════════════════════════════════════════════════════════════╗
║   RMW DSoftBus Standalone Test                            ║
║   Mode: Publisher                                          ║
║   Topic: /chatter                                          ║
╚════════════════════════════════════════════════════════════╝

[Step 1] Initializing RMW...
  Implementation: rmw_dsoftbus
  ✅ Init options created
  ✅ Context initialized

[Step 2] Creating node...
  ✅ Node created: publisher

[Step 3] Creating publisher...
  ✅ Publisher created on topic: /chatter

[Step 4] Publishing messages...
  [0] Publishing: Hello RMW DSoftBus 0
  [1] Publishing: Hello RMW DSoftBus 1
  ...

[Step 5] Testing Graph Discovery...
  ✅ Discovered 1 nodes:
     - /publisher

[Cleanup] Shutting down...
  ✅ Node destroyed
  ✅ Context shutdown
  ✅ Context finalized
  ✅ Init options finalized

╔════════════════════════════════════════════════════════════╗
║   Test completed successfully                              ║
╚════════════════════════════════════════════════════════════╝
```

### 失败案例

如果出现错误，会显示：

```
[Step 1] Initializing RMW...
  ❌ Failed to init context: 1
```

---

## 故障排查

### 问题 1: 找不到 librmw_dsoftbus.so

**症状**:
```
error while loading shared libraries: librmw_dsoftbus.so.0
```

**解决**:
```bash
# 确保设置了 LD_LIBRARY_PATH
LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=pub

# 或者将库复制到系统目录
powershell.exe -Command "hdc -t $DEVICE_ID shell 'cp /data/librmw_dsoftbus.so.0.1.0 /system/lib64/'"
```

### 问题 2: 权限不足

**症状**:
```
Permission denied
```

**解决**:
```bash
powershell.exe -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/test/rmw_dsoftbus_standalone_test'"
```

### 问题 3: dsoftbus 服务未运行

**症状**:
```
Failed to init context: 1
```

**检查**:
```bash
# 检查 dsoftbus 服务
powershell.exe -Command "hdc -t $DEVICE_ID shell 'ps -ef | grep softbus'"

# 检查日志
powershell.exe -Command "hdc -t $DEVICE_ID shell 'hilog | grep -i softbus'"
```

### 问题 4: 权限配置未生效

**症状**:
CreateSessionServer 返回错误

**解决**:
确保已部署权限配置文件：
```bash
powershell.exe -Command "hdc -t $DEVICE_ID file send config/softbus_trans_permission.json /system/etc/communication/softbus/"
powershell.exe -Command "hdc -t $DEVICE_ID shell 'reboot'"
```

---

## 验证清单

测试通过应满足：

- [ ] 测试程序成功编译（aarch64）
- [ ] 成功部署到 rk3588s 设备
- [ ] RMW 初始化成功
- [ ] 节点创建成功
- [ ] Publisher/Subscriber 创建成功
- [ ] Graph Discovery 返回节点列表
- [ ] 跨设备能够发现对方节点（如有多设备）
- [ ] 消息能够发送（Publisher）
- [ ] 消息能够接收（Subscriber，如有多设备）
- [ ] 清理过程无错误

---

## 日志收集

### 收集设备日志

```bash
# 运行测试并保存日志
powershell.exe -Command "hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=pub'" > test_output.txt 2>&1

# 收集 hilog
powershell.exe -Command "hdc -t $DEVICE_ID shell 'hilog | grep -i rmw'" > rmw_hilog.txt
```

### 检查关键信息

```bash
# 检查初始化
grep "Initializing RMW" test_output.txt

# 检查错误
grep "❌" test_output.txt

# 检查成功标记
grep "✅" test_output.txt
```

---

## 下一步

测试成功后，可以：

1. **集成 ROS2**: 将 rmw_dsoftbus 集成到 ROS2 环境
2. **性能测试**: 测试消息吞吐量和延迟
3. **压力测试**: 长时间运行和大量消息测试
4. **多节点测试**: 测试多个 Publisher/Subscriber

---

**最后更新**: 2026-01-17
**维护者**: Claude Code
**文档位置**: `/home/jiusi/M-DDS/rmw_dsoftbus/test/RMW_DSOFTBUS_STANDALONE_TEST_GUIDE.md`
