.. _uz_dataviewer_architecture:

===================
Developer reference
===================

Developer reference for how ``uz_dataviewer`` is structured, the design decisions behind it, and how to extend it.
End-user documentation is in :doc:`uz_dataviewer_usage`; packaging is in :doc:`uz_dataviewer_build`.

Core model
==========

The viewer is **state-driven and command-routed**:

- A single source of truth, ``AppState`` (``state.py``). Panels are (almost) pure render functions: each frame they read ``AppState`` and draw it.
- **Data and analysis controls use the command registry** (``commands.py``). A command mutates ``AppState`` *and* echoes its canonical call to the console.

This model yields four properties:

#. **Scriptability** — external Python calls ``uz_dataviewer.Client`` to control the running app.
#. **Live transcript** — the console shows what happened, as commands.
#. **Save/restore** — sessions serialize to JSON through one restoration path.
#. **Testability** — typed operations and local transport can be exercised without opening a window.

.. warning::

   A feature whose only trigger is a direct widget mutation breaks this model.
   Add a command and have the widget call it.

Frame flow
==========

``immapp.run()`` (hello_imgui) drives a classic immediate-mode loop.
Per frame:

.. code-block:: text

   pre_new_frame()                      # app.py: poll async loads, focus requests, file dialogs
   └─ docking layout renders each DockableWindow's gui_function:
      ├─ NavigationPanel.render(state)  # left: runs + signals + normalize menu
      ├─ PlotsPanel.render(state)       # center: subplot grid
      ├─ FftPanel.render(state)         # center tab: FFT window
      ├─ HistogramPanel.render(state)   # center tab: Histogram window
      ├─ NodesPanel.render(state)       # center tab: node canvas
      └─ Console.render(state)          # bottom: read-only application log

Immediate mode has **no retained widget state**, so anything that must persist across frames lives in ``AppState``/``SubplotCell``.
Transient "do this once next frame" requests use a **pending-flag pattern** (``cell.fit_pending``, ``cell.pending_x_lim``, ``cfg.compute_requested``): the renderer consumes and clears the flag.

Module map
==========

.. list-table::
   :header-rows: 1
   :widths: 25 45 30

   * - Module
     - Responsibility
     - Key types
   * - ``app.py``
     - Docking layout, ``immapp`` runner, theme, Session menu, Python-script and recording startup
     - ``DataViewerApp``
   * - ``api.py``
     - GUI-free façade for headless/library use (load, FFT, node transforms) — see :doc:`uz_dataviewer_library`
     - ``read``, ``Dataset``, ``fft``, ``fft_frame``, ``node``, ``kinds``
   * - ``state.py``
     - The single app state, grid/cells, analysis configs, async load orchestration
     - ``AppState``, ``SubplotCell``, ``PlotType``,
       ``AnalysisConfig``/``FftConfig``/``HistogramConfig``
   * - ``commands.py``
     - Shared operation metadata, validation and GUI handlers
     - ``CommandRegistry``, ``Command``, ``Param``
   * - ``command_doc.py``
     - Generates the docs command reference (CSV) from public Python client signatures — see :ref:`uz_dataviewer_generated_command_reference`
     - ``build_csv``, ``group_for``, ``GROUP_ORDER``
   * - ``console.py``
     - Scrolling selectable application log
     - ``Console``
   * - ``model.py``
     - Loaded data + per-log time normalization
     - ``Run``, ``Signal``, ``DataRegistry``
   * - ``loader.py``
     - CSV (Arrow) / Parquet loading, header cleaning, delimiter sniffing; lean large-log loading (float32-at-parse, CSV size guard, streaming Parquet, CSV→Parquet ``convert``) — see :ref:`uz_dataviewer_loader_large_logs`
     - ``open_file``, ``parse_file``, ``ParsedRun``, ``parse_channel_name``,
       ``convert_csv_to_parquet``
   * - ``sources.py``
     - Resident/lazy raw-sample access, timestamp indexes, persistent display summaries, shared byte-bounded cache
     - ``Source``, ``ArraySource``, ``ParquetSource``, ``SourceColumn``, ``ByteCache``
   * - ``requests.py``
     - Coalescing worker requests; cancellation and result publication without GUI calls
     - ``Requests``
   * - ``downsample.py``
     - Range selection and an adapter to the shared source downsampler
     - ``decimate_range``, ``visible_slice`` (shared source downsampling)
   * - ``analysis.py``
     - GUI-free transforms (FFT)
     - ``compute_fft``, ``FftResult``
   * - ``transforms.py``
     - GUI-free node transforms (math, FIR filter), pure NumPy
     - ``math_node``, ``filter_node``
   * - ``nodes.py``
     - Dataflow graph + on-demand evaluation → derived runs; the transform **registry**
     - ``NodeGraph``, ``Node``, ``evaluate``, ``is_stale``, ``TransformSpec``, ``REGISTRY``
   * - ``plugins.py``
     - Load external transform-node plugins (``@transform``); robust to missing dirs/files
     - ``transform``, ``ParamSpec``, ``load_plugins``
   * - ``session.py``
     - JSON save/restore, command-script execution, CSV exports
     - ``to_dict``/``apply_dict``, ``export_*``
   * - ``panels/navigation.py``
     - Left tree, drag sources, file dialog, normalize menu
     - ``NavigationPanel``
   * - ``panels/plots.py``
     - Subplot grid: types, cursors, spy, axis linking, secondary axis, export
     - ``PlotsPanel``
   * - ``panels/analysis.py``
     - Shared base for analysis windows (sources, follow-window, compute, stale, zoom, export)
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

