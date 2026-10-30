"""GUI exports use captured settings and background IO, with atomic publication."""
from copy import copy, deepcopy
from .console import Console
from .sources import check


def submit(state, handler, values):
    jobs = state.services.exports
    if jobs:
        raise ValueError('An export is already running; wait for it to finish')
    snapshot = copy(state)
    snapshot.cells = deepcopy(state.cells)
    # Rendering mutates this dictionary in place. Keep the windows from the
    # click, even if this job waits behind a load and the user keeps zooming.
    snapshot.plot_x_ranges = dict(state.plot_x_ranges)
    snapshot.fft = deepcopy(state.fft)
    snapshot.histogram = deepcopy(state.histogram)
    snapshot.registry = copy(state.registry)
    snapshot.registry._runs = {}
    for key, run in state.registry._runs.items():
        saved = copy(run)
        saved.signals = {name: copy(signal) for name, signal in run.signals.items()}
        saved.time = copy(run.time) if hasattr(run.time, 'source') else run.time
        snapshot.registry._runs[key] = saved
    snapshot.console = Console()
    def work(cancel):
        snapshot._export_cancel = cancel
        check(cancel)
        return handler(snapshot, values)
    jobs.append((state.services.executor.submit(work), snapshot))
    return 'Export started'


def poll(state):
    jobs = state.services.exports
    for future, snapshot in list(jobs):
        if future.done():
            jobs.remove((future, snapshot))
            state.console.extend_from(snapshot.console)
            try:
                message = future.result()
                if message:
                    state.console.ok(message)
            except Exception as exc:
                state.console.error(f'Export failed: {exc}')

    from .automation import poll as poll_replay
    poll_replay(state)
