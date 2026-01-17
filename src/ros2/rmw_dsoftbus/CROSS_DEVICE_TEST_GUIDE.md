# 跨设备 Session 通信测试指南

**创建时间**: 2026-01-14 14:08
**状态**: ✅ 部署包已准备，等待多设备上线

---

## 🎯 测试目标

验证 Phase 2 跨设备功能:
1. 设备互相发现
2. 跨设备 Session 建立
3. 双向数据传输
4. Session 管理

---

## 📦 部署包内容

**位置**: `/home/jiusi/M-DDS/rmw_dsoftbus/cross_device_test_package/`

**文件**:
1. **rmw_complete_test** (196KB)
   - 测试程序
   - 包含所有 Phase 2 API
   - 已验证单设备功能

2. **softbus_trans_permission.json**
   - 正确的配置文件
   - 数组格式
   - 明确匹配规则

3. **deploy_to_device.sh**
   - 单设备部署脚本
   - 自动化配置和程序部署

4. **run_cross_device_test.sh**
   - 跨设备测试启动脚本
   - 自动化测试流程

---

## 📋 部署步骤

### Step 1: 检查设备

```bash
powershell.exe -Command "hdc list targets"
```

**应该看到**: 至少 2 个设备

---

### Step 2: 为每个设备部署

**设备 1** (已部署):
```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus/cross_device_test_package
# 已完成
```

**设备 2** (新设备):
```bash
./deploy_to_device.sh ec29004133314d38433031a751c63c00
```

**设备 3** (如果有):
```bash
./deploy_to_device.sh <设备3_ID>
```

---

### Step 3: 重启所有设备

```bash
powershell.exe -Command "hdc -t <设备ID> shell reboot"
```

**等待**: 约 1 分钟

---

### Step 4: 验证部署

**检查配置文件**:
```bash
powershell.exe -Command "hdc -t <设备ID> shell cat /system/etc/communication/softbus/softbus_trans_permission.json"
```

**检查程序**:
```bash
powershell.exe -Command "hdc -t <设备ID> shell ls -lh /data/local/tmp/rmw_complete_test"
```

---

## 🚀 运行跨设备测试

### 方案 A: 使用自动化脚本

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus/cross_device_test_package
./run_cross_device_test.sh
```

**功能**:
- 自动检测所有在线设备
- 获取 Network ID
- 启动 Server 和 Client
- 执行跨设备通信

---

### 方案 B: 手动测试（更灵活）

**获取设备 Network ID**:
```bash
DEVICE1="ec29004133314d38433031a522413c00"
DEVICE2="ec29004133314d38433031a751c63c00"

# 在设备 1 上获取 Network ID
powershell.exe -Command "hdc -t $DEVICE1 shell '/data/local/tmp/rmw_complete_test'" | grep "NetworkID:"

# 在设备 2 上获取 Network ID
powershell.exe -Command "hdc -t $DEVICE2 shell '/data/local/tmp/rmw_complete_test'" | grep "NetworkID:"
```

**运行测试**:

**设备 1** (Session Server):
```bash
# 在一个终端窗口
powershell.exe -Command "hdc -t $DEVICE1 shell '/data/local/tmp/rmw_complete_test'"
```

**设备 2** (验证发现):
```bash
# 在另一个终端窗口
powershell.exe -Command "hdc -t $DEVICE2 shell '/data/local/tmp/rmw_complete_test'"

# 查看是否发现了设备 1
# 应该看到设备 1 的 NetworkID
```

---

## 📊 预期结果

### 设备互相发现

**设备 1 输出**:
```
[Callback] ✓ Device online: <设备2名称>
```

**设备 2 输出**:
```
[Callback] ✓ Device online: <设备1名称>
```

---

### Session 建立

**如果扩展 rmw_complete_test 支持跨设备 OpenSession**:

```cpp
// 在设备 2 上
NodeBasicInfo *devices;
int count;
GetAllNodeDeviceInfo_func(PKG_NAME, &devices, &count);

if (count > 0) {
    // 连接到设备 1
    int sessionId = OpenSession_func(
        SESSION_NAME,
        SESSION_NAME,
        devices[0].networkId,  // 设备 1 的 Network ID
        nullptr,
        &attr
    );

    if (sessionId >= 0) {
        printf("✅ Session opened: %d\n", sessionId);

        // 发送数据
        const char* msg = "Hello from Device 2!";
        SendBytes_func(sessionId, msg, strlen(msg) + 1);
    }
}
```

---

## 🔧 故障排查

### 设备未发现

**检查**:
1. 两个设备是否在同一网络
2. WiFi 是否连接
3. dsoftbus 服务是否运行

### Session 建立失败

**检查**:
1. 配置文件是否正确
2. Network ID 是否正确
3. 两端的 SESSION_NAME 是否一致

### 权限拒绝

**检查**:
1. Token 是否获取成功
2. processName 是否与 PKG_NAME 一致
3. 配置文件是否生效（重启后）

---

## 📌 当前状态

**已部署**: 设备 1（已重启）

**待部署**: 设备 2（部署中）

**下一步**: 等待设备上线后运行跨设备测试

---

## ✅ 单设备验证已完成

**所有 API**: ✅ 100% 成功

**可用于开发**: ✅ 所有 Phase 2 功能

**跨设备测试**: 🔄 准备中

---

**指南创建时间**: 2026-01-14 14:08

**状态**: 部署包已准备，等待多设备上线进行跨设备测试
