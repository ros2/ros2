# dsoftbus Session API 使用注意事项

Date: 2026-01-16
Purpose: 记录关键注意事项，避免常见错误

---

## 核心注意事项

### 1. PKG_NAME 不支持正则表达式

问题: PKG_NAME 字段只支持精确字符串匹配

错误用法:
- PKG_NAME: ".*"  (尝试用正则匹配所有)
- PKG_NAME: "com.huawei.*"  (尝试用正则前缀匹配)

正确用法:
- PKG_NAME: ""  (空字符串跳过验证)
- PKG_NAME: "com.huawei.ros2_rmw_dsoftbus"  (精确匹配)

源码原因: permission_entry.c:374 固定传 false 给正则参数

### 2. Network ID vs Device ID

不要混淆两个概念:

Device ID:
- 长度: 32 字符
- 示例: ec29004133314d38433031a5544f3c00
- 用途: HDC 连接识别
- 获取: hdc list targets

Network ID:
- 长度: 64 字符
- 示例: e05acef96ee6b1b68025cac8b3de7ee95ab6b8bb457051176eafea89cc0d1212
- 用途: dsoftbus 通信识别
- 获取: GetAllNodeDeviceInfo (从对端查询)

错误: 使用 Device ID 调用 OpenSession
正确: 使用 Network ID 调用 OpenSession

### 3. Network ID 必须实时查询

问题: Network ID 可能变化

错误做法:
- 硬编码 Network ID
- 使用几天前查询的 Network ID
- 从本设备查询本设备的 ID

正确做法:
- 每次连接前从对端设备查询
- 使用 GetAllNodeDeviceInfo 实时获取
- 从 Device B 查询看到的就是 Device A 的 ID

设备发现不稳定原因:
- 多台设备间发现有延迟
- 设备可能动态上下线
- Network ID 可能重新生成

### 4. Session Server 生命周期

关键: Session Server 注册与进程绑定

生命周期:
- CreateSessionServer → 注册到 dsoftbus
- 进程运行 → 注册保持有效
- 进程退出 → 注册自动失效
- RemoveSessionServer → 手动移除注册

错误 -426115004 原因:
- 进程已退出但 Client 尝试连接
- RemoveSessionServer 被调用
- Server 在重启间隙

ROS2 建议:
- Node 持续运行直到 shutdown
- 不要有超时退出机制
- 只在 rmw_destroy_node 时清理

### 5. sessionName 必须完全一致

Server 和 Client 的 sessionName 必须完全相同:

大小写敏感:
- "com.huawei.Test" ≠ "com.huawei.test"

空格敏感:
- "com.huawei.test " ≠ "com.huawei.test"

拼写必须完全一致:
- "com.huawei.ros2_rmw_dsoftbus.test"
- "com.huawei.ros2_rmw_dsoftbus.test"

不一致会导致:
- GetPkgNameBySessionName 失败
- 返回 -426115004 (PEER_SESSION_NOT_CREATED)

### 6. SessionAttribute 配置

推荐配置:

dataType:
- TYPE_BYTES (2) - 用于 ROS2 消息 (最大 64KB)
- TYPE_MESSAGE (1) - 小消息 (最大 4KB)

linkTypeNum:
- 0 - 自动选择最优链路
- 非 0 - 手动指定链路类型

linkType:
- NULL - 使用默认配置
- 数组 - 指定特定链路

自动选择优先级: WiFi > Bluetooth > P2P

### 7. 测试环境 vs 生产环境

测试环境特点:
- 测试程序通常有超时机制
- 需要精确的时序控制
- Server 可能自动退出

生产环境特点:
- ROS2 节点持续运行
- 没有超时退出
- Session Server 在整个生命周期有效

结论: 测试环境的时序问题不会出现在 ROS2 中

---

## 常见错误及解决

### 错误 A: CreateSessionServer 返回 -426442743

原因: 权限配置中 PKG_NAME 使用了正则表达式

解决: 使用空字符串 "" 或精确的包名

验证: 部署新配置后重启设备

### 错误 B: OpenSession 返回 -426442706

