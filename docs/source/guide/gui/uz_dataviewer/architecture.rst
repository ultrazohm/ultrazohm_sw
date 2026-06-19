.. _uz_dataviewer_architecture:

==================================
Architecture & Design (developer)
==================================

This document explains how ``uz_dataviewer`` is put together, the design decisions
behind it, and how to extend it. For end-user docs see :doc:`usage`; for packaging
see :doc:`build`.

1. The one big idea
===================

The viewer is **state-driven and command-routed**:

- There is a single source of truth, ``AppState`` (``state.py``). Panels are (almost)
  pure render functions: each frame they read ``AppState`` and draw it.
- **Every discrete user action goes through the command registry** (``commands.py``).
  A command mutates ``AppState`` *and* echoes its canonical call to the console.

Because of this, four things fall out for free:

#. **Scriptability** — anything you can click, you can type or replay (``.uzscript``).
#. **A live transcript** — the console shows exactly what happened, as commands.
#. **Save/restore** — sessions serialise to JSON or to a replayable command script.
#. **Testability** — the whole app logic is exercised by dispatching command strings;
   no window required.

.. note::

   If you add a feature and the only way to trigger it is a direct widget mutation,
   you've broken the model. Add a command and have the widget call it.

2. Frame flow
=============

``immapp.run()`` (hello_imgui) drives a classic immediate-mode loop. Per frame:

.. code-block:: text

   pre_new_frame()                      # app.py: poll async loads, focus requests, file dialogs
   └─ docking layout renders each DockableWindow's gui_function:
      ├─ NavigationPanel.render(state)  # left: runs + signals + normalize menu
      ├─ PlotsPanel.render(state)       # center: subplot grid
      ├─ FftPanel.render(state)         # center tab: FFT window
      ├─ HistogramPanel.render(state)   # center tab: Histogram window
      ├─ NodesPanel.render(state)       # center tab: node canvas
      └─ Console.render(state)          # bottom: log + command input

Immediate mode has one structural consequence the code leans on everywhere:
**there is no retained widget state**, so anything that must persist across frames
lives in ``AppState``/``SubplotCell``. Transient "do this once next frame" requests use
a **pending-flag pattern**: e.g. ``cell.fit_pending``, ``cell.pending_x_lim``,
``cfg.compute_requested``. The renderer consumes and clears the flag.

3. Module map
=============

