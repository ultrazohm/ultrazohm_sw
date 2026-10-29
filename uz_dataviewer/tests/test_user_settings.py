"""Standalone storage, runtime profiles, and remembered XSCT launchers."""
from uz_dataviewer import settings as runtime_settings
import json
import os
from pathlib import Path
import sys

import pytest

from uz_dataviewer import flashing
from uz_dataviewer.user_paths import data_directory


@pytest.mark.parametrize('explicit', [False, True])
@pytest.mark.parametrize('frozen', [False, True])
def test_mode_data_is_under_repository_artifacts(tmp_path, monkeypatch, explicit, frozen):
    header = tmp_path/'vitis/software/Baremetal/src/include/javascope.h'
    header.parent.mkdir(parents=True)
    header.touch()
    monkeypatch.setattr(sys, 'frozen', frozen, raising=False)
    monkeypatch.chdir(header.parent)
    name = '_user_standalone' if frozen else '_user'
    assert data_directory(tmp_path if explicit else None) == tmp_path/'artifacts'/name
    assert not (tmp_path/'_user').exists()


def test_windows_console_has_no_cli_handler_and_guides_users_to_python(monkeypatch):
    from uz_dataviewer.app import DataViewerApp
    monkeypatch.setattr('uz_dataviewer.console.CLI_SUPPORTED', False)
    app = DataViewerApp(use_live=True)
    try:
        console = app.state.console
        assert console.cli_handler is None
        assert not console.cli_supported
        console._input = 'uz status'
        console._submit(app.state)
        assert 'unavailable on Windows' in console.as_text()
        assert 'Python panel' in console.as_text()
        assert app._cli_console is None
        console._input = 'set_grid(2, 2)'
        console._submit(app.state)
        assert app.state.cell_count == 4
    finally:
        app._shutdown()


def test_modes_isolate_data_in_the_same_workspace(tmp_path, monkeypatch):
    executable = tmp_path/'distribution'/'uz_dataviewer.exe'
    monkeypatch.setattr(sys, 'frozen', True, raising=False)
    monkeypatch.setattr(sys, 'executable', str(executable))
    workspace = tmp_path/'workspace'
    standalone = data_directory(workspace)
    assert standalone == workspace/'artifacts'/'_user_standalone'
    (standalone/'settings.json').write_text('standalone preferences')
    monkeypatch.setattr(sys, 'frozen', False)
    developer = data_directory(workspace)
    assert developer == workspace/'artifacts'/'_user'
    assert not (developer/'settings.json').exists()
    assert (standalone/'settings.json').read_text() == 'standalone preferences'
    assert not (executable.parent/'artifacts').exists()


def test_normal_connect_filters_bundled_defaults_and_loads_editable_settings(tmp_path, monkeypatch):
    path = tmp_path/'mapping.json'
    path.write_text(json.dumps({'channels': 20, 'observables': {'JSO_lifecheck': 3}}))
    monkeypatch.setattr(runtime_settings, 'default_profile', lambda: {
        'name': 'standard', 'sample_period_us': 100,
        'initial_channels': {'3': 'JSO_lifecheck', '4': 'JSO_theta_mech'}})
    settings_path, removed = runtime_settings.prepare_profile(path)
    assert removed == []  # Missing firmware names were filtered when seeding defaults.
    settings = json.loads(settings_path.read_text())
    assert settings['initial_channels'] == {'3': 'JSO_lifecheck'}
    settings['sample_period_us'] = 50
    settings['initial_channels'] = {}
    settings_path.write_text(json.dumps(settings))
    monkeypatch.setattr(runtime_settings, 'default_profile', lambda: pytest.fail('Must use saved settings'))
    same_path, removed = runtime_settings.prepare_profile(path)
    assert same_path == settings_path
    assert not removed
    assert json.loads(same_path.read_text()) == settings


def test_invalid_settings_fail_without_overwriting(tmp_path):
    path = tmp_path/'mapping.json'
    path.write_text('{}')
    settings = tmp_path/'settings.json'
    settings.write_text('{bad json')
    with pytest.raises(ValueError):
        runtime_settings.prepare_profile(path)
    assert settings.read_text() == '{bad json'


