#!/usr/bin/env bash

ORG=openrobotics
IMAGE=spaceros
TAG=latest

VCS_REF=""
VERSION=preview

echo ""
echo "##### Building Space ROS Docker Image #####"
echo ""

docker build -t $ORG/$IMAGE:$TAG \
    --build-arg VCS_REF="$VCS_REF" \
    --build-arg VERSION="$VERSION" .

echo ""
echo "##### Done! #####"

