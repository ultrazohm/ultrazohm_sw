"""GUI-independent analysis request construction and input identity."""
from .analysis import AnalysisInput, FftRequest, HistogramRequest
from .sources import validation_error


def config(state, kind):
    return state.fft if kind == 'fft' else state.histogram


def source_error(state, cfg):
    sources = []
    for ref in cfg.sources:
        run = state.registry.get(ref[0])
        if run is None or ref[1] not in run.signals:
            return 'Analysis source is no longer loaded'
        if run.axis_domain != 'time':
            return 'Analysis windows require a time-domain recording'
        sources.append(run.data_source())
    return validation_error(sources, state.services.validation_jobs)


def fingerprint(state, kind):
    cfg = config(state, kind)
    try:
        window = state.resolve_x_window(cfg.follow_plot, (cfg.x_min, cfg.x_max), cfg.sources)
    except ValueError:
        window = (cfg.x_min, cfg.x_max)
    versions = tuple((ref, state.registry.get(ref[0]).time_version,
                      state.registry.get_signal(*ref).version)
                     for ref in cfg.sources if state.registry.get_signal(*ref) is not None)
    options = (cfg.remove_dc, cfg.window) if kind == 'fft' else (cfg.bins,)
    return (versions, *window, source_error(state, cfg), *options)


def request(state, kind, limits=None):
    cfg = config(state, kind)
    if limits is None:
        limits = state.resolve_x_window(cfg.follow_plot, (cfg.x_min, cfg.x_max), cfg.sources)
    inputs = AnalysisInput.capture(state.registry, cfg.sources)
    if kind == 'fft':
        return FftRequest(inputs, limits, cfg.remove_dc, cfg.window, state.registry.cache)
    return HistogramRequest(inputs, limits, cfg.bins)
