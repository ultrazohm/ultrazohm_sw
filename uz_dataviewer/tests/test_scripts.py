"""Command scripts are automation; JSON is the sole session format."""

import json

import pytest

from uz_dataviewer import session
from uz_dataviewer.commands import CommandError
from uz_dataviewer.state import AppState


def test_automation_can_load_json_and_continue(app_state, tmp_path):
    snapshot = tmp_path / 'state.json'
    app_state.set_grid(2, 1)
    session.save_state(app_state, str(snapshot))
    app_state.set_grid(1, 1)
    script = tmp_path / 'commands.uzscript'
    script.write_text(f'# Automation\n\nload_state({json.dumps(str(snapshot))})\nset_max_points(750)\n')
    assert session.run_script(app_state, str(script)) == 2
    assert (app_state.rows, app_state.cols) == (2, 1)
    assert app_state.max_points == 750


def test_generated_session_scripts_rejected_before_mutation(app_state, tmp_path):
    script = tmp_path / 'legacy.uzscript'
    script.write_text('# UltraZohm Data Viewer session script v4\nclear_session()\n')
    token = app_state.session_token
    with pytest.raises(ValueError, match='save sessions as JSON'):
        session.run_script(app_state, str(script))
    assert app_state.session_token is token
    with pytest.raises(CommandError, match='Unknown command'):
        app_state.commands.execute(app_state, 'export_script', [str(script)])


@pytest.mark.parametrize("reset_command", ["clear_session()", "load_state"])
def test_gui_replay_continues_after_session_replacement(app_state, tmp_path, reset_command):
    from uz_dataviewer import automation

    snapshot = tmp_path / "session.json"
    session.save_state(app_state, str(snapshot))
    if reset_command == "load_state":
        reset_command = f"load_state({json.dumps(str(snapshot))})"
    recording = tmp_path / "recording.csv"
    recording.write_text("time,y\n0,0\n0.0001,0.1\n")
    script = tmp_path / "commands.uzscript"
    script.write_text(
        f"{reset_command}\nload({json.dumps(str(recording))})\n"
        'set_grid(2, 1)\nadd_signal(plot_1, "recording.csv", "y")\n'
    )
    app_state.async_exports = True
    assert session.run_script(app_state, str(script)) is None
    for _ in range(10):
        automation.poll(app_state)
        if app_state.services.replay is None:
            break
    assert len(app_state.registry.runs) == 1
    assert app_state.cell_count == 2
    assert app_state.cells[0].signals == [(app_state.registry.runs[0].id, "y")]
    assert app_state.services.replay is None


def test_script_aborts_when_a_recording_cannot_load(tmp_path):
    from uz_dataviewer.session import run_script
    state = AppState()
    script = tmp_path / 'missing.uzscript'
    script.write_text('load("missing.csv")\nset_grid(2,2)\n')
    try:
        with pytest.raises(CommandError, match='Failed to load'):
            run_script(state, str(script))
        assert state.cell_count == 1
    finally:
        state.shutdown()
