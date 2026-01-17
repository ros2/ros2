# 产品名称修正记录

**日期**: 2026-01-06
**最终正确产品名**: `khs_3588s_sbc`

---

## 📋 修正历史

### 修正1 (2026-01-06 早些时候)
- **错误**: `rk3588`
- **修正为**: `khd_rk3588s_sbc`
- **原因**: 第一次确认Kaihong定制产品名称

### 修正2 (2026-01-06 现在)
- **错误**: `khd_rk3588s_sbc`
- **修正为**: `khs_3588s_sbc`
- **原因**: 用户提供了准确的产品名称

---

## ✅ 最终确认

**正确的产品名称**: `khs_3588s_sbc`

### 编译命令
```bash
./build.sh --product-name khs_3588s_sbc --build-target rmw_dsoftbus --ccache
```

### 输出路径
```
out/khs_3588s_sbc/
├── communication/rmw_dsoftbus/
│   ├── librmw_dsoftbus.so
│   └── rmw_discovery_daemon
└── packages/phone/images/
    ├── system.img
    ├── vendor.img
    └── userdata.img
```

### 产品配置文件
```
productdefine/common/products/khs_3588s_sbc.json
```

---

## 📝 已修正的文档

### 核心文档 ✅
1. `docs/ohos/OPENHARMONY_GN_INTEGRATION_GUIDE.md`
   - 第5.2节：产品配置文件路径
   - 第6.1节：编译命令
   - 第6.2节：输出路径
   - 第6.3节：刷写命令

2. `SOLUTION2_EXECUTION_PLAN.md`
   - Phase 4：编译命令
   - Phase 5：刷写路径

3. `CORRECTION_SUMMARY_2026-01-06.md`
   - 文档头部添加产品名称说明

### 新增文档 ✅
4. `PRODUCT_NAME_CORRECTION.md` (本文件)
   - 修正历史记录
   - 最终确认的产品名称

---

## 🔍 产品名称解析

### 名称结构
```
khs_3588s_sbc
│││  │    │││
│││  │    ││└─ sbc (single board computer)
│││  │    │└── s (series/standard)
│││  └────┴─── 3588 (RK3588芯片型号)
││└────────── h (可能是Harmony/HongMeng)
│└─────────── s (可能是system/standard)
└──────────── k (Kaihong 开鸿)
```

### 推测
- **khs**: Kaihong Harmony Standard / Kaihong HongMeng System
- **3588s**: RockChip RK3588S 芯片
- **sbc**: Single Board Computer（单板计算机）

---

## 🎯 关键命令速查

### 编译
```bash
# 单组件编译
./build.sh --product-name khs_3588s_sbc --build-target rmw_dsoftbus --ccache

# 完整编译
./build.sh --product-name khs_3588s_sbc --ccache
```

### 刷写
```bash
# 刷写system分区
fastboot flash system out/khs_3588s_sbc/packages/phone/images/system.img

# 刷写完整镜像
cd out/khs_3588s_sbc/packages/phone/images/
fastboot flash system system.img
fastboot flash vendor vendor.img
fastboot flash userdata userdata.img
```

### 验证
```bash
# 检查编译输出
ls -lh out/khs_3588s_sbc/communication/rmw_dsoftbus/

# 检查镜像
ls -lh out/khs_3588s_sbc/packages/phone/images/system.img
```

---

## 📊 与其他产品名称对比

| 环境 | 产品名 | 说明 |
|------|--------|-----|
| 标准OpenHarmony | `rk3588` | 通用RK3588产品 |
| Kaihong定制 | `khs_3588s_sbc` | ✅ **当前使用** |
| 其他可能 | `khd_rk3588s_sbc` | ❌ 错误（之前误用） |

---

## ⚠️ 重要提醒

### 确保使用正确的产品名称

在以下场景中必须使用 `khs_3588s_sbc`：

1. **编译时** ✅
   ```bash
   ./build.sh --product-name khs_3588s_sbc
   ```

2. **修改产品配置时** ✅
   ```bash
   vim productdefine/common/products/khs_3588s_sbc.json
   ```

3. **查找输出文件时** ✅
   ```bash
   ls out/khs_3588s_sbc/
   ```

4. **文档中引用时** ✅
   - BUILD.gn注释
   - bundle.json说明
   - README文档

---

## 🔗 相关文档

- `docs/ohos/OPENHARMONY_GN_INTEGRATION_GUIDE.md` - 完整集成指南（已修正）
- `SOLUTION2_EXECUTION_PLAN.md` - 执行计划（已修正）
- `WHY_MUST_FLASH_SYSTEM.md` - 为什么必须刷系统
- `CORRECTION_SUMMARY_2026-01-06.md` - 修正总结

---

**最终确认**: 所有文档已更新为正确的产品名称 `khs_3588s_sbc` ✅

**更新时间**: 2026-01-06 05:50 UTC
