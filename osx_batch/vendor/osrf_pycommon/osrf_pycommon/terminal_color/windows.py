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

# Some of the code in this module is taken from the colorama project:
#
#     https://github.com/tartley/colorama
#
# Which is licensed under the standard 3-claus new BSD license, here is a copy:
#
#     Copyright (c) 2010 Jonathan Hartley
#     All rights reserved.
#
#     Redistribution and use in source and binary forms, with or without
#     modification, are permitted provided that the following conditions
#     are met:
#
#     * Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
#     * Neither the name of the copyright holders, nor those of its
#       contributors may be used to endorse or promote products derived from
#       this software without specific prior written permission.
#
#     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#     "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
#     PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
#     OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#     EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#     PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#     PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#     LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#     NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# End copy.

from __future__ import print_function

import ctypes
import ctypes.wintypes
import os
import sys

from .ansi_re import split_by_ansi_escape_sequence

# From winbase.h
STDOUT = -11
STDERR = -12
NORMAL = 0x00
BRIGHT = 0x08


def _print_ansi_color_win32(*args, **kwargs):
    global STDOUT, STDERR
    # Validate the kwargs
    for kwarg in kwargs:
        if kwarg not in ['sep', 'end', 'file']:
            raise TypeError(
                "'{0}' is an invalid keyword argument for this function"
                .format(kwarg))
    sep = kwargs.get('sep', ' ')
    end = kwargs.get('end', os.linesep)
    file = kwargs.get('file', sys.stdout)
    file = sys.stdout if file is None else file
    # For each argument, split into more arguments split on ansi escape
    # sequences and replacing them with (cmd, arg) tuples for Windows
    # For example:
    #
    #   `\033]31mred\033]0m` => `[(_win_foreground, 4), 'red', (_win_reset, )]`
    args = [token for arg in args
            for token in _tokenize_ansi_string_for_win32(arg) + [sep]]
    # There is always a trailing sep, strip it
    args = args[:-1]
    # Figure out where the data is getting written to
    try:
        fn = file.fileno()
    except AttributeError:
        fn = None
    if fn == 1:  # stdout
        handle = STDOUT
    elif fn == 2:  # stderr
        handle = STDERR
    else:  # something else, which cannot be colored
        handle = None
    if handle is None:
        # Cannot colorize, strip colorization tuples and pass on to print
        args = [a for a in args if not isinstance(a, tuple)]
        return print(*args, sep=sep, end=end, file=file)
    default_attrs = GetConsoleScreenBufferInfo(handle).wAttributes
    # Print tokenized arguments
    attrs = _print_args(args, handle, default_attrs, default_attrs, file)
    # Print ending
    end = _tokenize_ansi_string_for_win32(end)
    _print_args(end, handle, attrs, default_attrs, file)


def _print_args(args, handle, attrs, default_attrs, file):
    for i, arg in enumerate(args):
        if isinstance(arg, tuple):
            # Do the proper thing on the windows console
            assert len(arg) > 0, arg
            if arg[0] == _win_reset:
                attrs = arg[0](handle, default_attrs)
            elif arg[0] == _win_style and len(arg) > 1 and arg[1] is None:
                # Means the style is not supported on Windows
                continue
            else:
                attrs = arg[0](*(arg[1:] + (handle, attrs)))
        else:
            print(arg, end='', file=file)
    return attrs


def _unpack_attrs(attrs):
    return [attrs & 7, (attrs << 4) & 7, attrs & BRIGHT]


def _pack_attrs(foreground, background, style):
    return foreground + (background * 16) + style


def _win_reset(handle, attrs):
    SetConsoleTextAttribute(handle, attrs)
    return attrs


def _win_style(style, handle, attrs):
    attrs_list = _unpack_attrs(attrs)
    attrs_list[2] = style
    attrs = _pack_attrs(*attrs_list)
    SetConsoleTextAttribute(handle, attrs)
    return attrs


def _win_foreground(foreground, handle, attrs):
    attrs_list = _unpack_attrs(attrs)
    attrs_list[0] = foreground
    attrs = _pack_attrs(*attrs_list)
    SetConsoleTextAttribute(handle, attrs)
    return attrs


def _win_background(background, handle, attrs):
    attrs_list = _unpack_attrs(attrs)
    attrs_list[1] = background
    attrs = _pack_attrs(*attrs_list)
    SetConsoleTextAttribute(handle, attrs)
    return attrs

