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
import pty
import time

from subprocess import Popen
from subprocess import STDOUT

from .execute_process_nopty import _close_fds
from .execute_process_nopty import _yield_data


def _execute_process_pty(cmd, cwd, env, shell, stderr_to_stdout=True):
    stdout_master, stdout_slave = None, None
    stderr_master, stderr_slave = None, None
    fds_to_close = [stdout_master, stdout_slave, stderr_master, stderr_slave]
    try:
        stdout_master, stdout_slave = pty.openpty()
        if stderr_to_stdout:
            stderr_master, stderr_slave = stdout_master, stdout_slave
        else:
            stderr_master, stderr_slave = pty.openpty()

        p = None
        while p is None:
            try:
                p = Popen(
                    cmd,
                    stdin=stdout_slave, stdout=stderr_slave, stderr=STDOUT,
                    cwd=cwd, env=env, shell=shell)
            except OSError as exc:
                # This can happen if a file you are trying to execute is being
                # written to simultaneously on Linux
                # (doesn't appear to happen on OS X)
                # It seems like the best strategy is to just try again later
                # Worst case is that the file eventually gets deleted, then a
                # different OSError would occur.
                if 'Text file busy' in '{0}'.format(exc):
                    # This is a transient error, try again shortly
                    time.sleep(0.01)
                    continue
                raise
        # This causes the below select to exit when the subprocess closes.
        # On Linux, this sometimes causes Errno 5 OSError's when os.read
        # is called from within _yield_data, so on Linux _yield_data
        # catches and passes on that particular OSError.
        os.close(stdout_slave)
        if not stderr_to_stdout:
            os.close(stderr_slave)

        left_overs = {stdout_master: b'', stderr_master: b''}

        fds = [stdout_master]
        if stderr_master != stdout_master:
            fds.append(stderr_master)
    finally:
        # Make sure we don't leak file descriptors
        _close_fds(fds_to_close)

    # The linesep with pty's always seems to be "\r\n", even on OS X
    return _yield_data(p, fds, left_overs, "\r\n", fds_to_close)
