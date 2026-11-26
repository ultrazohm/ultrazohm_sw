# DataViewer (`ultrazohm_dataviewer`)

The DataViewer opens CSV and Parquet recordings and plots live measurements on Windows and Linux.
It supports linked subplots, FFTs, histograms, and node transforms.
Use `ultrazohm_dataviewer.Client` or the terminal commands to automate an open DataViewer.
Save and restore your analysis as a JSON session.

See the [analysis guide](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_analysis.rst), [live guide](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_live.rst), and [end-to-end workflows](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_workflows.rst).

## Quick start

Run `uvx ultrazohm-dataviewer` or extract the Windows ZIP and launch `ultrazohm-dataviewer.exe`.
See the [installation guide](../README.MD#ultrazohm-cli-and-dataviewer) for repository environments and persistent commands.

```sh
ultrazohm-dataviewer gui path/to/log.csv
ultrazohm-dataviewer gui session.json
```

Use **Open file(s)…** in Navigation or drop a recording onto the window.
Expand the recording and drag a signal into a plot.
For CSV files larger than 1 GiB, choose **Open CSV** to read directly or **Convert to Parquet** to write and open a sibling file.
Conversion preserves the CSV and any existing Parquet file.
Use **View → New plot window** for a grid with independent plot settings and shared recordings.
Run `ultrazohm-dataviewer --help` for application commands.

## Settings

Choose **UltraZohm Dataviewer → Settings** to open the settings window:

- **General:** log browser directory and startup visibility of Application log and Python.
- **Data loading:** backend, loading mode, and disk cache for newly opened recordings.
- **Performance:** RAM cache limit and display points per signal.

Edits apply immediately (except startup visibility) and persist as application defaults in `viewer_preferences.json` in the platform user data directory.
Each section has **Reset this section**.
An empty log directory uses the firmware checkout's `artifacts` directory.
The status bar displays FPS and cache usage.

Session files retain their own data and plot settings; loading a session does not rewrite application defaults.
Explicit startup options override saved defaults for that launch.
Device configuration remains in its acquisition panels.
The Python client uses the same DataViewer settings API:

```python
viewer.get_settings()
viewer.set_setting("cache_budget", 512)
viewer.set_setting("show_application_log", False)
```

## Large recordings and responsiveness

The DataViewer keeps rendering during live and offline use, even without input.

The default is **Polars + Lazy**.
Select PyArrow or In memory in **Settings → Data loading** when needed.
Choose the loading mode before opening files, or set it at startup.

```bash
ultrazohm-dataviewer gui --loading-mode lazy path/to/log.parquet
ultrazohm-dataviewer gui --loading-mode lazy path/to/log.csv
```

- **In memory** retains the existing full NumPy arrays for fast analysis.
- **Lazy** (desktop default) reads selected columns and sample ranges from Parquet or streams CSV directly.
  CSV requires repeated text scanning and is slower for interactive navigation.

The setting affects subsequent opens.
Existing runs retain their storage mode; JSON sessions preserve mixed modes.
The Python client equivalents are `viewer.loading_mode("lazy")` and `viewer.cache_budget(1024)`.

Plot preparation, first-use summaries, XY sampling, cursor reads, and GUI FFT / histogram computation run outside the desktop rendering thread.
During an update, the last completed plot remains visible.
Up to four plot requests run concurrently, so a slow first-time summary of one channel does not hold back other subplots; concurrent requests can each hold their own decoded batches in memory.
Superseded display requests are cancelled or discarded.
Main and spy plots reuse completed results, and finite display-point budgets account for pixel width and trace count.
Gap markers may add points beyond the finite-point budget.

Parquet opens use footer statistics when available.
The first sample query validates timestamp order and builds a persistent timestamp index; files without usable statistics need that scan during opening.
First display of a channel builds its persistent min/max summaries.
These operations stream through the file and can take seconds for large recordings.
Reopening reuses valid indexes.
Changed files must be reopened; cached results from their previous version are not reused, including in XY plots and cursor readouts.
Lazy reads run on the desktop worker even for short recordings.

The shared timestamp/summary RAM cache defaults to 1,024 MiB and is configurable with **Settings → Performance → RAM cache (MiB)**.
Prepared plot arrays are bounded by display budgets.
Cache limits are **not a hard process-RAM limit**: decoded batches, index-building scratch, FFTs, explicit NumPy conversions, exports and Python transformation plugins can allocate additional memory.
A full-recording FFT still needs its raw input and output arrays.
Histograms stream raw batches in two passes.
Node evaluation runs on a detached graph in a background worker.
Results are published on the application thread only if the graph and source inputs still match.
Editing inputs during evaluation discards the result; evaluate again to use the new settings.
Cancellation takes effect between reads and transforms; a running native transform returns before its cancellation can be observed.

Measurement caches stay in RAM by default; no automatic CSV conversion is written.
Enable **Settings → Data loading → Disk cache**, pass `--disk-cache`, or use `viewer.disk_cache(True)` to persist indexes and summaries and convert lazy CSV inputs into reusable Parquet files.
Reopen existing files to change their cache policy.
JSON sessions preserve the setting for each file.
In the GUI, disk caches live in `<checkout>/artifacts/_user/viewer_cache`, or in `viewer_cache` under the platform user-data directory when no checkout is selected.
`UZ_DATAVIEWER_CACHE` overrides this path.
Direct source-library use defaults to `~/.cache/ultrazohm_dataviewer`.
Polars uses a `polars/` subdirectory.
They are disposable and source-versioned; close the DataViewer before clearing that directory.
Disabling disk caching leaves existing cache files untouched and does not read them.
There is currently no automatic disk-cache size limit.
Read-only or full summary-cache storage falls back to RAM; enabled lazy CSV conversion requires writable cache space.

### Session format and analysis correctness

Sessions now use schema version 6 with explicit run identities, including repeated opens and identical filenames in different directories.
Node links preserve explicit input slots, including disconnected slots.
Canvas connection order does not change subtraction or division.
A failed restore leaves the current session intact.
Recreate version 1–5 snapshots and generated session scripts as version 6 JSON sessions.
Plot windows, precise time ranges and inactive recordings survive JSON round trips.
Restoring a session resets panel caches and canvas positions; Y fitting completes when lazy samples arrive.
Both primary and secondary Y limits survive JSON saves, including mouse zoom.
Removing a followed subplot switches its analysis windows to Full and discards the removed plot's cached range.
Recomputing a node preserves its derived recording's selected time origin.
Live snapshots and other memory-only recordings must be exported before saving a reloadable session.
Exporting does not attach the saved file to the existing snapshot.
Open the exported file, recreate plot assignments and node sources using that recording, then remove the memory-only snapshot before saving the session.
Node outputs derived from reloadable recordings are restored through their saved graph and do not require separate exports.
Chain transforms with node links; using derived outputs as new source nodes is no longer supported.
Analysis and exports use exact time windows, while plotting retains edge padding.
Full analysis covers all selected recordings regardless of selection order.
Linked time ranges apply immediately to scripts, exports and analysis, including before the first GUI frame.
Reset view updates the linked range to the selected plot's recording extent.
FFT inputs must be equal-length one-dimensional arrays.
FFT and FIR filters reject duplicate or irregular timestamps.
JavaScope logs identified by raw `CHn=n)` headers use their 10 ns timestamp resolution: samples must fit one uniform grid within ±5 ns plus floating-point roundoff.
This also applies after conversion to Parquet and time normalization.
Other inputs retain the 100 ppm interval tolerance.
For plain-array API calls, pass `timestamp_resolution=data.timestamp_resolution` from `data = uz.read(path)` to `uz.fft(...)` or `uz.filter(...)`; the default is unspecified precision, not an assumed JavaScope format.
No samples are resampled.
Binary math and XY plots require matching timestamps throughout both inputs; implicit index alignment and XY truncation have been removed.
XY limits and zoom survive session round trips without changing linked time axes.
Stale or failed derived outputs are blocked from plots, analysis and exports until successful reevaluation; existing assignments are preserved, including across JSON restoration.
Failed graphs restore with empty, unavailable output placeholders until repaired.
Source validation covers original CSV files even when reading a cached conversion.
JSON is the only saved-session format; generated session-script export has been removed.
Python automation uses `viewer.load_session("session.json")`; calls run sequentially and exceptions stop the script unless handled.
Completing an export dialog after its subplot was removed cancels the export.
FFT export validates every selected signal before writing: an invalid channel fails the export with its name and reason, preserving any existing destination file.
The FFT window reports each failed channel even when other channels succeed.
Plugin imports roll back their registrations on failure.
Existing transform kinds cannot be replaced at runtime; restart the DataViewer after editing a loaded plugin.

Division and reciprocal transforms preserve undefined samples as NaN gaps; FFTs reject those inputs rather than treating undefined values as zero.
Numeric node parameters must be finite, and integer parameters must fit a 32-bit integer.
Built-in and plugin parameter editors use the same declared types as validation.
Removing a recording immediately invalidates its analysis results.
Explicit FFT/histogram X limits survive recomputation; Reset view clears those limits.
These explicit analysis view limits also survive JSON session restoration.
Shared upstream nodes are validated once per traversal, avoiding exponential work in graphs with reused inputs.
Hann windows are released after each FFT.
Native CSV materialization uses checked batch allocation for both backends, including actual row counts and retained buffer capacity.
Parser scratch and transient growth copies remain outside the numeric-data budget.
Both CSV backends share missing-value spellings (including NA, NULL and NaN).

Session restoration rejects malformed coordinates, unknown plot types/styles, and invalid numeric settings before replacing the current session.
Commands use the same bounds: 1–100,000 histogram bins, 1–16 rows/columns, 2–1,000,000 display points, and 1–1,048,576 MiB of cache.
Mouse zoom in analysis windows persists through recomputation and JSON restoration.
FFT display sampling, including summary rebuilds after cache eviction, runs on a desktop worker.
Headless reads, conversions, and analysis do not import the GUI.
Import GUI entry points explicitly from `ultrazohm_dataviewer.app`; package-root GUI aliases were removed.

## Documentation

| Doc | For |
|-----|-----|
| **[Usage](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_usage.rst)** | Driving the app: panels, plots, analysis windows, Python automation, application log, full client API reference. |
| **[Architecture](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_architecture.rst)** | Developers: module map, the state-driven/command-routed design, internals, how to extend, testing, design decisions. |
| **[Build](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_build.rst)** | Tasks, desktop bundles and releases. |
| **[Plugins](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_plugins.rst)** | Writing your own node transforms as Python plugins. |
| **[Library](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_library.rst)** | Using the data/analysis core headlessly as a Python library (load logs, FFT, node transforms) — no GUI. |
| **[Roadmap](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_roadmap.rst)** | Open ideas and the record of what's already shipped. |
| **[DataViewer V Javascope](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer.rst)** | Application overview, installation, and links to analysis and live workflows. |

## Project layout

```
ultrazohm_dataviewer/
├── run.py                    # run from a source checkout (also accepts Python startup files)
├── src/ultrazohm_dataviewer/
│   ├── app.py                # docking layout, runner, theme, Session menu
│   ├── state.py              # AppState, SubplotCell, FFT/Histogram configs
│   ├── commands.py           # internal command metadata and handlers (public automation uses Client)
│   ├── console.py            # application activity log
│   ├── model.py              # Run / Signal / DataRegistry (+ time normalization)
│   ├── loader.py             # CSV/Parquet loading + channel-name parsing
│   ├── sources.py            # raw sources, bounded caches and min/max summaries
│   ├── downsample.py         # visible-window selection and display adapter
│   ├── analysis.py           # GUI-free transforms (FFT)
│   ├── transforms.py         # GUI-free node transforms (math, FIR filter)
│   ├── nodes.py              # dataflow graph + evaluation -> derived signals
│   ├── plugins.py            # external transform-node plugins (@transform, loader)
│   ├── session.py            # JSON save/restore + CSV export
│   └── panels/               # navigation, plots, analysis base, fft, histogram, nodes
├── tests/                    # pytest (logic via commands + headless rendering)
├── tasks.py                  # lint and test; Windows bundle and bundle-smoke
└── build/                    # PyInstaller spec and frozen smoke tests
```

Documentation lives in `../docs/source/guide/gui/ultrazohm_dataviewer/`.

## Tests

Run the same checks as CI, on Linux (dev container) or Windows:

```bash
./uz_developer check dataviewer                  # ruff and the full pytest suite, with a CLI wheel from this checkout
./uz_developer build linux_wheels           # build/install both applications
./uz_developer check linux_wheels           # includes GUI startup checks
```

Checks use temporary environments; developer builds update the persistent development environment.
`check` builds a debug ultrazohm-cli wheel from `../ultrazohm_cli` unless `--cli-wheel PATH` is given, so the live tests run against the same commit.
`./uz_developer check dataviewer` forwards to the same task implementation.
Linux CI runs it in the `ci` stage of `.devcontainer/Dockerfile`; Linux is distributed through Python wheels.
Windows standalone packaging copies the build system's libraries.

The Application log records supported operations.
Use JSON sessions to restore supported view settings.
FFT-derived plots use Hz, remain independent of linked time axes, and export a `frequency` column.
Time normalization and time-based analysis reject spectra.

Sampling and domain transitions ------------------------------

Timestamp roundoff allowances are bounded to one percent of a sample interval.
FFT and FIR reject axes whose absolute timestamp precision cannot establish that bound; binary math and XY never treat a sample-sized displacement as roundoff.
Graph domain resolution shares a per-evaluation cache and uses iterative traversal.
When a saved graph changes an output's domain, restoration discards its incompatible normalization and consumer assignments, matching live reevaluation.
Failed outputs retain their saved domain as unavailable placeholders until repaired.

## Live acquisition

### Python and terminal automation

The DataViewer hosts a local control API at `127.0.0.1:19741`.
Open an environment shell with `./uz venv dev`, then use ordinary Python or terminal commands.
Control commands attach to an existing application:

```bash
ultrazohm-dataviewer --endpoint 127.0.0.1:19741 gui
# Open directly on the live plots and controls (connection is still explicit):
ultrazohm-dataviewer --endpoint 127.0.0.1:19741 gui --live
# In another terminal:
ultrazohm-dataviewer status
ultrazohm-dataviewer load recording.csv
ultrazohm-dataviewer set-grid 3 2
ultrazohm-dataviewer --json list-runs
```

```python
from ultrazohm_dataviewer import Client

with Client() as viewer:
    run = viewer.load("recording.csv")
    viewer.set_grid(2, 1)
    viewer.add_signal(1, run, "current")
    view = viewer.create_view()
    viewer.add_signal(1, run, "current", view=view)
    viewer.save_session("analysis.json")
```

`Client` uses an explicit endpoint, then `UZ_DATAVIEWER_ENDPOINT`, then the default.
Each DataViewer instance needs a distinct endpoint.
Recording, node, and view handles belong to a session; removal or session replacement invalidates old handles.
`list_runs()`, `list_nodes()`, `list_plots()`, and `list_views()` inspect state.
Terminal subcommands use hyphens, Python methods use underscores.
Run `ultrazohm-dataviewer --help` or a subcommand's `--help` for signatures.
`--json` prints machine-readable results; failures return a nonzero exit code.

Calls execute sequentially for each client.
Loads and exports return when ready, while manual GUI interaction remains available.
Manual changes can occur between calls; interactive automation is not a deterministic batch transaction.
Client paths resolve from the caller's working directory.
Mutations are never retried automatically after a transport failure, because they may already have completed.

The **Python** panel is available in offline and live modes through **View → Python**.
The Python panel edits ordinary Python files.
Run saves the file and starts a fresh process in the DataViewer environment, with `UZ_DATAVIEWER_ENDPOINT` supplied.
**Managed device run** requires a connected ultrazohm-cli process, supplies `UZ_ACQUISITION_ENDPOINT`, locks manual device controls, and provides **Stop script + device**.
Ordinary **Stop script** terminates Python without issuing a hardware Stop.
External terminal processes remain externally owned.
A script can import both `ultrazohm_dataviewer.Client` and `ultrazohm_cli.Client`; the latter connects to the ultrazohm-cli process.

The **Application log** displays diagnostics and operation activity.
It has no command input.
`.uzscript` and the old `uz …` console shortcut are removed.
Use normal `.py` files and the acquisition package's terminal interface instead.
See [compare_recordings.py](examples/compare_recordings.py) for the two-recording PT1 comparison workflow.

JSON schema 6 snapshots preserve recording references, node graphs, analysis settings, and additional plot grids.
Recording paths are relative to the JSON file where possible.
Saves replace files atomically; failed restoration leaves the existing workspace intact.
Python variables, processes, and interpreter state are not persisted.
Wheel installations use their Python environment; frozen builds run scripts using bundled modules.
An external Python environment can also attach to either.
Choosing **Load state** manually stops app-owned scripts and clears pending startup automation before loading.
External scripts retain ownership of their processes; their old session handles are rejected after replacement.

Each DataViewer creates a random local control credential.
Python clients and the ultrazohm-dataviewer command discover it automatically in a private per-user directory under the OS temporary directory.
No token needs to be copied for normal use.
Credentials are removed on shutdown; a restarted DataViewer requires a new client.
The listener accepts only loopback connections and does not execute Python code from requests.

### Starting acquisition

The ordinary launcher and the bundle include the ultrazohm-cli; no Rust compiler is needed.
Startup does not connect to hardware; **Connect** starts acquisition; **Existing service → Attach** reuses an existing ultrazohm-cli process.
Relative recording arguments keep their original working directory.

Launching `ultrazohm-dataviewer` from an UltraZohm checkout (or any of its subdirectories) automatically selects that checkout for live mode.
`gui --live-repo PATH` overrides this default.
Outside a checkout, use **Live Data → Browse for ultrazohm_sw**; Browse also lets you switch to another checkout after startup.

Preparing the selected checkout asks the ultrazohm-cli for `channel-mapping --repo PATH` and, when preferences are missing, `profile --repo PATH`.
The ultrazohm-cli reads current headers and filters only built-in default assignments.
Metadata is returned directly; ordinary preparation creates no mapping cache file.
Preparation runs in the background, and failures appear in Live Data without closing the DataViewer.
Connect and Flash UZ require successful preparation; attaching to an existing ultrazohm-cli process does not.

Connect launches `serve --repo PATH --profile settings.json`.
The ultrazohm-cli process resolves the firmware configuration itself, strictly validates saved preferences, and exposes the effective configuration through `catalog`.
An existing ultrazohm-cli process keeps its loaded configuration until a coordinated flash replaces the session.
Restart the ultrazohm-cli process to select a different repository.
Select the checkout in the DataViewer, or pass `ultrazohm-dataviewer gui --live-repo PATH`.

`./uz venv stable|prerelease` opens a cached shell with both published applications.
`./uz venv dev` activates the persistent development environment.
Run `./uz_developer build linux_wheels` after source changes and restart applications.
All shell modes include dependencies declared in root `requirements.txt`.

**Flash UZ** submits a firmware job to the selected ultrazohm-cli process after confirmation.
The machine running ultrazohm-cli needs XSCT and a configured firmware checkout; an attached DataViewer does not need either locally.
The ultrazohm-cli process sends Stop, finalizes recordings, programs, reloads firmware configuration, and reconnects with a fresh session.
The control endpoint stays available and all clients observe the new session.
Logging starts idle.
The Application log shows job progress.
A terminal can initiate or inspect the same jobs.

Closing any attached DataViewer sends device Stop.
If the DataViewer started the ultrazohm-cli process, it also requests shutdown; otherwise the ultrazohm-cli process stays running.
An accepted shutdown waits for programming already underway to finish.
Other terminal clients observe Stop or, for a DataViewer-owned ultrazohm-cli process, its eventual shutdown.
Stop delivery is best effort when the device connection is unavailable.

Select local XSCT before starting a DataViewer-owned ultrazohm-cli process.
Once attached, tool capability comes from the ultrazohm-cli process; changing the local PATH does not configure a remote process.

- **Live Data** sits beside Navigation.
  **Connect** starts an ultrazohm-cli process at the selected endpoint and connects it to the device.
  **Existing service → Attach** attaches to an already running ultrazohm-cli process without changing its device connection.
  An existing ultrazohm-cli process owns its settings; session directory and channel mapping fields apply only when launching a new ultrazohm-cli process.
  The session directory must not exist.
  A sibling `<session>.service.log` contains ultrazohm-cli process startup diagnostics.
  Connection progress appears immediately above the controls, followed by a connected/data-reception indicator or an error.
  Progress and results also appear in the Console; connection buttons stay disabled while a request is pending.
- The 20 channel slots show the ultrazohm-cli process's requested assignments.
  Double-click a slot to choose an observable using case-insensitive fuzzy search.
  Use **Up/Down** to highlight a result, **Enter** to assign it, and **Esc** to cancel.
  Typing continues filtering the list after arrow navigation; editing the query highlights the first match.
  Matches accept gaps between characters, but require their original order; contiguous matches rank first.
  Selection is blocked while either stream is recording.
  A mapping/reconnect generation change clears live plot assignments and cached samples; drag the desired signals again.
- Drag channels into **Live Plots**.
  This reuses the normal plot renderer, grid, zooming and display downsampling, with independent live axes and drag targets.
  **Follow live** anchors the right edge at the newest sample.
  Mouse-wheel zoom changes X and Y like the ordinary Plots window; X zoom updates **Time depth (s)**.
  Live Plots uses exactly the ordinary Plots window's ImPlot mouse mapping, including its pan/box-selection buttons and modifier-based axis constraints; it does not remap buttons.
  Ordinary wheel and box zoom keep following: their X span becomes the time depth and the right edge returns to the newest samples.
  **Shift-modified zoom** enters **Inspect** and keeps the selected region, freezing the current bounded RAM snapshot while acquisition and logging continue.
  Horizontal panning also enters Inspect.
  Unchecking **Follow live** freezes the display in the same way.
  The slider controls the same X duration.
  In Inspect, normal cursor-centered zoom and pan work; the slider changes duration around the current view's center.
  Checking **Follow live** catches up to the newest samples at the chosen duration.
  **Reset view**, including a double-left-click on a plot or axis, also resumes Follow live and resets the subplot's axes while preserving the chosen time depth.
  The toolbar's Reset view resets all subplots; the popup and double-click reset the selected subplot.
  No disk/cloud history is fetched in either mode.
- **Freeze plot 1 for analysis** copies all channels in that plot's time window to Navigation and assigns its plotted signals to the normal Plots window.
  FFT, histogram and nodes can then consume stable samples.
  Snapshots are memory-only; export them if needed before closing the DataViewer.
- **Control** exposes Enable System, Enable Control, device Stop, user buttons 1–8, and a scrollable variable table populated from the ultrazohm-cli process's JSON mapping.
  Each row retains its own entered value; press **Enter** in that input to send it.
  A successful send highlights that value blue for 0.2 seconds.
  Editing, leaving a field, and filtering do not send commands.
  The filter narrows the table; rows follow command-ID order.
  Entered values are local, not device readbacks, and inputs are disabled while a Python script runs.
  Commands are sent without firmware acknowledgment; streamed platform state is shown separately.
  Error Reset is omitted because current firmware does not implement it.
- Fast and slow logging have independent Start/Stop controls and phase/error/path indicators.
  **Open completed log** opens the final Parquet through the ordinary lazy file workflow.
  Stopping logging does not stop acquisition or the device.
- **Existing service → Detach** leaves the ultrazohm-cli process and logging running.
  Closing the DataViewer shuts down a DataViewer-started ultrazohm-cli process; for an external ultrazohm-cli process it sends device Stop and leaves logging running.
  **Disconnect** and **Existing service → Shutdown** send device Stop, end acquisition, finalize logs, and shut down the ultrazohm-cli process.
  An external ultrazohm-cli can attach to the same endpoint throughout.

A polling worker uses `Client.read_since()` at up to 30 Hz and retains at most the ultrazohm-cli process's configured sample capacity.
Device commands, Connect, Shutdown and Flash UZ run on a separate worker with their own ultrazohm-cli process connection, so live plots keep updating while a command is in progress (polling pauses only during Flash UZ).
Each publication is an immutable NumPy-backed snapshot that also carries per-bucket minima/maxima, maintained incrementally as samples arrive; wide windows are drawn from these buckets, narrow windows from raw samples, using the existing background request scheduler.
The GUI does not read intermediate recording files.
The default ring covers 30 seconds at the configured sample rate (300,000 samples at 10 kHz; 3,000,000 at 100 kHz).
The slider's maximum automatically follows the ultrazohm-cli process capacity times its configured sample period, not a measured wall clock.
Your selected time depth is preserved and clamped when needed.
The plot shows only the samples received so far while the buffer fills.
Requests are paged independently of buffer capacity to respect the ultrazohm-cli response-size limit.
Stale data, backend errors and cursor resynchronization are shown in the UI.

To compare live-data preparation performance between machines, run this with the DataViewer's installed Python environment (PowerShell shown):

```powershell
python .\ultrazohm_dataviewer\build\benchmark_live.py --sample-rate 10000 --traces 3
```

Run this from a `./uz venv dev` shell; on Linux use the same script and options.
The benchmark simulates filling and wrapping the 30-second buffer and prints JSON timings for appends and preparing the visible traces.
It runs without hardware.
`--channels` defaults to 20: buffering work depends on acquired channels even when only three are plotted.
These are CPU timings, not GUI FPS; they exclude the ultrazohm-cli, network, graphics driver and competition between worker threads.
The reported ring allocation also excludes the ultrazohm-cli and older snapshots still held by Inspect or display readers.
The status bar's RAM cache is a separate cache and does not include these live buffers.

Live history is bounded by the RAM buffer, including while recording.
Full recording history during acquisition and cloud access are future adapters using the same source/query boundary.
Live windows/settings are not saved in offline sessions; analysis runs only on explicit frozen snapshots.
Session times follow the ultrazohm-cli's nominal sampling clock; transport gaps cannot currently be reconstructed.

GUI plot, FFT, and histogram exports run in the background using captured settings.
The Console reports completion or failure; one export per workspace runs at a time.
Closing the workspace cancels publication of an unfinished export.
Measurement-script completion terminates remaining child processes in its process group (on Windows, its job object) before manual controls are restored.

The Python panel starts hidden; open it with **View → Python**.
Set **Arguments** (quote values containing spaces) and **Working directory** before running.
Arguments are passed directly to Python without shell expansion; use forward slashes for Windows paths.
Scripts receive DataViewer and available acquisition endpoints through `UZ_DATAVIEWER_ENDPOINT` and `UZ_ACQUISITION_ENDPOINT`.
The ordinary runner stops the script process; **Managed device run** also provides the device Stop workflow.
Python client export calls wait for publication and raise on failure.
Startup Python files run sequentially after the GUI opens, so the DataViewer can process their requests; a failed startup script stops the sequence.

**Connect** starts a DataViewer-managed ultrazohm-cli process and connects to the selected device IP.
If an external ultrazohm-cli process already occupies that endpoint, use **Existing service → Attach**.
When attached to an ultrazohm-cli process whose device is disconnected, **Connect device** connects that ultrazohm-cli process to the displayed Device IP and port.
The address is resolved on the machine running ultrazohm-cli.
This also works through an SSH tunnel without a local firmware checkout.
The attachment status and device connection status are shown separately.
**Disconnect** sends shutdown (device Stop, recording finalization, and ultrazohm-cli process exit) and leaves the GUI open.
For a DataViewer-started ultrazohm-cli process it waits for process exit before enabling Connect again.
Each subsequent connection uses a fresh recording directory.
The **Existing service** section contains Attach, Detach (DataViewer only), and Shutdown; Disconnect also shuts down an attached external ultrazohm-cli process, whereas closing the GUI retains the ownership policy for external ultrazohm-cli processes.

### Workspace files and firmware tools

The DataViewer stores workspace files in `<workspace>/artifacts/_user/`.
Without a selected checkout it uses `%LOCALAPPDATA%\UltraZohm\ultrazohm_dataviewer` on Windows or `${XDG_DATA_HOME:-~/.local/share}/ultrazohm/ultrazohm_dataviewer` on Linux.
This directory holds `logs/`, `viewer.ini`, and the optional `viewer_cache/`.
Set `UZ_DATAVIEWER_CACHE` to override the cache path.

The DataViewer seeds missing `settings.json` from the ultrazohm-cli's standard profile, filtered against the selected checkout.
Edit `sample_period_us` and `initial_channels` before connecting, or explicitly use **Save startup profile** to save current channel assignments validated against the selected local firmware mapping.
**Save view preferences** separately saves layout, endpoint and display preferences without changing startup profiles; it also works when attaching without a local checkout.
Saving while disconnected preserves the existing startup assignments.
The DataViewer saves view preferences separately in `live_view.json` and restores them without connecting or writing to the device.

Use **Browse for XSCT** to select the Vitis launcher if it is missing from PATH.
The ultrazohm-cli stores the selection in `tools.json`.
Explicit ultrazohm-cli process `--xsct` overrides that selection; PATH is the fallback when no selection is saved.
Selecting a launcher does not change the DataViewer's PATH.
Attached DataViewers use the ultrazohm-cli process's tool capabilities.
Firmware operations require Vitis 2022.2, the workspace and its hardware export, and JTAG access.
Generate the Vitis workspace before using **Flash UZ**.
**Flash UZ** uses the ultrazohm-cli's embedded Tcl scripts, including in development builds, which capture local scripts when the ultrazohm-cli is built.
Later script edits require an ultrazohm-cli rebuild and ultrazohm-cli process restart unless `UZ_CLI_TCL_DIR` is explicitly set before ultrazohm-cli process startup.
Vitis IDE Run/Debug independently uses checkout scripts.
See [script selection and the runtime override](../ultrazohm_cli/README.md#which-tcl-scripts-run).
See the [ultrazohm-cli firmware guide](../ultrazohm_cli/README.md#vitis-workspace-build-and-jtag-programming) and the [DataViewer build guide](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_build.rst) for details.

## Python linting and formatting

This project owns its Ruff configuration and pinned version in `pyproject.toml`.
These tasks run Ruff in an isolated tool environment and do not build or install either application.
Run from the repository root:

```bash
./uz_developer task dataviewer lint
./uz_developer task dataviewer format
./uz_developer task dataviewer format-check
```

On Windows, use `.\uz_developer.ps1` with the same arguments.
`format` applies layout changes only; lint fixes and import sorting require explicit review.
The enabled lint rules are `F`, `E4`, `E7`, `E9`, `I`, `B`, `UP`, and `C4`.
The project's `check` task and CI enforce both lint and formatting.

## Import axes and migration

A single column named `time` or `frequency` selects the independent axis automatically.
FFT exports (`frequency,out`) therefore reopen as frequency-domain data in both loading modes and both backends.
Files with neither name, or with both names, show **Choose independent axis** when opened in the GUI.
Select the column and whether it represents seconds or Hz.
Cancellation skips that file.
Non-numeric axis columns are rejected.

Python and terminal automation specify the selection explicitly:

```python
data = read("measurement.csv", axis_column="seconds", axis_domain="time")
run = viewer.load("spectrum.csv", axis_column="hz", axis_domain="frequency")
viewer.convert("spectrum.csv", axis_column="hz", axis_domain="frequency")
```

```sh
ultrazohm-dataviewer load spectrum.csv --axis-column hz --axis-domain frequency
```

`load` and `convert` terminal commands control an already-running DataViewer.
`ultrazohm-dataviewer gui measurement.csv` opens the GUI.
`read()` works directly in Python without a GUI.
The Python dataset exposes `axis_column` and `axis_domain`; its historical `.time` array holds the selected independent axis in either domain.
`to_dataframe()` preserves the selected column name.
CSV plot exports use the canonical `time` or `frequency` header and reject signal-name collisions instead of overwriting the axis.

CSV-to-Parquet conversion writes axis metadata.
Sessions save each recording's column and domain, and cache identities include the column selection.
Existing schema-6 sessions without axis fields retain the former time/first-column selection.
Frequency-domain recordings reject time normalization and time-only analysis.
Earlier unsupported session schemas still require recreation.

The migration removes the custom command language and `.uzscript` runner, generated script export, automatic loading mode and its old memory-budget controls.
Use Python `Client` automation, JSON sessions, explicit memory/lazy loading and the retained-cache budget.
Old browser/Pyodide delivery and Linux standalone archives are not current distribution targets; Linux uses Python wheels.
JavaScope firmware compatibility remains supported.

Device Stop, recording Stop and ultrazohm-cli process shutdown have different meanings: device Stop leaves acquisition connected; stopping fast or slow logging finalizes only that stream; shutdown ends the ultrazohm-cli process and finalizes recordings.
Detaching a DataViewer from an externally owned ultrazohm-cli process leaves that ultrazohm-cli process running.
Live viewing uses bounded recent history; complete history browsing during acquisition and cloud storage remain future capabilities.
Acquisition timestamps use the nominal configured sampling period and cannot reconstruct transport gaps.

## Capability status

| Capability | Current maturity and validation |
| --- | --- |
| CSV/Parquet browsing, plotting and exports | Implemented; both backends, memory/lazy modes and axis roundtrips covered by regression tests. |
| FFT, histogram and node analysis | Implemented; domain constraints and session persistence covered by tests. |
| Python Client, terminal control and Python panel | Implemented; local control and startup ordering tested. |
| Live scope and fast/slow recording | Implemented; simulator integration covers control, finalization and disconnects. Physical-device acceptance remains pending. |
| Header discovery and Flash UZ | Implemented; parser and fake-tooling tests pass. Actual Vitis/JTAG acceptance remains pending. |
| Windows desktop distribution | Release-wheel bundling and smoke checks run in Windows CI; no local Windows execution is claimed. |
| Full recording-history browsing during acquisition; cloud storage | Future capabilities. |

The retained tests and pending hardware checklist are described in the [ultrazohm-cli validation guide](../ultrazohm_cli/README.md#hardware-acceptance-pending).
