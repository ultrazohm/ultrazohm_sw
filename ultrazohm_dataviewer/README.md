# DataViewer (`ultrazohm_dataviewer`)

The DataViewer opens CSV and Parquet recordings and plots live measurements on Windows and Linux.
It supports linked subplots, FFTs, histograms, and node transforms.
Use `ultrazohm_dataviewer.Client` or the terminal commands to automate an open DataViewer.
Save and restore your analysis as a JSON session.

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
Use **View → New plot window** for a grid with independent plot settings and shared recordings.
Run `ultrazohm-dataviewer --help` for application commands.

**UltraZohm Dataviewer → Settings** holds the log browser directory, loading mode, disk cache, RAM cache limit and display points.
Settings persist as application defaults; session files keep their own data and plot settings.

## Live acquisition

**Live Data → Connect** starts the bundled ultrazohm-cli service and connects it to the UltraZohm; **Existing service → Attach** shares a running service.
Device Stop leaves acquisition connected, stopping a logging stream finalizes only that stream, and shutdown ends the service after finalizing recordings.
See the [live guide](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_live.rst) for setup, the Live Data panel, Flash UZ and file locations.

## Automation

The DataViewer hosts a local control API at `127.0.0.1:19741`:

```python
from ultrazohm_dataviewer import Client

with Client() as viewer:
    run = viewer.load("recording.csv")
    viewer.set_grid(2, 1)
    viewer.add_signal(1, run, "current")
    viewer.save_session("analysis.json")
```

The same operations exist as terminal subcommands, for example `ultrazohm-dataviewer set-grid 3 2`.
**View → Python** runs ordinary Python files against the open DataViewer and, as a managed device run, against the acquisition service.
See [compare_recordings.py](examples/compare_recordings.py) for a two-recording comparison.

## Documentation

| Doc | For |
|-----|-----|
| **[Overview](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer.rst)** | Application overview, installation, and links to analysis and live workflows. |
| **[Usage](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_usage.rst)** | Panels, loading modes, axes, analysis windows, sessions, Python automation and the client API reference. |
| **[Live](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_live.rst)** | Connecting, recording, the Live Data panel, lifecycle and file locations. |
| **[Workflows](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_workflows.rst)** | End-to-end examples. |
| **[Architecture](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_architecture.rst)** | Module map, design, loading and memory behavior, testing and design decisions. |
| **[Build](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_build.rst)** | Tasks, linting, desktop bundles and releases. |
| **[Plugins](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_plugins.rst)** | Writing node transforms as Python plugins. |
| **[Library](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_library.rst)** | Using the data and analysis core headlessly. |
| **[Roadmap](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_roadmap.rst)** | Deliberate limits and capability status. |

## Project layout

```
ultrazohm_dataviewer/
├── run.py                    # run from a source checkout (also accepts Python startup files)
├── src/ultrazohm_dataviewer/
│   ├── app.py                # docking layout, runner, theme, Session menu
│   ├── state.py              # AppState, SubplotCell, FFT/Histogram configs
│   ├── commands.py           # command metadata and handlers (public automation uses Client)
│   ├── live.py               # live controller, ring buffer and live sources
│   ├── model.py              # Run / Signal / DataRegistry (+ time normalization)
│   ├── loader.py             # CSV/Parquet loading + channel-name parsing
│   ├── sources.py            # raw sources, bounded caches and min/max summaries
│   ├── extrema.py            # shared min/max bucket reduction
│   ├── analysis.py           # GUI-free transforms (FFT)
│   ├── transforms.py         # GUI-free node transforms (math, FIR filter)
│   ├── nodes.py              # dataflow graph + evaluation -> derived signals
│   ├── plugins.py            # external transform-node plugins (@transform, loader)
│   ├── session.py            # JSON save/restore + CSV export
│   └── panels/               # navigation, plots, live, analysis, nodes, Python
├── tests/                    # pytest (logic via commands + headless rendering)
├── tools/                    # client generator and release tooling
├── tasks.py                  # lint, test, wheel, Windows bundle
└── build/                    # PyInstaller spec and frozen smoke tests
```

## Tests

Run the same checks as CI from the repository root, on Linux (dev container) or Windows (`.\uz_developer.ps1`):

```bash
./uz_developer dataviewer check     # Ruff and the full pytest suite, with a CLI wheel from this checkout
./uz_developer verify linux         # release checks of the built pair, including GUI startup
```

`check` builds a debug ultrazohm-cli wheel from `../ultrazohm_cli` unless `--cli-wheel PATH` is given, so the live tests run against the same commit.
See the [build guide](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_build.rst) for all tasks.
