#!/bin/bash
set -e

# Setup the Space ROS environment
source "/root/src/spaceros_ws/install/setup.bash"
exec "$@"
