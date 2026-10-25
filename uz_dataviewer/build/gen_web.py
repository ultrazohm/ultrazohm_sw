#!/usr/bin/env python3
"""Generate a self-contained Pyodide ``index.html`` for the data viewer.

Follows the official imgui_bundle Pyodide template
(https://imgui-bundle.pages.dev/min_pyodide_app/) :

* loads Pyodide from the CDN,
* wires the WebGL canvas to SDL,
* installs the imgui_bundle WASM wheel (hosted by pthom) plus numpy / pandas /
  pyarrow from the Pyodide package index,
* embeds every ``uz_dataviewer`` source as a ``<script type="text/python">`` tag
  (browsers keep the text verbatim -- no escaping, no extra fetches), writes
  them into the Pyodide virtual filesystem, then boots the app.

Browser specifics handled here: a hidden ``<input type="file">`` feeds chosen
files in (the OS file dialog used on desktop does not exist in a tab). Small
files / Parquet go through the Pyodide FS + ``webbridge.load_uploaded``; large
CSVs are stream-parsed into typed arrays and handed to ``webbridge.load_columns``
so the multi-gigabyte text never has to be resident in 32-bit WASM memory.

NOTE: the page must be served over HTTP (``python -m http.server``); opening it
via ``file://`` prevents Pyodide package loading (per the imgui_bundle docs).
"""

from __future__ import annotations

import os
import sys
import json
import runpy

# Versions are pinned for ABI compatibility: the imgui_bundle WASM wheel is built
# against one specific Pyodide/emscripten release.
PYODIDE_VERSION = "v0.29.4"
IMGUI_BUNDLE_WHEEL = "imgui_bundle-1.92.705-cp313-cp313-pyemscripten_2025_0_wasm32.whl"
# Upstream host the wheel is fetched from at build time...
IMGUI_BUNDLE_WHEEL_URL = f"https://imgui-bundle.pages.dev/local_wheels/{IMGUI_BUNDLE_WHEEL}"
# ...then vendored here and installed via a same-origin relative path, so the
# deployed site (e.g. GitHub Pages) has no third-party host dependency at runtime
# except the Pyodide CDN.
IMGUI_BUNDLE_WHEEL_REL = f"local_wheels/{IMGUI_BUNDLE_WHEEL}"
# Available in the Pyodide distribution. Downsampling is pure NumPy (the min/max
# pyramid in sources.py), so native and web run the same decimation code.
EXTRA_PACKAGES = ["numpy", "pandas", "pyarrow"]

HERE = os.path.dirname(os.path.abspath(__file__))
SRC_ROOT = os.path.join(HERE, "..", "src")
PKG_DIR = os.path.join(SRC_ROOT, "uz_dataviewer")


def _collect_sources() -> list[tuple[str, str]]:
    """Return (relative_path, source) for every package .py file."""
    sources: list[tuple[str, str]] = []
    for root, _, files in os.walk(PKG_DIR):
        for name in sorted(files):
            if not name.endswith(".py"):
                continue
            abs_path = os.path.join(root, name)
            rel = os.path.relpath(abs_path, SRC_ROOT).replace(os.sep, "/")
            with open(abs_path, encoding="utf-8") as fh:
                text = fh.read()
            if "</script>" in text:  # would break the embedding
                raise ValueError(f"{rel} contains a literal </script>; cannot embed")
            sources.append((rel, text))
    return sources


_BOOTSTRAP = """
import sys
sys.path.insert(0, "/app")
from uz_dataviewer.app import DataViewerApp

# In Pyodide, immapp.run() is auto-patched to be non-blocking, so this returns
# immediately and the GUI keeps animating via requestAnimationFrame.
_app = DataViewerApp()
_app.run()
"""


