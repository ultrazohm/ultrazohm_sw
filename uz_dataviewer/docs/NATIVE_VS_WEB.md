# Native vs Web

The same `uz_dataviewer` Python runs on the desktop **and** in the browser. Native is
CPython (a PyInstaller-frozen interpreter); web is **Pyodide** (CPython compiled to
WebAssembly). One flag, `webbridge.IS_WEB`, gates the handful of places they differ.

The UI, the command layer, plots, FFT/Histogram, nodes, and the downsampler are
**identical** on both. The differences are all at the edges: file I/O, threading, and the
WASM memory ceiling.

For building each target see **[BUILD.md](BUILD.md)**; for internals see
**[ARCHITECTURE.md](ARCHITECTURE.md#10-native-vs-web-webbridgepy)**.

---

## At a glance

| Concern | Native (desktop) | Web (Pyodide/WASM) |
|---|---|---|
| **Runtime** | CPython, frozen by PyInstaller | CPython → WebAssembly (Pyodide) |
| **Distribution** | One self-contained executable | A static web page (must be served over HTTP) |
| **File open** | OS file dialog (`portable_file_dialogs`) + drag files onto the window (GLFW) | Hidden HTML `<input type=file>` picker |
| **Loading** | Async on a `ThreadPoolExecutor` | **Synchronous** (Pyodide has no worker threads) |
| **Large CSV** | Arrow reads the whole file | **> 200 MB** is **stream-parsed** into typed arrays; ≤ 200 MB CSV and any Parquet still go through Arrow |
| **Downsampler** | Min/max pyramid (pure NumPy) | **Identical** — same code, no native dependency |
| **Export / Save** | OS save dialog | Browser download (Blob + anchor); **Session save/restore menu disabled** |
| **Memory** | OS RAM | Hard ~4 GB wasm32 address space |
| **Internet needed?** | No | **Yes at load** — fetches the Pyodide runtime + wheels |

---

## Why these differences exist

### File access
On the desktop you can open files via the OS dialog **or drag `.csv`/`.parquet` files onto
the window** (a GLFW drop callback; a no-op without the GLFW backend). A browser tab has no OS
file dialog, so **Open file(s)…** opens an HTML picker instead.
Saving works the same way in reverse: native pops an OS save dialog; web triggers a
**browser download** via `webbridge.download` (a Blob + a synthetic anchor click).
Because there's no OS path to write back to, the **Session menu's save/restore is disabled
on web** — you can still drive everything through the command console and `.uzscript`.

### Threading
Native loads files on a background `ThreadPoolExecutor` so the UI keeps rendering during a
big parse. Pyodide has **no worker threads**, so web loads **synchronously** — the tab
blocks for the duration of the parse.

### Large CSVs and the memory ceiling
The real constraint on web is wasm32's **~4 GB address space**. What matters is not the
raw text size but the **numeric** footprint after parsing (`rows × channels × 4` bytes for
`float32` channels + a `float64` time axis).

- **≤ 200 MB CSV and any Parquet** are written to the Pyodide FS and parsed by Arrow, same
  as native.
- **CSV > 200 MB** is **stream-parsed in the browser** directly into per-column typed
  arrays (`webbridge.load_columns`): the file blob is read in chunks, so the multi-gigabyte
  *text* never sits in WASM memory — only the compact numeric result.

The streaming loader **estimates the numeric footprint up front** and, if it would exceed a
safe budget (~1.5 GB), **decimates `1:stride` on the way in** and says so in the console
(e.g. *"Loaded … decimated 1:3 … use the native app for full detail"*). So a log under the
budget loads at **full resolution**, and a genuinely huge one (e.g. 5 GB) loads a usable
**decimated** view instead of silently aborting the WASM runtime. **For full resolution on
multi-GB logs, use the native app.**

### Downsampling is the same on both
The decimator is a pure-NumPy min/max pyramid (`downsample.py`) — there is no native/Rust
dependency to wheel for the browser, so native and web run **exactly the same** decimation
code. (This is why the legacy `tsdownsample` dependency was dropped.)

---

## Web-only operational notes

- **A local web server is required — `file://` does not work.** The browser blocks
  Pyodide's package downloads from a `file://` origin. Serve the page over HTTP
  (`python -m http.server`, nginx, GitHub/GitLab Pages, S3, …).
- **Internet access is needed at runtime** to fetch the Pyodide runtime and the wheels
  (the `imgui_bundle` WASM wheel from pthom's hosting, plus `numpy`/`pandas`/`pyarrow`).
- **Version pins matter:** the `imgui_bundle` wheel is built against one specific Pyodide
  release. If you bump one (`PYODIDE_VERSION` / `IMGUI_BUNDLE_WHEEL` in `build/gen_web.py`),
  bump the other to a compatible pair.
- A true *double-click-the-HTML, no-server* app would require a **C++ + emscripten
  `SINGLE_FILE` rebuild** (embedding the wasm as base64), which would drop the Python data
  stack — a separate effort, not this app. See [BUILD.md](BUILD.md#3-web--wasm-pyodide).

---

## What is identical

So it's clear how little actually diverges: the **command API and console**, **plots**
(types, cursors, spy, secondary axis, linked X, CSV export), **FFT & Histogram windows**,
the **node graph** and built-in transforms, **range-aware downsampling**, and the
**`.uzscript`** replay all behave the same on native and web. Plugins are native-first
(real filesystem + `importlib`); web plugin loading is a future idea — see
[PLUGINS.md](PLUGINS.md) and [ROADMAP.md](ROADMAP.md).
