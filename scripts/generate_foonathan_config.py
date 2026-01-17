#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# foonathan_memory configuration header generator script

import argparse
import os
import re
import sys

def main():
    parser = argparse.ArgumentParser(description='Generate foonathan_memory config_impl.hpp from template')
    parser.add_argument('--input', required=True, help='Input template file (config.hpp.in)')
    parser.add_argument('--output', required=True, help='Output config file (config_impl.hpp)')

    args = parser.parse_args()

    # Read template
    with open(args.input, 'r') as f:
        content = f.read()

    # Replace CMake variables with values for OpenHarmony port
    # Use conservative defaults for release build
    replacements = {
        '${FOONATHAN_MEMORY_DEFAULT_ALLOCATOR}': 'heap_allocator',
        '${FOONATHAN_MEMORY_DEBUG_FENCE}': '0',  # Disable debug fence in release
        '${FOONATHAN_MEMORY_TEMPORARY_STACK_MODE}': '0',  # Default stack mode
    }

    for key, value in replacements.items():
        content = content.replace(key, value)

    # Handle #cmakedefine01 directives (set to 0 for release build)
    # These control debug features - disable for performance
    cmakedefine01_vars = [
        'FOONATHAN_MEMORY_CHECK_ALLOCATION_SIZE',    # Disable size checking
        'FOONATHAN_MEMORY_DEBUG_ASSERT',             # Disable debug assertions
        'FOONATHAN_MEMORY_DEBUG_FILL',               # Disable fill patterns
        'FOONATHAN_MEMORY_DEBUG_LEAK_CHECK',         # Disable leak checking
        'FOONATHAN_MEMORY_DEBUG_POINTER_CHECK',      # Disable pointer validation
        'FOONATHAN_MEMORY_DEBUG_DOUBLE_DEALLOC_CHECK',  # Disable double-free check
        'FOONATHAN_MEMORY_EXTERN_TEMPLATE',          # Disable extern templates
    ]

    for var in cmakedefine01_vars:
        # Replace #cmakedefine01 VAR with #define VAR 0
        content = re.sub(
            rf'#cmakedefine01\s+{var}',
            f'#define {var} 0',
            content
        )

    # Create output directory if needed
    os.makedirs(os.path.dirname(args.output), exist_ok=True)

    # Write output
    with open(args.output, 'w') as f:
        f.write(content)

    print(f'Generated {args.output}')
    return 0

if __name__ == '__main__':
    sys.exit(main())