def build_html() -> str:
    sources = _collect_sources()
    null_values = runpy.run_path(os.path.join(PKG_DIR, "csv_policy.py"))["NULL_VALUES"]

    src_tags = "\n".join(
        f'<script type="text/python" class="uz-pysource" data-path="{rel}">\n{text}\n</script>'
        for rel, text in sources
    )
    bootstrap_tag = f'<script type="text/python" id="uzBootstrap">\n{_BOOTSTRAP}\n</script>'
    extra_installs = "\n        ".join(
        f'setStatus("Loading {p}..."); await micropip.install("{p}");' for p in EXTRA_PACKAGES
    )

    return f"""<!doctype html>
<!--
  UltraZohm Data Viewer -- web build (Pyodide).

  Serve over HTTP, e.g.:   python -m http.server 8000
  Then open:               http://localhost:8000/

  Opening via file:// will NOT work: the browser blocks Pyodide package loading.
-->
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>UltraZohm Data Viewer</title>
  <script src="https://cdn.jsdelivr.net/pyodide/{PYODIDE_VERSION}/full/pyodide.js"></script>
  <style>
    html, body {{ width: 100%; height: 100%; margin: 0; font-family: sans-serif; }}
    #canvas {{ display: block; width: 100%; height: 100%; }}
    #loader {{ position: fixed; inset: 0; display: flex; flex-direction: column;
               align-items: center; justify-content: center; gap: 16px;
               background: #1e1e1e; color: #eee; }}
    #loader::before {{ content: ""; width: 48px; height: 48px; border: 5px solid #444;
                       border-top-color: #eee; border-radius: 50%;
                       animation: spin 1s linear infinite; }}
    @keyframes spin {{ to {{ transform: rotate(360deg); }} }}
  </style>
</head>
<body>

<div id="loader">Loading Pyodide...</div>
<canvas id="canvas" tabindex="0"></canvas>
<input type="file" id="uzFileInput" accept=".csv,.parquet" multiple style="display:none">
<input type="file" id="uzSessionInput" accept=".json,.uzscript,.txt" style="display:none">

<!-- Embedded Python sources (written into the Pyodide FS before the app starts) -->
{src_tags}
{bootstrap_tag}

<script>
  const loaderEl = document.getElementById("loader");
  const setStatus = m => {{ if (loaderEl) loaderEl.textContent = m; }};
  const hideLoader = () => {{ if (loaderEl) loaderEl.remove(); }};
  const showError = e => {{ loaderEl.style.background = "#922";
                            setStatus("Error: " + (e?.message || e)); console.error(e); }};
  let pyodide = null;

  function writeSourcesToFs() {{
    // Recreate the package tree under /app from the embedded <script> tags.
    const mkdirp = (dir) => {{
      const parts = dir.split("/").filter(Boolean);
      let cur = "";
      for (const p of parts) {{ cur += "/" + p; try {{ pyodide.FS.mkdir(cur); }} catch (_) {{}} }}
    }};
    mkdirp("/app");
    for (const tag of document.querySelectorAll("script.uz-pysource")) {{
      const rel = tag.dataset.path;            // e.g. uz_dataviewer/panels/plots.py
      const full = "/app/" + rel;
      mkdirp(full.substring(0, full.lastIndexOf("/")));
      pyodide.FS.writeFile(full, tag.textContent);
    }}
  }}

  // Pyodide is 32-bit WASM (~4 GB ceiling). Small files are written to the FS and
  // parsed by Arrow as usual. Large CSVs would blow the ceiling if their whole
  // text were resident, so above this size we stream-parse them directly into
  // per-column typed arrays in the browser (full resolution) -- the huge text is
  // never held at once; only the compact numeric result is kept.
  const FULL_LOAD_LIMIT = 200 * 1024 * 1024;  // 200 MB

  function pyLoad(path, note) {{
    const py = "from uz_dataviewer.webbridge import load_uploaded; load_uploaded(" +
               JSON.stringify(path) + ", " + JSON.stringify(note || "") + ")";
    pyodide.runPython(py);
  }}

  // Run a snippet with the live AppState bound as `s` (for console messages).
  function pyRun(body) {{
    pyodide.runPython("from uz_dataviewer.webbridge import _active_state as s\\n" + body);
  }}

  let nextUploadId = 0;
  async function loadFull(file) {{
    const directory = "/uploads/" + (++nextUploadId);
    pyodide.FS.mkdir(directory);
    const path = directory + "/" + file.name;
    pyodide.FS.writeFile(path, new Uint8Array(await file.arrayBuffer()));
    pyLoad(path, "");
  }}

  // Stream-parse a large CSV directly into per-column typed arrays. The File blob
  // is disk-backed and read in chunks, so the multi-GB text is never resident;
  // only the compact numeric arrays (time float64 + channels float32) are kept,
  // which fit comfortably -- so the whole file loads at FULL resolution.
  async function loadStreamingCsv(file) {{
    const t0 = performance.now();
    const head = await file.slice(0, 256 * 1024).text();
    const headLines = Math.max(head.split("\\n").length - 1, 1);
    const avgLineBytes = Math.min(file.size, 256 * 1024) / headLines;

    // Preserve raw samples for analysis. Reject oversized recordings instead of
    // silently aliasing them through load-time stride decimation.
    const MEM_BUDGET = 1.5 * 1024 * 1024 * 1024;
    const firstLine = (head.split("\\n").find(l => l.trim() !== "")) || "";
    let commas = 0, semicolons = 0, quotedHeader = false;
    for (const ch of firstLine) {{
      if (ch === '"') quotedHeader = !quotedHeader;
      else if (!quotedHeader && ch === ',') commas++;
      else if (!quotedHeader && ch === ';') semicolons++;
    }}
    const delimiter = commas > semicolons ? "," : ";";
    const nDataCols = parseRow(firstLine).filter(s => s.trim() !== "").length - 1;
    if (nDataCols < 1) throw new Error("CSV must contain time and at least one signal column");
    const estRows = file.size / Math.max(avgLineBytes, 1);
    const bytesPerRow = 8 + 4 * nDataCols;
    const maxRows = Math.floor(MEM_BUDGET / bytesPerRow);
    const tooLarge = () => new Error("CSV exceeds the browser numeric-data budget; use the native app for full-resolution data.");
    if (estRows > maxRows) throw tooLarge();
    pyRun("s and s.console.info(" + JSON.stringify(
      "Parsing " + file.name + " in the browser, please wait...") + ")");
    let cap = Math.min(maxRows, Math.max(1024, Math.floor(estRows)));

    const reader = file.stream().getReader();
    const decoder = new TextDecoder();
    let remainder = "";
    let header = null;
    let fieldCount = 0;
    let timeIdx = 0;
    let dataIdx = [];       // field indices of the data columns
    let dataNames = [];     // their raw header names
    let timeArr = null;     // Float64Array
    let cols = [];          // Float32Array per data column
    let n = 0;
    let readBytes = 0;

    function grow(need) {{
      if (need > maxRows) throw tooLarge();
      if (need <= cap) return;
      const nc = Math.min(maxRows, Math.max(need, Math.ceil(cap * 1.5)));
      const nt = new Float64Array(nc); nt.set(timeArr.subarray(0, n)); timeArr = nt;
      for (let c = 0; c < cols.length; c++) {{
        const a = new Float32Array(nc); a.set(cols[c].subarray(0, n)); cols[c] = a;
      }}
      cap = nc;
    }}

    function parseRow(line) {{
      const fields = [];
      let field = "", quoted = false, closed = false;
      for (let i = 0; i < line.length; i++) {{
        const ch = line[i];
        if (quoted) {{
          if (ch === '"' && line[i + 1] === '"') {{ field += '"'; i++; }}
          else if (ch === '"') {{ quoted = false; closed = true; }}
          else field += ch;
        }} else if (ch === delimiter) {{
          fields.push(field); field = ""; closed = false;
        }} else if (ch === '"' && !field && !closed) quoted = true;
        else if (ch === '\\r' && i === line.length - 1) {{}}
        else if (closed || ch === '"') throw new Error("Malformed CSV quoting");
        else field += ch;
      }}
      if (quoted) throw new Error("Unclosed CSV quote (multiline fields are not supported by browser streaming)");
      fields.push(field);
      return fields;
    }}

    function numeric(field) {{
      const text = field.trim();
      if ({json.dumps(null_values)}.includes(text)) return NaN;
      if (/^[+]?inf(inity)?$/i.test(text)) return Infinity;
      if (/^-inf(inity)?$/i.test(text)) return -Infinity;
      if (!/^[+-]?(?:[0-9]+(?:\\.[0-9]*)?|\\.[0-9]+)(?:[eE][+-]?[0-9]+)?$/.test(text))
        throw new Error("Invalid numeric CSV value: " + text);
      return Number(text);
    }}

    function initHeader(line) {{
      const fields = parseRow(line);
      fieldCount = fields.length;
      const kept = [];
      for (let i = 0; i < fields.length; i++) {{
        const nm = fields[i].trim();
        if (nm !== "") kept.push([i, nm]);
      }}
      if (kept.length < 2 || new Set(kept.map(k => k[1])).size !== kept.length)
        throw new Error("CSV must contain distinct time and signal columns");
      let tPos = kept.findIndex(k => k[1] === "time");
      if (tPos < 0) tPos = 0;
      timeIdx = kept.length ? kept[tPos][0] : 0;
      for (let k = 0; k < kept.length; k++) {{
        if (k === tPos) continue;
        dataIdx.push(kept[k][0]);
        dataNames.push(kept[k][1]);
      }}
      timeArr = new Float64Array(cap);
      cols = dataNames.map(() => new Float32Array(cap));
    }}

    function pushRow(line) {{
      if (line.trim() === "") return;
      const f = parseRow(line);
      if (f.length !== fieldCount) throw new Error("CSV row has incorrect field count");
      grow(n + 1);
      timeArr[n] = numeric(f[timeIdx]);
      for (let c = 0; c < dataIdx.length; c++) cols[c][n] = numeric(f[dataIdx[c]]);
      n++;
    }}

    try {{
      while (true) {{
        const {{ done, value }} = await reader.read();
        if (done) break;
        readBytes += value.length;
        const parts = (remainder + decoder.decode(value, {{ stream: true }})).split("\\n");
        remainder = parts.pop();  // last (possibly partial) line
        for (const line of parts) {{
          if (header === null) {{ header = line; initHeader(line); continue; }}
          pushRow(line);
        }}
        console.log("Parsing " + file.name + ": " + (100 * readBytes / file.size).toFixed(0) + "%");
      }}
      if (header === null) initHeader(remainder); else pushRow(remainder.trim());
    }} finally {{
      await reader.cancel();
      reader.releaseLock();
    }}

    // Hand the compact typed arrays to Python (one copy into WASM; JS frees after).
    const bridge = pyodide.pyimport("uz_dataviewer.webbridge");
    bridge.load_columns(file.name, dataNames, cols.map(a => a.subarray(0, n)), timeArr.subarray(0, n));
    bridge.destroy();
    timeArr = null; cols = null;
    const secs = ((performance.now() - t0) / 1000).toFixed(1);
    console.log("Loaded " + file.name + ": " + n.toLocaleString() + " rows in " + secs + "s");
  }}

  function wireFileInput() {{
    const input = document.getElementById("uzFileInput");
    input.addEventListener("change", async (ev) => {{
      try {{ pyodide.FS.mkdir("/uploads"); }} catch (_) {{}}
      for (const file of ev.target.files) {{
        try {{
          const isCsv = file.name.toLowerCase().endsWith(".csv");
          if (isCsv && file.size > FULL_LOAD_LIMIT) await loadStreamingCsv(file);
          else await loadFull(file);
        }} catch (err) {{
          console.error(err);
          pyodide.runPython(
            "from uz_dataviewer.webbridge import _active_state as s\\n" +
            "s and s.console.error(" + JSON.stringify("Failed to read " + file.name + ": " + err) + ")");
        }}
      }}
      ev.target.value = "";  // allow re-selecting the same file
    }});
  }}

  // Session files (.json state / .uzscript) -- written to the FS then routed to
  // load_state / run_script by extension. Separate input from the data loader.
  function wireSessionInput() {{
    const input = document.getElementById("uzSessionInput");
    input.addEventListener("change", async (ev) => {{
      try {{ pyodide.FS.mkdir("/uploads"); }} catch (_) {{}}
      const file = ev.target.files[0];
      if (file) {{
        try {{
          const path = "/uploads/" + file.name;
          pyodide.FS.writeFile(path, new Uint8Array(await file.arrayBuffer()));
          pyodide.runPython(
            "from uz_dataviewer.webbridge import load_uploaded_session; load_uploaded_session(" +
            JSON.stringify(path) + ")");
        }} catch (err) {{
          console.error(err);
          pyRun("s and s.console.error(" + JSON.stringify("Failed to read " + file.name + ": " + err) + ")");
        }}
      }}
      ev.target.value = "";  // allow re-selecting the same file
    }});
  }}

  async function main() {{
    const canvas = document.getElementById("canvas");
    canvas.addEventListener("contextmenu", e => e.preventDefault());

    setStatus("Loading Pyodide...");
    pyodide = await loadPyodide();

    // SDL/WebGL canvas setup, cf https://pyodide.org/en/stable/usage/sdl.html
    pyodide.canvas.setCanvas2D(canvas);
    pyodide._api._skip_unwind_fatal_error = true;

    setStatus("Loading micropip...");
    await pyodide.loadPackage("micropip");
    const micropip = pyodide.pyimport("micropip");

    setStatus("Loading imgui_bundle (WASM wheel)...");
    await micropip.install("{IMGUI_BUNDLE_WHEEL_REL}");

    {extra_installs}

    setStatus("Starting viewer...");
    writeSourcesToFs();
    wireFileInput();
    wireSessionInput();
    pyodide.runPython(document.getElementById("uzBootstrap").textContent);
    hideLoader();
  }}
  main().catch(showError);
</script>
</body>
</html>
"""


