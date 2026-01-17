#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 KaihongOS Port Project
# Script to generate ROS2 interface C code from .msg/.srv/.action files
#
# This script wraps rosidl_generator_c to provide a simple interface for
# generating C code from ROS2 interface definitions during the build process.

import argparse
import json
import os
import sys
from pathlib import Path

# Add ROS2 rosidl modules to Python path
SCRIPT_DIR = Path(__file__).parent.resolve()
ROS2_SRC = SCRIPT_DIR.parent / "src" / "ros2"

# Add package directories (parent of package module) with absolute paths
sys.path.insert(0, str((ROS2_SRC / "rosidl" / "rosidl_adapter").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl" / "rosidl_generator_type_description").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl" / "rosidl_generator_c").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl" / "rosidl_generator_cpp").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl" / "rosidl_typesupport_introspection_c").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl" / "rosidl_typesupport_introspection_cpp").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl_typesupport" / "rosidl_typesupport_c").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl_typesupport" / "rosidl_typesupport_cpp").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl" / "rosidl_pycommon").resolve()))
sys.path.insert(0, str((ROS2_SRC / "rosidl" / "rosidl_parser").resolve()))

try:
    from rosidl_generator_c import generate_c
    from rosidl_generator_cpp import generate_cpp
    from rosidl_typesupport_introspection_c import generate_c as generate_typesupport_introspection_c
    from rosidl_typesupport_introspection_cpp import generate_cpp as generate_typesupport_introspection_cpp
    from rosidl_typesupport_c import generate_c as generate_typesupport_c
    from rosidl_typesupport_cpp import generate_cpp as generate_typesupport_cpp
    from rosidl_adapter.msg import convert_msg_to_idl
    from rosidl_adapter.srv import convert_srv_to_idl
    from rosidl_adapter.action import convert_action_to_idl
except ImportError as e:
    print(f"Error: Failed to import rosidl modules: {e}", file=sys.stderr)
    print(f"Python path: {sys.path}", file=sys.stderr)
    sys.exit(1)


def create_generator_arguments_file(package_name, interface_files, output_dir,
                                     dependency_packages=None, interface_types=None):
    """
    Create a generator arguments file for rosidl_generator_c.

    Args:
        package_name: Name of the interface package
        interface_files: List of .msg/.srv/.action file paths
        output_dir: Output directory for generated code
        dependency_packages: List of dependent interface packages
        interface_types: Dict mapping interface file paths to their types (msg/srv/action)

    Returns:
        Path to the generated arguments file
    """
    if dependency_packages is None:
        dependency_packages = []
    if interface_types is None:
        interface_types = {}

    # Convert interface file paths to absolute paths
    interface_files = [str(Path(f).resolve()) for f in interface_files]

    # Create output directory
    output_dir = Path(output_dir).resolve()
    output_dir.mkdir(parents=True, exist_ok=True)

    # Create IDL tuples in format "basepath:relative/path"
    # basepath is the output_dir, relative_path includes type subdirectory (msg/srv/action)
    idl_tuples = []
    for iface_file in interface_files:
        iface_path = Path(iface_file)
        # Determine interface type from file extension or provided mapping
        iface_type = interface_types.get(iface_file)
        if not iface_type:
            # Infer from extension
            suffix = iface_path.suffix
            if suffix == '.msg':
                iface_type = 'msg'
            elif suffix == '.srv':
                iface_type = 'srv'
            elif suffix == '.action':
                iface_type = 'action'
            else:
                raise ValueError(f"Cannot determine type for {iface_file}")

        # IDL files are organized by type: output_dir/msg/, output_dir/srv/, etc.
        idl_relative = f"{iface_type}/{iface_path.stem}.idl"
        # IdlLocator will do: output_dir / idl_relative to find the file
        idl_tuples.append(f"{output_dir}:{idl_relative}")

    # Get template directory
    template_dir = ROS2_SRC / "rosidl" / "rosidl_generator_c" / "resource"

    # Create list of target dependencies (template files)
    target_dependencies = []
    for template_file in template_dir.glob("*.em"):
        target_dependencies.append(str(template_file))

    # Add interface files as dependencies
    target_dependencies.extend(interface_files)

    # Generator arguments structure (matching CMake rosidl_write_generator_arguments output)
    generator_args = {
        "package_name": package_name,
        "idl_tuples": idl_tuples,
        "ros_interface_files": interface_files,
        "output_dir": str(output_dir),
        "template_dir": str(template_dir),
        "target_dependencies": target_dependencies,
        "ros_interface_dependencies": dependency_packages,
        "type_description_tuples": [],  # Optional, empty for now
    }

    # Write arguments file
    args_file = output_dir / f"{package_name}__rosidl_generator_c__arguments.json"
    with open(args_file, 'w') as f:
        json.dump(generator_args, f, indent=2)

    return args_file


