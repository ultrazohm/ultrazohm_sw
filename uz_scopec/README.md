# uz_scopec — UltraZohm live scope (C++)

Native C++20 port of [`uz_scope`](../uz_scope) built on Dear ImGui + ImPlot:
the same wire protocol, panels, trigger engine, diagnostics and command
console — plus **multiple plot windows**, each with a subplot grid, that can
be dragged outside the main window to become real OS windows (ImGui
multi-viewport).

It speaks the JavaScope TCP protocol against **unmodified firmware**
(`192.168.1.233:1000` by default) and parses `javascope.h` for observable
names, button ids and field labels, exactly like the Python scope.

## Build

Ubuntu / Debian:

```bash
sudo apt-get install -y build-essential cmake ninja-build libgl-dev xorg-dev \
    libwayland-dev libxkbcommon-dev wayland-protocols
./build_ubuntu.sh
./build/uz_scopec
```

Windows (Visual Studio 2022 + CMake + Git):

```bat
build_windows.bat
build\Release\uz_scopec.exe
```

All libraries (GLFW, Dear ImGui docking, ImPlot, nlohmann_json, doctest) are
fetched by CMake at configure time; no vcpkg or system GUI packages needed.
The result is a single ~5 MB binary.

## Try it without hardware

```bash
python javascope/test_server.py --port 5555        # from the repo root
uz_scopec/build/uz_scopec --ip 127.0.0.1 --port 5555 --connect
```

The test server is lock-step, so leave *ack pacing* on (the default).

## Multiple plot windows

- **`+ Plot window`** in the Scope 1 toolbar (or the `plot_add` command) opens
  another independent plot window; drag it outside the main window to make it
  a separate OS window.
- Every plot window has a **grid selector** (1x1, 1x2, 2x2, ... up to 4x4);
  each cell is its own plot with its own axes.
- **Drag a row from the Channels table into any cell** to plot that channel
  there; right-click a legend entry to remove it again.
- Scope 1's first cell additionally mirrors the classic per-channel *visible*
  checkboxes, so it behaves exactly like the single-plot scope.
- Layouts persist in `uz_scopec_settings.json` (`plots` section) and the
  window arrangement in `uz_scopec_layout.ini`.

## Differences to the Python uz_scope

- Logging formats are **csv** and **bin** (the raw-float32 spill with the
  same JSON sidecar, so `uz_scope`'s tools and the Data Viewer convert it);
  Parquet needs the Arrow C++ stack and stays a Python-scope feature for now.
- `properties.ini` import, session scripts (`export_script`/`run_script`) and
  the single-instance guard are not ported yet.
- Everything else is a 1:1 port, including the command console (`help` lists
  all commands), rate auto-detection, the lifecheck continuity monitor
  (firmware wrap at 1000), external log trigger (status bit 12) and the
  JavaScope-parity trigger overlay semantics.

## Tests

`ctest --test-dir build` runs the doctest suite (protocol golden frames,
header parser against the real `javascope.h`, ring wraparound, trigger edge
cases, lifecheck wrap, config round-trip, CSV/bin logger round-trip, command
dispatch). The build scripts run it automatically.
