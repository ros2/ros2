import unittest

from osrf_pycommon.cli_utils import verb_pattern

called = None


class TestCliUtilsVerbPattern(unittest.TestCase):
    def test_call_prepare_arguments(self):
        global called
        cpa = verb_pattern.call_prepare_arguments

        # Try with basic, one parameter
        called = False

        def fake_prepare_arguments(parser):
            global called
            called = True
            if called:
                pass
            return parser

        r = cpa(fake_prepare_arguments, None)
        self.assertTrue(called)
        self.assertIsNone(r)

        # Try with args
        called = False

        def fake_prepare_arguments(parser, args):
            global called
            called = True
            if called:
                pass
            return parser

        r = cpa(fake_prepare_arguments, None)
        self.assertTrue(called)
        self.assertIsNone(r)

        # Try with self
        called = False

        class Foo:
            def fake_prepare_arguments(self, parser, args):
                global called
                called = True
                if called:
                    pass
                return parser

        f = Foo()
        r = cpa(f.fake_prepare_arguments, None)
        self.assertTrue(called)
        self.assertIsNone(r)

        # Try with more than needed
        called = False

        class Foo:
            def fake_prepare_arguments(self, parser, args, extra):
                global called
                called = True
                if called:
                    pass
                return parser

        f = Foo()
        with self.assertRaisesRegexp(ValueError, 'one or two parameters'):
            r = cpa(f.fake_prepare_arguments, None)

        # Try with less than needed
        called = False

        class Foo:
            def fake_prepare_arguments(self):
                global called
                called = True
                if called:
                    pass
                return 'Should not get here'

        f = Foo()
        with self.assertRaisesRegexp(ValueError, 'one or two parameters'):
            r = cpa(f.fake_prepare_arguments, None)

    def test_split_arguments_by_verb(self):
        args = ['--cmd-arg1', 'verb', '--verb-arg1', '--verb-arg2']
        expected = ('verb', ['--cmd-arg1'], ['--verb-arg1', '--verb-arg2'])
        self.assertEqual(verb_pattern.split_arguments_by_verb(args), expected)

        args = ['verb', '--verb-arg1', '--verb-arg2']
        expected = ('verb', [], ['--verb-arg1', '--verb-arg2'])
        self.assertEqual(verb_pattern.split_arguments_by_verb(args), expected)

        args = ['--cmd-arg1', 'verb']
        expected = ('verb', ['--cmd-arg1'], [])
        self.assertEqual(verb_pattern.split_arguments_by_verb(args), expected)

        args = ['verb']
        expected = ('verb', [], [])
        self.assertEqual(verb_pattern.split_arguments_by_verb(args), expected)

        args = ['--cmd-arg1']
        expected = (None, ['--cmd-arg1'], [])
        self.assertEqual(verb_pattern.split_arguments_by_verb(args), expected)