.. list-table::
   :header-rows: 1
   :widths: 25 45 30

   * - Module
     - Responsibility
     - Key types
   * - ``app.py``
     - Docking layout, ``immapp`` runner, theme, Session menu, ``.uzscript``/file
       startup
     - ``DataViewerApp``
   * - ``api.py``
     - GUI-free façade for headless/library use (load, FFT, node transforms) — see
       :doc:`library`
     - ``read``, ``Dataset``, ``fft``, ``fft_frame``, ``node``, ``kinds``
   * - ``state.py``
     - The single app state, grid/cells, analysis configs, async load orchestration
     - ``AppState``, ``SubplotCell``, ``PlotType``,
       ``AnalysisConfig``/``FftConfig``/``HistogramConfig``
   * - ``commands.py``
     - Command registry, parser, dispatcher, the ~60 built-in commands
     - ``CommandRegistry``, ``Command``, ``Param``
   * - ``console.py``
     - Bottom console: scrolling selectable log + command input/completion/history
     - ``Console``
   * - ``model.py``
     - Loaded data + per-log time normalization
     - ``Run``, ``Signal``, ``DataRegistry``
   * - ``loader.py``
     - CSV (Arrow) / Parquet loading, header cleaning, delimiter sniffing; lean
       large-log loading (float32-at-parse, CSV size guard, streaming Parquet,
       CSV→Parquet ``convert``) — see §4a
     - ``load_file``, ``parse_file``, ``ParsedRun``, ``parse_channel_name``,
       ``convert_csv_to_parquet``
   * - ``downsample.py``
     - Range-aware decimation: min/max pyramid + one-shot (pure NumPy)
     - ``Pyramid``, ``decimate_range``, ``visible_slice``
   * - ``analysis.py``
     - GUI-free transforms (FFT)
     - ``compute_fft``, ``FftResult``
   * - ``transforms.py``
     - GUI-free node transforms (math, FIR filter), pure NumPy
     - ``math_node``, ``filter_node``
   * - ``nodes.py``
     - Dataflow graph + on-demand evaluation → derived runs; the transform
       **registry**
     - ``NodeGraph``, ``Node``, ``evaluate``, ``is_stale``, ``TransformSpec``,
       ``REGISTRY``
   * - ``plugins.py``
     - Load external transform-node plugins (``@transform``); robust to missing
       dirs/files
     - ``transform``, ``ParamSpec``, ``load_plugins``
   * - ``session.py``
     - JSON save/restore, ``.uzscript`` export/replay, CSV exports
     - ``to_dict``/``apply_dict``, ``export_*``
   * - ``webbridge.py``
     - Browser integration (file input, array load, downloads)
     - ``IS_WEB``, ``load_columns``, ``download``
   * - ``panels/navigation.py``
     - Left tree, drag sources, file dialog, normalize menu
     - ``NavigationPanel``
   * - ``panels/plots.py``
     - Subplot grid: types, cursors, spy, axis linking, secondary axis, export
     - ``PlotsPanel``
   * - ``panels/analysis.py``
     - Shared base for analysis windows (sources, follow-window, compute, stale, zoom,
       export)
     - ``AnalysisPanel``, ``follow_combo``
   * - ``panels/fft.py``
     - FFT window
     - ``FftPanel(AnalysisPanel)``
   * - ``panels/histogram.py``
     - Histogram window
     - ``HistogramPanel(AnalysisPanel)``
   * - ``panels/nodes.py``
     - Node canvas (``imgui_node_editor``) issuing ``node_*`` commands
     - ``NodesPanel``

4. Data model
=============

- A **``Run``** is one loaded file: a shared ``time`` axis (``float64``) plus one
  **``Signal``** per channel (``y`` as ``float32``, contiguous, ready for ImPlot and
  the pyramid).
- **``DataRegistry``** owns runs and hands out stable integer ids;
  ``SignalRef = (run_id, name)`` identifies a signal everywhere.
- **Time normalization** is per-log: ``Run.set_time_origin(target)`` keeps the original
  ``time_raw`` and derives ``time = time_raw - time_raw[0] + target``. It's reversible
  (``target=None`` restores raw) and only re-derives on change, never per frame.

Channel headers like ``CH8=8)ia`` are cleaned to ``ia`` by ``parse_channel_name``,
which also detects a trailing unit token (``_rpm``, ``_us``, …) for axis labels.

.. _uz_dataviewer_loader_large_logs:

4a. Loading & large logs (``loader.py``)
========================================

``load_file`` dispatches by extension through ``parse_file`` → ``parse_csv`` /
``parse_parquet``, each returning a ``ParsedRun`` (plain arrays, no registry touch)
that is then turned into a ``Run`` via ``ParsedRun.register`` (``DataRegistry.add_run``).
On native, loads run on a ``ThreadPoolExecutor``: the worker only **parses** into a
``ParsedRun``, and the main thread **registers** it in ``state.poll_pending_loads``, so
``DataRegistry`` is only ever mutated from one thread (see §10). The loader is built to
keep the **load-time memory peak** near the resident dataset size, so ~100M-point logs
open without OOM:

- **float32 at parse, no intermediate copy.** ``_csv_column_types`` feeds Arrow
  ``ConvertOptions(column_types=…)`` so channels parse straight to ``float32`` (time
  stays ``float64``) — avoiding the float64→float32 re-cast that used to double the
  channel memory. ``_named_signals`` then shares one naming/dedup pass across every
  load path.
- **Streaming CSV.** For files at/above ``CSV_STREAM_MIN_BYTES``,
  ``_parse_csv_streaming`` reads via Arrow's ``open_csv`` batch reader into
  **preallocated** numpy arrays (grown geometrically since a CSV's row count isn't
  known up front), ``include_columns`` projecting to just the named columns. Peak ≈
  resident + one batch (~1.5×) instead of the bulk ``read_csv`` peak (~4× the resident
  size, measured). Small CSVs keep the fast multithreaded bulk path.
