from __future__ import annotations

import html
import json
import platform
import subprocess
import sys
import traceback
from pathlib import Path
from typing import Any

from PyQt6.QtCore import PYQT_VERSION_STR, QT_VERSION_STR, QProcess, Qt, QTimer
from PyQt6.QtGui import QColor, QFont, QPixmap, QTextCursor
from PyQt6.QtWidgets import (
    QApplication,
    QComboBox,
    QCheckBox,
    QFileDialog,
    QFormLayout,
    QFrame,
    QGridLayout,
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMessageBox,
    QPlainTextEdit,
    QProgressDialog,
    QPushButton,
    QScrollArea,
    QSizePolicy,
    QSplitter,
    QTabWidget,
    QTextEdit,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

from ...models import SystemConfig
from ...paths import (
    APP_DIR,
    CPLD_CONFIG_DIR,
    DIGITAL_SLOTS,
    LOG_DIR,
    OUTPUT_DIR,
    SLOTS,
    USER_CONFIG_DIR,
    VIVADO_BD_CONFIG_DIR,
    VIVADO_RUN_SCRIPT_DIR,
)
from ...services.config_service import build_config_document
from ...services.cpld_programmer_service import generate_d_slot_xcf, read_cable_settings_from_xcf
from ...services.toolchain_service import TOOL_DEFINITIONS, detect_toolchain_executables
from ...services.vivado_service import clear_vivado_cache, vivado_cache_targets, write_vivado_run_wrapper
from ...theme import set_dark_mode
from ...version import __version__
from ..adapter_card_details import AdapterCardDetailsWidget


TIMING_CONTROL_WIDTH = 260


class ToolchainPageMixin:
    def _build_toolchain_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("Toolchain")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        splitter = QSplitter(Qt.Orientation.Vertical)
        controls = QWidget()
        controls_layout = QVBoxLayout(controls)

        vivado_group = QGroupBox("Vivado")
        vivado_form = QFormLayout(vivado_group)
        vivado_form.addRow("Executable", self._path_picker("vivado_executable", file_mode=True))
        controls_layout.addWidget(vivado_group)

        lattice_group = QGroupBox("Lattice CPLD")
        lattice_form = QFormLayout(lattice_group)
        lattice_form.addRow("Programmer executable", self._path_picker("lattice_programmer_executable", file_mode=True))
        lattice_hint = QLabel("Use pgrcmd.exe for command-line programming, not programmer.exe, which opens the GUI.")
        lattice_hint.setWordWrap(True)
        lattice_form.addRow("", lattice_hint)
        lattice_form.addRow("CPLD repository", self._path_picker("cpld_repository", file_mode=False))
        controls_layout.addWidget(lattice_group)

        vitis_group = QGroupBox("Vitis")
        vitis_form = QFormLayout(vitis_group)
        vitis_form.addRow("Executable", self._path_picker("vitis_executable", file_mode=True))
        controls_layout.addWidget(vitis_group)

        buttons = QHBoxLayout()
        detect_button = QPushButton("Detect tools")
        detect_button.setMinimumSize(180, 36)
        detect_button.clicked.connect(self.detect_toolchain_paths)
        buttons.addStretch(1)
        buttons.addWidget(detect_button)
        buttons.addStretch(1)
        controls_layout.addLayout(buttons)
        controls_layout.addStretch(1)
        splitter.addWidget(controls)

        self.toolchain_status = QPlainTextEdit()
        self.toolchain_status.setReadOnly(True)
        splitter.addWidget(self.toolchain_status)
        splitter.setStretchFactor(0, 1)
        splitter.setStretchFactor(1, 0)
        splitter.setSizes([520, 150])
        layout.addWidget(splitter, 1)

        return page



    def _path_picker(self, key: str, file_mode: bool) -> QWidget:
        container = QWidget()
        layout = QHBoxLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        field = QLineEdit()
        field.textChanged.connect(self.refresh_tcl_preview)
        if key in {"lattice_programmer_executable", "cpld_repository"}:
            field.textChanged.connect(self.invalidate_cpld_project_file)
        button = QPushButton("Browse...")
        button.clicked.connect(lambda: self.browse_toolchain_path(key, file_mode))
        self.toolchain_fields[key] = field
        layout.addWidget(field, 1)
        layout.addWidget(button)
        return container



    def browse_toolchain_path(self, key: str, file_mode: bool) -> None:
        field = self.toolchain_fields[key]
        start_path = field.text().strip() or str(APP_DIR)
        if file_mode:
            path_text, _ = QFileDialog.getOpenFileName(self, "Select executable", start_path, "Executables (*.exe);;All files (*)")
        else:
            path_text = QFileDialog.getExistingDirectory(self, "Select folder", start_path)
        if path_text:
            field.setText(path_text)



    def detect_toolchain_paths(self) -> None:
        results = {result.key: result for result in detect_toolchain_executables()}
        messages = []
        for key, definition in TOOL_DEFINITIONS.items():
            label = str(definition["label"])
            result = results.get(key)
            if result:
                field = self.toolchain_fields.get(key)
                if field and not field.text().strip():
                    field.setText(result.path)
                    messages.append(f"{label}: found via {result.source}: {result.path}")
                elif field:
                    messages.append(f"{label}: found via {result.source}, keeping existing value: {field.text().strip()}")
                else:
                    messages.append(f"{label}: found via {result.source}: {result.path}")
            else:
                messages.append(f"{label}: not found")
        messages.append("CPLD repository: not auto-detected")
        if self.toolchain_status:
            self.toolchain_status.setPlainText("\n".join(messages))
