# PyInstaller spec for the UltraZohm data viewer.
# Build from the uz_dataviewer project root:
#   pyinstaller packaging/desktop/uz_dataviewer.spec --noconfirm
# imgui_bundle ships assets (fonts, etc.) and native libraries that must be
# collected explicitly.

import os

from PyInstaller.utils.hooks import collect_data_files, collect_dynamic_libs

project_root = os.path.abspath(os.path.join(SPECPATH, "..", ".."))

datas = collect_data_files("imgui_bundle")
binaries = collect_dynamic_libs("imgui_bundle")

a = Analysis(
    [os.path.join(project_root, "src", "uz_dataviewer", "__main__.py")],
    pathex=[os.path.join(project_root, "src")],
    binaries=binaries,
    datas=datas,
    hiddenimports=[
        "uz_dataviewer",
        "tsdownsample",
        "pyarrow.csv",
        "pyarrow.parquet",
        "pyarrow.compute",
    ],
    excludes=["matplotlib", "PyQt5", "PyQt6", "PySide2", "PySide6", "tkinter"],
    noarchive=False,
)

pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    exclude_binaries=True,
    name="uz-dataviewer",
    console=False,
    upx=False,
)

coll = COLLECT(
    exe,
    a.binaries,
    a.datas,
    name="uz-dataviewer",
    upx=False,
)
