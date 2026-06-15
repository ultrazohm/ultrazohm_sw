# JavaScope vs. Data Viewer

A comparison of the two UltraZohm tools that deal with scope data, what each is for,
and how they relate.

> **TL;DR** — The **JavaScope** (`javascope/`) is a *live oscilloscope*: a Java/Swing
> application that connects to the UltraZohm hardware over TCP, streams scope channels in
> real time, triggers, scales, and sends commands/parameters **to** the device, and writes
> `Log_*.csv` files. The **Data Viewer** (`uz_dataviewer2/`) is an *offline post-processing
> viewer*: an ImGui/ImPlot desktop+web app that *reads* those logs for fast, interactive
> inspection. They are complementary, not competing — JavaScope **produces** the logs that
> the Data Viewer **consumes**. The Data Viewer is the modern successor to the legacy Plotly
> viewer `javascope/dataviewer.py`, **not** a replacement for the live Java scope.

---

## 1. The two tools at a glance

| | **JavaScope** (`javascope/`) | **Data Viewer** (`uz_dataviewer2/`) |
|---|---|---|
| Role | Live acquisition & device control | Offline log inspection & analysis |
| Tech | Java / Swing, JFreeChart (`UZ_GUI.jar`, `src/UZ_GUI/*.java`, ~23k LOC) | Python, Dear ImGui via `imgui_bundle` + ImPlot |
| Talks to hardware? | **Yes** — TCP socket to the UltraZohm (port 1000) | No — reads files only |
| Real-time? | Yes — streaming ring buffer | No — loads a complete log |
| Sends commands to device? | **Yes** — parameters, enable/control, buttons | No |
| Data direction | Receives stream, **writes** `Log_*.csv` | **Reads** `.csv` / `.parquet` |
| Platforms | Desktop JVM | Native (PyInstaller) + Web (Pyodide/WASM) |

There is also a **third, legacy artifact**: `javascope/dataviewer.py`, a Plotly/Dash web app.
`uz_dataviewer2` is its rewrite. See §4.

---

## 2. JavaScope — the live oscilloscope

The JavaScope is the operator console for the running UltraZohm. Its job is to talk to the
hardware while an experiment is live.

**Acquisition**
- Connects to the UltraZohm over TCP (default `192.168.1.233:1000`, configurable in
  `properties.ini`). `ReceiveController.java` (~4.1k LOC) decodes the incoming packet stream;
  `Transmitter.java` handles the socket.
- Streams **20 scope channels** (`scopeChannelNumber`), packed `MEASUREMENTS_PER_TCP_PACKET = 15`
  samples per TCP packet, into a `ScopeRingBuffer`.
- Time axis derived from `smallestTimeStepUSEC` (100 µs default) or auto-detected from packet
  rate (`autoDetectSamplingRate`).
- Channel headers parsed by `JavascopeHeaderParser.java`.

**Triggering** (a true scope feature the Data Viewer has no equivalent for)
- Configurable trigger channel, edge (rising/falling), threshold value, and pre-trigger
  fraction of the buffer (`properties.ini`: `triggerChannel`, `triggerEdge`, `triggerValue`,
  `pretrigger`).

**Display & conditioning**
- Live plot via `ScopeChartPanel` (JFreeChart), with auto-bounds / domain reset.
- Per-channel **scale** and **offset** (`initScaleCHx`, `initOffsetCHx`).
- Channel pre-selection and visibility toggles in the drop-downs.
- `MovingAverage.java` smoothing.

**Device control (the big differentiator)**
- `SendController.java` and `ParameterID.java` / `UZ_ParaID_view.java` let the operator set
  **parameters on the device** and issue commands: enable system, enable control, stop, error
  reset, custom buttons, data-channel selection (`CMD_*` constants visible in `test_server.py`).
- `ScopeDevPanel.java` — extended developer/test functions.

**Logging**
- Writes the `Log_*.csv` files (semicolon-separated, channel headers like `CH8=8)ia`) that the
  Data Viewer and the Matlab script (`JS_plot_data.m`) later read.

**Testing aid**
- `test_server.py` (~700 LOC) simulates the UltraZohm: it serves synthetic 20-channel scope
  data and accepts the command protocol, so the JavaScope can be exercised without hardware.

---

## 3. Data Viewer (`uz_dataviewer2`) — the offline analyzer

The Data Viewer never touches the hardware. It opens completed logs and makes large ones fast
to explore.

