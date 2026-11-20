"""Workspace storage, runtime profiles, and remembered XSCT launchers."""

import json
import os
import sys
from pathlib import Path

import pytest

from ultrazohm_dataviewer import flashing
from ultrazohm_dataviewer import settings as runtime_settings
from ultrazohm_dataviewer.user_paths import data_directory


def contract(observables):
    from ultrazohm_cli.configuration import channel_mapping

    value = channel_mapping(Path(__file__).resolve().parents[2])
    value["observables"] = observables
    return value


@pytest.mark.parametrize("explicit", [False, True])
@pytest.mark.parametrize("frozen", [False, True])
def test_data_is_under_repository_artifacts_in_both_modes(
    tmp_path, monkeypatch, explicit, frozen
):
    header = tmp_path / "vitis/software/Baremetal/src/include/javascope.h"
    header.parent.mkdir(parents=True)
    header.touch()
    monkeypatch.setattr(sys, "frozen", frozen, raising=False)
    monkeypatch.chdir(header.parent)
    assert (
        data_directory(tmp_path if explicit else None)
        == tmp_path / "artifacts" / "_user"
    )
    assert (tmp_path / "artifacts" / ".gitignore").read_text() == "*\n!*/\n!*.json\n"


def test_outside_a_checkout_data_goes_to_the_user_directory_not_the_working_directory(
    tmp_path, monkeypatch
):
    from ultrazohm_dataviewer.user_paths import user_data_directory

    downloads = tmp_path / "Downloads"
    downloads.mkdir()
    monkeypatch.chdir(downloads)
    directory = data_directory()
    assert directory == user_data_directory() and directory.is_dir()
    assert tmp_path in directory.parents  # The test isolates the per-user location.
    assert list(downloads.iterdir()) == []


def test_application_log_is_independent_of_live_connectivity():
    from ultrazohm_dataviewer.app import DataViewerApp

    app = DataViewerApp(use_live=False)
    try:
        app.state.console.info("Offline viewer ready")
        assert "Offline viewer ready" in app.state.console.as_text()
        assert not hasattr(app.state.console, "_submit")
    finally:
        app._shutdown()


def test_bundle_and_source_share_the_workspace_data(tmp_path, monkeypatch):
    executable = tmp_path / "distribution" / "ultrazohm_dataviewer.exe"
    monkeypatch.setattr(sys, "frozen", True, raising=False)
    monkeypatch.setattr(sys, "executable", str(executable))
    workspace = tmp_path / "workspace"
    bundle = data_directory(workspace)
    (bundle / "settings.json").write_text("preferences")
    monkeypatch.setattr(sys, "frozen", False)
    assert data_directory(workspace) == bundle == workspace / "artifacts" / "_user"
    assert (bundle / "settings.json").read_text() == "preferences"
    assert not (executable.parent / "artifacts").exists()


def test_normal_connect_filters_bundled_defaults_and_loads_editable_settings(
    tmp_path, monkeypatch
):
    path = tmp_path / "mapping.json"
    path.write_text(json.dumps(contract({"JSO_lifecheck": 3})))
    monkeypatch.setattr(
        runtime_settings,
        "default_profile",
        lambda: {
            "schema_version": 1,
            "name": "standard",
            "sample_period_us": 100,
            "initial_channels": {"3": "JSO_lifecheck", "4": "JSO_theta_mech"},
        },
    )
    settings_path, removed = runtime_settings.prepare_profile(path)
    assert removed == []  # Missing firmware names were filtered when seeding defaults.
    settings = json.loads(settings_path.read_text())
    assert settings["initial_channels"] == {"3": "JSO_lifecheck"}
    settings["sample_period_us"] = 50
    settings["initial_channels"] = {}
    settings_path.write_text(json.dumps(settings))
    monkeypatch.setattr(
        runtime_settings,
        "default_profile",
        lambda: pytest.fail("Must use saved settings"),
    )
    same_path, removed = runtime_settings.prepare_profile(path)
    assert same_path == settings_path
    assert not removed
    assert json.loads(same_path.read_text()) == settings


def test_invalid_settings_fail_without_overwriting(tmp_path):
    path = tmp_path / "mapping.json"
    path.write_text("{}")
    settings = tmp_path / "settings.json"
    settings.write_text("{bad json")
    with pytest.raises(ValueError):
        runtime_settings.prepare_profile(path)
    assert settings.read_text() == "{bad json"