Data model
==========

- A **``Run``** is one loaded file: a shared ``time`` axis (``float64``) plus one **``Signal``** per channel (``y`` as ``float32``).
  In-memory runs expose NumPy arrays; lazy runs expose ``SourceColumn`` views whose slices read original samples on demand.
  Plotting uses ``Run.data_source()``. ``SourceColumn.read_rows`` selects a row interval; ``materialize()`` or explicit ``np.asarray`` reads a whole column. Implicit arithmetic, fancy indexing and reverse slicing are unsupported.
- **``DataRegistry``** owns runs and hands out stable integer ids; ``SignalRef = (run_id, name)`` identifies a signal everywhere.
- **Time normalization** is per-log: ``Run.set_time_origin(target)`` keeps the original ``time_raw`` and derives ``time = time_raw - time_raw[0] + target``. It is reversible (``target=None`` restores raw) and re-derives only on change, never per frame.

Channel headers like ``CH8=8)ia`` are cleaned to ``ia`` by ``parse_channel_name``, which also detects a trailing unit token (``_rpm``, ``_us``, …) for axis labels.

.. _uz_dataviewer_loader_large_logs:

Loading & large logs (``loader.py``)
=====================================

``open_file`` selects the storage policy for GUI uploads, native loads and commands.
Memory loads dispatch through ``parse_file`` → ``parse_csv`` / ``parse_parquet`` and return a ``ParsedRun``; lazy loads return an ``OpenedSource``.
Both register through their ``register`` method. The redundant eager-only ``load_file`` wrapper has been removed.
On native, interactive GUI loads run on the cancellable daemon worker in ``workers.py``.
Recordings before the first startup Python file are prepared during startup.
Python files and subsequent arguments run sequentially after the UI opens.
External Python load calls wait for background preparation and application-thread
registration. A startup failure is logged and stops the remaining arguments.
The worker prepares a resident run or lazy source; the main thread registers it in ``state.poll_pending_loads``, so ``DataRegistry`` is only mutated from one thread.
Conversion runs in a spawned process so shutdown can interrupt native streaming IO and remove partial output.
Readers check cancellation between batches; an in-flight native read may finish before cancellation is observed, but it cannot keep the application process alive.

The in-memory loaders reduce transient allocations; the complete recording and analysis scratch still need to fit in RAM:

