# RMW Discovery 系统服务集成指南

**适用场景：** ROS2 作为命令行工具链，rmw_dsoftbus 作为系统基础组件

**部署模型：** System Service (非 HAP 应用)

---

## 为什么必须是系统服务

### ROS2 使用场景

1. **命令行工具：**
   ```bash
   ros2 node list
   ros2 topic list
   ros2 run demo_nodes_cpp talker
   ```

2. **进程模型：**
   - ROS2 节点是独立进程（非 HAP）
   - 通过 RMW 库（librmw_dsoftbus.so）调用 Discovery
   - Discovery 必须以守护进程形式运行

3. **权限要求：**
   - 所有 ROS2 进程需要访问 Discovery 服务
   - Discovery 需要 SoftBus 权限（DISTRIBUTED_DATASYNC）
   - 系统服务可以提供这种全局可访问性

---

## 系统服务架构

```
系统启动
  ↓
init 进程读取 /system/etc/init/rmw_discovery.cfg
  ↓
启动 rmw_discovery_daemon (UID=softbus_server)
  ↓
守护进程初始化：
  1. try_init_native_token() - 设置 token_id=671999888
  2. DiscoveryManager::initialize() - 创建 SessionServer
  3. connect_all_peers_once() - 连接其他设备
  ↓
Discovery 服务就绪（全局可用）
  ↓
ROS2 进程启动：
  1. 加载 librmw_dsoftbus.so
  2. 通过共享的 GraphCache 访问 Discovery 数据
  3. 注册本地节点/endpoint → Discovery 广播
```

---

## 集成步骤

### 步骤 1: 编译系统服务守护进程

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus/system_service
make clean && make

# 输出: rmw_discovery_daemon (291 KB)
```

### 步骤 2: 部署到设备

**方式 A: 使用部署脚本（推荐）**
```bash
chmod +x deploy.sh
./deploy.sh ec29004133314d38433031a522413c00
```

**方式 B: 手动部署**
```bash
DEVICE_ID="ec29004133314d38433031a522413c00"

# Upload files
hdc -t $DEVICE_ID file send rmw_discovery_daemon /data/local/tmp/
hdc -t $DEVICE_ID file send init/rmw_discovery.cfg /data/local/tmp/
hdc -t $DEVICE_ID file send token/native_token_config.json /data/local/tmp/

# Install to system
hdc -t $DEVICE_ID shell "mount -o remount,rw /system"
hdc -t $DEVICE_ID shell "cp /data/local/tmp/rmw_discovery_daemon /system/bin/"
hdc -t $DEVICE_ID shell "chmod 755 /system/bin/rmw_discovery_daemon"
hdc -t $DEVICE_ID shell "cp /data/local/tmp/rmw_discovery.cfg /system/etc/init/"
hdc -t $DEVICE_ID shell "mkdir -p /system/etc/token_sync"
hdc -t $DEVICE_ID shell "cp /data/local/tmp/native_token_config.json /system/etc/token_sync/rmw_discovery_token.json"
hdc -t $DEVICE_ID shell "sync"
```

### 步骤 3: 重启设备

```bash
hdc -t $DEVICE_ID shell "reboot"

# 等待 2 分钟设备启动
sleep 120
```

### 步骤 4: 验证服务运行

```bash
# 检查进程
hdc -t $DEVICE_ID shell "ps -ef | grep rmw_discovery"

# 预期输出:
# softbus_server  <PID>  1  ... /system/bin/rmw_discovery_daemon
```

### 步骤 5: 检查服务日志

```bash
# 服务日志（如果有）
hdc -t $DEVICE_ID shell "cat /data/log/rmw_discovery.log"

