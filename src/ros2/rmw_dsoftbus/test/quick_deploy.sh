#!/bin/bash
#
# One-click deploy and test for rmw_dsoftbus
#

set -e

DEVICE_ID=${1:-}

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN}════════════════════════════════════════════════════════════${NC}"
echo -e "${GREEN}  RMW DSoftBus Quick Deploy & Test${NC}"
echo -e "${GREEN}════════════════════════════════════════════════════════════${NC}"
echo ""

# Get device ID if not provided
if [ -z "$DEVICE_ID" ]; then
    echo "[1/6] Getting device list..."
    DEVICE_LIST=$(powershell.exe -NoProfile -Command "hdc list targets" 2>/dev/null | grep "device" | head -1)

    if [ -z "$DEVICE_LIST" ]; then
        echo -e "${RED}❌ No devices found${NC}"
        exit 1
    fi

    DEVICE_ID=$(echo "$DEVICE_LIST" | awk '{print $1}' | tr -d '\r\n')
    echo "   Using device: $DEVICE_ID"
else
    echo "[1/6] Using device: $DEVICE_ID"
fi

# Build
echo "[2/6] Building test..."
cd "$(dirname "$0")"
make -f Makefile.standalone clean simple 2>&1 | grep -E "✅|❌|Error"

if [ ! -f "build-standalone/rmw_simple_test" ]; then
    echo -e "${RED}❌ Build failed${NC}"
    exit 1
fi
echo "   ✅ Build complete"

# Prepare
echo "[3/6] Preparing files..."
make -f Makefile.standalone deploy 2>&1 | grep "✅"

# Deploy
echo "[4/6] Deploying to device..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'mkdir -p /data/test'" 2>/dev/null
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\rmw_simple_test /data/test/" 2>/dev/null
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0 /data/" 2>/dev/null
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/test/rmw_simple_test'" 2>/dev/null
echo "   ✅ Deployment complete"

# Verify
echo "[5/6] Verifying deployment..."
FILE_SIZE=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ls -lh /data/test/rmw_simple_test'" 2>/dev/null | awk '{print $5}' | tr -d '\r\n')
echo "   Test binary: $FILE_SIZE"

LIB_SIZE=$(powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ls -lh /data/librmw_dsoftbus.so.0.1.0'" 2>/dev/null | awk '{print $5}' | tr -d '\r\n')
echo "   Library: $LIB_SIZE"

# Run
echo "[6/6] Running test..."
echo ""

powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_simple_test'" 2>&1

echo ""
echo -e "${GREEN}════════════════════════════════════════════════════════════${NC}"
echo -e "${GREEN}  Deployment and test complete${NC}"
echo -e "${GREEN}════════════════════════════════════════════════════════════${NC}"
