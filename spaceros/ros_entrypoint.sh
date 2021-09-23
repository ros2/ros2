#!/bin/bash
set -e

# Setup the Space ROS environment
source "/usr/local/src/spaceros_ws/install/setup.bash"
exec "$@"
