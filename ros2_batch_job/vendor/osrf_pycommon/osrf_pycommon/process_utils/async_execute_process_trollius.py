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
import trollius as asyncio
from trollius import From
from trollius import Return

try:
    import pty
    has_pty = True
except ImportError:
    has_pty = False

from .get_loop_impl import get_loop_impl


def get_loop():
    return get_loop_impl(asyncio)


@asyncio.coroutine
def _async_execute_process_nopty(
    protocol_class, cmd, cwd, env, shell,
    stderr_to_stdout=True
):
    loop = get_loop()
    stderr = asyncio.subprocess.PIPE
    if stderr_to_stdout is True:
        stderr = asyncio.subprocess.STDOUT
    # Start the subprocess
    if shell is True:
        transport, protocol = yield From(loop.subprocess_shell(
            protocol_class, " ".join(cmd), cwd=cwd, env=env,
            stderr=stderr))
    else:
        transport, protocol = yield From(loop.subprocess_exec(
            protocol_class, *cmd, cwd=cwd, env=env,
            stderr=stderr))
    raise Return(transport, protocol)


if has_pty:
    # If pty is availabe, use them to emulate the tty
    @asyncio.coroutine
    def _async_execute_process_pty(
        protocol_class, cmd, cwd, env, shell,
        stderr_to_stdout=True
    ):
        loop = get_loop()
        # Create the PTY's
        stdout_master, stdout_slave = pty.openpty()
        if stderr_to_stdout:
            stderr_master, stderr_slave = stdout_master, stdout_slave
        else:
            stderr_master, stderr_slave = pty.openpty()

        def protocol_factory():
            return protocol_class(None, stdout_master, stderr_master)

        # Start the subprocess
        if shell is True:
            transport, protocol = yield From(loop.subprocess_shell(
                protocol_factory, " ".join(cmd), cwd=cwd, env=env,
                stdout=stdout_slave, stderr=stderr_slave))
        else:
            transport, protocol = yield From(loop.subprocess_exec(
                protocol_factory, *cmd, cwd=cwd, env=env,
                stdout=stdout_slave, stderr=stderr_slave))

        # Close our copies of the slaves,
        # the child's copy of the slave remain open until it terminates
        os.close(stdout_slave)
        if not stderr_to_stdout:
            os.close(stderr_slave)

        # Create Protocol classes
        class PtyStdoutProtocol(asyncio.Protocol):
            def connection_made(self, transport):
                if hasattr(protocol, 'on_stdout_open'):
                    protocol.on_stdout_open()

            def data_received(self, data):
                if hasattr(protocol, 'on_stdout_received'):
                    protocol.on_stdout_received(data)

            def connection_lost(self, exc):
                if hasattr(protocol, 'on_stdout_close'):
                    protocol.on_stdout_close(exc)

        class PtyStderrProtocol(asyncio.Protocol):
            def connection_made(self, transport):
                if hasattr(protocol, 'on_stderr_open'):
                    protocol.on_stderr_open()

            def data_received(self, data):
                if hasattr(protocol, 'on_stderr_received'):
                    protocol.on_stderr_received(data)

            def connection_lost(self, exc):
                if hasattr(protocol, 'on_stderr_close'):
                    protocol.on_stderr_close(exc)

        # Add the pty's to the read loop
        # Also store the transport, protocol tuple for each call to
        # connect_read_pipe, to prevent the destruction of the protocol
        # class instance, otherwise no data is received.
        protocol.stdout_tuple = yield From(loop.connect_read_pipe(
            PtyStdoutProtocol, os.fdopen(stdout_master, 'rb', 0)))
        if not stderr_to_stdout:
            protocol.stderr_tuple = yield From(loop.connect_read_pipe(
                PtyStderrProtocol, os.fdopen(stderr_master, 'rb', 0)))
        # Return the protocol and transport
        raise Return(transport, protocol)
else:
    _async_execute_process_pty = _async_execute_process_nopty


@asyncio.coroutine
def async_execute_process(
    protocol_class, cmd=None, cwd=None, env=None, shell=False,
    emulate_tty=False, stderr_to_stdout=True
):
    if emulate_tty:
        transport, protocol = yield From(_async_execute_process_pty(
            protocol_class, cmd, cwd, env, shell,
            stderr_to_stdout))
    else:
        transport, protocol = yield From(_async_execute_process_nopty(
            protocol_class, cmd, cwd, env, shell,
            stderr_to_stdout))
    raise Return(transport, protocol)