# 或通过 hilog
hdc -t $DEVICE_ID shell "hilog | grep -E 'DiscoveryManager|RMW Discovery'"
```

**成功标志：**
```
[DiscoveryManager] SessionServer created: id=100 ✅
[DiscoveryManager] Init complete: peers>=1 ✅
[RMW Discovery Daemon] Service is now running ✅
```

---

## Init Config 详解

**文件：** `/system/etc/init/rmw_discovery.cfg`

```json
{
  "services": [{
    "name": "rmw_discovery",                     // 服务名称
    "path": ["/system/bin/rmw_discovery_daemon"], // 可执行文件路径
    "uid": "softbus_server",                     // 以 softbus_server 身份运行
    "gid": ["softbus_server", "system"],         // 组权限
    "secon": "u:r:softbus_server:s0",            // SELinux context (复用 softbus)
    "caps": ["DAC_OVERRIDE", "DAC_READ_SEARCH"], // Linux capabilities
    "start-mode": "boot",                         // 开机自动启动
    "importance": 0,                              // 重要性级别
    "critical": [0, 5, 10],                       // 崩溃重启策略
    "ondemand": false,                            // 非按需启动
    "disabled": false,                            // 未禁用
    "sandbox": 0                                  // 不使用沙箱
  }]
}
```

**关键配置说明：**

1. **uid/gid: softbus_server**
   - 与 SoftBus 服务相同的身份
   - 确保有权访问 SoftBus IPC

2. **secon: u:r:softbus_server:s0**
   - 复用 softbus_server 的 SELinux 策略
   - 避免创建新的策略文件

3. **start-mode: boot**
   - 系统启动时自动运行
   - 确保 ROS2 节点启动前 Discovery 已就绪

4. **critical: [0, 5, 10]**
   - 崩溃后自动重启
   - 第 1 次立即，第 2 次 5 秒后，第 3 次 10 秒后

---

## Native Token 配置详解

**文件：** `/system/etc/token_sync/rmw_discovery_token.json`

```json
{
  "processName": "com.huawei.dmsdp",               // 进程身份（复用 dmsdp 权限）
  "APL": "system_basic",                           // 权限级别
  "version": 1,
  "tokenId": 671999888,                            // Token ID
  "permissions": [
    {
      "name": "ohos.permission.DISTRIBUTED_DATASYNC",      // SoftBus 必需
      "granted": true
    },
    {
      "name": "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER", // Bus Center 必需
      "granted": true
    },
    {
      "name": "ohos.permission.ACCESS_SERVICE_DM",         // Device Manager 必需
      "granted": true
    }
  ]
}
```

**关键点：**

1. **processName: com.huawei.dmsdp**
   - 复用已有的系统权限
   - 匹配 softbus_trans_permission.json 白名单

2. **APL: system_basic**
   - 系统级权限
   - 高于普通应用 (normal)

3. **tokenId: 671999888**
   - 与代码中 native_token.cpp 使用的 ID 一致
   - 通过 ioctl 设置到进程

---

## 前置条件检查

### 必需的系统配置

**1. SoftBus 权限白名单**
```bash
# 检查权限文件
hdc shell "cat /system/etc/communication/softbus/softbus_trans_permission.json"

# 必须包含:
{
  "SESSION_NAME": "com.huawei.dmsdp.*",
  "PKG_NAME": "com.huawei.dmsdp",
  "ACTIONS": "create,open"
}
```

**2. SoftBus 服务运行**
```bash
# 检查服务状态
hdc shell "ps -ef | grep softbus_server"

# 预期输出:
# dsoftbus   945   1  ... softbus_server
```

**3. Token 设备节点可用**
```bash
# 检查 token device node
hdc shell "ls -l /dev/access_token_id"

# 预期: crw-rw-rw- (character device)
```

---

## 故障排查

### 服务未启动

**检查 init log:**
```bash
hdc shell "dmesg | grep rmw_discovery"
hdc shell "hilog | grep 'init.*rmw_discovery'"
```

**可能原因：**
- init.cfg 语法错误
- 二进制文件权限不足 (需要 755)
- 依赖库缺失

**解决：**
```bash
# 手动启动测试
hdc shell "/system/bin/rmw_discovery_daemon -f"  # Foreground mode
```

### CreateSessionServer 仍然失败

**检查 Token 设置:**
```bash
# Token device node 权限
hdc shell "ls -l /dev/access_token_id"

# 尝试手动设置 token
hdc shell "echo 671999888 > /dev/access_token_id" || echo "Permission denied"
```

**检查 SELinux:**
```bash
# SELinux 状态
hdc shell "getenforce"

