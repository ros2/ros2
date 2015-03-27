# Copyright 2014 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""This module provides functions for doing process management.

The documentation for this module has a custom layout in process_utils.rst.
"""

from .async_execute_process import async_execute_process
from .async_execute_process import asyncio
from .async_execute_process import AsyncSubprocessProtocol
from .async_execute_process import get_loop

from .impl import execute_process
from .impl import execute_process_split
from .impl import which

__all__ = [
    'async_execute_process',
    'asyncio',
    'AsyncSubprocessProtocol',
    'get_loop',
    'execute_process',
    'execute_process_split',
    'which',
]