- **Releasing Arrow's pool.** After every parse, ``parse_file`` calls
  ``_release_arrow_pool`` (``pa.default_memory_pool().release_unused()``): Arrow retains
  freed parse scratch rather than returning it to the OS, so RSS otherwise stays pinned
  at the parse high-water mark (measured ~1.2 GB reclaimed on the 9M-row log, ~10 GB on
  the 75M).
- **CSV size guard.** ``_guard_csv_size`` estimates the resident footprint from file
  size × column count and **refuses** a CSV above ``MAX_CSV_NUMERIC_BYTES``. Now that
  large CSVs stream, this is a **resident-RAM** ceiling (the full record must still fit
  in memory), not a bulk-parse guard; it routes the user to ``convert(...)`` or fewer
  channels.
- **Streaming Parquet.** For files above ``PARQUET_STREAM_MIN_ROWS``,
  ``_parse_parquet_streaming`` reads the exact row count from
  ``ParquetFile.metadata.num_rows``, **preallocates** the output arrays, and fills them
  with ``iter_batches`` (peak ≈ resident + one row group, ~1.5× measured) instead of
  materialising the whole table. Small Parquet keeps the simple bulk path.
- **CSV→Parquet converter.** ``convert_csv_to_parquet`` stream-converts a CSV to Parquet
  with bounded memory (per-batch ``ParquetWriter.write_batch``), dropping JavaScope's
  empty trailing column and preserving raw headers so the result round-trips through the
  same name parsing. Exposed as the scriptable ``convert(src, [dst])`` command and the
  ``uz-dataviewer convert`` CLI.

The data stays **in RAM**, so FFT / histogram / node transforms still operate on the
full record. Lifting the in-RAM bound entirely (out-of-core, web's hard ~4 GB case) is
deferred — see :doc:`web_large_logs`.

5. The command layer
====================

``CommandRegistry`` holds ``Command``s (a name, typed ``Param``s, a handler, help). The
grammar is a single function call, ``name(arg, arg, ...)`` (``parse_call``).

- **Param kinds** drive both coercion and canonical formatting: ``int``, ``float``,
  ``bool``, ``str``, ``plot`` (``plot_1``↔index), ``run`` (``run_2`` or a file label),
  ``fwindow`` (``custom``/``full``/``plot_N`` for analysis windows).
- **Three entry points**:

  - ``execute(state, name, args)`` — used by UI handlers; coerces, runs, **echoes** the
    canonical call.
  - ``dispatch(state, text)`` — used by the console/scripts; parses then executes;
    errors go to the console.
  - ``echo(state, name, values)`` — logs a command **without** running it. Used for
    continuous gestures (zoom, cursor/spy drag) that ImPlot has *already* applied — the
    echo settles once on mouse-up rather than firing every frame.
- **Run resolution by label** is what lets scripts say
  ``add_signal(plot_1, Log.csv, ia)`` and survive run-id reassignment after a reload.

Panels never mutate ``AppState`` for a user action directly; they call
``state.commands.execute(...)`` (often via a small ``self._emit`` wrapper that logs
errors). This is the invariant that keeps everything scriptable.

6. Plots panel internals (``panels/plots.py``)
==============================================

A runtime grid of ``SubplotCell``s. Cell types: ``line`` / ``scatter`` / ``stairs``
(time series) and ``xy`` (one signal vs another). FFT and Histogram are **separate
windows**, not cell types.

Per time-series cell, each frame:

#. Compute the data extent and apply any **pending** axis limits (``fit_pending``,
   ``pending_x_lim``, ``pending_y_lim``) with ``Cond_.Always``.