# 如果是 Enforcing，可能需要策略
# 临时关闭测试（仅测试用）:
hdc shell "setenforce 0"
```

### 日志无输出

**检查日志目录:**
```bash
hdc shell "ls -ld /data/log"
hdc shell "ls -l /data/log/rmw_discovery.log"
```

**手动创建日志目录:**
```bash
hdc shell "mkdir -p /data/log && chmod 777 /data/log"
```

---

## 验收测试（服务运行后）

### T1: 两设备 Discovery 验证

**前提：** 两台设备都已部署并启动 rmw_discovery 服务

**验证步骤：**
```bash
# Device A
hdc -t <DEVICE_A> shell "hilog | grep -E '(SessionServer created|peers)'"

# Device B
hdc -t <DEVICE_B> shell "hilog | grep -E '(SessionServer created|peers)'"
```

**成功标志（10 秒内）：**
```
[DiscoveryManager] SessionServer created: id=100
[DiscoveryManager] Found 1 device(s) in network
[DiscoveryManager] OpenSession succeeded: session_id=101
[DiscoveryManager] Init complete: peers=1
```

### 检查 Counter 状态

在任意 ROS2 节点中调用：
```cpp
auto stats = DiscoveryManager::instance().get_stats();
printf("peers=%u query_sent=%lu snapshot_recv=%lu\n",
       stats.peer_sessions_count, stats.query_sent, stats.snapshot_recv);
```

**预期：**
- peers >= 1
- query_sent > 0
- snapshot_recv > 0

---

## 与 ROS2 集成

### ROS2 节点使用 Discovery

**ROS2 节点启动时：**
```cpp
// In rmw_init.cpp
rmw_ret_t rmw_init(...) {
    // Discovery daemon already running as system service
    // Just register this node with GraphCache
    GraphCache::instance().register_node(node_name, node_namespace, enclave);

    // Discovery daemon will automatically broadcast NODE_ADD
    // No need to initialize DiscoveryManager (already running)
}
```

**进程间通信：**
- GraphCache 可以通过共享内存或 IPC 与守护进程通信
- 或每个 ROS2 进程独立连接到 Discovery 网络（当前实现）

---

## GN 构建集成（长期）

### BUILD.gn (系统构建)

```gn
ohos_executable("rmw_discovery_daemon") {
  sources = [
    "system_service/rmw_discovery_daemon.cpp",
    "src/discovery_manager.cpp",
    "src/graph_cache.cpp",
    "src/native_token.cpp",
  ]

  include_dirs = [
    "include",
    "//foundation/communication/dsoftbus/interfaces/kits/transport",
    "//foundation/communication/dsoftbus/interfaces/kits/bus_center",
  ]

  external_deps = [
    "dsoftbus:softbus_client",
    "access_token:libaccesstoken_sdk",
  ]

  install_enable = true
  install_images = [ "system" ]
  part_name = "rmw_dsoftbus"
  subsystem_name = "ros2"
}

ohos_prebuilt_etc("rmw_discovery_init") {
  source = "system_service/init/rmw_discovery.cfg"
  install_images = [ "system" ]
  part_name = "rmw_dsoftbus"
  subsystem_name = "ros2"
}
```

---

## 安全考虑

### Token ID 管理

**当前使用：** `671999888` (固定 ID)

**生产建议：**
1. 使用系统分配的 token ID
2. 在系统 token 数据库中预注册
3. 与 processName 绑定

### SELinux 策略

**当前：** 复用 `u:r:softbus_server:s0`

**长期：** 创建专用策略
```
type rmw_discovery, domain;
type rmw_discovery_exec, exec_type, file_type;

init_daemon_domain(rmw_discovery)

allow rmw_discovery softbus_server:binder { call transfer };
allow rmw_discovery self:capability { dac_override dac_read_search };
```

---

## 快速部署（3 设备）

### 批量部署脚本

```bash
#!/bin/bash
# 批量部署到 3 台设备

DEVICES=(
    "ec29004133314d38433031a522413c00"
    "ec29004133314d38433031a5544f3c00"
    "ec29004133314d38433031a751c63c00"
)

for DEV in "${DEVICES[@]}"; do
    echo "=== Deploying to $DEV ==="
    ./deploy.sh $DEV
done

echo ""
echo "=== Rebooting all devices ==="
for DEV in "${DEVICES[@]}"; do
    powershell.exe -Command "hdc -t $DEV shell 'reboot'" &
