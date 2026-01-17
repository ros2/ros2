#!/bin/bash
#
# RMW DSoftBus Standalone Test - Deploy and Run Script
# 部署并运行 rmw_dsoftbus 独立测试
#

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RMW_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

print_step() {
    echo -e "${GREEN}[Step $1]${NC} $2"
}

print_error() {
    echo -e "${RED}[Error]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[Warning]${NC} $1"
}

# Check if running in WSL
if ! grep -qi microsoft /proc/version; then
    print_error "This script must run in WSL"
    exit 1
fi

# ============================================================================
# Step 1: Build the test program
# ============================================================================
print_step 1 "Building standalone test..."

cd "$SCRIPT_DIR"
make -f Makefile.standalone clean all

if [ ! -f "build-standalone/rmw_dsoftbus_standalone_test" ]; then
    print_error "Build failed"
    exit 1
fi

# ============================================================================
# Step 2: Get device list
# ============================================================================
print_step 2 "Getting device list..."

DEVICE_LIST=$(powershell.exe -NoProfile -Command "hdc list targets" 2>/dev/null | grep -v "^$" | head -5)

if [ -z "$DEVICE_LIST" ]; then
    print_error "No devices found"
    exit 1
fi

echo "$DEVICE_LIST"

# Get first device ID
DEVICE_ID=$(echo "$DEVICE_LIST" | head -1 | awk '{print $1}' | tr -d '\r\n')

print_warning "Using device: $DEVICE_ID"
read -p "Press Enter to continue or Ctrl+C to abort..."

# ============================================================================
# Step 3: Prepare files for deployment
# ============================================================================
print_step 3 "Preparing files..."

mkdir -p /mnt/c/tmp/hdc_transfer
cp build-standalone/rmw_dsoftbus_standalone_test /mnt/c/tmp/hdc_transfer/
cp ../build-aarch64/lib/librmw_dsoftbus.so.0.1.0 /mnt/c/tmp/hdc_transfer/

echo "  ✅ Files ready in /mnt/c/tmp/hdc_transfer/"

# ============================================================================
# Step 4: Deploy to device
# ============================================================================
print_step 4 "Deploying to device $DEVICE_ID..."

# Create directories on device
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'mkdir -p /data/test'" 2>/dev/null

# Deploy test binary
echo "  Deploying test binary..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\rmw_dsoftbus_standalone_test' '/data/test/'" 2>/dev/null

# Deploy library
echo "  Deploying library..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0' '/data/'" 2>/dev/null

# Set permissions
echo "  Setting permissions..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/test/rmw_dsoftbus_standalone_test'" 2>/dev/null

echo "  ✅ Deployment complete"

# ============================================================================
# Step 5: Run test
# ============================================================================
print_step 5 "Running test..."

echo ""
echo "════════════════════════════════════════════════════════════"
echo "  Publisher Mode Test"
echo "════════════════════════════════════════════════════════════"
echo ""

powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=pub'" 2>&1

echo ""
echo "════════════════════════════════════════════════════════════"
echo "  Test completed"
echo "════════════════════════════════════════════════════════════"
echo ""

# ============================================================================
# Additional test modes
# ============================================================================
echo ""
read -p "Run subscriber mode test? (y/N): " -n 1 -r
echo ""
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo ""
    echo "════════════════════════════════════════════════════════════"
    echo "  Subscriber Mode Test"
    echo "════════════════════════════════════════════════════════════"
    echo ""

    powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=sub'" 2>&1
fi

# ============================================================================
# Show manual commands
# ============================================================================
echo ""
echo "════════════════════════════════════════════════════════════"
echo "  Manual Test Commands"
echo "════════════════════════════════════════════════════════════"
echo ""
echo "Run publisher on Device 1:"
echo "  powershell.exe -Command \"hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=pub'\""
echo ""
echo "Run subscriber on Device 2:"
echo "  powershell.exe -Command \"hdc -t <DEVICE2_ID> shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_dsoftbus_standalone_test --mode=sub'\""
echo ""
echo "Check logs:"
echo "  powershell.exe -Command \"hdc -t $DEVICE_ID shell 'hilog | grep -i rmw'\""
echo ""