def test_xsct_selection_is_remembered_and_restored_for_child_processes(
    tmp_path, monkeypatch
):
    tool = (
        tmp_path
        / "Vitis with spaces"
        / "bin"
        / ("xsct.cmd" if os.name == "nt" else "xsct")
    )
    tool.parent.mkdir(parents=True)
    tool.touch()
    tool.chmod(0o755)
    monkeypatch.setenv("PATH", "")
    flashing.select_xsct(tool, tmp_path)
    assert flashing.xsct_available()
    assert json.loads(
        (tmp_path / "artifacts" / "_user" / "tools.json").read_text()
    ) == {"xsct": str(tool)}
    monkeypatch.setenv("PATH", "")
    flashing.restore_xsct(tmp_path)
    assert Path(os.environ["PATH"].split(os.pathsep)[0]) == tool.parent
    assert flashing.xsct_available()
    with pytest.raises(ValueError, match="XSCT launcher"):
        flashing.select_xsct(tool.with_name("vitis.exe"), tmp_path)
    tool.unlink()
    with pytest.raises(ValueError, match="no longer exists"):
        flashing.restore_xsct(tmp_path)


def test_service_launch_passes_filtered_settings_profile(tmp_path, monkeypatch):
    from types import SimpleNamespace

    from ultrazohm_dataviewer.live import LiveController

    mapping = tmp_path / "mapping.json"
    mapping.write_text(json.dumps(contract({"JSO_lifecheck": 3})))
    monkeypatch.setattr(
        runtime_settings,
        "default_profile",
        lambda: {
            "schema_version": 1,
            "name": "standard",
            "sample_period_us": 100,
            "initial_channels": {"3": "JSO_lifecheck", "4": "JSO_theta_mech"},
        },
    )
    calls = []

    def launch(args, **kwargs):
        calls.append(args)
        return SimpleNamespace(poll=lambda: None)

    monkeypatch.setattr("ultrazohm_dataviewer.live.subprocess.Popen", launch)
    controller = LiveController()
    controller.client = SimpleNamespace(status=lambda: {"service_id": "test-service"})
    controller._start_service(tmp_path / "logs" / "session", mapping)
    args = calls[0]
    settings = Path(args[args.index("--profile") + 1])
    assert settings == tmp_path / "settings.json"
    assert json.loads(settings.read_text())["initial_channels"] == {
        "3": "JSO_lifecheck"
    }
    assert controller.messages.empty()


def test_frozen_app_retains_selected_firmware_workspace(tmp_path, monkeypatch):
    from ultrazohm_dataviewer.app import DataViewerApp

    executable = tmp_path / "distribution" / "ultrazohm_dataviewer.exe"
    firmware = tmp_path / "separate firmware checkout"
    monkeypatch.setattr(sys, "frozen", True, raising=False)
    monkeypatch.setattr(sys, "executable", str(executable))
    user_dir = firmware / "artifacts" / "_user"
    app = DataViewerApp(
        use_live=True,
        live_mapping=str(user_dir / "mapping.json"),
        live_repo=str(firmware),
    )
    try:
        assert app.live.repo == str(firmware)
        assert app.artifacts == user_dir
        assert Path(app.live.output).parent == user_dir / "logs"
    finally:
        app._shutdown()


def test_initialize_and_connect_preserve_existing_preferences(tmp_path, monkeypatch):
    mapping = tmp_path / "mapping.json"
    mapping.write_text(json.dumps(contract({"JSO_lifecheck": 3})))
    settings = tmp_path / "settings.json"
    original = '{"schema_version":1,"name":"custom","sample_period_us":50,"initial_channels":{"3":"JSO_lifecheck","4":"JSO_theta_mech"}}\n'
    settings.write_text(original)
    tools = tmp_path / "tools.json"
    tools.write_text('{"xsct":null,"custom":"keep me"}\n')
    before = {
        path: (path.read_bytes(), path.stat().st_mtime_ns) for path in (settings, tools)
    }
    monkeypatch.setattr(
        runtime_settings,
        "default_profile",
        lambda: pytest.fail("Must preserve existing settings"),
    )
    assert runtime_settings.load_workspace_settings(mapping).path == settings
    effective, removed = runtime_settings.prepare_profile(
        mapping, tmp_path / "session.profile.json"
    )
    assert removed == ["JSO_theta_mech"]
    assert json.loads(effective.read_text())["initial_channels"] == {
        "3": "JSO_lifecheck"
    }
    assert {
        path: (path.read_bytes(), path.stat().st_mtime_ns) for path in (settings, tools)
    } == before
    assert (tmp_path / "logs").is_dir()
    monkeypatch.setattr(
        "ultrazohm_dataviewer.user_paths.data_directory", lambda repo=None: tmp_path
    )
    flashing.restore_xsct(
        tmp_path
    )  # No XSCT selection is required in a fresh workspace.


