# PyInstaller spec for the UltraZohm Data Viewer.
#
# Produces a self-contained folder with a native executable and _internal.
# Build with:
#
#     pyinstaller build/uz_dataviewer.spec
#
# imgui_bundle ships compiled extensions plus fonts/assets that must be bundled,
# so we collect the whole package. pyarrow carries native libraries which
# PyInstaller's hooks pick up automatically.

import os
import sys

from PyInstaller.utils.hooks import collect_all, collect_submodules

# Resolve paths relative to this spec file (PyInstaller sets SPECPATH).
SRC = os.path.abspath(os.path.join(SPECPATH, "..", "src"))
# Make `uz_dataviewer` importable while the spec is analysed.
if SRC not in sys.path:
    sys.path.insert(0, SRC)

from pathlib import Path
script_root = Path(SPECPATH).resolve().parents[1] / 'tcl_scripts'
datas = [(str(path), str(Path('tcl_scripts') / path.parent.relative_to(script_root)))
         for path in script_root.rglob('*.tcl')]
datas += [(str(script_root.parent / 'vitis/software' / name), 'tcl_scripts/launch')
          for name in ('Debug_UltraZohm.launch', 'Run_UltraZohm.launch',
                       'Debug_UltraZohm_fast_restart_PL_reset.launch')]
binaries, hiddenimports = [], []
for pkg in ("imgui_bundle", "pyarrow", "polars", "_polars_runtime_32", "ultrazohm"):
    d, b, h = collect_all(pkg)
    datas += d
    binaries += b
    hiddenimports += h

# Bundle our own package (entry point imports it absolutely).
hiddenimports += collect_submodules("uz_dataviewer")

a = Analysis(
    [os.path.join(SPECPATH, "entrypoint.py")],
    pathex=[SRC, SPECPATH],
    binaries=binaries,
    datas=datas,
    hiddenimports=hiddenimports,
    hookspath=[],
    runtime_hooks=[],
    excludes=[],
)

pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    [],
    exclude_binaries=True,
    name="uz_dataviewer",
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    console=False,  # GUI app: no console window on Windows
)

coll = COLLECT(exe, a.binaries, a.datas, strip=False, upx=False, name="uz_dataviewer")
