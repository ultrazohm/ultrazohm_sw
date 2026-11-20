# PyInstaller spec for the UltraZohm Data Viewer.
#
# Produces a self-contained folder with a native executable and _internal.
# Build with:
#
#     pyinstaller build/ultrazohm_dataviewer.spec
#
# imgui_bundle ships compiled extensions plus fonts/assets that must be bundled,
# so we collect the whole package. pyarrow carries native libraries which
# PyInstaller's hooks pick up automatically.

import os
import sys

from PyInstaller.utils.hooks import collect_all, collect_data_files, collect_submodules, copy_metadata

# Freeze the installed wheel, never the repository's editable source.
import importlib.util
PACKAGE = os.path.dirname(importlib.util.find_spec("ultrazohm_dataviewer").origin)

from pathlib import Path
script_root = Path(SPECPATH).resolve().parents[1] / 'tcl_scripts'
datas = [(str(path), str(Path('tcl_scripts') / path.parent.relative_to(script_root)))
         for path in script_root.rglob('*.tcl')]
datas += [(str(script_root.parent / 'vitis/software' / name), 'tcl_scripts/launch')
          for name in ('Debug_UltraZohm.launch', 'Run_UltraZohm.launch',
                       'Debug_UltraZohm_fast_restart_PL_reset.launch')]
binaries, hiddenimports = [], []
for pkg in ("imgui_bundle", "pyarrow", "polars", "_polars_runtime_32", "ultrazohm_cli"):
    d, b, h = collect_all(pkg)
    datas += d
    binaries += b
    hiddenimports += h

# Bundle our own package (entry point imports it absolutely).
hiddenimports += collect_submodules("ultrazohm_dataviewer")
datas += collect_data_files("ultrazohm_dataviewer")
datas += copy_metadata("ultrazohm-dataviewer")

a = Analysis(
    [os.path.join(SPECPATH, "entrypoint.py")],
    pathex=[SPECPATH],
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
    name="ultrazohm-dataviewer",
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    console=False,  # GUI app: no console window on Windows
    icon=os.path.join(PACKAGE, 'assets', 'app_settings', 'icon.ico') if sys.platform == 'win32' else None,
)

coll = COLLECT(exe, a.binaries, a.datas, strip=False, upx=False, name="ultrazohm-dataviewer")
