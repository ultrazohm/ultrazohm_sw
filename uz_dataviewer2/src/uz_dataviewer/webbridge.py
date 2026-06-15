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
