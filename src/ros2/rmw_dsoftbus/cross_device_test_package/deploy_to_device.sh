#!/bin/bash
# 跨设备测试部署脚本

if [ -z "$1" ]; then
    echo "用法: $0 <设备ID>"
    echo ""
    echo "示例: $0 ec29004133314d38433031a522413c00"
    exit 1
fi

DEVICE_ID="$1"

echo "=========================================="
echo "  部署到设备: $DEVICE_ID"
echo "=========================================="
echo ""

echo "=== 1. 部署配置文件 ==="

# 准备 Windows 路径
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cp "$SCRIPT_DIR/softbus_trans_permission.json" /mnt/c/tmp/

# 上传配置文件
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\\tmp\\softbus_trans_permission.json /data/local/tmp/" | grep -v "^$"

# 替换系统配置文件
powershell.exe -Command "hdc -t $DEVICE_ID shell 'cat /data/local/tmp/softbus_trans_permission.json > /system/etc/communication/softbus/softbus_trans_permission.json'" 2>&1

echo "✅ 配置文件已部署"

echo ""
echo "=== 2. 部署测试程序 ==="

cp "$SCRIPT_DIR/rmw_complete_test" /mnt/c/tmp/
powershell.exe -Command "hdc -t $DEVICE_ID file send C:\\tmp\\rmw_complete_test /data/local/tmp/" | grep -v "^$"
powershell.exe -Command "hdc -t $DEVICE_ID shell chmod +x /data/local/tmp/rmw_complete_test"

echo "✅ 测试程序已部署"

echo ""
echo "=== 3. 验证部署 ==="

powershell.exe -Command "hdc -t $DEVICE_ID shell 'ls -lh /data/local/tmp/rmw_complete_test'" 2>&1
powershell.exe -Command "hdc -t $DEVICE_ID shell 'cat /system/etc/communication/softbus/softbus_trans_permission.json | head -10'" 2>&1

echo ""
echo "✅ 部署完成！"
echo ""
echo "建议: 重启设备以加载新配置"
echo "  powershell.exe -Command \"hdc -t $DEVICE_ID shell reboot\""