- **Loading** — `.csv` (JavaScope `;`-format, read with Arrow's multithreaded parser) and
  `.parquet`, multiple files at once, async on desktop.
- **Navigation** — Matlab-style tree of runs → channels; clean channel names + unit detection;
  (de)activate / remove runs.
- **Subplot grid** — runtime-settable layout (1×1 … 2×2 …), drag-and-drop a signal into any cell.
- **Plot types** — line / scatter / stairs / XY (per cell); plus **secondary (right) Y axis**,
  **cursors** (Δx/frequency/Δy), a **spy** zoom inset, per-sample markers, and per-cell **CSV export**.
- **Linked X axes** — pan/zoom one subplot, the rest follow ("lock time axis").
- **Range-aware downsampling** — MinMax-LTTB via `tsdownsample` against the visible window, so
  multi-gigabyte logs stay interactive (NumPy fallback on the web build).
- **FFT & Histogram windows** — overlay several signals over a selectable time window
  (follow a plot / full / custom), computed on demand, with CSV export.
- **Scriptable command console** — every action echoes a replayable command; the input runs the
  same commands; sessions save to JSON or a `.uzscript`.

What it deliberately does **not** do: connect to hardware, trigger, stream live, or send any
command to the device. Those are JavaScope's domain.

---

## 4. Relationship to the legacy `dataviewer.py`

`javascope/dataviewer.py` (~1.7k LOC, Plotly/Dash) is the **direct predecessor** of
`uz_dataviewer2`. It already offered, in a browser:

- 4 graph panels, load up to 2 files, **overlay-compare** both files on one graph;
- **cursors**, **export data** (with "start time at 0" relative-time option);
- a **secondary (right) y-axis** with its own channel selection;
- **shared/linked x-axis** across graphs;
- **plotly-resampler** downsampling for big logs.

`uz_dataviewer2` reimplements this offline-viewer concept on Dear ImGui/ImPlot for a native
docked desktop app (and a WASM web build), reusing the *decimation engine* (`tsdownsample`)
that lived under plotly-resampler — which is the only part of the old viewer that could be
carried over, since `FigureResampler` is bound to Plotly figures.

| Feature | `dataviewer.py` (legacy) | `uz_dataviewer2` (current) |
|---|---|---|
| UI stack | Plotly / Dash (browser) | Dear ImGui + ImPlot (native + WASM) |
| Layout | 4 fixed graph panels | Runtime grid, drag-drop signals |
| Big-log handling | plotly-resampler | `tsdownsample` MinMax-LTTB + NumPy fallback |
| Overlay / multi-file | Yes (2 files) | Yes (many runs) |
| Secondary Y axis | Yes | Yes |
| Cursors | Yes | Yes (Δx/frequency/Δy) |
| Export data | Yes | Yes (per-cell + FFT/Histogram, "start at 0") |
| FFT | No | Yes (dedicated window) + Histogram window |
| Scripting / command API | No | Yes (every action is a command; `.uzscript` replay) |

> The parity items the legacy `dataviewer.py` had over the early `uz_dataviewer2`
> (secondary y-axis, cursors, data export) have since been implemented, and the viewer
> now goes beyond it with the command/scripting layer, Histogram window, spy tool and
> per-log time normalization.

---

## 5. How they fit together

```
   UltraZohm hardware
        │  TCP :1000  (live stream, 20 ch)
        ▼
 ┌──────────────────────┐     commands / parameters
 │  JavaScope (Java)     │ ───────────────────────────►  back to device
 │  live scope + control │
 └──────────┬───────────┘
            │ writes
            ▼
      Log_*.csv  ──────────────┬───────────────► JS_plot_data.m (Matlab import)
                               │
                               ▼
                 ┌────────────────────────────┐
                 │  Data Viewer (uz_dataviewer2)│  offline inspection,
                 │  ImGui/ImPlot                │  FFT, downsampling
                 └────────────────────────────┘
```

- **JavaScope** is for *running an experiment*: connect, trigger, observe live, tune
  parameters, and record.
- **Data Viewer** is for *understanding the recording afterwards*: open one or many logs,
  arrange subplots, zoom into gigabyte-scale data, run FFTs.

**One forward-looking overlap:** the Data Viewer roadmap (`dataviewer_idea_list.txt`) calls
for a unified, scriptable **command API** — every click becomes a logged, replayable command.
That mirrors the JavaScope's existing "send commands to the device" model conceptually, but
the Data Viewer's commands act on the *view* (plots, layout, FFT), not on hardware. The two
could converge later (e.g. a scriptable tool that both controls acquisition and analyzes the
result), but for now they stay on opposite sides of the `Log_*.csv` boundary.
