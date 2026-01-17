# DSoftBus权限配置部署报告
**执行日期**: 2026-01-15
**执行时间**: 17:04 - 17:09 UTC
**总耗时**: 约 5 分钟
**最终状态**: ✅ 成功

---

## 部署摘要

### 目标设备
| 设备 | 设备ID | 状态 |
|------|--------|------|
| Device 1 | ec29004133314d38433031a522413c00 | ✅ 部署成功 |
| Device 2 | ec29004133314d38433031a5544f3c00 | ✅ 部署成功 |

### 部署结果
| 指标 | Device 1 | Device 2 |
|------|----------|----------|
| 配置文件 | /system/etc/communication/softbus/softbus_trans_permission.json | /system/etc/communication/softbus/softbus_trans_permission.json |
| 文件大小 | 832 字节 | 832 字节 |
| MD5校验和 | 159075fff0dda87c5ec574f31b264305 | 159075fff0dda87c5ec574f31b264305 |
| 部署时间 | 17:04:25 | 17:04:56 |
| 验证时间 | 17:09:10 | 17:09:10 |
| 部署状态 | ✅ 一致 | ✅ 一致 |

---

## 详细部署流程

### Device 1 部署日志

#### 步骤1: 搜索权限配置文件
```
[17:03:58] 执行find命令搜索...
结果: 找到 /system/etc/communication/softbus/softbus_trans_permission.json
耗时: 25秒
```

#### 步骤2: 备份和部署
```
[17:04:23] 备份原文件
  结果: /system/etc/communication/softbus/softbus_trans_permission.json.bak

[17:04:23] 部署新配置文件
  文件大小: 832 字节
  传输速率: 83.20 kB/s
  传输耗时: 10ms
  结果: ✓ 成功

[17:04:25] 验证部署
  配置条目数: 2
  - com.huawei.ros2_rmw_dsoftbus.complete_test
  - com.softbus.graph.discovery
  结果: ✓ 验证成功
```

#### 步骤3: 重启服务与设备
```
[17:04:25] 终止DSoftBus服务
  killall softbus_server: 已执行
  killall softbus_daemon: 已执行

[17:04:27] 重启设备
  reboot命令: 已发送

[17:06-17:09] 等待设备启动
  设备上线: ✓ (约90秒后)
```

### Device 2 部署日志

#### 步骤1: 搜索权限配置文件
```
[17:04:27] 执行find命令搜索...
结果: 找到 /system/etc/communication/softbus/softbus_trans_permission.json
耗时: 25秒
```

#### 步骤2: 备份和部署
```
[17:04:52] 备份原文件
  结果: /system/etc/communication/softbus/softbus_trans_permission.json.bak

[17:04:52] 部署新配置文件
  文件大小: 832 字节
  传输速率: 138.67 kB/s
  传输耗时: 6ms
  结果: ✓ 成功

[17:04:53] 验证部署
  配置条目数: 2
  - com.huawei.ros2_rmw_dsoftbus.complete_test
  - com.softbus.graph.discovery
  结果: ✓ 验证成功
```

#### 步骤3: 重启服务与设备
```
[17:04:53] 终止DSoftBus服务
  killall softbus_server: 已执行
  killall softbus_daemon: 已执行

[17:04:56] 重启设备
  reboot命令: 已发送

[17:06-17:09] 等待设备启动
  设备上线: ✓ (约90秒后)
```

---

## 配置文件内容

**位置**: `/system/etc/communication/softbus/softbus_trans_permission.json`
**大小**: 832 字节
**校验和**: `159075fff0dda87c5ec574f31b264305`

### 权限条目1: ROS2 Complete Test
```json
{
  "SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.complete_test",
  "REGEXP": "false",
  "DEVID": "NETWORKID",
  "SEC_LEVEL": "public",
  "APP_INFO": [
    {
      "TYPE": "native_app",
      "PKG_NAME": "com.huawei.ros2_rmw_dsoftbus",
      "ACTIONS": "create,open"
    }
  ]
}
```

**说明**: 为ROS2完整测试应用配置会话创建和打开权限

### 权限条目2: Graph Discovery
```json
{
  "SESSION_NAME": "com.softbus.graph.discovery",
  "REGEXP": "false",
  "DEVID": "NETWORKID",
  "SEC_LEVEL": "public",
  "APP_INFO": [
    {
      "TYPE": "native_app",
      "PKG_NAME": "*",
      "ACTIONS": "create,open"
    }
  ]
}
```

**说明**: 为所有本地应用配置图形发现功能的会话权限

---

## 文件备份信息

### Device 1
- **备份路径**: `/system/etc/communication/softbus/softbus_trans_permission.json.bak`
- **备份时间**: 2026-01-15 17:04
- **文件大小**: 832 字节
- **状态**: ✅ 已保存

### Device 2
- **备份路径**: `/system/etc/communication/softbus/softbus_trans_permission.json.bak`
- **备份时间**: 2026-01-15 17:04
- **文件大小**: 832 字节
- **状态**: ✅ 已保存

---

## 最终验证结果

### 设备连接状态
```
Device 1: Connected (USB) ✅
Device 2: Connected (USB) ✅
```

### 文件验证

