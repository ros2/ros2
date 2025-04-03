import subprocess
import json
import os
import yaml
"""
Create `colcon.meta` file.
The file allows to inject dependencies and cmake code to downstream packages.
"""

CONFIG_PATH = "./colcon_ws_config"
CMAKE_INJECT_FILE_PATH = os.path.abspath(f"{CONFIG_PATH}/spaceros_inject.cmake")
INJECT_DEPENDENCIES_FILE_PATH = f"{CONFIG_PATH}/spaceros_inject.cmake"
OUTPUT_FILE_PATH = "spaceros-linters.meta"

def main():
    with open(f"{CONFIG_PATH}/spaceros_linters_deps.yaml", "r") as file:
        deps_file = yaml.safe_load(file)
        deps = deps_file["dependencies"]
        deps_str = " ".join(deps)

    pkgs = subprocess.run(
        [f"colcon list --packages-skip-up-to {deps_str} --names-only"],
        shell=True,
        capture_output=True,
        text=True,
    )

    output_meta = {"names": {}}

    for pkg in pkgs.stdout.split(sep="\n")[:-1]:
        output_meta["names"][pkg] = {
            "dependencies": deps,
            "ament-cmake-args": [f"-DCMAKE_PROJECT_INCLUDE={CMAKE_INJECT_FILE_PATH}"],
        }

    with open(OUTPUT_FILE_PATH, "w") as f:
        json.dump(output_meta, f, indent=4)

if __name__ == "__main__":
    main()
