#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Script to generate foonathan_memory config_impl.hpp

import argparse
import os


def generate_foonathan_config(input_file, output_file):
    """Generate foonathan_memory config_impl.hpp with default production settings."""

    # Production configuration (debug features disabled)
    config = {
        'FOONATHAN_MEMORY_CHECK_ALLOCATION_SIZE': '0',
        'FOONATHAN_MEMORY_DEFAULT_ALLOCATOR': 'heap_allocator',
        'FOONATHAN_MEMORY_DEBUG_ASSERT': '0',
        'FOONATHAN_MEMORY_DEBUG_FILL': '0',
        'FOONATHAN_MEMORY_DEBUG_FENCE': '0',
        'FOONATHAN_MEMORY_DEBUG_LEAK_CHECK': '0',
        'FOONATHAN_MEMORY_DEBUG_POINTER_CHECK': '0',
        'FOONATHAN_MEMORY_DEBUG_DOUBLE_DEALLOC_CHECK': '0',
        'FOONATHAN_MEMORY_EXTERN_TEMPLATE': '1',
        'FOONATHAN_MEMORY_TEMPORARY_STACK_MODE': '2',
    }

    # Read input template
    with open(input_file, 'r') as f:
        content = f.read()

    # Replace #cmakedefine01 directives with #define
    for key in ['FOONATHAN_MEMORY_CHECK_ALLOCATION_SIZE',
                'FOONATHAN_MEMORY_DEBUG_ASSERT',
                'FOONATHAN_MEMORY_DEBUG_FILL',
                'FOONATHAN_MEMORY_DEBUG_LEAK_CHECK',
                'FOONATHAN_MEMORY_DEBUG_POINTER_CHECK',
                'FOONATHAN_MEMORY_DEBUG_DOUBLE_DEALLOC_CHECK',
                'FOONATHAN_MEMORY_EXTERN_TEMPLATE']:
        old_line = f'#cmakedefine01 {key}'
        new_line = f'#define {key} {config[key]}'
        content = content.replace(old_line, new_line)

    # Replace ${VAR} patterns
    content = content.replace('${FOONATHAN_MEMORY_DEFAULT_ALLOCATOR}',
                             config['FOONATHAN_MEMORY_DEFAULT_ALLOCATOR'])
    content = content.replace('${FOONATHAN_MEMORY_DEBUG_FENCE}',
                             config['FOONATHAN_MEMORY_DEBUG_FENCE'])
    content = content.replace('${FOONATHAN_MEMORY_TEMPORARY_STACK_MODE}',
                             config['FOONATHAN_MEMORY_TEMPORARY_STACK_MODE'])

    # Ensure output directory exists
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    # Write output file
    with open(output_file, 'w') as f:
        f.write(content)

    print(f"Generated: {output_file}")


def main():
    parser = argparse.ArgumentParser(description='Generate foonathan_memory config')
    parser.add_argument('--input', required=True, help='Input template file')
    parser.add_argument('--output', required=True, help='Output config file')

    args = parser.parse_args()
    generate_foonathan_config(args.input, args.output)


if __name__ == '__main__':
    main()