def test_xsct_selection_is_remembered_and_restored_for_child_processes(tmp_path, monkeypatch):
    tool = tmp_path/'Vitis with spaces'/'bin'/('xsct.cmd' if os.name == 'nt' else 'xsct')
    tool.parent.mkdir(parents=True)
    tool.touch()
    tool.chmod(0o755)
    monkeypatch.setenv('PATH', '')
    flashing.select_xsct(tool, tmp_path)
    assert flashing.xsct_available()
    assert json.loads((tmp_path/'artifacts'/'_user'/'tools.json').read_text()) == {'xsct': str(tool)}
    monkeypatch.setenv('PATH', '')
    flashing.restore_xsct(tmp_path)
    assert Path(os.environ['PATH'].split(os.pathsep)[0]) == tool.parent
    assert flashing.xsct_available()
    with pytest.raises(ValueError, match='XSCT launcher'):
        flashing.select_xsct(tool.with_name('vitis.exe'), tmp_path)
    tool.unlink()
    with pytest.raises(ValueError, match='no longer exists'):
        flashing.restore_xsct(tmp_path)


def test_service_launch_passes_filtered_settings_profile(tmp_path, monkeypatch):
    from types import SimpleNamespace
    from uz_dataviewer.live import LiveController
    mapping = tmp_path/'mapping.json'
    mapping.write_text(json.dumps({'channels': 20, 'observables': {'JSO_lifecheck': 3}}))
    monkeypatch.setattr(runtime_settings, 'default_profile', lambda: {
        'name': 'standard', 'sample_period_us': 100,
        'initial_channels': {'3': 'JSO_lifecheck', '4': 'JSO_theta_mech'}})
    calls = []
    def launch(args, **kwargs):
        calls.append(args)
        return SimpleNamespace(poll=lambda: None)
    monkeypatch.setattr('uz_dataviewer.live.subprocess.Popen', launch)
    controller = LiveController()
    controller.client = SimpleNamespace(status=lambda: {})
    controller._start_service(tmp_path/'logs'/'session', mapping)
    args = calls[0]
    settings = Path(args[args.index('--profile') + 1])
    assert settings == tmp_path/'logs'/'session.profile.json'
    assert json.loads(settings.read_text())['initial_channels'] == {'3': 'JSO_lifecheck'}
    assert controller.messages.empty()


def test_frozen_app_retains_selected_firmware_workspace(tmp_path, monkeypatch):
    from uz_dataviewer.app import DataViewerApp
    executable = tmp_path/'distribution'/'uz_dataviewer.exe'
    firmware = tmp_path/'separate firmware checkout'
    monkeypatch.setattr(sys, 'frozen', True, raising=False)
    monkeypatch.setattr(sys, 'executable', str(executable))
    user_dir = firmware/'artifacts'/'_user_standalone'
    app = DataViewerApp(use_live=True, live_mapping=str(user_dir/'mapping.json'),
                        live_repo=str(firmware))
    try:
        assert app.live.repo == str(firmware)
        assert app.artifacts == user_dir
        assert Path(app.live.output).parent == user_dir/'logs'
    finally:
        app._shutdown()


def test_initialize_and_connect_preserve_existing_preferences(tmp_path, monkeypatch):
    mapping = tmp_path/'mapping.json'
    mapping.write_text(json.dumps({'channels': 20, 'observables': {'JSO_lifecheck': 3}}))
    settings = tmp_path/'settings.json'
    original = '{"schema_version":1,"name":"custom","sample_period_us":50,"initial_channels":{"3":"JSO_lifecheck","4":"JSO_theta_mech"}}\n'
    settings.write_text(original)
    tools = tmp_path/'tools.json'
    tools.write_text('{"xsct":null,"custom":"keep me"}\n')
    before = {path: (path.read_bytes(), path.stat().st_mtime_ns) for path in (settings, tools)}
    monkeypatch.setattr(runtime_settings, 'default_profile', lambda: pytest.fail('Must preserve existing settings'))
    assert runtime_settings.initialize_user_settings(mapping) == settings
    effective, removed = runtime_settings.prepare_profile(mapping, tmp_path/'session.profile.json')
    assert removed == ['JSO_theta_mech']
    assert json.loads(effective.read_text())['initial_channels'] == {'3': 'JSO_lifecheck'}
    assert {path: (path.read_bytes(), path.stat().st_mtime_ns) for path in (settings, tools)} == before
    assert (tmp_path/'logs').is_dir()
    monkeypatch.setattr('uz_dataviewer.user_paths.data_directory', lambda repo=None: tmp_path)
    flashing.restore_xsct(tmp_path)  # No XSCT selection is required in a fresh workspace.


