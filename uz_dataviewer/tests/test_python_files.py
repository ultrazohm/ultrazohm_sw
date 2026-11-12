"""Nonblocking Python file dialogs and save-before-run behavior."""
from types import SimpleNamespace

import pytest

from uz_dataviewer.live import LiveController, LiveUpdate
from uz_dataviewer.panels import live, script_editor
from uz_dataviewer.scripting import TEMPLATES


class Dialog:
    def __init__(self, result):
        self.value = result
        self.finished = False
        self.killed = False
    def ready(self, timeout=0): return self.finished
    def result(self): return self.value
    def kill(self): self.killed = True


@pytest.fixture
def files(monkeypatch):
    ws = live.LiveWorkspace(LiveController(lambda _: None))
    ws.controller.endpoint = '127.0.0.1:19740'
    ws.update = LiveUpdate(attached=True, status={'state': {'connected': True}})
    pending, starts, calls = [], [], []
    def choose(kind, title, default, filters):
        calls.append((kind, title, default, filters))
        return pending.pop(0)
    monkeypatch.setattr(script_editor, 'pfd', SimpleNamespace(
        open_file=lambda *args: choose('open', *args), save_file=lambda *args: choose('save', *args)))
    ws.scripts = SimpleNamespace(busy=False, message='Ready', output='', poll=lambda: None,
        start=lambda path, endpoint: starts.append((path, endpoint)), close=lambda: None)
    try:
        yield SimpleNamespace(ws=ws, pending=pending, starts=starts, calls=calls)
    finally:
        ws.close()


def test_open_save_and_save_as(files, tmp_path):
    ws = files.ws
    original = tmp_path/'source with spaces.py'
    original.write_text('print("original")\n')
    dialog = Dialog([str(original)])
    files.pending.append(dialog)
    ws.document.open_dialog('open')
    ws.document.poll()
    assert ws.document.path == ''  # Still waiting; no GUI blocking or state replacement.
    dialog.finished = True
    ws.document.poll()
    assert ws.document.code == original.read_text()
    assert ws.document.path == str(original)
    ws.document.code = 'print("edited")\n'
    ws.document.request_save()
    assert original.read_text() == ws.document.code
    target = tmp_path/'another script.py'
    dialog = Dialog(str(target))
    dialog.finished = True
    files.pending.append(dialog)
    ws.document.open_dialog('save')
    ws.document.poll()
    assert ws.document.path == str(target)
    assert target.read_text() == ws.document.code
    assert files.starts == []


def test_template_is_unsaved_and_cancelled_run_does_not_write_or_execute(files, tmp_path):
    ws = files.ws
    original = tmp_path/'existing.py'
    original.write_text('original file')
    ws.document.path = str(original)
    ws.document.choose_template('Timed recording')
    assert ws.document.path == ''
    assert ws.document.code == TEMPLATES['Timed recording']
    dialog = Dialog('')
    files.pending.append(dialog)
    ws.document.request_save(run_after=True)
    assert files.starts == []
    dialog.finished = True
    ws.document.poll()
    assert ws.document.path == ''
    assert ws.document.code == TEMPLATES['Timed recording']
    assert original.read_text() == 'original file'
    assert files.starts == []


def test_unsaved_run_saves_selected_filename_then_executes(files, tmp_path):
    target = tmp_path/'new script'  # Supply the extension when the dialog omits it.
    dialog = Dialog(str(target))
    files.pending.append(dialog)
    files.ws.document.request_save(run_after=True)
    assert files.starts == []
    dialog.finished = True
    files.ws.document.poll()
    saved = target.with_suffix('.py')
    assert saved.read_text() == files.ws.document.code
    assert files.starts == [(saved, '127.0.0.1:19740')]
    files.ws.document.request_save(run_after=True)
    assert len(files.calls) == 1  # Existing files run directly after saving.
    assert len(files.starts) == 2


def test_run_does_not_execute_after_connection_change_or_save_failure(files, tmp_path):
    dialog = Dialog(str(tmp_path/'new.py'))
    files.pending.append(dialog)
    files.ws.document.request_save(run_after=True)
    files.ws.controller.endpoint = '127.0.0.1:19741'
    dialog.finished = True
    files.ws.document.poll()
    assert files.starts == []
    assert 'connection changed' in files.ws.document.error
    files.ws.document.path = ''
    target = tmp_path/'directory.py'
    target.mkdir()
    dialog = Dialog(str(target))
    dialog.finished = True
    files.pending.append(dialog)
    files.ws.document.request_save(run_after=True)
    files.ws.document.poll()
    assert files.starts == []
    assert files.ws.document.error
    assert files.ws.document.path == ''


def test_added_extension_never_silently_overwrites_existing_file(files, tmp_path):
    target = tmp_path/'existing.py'
    target.write_text('keep me')
    first, confirm = Dialog(str(target.with_suffix(''))), Dialog(str(target))
    first.finished = True
    files.pending.extend([first, confirm])
    files.ws.document.request_save(run_after=True)
    files.ws.document.poll()
    assert target.read_text() == 'keep me'
    assert files.starts == []
    assert files.calls[-1][2] == str(target)
    confirm.finished = True
    files.ws.document.poll()
    assert target.read_text() == files.ws.document.code
    assert len(files.starts) == 1


def test_open_failure_preserves_editor_and_closing_cancels_dialog(files, tmp_path):
    code = files.ws.document.code
    dialog = Dialog([str(tmp_path/'missing.py')])
    dialog.finished = True
    files.pending.append(dialog)
    files.ws.document.open_dialog('open')
    files.ws.document.poll()
    assert files.ws.document.code == code
    assert files.ws.document.path == ''
    assert files.ws.document.error
    dialog = Dialog([])
    files.pending.append(dialog)
    files.ws.document.open_dialog('open')
    files.ws.close()
    assert dialog.killed
    assert files.starts == []


def test_python_panel_shows_filename_only(files, tmp_path, gui_frame, app_state, monkeypatch):
    from imgui_bundle import imgui
    captured = []
    original = imgui.text_unformatted
    def text(value, *args):
        captured.append(value)
        return original(value, *args)
    monkeypatch.setattr(imgui, 'text_unformatted', text)
    path = tmp_path/'private-directory'/'example.py'
    files.ws.document.path = str(path)
    gui_frame(SimpleNamespace(render=lambda _: files.ws.render_python()), app_state)
    assert path.name in captured
    assert str(path) not in captured


def test_dialog_completes_without_new_acquisition_updates(files, tmp_path):
    ws = files.ws
    path = tmp_path/'script.py'
    path.write_text('pass\n')
    dialog = Dialog([str(path)])
    files.pending.append(dialog)
    ws.controller.update = ws.update
    ws._revision = ws.update.revision
    ws.document.open_dialog('open')
    dialog.finished = True
    ws.pump()
    assert ws.document.path == str(path)
    assert ws.document.code == path.read_text()