def create_cpp_generator_arguments_file(c_args_file):
    """
    Create a generator arguments file for rosidl_generator_cpp based on C generator args.

    Args:
        c_args_file: Path to the C generator arguments file

    Returns:
        Path to the generated C++ arguments file
    """
    # Read C generator arguments
    with open(c_args_file, 'r') as f:
        c_args = json.load(f)

    # Get C++ template directory
    cpp_template_dir = ROS2_SRC / "rosidl" / "rosidl_generator_cpp" / "resource"

    # Create list of target dependencies (C++ template files)
    target_dependencies = []
    for template_file in cpp_template_dir.glob("*.em"):
        target_dependencies.append(str(template_file))

    # Add interface files as dependencies
    target_dependencies.extend(c_args['ros_interface_files'])

    # Create C++ generator arguments by copying C args and updating template_dir
    cpp_args = c_args.copy()
    cpp_args['template_dir'] = str(cpp_template_dir)
    cpp_args['target_dependencies'] = target_dependencies

    # Write C++ arguments file
    output_dir = Path(c_args['output_dir'])
    cpp_args_file = output_dir / f"{c_args['package_name']}__rosidl_generator_cpp__arguments.json"
    with open(cpp_args_file, 'w') as f:
        json.dump(cpp_args, f, indent=2)

    return cpp_args_file


def create_typesupport_introspection_cpp_arguments_file(c_args_file):
    """
    Create a generator arguments file for rosidl_typesupport_introspection_cpp based on C generator args.

    Args:
        c_args_file: Path to the C generator arguments file

    Returns:
        Path to the generated introspection C++ arguments file
    """
    # Read C generator arguments
    with open(c_args_file, 'r') as f:
        c_args = json.load(f)

    # Get introspection C++ template directory
    introspection_template_dir = ROS2_SRC / "rosidl" / "rosidl_typesupport_introspection_cpp" / "resource"

    # Create list of target dependencies (introspection C++ template files)
    target_dependencies = []
    for template_file in introspection_template_dir.glob("*.em"):
        target_dependencies.append(str(template_file))

    # Add interface files as dependencies
    target_dependencies.extend(c_args['ros_interface_files'])

    # Create introspection C++ generator arguments by copying C args and updating template_dir
    introspection_args = c_args.copy()
    introspection_args['template_dir'] = str(introspection_template_dir)
    introspection_args['target_dependencies'] = target_dependencies

    # Write introspection arguments file
    output_dir = Path(c_args['output_dir'])
    introspection_args_file = output_dir / f"{c_args['package_name']}__rosidl_typesupport_introspection_cpp__arguments.json"
    with open(introspection_args_file, 'w') as f:
        json.dump(introspection_args, f, indent=2)

    return introspection_args_file


