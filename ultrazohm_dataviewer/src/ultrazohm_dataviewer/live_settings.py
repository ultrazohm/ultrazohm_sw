"""Explicitly saved live preferences; signal names survive service restarts."""

import json
from pathlib import Path

from .session import plot_cells_to_list, restore_plot_cells
from .settings import load_workspace_settings, profile_for_mapping
from .state import AppState
from .user_paths import write_json
from .validation import axis_limits, boolean, bounded_int, display_budget, finite_float


def plot_setup(state):
    return {
        "grid": [state.rows, state.cols],
        "row_ratios": list(state.row_ratios),
        "col_ratios": list(state.col_ratios),
        "link_x": state.link_x,
        "shared_x": state.shared_x,
        "max_points": state.max_points,
        "cells": plot_cells_to_list(state, lambda ref: ref[1] if ref else None),
    }


def restore_plots(state, data, resolve):
    state.set_grid(*data["grid"])
    state.set_grid_ratios(data["row_ratios"], data["col_ratios"])
    state.link_x = boolean(data["link_x"])
    state.shared_x = (
        axis_limits(*data["shared_x"]) if data.get("shared_x") is not None else None
    )
    state.max_points = display_budget(data["max_points"])
    state.plot_x_ranges.clear()
    # Saved plot cells replace the previous layout, including secondary axes.
    from .state import SubplotCell

    state.cells = [SubplotCell() for _ in range(state.cell_count)]
    restore_plot_cells(state, data, resolve)


def read_view(path):
    if not path.exists():
        return None
    data = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(data, dict) or data.get("version") != 1:
        raise ValueError("Unsupported live view settings version")
    for key in ("endpoint", "ip", "query", "variable_query"):
        if not isinstance(data[key], str):
            raise ValueError(f"Invalid live setting: {key}")
    bounded_int(data["port"], 1, 65535, "device port")
    if finite_float(data["window_seconds"]) <= 0:
        raise ValueError("Live time depth must be positive")
    boolean(data["follow"])
    if "output_parent" in data and not isinstance(data["output_parent"], str):
        raise ValueError("Invalid recording directory preference")
    values = data["variable_values"]
    if not isinstance(values, dict) or not all(
        isinstance(k, str) and isinstance(v, str) for k, v in values.items()
    ):
        raise ValueError("Invalid variable input preferences")

    def resolve(name):
        if name is None:
            return None
        if not isinstance(name, str) or not name:
            raise ValueError("Invalid saved live signal name")
        return (0, name)

    temporary = AppState()
    try:
        restore_plots(temporary, data["plots"], resolve)
    finally:
        temporary.shutdown()
    return data


def save_startup_profile(workspace):
    directory = workspace.user_directory()
    settings = (
        workspace._repository_settings
        if workspace._repository_settings is not None
        else load_workspace_settings(workspace.mapping, directory)
    )
    # These preferences start a LOCAL service. An attached service's catalog
    # does not establish compatibility with that local firmware checkout.
    # Refresh repository metadata because the preview may predate a flash/edit.
    if (
        workspace._repository_settings is not None
        and workspace.update.attached
        and workspace.update.assignments
    ):
        from .live_mapping import read_mapping

        mapping = read_mapping(workspace.repo)
    else:
        mapping = settings.mapping
    from .settings import read_runtime_settings

    saved_profile = read_runtime_settings(settings.path)
    assignments = None
    if workspace.update.attached and workspace.update.assignments:
        assignments = {
            str(item["channel"]): item["name"]
            for item in workspace.update.assignments
            if item["name"]
        }
    profile, removed = profile_for_mapping(mapping, saved_profile, assignments)
    if assignments is not None and removed:
        raise ValueError(
            "Cannot save channels absent from the selected firmware mapping: "
            + ", ".join(removed)
        )
    profile["sample_period_us"] = workspace.update.catalog.get(
        "sample_period_us", profile["sample_period_us"]
    )
    # Disconnected saves preserve the existing startup selections.
    from ultrazohm_cli.configuration import save_profile, startup_profile_path

    save_profile(
        startup_profile_path(directory=directory),
        profile if assignments is not None else saved_profile,
        mapping,
    )
    return directory


def save_view_preferences(workspace):
    """Save presentation preferences without requiring local firmware or a CLI profile."""
    directory = workspace.user_directory()
    view = {
        key: getattr(workspace, key)
        for key in (
            "endpoint",
            "ip",
            "port",
            "follow",
            "window_seconds",
            "query",
            "variable_query",
            "variable_values",
        )
    }
    view.update(
        version=1,
        output_parent=str(Path(workspace.output).expanduser().resolve().parent),
        plots=workspace._pending_plot_setup or plot_setup(workspace.state),
    )
    write_json(directory / "live_view.json", view)
    return directory
