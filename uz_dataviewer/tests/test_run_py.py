"""run.py is the documented source-checkout launcher; it must only start the viewer."""
import runpy
from pathlib import Path

import uz_dataviewer.app as app


def test_run_py_starts_the_viewer(monkeypatch):
    calls = []
    monkeypatch.setattr(app, 'main', lambda: calls.append(True) or 0)
    try:
        runpy.run_path(str(Path(__file__).parents[1] / 'run.py'), run_name='__main__')
    except SystemExit as exc:
        assert exc.code == 0
    assert calls == [True]
    source = (Path(__file__).parents[1] / 'run.py').read_text()
    assert 'ultrazohm' not in source and 'enable' not in source
