#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Script to generate FastDDS/FastRTPS config.h

import argparse
import os
import re


def generate_fastdds_config(input_file, output_file, version_major, version_minor, version_patch):
    """Generate FastDDS config.h with specified configuration."""

    version = f"{version_major}.{version_minor}.{version_patch}"

    # Configuration values for minimal FastDDS build
    config = {
        'PROJECT_VERSION_MAJOR': str(version_major),
        'PROJECT_VERSION_MINOR': str(version_minor),
        'PROJECT_VERSION_PATCH': str(version_patch),
        'PROJECT_VERSION': version,
        'HAVE_CXX20': '0',
        'HAVE_CXX17': '1',
        'HAVE_CXX14': '1',
        'HAVE_CXX1Y': '1',
        'HAVE_CXX11': '1',
        'FASTDDS_IS_BIG_ENDIAN_TARGET': '0',  # aarch64 is little-endian
        'HAVE_SECURITY': '0',  # Disable security for simplicity
        'HAVE_SQLITE3': '0',  # Disable SQLite3
        'USE_THIRDPARTY_SHARED_MUTEX': '1',
        'TLS_FOUND': '0',
        'HAVE_STRICT_REALTIME': '0',
        'ENABLE_OLD_LOG_MACROS_': '0',
        'HAVE_LOG_NO_INFO': '0',
        'HAVE_LOG_NO_WARNING': '0',
        'HAVE_LOG_NO_ERROR': '0',
    }

    # Read input template
    with open(input_file, 'r') as f:
        content = f.read()

    # Replace @VAR@ patterns
    for key, value in config.items():
        content = content.replace(f'@{key}@', value)

    # Handle #cmakedefine01 directives
    content = re.sub(r'#cmakedefine01\s+USE_THIRDPARTY_SHARED_MUTEX',
                    f'#define USE_THIRDPARTY_SHARED_MUTEX {config["USE_THIRDPARTY_SHARED_MUTEX"]}',
                    content)

    # Handle #cmakedefine directives (undefined = commented out)
    # FASTDDS_ENFORCE_LOG_INFO - not defined
    content = re.sub(r'#cmakedefine\s+FASTDDS_ENFORCE_LOG_INFO',
                    '// #undef FASTDDS_ENFORCE_LOG_INFO',
                    content)

    # FASTDDS_STATISTICS - not defined
    content = re.sub(r'#cmakedefine\s+FASTDDS_STATISTICS',
                    '// #undef FASTDDS_STATISTICS',
                    content)

    # Ensure output directory exists
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    # Write output file
    with open(output_file, 'w') as f:
        f.write(content)

    print(f"Generated: {output_file}")


def main():
    parser = argparse.ArgumentParser(description='Generate FastDDS config.h')
    parser.add_argument('--input', required=True, help='Input template file')
    parser.add_argument('--output', required=True, help='Output config file')
    parser.add_argument('--version-major', type=int, default=2, help='Major version')
    parser.add_argument('--version-minor', type=int, default=14, help='Minor version')
    parser.add_argument('--version-patch', type=int, default=5, help='Patch version')

    args = parser.parse_args()
    generate_fastdds_config(args.input, args.output,
                           args.version_major, args.version_minor, args.version_patch)


if __name__ == '__main__':
    main()
