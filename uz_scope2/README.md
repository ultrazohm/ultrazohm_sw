# UltraZohm Scope 2

Scope 2 is the modern live plotting client for UltraZohm and the successor to JavaScope. It keeps the existing firmware TCP protocol while using the same Dear ImGui, ImPlot, NumPy, and data tooling as `uz_dataviewer`.

The application provides automatic observable acquisition slots, remap-safe signal history, dockable multi-window plots, subplot grids, linked time axes, per-window live following, trigger navigation, line/scatter/stairs/XY plots, dual Y axes, sample markers, measurement cursors, a zoom spy, and raw visible-range CSV export.

## Run

From the repository root:

```bash
source /workspaces/ultrazohm_sw/uz_scope/.venv/bin/activate
pip install -e ./uz_dataviewer -e ./uz_scope2
uz-scope2
```

Run against the included protocol test server:

```bash
python javascope/test_server.py --port 5555
uz-scope2 --ip 127.0.0.1 --port 5555 --connect
```

Scope 2 has its own package, command, settings, layout, and single-instance port. It does not modify or replace the existing `uz_scope` installation.

## Documentation

- [Usage](docs/USAGE.md)
- [Architecture](docs/ARCHITECTURE.md)

## Development

```bash
source /workspaces/ultrazohm_sw/uz_scope/.venv/bin/activate
python -m pytest -q uz_scope2/tests
```

The standalone build entry point is `uz_scope2/build/build_native.sh`. Benchmark tools are under `uz_scope2/tools`.
