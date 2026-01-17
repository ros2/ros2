#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# FastDDS configuration header generator script

import argparse
import os
import re
import sys

def main():
    parser = argparse.ArgumentParser(description='Generate FastDDS config.h from template')
    parser.add_argument('--input', required=True, help='Input template file')
    parser.add_argument('--output', required=True, help='Output config file')

    args = parser.parse_args()

    # Read template
    with open(args.input, 'r') as f:
        content = f.read()

    # Replace CMake variables with values for OpenHarmony port
    replacements = {
        '@PROJECT_VERSION_MAJOR@': '2',
        '@PROJECT_VERSION_MINOR@': '14',
        '@PROJECT_VERSION_PATCH@': '0',
        '@PROJECT_VERSION@': '2.14.0',
        '@HAVE_CXX20@': '0',
        '@HAVE_CXX17@': '1',
        '@HAVE_CXX14@': '1',
        '@HAVE_CXX1Y@': '1',
        '@HAVE_CXX11@': '1',
        '@FASTDDS_IS_BIG_ENDIAN_TARGET@': '0',  # aarch64 is little-endian
        '@HAVE_SECURITY@': '0',  # Disable security for initial port
        '@HAVE_SQLITE3@': '0',   # Disable SQLite3 for initial port
        '@TLS_FOUND@': '0',      # Disable TLS for initial port
        '@HAVE_STRICT_REALTIME@': '0',
        '@ENABLE_OLD_LOG_MACROS_@': '0',
        '@HAVE_LOG_NO_INFO@': '0',
        '@HAVE_LOG_NO_WARNING@': '0',
        '@HAVE_LOG_NO_ERROR@': '0',
    }

    for key, value in replacements.items():
        content = content.replace(key, value)

    # Handle #cmakedefine directives
    # #cmakedefine01 USE_THIRDPARTY_SHARED_MUTEX -> #define USE_THIRDPARTY_SHARED_MUTEX 1
    content = re.sub(r'#cmakedefine01\s+USE_THIRDPARTY_SHARED_MUTEX',
                     '#define USE_THIRDPARTY_SHARED_MUTEX 1', content)

    # #cmakedefine FASTDDS_ENFORCE_LOG_INFO -> comment out (not defined)
    content = re.sub(r'#cmakedefine\s+FASTDDS_ENFORCE_LOG_INFO',
                     '/* #undef FASTDDS_ENFORCE_LOG_INFO */', content)

    # #cmakedefine FASTDDS_STATISTICS -> comment out (not defined)
    content = re.sub(r'#cmakedefine\s+FASTDDS_STATISTICS',
                     '/* #undef FASTDDS_STATISTICS */', content)

    # Create output directory if needed
    os.makedirs(os.path.dirname(args.output), exist_ok=True)

    # Write output
    with open(args.output, 'w') as f:
        f.write(content)

    print(f'Generated {args.output}')
    return 0

if __name__ == '__main__':
    sys.exit(main())
