import os
import sys
import unittest

try:
    from .impl_aep_trollius import run
    from .impl_aep_trollius import loop
    print("Using Trollius")
except ImportError as exc:
    if 'PYTHONASYNCIODEBUG' in os.environ:
        import traceback
        traceback.print_exc()
    from .impl_aep_asyncio import run
    from .impl_aep_asyncio import loop
    print("Using asyncio")

this_dir = os.path.dirname(os.path.abspath(__file__))

test_script = os.path.join(
    this_dir,
    'fixtures',
    'execute_process',
    'stdout_stderr_ordering.py')
python = sys.executable


class TestProcessUtilsAsyncExecuteProcess(unittest.TestCase):
    def test_async_execute_process_no_emulation_shell_false_combined(self):
        stdout, stderr, retcode = loop.run_until_complete(run(
            [python, test_script]))
        stdout, stderr = stdout.decode(), stderr.decode()
        self.assertIn('out 1', stdout)
        self.assertIn('err 1', stdout)
        self.assertIn('out 2', stdout)
        self.assertEqual('', stderr)
        self.assertEqual(0, retcode)

    def test_async_execute_process_no_emulation_shell_true_combined(self):
        stdout, stderr, retcode = loop.run_until_complete(run(
            [python, test_script], shell=True))
        stdout, stderr = stdout.decode(), stderr.decode()
        self.assertIn('out 1', stdout)
        self.assertIn('err 1', stdout)
        self.assertIn('out 2', stdout)
        self.assertEqual('', stderr)
        self.assertEqual(0, retcode)

    def test_async_execute_process_no_emulation_shell_false(self):
        stdout, stderr, retcode = loop.run_until_complete(run(
            [python, test_script], stderr_to_stdout=False))
        stdout, stderr = stdout.decode(), stderr.decode()
        self.assertIn('out 1', stdout)
        self.assertIn('err 1', stderr)
        self.assertIn('out 2', stdout)
        self.assertEqual(0, retcode)

    def test_async_execute_process_no_emulation_shell_true(self):
        stdout, stderr, retcode = loop.run_until_complete(run(
            [python, test_script], stderr_to_stdout=False, shell=True))
        stdout, stderr = stdout.decode(), stderr.decode()
        self.assertIn('out 1', stdout)
        self.assertIn('err 1', stderr)
        self.assertIn('out 2', stdout)
        self.assertEqual(0, retcode)

    def test_async_execute_process_with_emulation_shell_false_combined(self):
        stdout, stderr, retcode = loop.run_until_complete(run(
            [python, test_script], emulate_tty=True))
        stdout, stderr = stdout.decode(), stderr.decode()
        self.assertIn('out 1', stdout)
        self.assertIn('err 1', stdout)
        self.assertIn('out 2', stdout)
        self.assertEqual('', stderr)
        self.assertEqual(0, retcode)

    def test_async_execute_process_with_emulation_shell_true_combined(self):
        stdout, stderr, retcode = loop.run_until_complete(run(
            [python, test_script], emulate_tty=True, shell=True))
        stdout, stderr = stdout.decode(), stderr.decode()
        self.assertIn('out 1', stdout)
        self.assertIn('err 1', stdout)
        self.assertIn('out 2', stdout)
        self.assertEqual('', stderr)
        self.assertEqual(0, retcode)

    def test_async_execute_process_with_emulation_shell_false(self):
        stdout, stderr, retcode = loop.run_until_complete(run(
            [python, test_script], emulate_tty=True, stderr_to_stdout=False))
        stdout, stderr = stdout.decode(), stderr.decode()
        self.assertIn('out 1', stdout)
        self.assertIn('err 1', stderr)
        self.assertIn('out 2', stdout)
        self.assertEqual(0, retcode)

    def test_async_execute_process_with_emulation_shell_true(self):
        stdout, stderr, retcode = loop.run_until_complete(run(
            [python, test_script], emulate_tty=True, stderr_to_stdout=False,
            shell=True))
        stdout, stderr = stdout.decode(), stderr.decode()
        self.assertIn('out 1', stdout)
        self.assertIn('err 1', stderr)
        self.assertIn('out 2', stdout)
        self.assertEqual(0, retcode)
