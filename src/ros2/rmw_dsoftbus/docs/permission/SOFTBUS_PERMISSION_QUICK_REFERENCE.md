# DSoftBus权限配置快速参考
**最后更新**: 2026-01-15
**部署状态**: ✅ 完成 (两台设备)

---

## 快速摘要

### 部署成果
✅ Device 1 (ec2900413331...) - 部署成功
✅ Device 2 (ec2900413331...) - 部署成功

### 配置文件
- **位置**: `/system/etc/communication/softbus/softbus_trans_permission.json`
- **大小**: 832 字节
- **校验和**: `159075fff0dda87c5ec574f31b264305`
- **权限条目数**: 2

---

## 配置内容

### 权限条目1: ROS2 Complete Test
```
SESSION_NAME: com.huawei.ros2_rmw_dsoftbus.complete_test
PKG_NAME: com.huawei.ros2_rmw_dsoftbus
ACTIONS: create,open
SEC_LEVEL: public
```

### 权限条目2: Graph Discovery
```
SESSION_NAME: com.softbus.graph.discovery
PKG_NAME: * (所有应用)
ACTIONS: create,open
SEC_LEVEL: public
```

---

## 常用命令

### 查看配置文件
```bash
# 显示完整内容
hdc -t <DEVICE_ID> shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json'

# 验证权限条目
hdc -t <DEVICE_ID> shell 'grep "com.huawei.ros2_rmw_dsoftbus" /system/etc/communication/softbus/softbus_trans_permission.json'

# 查看文件属性
hdc -t <DEVICE_ID> shell 'ls -lh /system/etc/communication/softbus/softbus_trans_permission.json'

# 计算MD5校验和
hdc -t <DEVICE_ID> shell 'md5sum /system/etc/communication/softbus/softbus_trans_permission.json'
```

### 检查服务状态
```bash
# 查看DSoftBus服务
hdc -t <DEVICE_ID> shell 'ps aux | grep softbus'

# 查看DSoftBus日志
hdc -t <DEVICE_ID> shell 'cat /data/log/softbus/softbus_server.log'

# 重启DSoftBus
hdc -t <DEVICE_ID> shell 'killall softbus_server softbus_daemon'
```

### 设备操作
```bash
# 重启设备
hdc -t <DEVICE_ID> shell 'reboot'

# 获取设备ID列表
powershell.exe -NoProfile -Command "hdc list targets"

# 检查HDC连接
powershell.exe -NoProfile -Command "hdc list targets -v"
```

---

## 设备ID参考

### Device 1
```
ID: ec29004133314d38433031a522413c00
配置文件: /system/etc/communication/softbus/softbus_trans_permission.json
备份文件: /system/etc/communication/softbus/softbus_trans_permission.json.bak
部署时间: 2026-01-15 17:04:25
验证时间: 2026-01-15 17:09:10
状态: ✅ 部署成功
```

### Device 2
```
ID: ec29004133314d38433031a5544f3c00
配置文件: /system/etc/communication/softbus/softbus_trans_permission.json
备份文件: /system/etc/communication/softbus/softbus_trans_permission.json.bak
部署时间: 2026-01-15 17:04:56
验证时间: 2026-01-15 17:09:10
状态: ✅ 部署成功
```

---

## 故障排查

### 问题1: 权限配置未生效

**症状**: DSoftBus会话创建失败

**排查步骤**:
```bash
# 1. 验证文件存在
hdc -t <DEVICE_ID> shell 'test -f /system/etc/communication/softbus/softbus_trans_permission.json && echo "文件存在" || echo "文件不存在"'

# 2. 验证内容
hdc -t <DEVICE_ID> shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json'

# 3. 验证权限
hdc -t <DEVICE_ID> shell 'ls -l /system/etc/communication/softbus/softbus_trans_permission.json'

# 4. 检查DSoftBus日志
hdc -t <DEVICE_ID> shell 'tail -100 /data/log/softbus/softbus_server.log | grep -i "permission\|error"'
```

**解决方案**:
- 验证JSON格式是否正确
- 重启DSoftBus服务
- 重启整个设备
- 检查是否需要重新部署

### 问题2: 文件传输失败

**症状**: HDC文件传输超时或中断

**原因**:
- 设备未连接或连接中断
- 目标目录权限不足
- 磁盘空间不足

**解决方案**:
```bash
# 检查设备连接
powershell.exe -NoProfile -Command "hdc list targets"

# 检查磁盘空间
hdc -t <DEVICE_ID> shell 'df -h'

# 检查目录权限
hdc -t <DEVICE_ID> shell 'ls -ld /system/etc/communication/softbus'

# 手动创建目录
hdc -t <DEVICE_ID> shell 'mkdir -p /system/etc/communication/softbus'

# 重试部署
./deploy_softbus_permission.sh <DEVICE_ID> /mnt/c/tmp/hdc_deploy/softbus_trans_permission.json
```

