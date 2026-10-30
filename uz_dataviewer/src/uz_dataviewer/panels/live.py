"""Live controls and a dedicated workspace sharing the existing plot renderer."""
from __future__ import annotations

import importlib.util
import math
import time
from pathlib import Path
from queue import Empty

from imgui_bundle import imgui, implot

from ..live import LiveController, fuzzy_names, new_output_directory, action_block_reason
from ..model import Signal
from ..sources import SourceColumn, shift_time
from ..state import AppState
from ..scripting import ScriptRunner
from .script_editor import ScriptEditor
from ..flashing import xsct_available, restore_xsct, select_xsct
from .plots import PlotsPanel

try:
    from imgui_bundle import portable_file_dialogs as pfd
except ImportError:
    pfd = None

LIVE_SIGNAL_DND_TYPE = 'UZ_LIVE_SIGNAL'


class LivePlotsPanel(PlotsPanel):
    def __init__(self, workspace=None):
        super().__init__(LIVE_SIGNAL_DND_TYPE)
        self.workspace = workspace
        self._axis_links = {}
        self._anchors = {}
        self._selection = None

    def _apply_pending_limits(self, state, cell, data_min, data_max):
        if self.workspace is not None:
            implot.setup_axis_zoom_constraints(implot.ImAxis_.x1, .001, self.workspace.maximum_depth())
        if not getattr(state, 'following_live', False):
            return super()._apply_pending_limits(state, cell, data_min, data_max)
        # A moving X window must not cancel the renderer's asynchronous initial
        # Y fit. Keep fitting Y until samples arrive, then apply the live X range.
        limits = cell.pending_x_lim
        if self._selection is not None and self._selection['cell'] == id(cell):
            limits = self._selection['anchor']
        cell.pending_x_lim = None
        super()._apply_pending_limits(state, cell, None, data_max)
        if limits is not None:
            self._anchors[id(cell)] = limits
            links = self._axis_links.setdefault(id(cell), (implot.BoxedValue(limits[0]), implot.BoxedValue(limits[1])))
            links[0].value, links[1].value = limits
            # Links seed each new live range without locking native mouse input.
            implot.setup_axis_links(implot.ImAxis_.x1, *links)
        return False

    def _setup_shared_x(self, state, index, cell):
        if not getattr(state, 'following_live', False):
            return super()._setup_shared_x(state, index, cell)
        return False

    def _time_series_input(self, state, index, cell, lo, hi):
        if self.workspace is None or not state.is_time_plot(cell):
            return
        hovered = implot.is_plot_hovered() or implot.is_axis_hovered(implot.ImAxis_.x1)
        wheel = imgui.get_io().mouse_wheel if hovered else 0.
        anchor = self._anchors.get(id(cell), (lo, hi))
        tolerance = max(1e-9, (anchor[1] - anchor[0]) * 1e-6)
        changed = abs(lo - anchor[0]) > tolerance or abs(hi - anchor[1]) > tolerance
        if state.following_live and hovered and ((wheel and imgui.get_io().key_shift) or
                (changed and not wheel and imgui.is_mouse_dragging(implot.get_input_map().pan))):
            self._driver = index
            self.workspace.window_seconds = max(.001, min(self.workspace.maximum_depth(), hi - lo))
            self.workspace.inspect((lo, hi))
        elif hovered and hi > lo and (wheel or not state.following_live):
            self.workspace.window_seconds = max(.001, min(self.workspace.maximum_depth(), hi - lo))
        self._handle_box_zoom(state, index, cell, lo, hi)

    def _handle_box_zoom(self, state, index, cell, lo, hi):
        selecting = implot.is_plot_selected()
        if selecting:
            if self._selection is None:
                button = implot.get_input_map().select
                self._selection = dict(cell=id(cell), button=button, inspect=imgui.get_io().key_shift,
                                       anchor=(lo, hi), box=None)
            selection = self._selection
            if selection['cell'] != id(cell):
                return
            box = implot.get_plot_selection()
            selection['box'] = (box.x.min, box.x.max, box.y.min, box.y.max)
            if selection['inspect'] and state.following_live:
                self._driver = index
                self.workspace.inspect((lo, hi))
        selection = self._selection
        if selection is None or selection['cell'] != id(cell):
            return
        if imgui.is_mouse_clicked(implot.get_input_map().select_cancel):
            self._selection = None
        elif imgui.is_mouse_released(selection['button']):
            self._selection = None
            box = selection['box']
            if box is None or box[1] <= box[0] or box[3] <= box[2]:
                return
            self._driver = index
            self.workspace.window_seconds = max(.001, min(self.workspace.maximum_depth(), box[1] - box[0]))
        elif not selecting and not imgui.is_mouse_down(selection['button']):
            self._selection = None

    def _maybe_echo_zoom(self, state, index, lo, hi, *, suppress):
        if not getattr(state, 'following_live', False):
            super()._maybe_echo_zoom(state, index, lo, hi, suppress=suppress)

    def render(self, state):
        cells = {id(cell) for cell in state.cells}
        self._axis_links = {key: value for key, value in self._axis_links.items() if key in cells}
        self._anchors = {key: value for key, value in self._anchors.items() if key in cells}
        if self._selection is not None and self._selection['cell'] not in cells:
            self._selection = None
        super().render(state)

    def _display(self, state, slot, run, channel, lo, hi, budget):
        source = run.data_source()
        offset = run.time_offset
        # Keep the last completed display while the next immutable snapshot is
        # decimated. The key changes with data; identity changes only per run.
        identity = (run.id, channel, offset)
        key = (identity, source.metadata.identity, lo, hi, budget)
        def compute(cancel):
            data = source.read_plot(channel, lo, hi, budget, cancel, offset=offset)
            return shift_time(data.time, offset), data.values, data.raw_count
        return self._request_data(state, slot, key, identity, [source], compute)


