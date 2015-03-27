import flake8.engine
import os


def test_flake8():
    """Test source code for pyFlakes and PEP8 conformance"""
    flake8style = flake8.engine.StyleGuide()
    report = flake8style.options.report
    report.start()
    this_dir = os.path.dirname(os.path.abspath(__file__))
    flake8style.input_dir(os.path.join(this_dir, '..', 'osrf_pycommon'))
    report.stop()
    assert report.total_errors == 0, \
        ("Found '{0}' code style errors (and warnings)."
         .format(report.total_errors))
