#!/bin/bash
#
# Graph Discovery Test Runner
# Runs cross-device session test on two OpenHarmony devices
#

set -e

# Device IDs
DEVICE1="ec29004133314d38433031a522413c00"
DEVICE2="ec29004133314d38433031a5544f3c00"

# Test binary path
TEST_BIN="/data/local/tmp/graph_discovery_test"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Helper functions
log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check devices are connected
check_devices() {
    log_info "Checking device connectivity..."

    local devices=$(powershell.exe -NoProfile -Command "hdc list targets" | grep -v "COM" | grep -v "^$" | tr -d '\r')

    if echo "$devices" | grep -q "$DEVICE1"; then
        log_success "Device 1 connected: $DEVICE1"
    else
        log_error "Device 1 not connected: $DEVICE1"
        exit 1
    fi

    if echo "$devices" | grep -q "$DEVICE2"; then
        log_success "Device 2 connected: $DEVICE2"
    else
        log_error "Device 2 not connected: $DEVICE2"
        exit 1
    fi
}

# Verify test binary exists on devices
verify_binary() {
    log_info "Verifying test binary on devices..."

    local result1=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell ls -l $TEST_BIN" 2>&1 | grep "graph_discovery_test" || true)
    if [ -n "$result1" ]; then
        log_success "Binary found on Device 1"
    else
        log_error "Binary not found on Device 1. Please deploy first."
        exit 1
    fi

    local result2=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell ls -l $TEST_BIN" 2>&1 | grep "graph_discovery_test" || true)
    if [ -n "$result2" ]; then
        log_success "Binary found on Device 2"
    else
        log_error "Binary not found on Device 2. Please deploy first."
        exit 1
    fi
}

# Run server on Device 1
run_server() {
    log_info "Starting server on Device 1..."
    log_warn "Server will run for 60 seconds or until data is received."
    log_warn "Press Ctrl+C to stop manually."
    echo ""

    powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell cd /data/local/tmp '&&' ./graph_discovery_test server"
}

# Run client on Device 2
run_client() {
    local peer_id="$1"

    log_info "Starting client on Device 2..."

    if [ -z "$peer_id" ]; then
        log_info "Using auto-discovery mode"
        powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell cd /data/local/tmp '&&' ./graph_discovery_test client"
    else
        log_info "Connecting to peer: $peer_id"
        powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell cd /data/local/tmp '&&' ./graph_discovery_test client $peer_id"
    fi
}

# Run both devices concurrently
run_concurrent() {
    log_info "Running server and client concurrently..."
    log_warn "Server on Device 1, Client on Device 2"
    log_warn "This will run in background. Check output files for results."
    echo ""

    # Start server in background
    log_info "Starting server on Device 1 (background)..."
    powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell cd /data/local/tmp '&&' ./graph_discovery_test server" > /tmp/graph_test_server.log 2>&1 &
    local server_pid=$!

    sleep 3

    # Start client
    log_info "Starting client on Device 2..."
    powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell cd /data/local/tmp '&&' ./graph_discovery_test client" > /tmp/graph_test_client.log 2>&1

    # Wait for server to finish
    wait $server_pid

    log_success "Test completed!"
    log_info "Server log: /tmp/graph_test_server.log"
    log_info "Client log: /tmp/graph_test_client.log"
    echo ""
    echo "=== Server Output ==="
    cat /tmp/graph_test_server.log
    echo ""
    echo "=== Client Output ==="
    cat /tmp/graph_test_client.log
}

# Get device network ID
get_network_id() {
    local device_id="$1"
    local device_name="$2"

    log_info "Getting network ID from $device_name..."
    powershell.exe -NoProfile -Command "hdc -t $device_id shell cd /data/local/tmp '&&' ./graph_discovery_test server" 2>&1 | grep "Local device:" | awk -F'NetworkID: ' '{print $2}' | tr -d ')' | tr -d '\r' | tr -d '\n'
}

# Show usage
usage() {
    cat << EOF
Usage: $0 <command> [options]

Commands:
    check           Check device connectivity and binary deployment
    server          Run as server on Device 1
    client [ID]     Run as client on Device 2 (optional peer network ID)
    concurrent      Run server and client concurrently (auto-discovery)
    network-id      Get network ID from Device 1

Examples:
    $0 check                          # Verify setup
    $0 server                         # Run server on Device 1
    $0 client                         # Run client on Device 2 (auto-discover)
    $0 client <network_id>           # Run client with specific peer
    $0 concurrent                     # Run both concurrently
    $0 network-id                     # Get Device 1 network ID

Device IDs:
    Device 1: $DEVICE1
    Device 2: $DEVICE2

EOF
}

# Main
main() {
    local command="${1:-}"

    case "$command" in
        check)
            check_devices
            verify_binary
            log_success "All checks passed!"
            ;;
        server)
            check_devices
            verify_binary
            run_server
            ;;
        client)
            check_devices
            verify_binary
            run_client "$2"
            ;;
        concurrent)
            check_devices
            verify_binary
            run_concurrent
            ;;
        network-id)
            check_devices
            verify_binary
            local net_id=$(get_network_id "$DEVICE1" "Device 1")
            if [ -n "$net_id" ]; then
                log_success "Device 1 Network ID: $net_id"
            else
                log_error "Failed to get network ID"
                exit 1
            fi
            ;;
        help|--help|-h)
            usage
            ;;
        *)
            log_error "Unknown command: $command"
            echo ""
            usage
            exit 1
            ;;
    esac
}

main "$@"
