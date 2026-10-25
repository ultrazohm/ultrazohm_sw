"""Browser (Pyodide) integration helpers.

Everything here is a no-op on desktop. In the browser, native facilities differ:

* file dialogs -- ``portable_file_dialogs`` opens an OS dialog that does not
  exist in a tab, so the navigation button instead clicks a hidden HTML
  ``<input type="file">`` (see ``build/gen_web.py``). The JS ``change`` handler
  writes the chosen file into the Pyodide virtual filesystem and then calls
  :func:`load_uploaded` to load it.
* threads -- Pyodide has no usable worker threads by default, so file loading
  runs synchronously (see ``AppState.request_load``).

Web mode is detected without importing the GUI, using the Emscripten platform.
"""

from __future__ import annotations

from . import runtime

# The running AppState, registered by the app so the JS->Python file bridge can
# reach it.
_active_state = None  # type: ignore[var-annotated]

UPLOAD_ROOT = "/uploads"
FILE_INPUT_ID = "uzFileInput"
SESSION_INPUT_ID = "uzSessionInput"


def register_state(state) -> None:
    global _active_state
    _active_state = state


def trigger_file_dialog() -> None:
    """Click the hidden HTML file input (browser only)."""
    if not runtime.IS_WEB:
        return
    import js  # type: ignore[import-not-found]

    element = js.document.getElementById(FILE_INPUT_ID)
    if element is not None:
        element.click()


def load_uploaded(path: str, note: str = "") -> None:
    """Load a file the browser wrote into the Pyodide FS. Called from JS.

    ``note`` carries an optional diagnostic message to surface in the console.
    """
    if _active_state is None:
        return
    if note:
        _active_state.console.warn(note)
    if not runtime.IS_WEB:
        _active_state.request_load(path)
        return
    # Browser loads are synchronous. Only accept ownership of upload paths,
    # never arbitrary files supplied through the command interface.
    from pathlib import Path
    upload = Path(path).resolve()
    if not upload.is_relative_to(Path(UPLOAD_ROOT)):
        raise ValueError("Expected a browser upload under /uploads")
    try:
        run = _active_state.load_sync(str(upload))
        if run is not None:
            run.reloadable = False
            if _active_state.loading_mode == "lazy":
                run.owned_upload = True
                return
    finally:
        if not any(r.owned_upload and r.path == str(upload) for r in _active_state.registry.runs):
            upload.unlink(missing_ok=True)
            if upload.parent != Path(UPLOAD_ROOT):
                try:
                    upload.parent.rmdir()
                except OSError:
                    pass


def trigger_session_open() -> None:
    """Click the hidden HTML session-file input (browser only).

    Separate from the data file input so an uploaded ``.json``/``.uzscript`` is
    routed to :func:`load_uploaded_session` (state restore / script replay)
    rather than to the data loader.
    """
    if not runtime.IS_WEB:
        return
    import js  # type: ignore[import-not-found]

    element = js.document.getElementById(SESSION_INPUT_ID)
    if element is not None:
        element.click()


def load_uploaded_session(path: str) -> None:
    """Load a session file the browser wrote into the Pyodide FS. Called from JS.

    Routes by extension: ``.json`` restores a state snapshot (``load_state``),
    anything else replays a command script (``run_script``). Both go through the
    command layer so the action is logged like any other.
    """
    if _active_state is None:
        return
    command = "load_state" if path.lower().endswith(".json") else "run_script"
    try:
        _active_state.commands.execute(_active_state, command, [path])
    except Exception as exc:  # noqa: BLE001 - surfaced to the console
        _active_state.console.error(str(exc))

    finally:
        if runtime.IS_WEB:
            from pathlib import Path
            upload = Path(path).resolve()
            if upload.is_relative_to(Path(UPLOAD_ROOT)):
                upload.unlink(missing_ok=True)


def download(path: str, filename: str | None = None) -> None:
    """Trigger a browser download of a file in the Pyodide FS (web only).

    On desktop the Export buttons use an OS save dialog; in a tab there is none,
    so the file is written to the in-memory FS and handed to the browser as a
    download via a Blob + anchor click.
    """
    if not runtime.IS_WEB:
        return
    import js  # type: ignore[import-not-found]
    from pyodide.ffi import to_js  # type: ignore[import-not-found]

    with open(path, encoding="utf-8") as fh:
        text = fh.read()
    name = filename or path.rsplit("/", 1)[-1]
    if name.endswith(".json"):
        mime = "application/json"
    elif name.endswith(".csv"):
        mime = "text/csv"
    else:
        mime = "text/plain"
    options = js.Object.new()
    options.type = mime
    blob = js.Blob.new(to_js([text]), options)
    url = js.URL.createObjectURL(blob)
    anchor = js.document.createElement("a")
    anchor.href = url
    anchor.setAttribute("download", name)
    js.document.body.appendChild(anchor)
    anchor.click()
    anchor.remove()
    js.URL.revokeObjectURL(url)


def save_and_download(state, name: str, emit) -> None:
    """Export to a fresh temporary path, downloading only on command success.

    ``emit`` must raise on failure or return False (SessionPanel._emit's contract).
    The browser Blob owns the bytes before the temporary directory is removed.
    """
    if not runtime.IS_WEB:
        return
    from pathlib import Path
    from tempfile import TemporaryDirectory

    try:
        with TemporaryDirectory(prefix="uz-export-") as directory:
            path = str(Path(directory) / name)
            if emit(path) is False:
                return
            download(path, name)
    except Exception as exc:  # GUI boundary
        state.console.error(str(exc))


def _to_numpy(buf, dtype):
    """Coerce a JS TypedArray (or anything array-like) to a numpy array."""
    import numpy as np

    if hasattr(buf, "to_py"):  # Pyodide JsProxy for a TypedArray -> memoryview
        buf = buf.to_py()
    return np.asarray(buf, dtype=dtype)


def load_columns(label: str, names, arrays, time, note: str = "") -> None:
    """Register a run from typed arrays parsed in the browser. Called from JS.

    The web loader stream-parses a large CSV directly into per-column typed
    arrays, avoiding the multi-gigabyte text ever being held in 32-bit WASM
    memory. ``names``/``arrays`` are parallel (raw channel header -> ``float32``
    samples); ``time`` is the shared ``float64`` axis. All samples are preserved; oversized
    files are rejected by the browser loader. ``note`` is an optional diagnostic.
    """
    if _active_state is None:
        return
    from .loader import _named_signals

    if note:
        _active_state.console.warn(note)
    t = _to_numpy(time, "float64")
    names, arrays = [str(name) for name in names], list(arrays)
    if not names or len(names) != len(arrays) or len(set(names)) != len(names):
        raise ValueError("CSV must contain distinct signal columns and matching arrays")
    columns = {name: _to_numpy(arr, "float32") for name, arr in zip(names, arrays)}
    if any(values.ndim != 1 or len(values) != len(t) for values in columns.values()):
        raise ValueError("Signal arrays must match the time axis")
    signals, units = _named_signals(names, columns.__getitem__)
    run = _active_state.add_run_from_arrays(label, label, t, signals, units)
    run.reloadable = False