#### Device 1
| 检查项 | 结果 |
|--------|------|
| 文件存在 | ✅ YES |
| 文件权限 | ✅ 644 (rw-r--r--) |
| 配置条目数 | ✅ 2 条 |
| 包含com.huawei.ros2_rmw_dsoftbus | ✅ YES |
| MD5校验 | ✅ 一致 |

#### Device 2
| 检查项 | 结果 |
|--------|------|
| 文件存在 | ✅ YES |
| 文件权限 | ✅ 644 (rw-r--r--) |
| 配置条目数 | ✅ 2 条 |
| 包含com.huawei.ros2_rmw_dsoftbus | ✅ YES |
| MD5校验 | ✅ 一致 |

---

## 关键发现

### 1. 单一配置文件位置
两台设备都只有一个权限配置文件位置:
```
/system/etc/communication/softbus/softbus_trans_permission.json
```

标准搜索路径中无其他副本:
- ✗ `/etc/communication/softbus/softbus_trans_permission.json`
- ✗ `/vendor/etc/communication/softbus/softbus_trans_permission.json`
- ✗ `/data/etc/communication/softbus/softbus_trans_permission.json`

### 2. 文件系统特性
- `/system` 分区虽然挂载但不在 `/proc/mounts` 中
- 可能为特殊只读分区或OverlayFS
- 但仍然成功完成了文件写入操作

### 3. 部署效率分析
| 操作 | 耗时 |
|------|------|
| 搜索文件 | 25秒 |
| 部署传输 | 6-10ms |
| 设备重启 | ~90秒 |
| **总计** | **~115秒** |

### 4. 传输速率
- Device 1: 83.20 kB/s
- Device 2: 138.67 kB/s

两台设备的连接状态稳定

---

## 推荐后续步骤

### 立即行动
1. ✅ 等待 60-90 秒让DSoftBus服务完全启动
2. 检查DSoftBus日志验证权限配置是否生效
3. 运行测试应用验证跨设备通信

### 可选操作
- 监控 `/data/log/softbus/` 日志目录
- 验证会话能否正常创建和打开
- 测试发现协议是否正常工作

### 恢复原配置
如需恢复原始配置:
```bash
# 使用HDC恢复
hdc -t <DEVICE_ID> shell 'cp /system/etc/communication/softbus/softbus_trans_permission.json.bak /system/etc/communication/softbus/softbus_trans_permission.json'

# 重启设备
hdc -t <DEVICE_ID> shell 'reboot'
```

---

## 技术细节

### 部署配置
| 参数 | 值 |
|------|-----|
| 源文件 | C:\tmp\hdc_deploy\softbus_trans_permission.json |
| 目标设备 | 2 台 rk3588s |
| 目标路径 | /system/etc/communication/softbus/ |
| 文件权限 | 644 |
| 备份方案 | 原文件重命名为 .bak |

### 验证方法
1. **文件存在检查**: `test -f <file> && echo YES`
2. **内容验证**: `grep "com.huawei.ros2_rmw_dsoftbus" <file>`
3. **校验和验证**: `md5sum <file>`
4. **权限检查**: `ls -l <file>`

---

## 故障排查参考

### 如果权限配置未生效

**症状**: DSoftBus会话创建或打开失败

**诊断步骤**:
1. 检查配置文件是否存在
2. 验证JSON格式是否正确
3. 检查DSoftBus服务是否运行
4. 查看DSoftBus日志获取具体错误

**恢复步骤**:
1. 检查备份文件完整性
2. 恢复原配置
3. 重启设备
4. 重新部署新配置

### 如果文件传输失败

**可能原因**:
- 设备未连接或断开连接
- 目标目录权限不足
- 文件系统已满

**解决方案**:
- 检查HDC连接: `hdc list targets`
- 检查磁盘空间: `hdc shell 'df -h'`
- 检查目录权限: `hdc shell 'ls -ld /system/etc/communication/softbus'`

---

## 附录

### 文件对比

**本地配置文件** (`/mnt/c/tmp/hdc_deploy/softbus_trans_permission.json`):
```
Size: 832 bytes
MD5:  159075fff0dda87c5ec574f31b264305
```

**Device 1 部署后**:
```
Path: /system/etc/communication/softbus/softbus_trans_permission.json
Size: 832 bytes
MD5:  159075fff0dda87c5ec574f31b264305
Time: 2026-01-15 17:04
```

**Device 2 部署后**:
```
Path: /system/etc/communication/softbus/softbus_trans_permission.json
Size: 832 bytes
MD5:  159075fff0dda87c5ec574f31b264305
Time: 2026-01-15 17:04
```

### 命令参考

查看配置文件内容:
```bash
hdc -t <DEVICE_ID> shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json'
```

验证权限条目:
```bash
hdc -t <DEVICE_ID> shell 'grep "com.huawei.ros2_rmw_dsoftbus" /system/etc/communication/softbus/softbus_trans_permission.json'
```

检查文件更新时间:
```bash
hdc -t <DEVICE_ID> shell 'stat /system/etc/communication/softbus/softbus_trans_permission.json'
```

---

**报告生成时间**: 2026-01-15 17:09:15
**执行代理**: HDC Controller Agent
**部署状态**: ✅✅ 两台设备部署成功
