#!/usr/bin/env bash

VCS_REF="$(git rev-parse HEAD)"
VERSION="$(git rev-parse --abbrev-ref HEAD)"

# Exit script with failure if build fails
set -eo pipefail

echo ""
echo "##### Building Space ROS Docker Image #####"
echo ""

rm -rf src
earthly +sources
earthly +image \
        --VCS_REF="${VCS_REF}" \
        --VERSION="${VERSION}"

echo ""
echo "##### Done! #####"

