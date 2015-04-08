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
This module provides tools for colorizing terminal output.

This module defines the ansi escape sequences used for colorizing the
output from terminal programs in Linux.
You can access the ansi escape sequences using the :py:func:`ansi` function:

.. code-block:: python

    >>> from osrf_pycommon.terminal_color import ansi
    >>> print(["This is ", ansi('red'), "red", ansi('reset'), "."])
    ['This is ', '\\x1b[31m', 'red', '\\x1b[0m', '.']

You can also use :py:func:`format_color` to do in-line substitution of keys
wrapped in ``@{}`` markers for their ansi escape sequences:

.. code-block:: python

    >>> from osrf_pycommon.terminal_color import format_color
    >>> print(format_color("This is @{bf}blue@{reset}.").split())
    ['This', 'is', '\\x1b[34mblue\\x1b[0m.']

This is a list of all of the available substitutions:

+-------------------+--------------+--------------+
| Long Form         | Shorter      | Value        |
+===================+==============+==============+
| ``@{blackf}``     | ``@{kf}``    | ``\\033[30m`` |
+-------------------+--------------+--------------+
| ``@{redf}``       | ``@{rf}``    | ``\\033[31m`` |
+-------------------+--------------+--------------+
| ``@{greenf}``     | ``@{gf}``    | ``\\033[32m`` |
+-------------------+--------------+--------------+
| ``@{yellowf}``    | ``@{yf}``    | ``\\033[33m`` |
+-------------------+--------------+--------------+
| ``@{bluef}``      | ``@{bf}``    | ``\\033[34m`` |
+-------------------+--------------+--------------+
| ``@{purplef}``    | ``@{pf}``    | ``\\033[35m`` |
+-------------------+--------------+--------------+
| ``@{cyanf}``      | ``@{cf}``    | ``\\033[36m`` |
+-------------------+--------------+--------------+
| ``@{whitef}``     | ``@{wf}``    | ``\\033[37m`` |
+-------------------+--------------+--------------+
| ``@{blackb}``     | ``@{kb}``    | ``\\033[40m`` |
+-------------------+--------------+--------------+
| ``@{redb}``       | ``@{rb}``    | ``\\033[41m`` |
+-------------------+--------------+--------------+
| ``@{greenb}``     | ``@{gb}``    | ``\\033[42m`` |
+-------------------+--------------+--------------+
| ``@{yellowb}``    | ``@{yb}``    | ``\\033[43m`` |
+-------------------+--------------+--------------+
| ``@{blueb}``      | ``@{bb}``    | ``\\033[44m`` |
+-------------------+--------------+--------------+
| ``@{purpleb}``    | ``@{pb}``    | ``\\033[45m`` |
+-------------------+--------------+--------------+
| ``@{cyanb}``      | ``@{cb}``    | ``\\033[46m`` |
+-------------------+--------------+--------------+
| ``@{whiteb}``     | ``@{wb}``    | ``\\033[47m`` |
+-------------------+--------------+--------------+
| ``@{escape}``     |              | ``\\033``     |
+-------------------+--------------+--------------+
| ``@{reset}``      | ``@|``       | ``\\033[0m``  |
+-------------------+--------------+--------------+
| ``@{boldon}``     | ``@!``       | ``\\033[1m``  |
+-------------------+--------------+--------------+
| ``@{italicson}``  | ``@/``       | ``\\033[3m``  |
+-------------------+--------------+--------------+
| ``@{ulon}``       | ``@_``       | ``\\033[4m``  |
+-------------------+--------------+--------------+
| ``@{invon}``      |              | ``\\033[7m``  |
+-------------------+--------------+--------------+
| ``@{boldoff}``    |              | ``\\033[22m`` |
+-------------------+--------------+--------------+
| ``@{italicsoff}`` |              | ``\\033[23m`` |
+-------------------+--------------+--------------+
| ``@{uloff}``      |              | ``\\033[24m`` |
+-------------------+--------------+--------------+
| ``@{invoff}``     |              | ``\\033[27m`` |
+-------------------+--------------+--------------+

These substitution's values come from the ANSI color escape sequences,
see: http://en.wikipedia.org/wiki/ANSI_escape_code

Also for any of the keys which have a trailing ``f``, you can safely drop the
trailing ``f`` and get the same thing.

For example, ``format_color("@{redf}")`` and ``format_color("@{red}")`` are
functionally equivalent.

Also, many of the substitutions have shorten forms for convenience, such that
``@{redf}``, ``@{rf}``, ``@{red}``, and ``@{r}`` are all the same.

Note that a trailing ``b`` is always required when specifying a background.

Some of the most common non-color sequences have ``{}``'less versions.

For example, ``@{boldon}``'s shorter form is ``@!``.

By default, the substitutions (and calls to :py:func:`ansi`) resolve to escape
sequences, but if you call :py:func:`disable_ansi_color_substitution_globally`
then they will resolve to empty strings.

This allows you to always use the substitution strings and disable them
globally when desired.

On Windows the substitutions are always resolved to empty strings as the
ansi escape sequences do not work on Windows.
Instead strings annotated with ``@{}`` style substitutions or raw ``\\x1b[xxm``
style ansi escape sequences must be passed to :py:func:`print_color` in order
for colors to be displayed on windows.
Also the :py:func:`print_ansi_color_win32` function can be used on strings
which only contain ansi escape sequences.

.. note::

    There are existing Python modules like
    `colorama <https://pypi.python.org/pypi/colorama>`_ which provide ansi
    colorization on multiple platforms, so a valid question is:
    "why write this module?".
    The reason for writing this module is to provide the color annotation of
    strings and functions for removing or replacing ansi escape sequences which
    are not provided by modules like colorama.
    This module could have depended on colorama for colorization on Windows,
    but colorama works by replacing the built-in ``sys.stdout`` and
    ``sys.stderr``, which we did not want and it has extra functionality that
    we do not need.
    So, instead of depending on colorama, the Windows color printing code
    was used as the inspiration for the Windows color printing in the
    ``windows.py`` module in this ``terminal_color`` package.
    The colorama license was placed in the header of that file and the colorama
    license is compatible with this package's license.

"""

from .ansi_re import remove_ansi_escape_senquences
from .ansi_re import split_by_ansi_escape_sequence

from .impl import ansi
from .impl import disable_ansi_color_substitution_globally
from .impl import enable_ansi_color_substitution_globally
from .impl import format_color
from .impl import get_ansi_dict
from .impl import print_ansi_color_win32
from .impl import print_color
from .impl import sanitize
from .impl import test_colors

__all__ = [
    'ansi',
    'disable_ansi_color_substitution_globally',
    'enable_ansi_color_substitution_globally',
    'format_color',
    'get_ansi_dict',
    'print_ansi_color_win32',
    'print_color',
    'remove_ansi_escape_senquences',
    'sanitize',
    'split_by_ansi_escape_sequence',
    'test_colors',
]
