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

import errno
import os
import select
import sys

from subprocess import PIPE
from subprocess import Popen
from subprocess import STDOUT

_is_linux = sys.platform.lower().startswith('linux')
_is_windows = sys.platform.lower().startswith('win')


def _process_incoming_lines(incoming, left_over):
    # This function takes the new data, the left over data from last time
    # and returns a list of complete lines (separated by sep) as well as
    # any sep trailing data for the next iteration
    # This function takes and returns bytes only (str in Python2)
    combined = (left_over + incoming)
    lines = combined.splitlines(True)
    if not lines:
        return None, left_over
    # Use splitlines because it is magic
    # comparing against os.linesep is not sufficient
    if lines[-1].splitlines() != [lines[-1]]:
        data = b''.join(lines)
        left_over = b''
    else:
        data = b''.join(lines[:-1])
        left_over = lines[-1]
    return data, left_over


def _close_fds(fds_to_close):
    # This function is used to close (if not already closed) any fds used
    for s in fds_to_close:
        if s is None:
            continue
        try:
            os.close(s)
        except OSError:
            # This could raise "OSError: [Errno 9] Bad file descriptor"
            # If it has already been closed, but that's ok
            pass


def _yield_data(p, fds, left_overs, linesep, fds_to_close=None):
    # This function uses select and subprocess.Popen.poll to collect out
    # from a subprocess until it has finished, yielding it as it goes
    fds_to_close = [] if fds_to_close is None else fds_to_close

    def yield_to_stream(data, stream):
        if stream == fds[0]:
            return data, None, None
        else:
            return None, data, None

    try:
        while p.poll() is None:
            # If Windows
            if _is_windows:
                for stream in fds:
                    # This will not produce the best results, but at least
                    # it will function on Windows. A True IOCP implementation
                    # would be required to get streaming from Windows streams.
                    data = stream.readline()
                    if data:
                        yield yield_to_stream(data, stream)
                continue
            # Otherwise Unix
            try:
                rlist, wlist, xlist = select.select(fds, [], [])
            except select.error as exc:
                # Ignore EINTR
                try:
                    errnum = exc.errno
                except AttributeError:
                    errnum = exc[0]
                if errnum == errno.EINTR:
                    continue
                raise
            for stream in rlist:
                left_over = left_overs[stream]
                fileno = getattr(stream, 'fileno', lambda: stream)()
                try:
                    incoming = os.read(fileno, 1024)
                except OSError as exc:
                    # On Linux, when using a pty, in order to get select
                    # to return when the subprocess finishes, os.close
                    # must be called on the slave pty fd after forking
                    # the subprocess with popen. On some versions of
                    # the Linux kernel this causes an Errno 5 OSError,
                    # "Input/output error". Therefore, I am explicitly
                    # catching and passing on this error. In my testing
                    # this error does not occur repeatedly (it does not
                    # become a busy wait). See:
                    #   http://stackoverflow.com/a/12207447/671658
                    if _is_linux and "Input/output error" in "{0}".format(exc):
                        continue
                    raise
                if not incoming:
                    # In this case, EOF has been reached, see docs for os.read
                    if left_over:
                        yield yield_to_stream(left_over, stream)
                    continue
                data, left_over = _process_incoming_lines(incoming, left_over)
                left_overs[stream] = left_over
                yield yield_to_stream(data, stream)
        # Done
        yield None, None, p.returncode
    finally:
        # Make sure we don't leak file descriptors
        _close_fds(fds_to_close)


def _execute_process_nopty(cmd, cwd, env, shell, stderr_to_stdout=True):
    if stderr_to_stdout:
        p = Popen(cmd,
                  stdin=PIPE, stdout=PIPE, stderr=STDOUT,
                  cwd=cwd, env=env, shell=shell)
    else:
        p = Popen(cmd,
                  stdin=PIPE, stdout=PIPE, stderr=PIPE,
                  cwd=cwd, env=env, shell=shell)

    # Left over data from read which isn't a complete line yet
    left_overs = {p.stdout: b'', p.stderr: b''}

    fds = list(filter(None, [p.stdout, p.stderr]))

    return _yield_data(p, fds, left_overs, os.linesep)
