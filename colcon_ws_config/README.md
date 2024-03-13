# SpaceROS workspace config

This directory contains collection of scripts and configuration file used in SpaceROS colcon workspace.
The content of this directory allows to inject cmake code into upstream packages without any source code modification.
SpaceROS uses files from this directory to include set of common linters and static code analysers into each package and to provide common colcon configurations.

## Using the config

For now the only use case for the config is to patch dependencies of upstream SpaceROS packages, so that every package uses common set of linting tools and static code analysers when `colcon test` is invoked.

The config is applied during SpaceROS' CI pipeline to include common set of linters.

You can also use it inside the SpaceROS docker image, to include common set of linters for all packages (SpaceROS + thirdparty) in your workspace. This can be achieved by running a `prepare_workspace.py` python script in root of the workspace:

```bash
python3 colcon_ws_config/prepare_workspace.py
```
The script above should produce a `spaceros-linters.meta` file, which can be added to the build command:

```bash
colcon build --metas spaceros-linters.meta (...rest of the command)
```

Now, `colcon test` should trigger common set of linters for each package.

Note that whenever any new package is added, you should re-run `prepare_workspace.py` script, to update the meta file.

## Package description

**Prerequisities**
- [Understand .meta files in colcon](https://colcon.readthedocs.io/en/released/user/configuration.html#meta-files)


The `prepare_workspace.py` creates a `spaceros-linters.meta` file that injects `spaceros_inject.cmake` script into packages in colcon workspace. The cmake script is injected using [CMAKE_PROJECT_INCLUDE](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_INCLUDE.html) CMAKE variable.
Additionally, `prepare_workspace.py` adds dependencies to `spaceros-linters.meta` file, so that packages used in injected cmake script are present to the package during build.

The `spaceros-linters.meta` file consist of the following entries for each SpaceROS package:
```json
"PACKAGE NAME": {
    "dependencies": [
      "ament_lint_auto",
      "ament_cmake"
      "ament_cmake_cobra",
      ...
      ], // from spaceros_linters_deps.yaml
    "ament-cmake-args": [
      "-DCMAKE_PROJECT_INCLUDE=ABSOLUTE_PATH_TO_WS/colcon_ws_config/spaceros_inject.cmake"
      ]
}
```

Packages declared in `spaceros_linters_deps.yaml` and their upstream dependencies are excluded from `spaceros-linters.meta` file, to avoid circular dependencies.


## Advanced guides

### Adding custom linters / arbitrary cmake code

You can inject arbitrary code into the packages, by modifying `spaceros_inject.cmake` file. Whenever you add any new package that the script depends on (i.e. you call `find_package()`), make sure you add the dependency into `spaceros_linters_deps.yaml` file.


### Understanding content of CMake script

By default [spaceros_inject.cmake](./spaceros_inject.cmake) script, contains set of `find_package` calls. We first call `find_package(ament_lint_auto REQUIRED)`. This creates [ament extension](https://docs.ros.org/en/foxy/How-To-Guides/Ament-CMake-Documentation.html#adding-to-extension-points) called `ament_lint_auto`, that will get executed as part of `ament_package()` macro in a ROS 2 package.

After that, `find_package()` for every ament linter is called (e.g. `find_package(ament_cmake_copyright)`).`. This call adds a script to `ament_lint_auto` extension point, that will be executed as part of this extension.

In order to make sure that injected code does not interfere with tests already added to upstream packages, `AMENT_LINT_AUTO_SKIP_PREEXISTING_TESTS` flag is set in the file.

## Limitations

### Package coverage

Only packages using `ament_cmake` build system are modified to include all spaceros analysers. To list packages that are not impacted, run:
```bash
colcon list | grep -v "ros.ament_cmake"
```
As of the time of writing this README (March 2024), there are 143 `ament_cmake` packages, 10 `cmake` packages and 58 `ament_python` packages.

### Tests overwriting

If an upstream package directly invokes a test using a macro in its `CMakeLists.txt` file (e.g., `ament_xmlint()`), that takes precedence over `ament_lint_auto`. Consequently, the settings for that test defined in the `CMakeLists.txt` file of upstream package will be effective.
