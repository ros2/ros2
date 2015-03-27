import unittest

from osrf_pycommon.terminal_color import ansi_re


class TestTerminalColorAnsiRe(unittest.TestCase):
    test_str = "\x1b[31mred \033[1mbold red \x1b[0mnormal \x1b[41mred bg"

    def test_split_by_ansi_escape_sequence(self):
        split_ansi = ansi_re.split_by_ansi_escape_sequence
        expected = [
            "", "\x1b[31m", "red ", "\x1b[1m", "bold red ", "\x1b[0m",
            "normal ", "\x1b[41m", "red bg"
        ]
        self.assertEqual(expected, split_ansi(self.test_str, True))
        expected = ["", "red ", "bold red ", "normal ", "red bg"]
        self.assertEqual(expected, split_ansi(self.test_str, False))

    def test_remove_ansi_escape_senquences(self):
        remove_ansi = ansi_re.remove_ansi_escape_senquences
        expected = "red bold red normal red bg"
        self.assertEqual(expected, remove_ansi(self.test_str))

    def test_remove_ansi_escape_senquences_false_positives(self):
        remove_ansi = ansi_re.remove_ansi_escape_senquences
        false_positive = "Should not match: \1xb[1234m \033[m \1xb[3Om"
        self.assertEqual(false_positive, remove_ansi(false_positive))