#. **Linked X:** the hovered cell becomes the ``_driver`` and publishes its X range to
   ``state.shared_x``; followers lock to it. Every time-series cell also publishes its
   own range to ``state.plot_x_ranges[plot_n]`` (used by analysis windows' "follow
   plot_N").
#. **Downsample** each signal to ~``max_points`` over the visible window
   (``decimate_range``, fed by ``visible_slice``) — this is what keeps multi-GB logs
   interactive. Note **XY cells are the exception**: they decimate by plain uniform
   stride (``_xy_stride``), *not* a min/max envelope, so a busy Lissajous figure can
   alias — acceptable for the phase-portrait use case but worth knowing.
#. Draw it (line/scatter/stairs), optionally with per-sample markers (``Spec.marker``),
   routing the left/right (secondary ``ImAxis_.y2``) axis per signal.
#. **Cursors** (two ``drag_line_x``) and **spy** (``drag_rect`` + a ``canvas_only``
   inset) draw on top. Their readouts and rectangles are computed cheaply and only
   recomputed on move.
#. **Zoom echo:** when a pan/zoom settles, ``echo set_x_lim(plot_n, ...)``.

.. note::

   **Performance landmine (documented in code):** cursor readouts originally used
   ``np.interp``, which **up-casts the entire ``float32`` signal to ``float64`` on every
   call** — ~150 ms/frame on a 5 M-point log. It was replaced with an O(log n)
   ``searchsorted`` lookup (``_value_at``) that touches only the two bracketing samples.

7. Analysis windows (``panels/analysis.py``)
============================================

FFT and Histogram share ``AnalysisPanel``. Subclasses set a command ``prefix``
(``fft``/``hist``) and a ``compute_command``, then implement ``_compute``, ``_draw``,
``_options_key``, and any ``_extra_controls``. The base provides:

- A **sources list** fed by drag-drop (``*_source`` command) and the legend "Remove"
  (``*_remove``).
- A **time-window selector** (``follow_combo``): ``Custom`` (``0``), ``Full`` (``-1``),
  or ``plot_N`` (``≥1``), resolved by ``AppState.resolve_x_window``. Switching to a plot
  computes immediately; switching to Custom/Full does **not** (the window can be the
  whole log).
- **On-demand compute only** — never per frame. A compute happens on the *Compute*
  button, on a drag-in, or once when an input changes (``compute_requested``). Following
  a plot and then panning it goes **stale** rather than recomputing.
- A **stale indicator**: a ``_computed_key`` snapshot (sources + window + options) is
  compared to the current key each frame; mismatch shows "⚠ stale - press Compute".
- **Every control routed through commands** (``fft_follow``, ``fft_remove_dc``,
  ``hist_bins``, ``*_xlim`` on zoom, ``*_export``, …) and **Export** (OS dialog on
  desktop, browser download on web).

This is why "absolutely everything is a command" holds for the analysis windows too.

.. _uz_dataviewer_node_graph:

7a. Node graph
==============

(``nodes.py``, ``transforms.py``, ``panels/nodes.py``)

A small dataflow engine, deliberately built as a **derived-signal factory**: a
transform node, when evaluated, materializes its result as a *new run* in the
registry (``Run.derived=True``) via ``AppState.upsert_derived_run``. That derived
signal then flows through the **existing** app unchanged — it shows in Navigation
and is draggable into plots / FFT / Histogram. Nodes *produce* data; nothing else
in the app needs to know they exist.

- **Graph** (``NodeGraph``) of ``Node``s: a **source** wraps a ``(run, signal)`` ref; a
  **transform** (``fft`` / ``math`` / ``filter`` / ``shift``) pulls arrays from its
  inputs and computes. Links are validated against cycles; ids are persisted so
  derived-run labels (= node name) are stable across save/restore.
- **On-demand evaluation** (``evaluate``): topological order; each transform reads its
  inputs (a source from the registry, an upstream transform from its cache), computes
  via ``transforms``/``analysis``, bumps a ``version``, and upserts its derived run **in
  place** (so plot references survive a re-eval). Per-node errors are logged and
  skipped, not fatal. A node is **stale** (``is_stale``) when its key — params + each
  input's version/identity — differs from the last evaluated key (the same idea as
  the analysis windows' ``_computed_key``).