@pytest.mark.parametrize("frozen", [False, True])
def test_workspace_startup_initializes_missing_preferences_once(
    tmp_path, monkeypatch, frozen
):
    from ultrazohm_dataviewer import app, live_mapping

    monkeypatch.setattr(sys, "frozen", frozen, raising=False)
    user_dir = data_directory(tmp_path)
    mapping = user_dir / "mapping.json"
    mapping.write_text(json.dumps(contract({"JSO_lifecheck": 3})))
    monkeypatch.setattr(
        live_mapping, "read_mapping", lambda repo: json.loads(mapping.read_text())
    )
    monkeypatch.setattr(
        runtime_settings,
        "default_profile",
        lambda repo=None: {
            "schema_version": 1,
            "name": "standard",
            "sample_period_us": 100,
            "initial_channels": {"3": "JSO_lifecheck"},
        },
    )
    header = tmp_path / live_mapping.HEADER
    header.parent.mkdir(parents=True)
    header.touch()

    class Viewer(app.DataViewerApp):
        def run(self):
            try:
                self.live._repo_future.result(timeout=3)
                self.live.pump(self.state)
                assert self.live.repository_ready
                assert (user_dir / "settings.json").is_file()
                assert (user_dir / "tools.json").is_file()
                assert (user_dir / "logs").is_dir()
            finally:
                self._shutdown()

    monkeypatch.setattr(app, "DataViewerApp", Viewer)
    monkeypatch.setattr(
        "importlib.util.find_spec",
        lambda name: object() if name == "ultrazohm_cli" else None,
    )
    args = ["--endpoint", "127.0.0.1:0", "--live-repo", str(tmp_path)]
    assert app.main(args) == 0
    saved = user_dir / "settings.json"
    original = '{"schema_version":1,"name":"edited","sample_period_us":75,"initial_channels":{}}\n'
    saved.write_text(original)
    monkeypatch.setattr(
        runtime_settings,
        "default_profile",
        lambda repo=None: pytest.fail("Must not reapply defaults"),
    )
    assert app.main(args) == 0
    assert saved.read_text() == original


@pytest.mark.parametrize("value", [[], None, {"xsct": 123}])
def test_malformed_tool_preferences_report_a_validation_error(
    tmp_path, monkeypatch, value
):
    directory = data_directory(tmp_path)
    path = directory / "tools.json"
    path.write_text(json.dumps(value))
    with pytest.raises(ValueError, match="Invalid tool preferences"):
        flashing.restore_xsct(tmp_path)
    assert json.loads(path.read_text()) == value


@pytest.mark.parametrize(
    "change",
    [
        {"schema_version": 2},
        {"sample_period_us": 0},
        {"sample_period_us": True},
        {"initial_channels": []},
        {"initial_channels": {"bad-channel": "JSO_lifecheck"}},
        {"unexpected": 42},
        {"name": None},
    ],
)
def test_invalid_runtime_preferences_are_rejected_without_rewriting(tmp_path, change):
    mapping = tmp_path / "mapping.json"
    mapping.write_text(json.dumps({"channels": 20, "observables": {}}))
    value = {
        "schema_version": 1,
        "name": "user",
        "sample_period_us": 100,
        "initial_channels": {},
    }
    value.update(change)
    path = tmp_path / "settings.json"
    original = json.dumps(value)
    path.write_text(original)
    with pytest.raises(ValueError, match="Invalid runtime settings"):
        runtime_settings.prepare_profile(mapping)
    assert path.read_text() == original


def test_json_publication_preserves_existing_file_on_failure(tmp_path, monkeypatch):
    from ultrazohm_dataviewer import user_paths

    path = tmp_path / "settings.json"
    path.write_text("original preferences")
    user_paths.write_json(path, {"new": "defaults"}, overwrite=False)
    assert path.read_text() == "original preferences"

    def fail(*args):
        raise OSError("cannot replace")

    monkeypatch.setattr(user_paths.os, "replace", fail)
    with pytest.raises(OSError, match="cannot replace"):
        user_paths.write_json(path, {"edited": True})
    assert path.read_text() == "original preferences"
    assert list(tmp_path.iterdir()) == [path]