def create_typesupport_cpp_arguments_file(c_args_file):
    """
    Create a generator arguments file for rosidl_typesupport_cpp based on C generator args.

    Args:
        c_args_file: Path to the C generator arguments file

    Returns:
        Path to the generated typesupport C++ arguments file
    """
    # Read C generator arguments
    with open(c_args_file, 'r') as f:
        c_args = json.load(f)

    # Get typesupport C++ template directory
    typesupport_template_dir = ROS2_SRC / "rosidl_typesupport" / "rosidl_typesupport_cpp" / "resource"

    # Create list of target dependencies (typesupport C++ template files)
    target_dependencies = []
    for template_file in typesupport_template_dir.glob("*.em"):
        target_dependencies.append(str(template_file))

    # Add interface files as dependencies
    target_dependencies.extend(c_args['ros_interface_files'])

    # Create typesupport C++ generator arguments by copying C args and updating template_dir
    typesupport_args = c_args.copy()
    typesupport_args['template_dir'] = str(typesupport_template_dir)
    typesupport_args['target_dependencies'] = target_dependencies

    # Write typesupport arguments file
    output_dir = Path(c_args['output_dir'])
    typesupport_args_file = output_dir / f"{c_args['package_name']}__rosidl_typesupport_cpp__arguments.json"
    with open(typesupport_args_file, 'w') as f:
        json.dump(typesupport_args, f, indent=2)

    return typesupport_args_file


def create_typesupport_c_arguments_file(c_args_file):
    """
    Create a generator arguments file for rosidl_typesupport_c based on C generator args.

    Args:
        c_args_file: Path to the C generator arguments file

    Returns:
        Path to the generated typesupport C arguments file
    """
    # Read C generator arguments
    with open(c_args_file, 'r') as f:
        c_args = json.load(f)

    # Get typesupport C template directory
    typesupport_template_dir = ROS2_SRC / "rosidl_typesupport" / "rosidl_typesupport_c" / "resource"

    # Create list of target dependencies (typesupport C template files)
    target_dependencies = []
    for template_file in typesupport_template_dir.glob("*.em"):
        target_dependencies.append(str(template_file))

    # Add interface files as dependencies
    target_dependencies.extend(c_args['ros_interface_files'])

    # Create typesupport C generator arguments by copying C args and updating template_dir
    typesupport_args = c_args.copy()
    typesupport_args['template_dir'] = str(typesupport_template_dir)
    typesupport_args['target_dependencies'] = target_dependencies

    # Write typesupport arguments file
    output_dir = Path(c_args['output_dir'])
    typesupport_args_file = output_dir / f"{c_args['package_name']}__rosidl_typesupport_c__arguments.json"
    with open(typesupport_args_file, 'w') as f:
        json.dump(typesupport_args, f, indent=2)

    return typesupport_args_file


def preserve_service_event_message_functions(output_dir):
    """
    After rosidl_generator_c runs, copy service detail/*__type_support.c files
    to srv/*__type_support.c before rosidl_typesupport_introspection_c overwrites them.

    This preserves the create/destroy service event message functions that
    rosidl_generator_c generates but rosidl_typesupport_introspection_c doesn't.

    Args:
        output_dir: Path to the package output directory
    """
    import shutil
    from pathlib import Path

    output_path = Path(output_dir)
    srv_detail_dir = output_path / "srv" / "detail"

    if not srv_detail_dir.exists():
        return  # No services in this package

    # Find all service detail/*__type_support.c files
    for type_support_c in srv_detail_dir.glob("*__type_support.c"):
        # Extract service name (e.g., get_type_description from get_type_description__type_support.c)
        service_name = type_support_c.stem.replace("__type_support", "")

        # Create srv/ directory if it doesn't exist
        srv_dir = output_path / "srv"
        srv_dir.mkdir(parents=True, exist_ok=True)

        # Copy to srv/<service_name>__type_support.c
        dest_file = srv_dir / f"{service_name}__type_support.c"
        shutil.copy2(type_support_c, dest_file)
        print(f"  Preserved service event functions: {dest_file.name}")


