from osrf_pycommon.process_utils import asyncio
from osrf_pycommon.process_utils import async_execute_process
from osrf_pycommon.process_utils import get_loop

from osrf_pycommon.process_utils.async_execute_process_trollius import From
from osrf_pycommon.process_utils.async_execute_process_trollius import Return

from .impl_aep_protocol import create_protocol

loop = get_loop()


@asyncio.coroutine
def run(cmd, **kwargs):
    transport, protocol = yield From(async_execute_process(
        create_protocol(), cmd, **kwargs))
    retcode = yield asyncio.From(protocol.complete)
    raise Return(protocol.stdout_buffer, protocol.stderr_buffer,
                 retcode)
