"""Dockable browser of local log files; directory scans never read log contents."""
from __future__ import annotations

from .. import runtime

import os
from pathlib import Path
import sys
from threading import Event

from imgui_bundle import imgui

from .navigation import LOG_DND_TYPE, pfd
from ..workers import CancellableExecutor


def default_log_directory() -> Path:
    """Find the checkout's javascope directory, including when started elsewhere."""
    starts = [Path.cwd(), Path(sys.executable).parent, Path(__file__).resolve().parent]
    for start in starts:
        for parent in (start, *start.parents):
            candidate = parent / "javascope"
            if candidate.is_dir():
                return candidate
    return Path.cwd() / "javascope"


def scan_logs(directory: Path, cancel: Event) -> tuple[list[Path], list[str]]:
    files, errors = [], []
    if cancel.is_set():
        return [], []
    if not directory.is_dir():
        return [], [f"Directory not found: {directory}"]
    for root, _, names in os.walk(directory, onerror=lambda error: errors.append(str(error))):
        if cancel.is_set():
            return [], []
        for name in names:
            if cancel.is_set():
                return [], []
            if Path(name).suffix.lower() in {".csv", ".parquet"}:
                path = Path(root) / name
                if path.is_file():
                    files.append(path.relative_to(directory))
    return sorted(files, key=lambda path: (str(path).casefold(), str(path))), errors


class LogBrowserPanel:
    def __init__(self, directory: Path | None = None):
        self.directory = directory.expanduser().resolve() if directory is not None else default_log_directory()
        self.files: list[Path] = []
        self.errors: list[str] = []
        self._dialog = None
        self._executor = None
        self._future = None
        self._cancel = Event()
        self._started = False
        self._open_path: str | None = None

    def refresh(self, directory: Path | None = None):
        self._cancel.set()
        if self._future is not None:
            self._future.cancel()
        self._cancel = Event()
        if directory is not None:
            self.directory = directory.resolve()
        self.files, self.errors = [], []
        if self._executor is None:
            self._executor = CancellableExecutor(name="log-browser")
        directory, request_cancel = self.directory, self._cancel

        def scan(cancel):
            # Refresh cancels this request independently of worker shutdown.
            # shutdown() sets both tokens; the executor also checks its token
            # before publishing a result.
            return scan_logs(directory, request_cancel)

        self._future = self._executor.submit(scan)
        self._started = True

    def shutdown(self):
        self._cancel.set()
        if self._executor is not None:
            self._executor.shutdown()

    def render(self, state):
        if runtime.IS_WEB:
            imgui.text_wrapped("Local directory browsing is available in the desktop app.")
            return
        if not self._started:
            self.refresh()
        if self._dialog is not None and self._dialog.ready():
            result = self._dialog.result()
            self._dialog = None
            if result:
                self.refresh(Path(result))
        if self._future is not None and self._future.done():
            try:
                self.files, self.errors = self._future.result()
            except Exception as exc:
                self.errors = [str(exc)]
            self._future = None
        imgui.begin_disabled(pfd is None or self._dialog is not None)
        if imgui.button("Open directory..."):
            self._dialog = pfd.select_folder("Choose log directory", str(self.directory))
        imgui.end_disabled()
        imgui.same_line()
        if imgui.button("Refresh"):
            self.refresh()
        imgui.text_wrapped(str(self.directory))
        if self._future is not None:
            imgui.text_disabled("Scanning...")
        else:
            imgui.text_disabled(f"{len(self.files)} logs · right-click to open or drag")
        for error in self.errors[:3]:
            imgui.text_wrapped(error)
        if not self.files and self._future is None and not self.errors:
            imgui.text_wrapped("No CSV or Parquet files found.")
        clicked_path = None
        if imgui.begin_child("log_files"):
            clipper = imgui.ListClipper()
            clipper.begin(len(self.files))
            while clipper.step():
                for index in range(clipper.display_start, clipper.display_end):
                    relative = self.files[index]
                    path = str(self.directory / relative)
                    imgui.push_id(index)
                    # Render paths as text so filenames containing ## remain visible.
                    # Selectable's hit box extends into the spacing around the row;
                    # its minimum corner is outside the text area's clip boundary.
                    text_position = imgui.get_cursor_screen_pos()
                    imgui.selectable("##log", False)
                    if imgui.is_item_clicked(imgui.MouseButton_.right):
                        clicked_path = path
                    imgui.get_window_draw_list().add_text(
                        text_position, imgui.get_color_u32(imgui.Col_.text), str(relative)
                    )
                    if imgui.begin_drag_drop_source():
                        state.dragged_log_path = path
                        imgui.set_drag_drop_payload_py_id(LOG_DND_TYPE, 0)
                        imgui.text_unformatted(str(relative))
                        imgui.end_drag_drop_source()
                    if imgui.is_item_hovered():
                        imgui.set_tooltip(path)
                    imgui.pop_id()
        imgui.end_child()
        if clicked_path is not None:
            self._open_path = clicked_path
            imgui.open_popup("open_log")
        if imgui.begin_popup("open_log"):
            imgui.text_unformatted(Path(self._open_path).name)
            imgui.text_disabled(f"Backend: {state.backend}")
            imgui.separator()
            if imgui.menu_item("Open lazy", "", False)[0]:
                state.request_load(self._open_path, loading_mode="lazy")
            if imgui.menu_item("Open in-memory", "", False)[0]:
                state.request_load(self._open_path, loading_mode="memory")
            imgui.end_popup()
