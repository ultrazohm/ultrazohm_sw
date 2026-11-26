"""Synchronous application mutations shared by command adapters."""

from .validation import boolean, bounded_int


def set_grid(state, rows: int, cols: int):
    state.set_grid(rows, cols)


def link_x(state, enabled: bool):
    state.set_link_x(boolean(enabled))


def add_signal(state, plot: int, run: int, signal: str):
    plot = bounded_int(plot, 1, state.cell_count, "plot")
    if state.registry.get_signal(run, signal) is None:
        raise ValueError(f"run_{run} has no signal {signal!r}")
    cell = state.cells[plot - 1]
    domain = state.registry.get(run).axis_domain
    if any(
        state.registry.get(ref[0]).axis_domain != domain for ref in cell.active_refs
    ):
        raise ValueError("Cannot combine time and frequency axes in one plot")
    if not cell.signals:
        cell.pending_x_lim = cell.x_lim = None
        state.plot_x_ranges.pop(plot, None)
    cell.add((run, signal))