- **float32 at parse, no intermediate copy.** ``_csv_column_types`` feeds Arrow ``ConvertOptions(column_types=…)`` so channels parse straight to ``float32`` (time stays ``float64``), avoiding the float64→float32 re-cast that doubled channel memory. ``_named_signals`` shares one naming/dedup pass across every load path.
- **Streaming CSV.** Both native backends stream numeric batches into the shared ``collect_csv_batches`` allocator. It checks actual rows and retained numeric capacity against ``MAX_CSV_NUMERIC_BYTES`` before allocating or growing arrays; the file-size estimate is only an initial admission check. Parser scratch and transient growth copies are additional memory. The former small-file bulk path and streaming-size threshold have been removed. ``csv_policy.NULL_VALUES`` defines the missing-value spellings used by both backends.
- **Releasing Arrow's pool.** After every parse, ``parse_file`` calls ``_release_arrow_pool`` (``pa.default_memory_pool().release_unused()``): Arrow otherwise retains freed parse scratch rather than returning it to the OS, pinning RSS at the parse high-water mark (measured ~1.2 GB reclaimed on the 9M-row log, ~10 GB on the 75M).
- **CSV size guard.** ``_guard_csv_size`` estimates the resident footprint from file size × column count and **refuses** a CSV above ``MAX_CSV_NUMERIC_BYTES``. Now that large CSVs stream, this is a **resident-RAM** ceiling (the full record must fit in memory), not a bulk-parse guard; it routes the user to lazy loading or ``convert(...)``. Actual capacity is checked independently during materialization.
- **Streaming Parquet.** All eager PyArrow Parquet loads preallocate arrays from ``ParquetFile.metadata.num_rows`` and fill them with ``iter_batches``. There is one path for small and large files; lazy loads retain indexed sources.
- **CSV→Parquet converter.** ``convert_csv_to_parquet`` stream-converts a CSV to Parquet with bounded memory (per-batch ``ParquetWriter.write_batch``), dropping JavaScope's empty trailing column and preserving raw headers so the result round-trips through the same name parsing. Exposed as the scriptable ``convert(src, [dst])`` command and the ``uz-dataviewer convert`` CLI.
  The shared converter owns temporary output, empty-recording validation, cancellation cleanup, and publication without overwriting existing destinations. GUI, Python control, and cache conversion use this same path; backend writers only fill unpublished temporary files.

In-memory mode retains the complete recording. Lazy mode reads raw windows
and streams histogram batches without keeping the full recording resident;
FFTs and node transforms still materialize their selected inputs.

The operation and transport layers
==================================

``operations.py`` owns application-lifetime request coordination. Both GUI handlers
and external control use shared state operations; the GUI does not connect to its
own socket. ``commands.py`` retains internal operation metadata and handlers for
existing panels. It has no text parser or script interpreter.

``client.py`` and ``client_methods.py`` provide the public Python API without GUI
or numerical imports. The client sends versioned, newline-delimited JSON over a
persistent loopback TCP connection. ``control_server.py`` owns the listener and a
bounded queue; socket threads never mutate application state. The application
polls requests on its owning thread. Deferred operations return futures, allowing
the UI to continue rendering while background work completes. Client disconnects
cancel pending operations. Mutations are never automatically retried.

Run, node and view handles include a session identity. Replacing the session
invalidates old handles. Explicit view handles address additional plot windows;
omitting a view addresses the main window. Relative file paths supplied to the
Python client are resolved in the caller's working directory.

The read-only application log records actions and failures. It is not a complete
session representation. Save supported state through JSON session snapshots.

.. _uz_dataviewer_generated_command_reference:

Generated Python API reference (``command_doc.py``)
--------------------------------------------------

``command_doc.build_csv`` renders public client signatures, documentation and
operation groups into ``uz_dataviewer_commands.csv``. The usage guide includes
this committed file, so documentation builds do not require the GUI runtime.
Regenerate with ``python -m uz_dataviewer.command_doc``. The documentation test
checks both the committed output and complete method grouping.

Plots panel internals (``panels/plots.py``)
============================================

A runtime grid of ``SubplotCell``s.
Cell types: ``line`` / ``scatter`` / ``stairs`` (time series) and ``xy`` (one signal vs another).
FFT and Histogram are **separate windows**, not cell types.

Per time-series cell, each frame:

#. Compute the data extent and apply any **pending** axis limits (``fit_pending``, ``pending_x_lim``, ``pending_y_lim``) with ``Cond_.Always``.
#. **Linked X:** the hovered cell becomes the ``_driver`` and publishes its X range to ``state.shared_x``; followers lock to it. Every time-series cell also publishes its own range to ``state.plot_x_ranges[plot_n]`` (used by analysis windows' "follow plot_N").
#. **Downsample** each signal to ~``max_points`` over the visible window (``decimate_range``, fed by ``visible_slice``) — this keeps multi-GB logs interactive. **XY cells are the exception**: they decimate by plain uniform stride (``sampling.sample_xy``), not a min/max envelope, so a busy Lissajous figure can alias (acceptable for the phase-portrait case).
#. Draw it (line/scatter/stairs), optionally with per-sample markers (``Spec.marker``), routing the left/right (secondary ``ImAxis_.y2``) axis per signal.
#. **Cursors** (two ``drag_line_x``) and **spy** (``drag_rect`` + a ``canvas_only`` inset) draw on top. Their readouts and rectangles are recomputed only on move.
#. **Zoom echo:** when a pan/zoom settles, ``echo set_x_lim(plot_n, ...)``.

