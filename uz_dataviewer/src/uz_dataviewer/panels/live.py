"""Live controls and a dedicated workspace sharing the existing plot renderer."""
from __future__ import annotations

import importlib.util
import time

from imgui_bundle import imgui, implot

from ..live import LiveController, fuzzy_names, new_output_directory
from ..model import Signal
from ..sources import SourceColumn, shift_time
from ..state import AppState
from .plots import PlotsPanel

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
            super()._setup_shared_x(state, index, cell)

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
    def __init__(self, controller=None):
        self.controller = controller or LiveController()
        self.state = AppState()
        self.state.registry.cache.limit = 64 * 1024**2
        self.plots = LivePlotsPanel(self)
        self.endpoint = '127.0.0.1:19740'
        self.ip = '192.168.1.233'
        self.port = 1000
        self.output = new_output_directory()
        self.mapping = ''
        self.follow = True
        self.paused = False
        self.window_seconds = 2.
        self.query = ''
        self.selected_slot = None
        self.variable = ''
        self.variable_query = ''
        self.variable_value = 0.
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

    def send(self, operation, **kwargs):
        try:
            if operation in ('connect', 'attach'):
                self.pending_message = 'Connecting…' if operation == 'connect' else 'Attaching to service…'
                self._pending_completion = self.controller.latest().completed_commands + 1
            self.controller.submit(operation, **kwargs)
            self.error = ''
        except Exception as exc:
            self.error = str(exc)
            self.pending_message = ''

    def pump(self, main_state=None):
        update = self.controller.latest()
        self.update = update
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
        if imgui.button('Connecting…' if activity else 'Connect'):
            self.send('connect', endpoint=self.endpoint, ip=self.ip, port=self.port,
                      output=self.output, mapping=self.mapping)
        imgui.same_line()
        if imgui.button('Attach service'):
            self.send('attach', endpoint=self.endpoint)
        if imgui.is_item_hovered():
            imgui.set_tooltip('Attach to an existing CLI service without connecting or changing the device.')
        imgui.end_disabled()
        if imgui.collapsing_header('Service settings (used when launching)'):
            _, self.output = imgui.input_text('New session directory', self.output)
            _, self.mapping = imgui.input_text('Channel mapping JSON (optional)', self.mapping)
            imgui.text_wrapped('Connect attaches to an existing service, or launches one if unavailable. Existing service settings take precedence.')
        state = self.update.status.get('state', {})
        imgui.separator()
        imgui.text_unformatted('Service: ' + ('attached' if self.update.attached else 'detached'))
        imgui.text_unformatted('Device: ' + ('connected' if state.get('connected') else 'disconnected'))
        imgui.text_unformatted('Platform: ' + str(state.get('platform_state') or 'unknown'))
        if self.update.received_at:
            age = time.monotonic() - self.update.received_at
            imgui.text_unformatted(f'Last data: {age:.1f}s ago' + (' — STALE' if age > 1 else ''))
        if self.run:
            imgui.text_unformatted(f'Visible RAM: {self.run.n_rows:,} samples / {self.run.duration:.2f}s')
        profile = self.update.catalog
        if profile:
            imgui.text_wrapped('Mapping: ' + profile.get('channel_mapping_name', ''))
        if state.get('error'):
            imgui.text_wrapped('Device error: ' + str(state['error']))
        if self.update.error or self.error:
            imgui.text_wrapped('Error: ' + (self.error or self.update.error))
        if self.update.notice:
            imgui.text_wrapped(self.update.notice)
        imgui.separator()
        logging = self.update.status.get('logging', {})
        if imgui.collapsing_header('Logging'):
            self._render_logging(main_state, state)
        imgui.separator()
        imgui.text_wrapped('Drag a channel into Live Plots. Double-click to change its observable.')
        locked = any(v.get('phase') == 'recording' for v in logging.values())
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
        imgui.separator()
        if imgui.button('Detach viewer'):
            self.send('detach')
        imgui.same_line()
        if imgui.button('Shutdown service'):
            self.send('shutdown')
        imgui.text_wrapped('Closing or detaching the viewer leaves logging running. Shutdown finalizes logs; it does not send device Stop.')

    def _render_logging(self, main_state, state):
        logging = self.update.status.get('logging', {})
        imgui.begin_disabled(not self.update.attached or not state.get('connected'))
        for stream, title, start, stop in (
            ('fast', 'Fast logging', 'start_logging', 'stop_logging'),
            ('slow', 'Slow logging', 'start_logging_slow_data', 'stop_logging_slow_data')):
            info = logging.get(stream, {})
            phase = info.get('phase', 'idle')
            imgui.text_unformatted(f'{title}: {phase}')
            imgui.begin_disabled(phase not in ('idle', 'complete', 'failed'))
            if imgui.button('Start##' + stream):
                self.send(start)
            imgui.end_disabled()
            imgui.same_line()
            imgui.begin_disabled(phase != 'recording')
            if imgui.button('Stop logging##' + stream):
                self.send(stop)
            imgui.end_disabled()
            if info.get('parquet'):
                imgui.text_wrapped(str(info['parquet']))
            if info.get('error'):
                imgui.text_wrapped(str(info['error']))
        imgui.end_disabled()
        for item in self.update.status.get('logging', {}).values():
            path = item.get('parquet')
            if item.get('phase') == 'complete' and path:
                if imgui.button('Open completed log##' + path):
                    main_state.request_load(path)

    def render_control(self):
        state = self.update.status.get('state', {})
        imgui.text_unformatted('Platform: ' + str(state.get('platform_state') or 'unknown'))
        imgui.begin_disabled(not self.update.attached or not state.get('connected'))
        for label, operation in [('Enable System', 'enable_system'), ('Enable Control', 'enable_control'), ('Stop', 'stop')]:
            if imgui.button(label):
                self.send(operation)
            imgui.same_line()
        imgui.new_line()
        for number in range(1, 9):
            if imgui.button(f'User {number}'):
                self.send('button', number=number)
            if number % 4:
                imgui.same_line()
        imgui.separator()
        _, self.variable_query = imgui.input_text('Find variable', self.variable_query)
        names = fuzzy_names(self.update.catalog.get('variables', {}), self.variable_query)
        if imgui.begin_combo('Variable', self.variable or 'Select variable'):
            for name in names:
                if imgui.selectable(name, self.variable == name)[0]:
                    self.variable = name
            imgui.end_combo()
        _, self.variable_value = imgui.input_float('Value', self.variable_value)
        imgui.begin_disabled(not self.variable)
        if imgui.button('Send variable'):
            self.send('set_variable', name=self.variable, value=self.variable_value)
        imgui.end_disabled()
        imgui.end_disabled()
        imgui.text_wrapped('Device commands are sent without acknowledgment. Platform state is observed from streamed status. Error Reset is not implemented by the current firmware.')
        if self.update.error or self.error:
            imgui.text_wrapped('Error: ' + (self.error or self.update.error))

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
            imgui.same_line()
            imgui.text_disabled('Inspect — snapshot frozen; acquisition continues')
        else:
            if imgui.button('Inspect'):
                self.inspect()
        maximum = self.maximum_depth()
        changed, seconds = imgui.slider_float('Time depth (s)', min(self.window_seconds, maximum),
                                       .001, maximum, '%.3f s')
        self.window_seconds = max(.001, min(maximum, seconds))
        imgui.text_disabled('Same mouse controls as Plots  |  Normal zoom: follow  |  Shift+zoom: inspect')
        if changed and not self.follow:
            for cell in self.state.cells:
                if self.state.is_time_plot(cell) and cell.x_lim is not None:
                    center = sum(cell.x_lim) / 2
                    cell.pending_x_lim = (center - self.window_seconds / 2, center + self.window_seconds / 2)
            self.state.shared_x = None
        self.state.following_live = self.follow and not self.paused
        imgui.begin_disabled(self.run is None)
        if imgui.button('Freeze plot 1 for analysis'):
            try:
                self.freeze(main_state)
            except Exception as exc:
                self.error = str(exc)
        imgui.end_disabled()
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
        self.controller.close()
        self.state.shutdown()
