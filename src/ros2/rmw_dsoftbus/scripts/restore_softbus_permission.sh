#!/bin/bash

################################################################################
# DSoftBus权限配置恢复脚本
# 功能: 从备份(.bak)文件恢复原始DSoftBus权限配置
# 用法: ./restore_softbus_permission.sh <DEVICE_ID>
# 例子: ./restore_softbus_permission.sh ec29004133314d38433031a522413c00
################################################################################

set -e

# 参数检查
if [ -z "$1" ]; then
    echo "错误: 未指定设备ID"
    echo "用法: $0 <DEVICE_ID>"
    echo ""
    echo "示例:"
    echo "  $0 ec29004133314d38433031a522413c00"
    echo ""
    echo "获取设备ID:"
    echo "  powershell.exe -NoProfile -Command \"hdc list targets\""
    exit 1
fi

DEVICE_ID="$1"
PERM_FILE="/system/etc/communication/softbus/softbus_trans_permission.json"
BACKUP_FILE="${PERM_FILE}.bak"

echo "============================================================"
echo "DSoftBus权限配置恢复"
echo "============================================================"
echo ""
echo "设备ID: $DEVICE_ID"
echo "恢复文件: $BACKUP_FILE"
echo "目标文件: $PERM_FILE"
echo ""

# Step 1: 验证设备连接
echo "[1/5] 检查设备连接..."
DEVICE_CHECK=$(powershell.exe -NoProfile -Command "hdc list targets" | grep "$DEVICE_ID" | wc -l)

if [ "$DEVICE_CHECK" -eq 0 ]; then
    echo "错误: 设备 $DEVICE_ID 未找到"
    echo ""
    echo "已连接的设备:"
    powershell.exe -NoProfile -Command "hdc list targets"
    exit 1
fi

echo "✓ 设备已连接"
echo ""

# Step 2: 检查备份文件存在
echo "[2/5] 检查备份文件..."
BACKUP_EXISTS=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'test -f $BACKUP_FILE && echo YES || echo NO'")

if [[ ! "$BACKUP_EXISTS" == *"YES"* ]]; then
    echo "错误: 备份文件不存在"
    echo "备份位置: $BACKUP_FILE"
    echo ""
    echo "查看可用文件:"
    powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ls -lh /system/etc/communication/softbus/'"
    exit 1
fi

echo "✓ 备份文件存在"
echo ""

# Step 3: 挂载为可写
echo "[3/5] 挂载文件系统为可写..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'mount -o remount,rw /system 2>/dev/null || true'"
echo "✓ 文件系统已处理"
echo ""

# Step 4: 恢复文件
echo "[4/5] 恢复权限配置文件..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'cp $BACKUP_FILE $PERM_FILE'"
echo "✓ 文件已恢复"
echo ""

# Step 5: 验证恢复
echo "[5/5] 验证恢复..."
echo "恢复后的文件信息:"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ls -lh $PERM_FILE'"

echo ""
echo "============================================================"
echo "恢复完成"
echo "============================================================"
echo ""
echo "下一步:"
echo "  1. 重启设备: hdc -t $DEVICE_ID shell 'reboot'"
echo "  2. 等待设备启动 (约90秒)"
echo "  3. 验证配置: hdc -t $DEVICE_ID shell 'cat $PERM_FILE'"
echo ""

# 询问是否立即重启
echo -n "是否立即重启设备? (y/n) [default: n] "
read -r RESPONSE

if [[ "$RESPONSE" == "y" || "$RESPONSE" == "Y" ]]; then
    echo "重启设备..."
    powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'reboot'"
    echo "设备正在重启，请等待约90秒..."
else
    echo "取消重启。请手动重启设备以使改动生效。"
fi
