import mock
import unittest

from osrf_pycommon.terminal_utils import is_tty


class TestTerminalUtils(unittest.TestCase):
    def test_is_tty(self):
        mock_stream = object()
        self.assertFalse(is_tty(mock_stream))
        mock_stream = mock.MagicMock()
        mock_stream.isatty = mock.MagicMock(return_value=None)
        self.assertFalse(is_tty(mock_stream))
        mock_stream.isatty = mock.MagicMock(return_value=False)
        self.assertFalse(is_tty(mock_stream))
        mock_stream.isatty = mock.MagicMock(return_value=True)
        self.assertTrue(is_tty(mock_stream))
