"""Command scripts are automation; JSON is the sole session format."""

from uz_dataviewer import runtime

import pytest

from uz_dataviewer import session
from uz_dataviewer.commands import CommandError
from uz_dataviewer.state import AppState


@pytest.mark.parametrize('web', [False, True])
def test_automation_can_load_json_and_continue(app_state, tmp_path, monkeypatch, web):
    from uz_dataviewer import webbridge
    snapshot = tmp_path / 'state.json'
    app_state.set_grid(2, 1)
    session.save_state(app_state, str(snapshot))
    app_state.set_grid(1, 1)
    monkeypatch.setattr(runtime, 'IS_WEB', web)
    script = tmp_path / 'commands.uzscript'
    script.write_text(f'# Automation\n\nload_state("{snapshot}")\nset_max_points(750)\n')
    assert session.run_script(app_state, str(script)) == 2
    assert (app_state.rows, app_state.cols) == (2, 1)
    assert app_state.max_points == 750
    if web:
        assert app_state.backend == 'pyarrow'


def test_generated_session_scripts_rejected_before_mutation(app_state, tmp_path):
    script = tmp_path / 'legacy.uzscript'
    script.write_text('# UltraZohm Data Viewer session script v4\nclear_session()\n')
    token = app_state.session_token
    with pytest.raises(ValueError, match='save sessions as JSON'):
        session.run_script(app_state, str(script))
    assert app_state.session_token is token
    with pytest.raises(CommandError, match='Unknown command'):
        app_state.commands.execute(app_state, 'export_script', [str(script)])


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