def create_typesupport_introspection_c_arguments_file(c_args_file):
    """
    Create a generator arguments file for rosidl_typesupport_introspection_c based on C generator args.

    Args:
        c_args_file: Path to the C generator arguments file

    Returns:
        Path to the generated introspection C arguments file
    """
    # Read C generator arguments
    with open(c_args_file, 'r') as f:
        c_args = json.load(f)

    # Get introspection C template directory
    introspection_template_dir = ROS2_SRC / "rosidl" / "rosidl_typesupport_introspection_c" / "resource"

    # Create list of target dependencies (introspection C template files)
    target_dependencies = []
    for template_file in introspection_template_dir.glob("*.em"):
        target_dependencies.append(str(template_file))

    # Add interface files as dependencies
    target_dependencies.extend(c_args['ros_interface_files'])

    # Create introspection C generator arguments by copying C args and updating template_dir
    introspection_args = c_args.copy()
    introspection_args['template_dir'] = str(introspection_template_dir)
    introspection_args['target_dependencies'] = target_dependencies

    # Write introspection arguments file
    output_dir = Path(c_args['output_dir'])
    introspection_args_file = output_dir / f"{c_args['package_name']}__rosidl_typesupport_introspection_c__arguments.json"
    with open(introspection_args_file, 'w') as f:
        json.dump(introspection_args, f, indent=2)

    return introspection_args_file


def convert_to_idl(interface_file, package_name, package_dir, output_base_dir):
    """
    Convert .msg/.srv/.action file to .idl format.

    Args:
        interface_file: Path to .msg/.srv/.action file (can be absolute or relative)
        package_name: Package name
        package_dir: Package root directory
        output_base_dir: Base output directory for .idl files

    Returns:
        Tuple of (path to generated .idl file, interface type)
    """
    interface_file = Path(interface_file).resolve()
    package_dir = Path(package_dir).resolve()
    output_base_dir = Path(output_base_dir).resolve()

    # Convert interface_file to be relative to package_dir
    # rosidl_adapter expects: package_dir (absolute) + input_file (relative)
    try:
        relative_interface_file = interface_file.relative_to(package_dir)
    except ValueError:
        raise ValueError(f"Interface file {interface_file} is not under package directory {package_dir}")

    # Determine file type and converter
    suffix = interface_file.suffix
    if suffix == '.msg':
        converter = convert_msg_to_idl
        iface_type = 'msg'
    elif suffix == '.srv':
        converter = convert_srv_to_idl
        iface_type = 'srv'
    elif suffix == '.action':
        converter = convert_action_to_idl
        iface_type = 'action'
    else:
        raise ValueError(f"Unsupported interface file type: {suffix}")

    # Create type-specific output directory (msg/, srv/, or action/)
    output_dir = output_base_dir / iface_type
    output_dir.mkdir(parents=True, exist_ok=True)

    # Convert to IDL
    # Signature: (package_dir, package_name, input_file, output_dir)
    # input_file must be relative to package_dir
    returned_output_file = converter(package_dir, package_name, relative_interface_file, output_dir)

    # The converter returns the output file path
    if returned_output_file:
        idl_file = Path(returned_output_file)
        if not idl_file.exists():
            raise FileNotFoundError(f"Expected IDL file not found: {idl_file}")
        return str(idl_file.resolve()), iface_type

    # Fallback: determine where the IDL file should be
    # The converters write to output_dir/<Name>.idl
    idl_file = output_dir / f"{interface_file.stem}.idl"

    if not idl_file.exists():
        raise FileNotFoundError(f"Expected IDL file not found: {idl_file}")

    return str(idl_file.resolve()), iface_type


def parse_interface_files(interface_dir):
    """
    Find all .msg, .srv, and .action files in a directory.

    Args:
        interface_dir: Directory containing interface files

    Returns:
        List of interface file paths
    """
    interface_dir = Path(interface_dir)

    files = []
    for pattern in ['**/*.msg', '**/*.srv', '**/*.action']:
        files.extend(interface_dir.glob(pattern))

    return [str(f) for f in sorted(files)]


