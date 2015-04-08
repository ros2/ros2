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

from __future__ import print_function

import os
import sys

try:
    # If Python is < 3.3 then a SyntaxError will occur with asyncio
    # If Python is 3.3 and asyncio is not installed an ImportError occurs
    # In both cases, we must try to use trollius first
    from .async_execute_process_trollius import async_execute_process
    from .async_execute_process_trollius import get_loop
    from .async_execute_process_trollius import asyncio
except ImportError as exc:
    if 'PYTHONASYNCIODEBUG' in os.environ:
        import traceback
        traceback.print_exc()
    # If Trollius is not installed, they we can try asyncio
    # If Python is >= 3.4 asyncio is included
    # If Python is == 3.3 asyncio can be installed via pip
    try:
        from .async_execute_process_asyncio import async_execute_process
        from .async_execute_process_asyncio import get_loop
        from .async_execute_process_asyncio import asyncio
    except SyntaxError:
        raise ImportError("No module named trollius and asyncio not supported")
    except ImportError:
        raise ImportError("No module named trollius or asyncio")

__all__ = [
    'async_execute_process',
    'AsyncSubprocessProtocol',
    'get_loop',
]

async_execute_process.__doc__ = """
Coroutine to execute a subprocess and yield the output back asynchronously.

This function is meant to be used with the Python :py:mod:`asyncio` module,
which is available via pip with Python 3.3 and built-in to Python 3.4.
On Python >= 2.6 you can use the :py:mod:`trollius` module to get the same
functionality, but without using the new ``yield from`` syntax.

Here is an example of how to use this function:

.. code-block:: python

    import asyncio
    from osrf_pycommon.process_utils import async_execute_process
    from osrf_pycommon.process_utils import AsyncSubprocessProtocol
    from osrf_pycommon.process_utils import get_loop()


    @asyncio.coroutine
    def setup():
        transport, protocol = async_execute_process(
            AsyncSubprocessProtocol, ['ls', '/usr'])
        returncode = yield from protocol.complete
        return returncode

    retcode = get_loop().run_until_complete(setup())

That same example using :py:mod:`trollius` would look like this:

.. code-block:: python

    import trollius as asyncio
    from osrf_pycommon.process_utils import async_execute_process
    from osrf_pycommon.process_utils import AsyncSubprocessProtocol
    from osrf_pycommon.process_utils import get_loop()


    @asyncio.coroutine
    def setup():
        transport, protocol = async_execute_process(
            AsyncSubprocessProtocol, ['ls', '/usr'])
        returncode = yield asyncio.From(protocol.complete)
        raise asyncio.Return(returncode)

    retcode = get_loop().run_until_complete(setup())

This difference is required because in Python < 3.3 the ``yield from`` syntax
is not valid.

In both examples, the first argument is the default
:py:class:`AsyncSubprocessProtocol` protocol class, which simply prints output
from stdout to stdout and output from stderr to stderr.

If you want to capture and do something with the output or write to the stdin,
then you need to subclass from the :py:class:`AsyncSubprocessProtocol` class,
and override the ``on_stdout_received``, ``on_stderr_received``, and
``on_process_exited`` functions.

See the documentation for the :py:class:`AsyncSubprocessProtocol` class for
more details, but here is an example:

.. code-block:: python

    import trollius as asyncio
    from osrf_pycommon.process_utils import async_execute_process
    from osrf_pycommon.process_utils import AsyncSubprocessProtocol
    from osrf_pycommon.process_utils import loop

    class MyProtocol(AsyncSubprocessProtocol):
        def __init__(self, file_name, **kwargs):
            self.fh = open(file_name, 'w')
            AsyncSubprocessProtocol.__init__(self, **kwargs)

        def on_stdout_received(self, data):
            self.fh.write(data)  # Data has line endings intact

        def on_stderr_received(self, data):
            self.fh.write(data)

        def on_process_exited(self, returncode):
            self.fh.write("Exited with return code: {0}".format(returncode))
            self.fh.close()

    @asyncio.coroutine
    def log_command_to_file(self, cmd, file_name):

        def create_protocol(**kwargs):
            return MyProtocol(file_name, **kwargs)

        transport, protocol = async_execute_process(create_protocol, cmd)
        returncode = yield from protocol.complete
        return returncode

    loop.run_until_complete(log_command_to_file(['ls', '/'], '/tmp/out.txt'))

See the :py:class:`subprocess.Popen` class for more details on some of the
parameters to this function like ``cwd``, ``env``, and ``shell``.

See the :py:func:`osrf_pycommon.process_utils.execute_process` function for
more details on the ``emulate_tty`` parameter.

:param protocol_class: Protocol class which handles subprocess callbacks
:type protocol_class: :py:class:`AsyncSubprocessProtocol` or a subclass
:param list cmd: list of arguments where the executable is the first item
:param str cwd: directory in which to run the command
:param dict env: a dictionary of environment variable names to values
:param bool shell: if True, the ``cmd`` variable is interpreted by a the shell
:param bool emulate_tty: if True, pty's are passed to the subprocess for stdout
    and stderr, see :py:func:`osrf_pycommon.process_utils.execute_process`.
:param bool stderr_to_stdout: if True, stderr is directed to stdout, so they
    are not captured separately.
"""


