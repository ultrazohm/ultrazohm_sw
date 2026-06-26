#!/usr/bin/env bash
# Build the UltraZohm Data Viewer as a web (WASM) app via Pyodide.
#
# imgui_bundle runs the *same* Python sources in the browser through Pyodide
# (CPython compiled to WebAssembly, rendering via WebGL). This script generates
# a single self-contained `web/index.html` with the Python embedded.
#
#   ./build/build_web.sh
#   (cd web && python -m http.server 8000)   # then open http://localhost:8000/
#
# IMPORTANT: the page must be served over HTTP. Opening index.html directly via
# file:// does NOT work -- the browser blocks Pyodide's package downloads (a
# Pyodide/browser limitation, documented by imgui_bundle). The only true
# "double-click an .html, no server" path would be a C++/emscripten SINGLE_FILE
# rebuild, which is a separate effort.
#
# Runtime requirements (fetched by the browser, not bundled): internet access to
# the Pyodide CDN and the imgui_bundle WASM wheel. numpy/pandas/pyarrow come from
# the Pyodide package index; tsdownsample has no WASM wheel, so downsampling uses
# the pure-NumPy fallback in downsample.py.
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
rm -rf "$HERE/web"
python3 "$HERE/build/gen_web.py"