_ansi_to_win32 = {
    '\x1b[0m': (_win_reset, ),          # reset
    '\x1b[1m': (_win_style, BRIGHT),    # boldon, see wincon.h
    '\x1b[22m': (_win_style, NORMAL),   # boldoff, see wincon.h
    '\x1b[3m': (_win_style, None),      # italicson, nothing on Windows
    '\x1b[23m': (_win_style, None),     # italicsoff, nothing on Windows
    '\x1b[4m': (_win_style, None),      # ulon, nothing on Windows
    '\x1b[24m': (_win_style, None),     # uloff, nothing on Windows
    '\x1b[7m': (_win_style, None),      # invon, nothing on Windows
    '\x1b[27m': (_win_style, None),     # invoff, nothing on Windows
    '\x1b[30m': (_win_foreground, 0),   # blackf
    '\x1b[40m': (_win_background, 0),   # blackb
    '\x1b[34m': (_win_foreground, 1),   # bluef
    '\x1b[44m': (_win_background, 1),   # blueb
    '\x1b[32m': (_win_foreground, 2),   # greenf
    '\x1b[42m': (_win_background, 2),   # greenb
    '\x1b[36m': (_win_foreground, 3),   # cyanf
    '\x1b[46m': (_win_background, 3),   # cyanb
    '\x1b[31m': (_win_foreground, 4),   # redf
    '\x1b[41m': (_win_background, 4),   # redb
    '\x1b[35m': (_win_foreground, 5),   # purplef
    '\x1b[45m': (_win_background, 5),   # purpleb
    '\x1b[33m': (_win_foreground, 6),   # yellowf
    '\x1b[43m': (_win_background, 6),   # yellowb
    '\x1b[37m': (_win_foreground, 7),   # whitef
    '\x1b[47m': (_win_background, 7),   # whiteb
}


def _tokenize_ansi_string_for_win32(msg):
    global _ansi_to_win32
    tokens = filter(None, split_by_ansi_escape_sequence(msg, True))
    tokens = [_ansi_to_win32.get(t, t) for t in tokens]
    return tokens

windll = ctypes.LibraryLoader(ctypes.WinDLL)

# Replication of types and defines from winbase.h


class CONSOLE_SCREEN_BUFFER_INFO(ctypes.Structure):
    _fields_ = [
        ("dwSize", ctypes.wintypes._COORD),
        ("dwCursorPosition", ctypes.wintypes._COORD),
        ("wAttributes", ctypes.wintypes.WORD),
        ("srWindow", ctypes.wintypes.SMALL_RECT),
        ("dwMaximumWindowSize", ctypes.wintypes._COORD),
    ]

    def __str__(self):
        return (
            '({0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0})'
            .format(
                self.dwSize.Y, self.dwSize.X,
                self.dwCursorPosition.Y, self.dwCursorPosition.X,
                self.wAttributes,
                self.srWindow.Top, self.srWindow.Left,
                self.srWindow.Bottom, self.srWindow.Right,
                self.dwMaximumWindowSize.Y, self.dwMaximumWindowSize.X)
        )

_GetStdHandle = windll.kernel32.GetStdHandle
_GetStdHandle.argtypes = [
    ctypes.wintypes.DWORD,
]
_GetStdHandle.restype = ctypes.wintypes.HANDLE

_GetConsoleScreenBufferInfo = windll.kernel32.GetConsoleScreenBufferInfo
_GetConsoleScreenBufferInfo.argtypes = [
    ctypes.wintypes.HANDLE,
    ctypes.POINTER(CONSOLE_SCREEN_BUFFER_INFO),
]
_GetConsoleScreenBufferInfo.restype = ctypes.wintypes.BOOL

_SetConsoleTextAttribute = windll.kernel32.SetConsoleTextAttribute
_SetConsoleTextAttribute.argtypes = [
    ctypes.wintypes.HANDLE,
    ctypes.wintypes.WORD,
]
_SetConsoleTextAttribute.restype = ctypes.wintypes.BOOL

handles = {
    STDOUT: _GetStdHandle(STDOUT),
    STDERR: _GetStdHandle(STDERR),
}


def GetConsoleScreenBufferInfo(stream_id=STDOUT):
    global handles, CONSOLE_SCREEN_BUFFER_INFO, _GetConsoleScreenBufferInfo
    handle = handles[stream_id]
    csbi = CONSOLE_SCREEN_BUFFER_INFO()
    _GetConsoleScreenBufferInfo(handle, ctypes.byref(csbi))
    return csbi


def SetConsoleTextAttribute(stream_id, attrs):
    global handles, _SetConsoleTextAttribute
    handle = handles[stream_id]
    return _SetConsoleTextAttribute(handle, attrs)
