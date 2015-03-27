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
import string

_is_windows = (os.name in ['nt'])

if _is_windows:
    from .windows import _print_ansi_color_win32

_ansi = {
    # Escape sequence start
    'escape': '\x1b',

    # Reset
    'reset': '\x1b[0m',
    '|': '\x1b[0m',
    'atbar': '@|',

    # Bold on
    'boldon': '\x1b[1m',
    '!': '\x1b[1m',
    'atexclimation': '@!',

    # Bold off
    'boldoff': '\x1b[22m',

    # Italics on
    'italicson': '\x1b[3m',
    '/': '\x1b[3m',
    'atfwdslash': '@/',

    # Intalics off
    'italicsoff': '\x1b[23m',

    # Underline on
    'ulon': '\x1b[4m',
    '_': '\x1b[4m',
    'atunderscore': '@_',

    # Underline off
    'uloff': '\x1b[24m',

    # Invert foreground/background on/off
    'invon': '\x1b[7m',
    'invoff': '\x1b[27m',

    # Black foreground
    'k': '\x1b[30m',
    'kf': '\x1b[30m',
    'black': '\x1b[30m',
    'blackf': '\x1b[30m',

    # Black background
    'kb': '\x1b[40m',
    'blackb': '\x1b[40m',

    # Blue foreground
    'b': '\x1b[34m',
    'bf': '\x1b[34m',
    'blue': '\x1b[34m',
    'bluef': '\x1b[34m',

    # Blue background
    'bb': '\x1b[44m',
    'blueb': '\x1b[44m',

    # Cyan foreground
    'c': '\x1b[36m',
    'cf': '\x1b[36m',
    'cyan': '\x1b[36m',
    'cyanf': '\x1b[36m',

    # Cyan background
    'cb': '\x1b[46m',
    'cyanb': '\x1b[46m',

    # Green foreground
    'g': '\x1b[32m',
    'gf': '\x1b[32m',
    'green': '\x1b[32m',
    'greenf': '\x1b[32m',

    # Green background
    'gb': '\x1b[42m',
    'greenb': '\x1b[42m',

    # Purple (magenta) foreground
    'p': '\x1b[35m',
    'pf': '\x1b[35m',
    'purple': '\x1b[35m',
    'purplef': '\x1b[35m',

    # Purple (magenta) background
    'pb': '\x1b[45m',
    'purpleb': '\x1b[45m',

    # Red foreground
    'r': '\x1b[31m',
    'rf': '\x1b[31m',
    'red': '\x1b[31m',
    'redf': '\x1b[31m',

    # Red background
    'rb': '\x1b[41m',
    'redb': '\x1b[41m',

    # White foreground
    'w': '\x1b[37m',
    'wf': '\x1b[37m',
    'white': '\x1b[37m',
    'whitef': '\x1b[37m',

    # White background
    'wb': '\x1b[47m',
    'whiteb': '\x1b[47m',

    # Yellow foreground
    'y': '\x1b[33m',
    'yf': '\x1b[33m',
    'yellow': '\x1b[33m',
    'yellowf': '\x1b[33m',

    # Yellow background
    'yb': '\x1b[43m',
    'yellowb': '\x1b[43m',
}
# Set all values to empty string
_null_ansi = dict([(k, '') for k, v in _ansi.items()])
# Except format preservers used by sanitize
_null_ansi.update({
    'atexclimation': '@!',
    'atfwdslash': '@/',
    'atunderscore': '@_',
    'atbar': '@|',
})
# Enable by default
_enabled = True


def ansi(key):
    """Returns the escape sequence for a given ansi color key."""
    global _ansi, _null_ansi, _enabled
    return (_ansi if _enabled else _null_ansi)[key]


def get_ansi_dict():
    """Returns a copy of the dictionary of keys and ansi escape sequences."""
    global _ansi
    return dict(_ansi)


