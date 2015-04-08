import unittest

from osrf_pycommon.terminal_color import impl

assert impl._enabled is True


class TestTerminalColorImpl(unittest.TestCase):
    test_format_str = "@{r}red @!bold red @|normal @{rb}red bg"
    test_str = "\x1b[31mred \033[1mbold red \x1b[0mnormal \x1b[41mred bg"

    def test_ansi(self):
        ansi = impl.ansi
        self.assertEqual('\x1b[0m', ansi('reset'))
        impl.disable_ansi_color_substitution_globally()
        self.assertNotEqual('\x1b[0m', ansi('reset'))
        self.assertEqual('@|', ansi('atbar'))
        impl.enable_ansi_color_substitution_globally()
        self.assertEqual('\x1b[0m', ansi('reset'))

    def test_get_ansi_dict(self):
        get_ansi_dict = impl.get_ansi_dict
        ansi_dict = get_ansi_dict()
        self.assertNotEqual({}, ansi_dict)
        self.assertEqual('\x1b[0m', ansi_dict['reset'])
        impl.disable_ansi_color_substitution_globally()
        ansi_dict = get_ansi_dict()
        self.assertEqual('\x1b[0m', ansi_dict['reset'])
        self.assertEqual('@|', ansi_dict['atbar'])
        self.assertNotEqual({}, ansi_dict)
        impl.enable_ansi_color_substitution_globally()
        ansi_dict = get_ansi_dict()
        self.assertNotEqual({}, ansi_dict)
        self.assertEqual('\x1b[0m', ansi_dict['reset'])

    def test_enable_and_disable_ansi_color_substitution_globally(self):
        enable = impl.enable_ansi_color_substitution_globally
        disable = impl.disable_ansi_color_substitution_globally
        is_windows = impl._is_windows
        enabled = impl._enabled
        try:
            impl._is_windows = False
            impl._enabled = True
            enable()
            self.assertEqual('\x1b[0m', impl.ansi('reset'))
            self.assertEqual('\x1b[0m', impl.format_color('@|'))
            disable()
            self.assertEqual('', impl.ansi('reset'))
            self.assertEqual('', impl.format_color('@|'))
            enable()
            self.assertEqual('\x1b[0m', impl.ansi('reset'))
            self.assertEqual('\x1b[0m', impl.format_color('@|'))
        finally:
            impl._is_windows = is_windows
            impl._enabled = enabled

    def test_format_color(self):
        is_windows = impl._is_windows
        try:
            impl._is_windows = False
            format_color = impl.format_color
            self.assertEqual(self.test_str, format_color(self.test_format_str))
            sanitized_str = "|@@ Notice @{atbar}"
            self.assertEqual("|@ Notice @|", format_color(sanitized_str))
        finally:
            impl._is_windows = is_windows

    def test_sanitize(self):
        sanitize = impl.sanitize
        test_str = "Email: {email}@{org}"
        self.assertEqual("Email: {{email}}@@{{org}}", sanitize(test_str))
        test_str = "|@ Notice @|"
        self.assertEqual("|@@ Notice @{atbar}", sanitize(test_str))
