"""External node plugins: load user-written transform nodes at runtime.

A plugin is a plain ``.py`` file that registers one or more transforms with the
:func:`transform` decorator; once loaded, the new node kind is indistinguishable
from a builtin (it works through the canvas, commands, evaluation and sessions).

Example plugin (``~/.uz_dataviewer/nodes/movavg.py``)::

    import numpy as np
    from uz_dataviewer.plugins import transform, ParamSpec

    @transform("movavg", params={"width": "51"}, inputs=(1, 1),
               ui=[ParamSpec.int("width", "window (samples)")])
    def moving_average(inputs, params):
        t, y = inputs[0]
        w = max(1, int(float(params["width"])))
        return t, np.convolve(np.asarray(y, float), np.ones(w) / w, mode="same"), f"avg {w}"

Loading is **entirely optional and failure-tolerant**: with no plugin files and no
plugin directory present, the app runs exactly as before (only the builtins). A
broken plugin is logged and skipped; it never blocks startup.

Where plugins are looked for (a "setting" pointing at the location):

* ``$UZ_DATAVIEWER_PLUGINS`` -- one or more directories (``os.pathsep``-separated),
* ``~/.uz_dataviewer/nodes/`` -- the default user plugin folder.

Both are scanned only if they exist; either may be absent.
"""

from __future__ import annotations

import importlib.util
import os
import sys

from .nodes import REGISTRY, ParamSpec, TransformSpec, register_transform

__all__ = ["transform", "ParamSpec", "API_VERSION", "load_plugins", "plugin_dirs"]

# Bump if the plugin contract changes; plugins may check it.
API_VERSION = 1

ENV_VAR = "UZ_DATAVIEWER_PLUGINS"
DEFAULT_DIR = os.path.join(os.path.expanduser("~"), ".uz_dataviewer", "nodes")


def transform(kind, *, params=None, inputs=(1, 1), ui=(), unit=""):
    """Decorator: register ``fn(inputs, params) -> (out_time, out_y, info)`` as a
    transform node ``kind``. ``inputs`` is the ``(min, max)`` input arity; ``ui`` is
    a list of :class:`~uz_dataviewer.nodes.ParamSpec` for the generic canvas widgets.
    """

    def decorator(fn):
        register_transform(TransformSpec(
            kind=str(kind), compute=fn, params=dict(params or {}),
            inputs=tuple(inputs), ui=tuple(ui), unit=str(unit),
        ))
        return fn

    return decorator


def plugin_dirs(extra: list[str] | None = None) -> list[str]:
    """The directories to scan, in order (extras first, then env var, then default)."""
    dirs: list[str] = list(extra or [])
    env = os.environ.get(ENV_VAR, "")
    dirs += [d for d in env.split(os.pathsep) if d.strip()]
    dirs.append(DEFAULT_DIR)
    return dirs


def _load_file(path: str):
    name = "uz_plugin_" + os.path.splitext(os.path.basename(path))[0]
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise ImportError(f"cannot import {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)  # runs the @transform registrations
    return module


def load_plugins(dirs: list[str] | None = None, console=None) -> tuple[str, ...]:
    """Import every ``*.py`` in the plugin directories and return the newly
    registered kinds. Missing directories are skipped; a failing file is logged
    (if ``console`` is given) and skipped. Never raises.
    """
    search = dirs if dirs is not None else plugin_dirs()
    before = set(REGISTRY)
    for directory in search:
        if not directory or not os.path.isdir(directory):
            continue
        try:
            entries = sorted(os.listdir(directory))
        except OSError:
            continue
        for fname in entries:
            if not fname.endswith(".py") or fname.startswith("_"):
                continue
            try:
                _load_file(os.path.join(directory, fname))
            except Exception as exc:  # noqa: BLE001 - one bad plugin must not break startup
                if console is not None:
                    console.error(f"plugin {fname}: {exc}")
    new = tuple(k for k in REGISTRY if k not in before)
    if console is not None and new:
        console.ok(f"Loaded {len(new)} plugin node(s): {', '.join(new)}")
    return new