def _vendor_wheel(out_dir: str) -> None:
    """Download the imgui_bundle WASM wheel into web/local_wheels/ (idempotent)."""
    import urllib.request

    dest_dir = os.path.join(out_dir, "local_wheels")
    os.makedirs(dest_dir, exist_ok=True)
    dest = os.path.join(dest_dir, IMGUI_BUNDLE_WHEEL)
    if os.path.exists(dest) and os.path.getsize(dest) > 0:
        print(f"  wheel already vendored: {dest} ({os.path.getsize(dest):,} bytes)")
        return
    print(f"  downloading wheel: {IMGUI_BUNDLE_WHEEL_URL}")
    # Cloudflare (pages.dev) rejects the default Python-urllib User-Agent (403),
    # so present a browser-like one.
    req = urllib.request.Request(
        IMGUI_BUNDLE_WHEEL_URL, headers={"User-Agent": "Mozilla/5.0 (build script)"}
    )
    with urllib.request.urlopen(req) as resp, open(dest, "wb") as fh:
        fh.write(resp.read())
    print(f"  vendored: {dest} ({os.path.getsize(dest):,} bytes)")


def main() -> int:
    out_dir = os.path.join(HERE, "..", "web")
    os.makedirs(out_dir, exist_ok=True)

    _vendor_wheel(out_dir)

    # Disable Jekyll so GitHub Pages serves files verbatim (no _-path mangling).
    open(os.path.join(out_dir, ".nojekyll"), "w").close()

    out_path = os.path.join(out_dir, "index.html")
    with open(out_path, "w", encoding="utf-8") as fh:
        fh.write(build_html())
    print(f"Wrote {os.path.abspath(out_path)}")
    print(f"  Pyodide:      {PYODIDE_VERSION}")
    print(f"  imgui_bundle: {IMGUI_BUNDLE_WHEEL} (vendored, same-origin install)")
    print("Deploy: push the web/ folder to GitHub Pages, or serve locally with")
    print("        (cd web && python -m http.server 8000)  then open http://localhost:8000/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
