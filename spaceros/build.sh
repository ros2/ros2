#!/usr/bin/env bash

VCS_REF="$(git rev-parse HEAD)"
VERSION=preview

echo ""
echo "##### Building Space ROS Docker Image #####"
echo ""

rm -rf src
earthly +sources
earthly +image \
    --VCS_REF="$VCS_REF"

echo ""
echo "##### Done! #####"

