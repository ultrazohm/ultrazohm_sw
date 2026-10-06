# uz_scope

Modern live-scope GUI for the UltraZohm — the JavaScope replacement.
Built on the same stack as `uz_dataviewer` (Dear ImGui / ImPlot via
`imgui_bundle`, NumPy), speaking the existing JavaScope TCP protocol
against unmodified firmware.

Docs: `docs/source/guide/gui/uz_scope/` (usage, architecture, build).

## Install and run (from repo root)

```bash
pip install -e ./uz_dataviewer -e ./uz_scope
python uz_scope/run.py                       # or: uz-scope
```

Without hardware, use the test server:

```bash
python javascope/test_server.py --port 5555
python uz_scope/run.py --ip 127.0.0.1 --port 5555 --connect
```

## Develop

```bash
python -m pytest uz_scope/tests              # unit + integration tests
./build/build_native.sh                      # standalone executable (dist/uz_scope)
```

Performance harness (design target 200 ch x 100 kHz = 80.8 MB/s):

```bash
python uz_scope/tools/bench_server.py --channels 200 --rate 100000
python uz_scope/tools/bench_client.py --channels 200 --rate 100000 --seconds 60
```

## Layout

- `src/uz_scope/` — GUI-free core (`protocol`, `javascope_header`, `config`,
  `netclient`, `ring`, `acquisition`, `history`, `slowdata`, `capture_log`,
  `lifecheck`, `dashboard`, `commands`, `state`, `session`) plus the ImGui
  `app`/`panels` (multi plot windows, logged variables, observables browser,
  dashboard canvas, control, …).
- `tools/` — benchmark firehose server, soak client, parse micro-benchmark.
- `tests/` — pytest suite (run in CI); also spawns `javascope/test_server.py`
  end-to-end and round-trips logs through `uz_dataviewer.loader`.
- `build/` — PyInstaller spec and build script.
