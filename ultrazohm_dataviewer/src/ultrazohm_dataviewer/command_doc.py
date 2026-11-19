"""Generate the public Python client reference from its actual method signatures."""

from __future__ import annotations

import csv
import inspect
import io
import pathlib

from .cli import public_methods

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
    "backend": "Data / runs",
    "loading_mode": "Data / runs",
    "clear_session": "Data / runs",
    "disk_cache": "Data / runs",
    "cache_budget": "Data / runs",
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
    "save_session": "Session",
    "load_session": "Session",
    "status": "Session",
    "get_settings": "Session",
    "set_setting": "Session",
    "list_runs": "Data / runs",
    "list_nodes": "Nodes",
    "list_plots": "Layout",
    "create_view": "Layout",
    "list_views": "Layout",
    "close_view": "Layout",
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


def build_csv() -> str:
    """Generate the same operation surface exposed by Python and terminal clients."""
    methods = sorted(
        public_methods().items(),
        key=lambda item: (GROUP_ORDER.index(group_for(item[0])), item[0]),
    )
    buf = io.StringIO()
    writer = csv.writer(buf, lineterminator="\n")
    writer.writerow(["Method", "Group", "Description", "Signature"])
    for name, method in methods:
        parameters = list(inspect.signature(method).parameters.values())[1:]
        signature = inspect.Signature(parameters)
        writer.writerow(
            [
                name,
                group_for(name),
                method.__doc__ or name.replace("_", " ").capitalize(),
                f"``viewer.{name}{signature}``",
            ]
        )
    return buf.getvalue()


# Committed CSV consumed by docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_usage.rst.
CSV_PATH = (
    pathlib.Path(__file__).resolve().parents[3]
    / "docs"
    / "source"
    / "guide"
    / "gui"
    / "ultrazohm_dataviewer"
    / "ultrazohm_dataviewer_commands.csv"
)


def main() -> None:
    CSV_PATH.write_text(build_csv(), encoding="utf-8")
    print(f"wrote {CSV_PATH}")


if __name__ == "__main__":
    main()
