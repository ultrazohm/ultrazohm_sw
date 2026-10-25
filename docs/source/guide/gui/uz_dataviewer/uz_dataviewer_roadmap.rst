.. _uz_dataviewer_roadmap:

Maintenance status and remaining limits
======================================

This page replaces the earlier design backlog, which described several already
implemented paths as future work. It is not a commitment to add features.

Implemented contracts
---------------------

- Native defaults to Polars and lazy loading; PyArrow remains supported on native
  and is the browser backend. Both engines share naming and selection contracts.
- Native FFT and histogram work runs through cancellable request workers.
  Browser computations are synchronous because the current Pyodide runtime has
  no worker-thread execution path.
- Display summaries live in ``sources.py``. Raw window reads and exports do not
  use display decimation. Browser streaming CSV imports preserve every sample
  and reject data exceeding the numeric-memory budget.
- Source nodes reference recordings. Transform-to-transform links carry graph
  dependencies; wrapping a derived output in a source node is rejected.
- Sessions use stable file/node references, not display labels, to restore links.
- FFT-derived runs carry a frequency axis. They cannot share a plot or linked
  time range with time-domain recordings. Math preserves the input axis domain;
  FFT, FIR filtering and time shifting require time-domain inputs.

.. _uz_dataviewer_web_large_logs:

Deliberate limits
-----------------

- Browser uploads are temporary. Memory imports release their upload bytes after
  parsing; lazy uploads retain their backing file until the last run is removed
  or the session closes. Session saving rejects these recordings because the
  upload paths are not portable or durable.
- XY plots use uniform stride for display and can alias dense trajectories.
  Their inputs must share matching sample axes; there is no implicit resampling.
- Plugin inputs are read-only views and outputs are copied into owned numeric
  buffers. This prevents accidental mutation, not malicious Python code.
  Plugins are trusted native code and must preserve the independent-axis domain.
- Units are not inferred through arbitrary math or plugins. A transform can
  declare its output unit explicitly; automatic dimensional algebra is absent.
- The command transcript records supported operations, not every GUI gesture.
  JSON snapshots capture supported view settings; window docking is separate.
- FFT and node evaluation can require substantial resident memory. Display cache
  budgets do not bound raw transform input/output allocations.

Validation
----------

The test suite covers both backends, memory/lazy loading, GUI contexts, exports,
plugins, session restoration, cancellation and generated browser CSV parsing.
The browser smoke test boots the generated page with the pinned Pyodide and
imgui-bundle wheel, imports a recording and exercises plotting and analysis.
Native release builds additionally run the frozen-executable self-test.
