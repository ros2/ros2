#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 KaihongOS Port Project
# Simple script to check if a file exists (for GN conditional compilation)

import os
import sys

if len(sys.argv) != 2:
    print("false")
    sys.exit(0)

file_path = sys.argv[1]
exists = os.path.isfile(file_path)
print("true" if exists else "false")
