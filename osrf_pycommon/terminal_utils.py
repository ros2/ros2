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

"""
This module has a miscellaneous set of functions for working with terminals.

You can use the :py:func:`get_terminal_dimensions` to get the width and
height of the terminal as a tuple.

You can also use the :py:func:`is_tty` function to determine if a given object
is a tty.
"""

__all__ = ['GetTerminalDimensionsError', 'get_terminal_dimensions', 'is_tty']

import os
import struct
import subprocess


class GetTerminalDimensionsError(Exception):
    """Raised when the terminal dimensions cannot be determined."""
    pass


def _get_terminal_dimensions_windows():
    try:
        from ctypes import create_string_buffer
        from ctypes import windll
    except ImportError as exc:
        raise GetTerminalDimensionsError("Failed to get dimensions: {0}"
                                         .format(exc))
    STDOUT = -11
    h = windll.kernel32.GetStdHandle(STDOUT)
    buffer_info = create_string_buffer(22)
    if not windll.kernel32.GetConsoleScreenBufferInfo(h, buffer_info):
        raise GetTerminalDimensionsError(
            "Call to windll.kernel32.GetConsoleScreenBufferInfo failed")

    try:
        (_, _, _, _, _, left, top, right, bottom, _, _) \
            = struct.unpack("hhhhHhhhhhh", buffer_info.raw)
    except struct.error as exc:
        raise GetTerminalDimensionsError("Failed to unpack data: {0}"
                                         .format(exc))
    width = right - left + 1
    height = bottom - top + 1

    return width, height


def _get_terminal_dimensions_unix():
    # This function uses `tput` and should work on any Unix system
    # See: http://en.wikipedia.org/wiki/Tput
    try:
        width = subprocess.check_output(['tput', 'cols'])

        width = int(width.strip())
    except (subprocess.CalledProcessError, ValueError) as exc:
        raise GetTerminalDimensionsError("Failed to get width: {0}"
                                         .format(exc))
    try:
        height = subprocess.check_output(['tput', 'lines'])

        height = int(height.strip())
    except (subprocess.CalledProcessError, ValueError) as exc:
        raise GetTerminalDimensionsError("Failed to get height: {0}"
                                         .format(exc))
    return width, height


def get_terminal_dimensions():
    """Returns the width and height of the terminal.

    :returns: width and height in that order as a tuple
    :rtype: tuple
    :raises: GetTerminalDimensionsError when the terminal dimensions
        cannot be determined
    """
    if os.name in ['nt']:
        return _get_terminal_dimensions_windows()
    return _get_terminal_dimensions_unix()


def is_tty(stream):
    """Returns True if the given stream is a tty, else False

    :param stream: object to be checked for being a tty
    :returns: True if the given object is a tty, otherwise False
    :rtype: bool
    """
    return hasattr(stream, 'isatty') and stream.isatty()