def test_failed_settings_seed_leaves_no_partial_destination(tmp_path, monkeypatch):
    from ultrazohm_dataviewer import user_paths

    path = tmp_path / "settings.json"
    fdopen = user_paths.os.fdopen

    class FailingWriter:
        def __init__(self, *args, **kwargs):
            self.output = fdopen(*args, **kwargs)

        def __enter__(self):
            return self

        def __exit__(self, *args):
            self.output.close()

        def write(self, data):
            self.output.write(data[:3])
            raise OSError("disk full")

    with monkeypatch.context() as patch:
        patch.setattr(user_paths.os, "fdopen", FailingWriter)
        with pytest.raises(OSError, match="disk full"):
            user_paths.write_json(path, {"schema_version": 1}, overwrite=False)
    assert not path.exists()
    assert list(tmp_path.iterdir()) == []
    user_paths.write_json(path, {"schema_version": 1}, overwrite=False)
    assert json.loads(path.read_text()) == {"schema_version": 1}


@pytest.mark.parametrize("windows", [False, True])
@pytest.mark.parametrize("concurrent_writer", [False, True])
def test_settings_seed_publishes_complete_json_without_replacing_winner(
    tmp_path, monkeypatch, windows, concurrent_writer
):
    from ultrazohm_dataviewer import user_paths

    path = tmp_path / "settings.json"
    defaults, winner = {"schema_version": 1}, {"user": "preferences"}
    link = user_paths.os.link

    def publish(temporary, destination):
        assert not path.exists()  # No reader can observe an unfinished seed.
        assert json.loads(Path(temporary).read_text()) == defaults
        if concurrent_writer:
            path.write_text(json.dumps(winner))
        # link has the same no-replace semantics as rename on Windows.
        link(temporary, destination)

    if windows:
        monkeypatch.setattr(user_paths.sys, "platform", "win32")
        monkeypatch.setattr(user_paths.os, "rename", publish)

        def no_links(*args):
            raise OSError("hard links unsupported")

        monkeypatch.setattr(user_paths.os, "link", no_links)
    else:
        monkeypatch.setattr(user_paths.sys, "platform", "linux")
        monkeypatch.setattr(user_paths.os, "link", publish)
    user_paths.write_json(path, defaults, overwrite=False)
    assert json.loads(path.read_text()) == (winner if concurrent_writer else defaults)
    assert list(tmp_path.iterdir()) == [path]


def test_external_mapping_keeps_preferences_in_selected_workspace(
    tmp_path, monkeypatch
):
    external = tmp_path / "external"
    external.mkdir()
    mapping = external / "mapping.json"
    mapping.write_text(json.dumps(contract({"JSO_lifecheck": 3})))
    user_dir = data_directory(tmp_path / "workspace")
    monkeypatch.setattr(
        runtime_settings,
        "default_profile",
        lambda: {
            "schema_version": 1,
            "name": "standard",
            "sample_period_us": 100,
            "initial_channels": {"3": "JSO_lifecheck"},
        },
    )
    effective, _ = runtime_settings.prepare_profile(mapping, user_directory=user_dir)
    assert effective == user_dir / "settings.json"
    assert list(external.iterdir()) == [mapping]
    assert (user_dir / "tools.json").is_file()


def test_default_profile_library_failure_has_actionable_error(monkeypatch):
    import ultrazohm_cli.configuration as configuration

    def fail(*args, **kwargs):
        raise RuntimeError("native profile error")

    monkeypatch.setattr(configuration, "default_profile", fail)
    with pytest.raises(RuntimeError, match="native profile error"):
        runtime_settings.default_profile()


def test_malformed_mapping_is_rejected_clearly(tmp_path):
    mapping = tmp_path / "mapping.json"
    mapping.write_text("{}")
    with pytest.raises(ValueError, match="Invalid channel mapping"):
        runtime_settings.load_workspace_settings(mapping)


@pytest.mark.parametrize("saved", [False, True])
def test_repository_service_passes_repo_and_preserves_explicit_profile(
    tmp_path, monkeypatch, saved
):
    from types import SimpleNamespace

    from ultrazohm_dataviewer.live import LiveController

    directory = data_directory(tmp_path)
    settings = directory / "settings.json"
    if saved:
        # Even an unknown signal must reach CLI validation unchanged.
        settings.write_text(
            json.dumps(
                {
                    "schema_version": 1,
                    "name": "user",
                    "sample_period_us": 50,
                    "initial_channels": {"4": "JSO_not_in_firmware"},
                }
            )
        )
    calls = []
    monkeypatch.setattr(
        "ultrazohm_dataviewer.live.subprocess.Popen",
        lambda args, **kwargs: calls.append(args) or SimpleNamespace(poll=lambda: None),
    )
    monkeypatch.setattr(
        runtime_settings,
        "prepare_profile",
        lambda *args: pytest.fail("No temporary profile"),
    )
    controller = LiveController()
    controller.client = SimpleNamespace(status=lambda: {"service_id": "test-service"})
    controller._start_service(tmp_path / "session", "", repo=tmp_path)
    args = calls[0]
    assert args[args.index("--repo") + 1] == str(tmp_path)
    assert "--channel-mapping" not in args
    assert ("--profile" in args) == saved
    if saved:
        assert args[args.index("--profile") + 1] == str(settings)
        assert json.loads(settings.read_text())["initial_channels"] == {
            "4": "JSO_not_in_firmware"
        }
    assert not (tmp_path / "session.profile.json").exists()


