#!/bin/bash

################################################################################
# DSoftBus权限配置部署脚本
# 功能: 在指定设备上搜索、备份并部署新的DSoftBus权限配置文件
# 用法: ./deploy_softbus_permission.sh <DEVICE_ID> <CONFIG_FILE> [--no-reboot]
# 例子: ./deploy_softbus_permission.sh ec29004133314d38433031a522413c00 ./softbus_trans_permission.json
################################################################################

set -e

# 参数检查
if [ -z "$1" ] || [ -z "$2" ]; then
    echo "错误: 参数不完整"
    echo ""
    echo "用法: $0 <DEVICE_ID> <CONFIG_FILE> [--no-reboot]"
    echo ""
    echo "参数说明:"
    echo "  DEVICE_ID      - 目标设备ID"
    echo "  CONFIG_FILE    - 新配置文件路径 (本地WSL路径)"
    echo "  --no-reboot    - (可选) 部署后不重启设备"
    echo ""
    echo "示例:"
    echo "  $0 ec29004133314d38433031a522413c00 /mnt/c/tmp/hdc_deploy/softbus_trans_permission.json"
    echo ""
    echo "获取设备ID:"
    echo "  powershell.exe -NoProfile -Command \"hdc list targets\""
    exit 1
fi

DEVICE_ID="$1"
CONFIG_FILE_WSL="$2"
NO_REBOOT="${3:-}"
PERM_FILE="/system/etc/communication/softbus/softbus_trans_permission.json"

# 转换WSL路径为Windows路径
if [[ "$CONFIG_FILE_WSL" == /mnt/c/* ]]; then
    CONFIG_FILE_WIN=$(echo "$CONFIG_FILE_WSL" | sed 's|/mnt/c/|C:\\|g' | sed 's|/|\\|g')
else
    echo "错误: 配置文件必须在 /mnt/c/ 目录中 (Windows可访问路径)"
    echo "当前路径: $CONFIG_FILE_WSL"
    echo ""
    echo "请将文件复制到 /mnt/c/ 下, 例如:"
    echo "  cp $CONFIG_FILE_WSL /mnt/c/tmp/hdc_deploy/"
    exit 1
fi

# 检查本地文件是否存在
if [ ! -f "$CONFIG_FILE_WSL" ]; then
    echo "错误: 配置文件不存在"
    echo "路径: $CONFIG_FILE_WSL"
    exit 1
fi

echo "============================================================"
echo "DSoftBus权限配置部署"
echo "============================================================"
echo ""
echo "设备ID: $DEVICE_ID"
echo "配置文件(WSL): $CONFIG_FILE_WSL"
echo "配置文件(Win): $CONFIG_FILE_WIN"
echo "目标路径: $PERM_FILE"
echo ""

# Step 1: 验证设备连接
echo "[1/7] 检查设备连接..."
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

# Step 2: 搜索权限配置文件
echo "[2/7] 搜索现有权限配置文件..."
FOUND_FILES=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'find /system /etc /vendor /data -name softbus_trans_permission.json -type f 2>/dev/null | head -5'")

if [ -z "$FOUND_FILES" ]; then
    echo "未找到现有配置文件，将在标准位置创建"
    FOUND_FILES="$PERM_FILE"
else
    echo "找到的配置文件:"
    echo "$FOUND_FILES" | while read line; do
        echo "  - $line"
    done
fi
echo ""

# Step 3: 创建目录并挂载为可写
echo "[3/7] 准备文件系统..."
PERM_DIR=$(dirname "$PERM_FILE")
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'mkdir -p $PERM_DIR'" 2>/dev/null || true
echo "✓ 目录已创建/验证"
echo ""

# Step 4: 备份现有文件
echo "[4/7] 备份原文件..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'cp $PERM_FILE $PERM_FILE.bak 2>/dev/null; true'"
BACKUP_CHECK=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'test -f $PERM_FILE.bak && echo YES || echo NO'")

if [[ "$BACKUP_CHECK" == *"YES"* ]]; then
    echo "✓ 备份已创建"
else
    echo "! 备份失败或无原文件 (将继续部署)"
fi
echo ""

# Step 5: 部署新配置文件
echo "[5/7] 部署新配置文件..."
echo "  传输中..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send '$CONFIG_FILE_WIN' '$PERM_FILE'"
echo "✓ 文件已传输"
echo ""

# Step 6: 验证部署
echo "[6/7] 验证部署..."
FILE_EXISTS=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'test -f $PERM_FILE && echo YES || echo NO'")

if [[ ! "$FILE_EXISTS" == *"YES"* ]]; then
    echo "✗ 文件传输失败"
    exit 1
fi

echo "✓ 文件存在"

# 验证内容
CONTENT_CHECK=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'grep -c \"com.huawei.ros2_rmw_dsoftbus\" $PERM_FILE 2>/dev/null || echo 0'")
echo "✓ 配置条目: $CONTENT_CHECK"

# MD5校验
LOCAL_MD5=$(md5sum "$CONFIG_FILE_WSL" | awk '{print $1}')
DEVICE_MD5=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'md5sum $PERM_FILE'" | awk '{print $1}')

if [ "$LOCAL_MD5" = "$DEVICE_MD5" ]; then
    echo "✓ MD5校验: 一致"
else
    echo "! MD5校验: 不一致 (LOCAL: $LOCAL_MD5, DEVICE: $DEVICE_MD5)"
fi
echo ""

# Step 7: 重启处理
echo "[7/7] 设备重启处理..."

if [ "$NO_REBOOT" = "--no-reboot" ]; then
    echo "! 已跳过自动重启 (使用了 --no-reboot 选项)"
    echo ""
    echo "要使配置生效，请手动重启设备:"
    echo "  powershell.exe -NoProfile -Command \"hdc -t $DEVICE_ID shell 'reboot'\""
else
    echo "准备重启设备..."
    powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'killall softbus_server 2>/dev/null; true'"
    powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'killall softbus_daemon 2>/dev/null; true'"
    sleep 2
    powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'reboot'"
    echo "✓ 重启命令已发送"
    echo "  等待设备启动... (约90秒)"
fi

echo ""
echo "============================================================"
echo "部署完成"
echo "============================================================"
echo ""
echo "下一步:"
echo "  1. 等待设备启动 (约90秒)"
echo "  2. 验证配置:"
echo "     hdc -t $DEVICE_ID shell 'cat $PERM_FILE'"
echo "  3. 检查DSoftBus服务:"
echo "     hdc -t $DEVICE_ID shell 'ps aux | grep softbus'"
echo ""

# 可选的自动等待
if [ "$NO_REBOOT" != "--no-reboot" ]; then
    echo -n "是否等待设备启动并验证? (y/n) [default: n] "
    read -r WAIT_RESPONSE

    if [[ "$WAIT_RESPONSE" == "y" || "$WAIT_RESPONSE" == "Y" ]]; then
        echo "等待设备上线..."
        for i in {1..30}; do
            DEVICE_STATUS=$(powershell.exe -NoProfile -Command "hdc list targets" | grep "$DEVICE_ID" | wc -l)
            if [ "$DEVICE_STATUS" -eq 1 ]; then
                echo "✓ 设备已上线"
                sleep 5
                echo ""
                echo "验证配置文件:"
                powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'cat $PERM_FILE'"
                break
            fi
            echo -n "."
            sleep 3
        done
    fi
fi