class AsyncSubprocessProtocol(asyncio.SubprocessProtocol):
    """
    Protocol to subclass to get events from :py:func:`async_execute_process`.

    When subclassing this Protocol class, you should override these functions:

    .. code-block:: python

        def on_stdout_received(self, data):
            # ...

        def on_stderr_received(self, data):
            # ...

        def on_process_exited(self, returncode):
            # ...


    By default these functions just print the data received from
    stdout and stderr and does nothing when the process exits.

    Data received by the ``on_stdout_received`` and ``on_stderr_received``
    functions is always in bytes (``str`` in Python2 and ``bytes`` in Python3).
    Therefore, it may be necessary to call ``.decode()`` on the data before
    printing to the screen.

    Additionally, the data received will not be stripped of new lines, so take
    that into consideration when printing the result.

    You can also override these less commonly used functions:

    .. code-block:: python

        def on_stdout_open(self):
            # ...

        def on_stdout_close(self, exc):
            # ...

        def on_stderr_open(self):
            # ...

        def on_stderr_close(self, exc):
            # ...


    These functions are called when stdout/stderr are opened and closed, and
    can be useful when using pty's for example. The ``exc`` parameter of the
    ``*_close`` functions is None unless there was an exception.

    In addition to the overridable functions this class has a few useful
    public attributes.
    The ``stdin`` attribute is a reference to the PipeProto which follows the
    :py:class:`asyncio.WriteTransport` interface.
    The ``stdout`` and ``stderr`` attributes also reference their PipeProto.
    The ``complete`` attribute is a :py:class:`asyncio.Future` which is set to
    complete when the process exits and its result is the return code.

    The ``complete`` attribute can be used like this:

    .. code-block:: python

        @asyncio.coroutine
        def setup():
            transport, protocol = yield from async_execute_process(
                AsyncSubprocessProtocol, ['ls', '-G', '/usr'])
            retcode = yield from protocol.complete
            print("Exited with", retcode)

        # This will block until the protocol.complete Future is done.
        asyncio.get_event_loop().run_until_complete(setup())

    """
    def __init__(self, stdin=None, stdout=None, stderr=None):
        self.stdin = stdin
        self.stdout = stdout
        self.stderr = stderr
        self.complete = asyncio.Future()
        asyncio.SubprocessProtocol.__init__(self)

    def connection_made(self, transport):
        self.transport = transport
        if self.stdin is None:
            self.stdin = self.transport.get_pipe_transport(0)
        if self.stdout is None:
            self.stdout = self.transport.get_pipe_transport(1)
        if self.stderr is None:
            self.stderr = self.transport.get_pipe_transport(2)

    def pipe_data_received(self, fd, data):
        # This function is only called when pty's are not being used
        stdout = self.stdout
        if not isinstance(stdout, int):
            stdout = 1
        if fd == stdout:
            if hasattr(self, 'on_stdout_received'):
                self.on_stdout_received(data)
        else:
            assert fd == 2
            if hasattr(self, 'on_stderr_received'):
                self.on_stderr_received(data)

    def _on_stdout_received(self, data):
        # print(data.__repr__())
        print(data.decode(), end='')

    def _on_stderr_received(self, data):
        # print(data.__repr__(), file=sys.stderr)
        print(data.decode(), end='', file=sys.stderr)

    def process_exited(self):
        retcode = self.transport.get_returncode()
        self.complete.set_result(retcode)
        self.on_process_exited(retcode)

    def on_process_exited(self, returncode):
        # print("Exited with", returncode)
        pass

get_loop.__doc__ = """\
This function will return the proper event loop for the subprocess async calls.

On Unix this just returns :py:func:`asyncio.get_event_loop`, but on Windows it
will set and return a :py:class:`asyncio.ProactorEventLoop` instead.
"""