def enable_ansi_color_substitution_globally():
    """
    Causes :py:func:`format_color` to replace color annotations with ansi
    esacpe sequences.

    It also affects :py:func:`ansi`.

    This is the case by default, so there is no need to call this everytime.

    If you have previously caused all substitutions to evaluate to an empty
    string by calling :py:func:`disable_ansi_color_substitution_globally`, then
    you can restore the escape sequences for substitutions by calling this
    function.
    """
    global _enabled
    _enabled = True


def disable_ansi_color_substitution_globally():
    """
    Causes :py:func:`format_color` to replace color annotations with
    empty strings.

    It also affects :py:func:`ansi`.

    This is not the case by default, so if you want to make all substitutions
    given to either function mentioned above return empty strings then call
    this function.

    The default behavior can be restored by calling
    :py:func:`enable_ansi_color_substitution_globally`.
    """
    global _enabled
    _enabled = False


def format_color(msg):
    """
    Replaces color annotations with ansi escape sequences.

    See this module's documentation for the list of available substitutions.

    If :py:func:`disable_ansi_color_substitution_globally` has been called
    then all color annotations will be replaced by empty strings.

    Also, on Windows all color annotations will be replaced with empty strings.
    If you want colorization on Windows, you must pass annotated strings to
    :py:func:`print_color`.

    :param str msg: string message to be colorized
    :returns: colorized string
    :rtype: str
    """
    global _ansi, _null_ansi, _enabled
    ansi_dict = _null_ansi if not _enabled or _is_windows else _ansi
    return _format_color(msg, ansi_dict)


def _format_color(msg, ansi_dict):
    msg = msg.replace('@!', '@{boldon}')
    msg = msg.replace('@/', '@{italicson}')
    msg = msg.replace('@_', '@{ulon}')
    msg = msg.replace('@|', '@{reset}')

    class ColorTemplate(string.Template):
        delimiter = '@'
    return ColorTemplate(msg).substitute(ansi_dict)


def print_ansi_color_win32(*args, **kwargs):
    """
    Prints color string containing ansi escape sequences to console in Windows.

    If called on a non-Windows system, a :py:exc:`NotImplementedError` occurs.

    Does not respect :py:func:`disable_ansi_color_substitution_globally`.

    Does not substitute color annotations like ``@{r}`` or ``@!``, the string
    must already contain the ``\\033[1m`` style ansi escape sequences.

    Works by splitting each argument up by ansi escape sequence, printing
    the text between the sequences, and doing the corresponding win32 action
    for each ansi sequence encountered.
    """
    if not _is_windows:
        raise NotImplementedError(
            "print_ansi_color_win32() is not implemented for this system")
    return _print_ansi_color_win32(*args, **kwargs)


def print_color(*args, **kwargs):
    """
    Colorizes and prints with an implicit ansi reset at the end

    Calls :py:func:`format_color` on each positional argument and then sends
    all positional and keyword arguments to :py:obj:`print`.

    If the ``end`` keyword argument is not present then the default end value
    ``ansi('reset') + '\\n'`` is used and passed to :py:obj:`print`.

    :py:obj:`os.linesep` is used to determine the actual value for ``\\n``.

    Therefore, if you use the ``end`` keyword argument be sure to include
    an ansi reset escape sequence if necessary.

    On Windows the substituted arguments and keyword arguments are passed to
    :py:func:`print_ansi_color_win32` instead of just :py:obj:`print`.
    """
    global _ansi, _null_ansi, _enabled
    # If no end given, use reset + new line
    if 'end' not in kwargs:
        kwargs['end'] = '{0}{1}'.format(ansi('reset'), os.linesep)
    args = [_format_color(a, _ansi if _enabled else _null_ansi) for a in args]
    # If windows, pass to win32 print color function
    if _enabled and _is_windows:
        return print_ansi_color_win32(*args, **kwargs)
    return print(*args, **kwargs)


