#!/usr/bin/env python3

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
import sys

# Make sure we're using Python3
assert sys.version.startswith('3'), "This script is only meant to work with Python3"

# Make sure we get the local imports
this_dir = os.path.abspath(os.path.dirname(__file__))
sys.path.insert(0, this_dir)
import ros2_batch_job
assert ros2_batch_job.__file__.startswith(this_dir), \
    "ros2_batch_job was imported from somewhere other than the local directory of this script"
from ros2_batch_job.packaging import main

if __name__ == '__main__':
    sys.exit(main())
