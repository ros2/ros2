# Reproducible Builds

This section describes how to rebuild Space ROS and run the unit tests in the Docker container.
Make sure the dev variant of the space ROS image is ready before proceeding.

Additionally, ensure the source code and workspace are updated as noted in the [usage docs](./USAGE.md).

### Building and Testing

Inside the dev container we start inside of the colcon workspace:

```bash
cd ${HOME}/spaceros_ws
```

To recompile the `dev` install using `--merge-install`:

```bash
colcon build \
  --merge-install \
  --install-base ${SPACEROS_DIR} \
  --cmake-args \
  -DBUILD_TESTING=ON \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  --no-warn-unused-cli
```

Then execute tests with:

```bash
colcon test \
  --merge-install \
  --install-base ${SPACEROS_DIR} \
  --ctest-args -LE "(ikos|xfail)" \
  --pytest-args -m "not xfail"
```

## Running Tests

The tests include running the static analysis tools clang_tidy and cppcheck (which has the MISRA 2012 add-on enabled).

Use colcon's `--packages-select` option to run a subset of packages.
For example, to run tests only for the `rcpputils` package and display the output directly to the console (as well as saving it to a log file):

```bash
colcon test \
  --packages-select rcpputils \
  --merge-install \
  --install-base ${SPACEROS_DIR} \
  --event-handlers console_direct+
```

### Viewing Test Output

The output from the tests are stored in XUnit XML files, named *\<tool-name\>*.xunit.xml.
After running the unit tests, you can scan the build directory for the various *\*.xunit.xml* files.

Here is an example test results file from `rmw` in `build/rmw/test_results/rmw/test_qos_string_conversions.gtest.xml`:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<testsuites tests="2" failures="0" disabled="0" errors="0" time="0." timestamp="2025-06-27T18:14:10.630" name="AllTests">
  <testsuite name="test_qos_policy_stringify" tests="2" failures="0" disabled="0" skipped="0" errors="0" time="0." timestamp="2025-06-27T18:14:10.630">
    <testcase name="test_policy_values" file="/home/spaceros-user/spaceros_ws/src/rmw/rmw/test/test_qos_string_conversions.cpp" line="40" status="run" result="completed" time="0." timestamp="2025-06-27T18:14:10.630" classname="rmw.test_qos_policy_stringify" />
    <testcase name="test_policy_kinds" file="/home/spaceros-user/spaceros_ws/src/rmw/rmw/test/test_qos_string_conversions.cpp" line="70" status="run" result="completed" time="0." timestamp="2025-06-27T18:14:10.630" classname="rmw.test_qos_policy_stringify" />
  </testsuite>
</testsuites>
```
