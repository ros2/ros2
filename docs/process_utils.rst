The ``process_utils`` Module
=============================

This module provides functions for doing process management.

These are the main sections of this module:

- `Asynchronous Process Utilities`_
- `Synchronous Process Utilities`_
- `Utility Functions`_

Asynchronous Process Utilities
------------------------------

There is a function and class which can be used together with your custom `Tollius <http://trollius.readthedocs.org/>`_ or `asyncio <https://docs.python.org/3/library/asyncio.html>`_ run loop.

The :py:func:`osrf_pycommon.process_utils.async_execute_process` function is a `coroutine <https://docs.python.org/3/library/asyncio-task.html#coroutines>`_ which allows you to run a process and get the output back bit by bit in real-time, either with stdout and stderr separated or combined.
This function also allows you to emulate the terminal using a pty simply by toggling a flag in the parameters.

Along side this coroutine is a `Protocol <https://docs.python.org/3/library/asyncio-protocol.html#protocols>`_ class, :py:class:`osrf_pycommon.process_utils.AsyncSubprocessProtocol`, from which you can inherit in order to customize how the yielded output is handled.

Because this coroutine is built on the ``trollius``/``asyncio`` framework's subprocess functions, it is portable and should behave the same on all major OS's. (including on Windows where an IOCP implementation is used)

.. autofunction:: osrf_pycommon.process_utils.async_execute_process

.. autoclass:: osrf_pycommon.process_utils.AsyncSubprocessProtocol
    :members:

In addtion to these functions, there is a utility function for getting the correct ``asyncio`` event loop:

.. autofunction:: osrf_pycommon.process_utils.get_loop

Synchronous Process Utilities
-----------------------------

For synchronous execution and output capture of subprocess, there are two functions:

- :py:func:`osrf_pycommon.process_utils.execute_process`
- :py:func:`osrf_pycommon.process_utils.execute_process_split`

These functions are not yet using the ``trollius``/``asyncio`` framework as a back-end and therefore on Windows will not stream the data from the subprocess as it does on Unix machines.
Instead data will not be yielded until the subprocess is finished and all output is buffered (the normal warnings about long running programs with lots of output apply).

The streaming of output does not work on Windows because on Windows the :py:func:`select.select` method only works on sockets and not file-like objects which are used with subprocess pipes.
``asyncio`` implements Windows subprocess support by implementing a Proactor event loop based on Window's IOCP API.
One future option will be to implement this synchronous style method using IOCP in this module, but another option is to just make synchronous the asynchronous calls, but there are issues with that as well.
In the mean time, if you need streaming of output in both Windows and Unix, use the asynchronous calls.

.. autofunction:: osrf_pycommon.process_utils.execute_process

Availability: Unix (streaming), Windows (blocking)

.. autofunction:: osrf_pycommon.process_utils.execute_process_split

Availability: Unix (streaming), Windows (blocking)

Utility Functions
-----------------

Currently there is only one utility function, a Python implementation of the ``which`` shell command.

.. autofunction:: osrf_pycommon.process_utils.which
