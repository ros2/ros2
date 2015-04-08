from __future__ import unicode_literals

import os
import unittest

from osrf_pycommon.process_utils import impl

this_dir = os.path.dirname(os.path.abspath(__file__))


class TestProcessUtilsImpl(unittest.TestCase):
    def test_which(self):
        which = impl.which
        j = os.path.join
        prefix = j(this_dir, 'fixtures', 'impl_which')
        paths = os.pathsep.join([
            j(prefix, 'usr', 'local', 'bin'),
            j(prefix, 'usr', 'bin'),
            j(prefix, 'bin'),
        ])
        # bin_only exists +x in bin only
        expected = j(prefix, 'bin', 'bin_only.exe')
        self.assertEqual(expected, which('bin_only.exe', path=paths))
        self.assertEqual(expected, which(expected, path=paths))
        # exc1 exists +x in bin and usr/bin
        expected = j(prefix, 'usr', 'bin', 'exc1.exe')
        self.assertEqual(expected, which('exc1.exe', path=paths))
        self.assertEqual(expected, which(expected, path=paths))
        # exc2 exists +x in bin and usr/bin, but -x in usr/local/bin
        expected = j(prefix, 'usr', 'bin', 'exc2.exe')
        self.assertEqual(expected, which('exc2.exe', path=paths))
        self.assertEqual(expected, which(expected, path=paths))
        # Same as above, with PATH
        orig_path = os.environ['PATH']
        try:
            os.environ['PATH'] = paths
            # bin_only exists +x in bin only
            expected = j(prefix, 'bin', 'bin_only.exe')
            self.assertEqual(expected, which('bin_only.exe'))
            self.assertEqual(expected, which(expected))
            # exc1 exists +x in bin and usr/bin
            expected = j(prefix, 'usr', 'bin', 'exc1.exe')
            self.assertEqual(expected, which('exc1.exe'))
            self.assertEqual(expected, which(expected))
            # exc2 exists +x in bin and usr/bin, but -x in usr/local/bin
            expected = j(prefix, 'usr', 'bin', 'exc2.exe')
            self.assertEqual(expected, which('exc2.exe'))
            self.assertEqual(expected, which(expected))
        finally:
            os.environ['PATH'] = orig_path
        which(str("exc1.exe"), path=paths)  # Make sure unicode/str works
