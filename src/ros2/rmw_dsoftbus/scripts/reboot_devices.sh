#!/bin/bash

################################################################################
# KaihongOS 设备重启脚本
# 用途: 重启指定的 KaihongOS 开发板
# 用法: bash reboot_devices.sh [device_id1] [device_id2] ...
################################################################################

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_header() {
    echo -e "${BLUE}=================================================================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}=================================================================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

# 获取设备列表
if [ $# -eq 0 ]; then
    # 自动发现所有设备
    print_info "扫描在线设备..."
    mapfile -t DEVICES < <(powershell.exe -NoProfile -Command "hdc list targets 2>&1" | grep -E '^[a-f0-9]{32}' || true)
    
    if [ ${#DEVICES[@]} -eq 0 ]; then
        echo "未找到在线设备"
        exit 1
    fi
else
    # 使用指定的设备
    DEVICES=("$@")
fi

print_header "KaihongOS 设备重启工具"
print_info "将重启 ${#DEVICES[@]} 台设备（每台需要 2-3 分钟）"
echo ""

# 确认
read -p "确认重启这些设备吗? (yes/no): " confirm
if [ "$confirm" != "yes" ]; then
    print_warning "已取消重启"
    exit 0
fi

echo ""

# 重启每个设备
for i in "${!DEVICES[@]}"; do
    device="${DEVICES[$i]}"
    echo -e "${YELLOW}────────────────────────────────────────${NC}"
    echo "设备 $((i+1))/${#DEVICES[@]}: $device"
    echo -e "${YELLOW}────────────────────────────────────────${NC}"
    
    print_info "发送重启命令..."
    powershell.exe -NoProfile -Command "hdc -t $device target boot" 2>&1 | tail -2
    
    print_success "重启命令已发送"
    print_info "等待设备重启（约 2-3 分钟）..."
    
    if [ $i -lt $((${#DEVICES[@]}-1)) ]; then
        sleep 60
        echo "继续重启下一个设备..."
        echo ""
    fi
done

echo ""
print_header "所有设备重启命令已发送"
print_info "请等待 ${#DEVICES[@]} × 3 分钟确保所有设备重启完成"
print_info "完成后可运行验证脚本检查权限配置是否生效"
echo ""
