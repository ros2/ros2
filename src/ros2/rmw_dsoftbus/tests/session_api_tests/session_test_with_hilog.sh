#!/bin/bash
# Complete Session Test with hilog Capture
# 完整的跨设备 Session 测试，抓取双端 hilog

DEVICE1="ec29004133314d38433031a5544f3c00"
DEVICE2="ec29004133314d38433031a522413c00"
DEVICE1_NETWORK_ID="6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3"

LOG_DIR="/home/jiusi/M-DDS/tests/logs"
mkdir -p "$LOG_DIR"

echo "=========================================="
echo "Session Test with Complete hilog Capture"
echo "=========================================="
echo "Device 1 (Server): $DEVICE1"
echo "Device 2 (Client): $DEVICE2"
echo "Log Directory: $LOG_DIR"
echo "=========================================="
echo ""

# Clean up
echo "[1] Cleaning up processes and logs..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'pkill -f phase3b_session_test'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell 'pkill -f phase3b_session_test'"
sleep 2

# Clear hilog on both devices
echo "[2] Clearing hilog on both devices..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'hilog -r'" > /dev/null 2>&1
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell 'hilog -r'" > /dev/null 2>&1
sleep 1

# Start hilog capture in background
echo "[3] Starting hilog capture on both devices..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'hilog -x > /data/test/device1_hilog.txt 2>&1 &'" &
HILOG1_PID=$!
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell 'hilog -x > /data/test/device2_hilog.txt 2>&1 &'" &
HILOG2_PID=$!
sleep 2
echo "hilog capture started"

# Start server
echo ""
echo "[4] Starting Server on Device 1..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'cd /data/test && (LD_LIBRARY_PATH=. ./phase3b_session_test server > /data/test/server_test.log 2>&1 &)'" &
sleep 8

# Check server status
echo ""
echo "[5] Checking Server startup..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'head -25 /data/test/server_test.log'"

# Run client immediately
echo ""
echo "[6] Running Client on Device 2 (immediately to avoid server timeout)..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell 'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client $DEVICE1_NETWORK_ID'" > "$LOG_DIR/client_output.txt" 2>&1

# Display client result
echo ""
echo "=========================================="
echo "Client Test Output:"
echo "=========================================="
cat "$LOG_DIR/client_output.txt" | grep -E "OpenSession|OnSessionOpened|SendBytes|OnBytesReceived|FAIL|OK"

# Stop hilog capture
echo ""
echo "[7] Stopping hilog capture..."
sleep 2
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'pkill hilog'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell 'pkill hilog'"
sleep 1

# Retrieve hilog files
echo ""
echo "[8] Retrieving hilog files to local..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 file recv /data/test/device1_hilog.txt '$LOG_DIR/device1_hilog_raw.txt'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 file recv /data/test/device2_hilog.txt '$LOG_DIR/device2_hilog_raw.txt'"

# Filter relevant hilog entries
echo ""
echo "[9] Filtering relevant hilog entries..."

echo "Device 1 (Server) hilog:" > "$LOG_DIR/device1_hilog_filtered.txt"
grep -E "CreateSessionServer|OpenSession|Session|OnBytes|TransSdk|TransCtrl|426115004|426442743|com.huawei.ros2" "$LOG_DIR/device1_hilog_raw.txt" >> "$LOG_DIR/device1_hilog_filtered.txt" 2>/dev/null

echo "Device 2 (Client) hilog:" > "$LOG_DIR/device2_hilog_filtered.txt"
grep -E "CreateSessionServer|OpenSession|Session|OnBytes|TransSdk|TransCtrl|426115004|426442743|com.huawei.ros2" "$LOG_DIR/device2_hilog_raw.txt" >> "$LOG_DIR/device2_hilog_filtered.txt" 2>/dev/null

# Show filtered results
echo ""
echo "=========================================="
echo "Device 1 Server hilog (filtered):"
echo "=========================================="
tail -50 "$LOG_DIR/device1_hilog_filtered.txt"

echo ""
echo "=========================================="
echo "Device 2 Client hilog (filtered):"
echo "=========================================="
tail -50 "$LOG_DIR/device2_hilog_filtered.txt"

# Retrieve server log
echo ""
echo "[10] Retrieving server application log..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 file recv /data/test/server_test.log '$LOG_DIR/server_app.log'"

# Summary
echo ""
echo "=========================================="
echo "Log Files Saved:"
echo "=========================================="
ls -lh "$LOG_DIR"/*.txt "$LOG_DIR"/*.log 2>/dev/null

echo ""
echo "=========================================="
echo "Test Complete"
echo "=========================================="
echo "Full logs saved to: $LOG_DIR"
