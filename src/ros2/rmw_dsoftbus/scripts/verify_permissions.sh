#!/bin/bash

################################################################################
# SoftBus 权限配置验证脚本
# 用途: 验证权限配置文件是否正确部署并生效
# 用法: bash verify_permissions.sh [device_id]
################################################################################

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# 配置
TARGET_PATH="/system/etc/communication/softbus/softbus_trans_permission.json"

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

# 获取设备列表
get_devices() {
    if [ $# -gt 0 ]; then
        # 使用指定的设备
        echo "$1"
    else
        # 自动发现所有设备
        powershell.exe -NoProfile -Command "hdc list targets 2>&1" | grep -E '^[a-f0-9]{32}' || true
    fi
}

# 验证单个设备
verify_device() {
    local device=$1

    echo ""
    echo -e "${YELLOW}════════════════════════════════════════${NC}"
    echo -e "${YELLOW}验证设备: $device${NC}"
    echo -e "${YELLOW}════════════════════════════════════════${NC}"

    # 1. 验证文件是否存在
    print_info "1. 检查文件是否存在..."
    local file_info=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'ls -l $TARGET_PATH 2>&1'" 2>&1 | tail -1 | tr -d '\r')

    if echo "$file_info" | grep -q "$TARGET_PATH"; then
        print_success "文件存在"
        echo "  $file_info"
    else
        print_error "文件不存在"
        return 1
    fi

    # 2. 验证文件权限
    print_info "2. 检查文件权限..."
    local perms=$(echo "$file_info" | awk '{print $1}')
    if [ "$perms" = "-rw-r--r--" ]; then
        print_success "文件权限正确 ($perms)"
    else
        print_warning "文件权限为 $perms（预期: -rw-r--r--）"
    fi

    # 3. 验证文件大小
    print_info "3. 检查文件大小..."
    local size=$(echo "$file_info" | awk '{print $5}')
    if [ "$size" -gt 500 ] && [ "$size" -lt 1000 ]; then
        print_success "文件大小合理 ($size 字节)"
    else
        print_warning "文件大小异常 ($size 字节，预期: ~832 字节)"
    fi

    # 4. 验证关键配置项
    print_info "4. 验证关键配置项..."
    local content=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'cat $TARGET_PATH'" 2>&1)

    local session1="com.huawei.ros2_rmw_dsoftbus.complete_test"
    local session2="com.softbus.graph.discovery"

    if echo "$content" | grep -q "$session1"; then
        print_success "找到会话配置: $session1"
    else
        print_error "缺少会话配置: $session1"
    fi

    if echo "$content" | grep -q "$session2"; then
        print_success "找到会话配置: $session2"
    else
        print_error "缺少会话配置: $session2"
    fi

    # 5. 验证权限级别
    print_info "5. 检查权限级别..."
    if echo "$content" | grep -q '"SEC_LEVEL": "public"'; then
        print_success "权限级别设置为 public"
    else
        print_warning "权限级别未设置为 public"
    fi

    # 6. 验证操作权限
    print_info "6. 检查操作权限..."
    if echo "$content" | grep -q '"ACTIONS": "create,open"'; then
        print_success "操作权限设置正确 (create,open)"
    else
        print_warning "操作权限配置异常"
    fi

    # 7. 检查 DSoftBus 服务状态
    print_info "7. 检查 DSoftBus 服务状态..."
    local pids=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'pidof softbus_server softbus_daemon 2>/dev/null || echo NONE'" 2>&1 | tail -1 | tr -d '\r')

    if [ "$pids" != "NONE" ] && [ ! -z "$pids" ]; then
        print_success "DSoftBus 服务运行中 (PID: $pids)"
    else
        print_warning "DSoftBus 服务未运行"
    fi

    # 8. 检查权限文件修改时间
    print_info "8. 检查权限文件修改时间..."
    local mod_time=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'stat -c %y $TARGET_PATH 2>/dev/null | cut -d. -f1'" 2>&1 | tail -1 | tr -d '\r')

    if [ ! -z "$mod_time" ]; then
        print_success "文件修改时间: $mod_time"
    else
        print_warning "无法获取文件修改时间"
    fi

    # 9. 查看近期 DSoftBus 日志
    print_info "9. 查看近期 DSoftBus 日志..."
    local logs=$(powershell.exe -NoProfile -Command "hdc -t $device shell 'hilog 2>/dev/null | grep -i permission | tail -3 || echo NO_LOGS'" 2>&1 | tail -4)

    if echo "$logs" | grep -qv "NO_LOGS"; then
        print_success "找到权限相关日志"
        echo "$logs" | while read line; do
            echo "  $line" | tr -d '\r'
        done
    else
        print_info "未找到权限相关日志（可能是正常的）"
    fi

    echo ""
    print_success "设备 $device 验证完成"
}

# 显示使用帮助
show_help() {
    cat << EOF
使用方法: bash verify_permissions.sh [选项]

选项:
    -h, --help              显示帮助信息
    device_id               验证指定设备（设备ID）

示例:
    # 验证所有在线设备
    bash verify_permissions.sh

    # 验证指定设备
    bash verify_permissions.sh ec29004133314d38433031a522413c00

EOF
}

################################################################################
# 主程序
################################################################################

# 解析命令行参数
DEVICE_FILTER=""

while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            DEVICE_FILTER="$1"
            shift
            ;;
    esac
done

# 执行验证
print_header "SoftBus 权限配置验证工具"

# 获取设备列表
mapfile -t DEVICES < <(get_devices "$DEVICE_FILTER")

if [ ${#DEVICES[@]} -eq 0 ]; then
    print_error "未找到在线设备"
    exit 1
fi

print_info "找到 ${#DEVICES[@]} 台设备"

# 验证每个设备
for device in "${DEVICES[@]}"; do
    verify_device "$device" || true
done

# 总结
echo ""
print_header "验证完成"
print_info "已验证 ${#DEVICES[@]} 台设备的权限配置"

# 建议
echo ""
print_info "后续建议："
echo "  1. 如果权限配置未生效，请重启设备"
echo "  2. 重启后再次运行此脚本进行验证"
echo "  3. 查看 DSoftBus 日志了解更多信息："
echo "     powershell.exe -NoProfile -Command \"hdc -t <DEVICE_ID> shell 'hilog | grep -i softbus'\""
echo ""
