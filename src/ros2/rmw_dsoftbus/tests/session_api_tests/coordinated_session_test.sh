#!/bin/bash
# Coordinated Session Test - Server and Client timing synchronized
# 解决 PEER_SESSION_NOT_CREATED 问题

DEVICE1="ec29004133314d38433031a5544f3c00"
DEVICE2="ec29004133314d38433031a522413c00"
DEVICE1_NETWORK_ID="6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3"

echo "=========================================="
echo "Coordinated Cross-Device Session Test"
echo "=========================================="
echo "Device 1 (Server): $DEVICE1"
echo "Device 2 (Client): $DEVICE2"
echo "Device 1 Network ID: $DEVICE1_NETWORK_ID"
echo "=========================================="
echo ""

# Clean up any existing processes
echo "[1] Cleaning up old processes..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'pkill -f phase3b_session_test'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell 'pkill -f phase3b_session_test'"
sleep 2

# Start server in background
echo ""
echo "[2] Starting server on Device 1 in background..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'cd /data/test && (LD_LIBRARY_PATH=. ./phase3b_session_test server > /tmp/server_coordinated.log 2>&1 &)'" &
SERVER_PID=$!

# Wait for server to initialize
echo "[3] Waiting for server to initialize (10 seconds)..."
sleep 10

# Check server log
echo ""
echo "[4] Checking server status..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'head -25 /tmp/server_coordinated.log | grep -E \"CreateSessionServer|SERVER MODE\"'"

# Run client immediately
echo ""
echo "[5] Running client on Device 2..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell 'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client $DEVICE1_NETWORK_ID'" > /tmp/client_coordinated.log 2>&1

# Display client result
echo ""
echo "=========================================="
echo "Client Test Result:"
echo "=========================================="
cat /tmp/client_coordinated.log | grep -E "OpenSession returned|OnSessionOpened|SendBytes returned|OnBytesReceived|FAIL|OK Session"

# Check server log for received messages
echo ""
echo "=========================================="
echo "Server Received Messages:"
echo "=========================================="
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'cat /tmp/server_coordinated.log | grep -E \"OnSessionOpened|OnBytesReceived\" | head -20'"

# Cleanup
echo ""
echo "[6] Cleaning up..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell 'pkill -f phase3b_session_test'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell 'pkill -f phase3b_session_test'"

echo ""
echo "=========================================="
echo "Test Complete"
echo "=========================================="
