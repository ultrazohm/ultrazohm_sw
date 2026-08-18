from __future__ import annotations

import glob
import shutil
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class ToolDetectionResult:
    key: str
    label: str
    path: str
    source: str


TOOL_DEFINITIONS = {
    "vivado_executable": {
        "label": "Vivado",
        "path_names": ["vivado", "vivado.bat", "vivado.exe"],
        "patterns": [
            r"C:\Xilinx\Vivado\*\bin\vivado.bat",
            r"C:\Xilinx\Vivado\*\bin\vivado.exe",
            "/tools/Xilinx/Vivado/*/bin/vivado",
            "/opt/Xilinx/Vivado/*/bin/vivado",
        ],
    },
    "vitis_executable": {
        "label": "Vitis",
        "path_names": ["vitis", "vitis.bat", "vitis.exe"],
        "patterns": [
            r"C:\Xilinx\Vitis\*\bin\vitis.bat",
            r"C:\Xilinx\Vitis\*\bin\vitis.exe",
            "/tools/Xilinx/Vitis/*/bin/vitis",
            "/opt/Xilinx/Vitis/*/bin/vitis",
        ],
    },
    "lattice_programmer_executable": {
        "label": "Lattice Programmer",
        "path_names": ["pgrcmd", "pgrcmd.exe"],
        "patterns": [
            r"C:\lscc\diamond\*\bin\nt64\pgrcmd.exe",
            r"C:\lscc\diamond\*\bin\nt\pgrcmd.exe",
            r"C:\lscc\programmer\diamond\*\bin\nt64\pgrcmd.exe",
            r"C:\lscc\programmer\diamond\*\bin\nt\pgrcmd.exe",
            r"C:\lscc\programmer\*\bin\nt64\pgrcmd.exe",
            r"C:\lscc\programmer\*\bin\nt\pgrcmd.exe",
            "/usr/local/diamond/*/bin/lin64/pgrcmd",
            "/opt/diamond/*/bin/lin64/pgrcmd",
            "/usr/local/programmer/diamond/*/bin/lin64/pgrcmd",
            "/opt/programmer/diamond/*/bin/lin64/pgrcmd",
        ],
    },
}


def detect_toolchain_executables() -> list[ToolDetectionResult]:
    results = []
    for key, definition in TOOL_DEFINITIONS.items():
        result = _detect_tool(key, definition)
        if result:
            results.append(result)
    return results


def _detect_tool(key: str, definition: dict[str, object]) -> ToolDetectionResult | None:
    label = str(definition["label"])
    for path_name in definition.get("path_names", []):
        path = shutil.which(str(path_name))
        if path:
            return ToolDetectionResult(key=key, label=label, path=str(Path(path)), source=f"PATH ({path_name})")

    candidates = []
    for pattern in definition.get("patterns", []):
        candidates.extend(glob.glob(str(pattern)))
    existing = sorted((Path(path) for path in candidates if Path(path).is_file()), reverse=True)
    if existing:
        return ToolDetectionResult(key=key, label=label, path=str(existing[0]), source="known install location")
    return None
