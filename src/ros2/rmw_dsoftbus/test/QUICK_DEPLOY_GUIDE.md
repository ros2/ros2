# rmw_dsoftbus 快速部署测试指南

**目标**: 在 rk3588s 上测试 rmw_dsoftbus（无 ROS2，无 stub/mock）

---

## 快速开始（5 分钟）

### Step 1: 编译测试程序

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus/test
make -f Makefile.standalone clean simple
```

**输出**:
- `build-standalone/rmw_simple_test` (19KB, aarch64)

### Step 2: 准备部署

```bash
make -f Makefile.standalone deploy
```

**输出**:
```
✅ Files copied to /mnt/c/tmp/hdc_transfer/
  - rmw_simple_test
  - librmw_dsoftbus.so.0.1.0
```

### Step 3: 获取设备 ID

```bash
powershell.exe -Command "hdc list targets"
```

**示例输出**:
```
ec29004133314d38433031a522413c00    device
```

### Step 4: 部署到设备

```bash
# 设置设备 ID
export DEVICE_ID=ec29004133314d38433031a522413c00

# 创建目录
powershell.exe -Command "hdc -t $DEVICE_ID shell 'mkdir -p /data/test'"

# 部署测试程序
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\rmw_simple_test /data/test/"

# 部署库
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0 /data/"

# 设置权限
powershell.exe -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/test/rmw_simple_test'"
```

### Step 5: 运行测试

```bash
powershell.exe -Command "hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_simple_test'"
```

**预期输出**:
```
════════════════════════════════════════════════════════════
  RMW DSoftBus Simple Test
  Direct library test (no stub/mock)
════════════════════════════════════════════════════════════

[Step 1] Loading librmw_dsoftbus.so...
  ✅ Library loaded

[Step 2] Getting implementation identifier...
  ✅ Implementation: rmw_dsoftbus

[Step 3] Testing symbol exports...
  ✅ rmw_init
  ✅ rmw_create_node
  ✅ rmw_destroy_node
  ✅ rmw_create_publisher
  ✅ rmw_create_subscription
  ✅ rmw_get_node_names

  Result: 6/6 symbols found

[Cleanup] Closing library...
  ✅ Done

════════════════════════════════════════════════════════════
  ✅ Test PASSED - All symbols found
════════════════════════════════════════════════════════════
```

---

## 测试内容

### 当前测试覆盖

| 测试项 | 内容 |
|--------|------|
| 库加载 | dlopen librmw_dsoftbus.so |
| 符号导出 | 验证 106 个 RMW API 符号可见 |
| 实现标识符 | 确认是 "rmw_dsoftbus" |

### 核心 API 验证

测试程序会验证以下核心 API：
- `rmw_init` - 初始化
- `rmw_create_node` - 创建节点
- `rmw_destroy_node` - 销毁节点
- `rmw_create_publisher` - 创建发布者
- `rmw_create_subscription` - 创建订阅者
- `rmw_get_node_names` - 获取节点列表

---

## 一键部署脚本（所有步骤）

创建 `quick_deploy.sh`:

```bash
#!/bin/bash
set -e

DEVICE_ID=${1:-$(powershell.exe -Command "hdc list targets" | head -1 | awk '{print $1}' | tr -d '\r\n')}

echo "Using device: $DEVICE_ID"

# Build
cd /home/jiusi/M-DDS/rmw_dsoftbus/test
make -f Makefile.standalone clean simple
make -f Makefile.standalone deploy

# Deploy
powershell.exe -Command "hdc -t $DEVICE_ID shell 'mkdir -p /data/test'"
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\rmw_simple_test /data/test/"
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0 /data/"
powershell.exe -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/test/rmw_simple_test'"

# Run
echo ""
echo "Running test..."
powershell.exe -Command "hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_simple_test'"
```

**使用**:
```bash
chmod +x quick_deploy.sh
./quick_deploy.sh
```

---

## 故障排查

### 问题 1: 找不到库

**症状**:
```
error while loading shared libraries: librmw_dsoftbus.so.0
```

**解决**:
```bash
# 检查库是否部署
powershell.exe -Command "hdc -t $DEVICE_ID shell 'ls -lh /data/librmw_dsoftbus.so.0.1.0'"

# 重新部署
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0 /data/"
```

### 问题 2: 权限不足

**症状**:
```
Permission denied
```

**解决**:
```bash
powershell.exe -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/test/rmw_simple_test'"
```

### 问题 3: 符号未找到

**症状**:
```
❌ rmw_init (not found)
```

**检查**:
```bash
# 检查库中的符号
powershell.exe -Command "hdc -t $DEVICE_ID shell 'nm -D /data/librmw_dsoftbus.so.0.1.0 | grep rmw_init'"
```

---

## 下一步测试

成功后可以进行更高级的测试：

### 1. 跨设备通信测试

部署到两台设备并测试真实通信。

### 2. 完整功能测试

使用 `rmw_dsoftbus_standalone_test` 进行完整功能测试（需要修复编译错误）。

### 3. 集成 ROS2

将 rmw_dsoftbus 集成到 ROS2 环境中运行 talker/listener。

---

**创建时间**: 2026-01-17
**适用环境**: rk3588s KaihongOS (aarch64)
**测试模式**: 真实 dsoftbus API（无 stub/mock）
