# Building the UltraZohm Data Viewer

> Usage: **[USAGE.md](USAGE.md)** · Internals/design: **[ARCHITECTURE.md](ARCHITECTURE.md)**

The viewer is a pure-Python `imgui_bundle` application. `imgui_bundle` ships
prebuilt native binaries (Dear ImGui, ImPlot, hello_imgui) for Windows, Linux
and macOS, so the same source runs on all desktop platforms, and can also be
executed in the browser via Pyodide. (CI for native + web builds lives in the
repo-root `.gitlab-ci.yml`.)

## 1. Run from source (any desktop OS)

```bash
pip install -r requirements.txt
python run.py
```

## 2. Native single-file executables (PyInstaller)

The build collects `imgui_bundle` and `pyarrow` (which carry native libraries)
into one self-contained binary.

### Linux / Ubuntu / macOS
```bash
./build/build_native.sh
# -> dist/uz_dataviewer
```

### Windows (PowerShell)
```powershell
.\build\build_native.ps1
# -> dist\uz_dataviewer.exe
```

Both wrap `pyinstaller build/uz_dataviewer.spec`. Cross-compiling is not
supported by PyInstaller — build each OS's binary on that OS (e.g. via a CI
matrix with `ubuntu-latest`, `windows-latest`, `macos-latest`).

## 3. Web / WASM (Pyodide)

```bash
./build/build_web.sh                      # writes web/index.html (self-contained)
cd web && python -m http.server 8000      # then open http://localhost:8000/
```

`build_web.sh` runs `build/gen_web.py`, which emits a single self-contained
`web/index.html` following the official imgui_bundle Pyodide template. At load
time the page:

1. loads Pyodide `v0.29.4` from the CDN and wires the WebGL canvas to SDL;
2. `micropip`-installs the **imgui_bundle WASM wheel** (hosted by pthom at
   `https://imgui-bundle.pages.dev/local_wheels/`) plus `numpy`/`pandas`/`pyarrow`
   from the Pyodide package index;
3. writes the embedded `uz_dataviewer` sources into the Pyodide FS and starts the
   app (in Pyodide `immapp.run()` is auto-patched to be non-blocking).

> **Why the old build hung at "Installing packages…":** imgui-bundle publishes
> **no WASM wheel to PyPI**, so `micropip.install("imgui-bundle")` could never
> resolve. The wheel must come from pthom's hosting, which the generator now uses.

### ⚠️ A local web server is required — `file://` does not work

Opening `index.html` directly from disk (`file://`) **fails**: the browser blocks
Pyodide's package downloads from a `file://` origin (documented imgui_bundle /
Pyodide limitation). Use any static server — `python -m http.server`, nginx,
GitHub Pages, S3, etc. The page still needs internet access at runtime to fetch
the Pyodide runtime and the wheels.

The only way to get a true *double-click-the-html, no-server* app would be a
**C++ + emscripten `SINGLE_FILE` rebuild** (embeds the wasm as base64 in one
HTML). That's a separate effort and would drop the Python data stack.

### Loading data in the browser

There is no OS file dialog in a tab, so the **Open file(s)…** button opens an
HTML file picker. Loading is synchronous (Pyodide has no worker threads):

- **Small files (≤ 200 MB) and any Parquet** are written to the Pyodide FS and
  parsed by Arrow as usual.
- **Large CSVs (> 200 MB)** are **stream-parsed in the browser** directly into
  per-column typed arrays (`webbridge.load_columns`): the File blob is read in
  chunks, so the multi-gigabyte *text* is never resident in 32-bit WASM memory —
  only the compact numeric result (time `float64` + channels `float32`).

The hard limit is wasm32's ~4 GB address space: the *numeric* arrays must fit
(≈ `rows × channels × 4` bytes), which is far smaller than the raw CSV but still
caps how big a log the browser can hold. The streaming loader estimates that
footprint up front and, **if it would exceed a safe budget (~1.5 GB), decimates
`1:stride` on the way in** and says so in the console (e.g. *"Loaded … decimated
1:3 … use the native app for full detail"*). So a file under the budget loads at
**full resolution**, and a genuinely huge one (e.g. a 5 GB log) loads a usable
**decimated** view instead of silently aborting the WASM runtime. For full
resolution on multi-GB logs, use the native app.

Web-specific notes:

- Version pins live in `build/gen_web.py` (`PYODIDE_VERSION`, `IMGUI_BUNDLE_WHEEL`).
  The wheel is built against one specific Pyodide release; if you bump one, bump
  the other to a compatible pair (see the imgui_bundle Pyodide docs).
- Downsampling is pure NumPy (the min/max pyramid in `downsample.py`), so the native
  and web builds run identical decimation code — no native/Rust dependency to wheel.

Reference: imgui_bundle Pyodide docs —
<https://pthom.github.io/imgui_bundle/python_pyodide.html>
