# Using uz_dataviewer as a Python library (headless)

The data/analysis core runs **without a window**. You can load logs, compute FFTs, and
run the node transforms from a plain script or a notebook through the ergonomic façade
in [`uz_dataviewer.api`](../src/uz_dataviewer/api.py) — re-exported at the package top
level.

**Importing the package does not import the imgui GUI stack.** `import uz_dataviewer`
(and `uz_dataviewer.api` / `.analysis` / `.nodes`) needs only numpy/pandas/pyarrow; the
GUI (`DataViewerApp` / `main`) is loaded lazily, only when you actually access it. So the
core is usable on a headless server, and `import` stays fast.

## Quick start

```python
import uz_dataviewer as uz

data = uz.read("Log.csv")              # -> Dataset (shared time axis + named signals)
t, ia = data.time, data["ia"]

df = data.to_dataframe()               # pandas: column 'time' + one per signal

spec = uz.fft(t, ia)                   # -> FftResult (.freqs, .mag, .info, .ok); full span
sdf  = uz.fft_frame(t, ia)            # -> pandas DataFrame [frequency, amplitude]

# Node transforms — the exact calculations the GUI's node graph uses.
print(uz.kinds())                      # ('fft', 'math', 'filter', 'shift')
t2, y2, info = uz.node("filter", (t, ia), type="low", cutoff=40, taps=201)
```

A runnable version is in [`examples/headless_example.py`](../examples/headless_example.py).

## API surface

| Call | Returns | Notes |
|---|---|---|
| `read(path)` | `Dataset` | `.time`, `.signals`, `.units`, `.names`; `data["ia"]`, `in`, iter, `len`, `.to_dataframe()` |
| `fft(time, y, *, remove_dc=True, window=True, x_min=None, x_max=None)` | `FftResult` | full record unless a window is given |
| `fft_frame(time, y, **kw)` | `pandas.DataFrame` | `[frequency, amplitude]`; raises `ValueError` if it can't compute |
| `node(kind, *signals, **params)` | `(out_time, out_y, info)` | generic dispatch; `signals` are `(time, y)` tuples |
| `filter(time, y, **params)` | `(time, y, info)` | windowed-sinc FIR low/high/band-pass |
| `math(*signals, **params)` | `(time, y, info)` | scale/offset/derivative/integral/reciprocal, binary add/sub/mul/div |
| `kinds()` | `tuple[str, ...]` | available transform kinds |
| `load_plugins(dirs=None)` | `tuple[str, ...]` | opt into external `@transform` plugin kinds (builtins are always present) |

The façade adds no compute logic — it reuses `loader.parse_file`, `analysis.compute_fft`,
`nodes.REGISTRY` and `transforms.*`. For the full internals see
[ARCHITECTURE.md](ARCHITECTURE.md).