@pytest.mark.parametrize('frozen', [False, True])
def test_workspace_startup_initializes_missing_preferences_once(tmp_path, monkeypatch, frozen):
    from uz_dataviewer import app, live_mapping
    monkeypatch.setattr(sys, 'frozen', frozen, raising=False)
    monkeypatch.setattr(app.runtime, 'IS_WEB', False)
    user_dir = data_directory(tmp_path)
    mapping = user_dir/'mapping.json'
    mapping.write_text(json.dumps({'channels': 20, 'observables': {'JSO_lifecheck': 3}}))
    monkeypatch.setattr(live_mapping, 'generate_mapping', lambda repo: mapping)
    monkeypatch.setattr(runtime_settings, 'default_profile', lambda: {
        'name': 'standard', 'sample_period_us': 100,
        'initial_channels': {'3': 'JSO_lifecheck', '4': 'JSO_theta_mech'}})
    class Viewer:
        def __init__(self, **kwargs):
            assert kwargs['live_repo'] == str(tmp_path)
            assert (user_dir/'settings.json').is_file()
            assert (user_dir/'tools.json').is_file()
            assert (user_dir/'logs').is_dir()
        def run(self): pass
    monkeypatch.setattr(app, 'DataViewerApp', Viewer)
    args = ['--use-live', '--live-repo', str(tmp_path)]
    assert app.main(args) == 0
    saved = user_dir/'settings.json'
    original = '{"schema_version":1,"name":"edited","sample_period_us":75,"initial_channels":{}}\n'
    saved.write_text(original)
    monkeypatch.setattr(runtime_settings, 'default_profile', lambda: pytest.fail('Must not reapply defaults'))
    assert app.main(args) == 0
    assert saved.read_text() == original


@pytest.mark.parametrize('value', [[], None, {'xsct': 123}])
def test_malformed_tool_preferences_report_a_validation_error(tmp_path, monkeypatch, value):
    directory = data_directory(tmp_path)
    path = directory/'tools.json'
    path.write_text(json.dumps(value))
    with pytest.raises(ValueError, match='Invalid tool preferences'):
        flashing.restore_xsct(tmp_path)
    assert json.loads(path.read_text()) == value


@pytest.mark.parametrize('change', [
    {'schema_version': 2}, {'sample_period_us': 0}, {'sample_period_us': True},
    {'initial_channels': []}, {'initial_channels': {'bad-channel': 'JSO_lifecheck'}},
    {'unexpected': 42}, {'name': None},
])
def test_invalid_runtime_preferences_are_rejected_without_rewriting(tmp_path, change):
    mapping = tmp_path/'mapping.json'
    mapping.write_text('{}')
    value = {'schema_version': 1, 'name': 'user', 'sample_period_us': 100, 'initial_channels': {}}
    value.update(change)
    path = tmp_path/'settings.json'
    original = json.dumps(value)
    path.write_text(original)
    with pytest.raises(ValueError, match='Invalid runtime settings'):
        runtime_settings.prepare_profile(mapping)
    assert path.read_text() == original


def test_json_publication_preserves_existing_file_on_failure(tmp_path, monkeypatch):
    from uz_dataviewer import user_paths
    path = tmp_path/'settings.json'
    path.write_text('original preferences')
    user_paths.write_json(path, {'new': 'defaults'}, overwrite=False)
    assert path.read_text() == 'original preferences'
    def fail(*args): raise OSError('cannot replace')
    monkeypatch.setattr(user_paths.os, 'replace', fail)
    with pytest.raises(OSError, match='cannot replace'):
        user_paths.write_json(path, {'edited': True})
    assert path.read_text() == 'original preferences'
    assert list(tmp_path.iterdir()) == [path]


def test_external_mapping_keeps_preferences_in_selected_workspace(tmp_path, monkeypatch):
    external = tmp_path/'external'
    external.mkdir()
    mapping = external/'mapping.json'
    mapping.write_text(json.dumps({'channels': 20, 'observables': {'JSO_lifecheck': 3}}))
    user_dir = data_directory(tmp_path/'workspace')
    monkeypatch.setattr(runtime_settings, 'default_profile', lambda: {
        'name': 'standard', 'sample_period_us': 100, 'initial_channels': {'3': 'JSO_lifecheck'}})
    effective, _ = runtime_settings.prepare_profile(mapping, user_directory=user_dir)
    assert effective == user_dir/'settings.json'
    assert list(external.iterdir()) == [mapping]
    assert (user_dir/'tools.json').is_file()


def test_default_profile_worker_failure_has_actionable_error(monkeypatch):
    import subprocess
    def fail(*args, **kwargs):
        raise subprocess.CalledProcessError(1, ['profile'], stderr='native profile error')
    monkeypatch.setattr(runtime_settings.subprocess, 'run', fail)
    with pytest.raises(RuntimeError, match='native profile error'):
        runtime_settings.default_profile()