- **GUI-free + scriptable**: ``nodes.py``/``transforms.py`` import no GUI and raise
  plain ``ValueError``s, so the whole engine is driven and tested from command strings.
  The canvas (``panels/nodes.py``, ``imgui_node_editor``) is a thin layer that **only
  issues ``node_*`` commands** — drag-drop → ``node_source``, link → ``node_link``, a
  widget → ``node_set``, a drag → ``node_pos``, the button → ``node_eval``. So the graph
  round-trips through the console, ``.uzscript``, and the JSON session like everything
  else.
- **Transforms are pure NumPy** (windowed-sinc FIR filter, not SciPy) so native and
  web share one code path. FFT reuses ``analysis.compute_fft``; its derived run's x-axis
  is frequency.
- **Registry-driven.** Every transform (builtin *or* plugin) is a ``TransformSpec`` in
  ``REGISTRY``; the engine looks up available kinds, default params, input arity and the
  compute function there, so a plugin is indistinguishable from a builtin. External
  plugins (``plugins.py``, the ``@transform`` decorator) are loaded at startup from
  ``$UZ_DATAVIEWER_PLUGINS`` / ``~/.uz_dataviewer/nodes/`` — both optional; a missing
  dir, no files, or a broken plugin are all tolerated (the app runs with just the
  builtins). An unknown kind (plugin not installed) restores as a placeholder that keeps
  its params/links. See :doc:`plugins`.

.. note::

   v1 limits (intentional): binary math needs equal-length inputs (no resampling);
   a source node pointing at *another node's* derived output is a runtime convenience
   that may not fully survive restore (chaining is meant to go through ``node_link``).

8. Downsampling (``downsample.py``)
===================================

Pure NumPy — **identical on native and web** (the Rust ``tsdownsample`` dependency was
removed in favour of the pyramid). Every path produces a **min/max envelope at the
signals' true sample positions** (so it looks like the waveform, not a blocky
bucket-centre grid) and a **consistent ~``max_points`` output at every zoom**. Two
layers:

- **One-shot envelope (``_envelope_oneshot``)** — splits the visible slice into
  ~``max_points/2`` near-equal buckets, takes each bucket's argmin/argmax, and
  interleaves them in order. Vectorised, **O(visible points)** — used for windows up to
  ``PYRAMID_MIN_POINTS`` (1 M), a couple of ms at that size.
- **Multi-resolution pyramid (``Pyramid``)** — for larger windows. Built **once per
  signal on first display** (lazily, cached on ``Signal.pyramid``): geometric levels
  storing the per-bucket argmin/argmax **sample indices** (``64, 512, 4096, …``), each
  aggregated from the previous, so the build is O(n). A query picks the coarsest level
  that still has ≥ the budget of buckets, then groups those down to the budget keeping
  each group's true extreme — **O(output)**.

