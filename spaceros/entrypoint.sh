#!/bin/bash
set -e

# Setup the Space ROS environment
source "${SPACEROS_DIR}/install/setup.bash"
exec "$@"