def sanitize(msg):
    """
    Sanitizes the given string to prevent :py:func:`format_color` from
    substituting content.

    For example, when the string ``'Email: {user}@{org}'`` is passed to
    :py:func:`format_color` the ``@{org}`` will be incorrectly recognized
    as a colorization annotation and it will fail to substitute with a
    :py:exc:`KeyError`: ``org``.

    In order to prevent this, you can first "sanatize" the string, add color
    annotations, and then pass the whole string to :py:func:`format_color`.

    If you give this function the string ``'Email: {user}@{org}'``, then it
    will return ``'Email: {{user}}@@{{org}}'``. Then if you pass that to
    :py:func:`format_color` it will return ``'Email: {user}@{org}'``.
    In this way :py:func:`format_color` is the reverse of this function and
    so it is safe to call this function on any incoming data if it will
    eventually be passed to :py:func:`format_color`.

    In addition to expanding ``{`` => ``{{``, ``}`` => ``}}``, and
    ``@`` => ``@@``, this function will also replace any instances of
    ``@!``, ``@/``, ``@_``, and ``@|`` with ``@{atexclimation}``,
    ``@{atfwdslash}``, ``@{atunderscore}``, and ``@{atbar}`` respectively.
    And then there are corresponding keys in the ansi dict to convert them
    back.

    For example, if you pass the string ``'|@ Notice @|'`` to this function
    it will return ``'|@@ Notice @{atbar}'``.
    And since ``ansi('atbar')`` always returns ``@|``, even when
    :py:func:`disable_ansi_color_substitution_globally` has been called, the
    result of passing that string to :py:func:`format_color` will be
    ``'|@ Notice @|'`` again.

    There are two main strategies for constructing strings which use both the
    Python :py:func:`str.format` function and the colorization annotations.

    One way is to just build each piece and concatenate the result:

    .. code-block:: python

        print_color("@{r}", "{error}".format(error=error_str))
        # Or using print (remember to include an ansi reset)
        print(format_color("@{r}" + "{error}".format(error=error_str) + "@|"))

    Another way is to use this function on the format string, concatenate to
    the annotations, pass the whole string to :py:func:`format_color`, and then
    format the whole thing:

    .. code-block:: python

        print(format_color("@{r}" + sanitize("{error}") + "@|")
              .format(error=error_str))

    However, the most common use for this function is to sanitize incoming
    strings which may have unknown content:

    .. code-block:: python

        def my_func(user_content):
            print_color("@{y}" + sanitize(user_content))

    This function is not intended to be used on strings with color annotations.

    :param str msg: string message to be sanitized
    :returns: sanitized string
    :rtype: str
    """
    msg = msg.replace('@', '@@')
    msg = msg.replace('{', '{{')
    msg = msg.replace('}', '}}')
    # Above line `msg = msg.replace('@', '@@')` will have converted @* to @@*
    msg = msg.replace('@@!', '@{atexclimation}')
    msg = msg.replace('@@/', '@{atfwdslash}')
    msg = msg.replace('@@_', '@{atunderscore}')
    msg = msg.replace('@@|', '@{atbar}')
    return msg


def test_colors(file=None):
    """Prints a color testing block using :py:func:`print_color`"""
    print_color("| Normal     | @!Bold Normal", file=file)
    print_color("| @{kf}Black      @|| @!@{kf}Bold Black", file=file)
    print_color("| @{rf}Red        @|| @!@{rf}Bold Red", file=file)
    print_color("| @{gf}Green      @|| @!@{gf}Bold Green", file=file)
    print_color("| @{yf}Yellow     @|| @!@{yf}Bold Yellow", file=file)
    print_color("| @{bf}Blue       @|| @!@{bf}Bold Blue", file=file)
    print_color("| @{pf}Purple     @|| @!@{pf}Bold Purple", file=file)
    print_color("| @{cf}Cyan       @|| @!@{cf}Bold Cyan", file=file)
    print_color("| @{wf}White      @|| @!@{wf}Bold White", file=file)
