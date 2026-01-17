# rmw_dsoftbus 编译指令（已修正）

**部署时间**: 2026-01-06
**部署位置**: cp服务器 `/kh_data/pengys/OpenHarmony/foundation/communication/rmw_dsoftbus/`
**产品名称**: `khs_3588s_sbc`
**状态**: ✅ 部署完成，GN gen成功

---

## ⚠️ 编译错误修正

### 错误信息
```
ninja: error: unknown target 'rmw_dsoftbus'
```

### 原因
- GN gen成功 ✅（生成了69520个targets）
- 但--build-target rmw_dsoftbus找不到目标

### ✅ 解决方案
**不要使用 --build-target，直接完整编译**

---

## 🚀 正确的编译命令（在cp服务器执行）

### 步骤1: SSH登录到cp服务器
```bash
ssh cp
```

### 步骤2: 进入OpenHarmony源码目录
```bash
cd /kh_data/pengys/OpenHarmony
```

### 步骤3: 完整编译（推荐）
```bash
# 完整编译（不要用--build-target）
./build.sh --product-name khs_3588s_sbc --ccache

# 预计时间: 1-2小时
```

**关键**：
- ✅ 使用完整编译（会包含rmw_dsoftbus）
- ❌ 不要用 `--build-target rmw_dsoftbus`（ninja找不到）

### 步骤4: 检查编译输出
```bash
# 编译完成后检查rmw_dsoftbus组件
ls -lh out/khs_3588s_sbc/communication/rmw_dsoftbus/

# 预期输出:
# librmw_dsoftbus.so
# rmw_discovery_daemon

# 检查system.img
ls -lh out/khs_3588s_sbc/packages/phone/images/system.img
```

---

## 📦 编译完成后：下载system.img到本地

### 在本地WSL执行
```bash
# 下载system.img（约500MB-2GB，需要几分钟）
scp cp:/kh_data/pengys/OpenHarmony/out/khs_3588s_sbc/packages/phone/images/system.img /tmp/

# 验证文件
ls -lh /tmp/system.img
```

---

## 🔥 刷写system.img到设备（必须）

### 刷写所有3个设备
```bash
DEVICE1="ec29004133314d38433031a522413c00"
DEVICE2="ec29004133314d38433031a5544f3c00"
DEVICE3="ec29004133314d38433031a751c63c00"

# 方式1：使用powershell.exe（WSL环境）
for DEVICE in $DEVICE1 $DEVICE2 $DEVICE3; do
  echo "刷写设备: $DEVICE"
  
  # 进入fastboot
  powershell.exe -NoProfile -Command "hdc -t $DEVICE shell 'reboot bootloader'"
  sleep 10
  
  # 刷写system分区
  powershell.exe -NoProfile -Command "fastboot flash system /tmp/system.img"
  
  # 重启
  powershell.exe -NoProfile -Command "fastboot reboot"
  
  echo "✓ 设备 $DEVICE 刷写完成"
  sleep 120
done

# 方式2：如果fastboot在WSL中
# 需要先把system.img复制到Windows路径
cp /tmp/system.img /mnt/c/tmp/
# 然后用Windows的fastboot工具刷写
```

**预计时间**：每个设备10-15分钟，3个设备约30-45分钟

---

## ✅ 验证Token注册（关键）

### 等待所有设备启动后

```bash
DEVICE_ID="ec29004133314d38433031a5544f3c00"

# 检查1: daemon是否由init自动启动
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ps -ef | grep rmw_discovery_daemon'"

# 预期输出:
# softbus  1234  1  ...  rmw_discovery_daemon
#          ^^^  ^
#          PID  父进程=1（init启动）✅

# 检查2: SELinux上下文
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ps -Z | grep rmw_discovery'"

# 预期输出:
# u:r:rmw_discovery:s0  ...  rmw_discovery_daemon
#    ^^^^^^^^^^^^^^^^
#    正确的domain（不是su:s0）✅
```

