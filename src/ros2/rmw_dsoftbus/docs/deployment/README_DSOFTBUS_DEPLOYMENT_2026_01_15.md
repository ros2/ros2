# DSoftBus权限配置部署 - README

**部署日期**: 2026-01-15 | **状态**: ✅ 完成 | **版本**: 1.0

---

## 部署概况

在两台rk3588s开发板(Device 1和Device 2)上成功搜索、备份并部署了新的DSoftBus权限配置文件。

**关键成果:**
- ✅ 两台设备配置文件部署成功
- ✅ 权限条目验证通过
- ✅ 原配置文件已备份
- ✅ 设备已重启并恢复在线
- ✅ 完整文档已生成

---

## 快速查看

### 30秒了解

两台设备(`ec29004133...`和`ec29004133...`)已成功部署DSoftBus权限配置文件。配置包含两个权限条目:
1. `com.huawei.ros2_rmw_dsoftbus.complete_test` - ROS2完整测试权限
2. `com.softbus.graph.discovery` - 图形发现功能权限

**MD5校验和**: `159075fff0dda87c5ec574f31b264305` (验证一致)

### 3分钟快速阅读

→ 参考: [SOFTBUS_PERMISSION_QUICK_REFERENCE.md](SOFTBUS_PERMISSION_QUICK_REFERENCE.md)

包含: 配置内容、常用命令、设备ID参考、故障排查

### 15分钟深度了解

→ 参考: [DSOFTBUS_PERMISSION_DEPLOYMENT_REPORT_2026_01_15.md](DSOFTBUS_PERMISSION_DEPLOYMENT_REPORT_2026_01_15.md)

包含: 完整部署流程、验证结果、技术细节

### 5分钟文档导航

→ 参考: [DSOFTBUS_DEPLOYMENT_INDEX_2026_01_15.md](DSOFTBUS_DEPLOYMENT_INDEX_2026_01_15.md)

帮助: 快速找到需要的文档和脚本

---

## 文件清单

### 📋 核心文档

| 文件 | 大小 | 用途 |
|------|------|------|
| DSOFTBUS_PERMISSION_DEPLOYMENT_REPORT_2026_01_15.md | 8.3 KB | 完整部署报告 |
| SOFTBUS_PERMISSION_QUICK_REFERENCE.md | 7.5 KB | 快速参考指南 |
| DEPLOYMENT_EXECUTION_LOG_2026_01_15.txt | 9.5 KB | 执行日志 |
| DSOFTBUS_DEPLOYMENT_INDEX_2026_01_15.md | 3.2 KB | 文档导航 |
| README_DSOFTBUS_DEPLOYMENT_2026_01_15.md | 本文件 | README |

### 📜 脚本

| 脚本 | 大小 | 功能 |
|------|------|------|
| ../scripts/deploy_softbus_permission.sh | 6.7 KB | 在新设备上部署 |
| ../scripts/restore_softbus_permission.sh | 3.4 KB | 从备份恢复原配置 |

---

## 常用操作

### 验证配置是否部署

```bash
# Device 1
hdc -t ec29004133314d38433031a522413c00 shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json'

# Device 2
hdc -t ec29004133314d38433031a5544f3c00 shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json'
```

### 检查备份文件

```bash
# Device 1
hdc -t ec29004133314d38433031a522413c00 shell 'ls -lh /system/etc/communication/softbus/*.bak'

# Device 2
hdc -t ec29004133314d38433031a5544f3c00 shell 'ls -lh /system/etc/communication/softbus/*.bak'
```

### 恢复原配置

```bash
# Device 1
./scripts/restore_softbus_permission.sh ec29004133314d38433031a522413c00

# Device 2
./scripts/restore_softbus_permission.sh ec29004133314d38433031a5544f3c00
```

### 在新设备部署

```bash
# 获取设备ID
powershell.exe -NoProfile -Command "hdc list targets"

# 在新设备部署
cd /home/jiusi/M-DDS/rmw_dsoftbus
./scripts/deploy_softbus_permission.sh <NEW_DEVICE_ID> /mnt/c/tmp/hdc_deploy/softbus_trans_permission.json
```

---

## 配置文件详情

**位置**: `/system/etc/communication/softbus/softbus_trans_permission.json`

**大小**: 832 字节

**格式**: JSON

**权限条目**:
```json
{
  "SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.complete_test",
  "PKG_NAME": "com.huawei.ros2_rmw_dsoftbus",
  "ACTIONS": "create,open"
}
```

```json
{
  "SESSION_NAME": "com.softbus.graph.discovery",
  "PKG_NAME": "*",
  "ACTIONS": "create,open"
}
```

**备份位置**:
- Device 1: `/system/etc/communication/softbus/softbus_trans_permission.json.bak`
- Device 2: `/system/etc/communication/softbus/softbus_trans_permission.json.bak`

---

## 部署统计

| 指标 | 值 |
|------|-----|
| 总部署时间 | ~6 分钟 |
| Device 1 部署耗时 | ~25 秒 |
| Device 2 部署耗时 | ~25 秒 |
| 设备重启耗时 | ~165 秒 |
| 平均传输速率 | 110.94 kB/s |
| 成功率 | 100% (2/2) |

---

## 验收标准

所有以下标准已满足:

