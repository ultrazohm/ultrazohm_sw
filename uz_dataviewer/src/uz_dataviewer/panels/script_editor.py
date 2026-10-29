"""Python document editing and nonblocking file dialogs, independent of acquisition state."""
from pathlib import Path
from imgui_bundle import imgui, imgui_color_text_edit
from ..scripting import TEMPLATES
try:
    from imgui_bundle import portable_file_dialogs as pfd
except ImportError:
    pfd = None


class ScriptEditor:
    def __init__(self, busy, endpoint, start):
        self.busy = busy
        self.endpoint = endpoint
        self.start = start
        self.path = ''
        self.dialog = None
        self.editor = None
        self.code = TEMPLATES['Blank']
        self.error = ''

    @property
    def code(self):
        return self.editor.get_text() if self.editor is not None else self._code

    @code.setter
    def code(self, code):
        self._code = code
        if self.editor is not None:
            self.editor.set_text(code)

    def widget(self):
        # Create only in a GUI context. Do not reset text each frame: that would
        # discard the cursor, selection, and undo history while the user types.
        if self.editor is None:
            editor = imgui_color_text_edit.TextEditor()
            editor.set_language(imgui_color_text_edit.TextEditor.Language.python())
            editor.set_palette(editor.get_dark_palette())
            editor.set_tab_size(4)
            editor.set_insert_spaces_on_tabs(True)
            editor.set_auto_indent_enabled(True)
            editor.set_show_line_numbers_enabled(True)
            editor.set_show_matching_brackets(True)
            editor.set_text(self._code)
            self.editor = editor
        return self.editor

    def render(self, can_run):
        imgui.text_wrapped('Run executes this file with --endpoint HOST:PORT in this Python environment. '
                           'Use a template for argument parsing and Client setup; imports and __main__ work normally.')
        imgui.text_unformatted(Path(self.path).name if self.path else 'Unsaved script')
        imgui.begin_disabled(self.busy() or self.dialog is not None)
        if imgui.button('Open Python file...'):
            self.open_dialog('open')
        imgui.same_line()
        if imgui.button('Save'):
            self.request_save()
        imgui.same_line()
        if imgui.button('Save as...'):
            self.open_dialog('save')
        imgui.same_line()
        if imgui.begin_combo('Template', 'Choose template'):
            for name in TEMPLATES:
                if imgui.selectable(name, False)[0]:
                    self.choose_template(name)
            imgui.end_combo()
        editor = self.widget()
        editor.set_read_only_enabled(self.busy() or self.dialog is not None)
        editor.render('##python-code', imgui.ImVec2(max(100., imgui.get_content_region_avail().x), 260.))
        imgui.begin_disabled(not can_run)
        if imgui.button('Run'):
            self.request_save(run_after=True)
        imgui.end_disabled()
        imgui.end_disabled()
    def choose_template(self, name):
        self.code = TEMPLATES[name]
        self.path = ''
        self.error = ''

    def open_dialog(self, action, default_path=None, endpoint=None):
        if self.busy() or self.dialog is not None:
            return
        try:
            if pfd is None:
                raise RuntimeError('Native file dialogs are unavailable in this build')
            filters = ['Python files (*.py)', '*.py']
            default_path = default_path or self.path or 'measurement.py'
            dialog = (pfd.open_file('Open Python file', default_path, filters) if action == 'open' else
                      pfd.save_file('Save Python file', default_path, filters))
            self.dialog = (dialog, action, endpoint or self.endpoint())
            self.error = ''
        except Exception as exc:
            self.error = str(exc)

    def poll(self):
        if self.dialog is None:
            return
        dialog, action, endpoint = self.dialog
        if not dialog.ready(0):
            return
        self.dialog = None
        try:
            result = dialog.result()
            selected = (result[0] if result else '') if action == 'open' else result
            if not selected:
                return
            path = Path(selected).expanduser().resolve()
            if action == 'open':
                if path.suffix.lower() != '.py':
                    raise ValueError('Choose a .py file')
                self.code = path.read_text(encoding='utf-8')
                self.path = str(path)
                self.error = ''
                return
            if not path.suffix:
                path = path.with_suffix('.py')
                if path.exists():
                    # Reopen on the actual destination so the native dialog
                    # confirms replacement after we supply the .py extension.
                    self.open_dialog(action, str(path), endpoint)
                    return
            saved = self.save(path)
            if saved is not None and action == 'run':
                self.start(saved, endpoint)
        except Exception as exc:
            self.error = str(exc)

    def request_save(self, run_after=False):
        if self.busy() or self.dialog is not None:
            return
        if not self.path:
            self.open_dialog('run' if run_after else 'save')
            return
        path = self.save()
        if path is not None and run_after:
            self.start(path, self.endpoint())

    def save(self, destination=None):
        try:
            path = Path(destination or self.path).expanduser().resolve()
            if path.suffix.lower() != '.py':
                raise ValueError('Choose a .py file')
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(self.code, encoding='utf-8')
            self.path = str(path)
            self.error = ''
            return path
        except Exception as exc:
            self.error = str(exc)
            return None

    def close(self):
        if self.dialog is not None:
            self.dialog[0].kill()
            self.dialog = None
