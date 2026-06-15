"""Browser (Pyodide) integration helpers.

Everything here is a no-op on desktop. In the browser, native facilities differ:

* file dialogs -- ``portable_file_dialogs`` opens an OS dialog that does not
  exist in a tab, so the navigation button instead clicks a hidden HTML
  ``<input type="file">`` (see ``build/gen_web.py``). The JS ``change`` handler
  writes the chosen file into the Pyodide virtual filesystem and then calls
  :func:`load_uploaded` to load it.
* threads -- Pyodide has no usable worker threads by default, so file loading
  runs synchronously (see ``AppState.request_load``).

Web mode is detected via imgui_bundle's ``__bundle_pyodide__`` flag, which is
True only in the Pyodide wheel.
"""

from __future__ import annotations

try:
    from imgui_bundle import __bundle_pyodide__ as IS_WEB
except Exception:  # pragma: no cover - defensive; flag should always exist
    IS_WEB = False

# The running AppState, registered by the app so the JS->Python file bridge can
# reach it.
_active_state = None  # type: ignore[var-annotated]

FILE_INPUT_ID = "uzFileInput"


def register_state(state) -> None:
    global _active_state
    _active_state = state


def trigger_file_dialog() -> None:
    """Click the hidden HTML file input (browser only)."""
    if not IS_WEB:
        return
    import js  # type: ignore[import-not-found]

    element = js.document.getElementById(FILE_INPUT_ID)
    if element is not None:
        element.click()


def load_uploaded(path: str, note: str = "") -> None:
    """Load a file the browser wrote into the Pyodide FS. Called from JS.

    ``note`` carries an optional message (e.g. that the file was decimated on
    the way in because it was too large to fit in the browser's 32-bit WASM
    memory) to surface in the console.
    """
    if _active_state is None:
        return
    if note:
        _active_state.console.warn(note)
    _active_state.request_load(path)


def download(path: str, filename: str | None = None) -> None:
    """Trigger a browser download of a file in the Pyodide FS (web only).

    On desktop the Export buttons use an OS save dialog; in a tab there is none,
    so the file is written to the in-memory FS and handed to the browser as a
    download via a Blob + anchor click.
    """
    if not IS_WEB:
        return
    import js  # type: ignore[import-not-found]
    from pyodide.ffi import to_js  # type: ignore[import-not-found]

    with open(path, encoding="utf-8") as fh:
        text = fh.read()
    options = js.Object.new()
    options.type = "text/csv"
    blob = js.Blob.new(to_js([text]), options)
    url = js.URL.createObjectURL(blob)
    anchor = js.document.createElement("a")
    anchor.href = url
    anchor.setAttribute("download", filename or path.rsplit("/", 1)[-1])
    js.document.body.appendChild(anchor)
    anchor.click()
    anchor.remove()
    js.URL.revokeObjectURL(url)


def _to_numpy(buf, dtype):
    """Coerce a JS TypedArray (or anything array-like) to a numpy array."""
    import numpy as np

    if hasattr(buf, "to_py"):  # Pyodide JsProxy for a TypedArray -> memoryview
        buf = buf.to_py()
    return np.asarray(buf, dtype=dtype)


def load_columns(label: str, names, arrays, time) -> None:
    """Register a run from typed arrays parsed in the browser. Called from JS.

    The web loader stream-parses a large CSV directly into per-column typed
    arrays (full resolution), avoiding the multi-gigabyte text ever being held in
    32-bit WASM memory. ``names``/``arrays`` are parallel (raw channel header ->
    ``float32`` samples); ``time`` is the shared ``float64`` axis.
    """
    if _active_state is None:
        return
    from .loader import parse_channel_name

    t = _to_numpy(time, "float64")
    signals: dict = {}
    units: dict = {}
    for raw, arr in zip(list(names), arrays):
        raw = str(raw)
        name, unit = parse_channel_name(raw)
        if name in signals:  # guard duplicate friendly names
            name = raw
        signals[name] = _to_numpy(arr, "float32")
        units[name] = unit
    _active_state.add_run_from_arrays(label, label, t, signals, units)