.. note::

   **Cursor performance.** Cursor readouts originally used ``np.interp``, which up-casts the entire ``float32`` signal to ``float64`` on every call (~150 ms/frame on a 5 M-point log).
   It was replaced with an O(log n) ``searchsorted`` lookup (``_value_at``) that touches only the two bracketing samples.

Analysis windows (``panels/analysis.py``)
==========================================

FFT and Histogram share ``AnalysisPanel``.
Subclasses set a command ``prefix`` (``fft``/``hist``) and a ``compute_command``, then implement ``_make_request``, ``_draw``, ``_options_key``, and any ``_extra_controls``.
The base provides:

- A **sources list** fed by drag-drop (``*_source`` command) and the legend "Remove" (``*_remove``).
- A **time-window selector** (``follow_combo``): ``Custom`` (``0``), ``Full`` (``-1``), or ``plot_N`` (``≥1``), resolved by ``AppState.resolve_x_window``. Switching to a plot computes immediately; switching to Custom/Full does **not** (the window can be the whole log).
- **On-demand compute only** — never per frame. A compute happens on the *Compute* button, on a drag-in, or once when an input changes (``compute_requested``). Following a plot and then panning it goes **stale** rather than recomputing.
- A **stale indicator**: a ``_computed_key`` snapshot (sources + window + options) is compared to the current key each frame; mismatch shows "⚠ stale - press Compute".
- **Shared analysis controls use commands** (``fft_follow``, ``fft_remove_dc``, ``hist_bins``, ``*_xlim`` on zoom, ``*_export``, …) and **Export** (OS save dialog).

.. _uz_dataviewer_node_graph:

Node graph (``nodes.py``, ``transforms.py``, ``panels/nodes.py``)
==================================================================

A small dataflow engine, built as a **derived-signal factory**: a transform node, when evaluated, materializes its result as a *new run* in the registry (``Run.derived=True``) via ``AppState.upsert_derived_run``.
That derived signal then flows through the existing app unchanged — it shows in Navigation and is draggable into plots / FFT / Histogram.
Nodes *produce* data; nothing else in the app needs to know they exist.

- **Graph** (``NodeGraph``) of ``Node``s: a **source** wraps a ``(run, signal)`` ref; a **transform** (``fft`` / ``math`` / ``filter`` / ``shift``) pulls arrays from its inputs and computes. Links are validated against cycles; ids are persisted so derived-run labels (= node name) are stable across save/restore.
- **On-demand evaluation** (``evaluate``): topological order; each transform reads its inputs (a source from the registry, an upstream transform from its cache), computes via ``transforms``/``analysis``, bumps a ``version``, and upserts its derived run **in place** (so plot references survive a re-eval). Per-node errors are logged and skipped, not fatal. A node is **stale** (``is_stale``) when its key — params + each input's version/identity — differs from the last evaluated key (the same idea as the analysis windows' ``_computed_key``).
- **GUI-free + scriptable**: ``nodes.py``/``transforms.py`` import no GUI and raise plain ``ValueError``s, so the whole engine is driven and tested from command strings. The canvas (``panels/nodes.py``, ``imgui_node_editor``) is a thin layer that **only issues ``node_*`` commands** — drag-drop → ``node_source``, link → ``node_link``, a widget → ``node_set``, a drag → ``node_pos``, the button → ``node_eval``. The graph is automated through commands and restored through the JSON session.
- **Transforms use NumPy** (windowed-sinc FIR filter). FFT reuses ``analysis.compute_fft``; its derived run's x-axis is frequency.
- **Registry-driven.** Every transform (builtin *or* plugin) is a ``TransformSpec`` in ``REGISTRY``; the engine looks up available kinds, default params, input arity and the compute function there, so a plugin is indistinguishable from a builtin. External plugins (``plugins.py``, the ``@transform`` decorator) are loaded at startup from ``$UZ_DATAVIEWER_PLUGINS`` / ``~/.uz_dataviewer/nodes/`` — both optional; a missing dir, no files, or a broken plugin are all tolerated (the app runs with just the builtins). An unknown kind (plugin not installed) restores as a placeholder that keeps its params/links. See :doc:`uz_dataviewer_plugins`.