done

wait
echo "Waiting for devices to boot (120 seconds)..."
sleep 120

echo ""
echo "=== Verifying services ==="
for DEV in "${DEVICES[@]}"; do
    echo "Device $DEV:"
    powershell.exe -Command "hdc -t $DEV shell 'ps -ef | grep rmw_discovery | grep -v grep'"
done
```

---

## 当前状态

### ✅ 已完成

- ✅ 守护进程实现 (rmw_discovery_daemon.cpp)
- ✅ Init config (rmw_discovery.cfg)
- ✅ Token config (native_token_config.json)
- ✅ Makefile (系统服务编译)
- ✅ 部署脚本 (deploy.sh)
- ✅ 集成指南 (本文档)

### ⏸️ 待执行

1. 编译守护进程
2. 部署到 3 台设备
3. 重启设备
4. 验证服务启动
5. 执行 T1/T5/T6 测试

---

## 预期结果

### 服务启动后（每台设备）

```
[RMW Discovery Daemon] Starting...
[RMW Discovery Daemon] Mode: daemon
[RMW Discovery Daemon] PID: <PID>
[RMW Discovery Daemon] UID: <softbus_uid> GID: <softbus_gid>
[RMW Discovery Daemon] Initializing Native Token...
[rmw_dsoftbus] NativeToken: set token_id=671999888 (verify=671999888) ✅
[RMW Discovery Daemon] Native token initialized successfully
[RMW Discovery Daemon] Initializing DiscoveryManager...
[DiscoveryManager] Initializing discovery subsystem
[DiscoveryManager] Got network_id from dsoftbus: <real_network_id> ✅
[DiscoveryManager] Creating SessionServer: name=com.huawei.dmsdp.ros2_disc_<PID>
[DiscoveryManager] SessionServer created: id=100 ✅
[DiscoveryManager] Connecting to all peers...
[Discovery] Found 2 device(s) in network ✅
[DiscoveryManager] OpenSession to <peer1> succeeded: session_id=101 ✅
[DiscoveryManager] OpenSession to <peer2> succeeded: session_id=102 ✅
[DiscoveryManager] Connected to 2 peer(s)
[DiscoveryManager] Init complete: local=<id> server_id=100 peers=2 shim=loaded ✅
[RMW Discovery Daemon] GraphCache initialized
[RMW Discovery Daemon] Startup stats: peers=2 ✅
[RMW Discovery Daemon] Service is now running (PID: <PID>)
```

### Counter 验证（30 秒后）

```
[RMW Discovery Daemon] Stats[1]: peers=2 rx=4 tx=4 query=2 snap=2 drops=0
```

---

## 文档备注（满足团队要求）

### 权限说明

**系统服务所需权限：**

1. **ohos.permission.DISTRIBUTED_DATASYNC**
   - 用途：调用 SoftBus Session/Transport APIs
   - 授权方式：Native token 注册（system_basic APL）

2. **ohos.permission.DISTRIBUTED_SOFTBUS_CENTER**
   - 用途：调用 Bus Center APIs（设备发现）
   - 授权方式：Native token 注册

3. **ohos.permission.ACCESS_SERVICE_DM**
   - 用途：访问 Device Manager 服务
   - 授权方式：Native token 注册

**Token 注册位置：** `/system/etc/token_sync/rmw_discovery_token.json`

**白名单配置：** `/system/etc/communication/softbus/softbus_trans_permission.json`
```json
{
  "SESSION_NAME": "com.huawei.dmsdp.*",
  "PKG_NAME": "com.huawei.dmsdp",
  "ACTIONS": "create,open"
}
```

---

## 下一步行动

### 立即执行

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus/system_service
make
./deploy.sh ec29004133314d38433031a522413c00
./deploy.sh ec29004133314d38433031a5544f3c00
./deploy.sh ec29004133314d38433031a751c63c00

# Reboot all devices
# Wait 2 minutes
# Verify service running
# Execute T1/T5/T6 tests
```

**ETA:** 30-45 分钟（编译 + 部署 + 重启 + 验证）

---

**文档版本：** 1.0
**创建日期：** 2026-01-04
**适用平台：** KaihongOS / OpenHarmony 11+
**作者：** Claude Code (Automated)