**如果daemon未自动启动**：
这是正常的，因为我们还没创建init配置文件（.cfg）。Token注册的验证可以通过手动启动daemon来完成。

---

## 🎯 最终验收: rx > 0（Phase 2封板标准）

### 运行跨设备测试

**Device 2 (Server)**:
```bash
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'cd /data/local/tmp && LD_LIBRARY_PATH=/system/lib64 ./discovery_final_test'"
```

**Device 3 (Client)**:
```bash
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a751c63c00 shell 'cd /data/local/tmp && LD_LIBRARY_PATH=/system/lib64 ./discovery_final_test'"
```

### 预期结果（成功标志）

**关键变化**：
```
之前（方案1）:
  [Discovery Callback] Session open failed: id=1 result=-426115004  ❌

现在（方案2预期）:
  [Discovery Callback] Session opened successfully: id=1            ✅
  [T+5s STATS] rx=1 tx=1                                           ✅
```

### Phase 2封板条件
- ✅ Session建立成功（不再 -426115004）
- ✅ **rx > 0**（至少收到一条discovery消息）
- ✅ Leader Election生效
- ✅ 3设备稳定运行

---

## 📊 如果遇到问题

### 问题1: 编译时找不到access_token依赖
```
错误: external_deps "access_token:libaccesstoken_sdk" not found
```

**解决**：检查access_token组件
```bash
ssh cp 'ls /kh_data/pengys/OpenHarmony/base/security/access_token'
```

如果不存在，需要修改BUILD.gn移除这些依赖。

### 问题2: 刷写后Session依然失败
**可能原因**：
1. daemon未自动启动（需要.cfg配置）
2. SELinux策略缺失

**临时解决**：
手动启动daemon并设置LD_LIBRARY_PATH：
```bash
hdc shell "LD_LIBRARY_PATH=/system/lib64 /system/bin/rmw_discovery_daemon &"
```

### 问题3: Token注册依然失败
**深度诊断**：
```bash
# 检查daemon的AccessToken
hdc shell "cat /proc/\$(pidof rmw_discovery_daemon)/attr/current"

# 如果依然显示su:s0，说明：
# - 可能需要创建SELinux策略
# - 或者系统不支持native token注册
```

---

## 🔍 编译日志查看

```bash
# 查看编译进度
ssh cp 'tail -f /kh_data/pengys/OpenHarmony/out/khs_3588s_sbc/build.log'

# 查看错误（如果编译失败）
ssh cp 'cat /kh_data/pengys/OpenHarmony/out/khs_3588s_sbc/error.log'
```

---

## ⏱️ 时间预算

| 任务 | 预计时间 |
|------|---------|
| 编译system.img | 1-2小时 |
| 下载system.img | 5分钟 |
| 刷写3个设备 | 30-45分钟 |
| 验证Token | 15分钟 |
| 最终验收 | 15分钟 |
| **总计** | **约2-3小时** |

---

## 📋 快速命令参考

### 在cp服务器编译
```bash
ssh cp
cd /kh_data/pengys/OpenHarmony
./build.sh --product-name khs_3588s_sbc --ccache
exit
```

### 下载并刷写
```bash
# 下载
scp cp:/kh_data/pengys/OpenHarmony/out/khs_3588s_sbc/packages/phone/images/system.img /tmp/

# 刷写（每个设备）
powershell.exe -Command "hdc -t <DEVICE_ID> shell 'reboot bootloader'"
powershell.exe -Command "fastboot flash system C:\tmp\system.img"
powershell.exe -Command "fastboot reboot"
```

### 验收测试
```bash
# Device 2
powershell.exe -Command "hdc -t ec29004133314d38433031a5544f3c00 shell '/data/local/tmp/discovery_final_test'"

# Device 3  
powershell.exe -Command "hdc -t ec29004133314d38433031a751c63c00 shell '/data/local/tmp/discovery_final_test'"

# 看到 rx > 0 即成功 ✅
```

---

**准备好开始完整编译了！** 🚀

**关键修正**：不要用 `--build-target rmw_dsoftbus`，直接完整编译即可。
