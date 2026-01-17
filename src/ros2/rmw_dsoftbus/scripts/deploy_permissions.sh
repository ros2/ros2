#!/bin/bash

################################################################################
# SoftBus 权限配置文件快速部署脚本
# 用途: 一键部署 softbus_trans_permission.json 到多台 KaihongOS 设备
# 用法: bash deploy_permissions.sh [--reboot] [--devices device_id1,device_id2,...]
################################################################################

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 配置
SOURCE_FILE="/mnt/c/tmp/hdc_deploy/softbus_trans_permission.json"
TARGET_PATH="/system/etc/communication/softbus/softbus_trans_permission.json"
BACKUP_SUFFIX=".bak"
DEVICE_IDS=()
AUTO_REBOOT=false

################################################################################
# 函数定义
################################################################################

print_header() {
    echo -e "${BLUE}=================================================================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}=================================================================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

# 检查源文件
check_source_file() {
    if [ ! -f "$SOURCE_FILE" ]; then
        print_error "源文件不存在: $SOURCE_FILE"
        exit 1
    fi
    print_success "源文件找到: $SOURCE_FILE"
}

# 获取设备列表
get_device_list() {
    if [ ${#DEVICE_IDS[@]} -eq 0 ]; then
        print_info "扫描在线设备..."
        mapfile -t DEVICE_IDS < <(powershell.exe -NoProfile -Command "hdc list targets 2>&1" | grep -E '^[a-f0-9]{32}' || true)

        if [ ${#DEVICE_IDS[@]} -eq 0 ]; then
            print_error "未找到在线设备"
            exit 1
        fi
    fi

    print_success "找到 ${#DEVICE_IDS[@]} 台设备"
}

# 备份原文件
backup_file() {
    local device=$1
    print_info "备份原文件..."

    local result=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'cp $TARGET_PATH $TARGET_PATH$BACKUP_SUFFIX 2>&1 && echo OK || echo FAILED'" 2>&1 | tail -1 | tr -d '\r')

    if [ "$result" = "OK" ]; then
        print_success "备份完成"
    else
        print_warning "备份可能失败，继续部署"
    fi
}

# 发送文件
send_file() {
    local device=$1
    print_info "发送权限配置文件..."

    local result=$(powershell.exe -NoProfile -Command "hdc -t $device file send 'C:\tmp\hdc_deploy\softbus_trans_permission.json' '$TARGET_PATH' 2>&1" 2>&1)

    if echo "$result" | grep -q "FileTransfer finish"; then
        print_success "文件发送成功"
    else
        print_error "文件发送失败"
        return 1
    fi
}

# 设置权限
set_permission() {
    local device=$1
    print_info "设置文件权限为 644..."

    local result=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'chmod 644 $TARGET_PATH 2>&1 && echo OK || echo FAILED'" 2>&1 | tail -1 | tr -d '\r')

    if [ "$result" = "OK" ]; then
        print_success "权限设置成功"
    else
        print_error "权限设置失败"
        return 1
    fi
}

# 验证文件
verify_file() {
    local device=$1
    print_info "验证文件内容..."

    local content=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'cat $TARGET_PATH'" 2>&1)

    if echo "$content" | grep -q "com.softbus.graph.discovery"; then
        print_success "文件内容验证成功"
    else
        print_error "文件内容验证失败"
        return 1
    fi
}

# 重启服务
restart_service() {
    local device=$1
    print_info "重启 DSoftBus 服务..."

    powershell.exe -NoProfile -Command "hdc -t $device shell 'killall softbus_server softbus_daemon 2>&1; sleep 2; echo OK'" 2>&1 > /dev/null

    sleep 3

    local pids=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'pidof softbus_server softbus_daemon 2>/dev/null || echo NONE'" 2>&1 | tail -1 | tr -d '\r')

    if [ "$pids" != "NONE" ] && [ ! -z "$pids" ]; then
        print_success "DSoftBus 服务已重启"
    else
        print_warning "DSoftBus 服务未运行（可能在启动中）"
    fi
}

# 部署单个设备
deploy_device() {
    local device=$1

    echo ""
    echo -e "${YELLOW}════════════════════════════════════════${NC}"
    echo -e "${YELLOW}部署设备: $device${NC}"
    echo -e "${YELLOW}════════════════════════════════════════${NC}"

    backup_file "$device" || return 1
    send_file "$device" || return 1
    set_permission "$device" || return 1
    verify_file "$device" || return 1
    restart_service "$device" || return 1

    print_success "设备 $device 部署完成"
}

# 重启所有设备
reboot_devices() {
    print_warning "将重启所有设备（等待 2-3 分钟）"

    for device in "${DEVICE_IDS[@]}"; do
        echo "重启设备: $device"
        powershell.exe -NoProfile -Command "hdc -t $device target boot" 2>&1 | tail -1
        sleep 2
    done

    print_success "设备重启命令已发送"
}

# 显示使用帮助
show_help() {
    cat << EOF
使用方法: bash deploy_permissions.sh [选项]

选项:
    -h, --help              显示帮助信息
    -r, --reboot            部署后重启设备
    -d, --devices LIST      指定设备ID列表（逗号分隔），例如: -d device1,device2

示例:
    # 自动发现并部署到所有在线设备
    bash deploy_permissions.sh

    # 部署后重启设备
    bash deploy_permissions.sh --reboot

    # 仅部署到指定设备
    bash deploy_permissions.sh -d ec29004133314d38433031a522413c00

    # 部署到多个指定设备并重启
    bash deploy_permissions.sh -d device1,device2 --reboot

EOF
}

################################################################################
# 主程序
################################################################################

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -r|--reboot)
            AUTO_REBOOT=true
            shift
            ;;
        -d|--devices)
            IFS=',' read -ra DEVICE_IDS <<< "$2"
            shift 2
            ;;
        *)
            print_error "未知选项: $1"
            show_help
            exit 1
            ;;
    esac
done

# 执行部署流程
print_header "SoftBus 权限配置文件部署工具"

check_source_file
get_device_list

print_info "准备部署到 ${#DEVICE_IDS[@]} 台设备"
echo ""

# 部署到每个设备
for device in "${DEVICE_IDS[@]}"; do
    deploy_device "$device" || print_warning "设备 $device 部署失败，继续下一个设备"
done

# 可选重启
if [ "$AUTO_REBOOT" = true ]; then
    echo ""
    reboot_devices
fi

# 部署完成
echo ""
print_header "部署完成"
print_success "SoftBus 权限配置文件已部署到 ${#DEVICE_IDS[@]} 台设备"

if [ "$AUTO_REBOOT" = false ]; then
    print_info "建议手动重启设备以确保新权限配置生效"
    echo ""
    echo "重启设备命令:"
    for device in "${DEVICE_IDS[@]}"; do
        echo "  powershell.exe -NoProfile -Command \"hdc -t $device target boot\""
    done
fi

echo ""
