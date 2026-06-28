"""Generate the console-command reference for the documentation.

The commands are not importable functions but closures held in
:class:`~uz_dataviewer.commands.CommandRegistry` (see ``commands.py``), so the docs
table cannot be produced by ``sphinx.ext.autodoc``. Instead we walk the live
registry and emit a CSV that ``uz_dataviewer_usage.rst`` includes via
``.. csv-table:: :file:``.

The grouping (which command belongs under "FFT window", "Signals", …) is *not*
stored in the registry; it lives here in :func:`group_for`. Run

    python -m uz_dataviewer.command_doc

to regenerate the committed CSV. ``tests/test_command_doc.py`` fails the build if the
checked-in file drifts from what this module produces.
"""

from __future__ import annotations

import csv
import io
import os
import pathlib

from .commands import Command, CommandRegistry

# Column / section order for the rendered table.
GROUP_ORDER: list[str] = [
    "Data / runs",
    "Layout",
    "Signals",
    "View",
    "Tools",
    "FFT window",
    "Histogram window",
    "Nodes",
    "Session",
    "Console",
]

# Commands without a shared name prefix are grouped explicitly. The prefixed
# families (fft_*, hist_*, node_*) are handled by rule in :func:`group_for`.
_EXPLICIT_GROUPS: dict[str, str] = {
    # Data / runs
    "load": "Data / runs",
    "convert": "Data / runs",
    "remove_run": "Data / runs",
    "set_active": "Data / runs",
    "normalize_time": "Data / runs",
    "reset_time": "Data / runs",
    # Layout
    "set_grid": "Layout",
    "link_x": "Layout",
    "set_max_points": "Layout",
    # Signals
    "add_signal": "Signals",
    "remove_signal": "Signals",
    "clear_plot": "Signals",
    "set_plot_type": "Signals",
    "set_xy": "Signals",
    "set_xy_style": "Signals",
    "set_axis": "Signals",
    # View
    "set_x_lim": "View",
    "set_y_lim": "View",
    "reset_view": "View",
    # Tools
    "show_samples": "Tools",
    "cursors": "Tools",
    "set_cursors": "Tools",
    "spy": "Tools",
    "set_spy_rect": "Tools",
    "export_data": "Tools",
    "set_export_relative": "Tools",
    # Session
    "save_state": "Session",
    "load_state": "Session",
    "export_script": "Session",
    "run_script": "Session",
    # Console
    "help": "Console",
    "clear_console": "Console",
}


def group_for(name: str) -> str:
    """Return the documentation group for a command name.

    Raises :class:`KeyError` for an unrecognised command so a newly added command
    that nobody assigned a group is caught by the drift test.
    """
    if name == "fft" or name.startswith("fft_"):
        return "FFT window"
    if name == "histogram" or name.startswith("hist_"):
        return "Histogram window"
    if name == "load_plugins" or name.startswith("node_"):
        return "Nodes"
    try:
        return _EXPLICIT_GROUPS[name]
    except KeyError:
        raise KeyError(
            f"command {name!r} has no documentation group; add it to "
            "_EXPLICIT_GROUPS or a prefix rule in command_doc.group_for"
        ) from None


def _args(cmd: Command) -> str:
    """Render the parameter list as ``name:kind`` tokens (optional ones bracketed)."""
    parts = []
    for p in cmd.params:
        token = f"{p.name}:{p.kind}"
        parts.append(f"[{token}]" if p.optional else token)
    return ", ".join(parts)


def _source(cmd: Command) -> str:
    """Return the handler's source location as ``commands.py:NNN``."""
    code = cmd.handler.__code__
    return f"{os.path.basename(code.co_filename)}:{code.co_firstlineno}"


def build_csv() -> str:
    """Render the full command reference as CSV text."""
    reg = CommandRegistry()
    rows = []
    for cmd in reg.all():
        group = group_for(cmd.name)
        rows.append((GROUP_ORDER.index(group), cmd.handler.__code__.co_firstlineno, cmd))
    # Sort by group order, then source line so commands from one factory stay together.
    rows.sort(key=lambda r: (r[0], r[1], r[2].name))

    buf = io.StringIO()
    writer = csv.writer(buf, lineterminator="\n")
    writer.writerow(["Command", "Group", "Description", "Arguments", "Source"])
    for _, _, cmd in rows:
        writer.writerow([cmd.name, group_for(cmd.name), cmd.help, _args(cmd), _source(cmd)])
    return buf.getvalue()


# Committed CSV consumed by docs/source/guide/gui/uz_dataviewer/uz_dataviewer_usage.rst.
CSV_PATH = (
    pathlib.Path(__file__).resolve().parents[3]
    / "docs"
    / "source"
    / "guide"
    / "gui"
    / "uz_dataviewer"
    / "uz_dataviewer_commands.csv"
)


def main() -> None:
    CSV_PATH.write_text(build_csv(), encoding="utf-8")
    print(f"wrote {CSV_PATH}")


if __name__ == "__main__":
    main()
