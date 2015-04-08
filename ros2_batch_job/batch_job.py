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

import sys

from .util import run


class BatchJob:
    def __init__(self):
        self.run = run
        self.run_history = []
        self.python = sys.executable
        self.python_history = []

    def push_run(self, run_func):
        self.run_history.append(self.run)
        self.run = run_func

    def pop_run(self):
        current_run_func = self.run
        if not self.run_history:
            raise RuntimeError("Called pop_run with an empty run history.")
        self.run = self.run_history.pop()
        return current_run_func

    def push_python(self, python_func):
        self.python_history.append(self.python)
        self.python = python_func

    def pop_python(self):
        current_python_func = self.python
        if not self.python_history:
            raise RuntimeError("Called pop_python with an empty python history.")
        self.python = self.python_history.pop()
        return current_python_func
