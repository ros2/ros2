# SoftBus 权限配置文件部署记录

**日期**: 2026-01-15 16:32 UTC
**状态**: ✅ 成功

## 部署概要

| 项目 | 详情 |
|------|------|
| 部署文件 | softbus_trans_permission.json (832 字节) |
| 目标路径 | /system/etc/communication/softbus/softbus_trans_permission.json |
| 设备数量 | 2 台 (rk3588s) |
| 部署用时 | 约 2 分钟 |
| 部署状态 | 全部成功 ✅ |

## 部署的设备

### 设备 1
- **ID**: ec29004133314d38433031a522413c00
- **型号**: rk3588s KaihongOS
- **状态**: 在线 ✓
- **文件大小**: 832 字节
- **权限**: -rw-r--r-- (644)
- **更新时间**: 2026-01-15 16:32:30
- **DSoftBus PID**: 3581 ✓

### 设备 2
- **ID**: ec29004133314d38433031a5544f3c00
- **型号**: rk3588s KaihongOS
- **状态**: 在线 ✓
- **文件大小**: 832 字节
- **权限**: -rw-r--r-- (644)
- **更新时间**: 2026-01-15 16:32:30
- **DSoftBus PID**: 5026 ✓

## 部署步骤完成情况

| 步骤 | 操作 | 设备1 | 设备2 | 状态 |
|------|------|------|------|------|
| 1 | 备份原文件 | ✓ | ✓ | 完成 |
| 2 | 传输新文件 | ✓ | ✓ | 完成 |
| 3 | 设置权限 644 | ✓ | ✓ | 完成 |
| 4 | 验证文件内容 | ✓ | ✓ | 完成 |
| 5 | 重启 DSoftBus 服务 | ✓ | ✓ | 完成 |
| 6 | 验证服务状态 | ✓ | ✓ | 完成 |

## 部署文件配置内容

### 会话配置 1: com.huawei.ros2_rmw_dsoftbus.complete_test
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

### 会话配置 2: com.softbus.graph.discovery
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

## 验证结果

### 文件内容验证 ✅
- 文件行数: 36 行
- 关键项验证:
  - ✓ `"SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.complete_test"`
  - ✓ `"PKG_NAME": "com.huawei.ros2_rmw_dsoftbus"`
  - ✓ `"SESSION_NAME": "com.softbus.graph.discovery"`
  - ✓ `"SEC_LEVEL": "public"`
  - ✓ `"ACTIONS": "create,open"`

### 文件权限验证 ✅
- 所有设备权限均设置为: `-rw-r--r-- (644)`

### DSoftBus 服务验证 ✅
- 设备1 DSoftBus 进程: 正常运行 (PID: 3581)
- 设备2 DSoftBus 进程: 正常运行 (PID: 5026)

## 备份信息

原始配置文件已备份至:
- **设备1**: `/system/etc/communication/softbus/softbus_trans_permission.json.bak`
- **设备2**: `/system/etc/communication/softbus/softbus_trans_permission.json.bak`

恢复命令（如需要）:
```bash
# 设备1
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'cp /system/etc/communication/softbus/softbus_trans_permission.json.bak /system/etc/communication/softbus/softbus_trans_permission.json'"

# 设备2
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'cp /system/etc/communication/softbus/softbus_trans_permission.json.bak /system/etc/communication/softbus/softbus_trans_permission.json'"
```

## 后续建议

### 强烈建议：重启设备

为确保新权限配置完全生效，建议重启设备：

```bash
# 重启设备1
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 target boot"

# 重启设备2
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 target boot"
```

设备重启需要约 2-3 分钟。

### 部署后验证

重启后可执行以下命令验证新权限生效:

```bash
# 检查权限文件
powershell.exe -NoProfile -Command "hdc -t <DEVICE_ID> shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json | head -20'"

# 检查 DSoftBus 日志
powershell.exe -NoProfile -Command "hdc -t <DEVICE_ID> shell 'hilog | grep -i permission'"

# 运行测试程序
powershell.exe -NoProfile -Command "hdc -t <DEVICE_ID> shell '/data/local/tmp/phase3_graph_discovery_test'"
```

## 快速故障排除

### 问题：权限配置未生效

**排查步骤**:
1. 验证文件内容是否正确
2. 检查 DSoftBus 服务是否运行
3. 重启设备（2-3 分钟）
4. 查看 DSoftBus 日志

### 问题：Session 创建失败

**可能原因**:
- 权限配置未加载
- 会话名称不匹配
- DSoftBus 服务异常

**解决方案**:
1. 重启设备
2. 检查测试程序中的会话名称是否与配置匹配
3. 查看 hilog 日志获取详细错误信息

### 查看日志

```bash
# 实时查看 DSoftBus 日志
powershell.exe -NoProfile -Command "hdc -t <DEVICE_ID> shell 'hilog | grep -E \"softbus|SOFTBUS|permission\"'"
```

## 部署工具和源文件

- **部署源**: `/mnt/c/tmp/hdc_deploy/softbus_trans_permission.json`
- **配置备份**: `/home/jiusi/M-DDS/rmw_dsoftbus/config/softbus_trans_permission.json`
- **部署工具**: HDC (OpenHarmony Device Connector)

## 相关文档

- 📖 权限配置详细说明: `docs/02_dsoftbus诊断体系/权限配置教程.md`
- 📖 DSoftBus 权限问题快速修复: `docs/02_dsoftbus诊断体系/dsoftbus权限问题快速修复指南.md`
- 📖 部署最终总结: `DEPLOYMENT_FINAL_SUMMARY_2026_01_05.md`

---

**部署完成**: 2026-01-15 16:32:45 UTC
**部署状态**: ✅ 全部成功
