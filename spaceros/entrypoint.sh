#!/bin/bash
set -e

# Setup the Space ROS environment
source "/root/src/spaceros/install/setup.bash"
exec "$@"
