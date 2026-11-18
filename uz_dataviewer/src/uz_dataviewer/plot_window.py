"""Independent, session-local plot views over the application's recordings."""

from .console import Console
from .state import AppState


class _WindowConsole(Console):
    def __init__(self, parent, label):
        super().__init__()
        self.parent = parent
        self.label = label

    def _log(self, level, message):
        # These calls target a separate grid. Do not put them in the main
        # console's replayable command history, which targets the original grid.
        self.parent._log('INFO' if level == 'CMD' else level, f'[{self.label}] {message}')

    def extend_from(self, other):
        for entry in other._entries:
            self._log(entry.level, entry.message)


class PlotWindowState(AppState):
    """Own plot settings and workers, but borrow recordings and their cache.

    The application closes these views when replacing the main session. They
    must never release uploads or clear the shared recording cache themselves.
    """

    def __init__(self, parent, window_id):
        super().__init__()
        self.plot_window_id = window_id
        self.registry = parent.registry
        self.console = _WindowConsole(parent.console, f'Plots {window_id}')
        self.async_exports = parent.async_exports
        self._domains = {run.id: run.axis_domain for run in self.registry.runs}

    def sync(self, parent):
        self.dragged_ref = parent.dragged_ref
        self.backend = parent.backend
        domains = {run.id: run.axis_domain for run in self.registry.runs}
        changed = {key for key in self._domains if domains.get(key) != self._domains[key]}
        for index, cell in enumerate(self.cells, 1):
            for ref in list(cell.signals):
                if ref[0] in changed or self.registry.get_signal(*ref) is None:
                    cell.remove(ref)
                    cell.x_lim = cell.pending_x_lim = None
                    self.plot_x_ranges.pop(index, None)
            if cell.xy_source and (cell.xy_source[0] in changed
                                   or self.registry.get_signal(*cell.xy_source) is None):
                cell.xy_source = None
                cell.fit_pending = True
        self._domains = domains
        self.poll_pending_loads()

    def shutdown(self):
        if self.services is not None:
            self.services.close()
            self.services = None