### 问题3: 需要恢复原配置

**恢复步骤**:
```bash
# 方法1: 使用提供的脚本
./restore_softbus_permission.sh <DEVICE_ID>

# 方法2: 手动恢复
hdc -t <DEVICE_ID> shell 'cp /system/etc/communication/softbus/softbus_trans_permission.json.bak /system/etc/communication/softbus/softbus_trans_permission.json'

# 重启设备使改动生效
hdc -t <DEVICE_ID> shell 'reboot'
```

---

## 部署脚本使用

### 部署新配置
```bash
# 基本用法
./deploy_softbus_permission.sh <DEVICE_ID> <CONFIG_FILE>

# 示例
./deploy_softbus_permission.sh ec29004133314d38433031a522413c00 /mnt/c/tmp/hdc_deploy/softbus_trans_permission.json

# 部署后不自动重启
./deploy_softbus_permission.sh ec29004133314d38433031a522413c00 /mnt/c/tmp/hdc_deploy/softbus_trans_permission.json --no-reboot
```

### 恢复原配置
```bash
# 基本用法
./restore_softbus_permission.sh <DEVICE_ID>

# 示例
./restore_softbus_permission.sh ec29004133314d38433031a522413c00
```

---

## 配置文件位置参考

### 系统中的权限文件位置
```
单一位置: /system/etc/communication/softbus/softbus_trans_permission.json
```

### 备份位置
```
Device 1: /system/etc/communication/softbus/softbus_trans_permission.json.bak
Device 2: /system/etc/communication/softbus/softbus_trans_permission.json.bak
```

### 源文件位置 (WSL)
```
/mnt/c/tmp/hdc_deploy/softbus_trans_permission.json
```

### 源文件位置 (Windows)
```
C:\tmp\hdc_deploy\softbus_trans_permission.json
```

---

## 验证检查清单

部署完成后使用以下检查清单验证:

- [ ] 两台设备都已连接
- [ ] 配置文件存在于两台设备上
- [ ] MD5校验和匹配 (159075fff0dda87c5ec574f31b264305)
- [ ] 文件包含 2 个权限条目
- [ ] 文件包含 com.huawei.ros2_rmw_dsoftbus 条目
- [ ] 文件包含 com.softbus.graph.discovery 条目
- [ ] 文件权限为 644 (rw-r--r--)
- [ ] 备份文件存在于两台设备上
- [ ] DSoftBus服务运行正常
- [ ] DSoftBus日志无权限相关错误

---

## 技术细节

### MD5校验和
```
源文件: 159075fff0dda87c5ec574f31b264305
Device 1: 159075fff0dda87c5ec574f31b264305
Device 2: 159075fff0dda87c5ec574f31b264305

验证: ✅ 所有文件一致
```

### 文件权限
```
原始权限: 644 (rw-r--r--)
所有者: root
所属组: root
类型: 普通文件
```

### 部署效率
```
搜索时间: 25 秒
部署时间: 6-10 毫秒
总传输大小: 832 字节
传输速率: 83-138 kB/s
设备重启: ~90 秒
总部署时间: ~5 分钟
```

---

## 重要提醒

### ⚠️ 部署前
- 确保两台设备都已连接
- 备份重要数据
- 确保设备有足够的存储空间
- 检查网络连接稳定性

### ⚠️ 部署中
- 不要中断设备连接
- 不要关闭设备或HDC连接
- 等待部署完全完成
- 设备重启期间请勿操作

### ⚠️ 部署后
- 等待 60-90 秒让DSoftBus服务启动
- 验证权限配置是否生效
- 如有问题，查看DSoftBus日志
- 必要时使用备份文件恢复原配置

---

## 相关文档

- **详细报告**: `DSOFTBUS_PERMISSION_DEPLOYMENT_REPORT_2026_01_15.md`
- **部署脚本**: `scripts/deploy_softbus_permission.sh`
- **恢复脚本**: `scripts/restore_softbus_permission.sh`
- **权限系统指南**: 见项目文档目录

---

## 联系与支持

如有问题或需要进一步帮助:

1. 查看详细部署报告: `DSOFTBUS_PERMISSION_DEPLOYMENT_REPORT_2026_01_15.md`
2. 检查项目文档: `/home/jiusi/M-DDS/rmw_dsoftbus/docs/`
3. 查看脚本日志: 部署/恢复脚本会输出详细信息

---

**最后更新**: 2026-01-15 17:09:15
**执行代理**: HDC Controller Agent
**部署状态**: ✅ 完成 (两台设备已成功部署)