def main():
    parser = argparse.ArgumentParser(
        description='Generate ROS2 interface C code for KaihongOS',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )

    parser.add_argument(
        '--package-name',
        required=True,
        help='Name of the interface package'
    )

    parser.add_argument(
        '--interface-files',
        nargs='*',
        help='List of .msg/.srv/.action files to process'
    )

    parser.add_argument(
        '--interface-dir',
        help='Directory containing interface files (alternative to --interface-files)'
    )

    parser.add_argument(
        '--package-dir',
        help='Package root directory (defaults to parent of interface-dir)'
    )

    parser.add_argument(
        '--output-dir',
        required=True,
        help='Output directory for generated C code'
    )

    parser.add_argument(
        '--dependencies',
        nargs='*',
        default=[],
        help='Dependent interface packages'
    )

    parser.add_argument(
        '--disable-description',
        action='store_true',
        help='Disable type description codegen to reduce binary size'
    )

    parser.add_argument(
        '--verbose',
        action='store_true',
        help='Enable verbose output'
    )

    args = parser.parse_args()

    # Get interface files
    if args.interface_dir:
        if args.verbose:
            print(f"Scanning directory: {args.interface_dir}")
        interface_files = parse_interface_files(args.interface_dir)

        # Determine package directory (default to parent of interface-dir)
        if not args.package_dir:
            # interface-dir is typically package/msg or package/srv
            # so package_dir should be the parent
            args.package_dir = str(Path(args.interface_dir).parent)
    elif args.interface_files:
        interface_files = args.interface_files

        # Determine package directory from first interface file if not specified
        if not args.package_dir:
            first_file = Path(interface_files[0])
            # Assuming structure: package/msg/File.msg or package/srv/File.srv
            args.package_dir = str(first_file.parent.parent)
    else:
        print("Error: Must specify either --interface-files or --interface-dir",
              file=sys.stderr)
        return 1

    if not interface_files:
        print(f"Error: No interface files found", file=sys.stderr)
        return 1

    if args.verbose:
        print(f"Package directory: {args.package_dir}")

    if args.verbose:
        print(f"Package: {args.package_name}")
        print(f"Interface files ({len(interface_files)}):")
        for f in interface_files:
            print(f"  - {f}")
        print(f"Output directory: {args.output_dir}")
        if args.dependencies:
            print(f"Dependencies: {', '.join(args.dependencies)}")

    # Step 1: Convert .msg/.srv/.action to .idl
    output_dir_path = Path(args.output_dir).resolve()
    idl_files = []
    interface_types = {}  # Map interface file path to its type

    if args.verbose:
        print("\n▶ Step 1: Converting interfaces to IDL format...")

    for iface_file in interface_files:
        try:
            idl_file, iface_type = convert_to_idl(iface_file, args.package_name,
                                                   args.package_dir, output_dir_path)
            idl_files.append(idl_file)
            interface_types[idl_file] = iface_type
            if args.verbose:
                iface_name = Path(iface_file).name
                idl_file_path = Path(idl_file)
                try:
                    rel_path = idl_file_path.relative_to(output_dir_path)
                except ValueError:
                    rel_path = idl_file_path.name
                print(f"  ✓ {iface_name} → {rel_path}")
        except Exception as e:
            print(f"  ✗ Error converting {iface_file}: {e}", file=sys.stderr)
            import traceback
            if args.verbose:
                traceback.print_exc()
            return 1

    if not idl_files:
        print("Error: No IDL files generated", file=sys.stderr)
        return 1

    # Step 2: Create generator arguments file
    if args.verbose:
        print(f"\n▶ Step 2: Creating generator arguments...")

    args_file = create_generator_arguments_file(
        args.package_name,
        idl_files,
        args.output_dir,
        args.dependencies,
        interface_types
    )

    if args.verbose:
        print(f"Generator arguments file: {args_file}")

    # Step 3: Run rosidl_generator_c
    try:
        if args.verbose:
            print(f"\n▶ Step 3: Generating C code...")

        generate_c(str(args_file), args.disable_description)

        if args.verbose:
            print("✅ C code generation completed!")

        # Step 3.5: Preserve service event message functions before introspection overwrites them
        if args.verbose:
            print(f"\n▶ Step 3.5: Preserving service event message functions...")
        preserve_service_event_message_functions(args.output_dir)

    except Exception as e:
        print(f"\n❌ Error during C code generation: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1

    # Step 4: Run rosidl_generator_cpp
    try:
        if args.verbose:
            print(f"\n▶ Step 4: Generating C++ code...")

        # Create C++ generator arguments file
        cpp_args_file = create_cpp_generator_arguments_file(args_file)

        generate_cpp(str(cpp_args_file))

        if args.verbose:
            print("✅ C++ code generation completed!")

    except Exception as e:
        print(f"\n❌ Error during C++ code generation: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1

    # Step 5: Run rosidl_typesupport_introspection_cpp
    try:
        if args.verbose:
            print(f"\n▶ Step 5: Generating C++ type support introspection code...")

        # Create introspection C++ generator arguments file
        introspection_cpp_args_file = create_typesupport_introspection_cpp_arguments_file(args_file)

        generate_typesupport_introspection_cpp(str(introspection_cpp_args_file))

        if args.verbose:
            print("✅ C++ type support introspection code generation completed!")

    except Exception as e:
        print(f"\n❌ Error during C++ type support introspection generation: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1

    # Step 6: Run rosidl_typesupport_introspection_c
    try:
        if args.verbose:
            print(f"\n▶ Step 6: Generating C type support introspection code...")

        # Create introspection C generator arguments file
        introspection_c_args_file = create_typesupport_introspection_c_arguments_file(args_file)

        generate_typesupport_introspection_c(str(introspection_c_args_file))

        if args.verbose:
            print("✅ C type support introspection code generation completed!")

    except Exception as e:
        print(f"\n❌ Error during C type support introspection generation: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1

    # Step 7: Run rosidl_typesupport_c (C dispatch layer) - GENERATE FIRST
    try:
        if args.verbose:
            print(f"\n▶ Step 7: Generating C type support dispatch code...")

        # Create typesupport C generator arguments file
        typesupport_c_args_file = create_typesupport_c_arguments_file(args_file)

        # Generate with introspection_c as the type support
        type_supports = ['rosidl_typesupport_introspection_c']
        generate_typesupport_c(str(typesupport_c_args_file), type_supports)

        if args.verbose:
            print("✅ C type support dispatch code generation completed!")

    except Exception as e:
        print(f"\n❌ Error during C type support dispatch generation: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1

    # Step 8: Run rosidl_typesupport_cpp (dispatch layer) - GENERATE LAST (overwrites C)
    try:
        if args.verbose:
            print(f"\n▶ Step 8: Generating C++ type support dispatch code...")

        # Create typesupport C++ generator arguments file
        typesupport_cpp_args_file = create_typesupport_cpp_arguments_file(args_file)

        # Generate with introspection_cpp as the type support
        type_supports = ['rosidl_typesupport_introspection_cpp']
        generate_typesupport_cpp(str(typesupport_cpp_args_file), type_supports)

        if args.verbose:
            print("✅ C++ type support dispatch code generation completed!")

    except Exception as e:
        print(f"\n❌ Error during C++ type support dispatch generation: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1

    # Step 9: Summary
    if args.verbose:
        print(f"\n✅ All code generation completed successfully!")
        print(f"\nGenerated files in: {args.output_dir}")

        # List generated files
        output_path = Path(args.output_dir)
        if output_path.exists():
            # Exclude IDL directory from count
            c_files = [f for f in output_path.rglob("*.c") if "idl" not in f.parts]
            c_headers = [f for f in output_path.rglob("*.h") if "idl" not in f.parts]
            cpp_headers = [f for f in output_path.rglob("*.hpp") if "idl" not in f.parts]

            print(f"\n📊 Generated code statistics:")
            print(f"  • C source files: {len(c_files)}")
            print(f"  • C header files: {len(c_headers)}")
            print(f"  • C++ header files: {len(cpp_headers)}")

            if c_files or c_headers or cpp_headers:
                print(f"\n📁 File structure:")
                # Group by type (msg, srv, action)
                for iface_type in ['msg', 'srv', 'action']:
                    type_cpp_files = [f for f in cpp_headers if f.parent.name == iface_type or
                                                        (f.parent.name == 'detail' and
                                                         f.parent.parent.name == iface_type)]
                    if type_cpp_files:
                        print(f"  {iface_type}/")
                        for f in sorted(type_cpp_files)[:3]:  # Show first 3
                            rel_path = f.relative_to(output_path)
                            print(f"    - {rel_path}")
                        if len(type_cpp_files) > 3:
                            print(f"    ... and {len(type_cpp_files) - 3} more")

    return 0


if __name__ == '__main__':
    sys.exit(main())
