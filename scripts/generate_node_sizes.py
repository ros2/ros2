#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generate container_node_sizes_impl.hpp for foonathan_memory

import argparse
import os
import sys

def main():
    parser = argparse.ArgumentParser(description='Generate container_node_sizes_impl.hpp')
    parser.add_argument('--output', required=True, help='Output header file')
    parser.add_argument('--arch', default='aarch64', help='Target architecture')

    args = parser.parse_args()

    # Container node sizes for aarch64 (64-bit pointers)
    # These are typical sizes for std:: containers on 64-bit platforms
    # Based on libc++ and libstdc++ implementations
    content = """// Copyright (C) 2015-2023 Jonathan Müller and foonathan/memory contributors
// SPDX-License-Identifier: Zlib
//
// Auto-generated container node sizes for aarch64 (OpenHarmony)

#ifndef FOONATHAN_MEMORY_IMPL_IN_CONTAINER_NODE_SIZES_HPP
#error "do not include this file directly, use container_node_sizes.hpp"
#endif

namespace foonathan { namespace memory { namespace detail
{
    // Forward list node sizes (single-linked list)
    template <class T>
    struct list_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) + sizeof(T);  // next pointer + data
    };

    // Map/set node sizes (tree-based containers)
    // RB-tree node: color(1) + 3 pointers (parent, left, right) + data
    template <class T>
    struct map_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) * 3 + sizeof(T) + 8;  // 3 pointers + data + color/padding
    };

    template <class T>
    struct set_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) * 3 + sizeof(T) + 8;  // Same as map
    };

    template <class T>
    struct multimap_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) * 3 + sizeof(T) + 8;  // Same as map
    };

    template <class T>
    struct multiset_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) * 3 + sizeof(T) + 8;  // Same as set
    };

    // Unordered map/set node sizes (hash-based containers)
    // Hash node: next pointer + hash value + data
    template <class T>
    struct unordered_map_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) + sizeof(std::size_t) + sizeof(T);  // next + hash + data
    };

    template <class T>
    struct unordered_set_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) + sizeof(std::size_t) + sizeof(T);  // Same as unordered_map
    };

    template <class T>
    struct unordered_multimap_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) + sizeof(std::size_t) + sizeof(T);  // Same as unordered_map
    };

    template <class T>
    struct unordered_multiset_node_size_impl
    {
        static constexpr std::size_t value = sizeof(T*) + sizeof(std::size_t) + sizeof(T);  // Same as unordered_set
    };
}}}
"""

    # Create output directory if needed
    os.makedirs(os.path.dirname(args.output), exist_ok=True)

    # Write output
    with open(args.output, 'w') as f:
        f.write(content)

    print(f'Generated {args.output} for architecture {args.arch}')
    return 0

if __name__ == '__main__':
    sys.exit(main())
