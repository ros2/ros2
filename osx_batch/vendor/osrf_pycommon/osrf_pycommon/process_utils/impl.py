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
import sys

from .execute_process_nopty import _execute_process_nopty
try:
    from .execute_process_pty import _execute_process_pty
except ImportError:
    # pty doesn't work on Windows, it will fail to import
    # so fallback to non pty implementation
    _execute_process_pty = None

try:
    _basestring = basestring  # Python 2
except NameError:
    _basestring = str  # Python 3


def execute_process(cmd, cwd=None, env=None, shell=False, emulate_tty=False):
    """Executes a command with arguments and returns output line by line.

    All arguments, except ``emulate_tty``, are passed directly to
    :py:class:`subprocess.Popen`.

    ``execute_process`` returns a generator which yields the output, line by
    line, until the subprocess finishes at which point the return code
    is yielded.

    This is an example of how this function should be used:

    .. code-block:: python

        from osrf_pycommon.process_utils import execute_process

        cmd = ['ls', '-G']
        for line in execute_process(cmd, cwd='/usr'):
            if isinstance(line, int):
                # This is a return code, the command has exited
                print("'{0}' exited with: {1}".format(' '.join(cmd), line))
                continue  # break would also be appropriate here
            # Then print it to the screen
            print(line, end='')

    ``stdout`` and ``stderr`` are always captured together and returned line
    by line through the returned generator.
    New line characters are preserved in the output, so if re-printing the data
    take care to use ``end=''`` or first ``rstrip`` the output lines.

    When ``emulate_tty`` is used on Unix systems, commands will identify that
    they are on a tty and should output color to the screen as if you were
    running it on the terminal, and therefore there should not be any need to
    pass arguments like ``-c color.ui=always`` to commands like ``git``.
    Additionally, programs might also behave differently in when
    ``emulate_tty`` is being used, for example, Python will default to
    unbuffered output when it detects a tty.

    ``emulate_tty`` works by using psuedo-terminals on Unix machines, and so
    if you are running this command many times in parallel (like hundreds
    of times) then you may get one of a few different :py:exc:`OSError`'s.
    For example, "OSError: [Errno 24] Too many open files: '/dev/ttyp0'" or
    "OSError: out of pty devices".
    You should also be aware that you share pty devices with the rest of the
    system, so even if you are not using a lot, it is possible to get
    this error.
    You can catch this error before getting data from the generator, so when
    using ``emulate_tty`` you might want to do something like this:

    .. code-block:: python

        from osrf_pycommon.process_utils import execute_process

        cmd = ['ls', '-G', '/usr']
        try:
            output = execute_process(cmd, emulate_tty=True)
        except OSError:
            output = execute_process(cmd, emulate_tty=False)
        for line in output:
            if isinstance(line, int):
                print("'{0}' exited with: {1}".format(' '.join(cmd), line))
                continue
            print(line, end='')

    This way if a pty cannot be opened in order to emulate the tty then you
    can try again without emulation, and any other :py:exc:`OSError` should
    raise again with ``emulate_tty`` set to ``False``.
    Obviously, you only want to do this if emulating the tty is non-critical
    to your processing, like when you are using it to capture color.

    Any color information that the command outputs as ANSI escape sequences
    is captured by this command.
    That way you can print the output to the screen and preserve the color
    formatting.

    If you do not want color to be in the output, then try setting
    ``emulate_tty`` to ``False``, but that does not guarantee that there is no
    color in the output, instead it only will cause called processes to
    identify that they are not being run in a terminal.
    Most well behaved programs will not output color if they detect that
    they are not being executed in a terminal, but you shouldn't rely on that.

    If you want to ensure there is no color in the output from an executed
    process, then use this function:

    :py:func:`osrf_pycommon.terminal_color.remove_ansi_escape_senquences`

    Exceptions can be raised by functions called by the implementation,
    for example, :py:class:`subprocess.Popen` can raise an :py:exc:`OSError`
    when the given command is not found.
    If you want to check for the existence of an executable on the path,
    see: :py:func:`which`.
    However, this function itself does not raise any special exceptions.

    :param list cmd: list of strings with the first item being a command
        and subsequent items being any arguments to that command;
        passed directly to :py:class:`subprocess.Popen`.
    :param str cwd: path in which to run the command, defaults to None which
        means :py:func:`os.getcwd` is used;
        passed directly to :py:class:`subprocess.Popen`.
    :param dict env: environment dictionary to use for executing the command,
        default is None which uses the :py:obj:`os.environ` environment;
        passed directly to :py:class:`subprocess.Popen`.
    :param bool shell: If True the system shell is used to evaluate the
        command, default is False;
        passed directly to :py:class:`subprocess.Popen`.
    :param bool emulate_tty: If True attempts to use a pty to convince
        subprocess's that they are being run in a terminal. Typically this is
        useful for capturing colorized output from commands. This does not
        work on Windows (no pty's), so it is considered False even when True.
        Defaults to False.
    :returns: a generator which yields output from the command line by line
    :rtype: generator which yields strings
    """
    exp_func = _execute_process_nopty
    if emulate_tty and _execute_process_pty is not None:
        exp_func = _execute_process_pty
    for out, err, ret in exp_func(cmd, cwd, env, shell, stderr_to_stdout=True):
        if ret is None:
            yield out
        yield ret


