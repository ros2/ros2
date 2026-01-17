#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Script to generate CycloneDDS configuration headers

import argparse
import os


def generate_config_h(output_file):
    """Generate config.h for CycloneDDS"""
    content = """/* Generated configuration header for CycloneDDS on OpenHarmony */
#ifndef DDS_CONFIG_H
#define DDS_CONFIG_H

/* Platform detection */
#define __linux__ 1
#define __OHOS__ 1

/* DDS Feature flags */
#define DDS_HAS_LIFESPAN 1
#define DDS_HAS_DEADLINE_MISSED 1
#define DDS_HAS_NETWORK_PARTITIONS 1
#define DDS_HAS_SSM 1
#define DDS_HAS_IPV6 1
#define DDS_HAS_TYPE_DISCOVERY 1
#define DDS_HAS_TOPIC_DISCOVERY 1

/* Disabled features - not defined (not just 0) to work with #ifdef */
/* #undef DDS_HAS_SECURITY */
/* #undef DDS_HAS_SHM */
/* #undef DDS_HAS_SSL */

/* Threading */
#define DDS_USE_PTHREADS 1

/* DDSRT Platform features */
#define DDSRT_HAVE_GETHOSTNAME 1
#define DDSRT_HAVE_RUSAGE 1
#define DDSRT_HAVE_FILESYSTEM 1
#define DDSRT_HAVE_NETSTAT 1
#define DDSRT_HAVE_DNS 1
#define DDSRT_HAVE_IPV6 1
#define DDSRT_HAVE_ATOMIC 1
#define DDSRT_HAVE_ATOMIC_LIFO 1
#define DDSRT_HAVE_DYNLIB 1

/* Thread features */
#define DDSRT_HAVE_THREAD_SETNAME 1
#define DDSRT_HAVE_THREAD_LIST 1

#endif /* DDS_CONFIG_H */
"""
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    with open(output_file, 'w') as f:
        f.write(content)
    print(f"Generated: {output_file}")


def generate_version_h(output_file):
    """Generate version.h for CycloneDDS"""
    content = """/* Generated version header for CycloneDDS */
#ifndef DDS_VERSION_H
#define DDS_VERSION_H

#define DDS_VERSION_MAJOR 0
#define DDS_VERSION_MINOR 10
#define DDS_VERSION_PATCH 5
#define DDS_VERSION "0.10.5"

/* Build information */
#define DDS_HOST_NAME "Linux"
#define DDS_TARGET_NAME "OHOS"

#endif /* DDS_VERSION_H */
"""
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    with open(output_file, 'w') as f:
        f.write(content)
    print(f"Generated: {output_file}")


def generate_features_h(output_file):
    """Generate features.h for CycloneDDS"""
    content = """/* Generated features header for CycloneDDS */
#ifndef DDS_FEATURES_H
#define DDS_FEATURES_H

/* Enabled features */
#define DDS_HAS_LIFESPAN 1
#define DDS_HAS_DEADLINE_MISSED 1
#define DDS_HAS_NETWORK_PARTITIONS 1
#define DDS_HAS_SSM 1
#define DDS_HAS_TYPE_DISCOVERY 1
#define DDS_HAS_TOPIC_DISCOVERY 1

/* Disabled features - not defined (not just 0) to work with #ifdef */
/* #undef DDS_HAS_SECURITY */
/* #undef DDS_HAS_SHM */

#endif /* DDS_FEATURES_H */
"""
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    with open(output_file, 'w') as f:
        f.write(content)
    print(f"Generated: {output_file}")


def generate_export_h(output_file):
    """Generate export.h for CycloneDDS"""
    content = """/* Generated export header for CycloneDDS */
#ifndef DDS_EXPORT_H
#define DDS_EXPORT_H

/* Export macros for shared library visibility */
#if defined(__GNUC__) || defined(__clang__)
#  define DDS_EXPORT __attribute__((visibility("default")))
#  define DDS_INLINE_EXPORT inline __attribute__((visibility("default")))
#  define DDS_IMPORT
#  define DDS_DEPRECATED_EXPORT __attribute__((deprecated)) __attribute__((visibility("default")))
#else
#  define DDS_EXPORT
#  define DDS_INLINE_EXPORT inline
#  define DDS_IMPORT
#  define DDS_DEPRECATED_EXPORT
#endif

/* Deprecated macro */
#define DDS_DEPRECATED(msg) __attribute__((deprecated(msg)))

#endif /* DDS_EXPORT_H */
"""
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    with open(output_file, 'w') as f:
        f.write(content)
    print(f"Generated: {output_file}")


def main():
    parser = argparse.ArgumentParser(description='Generate CycloneDDS configuration headers')
    parser.add_argument('--config', required=True, help='Output path for config.h')
    parser.add_argument('--version', required=True, help='Output path for version.h')
    parser.add_argument('--features', required=True, help='Output path for features.h')
    parser.add_argument('--export', required=True, help='Output path for export.h')

    args = parser.parse_args()

    generate_config_h(args.config)
    generate_version_h(args.version)
    generate_features_h(args.features)
    generate_export_h(args.export)


if __name__ == '__main__':
    main()
