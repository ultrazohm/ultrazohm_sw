# PyInstaller spec for the UltraZohm Scope.
#
# Produces a single self-contained native executable (Windows .exe / Linux ELF /
# macOS binary). Build with:
#
#     pyinstaller uz_scope2/build/uz_scope2.spec
#
# imgui_bundle ships compiled extensions plus fonts/assets that must be bundled,
# so we collect the whole package. pyarrow carries native libraries which
# PyInstaller's hooks pick up automatically. uz_dataviewer is bundled too — the
# scope imports it as a library (downsampling, console, loader).

import os
import sys

from PyInstaller.utils.hooks import collect_all, collect_submodules

# Resolve paths relative to this spec file (PyInstaller sets SPECPATH).
SRC = os.path.abspath(os.path.join(SPECPATH, "..", "src"))
DATAVIEWER_SRC = os.path.abspath(
    os.path.join(SPECPATH, "..", "..", "uz_dataviewer", "src")
)
for path in (SRC, DATAVIEWER_SRC):
    if path not in sys.path:
        sys.path.insert(0, path)

datas, binaries, hiddenimports = [], [], []
for pkg in ("imgui_bundle", "pyarrow"):
    d, b, h = collect_all(pkg)
    datas += d
    binaries += b
    hiddenimports += h

hiddenimports += collect_submodules("uz_scope2")
hiddenimports += collect_submodules("uz_dataviewer")

block_cipher = None

a = Analysis(
    [os.path.join(SPECPATH, "entrypoint.py")],
    pathex=[SRC, DATAVIEWER_SRC],
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
    name="uz_scope2",
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    console=False,  # GUI app: no console window on Windows
)
