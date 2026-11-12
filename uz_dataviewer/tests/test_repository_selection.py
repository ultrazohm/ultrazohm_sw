"""Repository setup happens after startup and gates managed acquisition."""
from types import SimpleNamespace

from uz_dataviewer.app import DataViewerApp
from uz_dataviewer.user_paths import HEADER


def test_selection_updates_paths_and_enables_connect(tmp_path, monkeypatch):
    root = tmp_path / 'ultrazohm_sw'
    header = root / HEADER
    header.parent.mkdir(parents=True)
    header.touch()
    directory = root / 'artifacts' / '_user'
    directory.mkdir(parents=True)
    mapping = directory / 'javascope_test.json'
    mapping.touch()
    monkeypatch.setattr('uz_dataviewer.live_mapping.generate_mapping', lambda root: mapping)
    monkeypatch.setattr('uz_dataviewer.settings.load_workspace_settings',
                        lambda mapping: SimpleNamespace(path=directory / 'settings.json'))
    monkeypatch.delenv('UZ_DATAVIEWER_CACHE', raising=False)
    app = DataViewerApp(use_live=True)
    calls = []
    monkeypatch.setattr(app.live.controller, 'submit', lambda op, **kwargs: calls.append(op))
    try:
        assert not app.live.repository_ready
        app.live.send('connect')
        assert not calls
        assert 'root directory' in app.live.error
        app.live.prepare_repository(root)
        assert not app.live.repository_ready
        app.live._repo_future.result(timeout=3)
        app.live.pump(app.state)
        assert app.live.repository_ready
        assert app.live.mapping == str(mapping)
        assert app.live.repo == str(root)
        assert app.live.user_directory() == directory
        assert app.log_browser.directory == root
        assert app.artifacts == directory
        assert app.state.cache_dir == str(directory / 'viewer_cache')
        assert app.live.output.startswith(str(directory / 'logs'))
        app.live.send('connect')
        assert calls == ['connect']
    finally:
        app._shutdown()


def test_attach_requires_no_repository_and_invalid_selection_can_retry(tmp_path, monkeypatch):
    app = DataViewerApp(use_live=True)
    calls = []
    monkeypatch.setattr(app.live.controller, 'submit', lambda op, **kwargs: calls.append(op))
    try:
        app.live.prepare_repository(tmp_path)
        import pytest
        with pytest.raises(ValueError):
            app.live._repo_future.result(timeout=3)
        app.live.pump(app.state)
        assert 'header not found' in app.live.repo_error
        assert not app.live.repository_ready
        assert app.live._repo_future is None
        app.live.send('attach', endpoint='127.0.0.1:19740')
        assert calls == ['attach']
    finally:
        app._shutdown()
