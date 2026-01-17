#!/bin/bash
# 跨设备 Session 通信测试

echo "=========================================="
echo "  跨设备 Session 通信测试"
echo "=========================================="
echo ""

# 获取所有在线设备
DEVICES=($(powershell.exe -Command "hdc list targets" 2>&1 | grep -v "^$" | awk '{print $1}' | tr -d '\r\n'))

echo "在线设备: ${#DEVICES[@]}"

if [ ${#DEVICES[@]} -lt 2 ]; then
    echo "❌ 需要至少 2 个设备"
    echo "当前在线: ${#DEVICES[@]}"
    exit 1
fi

DEVICE1="${DEVICES[0]}"
DEVICE2="${DEVICES[1]}"

echo "设备 1: $DEVICE1"
echo "设备 2: $DEVICE2"

echo ""
echo "=== 获取设备 Network ID ==="

echo "设备 1 Network ID:"
NID1=$(powershell.exe -Command "hdc -t $DEVICE1 shell '/data/local/tmp/rmw_complete_test' 2>&1" | grep "NetworkID:" | head -1 | awk '{print $2}')
echo "$NID1"

echo ""
echo "设备 2 Network ID:"
NID2=$(powershell.exe -Command "hdc -t $DEVICE2 shell '/data/local/tmp/rmw_complete_test' 2>&1" | grep "NetworkID:" | head -1 | awk '{print $2}')
echo "$NID2"

echo ""
echo "=========================================="
echo "  启动跨设备测试"
echo "=========================================="
echo ""

echo "设备 1: 作为 Session Server（等待连接）"
echo "设备 2: 作为 Client（发起连接）"

echo ""
echo "按任意键开始测试..."
read -n 1

echo ""
echo "=== 在设备 1 上启动 Session Server ==="
powershell.exe -Command "hdc -t $DEVICE1 shell '/data/local/tmp/rmw_complete_test server' &" 2>&1 &

sleep 3

echo ""
echo "=== 在设备 2 上启动 Client（连接到设备 1）==="
powershell.exe -Command "hdc -t $DEVICE2 shell '/data/local/tmp/rmw_complete_test client $NID1' 2>&1" | tee cross_device_result.log

echo ""
echo "=== 跨设备测试完成 ==="
