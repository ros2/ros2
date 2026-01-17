#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Script to generate container_node_sizes_impl.hpp for foonathan_memory

import argparse
import os


# Container node sizes for aarch64 Linux (64-bit)
# These are typical sizes - actual sizes may vary slightly based on compiler/stdlib
NODE_SIZES_AARCH64 = {
    'forward_list': 8,    # Single pointer
    'list': 16,           # Two pointers (prev, next)
    'set': 32,            # RB-tree node (color, parent, left, right, value)
    'map': 32,            # RB-tree node
    'multiset': 32,       # RB-tree node
    'multimap': 32,       # RB-tree node
    'unordered_set': 16,  # Hash node (next ptr + value)
    'unordered_map': 16,  # Hash node (next ptr + pair)
    'unordered_multiset': 16,
    'unordered_multimap': 16,
}


def generate_node_sizes(output_file, arch='aarch64'):
    """Generate container_node_sizes_impl.hpp with architecture-specific node sizes."""

    if arch != 'aarch64':
        raise ValueError(f"Unsupported architecture: {arch}")

    sizes = NODE_SIZES_AARCH64

    content = f"""// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// Auto-generated container node sizes for {arch}

#ifndef FOONATHAN_MEMORY_IMPL_IN_CONTAINER_NODE_SIZES_HPP
#error "do not include this file directly, use container_node_sizes.hpp"
#endif

#include <cstddef>

namespace foonathan {{ namespace memory {{ namespace detail
{{
    // Node sizes for standard containers on {arch}
    template <class T>
    struct node_size_impl;

    template <class T>
    struct node_size_impl<std::forward_list<T>>
    {{
        static constexpr std::size_t value = {sizes['forward_list']};
    }};

    template <class T>
    struct node_size_impl<std::list<T>>
    {{
        static constexpr std::size_t value = {sizes['list']};
    }};

    template <class T>
    struct node_size_impl<std::set<T>>
    {{
        static constexpr std::size_t value = {sizes['set']};
    }};

    template <class K, class V>
    struct node_size_impl<std::map<K, V>>
    {{
        static constexpr std::size_t value = {sizes['map']};
    }};

    template <class T>
    struct node_size_impl<std::multiset<T>>
    {{
        static constexpr std::size_t value = {sizes['multiset']};
    }};

    template <class K, class V>
    struct node_size_impl<std::multimap<K, V>>
    {{
        static constexpr std::size_t value = {sizes['multimap']};
    }};

    template <class T>
    struct node_size_impl<std::unordered_set<T>>
    {{
        static constexpr std::size_t value = {sizes['unordered_set']};
    }};

    template <class K, class V>
    struct node_size_impl<std::unordered_map<K, V>>
    {{
        static constexpr std::size_t value = {sizes['unordered_map']};
    }};

    template <class T>
    struct node_size_impl<std::unordered_multiset<T>>
    {{
        static constexpr std::size_t value = {sizes['unordered_multiset']};
    }};

    template <class K, class V>
    struct node_size_impl<std::unordered_multimap<K, V>>
    {{
        static constexpr std::size_t value = {sizes['unordered_multimap']};
    }};
}}}} // namespace foonathan::memory::detail
"""

    # Ensure output directory exists
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    # Write output file
    with open(output_file, 'w') as f:
        f.write(content)

    print(f"Generated: {output_file}")


def main():
    parser = argparse.ArgumentParser(description='Generate container node sizes')
    parser.add_argument('--output', required=True, help='Output file path')
    parser.add_argument('--arch', default='aarch64', help='Target architecture')

    args = parser.parse_args()
    generate_node_sizes(args.output, args.arch)


if __name__ == '__main__':
    main()