class LiveWorkspace:
    def __init__(self, controller=None, repo=None):
        self.controller = controller or LiveController()
        self.state = AppState()
        self.state.async_exports = True
        self.state.registry.cache.limit = 64 * 1024**2
        self.plots = LivePlotsPanel(self)
        self.endpoint = '127.0.0.1:19740'
        self.ip = '192.168.1.233'
        self.port = 1000
        self.output = new_output_directory(repo)
        self.mapping = ''
        self.repo = str(repo) if repo is not None else None
        self._xsct_dialog = None
        self.tool_error = ''
        try:
            restore_xsct(repo)
        except (OSError, ValueError, KeyError) as exc:
            self.tool_error = str(exc)
        self.cli_busy = lambda: False
        self.flash_available = xsct_available()
        self._flash_config = None
        self.follow = True
        self.paused = False
        self.window_seconds = 2.
        self.query = ''
        self.selected_slot = None
        self.variable_query = ''
        self.variable_values = {}
        self.run = None
        self._source = None
        self._epoch = None
        self._revision = -1
        self.update = self.controller.latest()
        self.error = ''
        self.pending_message = ''
        self._pending_completion = 0
        self._last_feedback = None
        self.available = importlib.util.find_spec('ultrazohm') is not None
        self.scripts = ScriptRunner(send_stop=self.controller.send_stop)
        self.document = ScriptEditor(lambda: self.scripts.busy, lambda: self.controller.endpoint, self._start_script)

    def block_reason(self, action='manual'):
        return action_block_reason(action, flashing=self.controller.flashing, script_busy=self.scripts.busy)

    def send(self, operation, **kwargs):
        try:
            if reason := self.block_reason(operation):
                raise RuntimeError(reason)
            if operation == 'stop':
                self.controller.cancel_pending_commands()
                if not self.scripts.busy:
                    self.scripts.endpoint = self.controller.endpoint
                self.scripts.stop()
                self.error = ''
                return
            if operation in ('connect', 'attach'):
                self.pending_message = 'Connecting…' if operation == 'connect' else 'Attaching to service…'
                self._pending_completion = self.controller.latest().completed_commands + 1
            self.controller.submit(operation, **kwargs)
            if operation == 'shutdown':
                self.output = new_output_directory(parent=Path(self.output).expanduser().resolve().parent)
            self.error = ''
        except Exception as exc:
            self.error = str(exc)
            self.pending_message = ''

    def pump(self, main_state=None):
        from ..exports import poll
        poll(self.state)
        self.scripts.poll()
        update = self.controller.latest()
        self.update = update
        self.document.poll()
        if self._xsct_dialog is not None and self._xsct_dialog.ready():
            selected = self._xsct_dialog.result()
            self._xsct_dialog = None
            if selected:
                try:
                    select_xsct(selected[0], self.repo)
                    self.flash_available = xsct_available()
                    self.tool_error = ''
                except (OSError, ValueError) as exc:
                    self.tool_error = str(exc)
        if update.flash_config is not None and update.flash_config != self._flash_config:
            self.mapping, self.output = update.flash_config
            self._flash_config = update.flash_config
        if main_state is not None:
            for _ in range(200):
                try:
                    level, text = self.controller.messages.get_nowait()
                except Empty:
                    break
                getattr(main_state.console, level)(text)
        if update.revision == self._revision:
            return
        self._revision = update.revision
        if update.completed_commands >= self._pending_completion:
            self.pending_message = ''
        feedback = (update.activity, update.error, update.notice)
        if main_state is not None and feedback != self._last_feedback:
            if update.error:
                main_state.console.error('Live: ' + update.error)
            elif update.activity:
                main_state.console.info('Live: ' + update.activity)
            elif update.notice:
                main_state.console.ok('Live: ' + update.notice)
            self._last_feedback = feedback
        if not self.paused and update.source is None and update.epoch != self._epoch:
            if self.run is not None:
                self.state.remove_run(self.run.id)
            self.run = self._source = None
            self._epoch = update.epoch
        if (self.paused or update.source is None or
                (update.source is self._source and update.epoch == self._epoch)):
            return
        source = update.source
        if self.run is None or self._epoch != update.epoch:
            if self.run is not None:
                self.state.remove_run(self.run.id)
            self.run = self.state.registry.add_source('Live UltraZohm', '', source)
            self.run.reloadable = False
            self._epoch = update.epoch
        else:
            run = self.run
            run.source = source
            run.time = run.time_raw = SourceColumn(source)
            run.signals = {name: Signal(name, '', SourceColumn(source, name), run.id)
                           for name in source.metadata.channels}
            run.mark_time_changed()
        self._source = source

    def freeze(self, target):
        """Copy the visible live window to the ordinary offline-analysis registry."""
        if self.run is None:
            return
        lo, hi = self.run.source.metadata.time_range
        if self.state.cells and self.state.cells[0].x_lim is not None:
            lo, hi = self.state.cells[0].x_lim
        t, ys = self.run.read_window(list(self.run.signals), lo, hi)
        if not len(t):
            raise ValueError('The visible live window contains no samples')
        run = target.registry.add_run('Live snapshot ' + time.strftime('%H:%M:%S'), '',
                                      t.copy(), {n: y.copy() for n, y in ys.items()}, {})
        run.reloadable = False
        refs = self.state.cells[0].signals or [(self.run.id, n) for n in list(ys)[:1]]
        for _, name in refs:
            if name in run.signals:
                target.cells[0].add((run.id, name))
        target.console.info(f'Frozen {len(t):,} live samples for analysis (not saved to disk)')

    def render_data(self, main_state):
        imgui.begin_disabled(bool(self.block_reason()))
        try:
            self._render_data(main_state)
        finally:
            imgui.end_disabled()

    def _render_data(self, main_state):
        from ..user_paths import data_directory
        if not self.available:
            imgui.text_wrapped('Live acquisition requires the ultrazohm backend. Restart with start.sh --use-live (start.ps1 on Windows). Use --live-wheel PATH to select an exact wheel.')
            return
        activity = self.update.activity or self.pending_message
        error = self.error or self.update.error
        if error and not activity:
            imgui.text_colored((1., .35, .3, 1.), 'Connection / command failed')
            imgui.text_wrapped(error)
        elif activity:
            imgui.text_colored((1., .8, .25, 1.), activity)
        elif self.update.attached and self.update.status.get('state', {}).get('connected'):
            receiving = self.update.received_at and time.monotonic() - self.update.received_at < 1
            imgui.text_colored((.3, .9, .5, 1.) if receiving else (1., .8, .25, 1.),
                               'Connected — receiving live data' if receiving else 'Connected — waiting for live data')
        else:
            imgui.text_disabled('Device disconnected')
        imgui.separator()
        imgui.begin_disabled(self.update.attached)
        _, self.endpoint = imgui.input_text('Service endpoint', self.endpoint)
        imgui.end_disabled()
        _, self.ip = imgui.input_text('Device IP', self.ip)
        _, port = imgui.input_int('Device port', self.port)
        self.port = max(1, min(65535, port))
        imgui.begin_disabled(bool(activity))
        connection_label = 'Disconnect' if self.update.attached else 'Connect'
        if imgui.button(connection_label):
            if self.update.attached:
                self.send('shutdown')
            else:
                self.send('connect', endpoint=self.endpoint, ip=self.ip, port=self.port,
                          output=self.output, mapping=self.mapping, user_directory=str(data_directory(self.repo)))
        if imgui.is_item_hovered(imgui.HoveredFlags_.allow_when_disabled):
            imgui.set_tooltip(
                'Send device Stop, finalize recordings, and shut down the service. Keep the viewer open.'
                if self.update.attached else
                'Start a viewer-managed service and connect to the selected UltraZohm IP. For a service already running, use Existing service > Attach.')

        def next_button(label):
            # Keep the actions together, wrapping in narrow docked panels.
            width = imgui.calc_text_size(label).x + 2 * imgui.get_style().frame_padding.x
            right = imgui.get_cursor_screen_pos().x + imgui.get_content_region_avail().x
            if imgui.get_item_rect_max().x + imgui.get_style().item_spacing.x + width <= right:
                imgui.same_line()

        next_button('Flash UZ')
        imgui.begin_disabled(self.cli_busy() or not self.flash_available)
        if imgui.button('Flash UZ'):
            imgui.open_popup('Flash UltraZohm?')
        imgui.end_disabled()
        if imgui.is_item_hovered(imgui.HoveredFlags_.allow_when_disabled):
            imgui.set_tooltip(
                'Select the Vitis XSCT launcher with Browse for XSCT, or start the viewer from a Vitis command prompt.'
                if not self.flash_available else
                'Ask for confirmation, then send device Stop, finalize logging, shut down the service, regenerate the mapping, flash, and reconnect.')
        imgui.end_disabled()
        imgui.begin_disabled(pfd is None or self._xsct_dialog is not None or bool(activity))
        if imgui.button('Browse for XSCT'):
            self._xsct_dialog = pfd.open_file('Select Vitis XSCT launcher', '',
                                             ['XSCT launcher', 'xsct xsct.exe xsct.cmd xsct.bat'])
        imgui.end_disabled()
        if self.tool_error:
            imgui.text_wrapped(self.tool_error)
        if imgui.collapsing_header('Existing service'):
            imgui.begin_disabled(bool(activity))
            if imgui.button('Attach'):
                self.send('attach', endpoint=self.endpoint, mapping=self.mapping)
            if imgui.is_item_hovered(imgui.HoveredFlags_.allow_when_disabled):
                imgui.set_tooltip('Attach to the service at the selected endpoint without starting a service or changing its device connection.')
            imgui.same_line()
            imgui.begin_disabled(not self.update.attached)
            if imgui.button('Detach'):
                self.send('detach')
            if imgui.is_item_hovered(imgui.HoveredFlags_.allow_when_disabled):
                imgui.set_tooltip('Detach only this viewer. Acquisition and logging continue; no device Stop is sent.')
            imgui.same_line()
            if imgui.button('Shutdown'):
                self.send('shutdown')
            if imgui.is_item_hovered(imgui.HoveredFlags_.allow_when_disabled):
                imgui.set_tooltip('Same as Disconnect: send device Stop, finalize recordings, and exit the attached service, including one started externally.')
            imgui.end_disabled()
            imgui.end_disabled()
        self._render_flash_confirmation()
        if imgui.collapsing_header('Service settings (used when launching)'):
            _, self.output = imgui.input_text('New session directory', self.output)
            _, self.mapping = imgui.input_text('Channel mapping JSON (optional)', self.mapping)
            if self.mapping:
                imgui.text_wrapped('Runtime settings: ' + str(data_directory(self.repo) / 'settings.json'))
            imgui.text_wrapped('Connect launches a new service with these settings. Use Existing service to attach to a running service.')
        state = self.update.status.get('state', {})
        profile = self.update.catalog
        imgui.separator()
        if imgui.collapsing_header('Connection details'):
            imgui.text_unformatted('Service: ' + ('attached' if self.update.attached else 'detached'))
            imgui.text_unformatted('Device: ' + ('connected' if state.get('connected') else 'disconnected'))
            imgui.text_unformatted('Platform: ' + str(state.get('platform_state') or 'unavailable'))
            if self.update.received_at:
                age = time.monotonic() - self.update.received_at
                imgui.text_unformatted(f'Last data: {age:.1f}s ago' + (' — STALE' if age > 1 else ''))
            if self.run:
                imgui.text_unformatted(f'Visible RAM: {self.run.n_rows:,} samples / {self.run.duration:.2f}s')
            if profile:
                imgui.text_wrapped('Mapping: ' + profile.get('channel_mapping_name', ''))
            if self.update.notice:
                imgui.text_wrapped(self.update.notice)
        if state.get('error'):
            imgui.text_wrapped('Device error: ' + str(state['error']))
        if self.update.error or self.error:
            imgui.text_wrapped('Error: ' + (self.error or self.update.error))
        logging = self.update.status.get('logging', {})
        imgui.separator_text('Logging')
        self._render_logging(main_state, state)
        imgui.separator()
        imgui.text_wrapped('Drag a channel into Live Plots. Double-click to change its observable.')
        locked = any(v.get('phase') in ('recording', 'paused') for v in logging.values())
        if locked:
            imgui.text_disabled('Stop fast and slow logging to change assignments.')
        for assignment in self.update.assignments:
            slot, name = assignment['channel'], assignment['name']
            imgui.selectable(f'{slot:02d}: {name or "unassigned"}', False)
            if not locked and imgui.is_item_hovered() and imgui.is_mouse_double_clicked(0):
                self.selected_slot, self.query = slot, ''
                imgui.open_popup('Select observable')
            if name and self.run and name in self.run.signals and imgui.begin_drag_drop_source():
                self.state.dragged_ref = (self.run.id, name)
                imgui.set_drag_drop_payload_py_id(LIVE_SIGNAL_DND_TYPE, 0)
                imgui.text_unformatted(name)
                imgui.end_drag_drop_source()
        if imgui.begin_popup('Select observable'):
            imgui.text_unformatted(f'Channel {self.selected_slot}')
            if imgui.is_window_appearing():
                imgui.set_keyboard_focus_here()
            _, self.query = imgui.input_text('Fuzzy search', self.query)
            imgui.begin_disabled(locked or not self.update.attached)
            for name in fuzzy_names(profile.get('observables', {}), self.query):
                if imgui.selectable(name, False)[0]:
                    self.send('set_observable', name=name, channel=self.selected_slot)
                    imgui.close_current_popup()
            imgui.end_disabled()
            imgui.end_popup()

    def _render_logging(self, main_state, state):
        logging = self.update.status.get('logging', {})
        flags = imgui.TableFlags_.sizing_stretch_same | imgui.TableFlags_.borders_inner_v
        if imgui.begin_table('##logging', 2, flags):
            for stream, title, start, stop in (
                ('fast', 'Fast logging', 'start_logging', 'stop_logging'),
                ('slow', 'Slow logging', 'start_logging_slow_data', 'stop_logging_slow_data')):
                imgui.table_next_column()
                info = logging.get(stream, {})
                phase = info.get('phase', 'idle')
                imgui.text_unformatted(f'{title}: {phase}')
                imgui.begin_disabled(not self.update.attached or not state.get('connected'))
                imgui.begin_disabled(phase not in ('idle', 'complete', 'failed'))
                if imgui.button('Start##' + stream):
                    self.send(start)
                imgui.end_disabled()
                imgui.same_line()
                imgui.begin_disabled(phase not in ('recording', 'paused'))
                if imgui.button('Stop logging##' + stream):
                    self.send(stop)
                imgui.end_disabled()
                imgui.end_disabled()
                path = info.get('parquet')
                if path:
                    imgui.text_wrapped(str(path))
                if info.get('error'):
                    imgui.text_wrapped(str(info['error']))
                if phase == 'complete' and path:
                    if imgui.button('Open completed log##' + stream):
                        main_state.request_load(path)
            imgui.end_table()

    def render_control(self):
        state = self.update.status.get('state', {})
        imgui.text_unformatted('Platform: ' + str(state.get('platform_state') or 'unavailable'))
        imgui.begin_disabled(not self.scripts.busy and (not self.update.attached or not state.get('connected')))
        for label, operation in [('Enable System', 'enable_system'), ('Enable Control', 'enable_control'), ('Stop', 'stop')]:
            imgui.begin_disabled(bool(self.block_reason(operation)))
            if imgui.button(label):
                self.send(operation)
            imgui.end_disabled()
            imgui.same_line()
        imgui.new_line()
        imgui.begin_disabled(bool(self.block_reason()))
        for number in range(1, 9):
            if imgui.button(f'User {number}'):
                self.send('button', number=number)
            if number % 4:
                imgui.same_line()
        imgui.separator()
        self._render_variables()
        imgui.end_disabled()
        imgui.end_disabled()
        if self.update.error or self.error:
            imgui.text_wrapped('Error: ' + (self.error or self.update.error))

    def _render_variables(self):
        _, self.variable_query = imgui.input_text('Filter variables', self.variable_query)
        variables = self.update.catalog.get('variables', {})
        names = sorted(variables, key=lambda name: (variables[name], name))
        if self.variable_query.strip():
            matches = set(fuzzy_names(names, self.variable_query))
            names = [name for name in names if name in matches]
        flags = (imgui.TableFlags_.row_bg | imgui.TableFlags_.borders_inner_v |
                 imgui.TableFlags_.resizable | imgui.TableFlags_.scroll_y)
        height = max(120., min(420., imgui.get_content_region_avail().y - 80.))
        if imgui.begin_table('##variables', 2, flags, imgui.ImVec2(0., height)):
            imgui.table_setup_column('Variable')
            imgui.table_setup_column('Value (Enter to send)')
            imgui.table_setup_scroll_freeze(0, 1)
            imgui.table_headers_row()
            for name in names:
                imgui.table_next_row()
                imgui.table_set_column_index(0)
                imgui.text_unformatted(name)
                imgui.table_set_column_index(1)
                imgui.set_next_item_width(-1.)
                text = self.variable_values.get(name, '0')
                sent = self.update.variable_sends.get(name)
                try:
                    highlight = sent is not None and time.monotonic() - sent[0] < .2 and float(text) == sent[1]
                except ValueError:
                    highlight = False
                if highlight:
                    for color in (imgui.Col_.frame_bg, imgui.Col_.frame_bg_hovered, imgui.Col_.frame_bg_active):
                        imgui.push_style_color(color, (.12, .32, .65, 1.))
                try:
                    submitted, text = imgui.input_text(f'##variable_value_{name}',
                        text, imgui.InputTextFlags_.enter_returns_true)
                finally:
                    if highlight:
                        imgui.pop_style_color(3)
                self.variable_values[name] = text
                if submitted:
                    try:
                        value = float(text)
                        if not math.isfinite(value):
                            raise ValueError('enter a finite number')
                    except ValueError as exc:
                        self.error = f'Invalid value for {name}: {exc}'
                    else:
                        self.send('set_variable', name=name, value=value)
            imgui.end_table()

    def render_python(self):
        connected = self.available and self.update.attached and self.update.status.get('state', {}).get('connected')
        self.document.render(connected and not self.block_reason('script'))
        imgui.same_line()
        imgui.begin_disabled(not self.scripts.busy)
        if imgui.button('Stop script + device'):
            self.send('stop')
        imgui.end_disabled()
        imgui.text_wrapped(self.scripts.message)
        imgui.text_wrapped('Run saves the file, asking for a filename for unsaved scripts. '
                           'Stop terminates Python and sends device Stop; logging stays enabled. '
                           'Completion or errors leave the device and logging in their resulting state.')
        if self.document.error:
            imgui.text_wrapped(self.document.error)
        imgui.separator()
        imgui.text_unformatted(self.scripts.output)

    def _start_script(self, path, endpoint):
        try:
            if reason := self.block_reason('script'):
                raise RuntimeError(reason)
            if (endpoint != self.controller.endpoint or not self.update.attached or
                    not self.update.status.get('state', {}).get('connected')):
                raise RuntimeError('Service connection changed; connect and press Run again')
            self.controller.cancel_pending_commands()
            if not self.controller.commands_idle():
                raise RuntimeError('A device command is still running; wait for it to finish and press Run again')
            self.scripts.start(path, endpoint)
        except Exception as exc:
            self.document.error = str(exc)

    def _render_flash_confirmation(self):
        opened, _ = imgui.begin_popup_modal('Flash UltraZohm?', flags=imgui.WindowFlags_.always_auto_resize)
        if not opened:
            return
        imgui.text_wrapped('Send device Stop, finish fast and slow logging, flash the system, and reconnect?')
        imgui.text_wrapped('The acquisition service will restart with a fresh channel mapping.')
        if imgui.button('OK'):
            if not self.flash_available:
                self.error = 'Vitis XSCT (xsct) is not on PATH'
            elif self.cli_busy():
                self.error = 'Wait for running CLI commands to finish before flashing'
            else:
                endpoint = self.controller.endpoint if self.update.attached else self.endpoint
                self.send('flash', endpoint=endpoint or self.endpoint, ip=self.ip, port=self.port,
                          output=self.output, repo=self.repo)
            imgui.close_current_popup()
        imgui.same_line()
        if imgui.button('Cancel'):
            imgui.close_current_popup()
        imgui.end_popup()

    def maximum_depth(self):
        capacity = self.update.status.get('data_options', {}).get('buffer_samples', 300_000)
        period = self.update.catalog.get('sample_period_us', 100.)
        return max(.001, capacity * period * 1e-6)

    def inspect(self, limits=None):
        """Freeze the current bounded snapshot; acquisition continues independently."""
        self.follow, self.paused = False, True
        self.state.following_live = False
        for cell in self.state.cells:
            cell.pending_x_lim = None
        if limits is not None:
            self.state.shared_x = limits

    def resume_live(self):
        self.follow, self.paused = True, False
        self._revision = -1
        self.pump()

    def render_plots(self, main_state):
        changed, follow = imgui.checkbox('Follow live', self.follow and not self.paused)
        if changed:
            self.resume_live() if follow else self.inspect()
        imgui.same_line()
        if not self.follow or self.paused:
            if imgui.button('Resume live'):
                self.resume_live()
        else:
            if imgui.button('Inspect'):
                self.inspect()
        imgui.same_line()
        imgui.begin_disabled(self.run is None)
        if imgui.button('Freeze plot 1 for analysis'):
            try:
                self.freeze(main_state)
            except Exception as exc:
                self.error = str(exc)
        imgui.end_disabled()
        imgui.same_line()
        maximum = self.maximum_depth()
        imgui.set_next_item_width(180.)
        changed, seconds = imgui.slider_float('Time depth (s)', min(self.window_seconds, maximum),
                                       .001, maximum, '%.3f s')
        self.window_seconds = max(.001, min(maximum, seconds))
        if not self.follow or self.paused:
            imgui.text_disabled('Inspect — snapshot frozen; acquisition continues')
        imgui.text_disabled('Same mouse controls as Plots  |  Normal zoom: follow  |  Shift+zoom: inspect')
        if changed and not self.follow:
            for cell in self.state.cells:
                if self.state.is_time_plot(cell) and cell.x_lim is not None:
                    center = sum(cell.x_lim) / 2
                    cell.pending_x_lim = (center - self.window_seconds / 2, center + self.window_seconds / 2)
            self.state.shared_x = None
        self.state.following_live = self.follow and not self.paused
        if not self.run:
            imgui.text_wrapped('Connect, then drag channels from Live Data into these plots. History is bounded by the CLI RAM buffer; disk/cloud history is a later step.')
        elif self.follow and not self.paused:
            start, stop = self.run.source.metadata.time_range
            limits = (max(start, stop - self.window_seconds), max(start + .000001, stop))
            self.state.shared_x = limits
            for cell in self.state.cells:
                if self.state.is_time_plot(cell):
                    cell.pending_x_lim = limits
        self.plots.render(self.state)

    def close(self):
        self.controller.cancel_pending_commands()
        if self._xsct_dialog is not None:
            self._xsct_dialog.kill()
            self._xsct_dialog = None
        self.document.close()
        self.scripts.close()
        self.controller.close()
        self.state.shutdown()
