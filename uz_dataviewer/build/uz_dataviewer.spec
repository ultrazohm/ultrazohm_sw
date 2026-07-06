# PyInstaller spec for the UltraZohm Data Viewer.
#
# Produces a single self-contained native executable (Windows .exe / Linux ELF /
# macOS binary). Build with:
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

datas, binaries, hiddenimports = [], [], []
for pkg in ("imgui_bundle", "pyarrow"):
    d, b, h = collect_all(pkg)
    datas += d
    binaries += b
    hiddenimports += h

# Bundle our own package (entry point imports it absolutely).
hiddenimports += collect_submodules("uz_dataviewer")

block_cipher = None

a = Analysis(
    [os.path.join(SPECPATH, "entrypoint.py")],
    pathex=[SRC],
    binaries=binaries,
    datas=datas,
    hiddenimports=hiddenimports,
    hookspath=[],
    runtime_hooks=[],
    excludes=[],
    cipher=block_cipher,
)

pyz = PYZ(a.pure, a.zipped_data, cipher=block_cipher)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.zipfiles,
    a.datas,
    [],
    name="uz_dataviewer",
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    console=False,  # GUI app: no console window on Windows
)