def test_changed_repository_requires_restarting_owned_service(tmp_path):
    from types import SimpleNamespace

    from ultrazohm_dataviewer.live import LiveController

    client = SimpleNamespace(status=lambda: {"service_id": "test-service"})
    controller = LiveController(lambda endpoint: client)
    controller.owned.endpoint = "test-endpoint"
    controller.owned.process = SimpleNamespace(poll=lambda: None)
    controller.owned.repo = tmp_path / "previous"
    with pytest.raises(RuntimeError, match="different firmware repository"):
        controller._command(
            "connect", {"endpoint": "test-endpoint", "repo": str(tmp_path / "new")}
        )


@pytest.mark.parametrize("explicit_repo", [False, True])
def test_explicit_mapping_survives_connect_with_workspace(
    tmp_path, monkeypatch, gui_frame, explicit_repo
):
    from types import SimpleNamespace

    from imgui_bundle import imgui

    from ultrazohm_dataviewer.app import DataViewerApp
    from ultrazohm_dataviewer.user_paths import HEADER

    root = tmp_path / "firmware"
    header = root / HEADER
    header.parent.mkdir(parents=True)
    header.touch()
    directory = data_directory(root)
    mapping = directory / "selected.json"
    mapping.write_text(json.dumps({"channels": 20, "observables": {"JSO_custom": 42}}))
    (directory / "settings.json").write_text(
        json.dumps(
            {
                "schema_version": 1,
                "name": "custom",
                "sample_period_us": 100,
                "initial_channels": {"1": "JSO_custom"},
            }
        )
    )
    app = DataViewerApp(
        use_live=True,
        live_mapping=str(mapping),
        live_repo=str(root) if explicit_repo else None,
    )
    requests, launches = [], []
    controller = app.live.controller
    try:
        app.live.available = True
        monkeypatch.setattr(
            controller,
            "submit",
            lambda operation, **kwargs: requests.append((operation, kwargs)),
        )
        with monkeypatch.context() as patch:
            patch.setattr(
                imgui, "button", lambda label, *args, **kwargs: label == "Connect"
            )
            gui_frame(SimpleNamespace(render=app.live.render_data), app.state)
        operation, args = requests[0]
        assert operation == "connect"
        assert args["repo"] is None
        assert args["mapping"] == str(mapping)
        assert args["user_directory"] == str(directory)
        controller.client = SimpleNamespace(
            status=lambda: {"service_id": "test-service"}
        )
        monkeypatch.setattr(
            "ultrazohm_dataviewer.live.subprocess.Popen",
            lambda args, **kwargs: (
                launches.append(args) or SimpleNamespace(poll=lambda: None)
            ),
        )
        controller._start_service(
            args["output"],
            args["mapping"],
            repo=args["repo"],
            user_directory=args["user_directory"],
        )
        command = launches[0]
        assert "--repo" not in command
        assert command[command.index("--channel-mapping") + 1] == str(mapping)
        assert command[command.index("--profile") + 1] == str(
            directory / "settings.json"
        )
        assert controller.owned.mapping == mapping
    finally:
        controller.owned.process = None
        app._shutdown()


def test_service_launch_rejects_ambiguous_configuration(tmp_path):
    from ultrazohm_dataviewer.live import LiveController

    with pytest.raises(ValueError, match="either"):
        LiveController()._start_service(
            tmp_path / "session", "selected.json", repo=tmp_path
        )
    assert not (tmp_path / "session.service.log").exists()


def test_changed_mapping_requires_restarting_owned_service(tmp_path):
    from types import SimpleNamespace

    from ultrazohm_dataviewer.live import LiveController

    controller = LiveController(
        lambda endpoint: SimpleNamespace(status=lambda: {"service_id": "test-service"})
    )
    controller.owned.endpoint = "test-endpoint"
    controller.owned.process = SimpleNamespace(poll=lambda: None)
    controller.owned.mapping = tmp_path / "previous.json"
    with pytest.raises(RuntimeError, match="different channel mapping"):
        controller._command(
            "connect",
            {"endpoint": "test-endpoint", "mapping": str(tmp_path / "new.json")},
        )
