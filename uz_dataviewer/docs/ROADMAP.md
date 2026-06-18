# Roadmap

Open ideas for the UltraZohm Data Viewer and the record of what's already shipped.
For how to use the app see **[USAGE.md](USAGE.md)**; for internals see
**[ARCHITECTURE.md](ARCHITECTURE.md)**.

This is the **single entry point** for future work: the table below is the index,
and the deep-dive files hold the detailed analysis (nodes, FFT, cloud data source).

---

## Open ideas

| Idea | Area | Status | Detail |
|------|------|--------|--------|
| **FFT as a plot type** (vs. the current dedicated window) | Plots | Deferred — the window was kept on purpose (per-frame transforms of a large window would tank fps; explicit *Compute* keeps it snappy). Revisit only if an inline spectrum cell is really wanted. | [ARCHITECTURE §13](ARCHITECTURE.md#13-design-decisions-in-brief) |
| **Polars for load/perf** | Loader | Idea — measure first; the hot paths (Arrow parse, NumPy pyramid/FFT) are already native, so the win may be small. | — |
| **3D flux maps from `pyuzlib`** | Plots | Idea — plot machine data with 3D flux maps. Larger feature; no design yet. | — |
| **ILA-mode (logic viewer)** | Loader/Plots | Idea — read ILA data (CSV or native) and show it as a logic-analyzer view. | — |
| **Node graph edges & polish** (input order, FFT x-axis label, unit propagation, name collisions, source-on-derived chaining) | Nodes | Open follow-ups, all low/low-medium severity — not core-path bugs. | [NODES_FUTURE_IDEAS.md](NODES_FUTURE_IDEAS.md) (items A–E) |
| **Inline-code nodes** (user Python typed into a node) | Nodes | Assessed, deferred — plugin files (Option B) shipped first; inline code would need a code-carrying command path + a trust model. | [NODES_FUTURE_IDEAS.md](NODES_FUTURE_IDEAS.md#custom-code-nodes-planned--feasibility-assessment) |
| **Fixed FFT bin count** (resample / Welch cap) | FFT | Idea — a user-set cap so huge windows compute cheaply. Welch vs. resample trade-offs worked out. | [FFT_FUTURE_IDEAS.md](FFT_FUTURE_IDEAS.md#part-2--fixed-number-of-frequency-bins-resample--welch) |
| **Move one-time `rfft` off the render thread** | FFT | Idea — kills the ~0.5 s *Compute* freeze on native (web has no worker threads). | [FFT_FUTURE_IDEAS.md](FFT_FUTURE_IDEAS.md) |
| **Cloud logs (authenticated file store)** | Loader | Proposed — serve logs from a PocketBase file store for native + web; client downloads and loads them through the existing pipeline (decimation stays client-side, local path untouched). | [REMOTE_DATA.md](REMOTE_DATA.md) |
| **Large logs in the web build (out-of-core)** | Loader | Analysis — wasm32's ~4 GB heap blocks big logs in the browser; out-of-core via an embedded DB or on-disk pyramid on OPFS is the fix (also removes the native RAM bound). Approach deferred. The **native** lean-loading path is now **shipped** (float32 channels, large-Parquet streaming, CSV size guard, CSV→Parquet `convert`); only the web/out-of-core route remains. | [WEB_LARGE_LOGS.md](WEB_LARGE_LOGS.md) |

---

## Shipped

Items from the original idea list that are now implemented (see USAGE/ARCHITECTURE):

- **Scriptable command API** — every click is a logged, replayable command; unified grammar.
- **Command console** — the bottom log shows commands and accepts command input, with
  completion and history.
- **Zoom/gesture echo** — e.g. a zoom emits `set_x_lim(plot_1, min, max)` to the log.
- **Save / restore state** — JSON snapshot and an editable, replayable `.uzscript`.
- **Nodes** — drag a signal into a canvas, apply a transform, get a new draggable signal;
  scriptable like everything else (`node_*`). Extensible via **plugins** ([PLUGINS.md](PLUGINS.md)).
- **More plot types** — XY plot; **Histogram** (as a dedicated window, like FFT).
- **Show samples** — per-sample markers on line plots.
- **Spy** — drag a rectangle; an inset below shows only that region.
- **MaterialFlat theme.**
- **Pyodide/web downsampling** — no longer needs a `tsdownsample` wheel: the decimator is
  a pure-NumPy min/max pyramid, so native and web share one code path.