.. note::

   Binary math needs equal-length inputs with matching timestamps throughout both axes (no resampling or implicit index alignment). Source nodes accept recordings only; connect transforms with ``node_link`` so the graph tracks every dependency.

.. _uz_dataviewer_downsampling:

Downsampling (``downsample.py``)
=================================

The time-series renderer consumes compact results from ``Source.read_plot``.
Raw reads (``read_rows`` and ``iter_raw``) are separate and always return original samples in file order, including equal timestamps.
FFT, exports and nodes never consume display summaries.

``ArraySource`` wraps existing resident arrays.
``ParquetSource`` opens footer metadata, projects selected columns, and reads batches of at most 65,536 rows.
On the first query it validates the complete timestamp order and persists a small timestamp index.
If footer time statistics are absent, that scan is needed at open.
Source identities include the resolved path, file size, nanosecond mtime/ctime, inode and cache format version.
Changed files must be reopened.

Display summaries retain original sample indices, times and extrema values in 1,024-sample buckets, then combine levels by a factor of eight.
Each bucket can also retain a representative non-finite gap.
Queries select a suitable level, refine partial boundaries through finer levels and raw samples, then reduce to the display budget.
A level is used only when it provides at least one bucket per requested extrema pair.
If even the finest level is too coarse, the selected raw window is read and reduced instead; this avoids sparse interiors with dense boundary samples at close zoom.
Those temporary window arrays are separate from the retained-cache budget.
A summary cannot represent every gap smaller than a pixel; raw analysis retains every original sample.
Gap markers may add up to half the finite-point budget.
Raw timestamps are stored in summaries; normalization is a view offset for lazy runs.

Desktop plot, fit, spy, XY and cursor requests run on one coalescing worker.
Each consumer has at most one queued request; superseded requests are cancelled and results are published only for the current request.
The renderer can retain the previous viewport while waiting, but never displays a result from a different source version.
Small resident signals (up to 4,096 samples) may use a synchronous fast path.
Completed view buffers are reused, including spy views.
Removed consumers release their results and idle workers release source references.

The shared timestamp/summary RAM cache is byte-bounded (1,024 MiB by default).
Display buffers are bounded by trace/plot budgets.
These are not total-process memory limits: decoded batches, summary-construction scratch, full FFTs and explicit array-based plugins/exports need additional memory.
Indexes and summaries are kept in RAM by default, without reading or writing disk caches.
Optional persistent caches have no automatic disk-size limit and can be removed while the viewer is closed.
The cache directory defaults to ``~/.cache/uz_dataviewer`` and is overridden by ``UZ_DATAVIEWER_CACHE``.
Writes are atomic; invalid cache containers are rebuilt.

``loading_mode(memory|lazy)`` affects subsequent opens.
The user explicitly selects resident or lazy loading; obsolete Auto sessions are rejected.
Lazy CSV input is scanned directly by the selected backend by default.
CSV navigation requires repeated text scanning and can be slower than Parquet.
Enabling ``disk_cache(true)`` for subsequent opens persists indexes and summaries and converts lazy CSV input to a versioned Parquet cache.
Existing cache files are left untouched when disk caching is disabled.
JSON sessions preserve per-file storage modes and the current settings.

GUI FFT and histogram computations use a separate worker with frozen ``FftRequest`` / ``HistogramRequest`` inputs.
``AnalysisInput`` captures each selected source, reference, label and time offset; options and the resolved window are copied as scalar values.
Sources and the thread-safe byte cache are shared deliberately. Workers receive neither ``AppState`` nor GUI panels and return an explicit ``AnalysisResult``.
Full analysis resolves the union of selected recording extents, so selection order cannot truncate a longer or disjoint recording. Custom and followed ranges remain shared explicit windows.
Histograms make two bounded passes over raw batches with shared bin edges.
FFT still materializes the selected window.
Hann windows belong to that computation and are released afterwards; there is no
process-global cache retaining windows from previous FFT sizes.
Cancellation of a NumPy FFT takes effect after its native call returns.
``node_jobs.py`` captures a detached graph and recording metadata for background
node evaluation. Immutable input arrays and the thread-safe sample cache are shared;
node parameters, input lists, runs and signal metadata are copied. Publication on
the application thread checks the original graph/source fingerprint and session
identity. Changed inputs discard the result. Existing derived-run IDs and time
normalization survive publication. GUI and Python node evaluation use this same
operation; the synchronous engine remains available for headless analysis and
preparing a replacement session. Cancellation is checked between reads and nodes,
and after each transform returns.

