# Building the UltraZohm Data Viewer

The viewer is a pure-Python `imgui_bundle` application. `imgui_bundle` ships
prebuilt native binaries (Dear ImGui, ImPlot, hello_imgui) for Windows, Linux
and macOS, so the same source runs on all desktop platforms, and can also be
executed in the browser via Pyodide.

## 1. Run from source (any desktop OS)

```bash
pip install -r requirements.txt
python run.py
```

## 2. Native single-file executables (PyInstaller)

The build collects `imgui_bundle`, `pyarrow` and `tsdownsample` (which carry
native libraries) into one self-contained binary.

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
HTML file picker. The chosen file is written into the Pyodide virtual filesystem
and loaded synchronously (Pyodide has no worker threads). Prefer Parquet or
pre-trimmed CSV — pushing multi-GB logs through the browser is impractical.

Web-specific notes:

- Version pins live in `build/gen_web.py` (`PYODIDE_VERSION`, `IMGUI_BUNDLE_WHEEL`).
  The wheel is built against one specific Pyodide release; if you bump one, bump
  the other to a compatible pair (see the imgui_bundle Pyodide docs).
- `tsdownsample` (Rust) has no Pyodide wheel; `downsample.py` automatically uses
  its pure-NumPy MinMax fallback there.

Reference: imgui_bundle Pyodide docs —
<https://pthom.github.io/imgui_bundle/python_pyodide.html>
