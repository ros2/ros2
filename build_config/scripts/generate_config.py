#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Script to generate config.h from config.h.in template

import argparse
import os
import re


def generate_config(input_file, output_file, substitutions):
    """Generate config file by substituting CMake variables."""

    # Read input template
    with open(input_file, 'r') as f:
        content = f.read()

    # Perform substitutions
    for key, value in substitutions.items():
        # Replace @KEY@ patterns
        content = content.replace(f'@{key}@', str(value))

    # Ensure output directory exists
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    # Write output file
    with open(output_file, 'w') as f:
        f.write(content)

    print(f"Generated: {output_file}")


def main():
    parser = argparse.ArgumentParser(description='Generate config header file')
    parser.add_argument('--input', required=True, help='Input template file')
    parser.add_argument('--output', required=True, help='Output config file')
    parser.add_argument('--version-major', type=int, help='Major version')
    parser.add_argument('--version-minor', type=int, help='Minor version')
    parser.add_argument('--version-patch', type=int, help='Patch version')
    parser.add_argument('--have-cxx11', type=int, default=1, help='C++11 support (0 or 1)')
    parser.add_argument('--is-big-endian', type=int, default=0, help='Big endian target (0 or 1)')
    parser.add_argument('--have-float128', type=int, default=0, help='Float128 support (0 or 1)')
    parser.add_argument('--sizeof-long-double', type=int, default=16, help='Size of long double')

    args = parser.parse_args()

    # Build substitutions dictionary
    substitutions = {}

    if args.version_major is not None:
        substitutions['PROJECT_VERSION_MAJOR'] = args.version_major
    if args.version_minor is not None:
        substitutions['PROJECT_VERSION_MINOR'] = args.version_minor
    if args.version_patch is not None:
        substitutions['PROJECT_VERSION_PATCH'] = args.version_patch

    if all(k in substitutions for k in ['PROJECT_VERSION_MAJOR', 'PROJECT_VERSION_MINOR', 'PROJECT_VERSION_PATCH']):
        substitutions['PROJECT_VERSION'] = f"{substitutions['PROJECT_VERSION_MAJOR']}.{substitutions['PROJECT_VERSION_MINOR']}.{substitutions['PROJECT_VERSION_PATCH']}"

    substitutions['HAVE_CXX11'] = args.have_cxx11
    substitutions['FASTCDR_IS_BIG_ENDIAN_TARGET'] = args.is_big_endian
    substitutions['FASTCDR_HAVE_FLOAT128'] = args.have_float128
    substitutions['FASTCDR_SIZEOF_LONG_DOUBLE'] = args.sizeof_long_double

    generate_config(args.input, args.output, substitutions)


if __name__ == '__main__':
    main()
