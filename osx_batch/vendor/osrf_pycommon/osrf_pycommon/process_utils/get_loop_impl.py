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

import os
import threading

_thread_local = threading.local()


def get_loop_impl(asyncio):
    global _thread_local
    if getattr(_thread_local, 'loop_has_been_setup', False):
        return asyncio.get_event_loop()
    # Setup this thread's loop and return it
    if os.name == 'nt':
        loop = asyncio.ProactorEventLoop()
        asyncio.set_event_loop(loop)
    else:
        try:
            loop = asyncio.get_event_loop()
        except AssertionError:
            loop = asyncio.new_event_loop()
            asyncio.set_event_loop(loop)
    _thread_local.loop_has_been_setup = True
    return loop
