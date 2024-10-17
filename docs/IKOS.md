# IKOS Integration

IKOS is a static analysis tool that performs interprocedural analysis on C/C++ code.

We use the `dev` image, which has the tool pre-installed and ready to run.
Ensure the source code and workspace are updated as noted in the [usage docs](./USAGE.md).

## Running an IKOS Scan

IKOS uses special compiler and linker settings in order to instrument and analyze binaries.
To run an IKOS scan on all of the Space ROS test binaries, we start from the workspace root:

```bash
cd ${HOME}/spaceros_ws
```

Next, we can rebuild the entirety of the workspace using the ikos wrappers in isolated folders.
This keeps the ikos build separate from the dev install (this may take a long time):

```bash
CC="ikos-scan-cc" CXX="ikos-scan-c++" LD="ikos-scan-cc" \
  colcon build \
  --build-base build_ikos \
  --install-base install_ikos \
  --cmake-args \
  -DBUILD_TESTING=ON \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DSECURITY=ON \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  --no-warn-unused-cli
```

The previous command generates the instrumented binaries and the associated output in a separate directory from the normal Space ROS build.
The command uses *--build-base* option to specify **build_ikos** as the build output directory instead of the default **build** directory.

To run an IKOS scan on a specific package, such as `rclcpp`, use the `--packages-up-to` or `--packages-select` options:

```bash
CC="ikos-scan-cc" CXX="ikos-scan-c++" LD="ikos-scan-cc" \
  colcon build \
  --packages-up-to rclcpp \
  --build-base build_ikos \
  --install-base install_ikos \
  --cmake-args \
  -DBUILD_TESTING=ON \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DSECURITY=ON \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  --no-warn-unused-cli
```

### Generating IKOS Results

To generate JUnit XML/SARIF files for all of the binaries resulting from the build command in the previous step, use `colcon test`, as follows:

```bash
colcon test \
  --build-base build_ikos \
  --install-base install_ikos \
  --ctest-args -L "ikos"
```

To generate a JUnit XML file for a specific package only, add the `--packages-select` option:

```bash
colcon test \
  --packages-select rclcpp \
  --build-base build_ikos \
  --install-base install_ikos \
  --ctest-args -L "ikos"
```

The `colcon test` command with the `-L "ikos"` flag runs IKOS report generation, which reads the IKOS database generated in the previous analysis step and generates a JUnit XML report file.
After running `colcon test`, the JUnit XML files will be available for view.
For example, to view the JUnit XML file for IKOS scan of the rcpputils binaries:

```bash
more build_ikos/rclcpp/test_results/rclcpp/ikos.xunit.xml
```

SARIF files are also available in the same path:

```bash
more build_ikos/rclcpp/test_results/rclcpp/ikos.sarif
```
