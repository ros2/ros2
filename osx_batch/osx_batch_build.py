# Copyright 2015 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import shutil
import sys
import time

from util import change_directory
from util import generated_venv_vars
from util import info
from util import run
from util import warn

# Make sure we're using Python3
assert sys.version.startswith('3'), "This script is only meant to work with Python3"


# Enforce unbuffered output
class Unbuffered(object):
    def __init__(self, stream):
        self.stream = stream

    def write(self, data):
        self.stream.write(data)
        self.stream.flush()

    def __getattr__(self, attr):
        return getattr(self.stream, attr)
sys.stdout = Unbuffered(sys.stdout)
sys.stderr = Unbuffered(sys.stderr)

pip_dependencies = [
    'nose',
    'pep8',
    'pyflakes',
    'flake8',
    'mock',
    'coverage',
    'EmPy',
    'vcstool',
]


def clean_workspace(workspace):
    if os.path.exists(workspace):
        warn("@{rf}@!DELETING ALL FILES@|@{yf} in the workspace '@{cf}{0}@{yf}', "
             "you have 5 seconds to ctrl-c...", fargs=(workspace,))
        time.sleep(5)
        shutil.rmtree(workspace)
    assert not os.path.exists(workspace), "'{0}' should not exist.".format(workspace)
    info("Creating folder: @{cf}{0}", fargs=(workspace,))
    os.makedirs(workspace)


def main():
    workspace = os.path.join(os.getcwd(), 'workspace')
    info("Using workspace: @{cf}{0}", fargs=(workspace,))
    # Prepend the PATH with `/usr/local/bin` for global Homebrew binaries.
    os.environ['PATH'] = "/usr/local/bin" + os.pathsep + os.environ.get('PATH', '')
    # Make sure the workspace is clear.
    clean_workspace(workspace)
    # Check the env.
    run(['export'], shell=True)
    # Show what Homebrew has installed
    run(['brew', 'list'])
    # Check for a tty in the subprocesses.
    run([sys.executable, '-c', 'import sys; print(sys.stdout.isatty())'])
    # Make sure virtual env is installed
    run([sys.executable, '-m', 'pip', 'install', '-U', 'virtualenv'])
    # Change to the workspace directory.
    with change_directory(workspace):
        # Create a virtualenv
        run([sys.executable, '-m', 'virtualenv', '-p', sys.executable, 'venv'])
        venv, venv_python, venv_pip = generated_venv_vars()

        # Check for a tty in the subprocesses.
        venv([venv_python, '-c', '"import sys; print(sys.stdout.isatty())"'])
        venv(['export'])
        # Display Python info and version
        venv(['which', 'python'])
        venv([venv_python, '--version'])
        # Update pip and setuptools
        venv([venv_pip, 'install', '-U', 'pip', 'setuptools'])
        # Print setuptools version
        venv([venv_python, '-c', '"import setuptools; print(setuptools.__version__)"'])
        # Print the pip version
        venv([venv_pip, '--version'])
        # Show what pip has installed
        venv([venv_pip, 'freeze'])
        # Install pip dependencies
        venv([venv_pip, 'install', '-U'] + pip_dependencies)
        # Show what pip has installed (again)
        venv([venv_pip, 'freeze'])
        # Fetch the repository listing
        venv(['wget', 'https://raw.githubusercontent.com/ros2/examples/master/ros2.repos'])
        venv(['cat', 'ros2.repos'])
        # Use the repository listing and vcstool to fetch repositories
        if not os.path.exists('src'):
            os.makedirs('src')
        venv(['vcs', 'import', 'src', '--input', 'ros2.repos'])
        # TODO(wjwwood): check the branch being tested, and try to match all repos to that branch.
        # Build repositories.
        unbuf_py = [venv_python, '-u']
        venv(unbuf_py + ['./src/ament/ament_tools/scripts/ament.py', 'build', '--build-tests'])
        # Run tests
        ret_test = venv(unbuf_py + ['./src/ament/ament_tools/scripts/ament.py', 'test', 'src'],
                        exit_on_error=False)
        info("ament.py test returned: '{0}'".format(ret_test))
        # Run test results
        ret_testr = venv(unbuf_py + ['./src/ament/ament_tools/scripts/ament.py', 'test_results'],
                         exit_on_error=False)
        info("ament.py test_results returned: '{0}'".format(ret_testr))
        # Uncomment this line to failing tests a failrue of this command.
        # return 0 if ret_test == 0 and ret_testr == 0 else 1

if __name__ == '__main__':
    try:
        sys.exit(main())
    except (KeyboardInterrupt, EOFError):
        sys.exit("User aborted.")