Time-series, XY and cursor requests share source validation, worker scheduling and error reporting through ``PlotsPanel._request_data``.
Cached display and analysis results share the ``sources.validation_error`` contract with node stale detection.
``FileIdentity`` validates both the original CSV and its cached Parquet representation; conversion publishes only if the original identity still matches.
Derived ``ArraySource`` objects validate their owning node and upstream inputs before raw reads or cache reuse. Failed or stale outputs remain assigned but cannot be plotted, analysed or exported until successfully reevaluated.
Only small resident arrays can run immediately on the desktop render thread.
XY sampling validates all displayed timestamps in bounded paired batches, including timestamps omitted by the display stride. Different lengths or time bases are rejected; there is no implicit interpolation.
XY view ranges are stored on their cell and never published as linked time ranges. Both plot types share explicit axis-limit application and view capture.

FFT and ordinary plots now share the ``ArraySource`` / ``SummarySource`` sampling engine.
FFT summaries are constructed by the analysis worker, and unchanged spectrum views reuse their reduced arrays.
``IndexedFileSource`` owns file identity, timestamp indexing, bounds and cache persistence for both backends.
Analysis, export and node cropping select exact time windows; padding is reserved for display.
FFT rejects duplicate or irregular timestamps instead of returning a misleading frequency axis.
JavaScope's raw ``CHn=n)`` headers identify its 10 ns timestamp quantization, including
in converted Parquet files. These recordings must fit a single uniform grid within
±5 ns plus floating-point roundoff; duplicate and backward timestamps remain invalid.
The precision is retained through normalization and built-in time-domain node outputs.
Other recordings use the existing 100 ppm interval tolerance plus roundoff. Array API
calls can explicitly pass ``timestamp_resolution`` (available on ``Dataset``).
``sampling.py`` shares this validation with FIR filters,
and validates complete time axes for binary math. Derived-run refresh preserves the existing time normalization.

Sessions (``session.py``)
==========================

**JSON snapshot** (``save_state``/``load_state``) is the only session format.
Schema version 6 includes additional plot views and reloads explicit per-run records and remaps recording/node keys,
preserving duplicate names and repeated opens of the same path. Restoration uses
a replacement state; failures leave the current session intact.

Automation uses ordinary Python files and ``Client.load_session`` /
``Client.save_session``. Session files contain data, never executable scripts.
Snapshot writes use atomic replacement; recording paths are relative to the
snapshot directory where possible. The custom script language is removed.

Failed or incomplete transforms with saved output assignments receive empty derived
run placeholders. The same validity check used for stale outputs blocks their data
from plots, analysis and exports. Successful evaluation refreshes those runs in place,
preserving assignments, visibility and time origin without saving stale sample arrays.

Input lists are indexed slots (``null`` represents a disconnected slot). ``node_link(src, dst, slot)``
and ``node_unlink(src, dst, slot)`` use zero-based slots; JSON preserves the slot explicitly.
The same upstream node can feed both binary inputs without collapsing the links.
Staleness checks traverse each upstream node once per call, with a local visited
set so shared inputs do not multiply work and subsequent edits remain visible.
Explicit FFT and histogram view limits are saved and restored alongside their
analysis settings, then reapplied when the panels recompute.

``AppState`` inherits the explicitly declared ``SessionData`` fields and owns a separate ``RuntimeServices`` object at ``state.services``.
Runtime services own display/analysis workers, the loading executor, pending loads and large-CSV prompts.
``AppState.replace_session`` transfers only declared session fields and service ownership, after shutting down the old workers.
It preserves the command registry and console, and installs a new session token. The consumed replacement no longer owns services; shutting it down cannot clear the transferred cache or stop the new workers.
``SessionPanel`` resets view caches and dialogs on token changes, including analysis results and canvas positions.
``clear_session`` uses the same replacement lifecycle.
GUI command wrappers share an explicit success result.

Runs without a backing file (live snapshots, arrays) cannot be saved in a reloadable session.
Saving rejects them before opening the destination file. Export their data first.

``SubplotCell.y_lim`` and ``y2_lim`` record the last rendered primary and secondary Y ranges, separately from their one-shot pending limits.
JSON persists pending limits when present, otherwise the live range. Each Y axis completes fitting independently, so a restored zoom is not overwritten when lazy data arrives for the other axis. Reset view clears both ranges.
Grid reduction prunes removed ranges and switches affected FFT/Histogram followers to Full.
Invalid analysis plot references are rejected by commands and session restore.
``validation.axis_limits`` rejects non-finite or non-increasing limits before mutation.
``SubplotCell`` owns clearing, secondary-axis membership and explicit limits; clearing
a plot removes secondary-axis assignments as well as plotted signals.

