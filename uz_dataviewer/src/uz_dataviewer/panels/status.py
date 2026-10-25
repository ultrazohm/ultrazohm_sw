"""Bottom status bar: loading controls on the left, usage on the right."""
from imgui_bundle import imgui

from .. import webbridge
from .base import SessionPanel


class StatusPanel(SessionPanel):
    def render(self, state):
        imgui.push_id('data_settings')
        backends = ['pyarrow'] if webbridge.IS_WEB else ['pyarrow', 'polars']
        labels = ['PyArrow'] if webbridge.IS_WEB else ['PyArrow', 'Polars']
        imgui.set_next_item_width(imgui.get_font_size() * 7)
        changed, backend = imgui.combo('Backend', backends.index(state.backend), labels)
        if changed:
            self._emit(state, 'backend', backends[backend])
        if imgui.is_item_hovered():
            imgui.set_tooltip('Applies to newly opened files. Existing runs keep their backend.')

        imgui.same_line()
        modes = ['memory', 'lazy']
        imgui.set_next_item_width(imgui.get_font_size() * 7)
        changed, mode = imgui.combo('Loading', modes.index(state.loading_mode), ['In memory', 'Lazy'])
        if changed:
            self._emit(state, 'loading_mode', modes[mode])
        if imgui.is_item_hovered():
            imgui.set_tooltip('Applies to files with backing storage; large browser-streamed CSVs remain in memory. '
                              'Existing runs keep their storage mode.')

        imgui.same_line()
        imgui.set_next_item_width(imgui.get_font_size() * 7)
        changed, mb = imgui.input_int('Cache (MiB)', state.registry.cache.limit // 1024**2)
        if changed:
            self._emit(state, 'cache_budget', max(1, mb))

        imgui.same_line()
        changed, enabled = imgui.checkbox('Disk cache', state.disk_cache)
        if changed:
            self._emit(state, 'disk_cache', enabled)
        if imgui.is_item_hovered():
            imgui.set_tooltip(
                'Cache indexes, summaries and CSV conversions in this tab; cleared on page reload. Reopen files to apply.'
                if webbridge.IS_WEB else
                'Save indexes, summaries and CSV conversions across restarts. Reopen files to apply.'
            )
        imgui.pop_id()

        imgui.same_line()
        imgui.align_text_to_frame_padding()
        cache = state.registry.cache.status()
        fps = imgui.get_io().framerate
        used = cache['bytes'] / 1024**2
        label = f"FPS: {fps:.1f}  |  RAM cache: {used:.1f} / {cache['limit'] / 1024**2:.0f} MiB"
        if cache['limit_hit']:
            label += '  |  cache limit hit'
        # Keep the settings and usage on one row without drawing over controls.
        right = imgui.get_window_width() - imgui.get_style().window_padding.x
        if imgui.calc_text_size(label).x > right - imgui.get_cursor_pos_x():
            label = f"FPS: {fps:.0f} | RAM: {used:.0f} MiB"
        imgui.set_cursor_pos_x(max(imgui.get_cursor_pos_x(), right - imgui.calc_text_size(label).x))
        if cache['limit_hit']:
            imgui.text_colored(imgui.ImVec4(1.0, 0.72, 0.25, 1.0), label)
        else:
            imgui.text_unformatted(label)
        if imgui.is_item_hovered():
            imgui.set_tooltip(
                f"RAM cache: {used:.1f} / {cache['limit'] / 1024**2:.0f} MiB; not total application memory.\n"
                'Limit hit is highlighted for 5 seconds after eviction or an oversized result.\n'
                f"Since cache clear: {cache['evictions']} entries evicted; "
                f"{cache['oversized']} oversized results not retained.\n"
                'Evicted data is reread or recomputed when needed; no measurement data is lost.')