- ✅ 文件已部署到指定位置
- ✅ 文件内容正确完整
- ✅ MD5校验和一致
- ✅ 权限条目正确配置
- ✅ 原配置备份已保存
- ✅ 设备已重启并恢复在线
- ✅ 最终验证通过
- ✅ 完整文档已生成

---

## 设备信息

### Device 1
- **ID**: ec29004133314d38433031a522413c00
- **类型**: rk3588s
- **配置文件**: /system/etc/communication/softbus/softbus_trans_permission.json
- **备份文件**: /system/etc/communication/softbus/softbus_trans_permission.json.bak
- **部署时间**: 2026-01-15 17:04:25
- **验证时间**: 2026-01-15 17:09:10
- **状态**: ✅ 部署成功

### Device 2
- **ID**: ec29004133314d38433031a5544f3c00
- **类型**: rk3588s
- **配置文件**: /system/etc/communication/softbus/softbus_trans_permission.json
- **备份文件**: /system/etc/communication/softbus/softbus_trans_permission.json.bak
- **部署时间**: 2026-01-15 17:04:56
- **验证时间**: 2026-01-15 17:09:10
- **状态**: ✅ 部署成功

---

## 故障排查

### 权限配置未生效

1. 验证文件存在: `hdc -t <DEVICE_ID> shell 'test -f /system/etc/communication/softbus/softbus_trans_permission.json && echo "存在" || echo "不存在"'`
2. 检查内容: `hdc -t <DEVICE_ID> shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json'`
3. 检查DSoftBus日志: `hdc -t <DEVICE_ID> shell 'cat /data/log/softbus/softbus_server.log'`
4. 参考: [SOFTBUS_PERMISSION_QUICK_REFERENCE.md](SOFTBUS_PERMISSION_QUICK_REFERENCE.md#故障排查)

### 需要恢复原配置

```bash
./scripts/restore_softbus_permission.sh <DEVICE_ID>
```

### 在新设备上部署

```bash
./scripts/deploy_softbus_permission.sh <NEW_DEVICE_ID> /mnt/c/tmp/hdc_deploy/softbus_trans_permission.json
```

---

## 技术特性

1. **并行部署**
   - 两台设备同时部署，节约时间

2. **完整验证**
   - 文件存在性、内容完整性、MD5校验、权限正确性

3. **自动备份**
   - 所有原配置自动备份为 .bak 文件

4. **一键恢复**
   - 提供恢复脚本，可快速还原原配置

5. **可复用脚本**
   - 脚本支持多设备，可用于将来的部署

---

## 后续步骤

**立即**:
- 等待DSoftBus服务完全启动(已完成，约90秒)
- 检查设备是否稳定运行

**今天**:
- 验证权限配置是否生效
- 运行图形发现测试
- 进行跨设备通信测试

**可选**:
- 审查DSoftBus日志
- 验证权限相关的会话创建/打开
- 测试实际应用中的权限功能

---

## 文件位置速查

```
/home/jiusi/M-DDS/rmw_dsoftbus/
├── docs/
│   ├── DSOFTBUS_PERMISSION_DEPLOYMENT_REPORT_2026_01_15.md ← 详细报告
│   ├── SOFTBUS_PERMISSION_QUICK_REFERENCE.md ← 快速参考
│   ├── DEPLOYMENT_EXECUTION_LOG_2026_01_15.txt ← 执行日志
│   ├── DSOFTBUS_DEPLOYMENT_INDEX_2026_01_15.md ← 文档导航
│   └── README_DSOFTBUS_DEPLOYMENT_2026_01_15.md ← 本文件
│
├── scripts/
│   ├── deploy_softbus_permission.sh ← 部署脚本
│   └── restore_softbus_permission.sh ← 恢复脚本
│
└── /mnt/c/tmp/hdc_deploy/
    └── softbus_trans_permission.json ← 源配置文件
```

---

## 快速链接

- **快速参考**: [SOFTBUS_PERMISSION_QUICK_REFERENCE.md](SOFTBUS_PERMISSION_QUICK_REFERENCE.md)
- **详细报告**: [DSOFTBUS_PERMISSION_DEPLOYMENT_REPORT_2026_01_15.md](DSOFTBUS_PERMISSION_DEPLOYMENT_REPORT_2026_01_15.md)
- **执行日志**: [DEPLOYMENT_EXECUTION_LOG_2026_01_15.txt](DEPLOYMENT_EXECUTION_LOG_2026_01_15.txt)
- **文档导航**: [DSOFTBUS_DEPLOYMENT_INDEX_2026_01_15.md](DSOFTBUS_DEPLOYMENT_INDEX_2026_01_15.md)

---

## 版本信息

| 项目 | 值 |
|------|-----|
| 版本 | v1.0 |
| 部署日期 | 2026-01-15 |
| 部署时间 | 17:03 - 17:11 UTC |
| 部署工具 | HDC Controller Agent |
| 最后更新 | 2026-01-15 17:11 |

---

## 关键指标

- **部署成功率**: 100% (2/2设备)
- **验证通过率**: 100% (所有检查项)
- **文档完整度**: 100% (4个完整文档)
- **脚本可用性**: 100% (2个脚本)
- **备份成功率**: 100% (2/2备份)

---

**部署状态**: ✅ 完成
**最后更新**: 2026-01-15 17:11
**执行代理**: HDC Controller Agent