.. note::

   **Hitting the budget exactly.** Both layers group their candidate buckets down to
   *exactly* ``max_points/2`` via ``_reduce_to`` — it assigns the ``k`` candidates to
   ``max_points/2`` near-equal groups (``grp = arange(k)*target//k``) and keeps each
   group's true extreme with one ``lexsort``. This replaced an integer **group factor**
   (``ceil(k/target)``), which could only halve/third/… the count and so realised as few
   as ~50 % of the budget at certain zooms (e.g. a 5 M-sample window landed on ~1 220 of
   2 000 points). The output is now a stable ~``max_points`` at every zoom and on every
   path. ``_reduce_to`` only ever runs on an already-bucketed array (≲ ``target ×
   factor``), so the query stays O(output); the pyramid *build* is untouched (still a
   fixed-stride O(n) pass).

Storing *indices* (not values) is what lets the envelope use true X/Y read from the
run's ``time``/``y`` arrays, so it's also normalization-agnostic. Measured (single
float32 signal, ``max_points=10 000``, one core; reproduce with a short
``Pyramid.build``/``decimate_range`` timing loop):

.. list-table::
   :header-rows: 1
   :widths: 24 19 19 19 19

   * - Signal
     - Build (once)
     - Query/frame (full)
     - Query/frame (zoomed)
     - Pyramid memory
   * - 10 M pts (40 MB)
     - ~15 ms
     - ~0.9 ms
     - ~0.15 ms
     - 1.4 MB (3.6 %)
   * - 50 M pts (200 MB)
     - ~75 ms
     - ~0.7 ms
     - ~0.2 ms
     - 7.1 MB (3.6 %)

For comparison, re-scanning the full 50 M extent every frame (the one-shot envelope, the
work the pyramid avoids) costs **~23 ms/frame** — i.e. the pyramid is ~30× cheaper per
frame at the price of a one-time build and ~3.6 % memory. The output also stays
~``max_points`` whether you view the whole record or a slice (the earlier 8×-jumpy point
count and bucket-centre blockiness are gone). *(Absolute times are hardware-dependent;
the point is the O(output) vs O(visible) gap, which is structural.)*

The FFT/Histogram windows use the same decimation: a multi-million-point spectrum is
range-decimated per frame (``AnalysisPanel._plot_decimated``) rather than drawn in full,
and a histogram is binned once at compute (not re-binned every frame).

Two trade-offs this design accepts, stated honestly:

- The pyramid is built **lazily on first display**, on the render thread — so the first
  frame after dropping in a large signal stalls for the build (~75 ms at 50 M above).
  It's a one-off per signal and dwarfed by the file load, but a smoother option would be
  to build it on the loader thread alongside parsing. *(Not done; noted as future
  work.)*
- The renderer **re-decimates every frame with no result cache**. Because a query is
  O(output) this is cheap even on a static view, and it keeps the code stateless (true
  to immediate mode). The alternative — caching the decimated arrays keyed on ``(visible
  limits, max_points)`` and reusing them while the view is unchanged — would trim idle
  CPU, at the cost of a cache to invalidate. We chose simplicity; the door is open if
  idle draw cost ever matters.

9. Sessions (``session.py``)
============================

Two complementary formats:

- **JSON snapshot** (``save_state``/``load_state``) — the exact view (grid, assignments,
  plot types, cursors/spy, secondary axes, FFT/Histogram config, time origins, file
  list). Restore reloads files then resolves assignments **by run label** (not id).
- **``.uzscript``** (``export_script``/``run_script``) — a human-readable, editable list
  of commands that reproduces the session when replayed. Normalised loads round-trip as
  ``load(path, start)``.

CSV exports (``export_data``, ``export_fft``, ``export_histogram``) also live here.

.. _uz_dataviewer_arch_native_web:

10. Native vs Web (``webbridge.py``)
====================================

The same Python runs on the desktop and in the browser via Pyodide (CPython→WASM); a
single flag, ``webbridge.IS_WEB``, gates the handful of edges that differ. The UI,
command layer, plots, FFT/Histogram, nodes and downsampler are **identical** on both —
the differences are file I/O, threading, and the WASM memory ceiling.

The design-relevant points: loads are async on native and synchronous on web (Pyodide
has no worker threads); the renderer never branches on the target because the
**decimator is pure NumPy** (no native dependency to wheel for the browser); and the web
build cannot hold a multi-GB log, so a large CSV is **stream-parsed into typed arrays**
and **decimated on a memory budget** at load rather than materialised whole.

The full table and the rationale for each difference live in :doc:`native_vs_web`; the
wasm32 ~4 GB ceiling and the deferred out-of-core fix are analysed in
:doc:`web_large_logs`.

11. Extending the app
=====================

**Add a command** — register it in ``register_builtins`` (``commands.py``):

.. code-block:: python

   def my_action(state, a):
       plot_n, value = a
       state.cells[plot_n - 1].something = value
   reg.add("my_action", [Param("plot", "plot"), Param("value", "float")], my_action, "help text")

Then have the widget call ``state.commands.execute(state, "my_action", [plot_n, value])``
(via the panel's ``_emit``) on change. Persist it in ``session.py`` if it should be
saved.

**Add a time-series option** — add a field to ``SubplotCell``, a command to toggle it, a
checkbox in ``PlotsPanel._cell_header`` that emits the command, the rendering in
``_render_time_series``, and the session round-trip.

**Add an analysis window** — subclass ``AnalysisPanel``, set ``prefix``/``compute_command``,
implement ``_compute``/``_draw``/``_options_key``/``_extra_controls``; register the
per-type commands (the common ones come from ``_register_analysis_common``); add a
``DockableWindow`` in ``app.py`` and a config dataclass + serialisation.

**Add a plot type** — extend ``PlotType``, branch in ``PlotsPanel._render_cell``, and
update ``session.py`` if it carries extra per-cell state.

**Add a node transform** — register a ``TransformSpec`` in ``nodes.py`` (a compute
function + default params + arity), or, for a user-supplied one, ship a plugin file with
the ``@transform`` decorator (see :doc:`plugins`). Builtins keep bespoke widgets in
``NodesPanel._params``; plugins render from their ``ParamSpec`` list automatically.
Commands and save/restore are generic (``node_set`` carries arbitrary params; the graph
stores only the kind name), so nothing else needs touching.

12. Testing
===========

Tests are pure ``pytest``, no real window. Two patterns:

- **Logic via commands** — dispatch command strings against an ``AppState`` and assert
  on state (e.g. ``test_commands.py``, ``test_session.py``).
- **Headless rendering** — create an ImGui/ImPlot context, set a backend-textures flag,
  and drive a few frames calling ``panel.render(state)`` (e.g. ``test_plot_types.py``).
  This exercises the real ImPlot calls (begin/end pairing, Spec markers, drag tools)
  without a GPU window. Destroy the contexts in a ``finally`` so tests don't leak across
  modules.

Run: ``pytest`` from the project root.

.. _uz_dataviewer_design_decisions:

13. Design decisions, in brief
==============================

.. list-table::
   :header-rows: 1
   :widths: 35 65

   * - Decision
     - Why
   * - Single ``AppState``, panels as renderers
     - One source of truth; trivial to serialise and test; no scattered widget state.
   * - Command layer is the only mutation path
     - Scriptability, console transcript, save/restore-by-replay, and headless testing
       all derive from it.
   * - Gestures **echo**, discrete actions **execute**
     - Zoom/drag are continuous; echoing once on settle keeps the console readable while
       staying replayable.
   * - Min/max **pyramid** (pure NumPy) for decimation
     - Per-frame cost becomes O(output), not O(visible points) (~0.7 ms vs ~23 ms/frame
       at 50 M points), so multi-GB logs pan at full fps — built once at first view
       (~75 ms/50 M), ~3.6 % memory. Replaced the Rust ``tsdownsample`` dep so native and
       web run the same code. **Cost:** lazy build hitches the first frame; the renderer
       re-decimates every frame uncached (both deemed acceptable — see §8).
   * - XY cells decimate by uniform **stride**, not min/max
     - An XY/phase plot has no monotone time axis to bucket against; stride keeps it
       simple, but can alias a dense Lissajous figure (the only place "range-aware
       downsampling" doesn't apply).
   * - FFT/Histogram are windows, on-demand
     - Per-frame transforms of a large window would tank the frame rate; explicit Compute
       keeps it snappy.
   * - Nodes are a **derived-signal factory** (not a new viewer)
     - Transforms emit ordinary runs, so plots/FFT/Histogram consume them unchanged — the
       canvas adds power without re-plumbing the rest. The engine is GUI-free and
       command-driven, so it's scriptable and headless-testable; the ``imgui_node_editor``
       canvas only issues ``node_*`` commands.
   * - ``searchsorted`` not ``np.interp`` for cursors
     - ``np.interp`` up-casts the whole array each call — catastrophic per frame.
   * - Session refs by run **label**
     - Run ids are reassigned on reload; labels survive.
   * - Per-log time normalization keeps ``time_raw``
     - Reversible, cheap (recompute on change only), and signals are never touched.
   * - Web: stream-parse CSV → arrays
     - Avoids holding multi-GB text in 32-bit WASM memory; loads full resolution.
   * - Pending-flag pattern (``fit_pending``, ``compute_requested``, …)
     - The immediate-mode way to express "do X once next frame".