CSV exports (``export_data``, ``export_fft``, ``export_histogram``) also live here.
FFT export validates all selected channels before writing; a missing or invalid channel aborts with its identity and reason.

Extending the app
=================

**Add a command** — register it in ``register_builtins`` (``commands.py``):

.. code-block:: python

   def my_action(state, a):
       plot_n, value = a
       state.cells[plot_n - 1].something = value
   reg.add("my_action", [Param("plot", "plot"), Param("value", "float")], my_action, "help text")

Then have the widget call ``state.commands.execute(state, "my_action", [plot_n, value])`` (via the panel's ``_emit``) on change.
Persist it in ``session.py`` if it should be saved.

**Add a time-series option** — add a field to ``SubplotCell``, a command to toggle it, a checkbox in ``PlotsPanel._cell_header`` that emits the command, the rendering in ``_render_time_series``, and the session round-trip.

**Add an analysis window** — subclass ``AnalysisPanel``, set ``prefix``/``compute_command``, implement ``_make_request``/``_draw``/``_options_key``/``_extra_controls``; register the per-type commands (the common ones come from ``_register_analysis_common``); add a ``DockableWindow`` in ``app.py`` and a config dataclass + serialisation.

**Add a plot type** — extend ``PlotType``, branch in ``PlotsPanel._render_cell``, and update ``session.py`` if it carries extra per-cell state.

**Add a node transform** — register a ``TransformSpec`` in ``nodes.py`` (a compute function + default params + arity), or, for a user-supplied one, ship a plugin file with the ``@transform`` decorator (see :doc:`uz_dataviewer_plugins`).
Builtins and plugins use the same ``ParamSpec`` widgets in ``NodesPanel._params``.
Commands and save/restore are generic (``node_set`` carries arbitrary params; the graph stores only the kind name), so nothing else needs touching.

Testing
=======

Tests are pure ``pytest``, no real window.
Two patterns:

- **Logic via commands** — dispatch command strings against an ``AppState`` and assert on state (e.g. ``test_commands.py``, ``test_session.py``).
- **Headless rendering** — create an ImGui/ImPlot context, set a backend-textures flag, and drive a few frames calling ``panel.render(state)`` (e.g. ``test_plot_types.py``). This exercises the real ImPlot calls (begin/end pairing, Spec markers, drag tools) without a GPU window. Destroy the contexts in a ``finally`` so tests don't leak across modules.

Run ``pytest`` from the project root.

.. _uz_dataviewer_design_decisions:

Design decisions
================

.. list-table::
   :header-rows: 1
   :widths: 35 65

   * - Decision
     - Why
   * - Single ``AppState``, panels as renderers
     - One source of truth; trivial to serialise and test; no scattered widget state.
   * - Command layer is the only mutation path
     - Scriptability, console transcript, command automation, and headless testing all
       derive from it.
   * - Gestures **echo**, discrete actions **execute**
     - Zoom/drag are continuous; echoing once on settle keeps the console readable while
       recording understandable activity messages.
   * - Shared min/max summaries for resident and lazy sources
     - Background workers build summaries and cache completed display requests.
       Raw analysis and exports use original samples, never display summaries.
   * - XY cells decimate by uniform **stride**, not min/max
     - An XY/phase plot has no monotone time axis to bucket against; stride keeps it simple
       but can alias a dense Lissajous figure (the one place range-aware downsampling does not
       apply).
   * - FFT/Histogram are windows, on-demand
     - Per-frame transforms of a large window would tank the frame rate; explicit Compute
       keeps it snappy.
   * - Nodes are a **derived-signal factory** (not a new viewer)
     - Transforms emit ordinary runs, so plots/FFT/Histogram consume them unchanged. The
       engine is GUI-free and command-driven (scriptable and headless-testable); the
       ``imgui_node_editor`` canvas only issues ``node_*`` commands.
   * - ``searchsorted`` not ``np.interp`` for cursors
     - ``np.interp`` up-casts the whole array each call — catastrophic per frame.
   * - Session refs by recording/node **identity**
     - Explicit references preserve repeated filenames and partially evaluated graphs.
   * - Per-log time normalization keeps ``time_raw``
     - Reversible, cheap (recompute on change only), and signals are never touched.
   * - Pending-flag pattern (``fit_pending``, ``compute_requested``, …)
     - The immediate-mode way to express "do X once next frame".

Repository layout
=================

.. code-block:: text

   uz_dataviewer/
   ├── run.py                    # run from a source checkout (also launches ordinary Python files)
   ├── src/uz_dataviewer/        # modules — see the module map above
   │   └── panels/               # navigation, plots, analysis base, fft, histogram, nodes
   ├── tests/                    # pytest (logic via commands + headless rendering)
   ├── tasks.py                  # lint, test, bundle, bundle-smoke (all systems)
   └── build/                    # PyInstaller spec and frozen smoke tests

Worker and source contracts
---------------------------

``workers.CancellableExecutor`` owns sequential loading and directory-scan work.
``requests.Requests`` retains its coalescing scheduler for display and analysis.
Both use daemon threads, cooperative cancellation and a bounded shutdown join;
a blocked native or filesystem call cannot hold the process open. Directory
refresh also cancels the previous scan, including between files in one directory.

``sources.SampleSource`` describes validated raw row reads and time-window bounds.
``DisplaySource`` adds display sampling and ``prepare_summary``; analysis never
uses display summaries as raw samples. ``nodes.compute_node`` is the shared
validated computation entry point for the graph and headless API.

Session saves write a temporary file beside the destination and replace the old
snapshot only after serialization and writing succeed. Failed saves remove the
temporary file and preserve the previous session.

Sampling and domain transitions
-------------------------------

Timestamp roundoff allowances are bounded to one percent of a sample interval.
FFT and FIR reject axes whose absolute timestamp precision cannot establish that
bound; binary math and XY never treat a sample-sized displacement as roundoff.
Graph domain resolution shares a per-evaluation cache and uses iterative traversal.
When a saved graph changes an output's domain, restoration discards its incompatible
normalization and consumer assignments, matching live reevaluation. Failed outputs
retain their saved domain as unavailable placeholders until repaired.


Background display policy
=========================

Live display requests retain one active job and the newest queued replacement.
Completed work from the same display identity may be shown while newer data is
pending; changing identity cancels it. Device commands retain their independent
Stop ordering and cancellation boundary, including queued manual mutations.
Lazy source identity checks run on background workers at approximately 4 Hz;
strict validation still surrounds actual reads and exports. Cached displays may
therefore remain visible briefly until a file change is detected. In-memory graph
validity is checked immediately.

The Data Viewer must never use GUI idle throttling. Keep
``params.fps_idling.enable_idling = False`` globally, including live streaming,
paused views, and offline analysis. Do not re-enable idling or rely on individual
plots to opt out; rendering must not slow down because mouse or keyboard input
stops. Actual FPS still depends on rendering workload and display synchronization.


Repository-owned service configuration
--------------------------------------

The CLI owns firmware configuration resolution. ``serve --repo PATH`` reads the
selected checkout's headers and filters only built-in initial-channel defaults.
Explicit ``--profile`` settings remain strict. ``--channel-mapping`` is an
alternative to ``--repo`` for standalone mapping files. The effective settings
are exposed by ``catalog``; selecting another checkout requires restarting the
service.

The viewer previews metadata with ``channel-mapping --repo`` and obtains initial
preferences through ``profile --repo``. These commands return JSON directly;
normal repository preparation writes no mapping snapshot. Missing workspace
preferences are seeded once. Connecting passes ``--repo`` and the saved
``settings.json`` directly, without a temporary filtered profile. Saved signal
selections use the running service's catalog. The Flash UZ migration path still
keeps its mapping and profile snapshots to preserve assignments across a restart.


Dependency and mapping selection checks
---------------------------------------

The viewer requires CLI 0.1.27.dev0 or newer for repository-based configuration.
CI exercises the locked PyPI CLI's repository commands before replacing it with
the checkout-built wheel for the full integration suite. This also covers the
ordinary source launcher, which uses the lockfile rather than a development wheel.

An explicit ``DataViewerApp(live_mapping=...)`` selects that mapping even when its
workspace is inferred from the path or supplied through ``live_repo``. The
workspace still owns preferences and recordings. Generated Flash UZ snapshots
are distinguished from explicit selections; subsequent repository-based launches
reread headers. Service startup rejects simultaneous repository and mapping
arguments, and changing either requires restarting an owned service.
