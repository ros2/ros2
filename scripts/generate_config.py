#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Configuration header generator script

import argparse
import os
import sys

def main():
    parser = argparse.ArgumentParser(description='Generate config.h from template')
    parser.add_argument('--input', required=True, help='Input template file')
    parser.add_argument('--output', required=True, help='Output config file')
    parser.add_argument('--version-major', default='1')
    parser.add_argument('--version-minor', default='0')
    parser.add_argument('--version-patch', default='0')
    parser.add_argument('--have-cxx11', default='1')
    parser.add_argument('--is-big-endian', default='0')
    parser.add_argument('--have-float128', default='0')
    parser.add_argument('--sizeof-long-double', default='16')

    args = parser.parse_args()

    # Read template
    with open(args.input, 'r') as f:
        content = f.read()

    # Version string
    version_str = f'{args.version_major}.{args.version_minor}.{args.version_patch}'

    # Replace CMake variables
    replacements = {
        '@PROJECT_VERSION_MAJOR@': args.version_major,
        '@PROJECT_VERSION_MINOR@': args.version_minor,
        '@PROJECT_VERSION_PATCH@': args.version_patch,
        '@PROJECT_VERSION@': version_str,
        '@HAVE_CXX11@': args.have_cxx11,
        '@FASTCDR_IS_BIG_ENDIAN_TARGET@': args.is_big_endian,
        '@FASTCDR_HAVE_FLOAT128@': args.have_float128,
        '@FASTCDR_SIZEOF_LONG_DOUBLE@': args.sizeof_long_double,
    }

    for key, value in replacements.items():
        content = content.replace(key, value)

    # Create output directory if needed
    os.makedirs(os.path.dirname(args.output), exist_ok=True)

    # Write output
    with open(args.output, 'w') as f:
        f.write(content)

    print(f'Generated {args.output}')
    return 0

if __name__ == '__main__':
    sys.exit(main())