def execute_process_split(
    cmd, cwd=None, env=None, shell=False, emulate_tty=False
):
    """:py:func:`execute_process`, except ``stderr`` is returned separately.

    Instead of yielding output line by line until yielding a return code, this
    function always a triplet of ``stdout``, ``stderr``, and return code.
    Each time only one of the three will not be None.
    Once you receive a non-None return code (type will be int) there will be no
    more ``stdout`` or ``stderr``.
    Therefore you can use the command like this:

    .. code-block:: python

        import sys
        from osrf_pycommon.process_utils import execute_process_split

        cmd = ['ls', '-G']
        for out, err, ret in execute_process_split(cmd, cwd='/usr'):
            if ret is not None:
                # This is a return code, the command has exited
                print("'{0}' exited with: {1}".format(' '.join(cmd), ret))
            elif out is not None:
                print(out, end='')
            elif err is not None:
                print(err, end='', file=sys.stderr)

    When using this, it is possible that the ``stdout`` and ``stderr`` data can
    be returned in a different order than what would happen on the terminal.
    This is due to the fact that the subprocess is given different buffers for
    ``stdout`` and ``stderr`` and so there is a race condition on the
    subprocess writing to the different buffers and this command reading the
    buffers.
    This can be avoided in most scenarios by using ``emulate_tty``, because of
    the use of ``pty``'s, though the ordering can still not be guaranteed and
    the number of ``pty``'s is finite as explained in the documentation for
    :py:func:`execute_process`.
    For situations where output ordering between ``stdout`` and ``stderr`` are
    critical, they should not be returned separately and instead should share
    one buffer, and so :py:func:`execute_process` should be used.

    For all other parameters and documentation see: :py:func:`execute_process`
    """
    exp_func = _execute_process_nopty
    if emulate_tty and _execute_process_pty is not None:
        exp_func = _execute_process_pty
    return exp_func(cmd, cwd, env, shell, stderr_to_stdout=True)

try:
    from shutil import which as _which
except ImportError:
    _which = None


def _which_backport(cmd, mode=os.F_OK | os.X_OK, path=None):
    # Check that a given file can be accessed with the correct mode.
    # Additionally check that `file` is not a directory, as on Windows
    # directories pass the os.access check.
    def _access_check(fn, mode):
        return (os.path.exists(fn) and os.access(fn, mode)
                and not os.path.isdir(fn))

    # If we're given a path with a directory part, look it up directly rather
    # than referring to PATH directories. This includes checking relative
    # to the current directory, e.g. ./script
    if os.path.dirname(cmd):
        if _access_check(cmd, mode):
            return cmd
        return None

    if path is None:
        path = os.environ.get("PATH", os.defpath)
    if not path:
        return None
    path = path.split(os.pathsep)

    if sys.platform == "win32":
        # The current directory takes precedence on Windows.
        if os.curdir not in path:
            path.insert(0, os.curdir)

        # PATHEXT is necessary to check on Windows.
        pathext = os.environ.get("PATHEXT", "").split(os.pathsep)
        # See if the given file matches any of the expected path extensions.
        # This will allow us to short circuit when given "python.exe".
        # If it does match, only test that one, otherwise we have to try
        # others.
        if any(cmd.lower().endswith(ext.lower()) for ext in pathext):
            files = [cmd]
        else:
            files = [cmd + ext for ext in pathext]
    else:
        # On other platforms you don't have things like PATHEXT to tell you
        # what file suffixes are executable, so just pass on cmd as-is.
        files = [cmd]

    seen = set()
    for directory in path:
        normdir = os.path.normcase(directory)
        if normdir not in seen:
            seen.add(normdir)
            for thefile in files:
                name = os.path.join(directory, thefile)
                if _access_check(name, mode):
                    return name
    return None


def which(cmd, mode=os.F_OK | os.X_OK, path=None, **kwargs):
    """Given a command, mode, and a PATH string, return the path which
    conforms to the given mode on the PATH, or None if there is no such
    file.

    `mode` defaults to ``os.F_OK | os.X_OK``. `path` defaults to the result
    of ``os.environ.get("PATH")``, or can be overridden with a custom search
    path.

    Backported from :py:func:`shutil.which`
    (`<https://docs.python.org/3.3/library/shutil.html#shutil.which>`_),
    available in Python 3.3.
    """
    kwargs.update({'mode': mode, 'path': path})
    global _which
    if _which is not None:
        return _which(cmd, **kwargs)
    return _which_backport(cmd, **kwargs)