原因: Network ID 错误或设备不在线

解决:
- 从对端设备实时查询 Network ID
- 确认设备在线 (GetAllNodeDeviceInfo)

验证: OpenSession 应返回正数

### 错误 C: OnSessionOpened callback result=-426115004

原因:
- 对端 Session Server 未创建
- 对端进程已退出
- Network ID 错误
- sessionName 不一致

解决:
- 确保 Server 持续运行
- 使用正确的 Network ID
- 检查 sessionName 拼写

验证: callback result=0

### 错误 D: SendBytes 返回非 0

原因: Session 未成功建立

解决: 先确保 OnSessionOpened result=0

验证: SendBytes 应返回 0

---

## 最佳实践

### 权限配置

使用固定的权限 JSON:
- 文件: softbus_trans_permission_fixed.json
- 部署到所有设备
- 重启生效

### 设备发现

每次连接前查询:
- 从对端设备调用 GetAllNodeDeviceInfo
- 使用返回的 networkId
- 不缓存 Network ID

### Session 管理

Server 端:
- CreateSessionServer 后保持运行
- 等待 Client 连接
- 收到 OnSessionOpened 回调
- 在 OnBytesReceived 中处理消息

Client 端:
- 确认对端在线 (GetAllNodeDeviceInfo)
- OpenSession 连接对端
- 等待 OnSessionOpened callback result=0
- 然后才能 SendBytes

### 错误处理

检查所有返回值:
- CreateSessionServer 返回值
- OpenSession 返回值
- OnSessionOpened callback result
- SendBytes 返回值

记录错误码:
- 根据错误码判断问题类型
- 使用本文档的错误码映射表

---

## ROS2 集成建议

### Node 初始化

在 rmw_create_node 时:
- 调用 CreateSessionServer
- 保存 packageName 和 sessionName
- 注册 Callback 处理函数

### Subscription 创建

在 rmw_create_subscription 时:
- 从 Publisher 获取 Network ID
- 调用 OpenSession
- 等待 OnSessionOpened result=0
- 保存 sessionId 用于接收

### 消息发送

在 rmw_publish 时:
- 序列化 ROS2 消息
- 遍历所有 Subscriber sessions
- 调用 SendBytes 发送

### 消息接收

在 OnBytesReceived callback 中:
- 反序列化消息
- 分发给用户回调

---

## 验证清单

部署前检查:
- 权限配置文件正确
- 测试程序已编译
- 设备可以互相发现

测试时检查:
- CreateSessionServer 返回 0
- OpenSession 返回正数
- OnSessionOpened result=0
- SendBytes 返回 0
- OnBytesReceived 触发

生产部署检查:
- 节点持续运行
- 没有超时退出
- 错误处理完善
- 日志记录完整

---

## 故障排查步骤

问题: CreateSessionServer 失败

步骤:
1. 检查权限配置文件
2. 验证 PKG_NAME 是否为空字符串
3. 重启设备
4. 查看 hilog 中的 permission 相关日志

问题: OpenSession 失败

步骤:
1. 检查 Network ID 是否正确
2. 验证对端设备在线
3. 确认 sessionName 完全一致
4. 检查对端 Session Server 是否创建

问题: OnSessionOpened callback 失败

步骤:
1. 检查返回的 error code
2. 如果是 -426115004，检查对端 Server
3. 如果是 -426442706，检查 Network ID
4. 查看 hilog 详细日志

---

## 参考资料

快速指南:
- tests/QUICK_TEST_CHECKLIST.md
- docs/investigation/2026-01-16/PERMISSION_FIX_QUICK_GUIDE.md

详细教程:
- tests/MANUAL_TEST_TUTORIAL.md
- docs/investigation/2026-01-16/DSOFTBUS_SESSION_AND_KH_TRANS_GUIDE.md

技术深入:
- docs/investigation/2026-01-16/DEEP_INVESTIGATION_REPORT_2026_01_16.md
- docs/investigation/2026-01-16/SUCCESS_COMPLETE_SESSION_TEST_2026_01_16.md

---

Last Updated: 2026-01-16
Status: Verified and production-ready
