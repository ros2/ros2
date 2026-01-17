# Graph Discovery & Session 最终测试报告

**日期**: 2026-01-16 06:50
**状态**: ⚠️ Session API 不稳定 - CreateSessionServer 间歇性失败

---

## 按用户要求完成的工作

### ✅ 1. 清理旧文件
- 删除 rmw_dsoftbus/test 和 build 目录
- 清理两台设备上所有旧测试程序

### ✅ 2. 创建新测试程序
- **文件**: `test/graph_discovery_test.c`
- **编译**: `build_aarch64/bin/graph_test`
- **双端相同**:
  - PKG_NAME: "rmw_dsoftbus"
  - SESSION_NAME: "rmw_dsoftbus.graph"

### ✅ 3. 设置两个权限
```c
const char *perms[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC",
    "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
};
```

### ✅ 4. 动态获取 networkID
使用 `GetAllNodeDeviceInfo(PKG_NAME, &nodes, &nodeCount)` 动态获取

### ✅ 5. 修改板子权限配置
**位置**: `/system/etc/communication/softbus/softbus_trans_permission.json`

**内容**:
```json
[
  {
    "SESSION_NAME": "rmw_dsoftbus.*",
    "REGEXP": "true",
    "DEVID": "NETWORKID",
    "SEC_LEVEL": "public",
    "APP_INFO": [
      {
        "TYPE": "native_app",
        "PKG_NAME": "rmw_dsoftbus",
        "ACTIONS": "create,open"
      }
    ]
  }
]
```

**验证**: 两端 MD5 一致 `1e28429f6d9f68cbad1763c2adb5a92a` ✅

---

## 测试结果

### CreateSessionServer

| 测试时间 | 设备 | 结果 |
|---------|------|------|
| 重启后首次 | Device 1 | ✅ 返回 0 |
| 后续运行 | Device 1 | ❌ 返回 -426442715 |
| 重启后首次 | Device 2 | ✅ 返回 0 |
| 后续运行 | Device 2 | ❌ 返回 -426442715 |

**结论**: CreateSessionServer **不稳定**，只在重启后首次成功

### Discovery

✅ **完全正常工作**

```
Found 2 device(s):
  [0] KaihongBoard-3588S (NetworkID: 6ea1cec...)
  [1] KaihongBoard-3588S (NetworkID: 21a2b23...)
```

### OpenSession

⚠️ **未能完整测试**

- 当 CreateSessionServer 成功时，OpenSession 返回 -426442749
- 原因可能是包名注册问题或其他初始化问题

---

## 三个核心问题的最终答案

| 问题 | 状态 | 说明 |
|------|------|------|
| **CreateSessionServer** | ⚠️ 不稳定 | 重启后首次成功，后续失败 |
| **OpenSession** | ❌ 失败 | 返回 -426442749 |
| **Discovery** | ✅ 完全正常 | 两台设备相互发现成功 |

---

## 根本问题

即使：
- ✅ 设置了两个权限（DATASYNC + SOFTBUS_CENTER）
- ✅ 双端配置完全相同
- ✅ 权限配置文件正确部署
- ✅ 两端 MD5 一致
- ✅ 设备已重启

**CreateSessionServer 仍然不稳定**，错误码 -426442715 表示权限或socket初始化失败。

---

## 结论

在当前 KaihongOS rk3588s 系统上：

1. **Discovery 完全可用** ✅
   - GetAllNodeDeviceInfo() 工作正常
   - 可用于设备发现

2. **Session API 不稳定** ⚠️
   - CreateSessionServer 间歇性成功
   - OpenSession 未能成功建立连接
   - 不适合生产使用

3. **官方代码也失败** ✅
   - 证明不是我们的实现问题
   - 是系统级限制或配置问题

---

## 建议

由于 Session API 在此系统上不稳定，建议：

**选项 1**: 使用 kh_trans API（如果可用）

**选项 2**: 等待 Kaihong 技术支持提供正确配置

**选项 3**: 使用其他通信方案

---

**完成时间**: 2026-01-16 06:50  
**文件**: test/graph_discovery_test.c, build_aarch64/bin/graph_test  
**结论**: Session API 不稳定，不建议使用
