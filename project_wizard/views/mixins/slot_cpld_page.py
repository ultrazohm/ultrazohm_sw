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


class SlotCpldPageMixin:
    def _build_slot_cpld_page(self) -> QWidget:
        page = QWidget()
        page_layout = QVBoxLayout(page)
        splitter = QSplitter(Qt.Orientation.Vertical)
        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        content = QWidget()
        outer = QVBoxLayout(content)

        title = QLabel("Slot CPLDs")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        outer.addWidget(title)

        group = QGroupBox("Digital slot CPLD programs")
        form = QFormLayout(group)
        for slot in DIGITAL_SLOTS:
            combo = QComboBox()
            self.cpld_combos[slot] = combo
            self._fill_cpld_combo(combo)
            combo.currentIndexChanged.connect(self.refresh_tcl_preview)
            combo.currentIndexChanged.connect(self.invalidate_cpld_project_file)
            form.addRow(slot, combo)
        outer.addWidget(group)

        cable_group = QGroupBox("Lattice cable settings")
        cable_form = QFormLayout(cable_group)
        cable_defaults = {
            "cable_name": "USB2",
            "port_address": "FTUSB-1",
            "usb_id": "UltraZohm B Location",
            "tck_delay": "3",
        }
        cable_labels = {
            "cable_name": "Cable name",
            "port_address": "Port address",
            "usb_id": "USB ID",
            "tck_delay": "Clock divider",
        }
        for key, default_value in cable_defaults.items():
            edit = QLineEdit(default_value)
            edit.textChanged.connect(self.invalidate_cpld_project_file)
            self.cpld_programmer_fields[key] = edit
            cable_form.addRow(cable_labels[key], edit)
        recovery_group = QGroupBox("Cable setup recovery")
        recovery_layout = QVBoxLayout(recovery_group)
        recovery_hint = QLabel(
            "This optional path is only needed when the default cable settings do not work. "
            "Open Diamond Programmer once, select UltraZohm B Location, save an XCF, "
            "and copy or import CableName and PortAdd from that file."
        )
        recovery_hint.setWordWrap(True)
        recovery_hint.setMinimumHeight(44)
        recovery_hint.setContentsMargins(0, 4, 0, 4)
        recovery_layout.addWidget(recovery_hint)
        import_enable = QCheckBox("I want to import cable settings from an existing Diamond Programmer XCF")
        import_button = QPushButton("Import cable settings from XCF")
        import_button.setEnabled(False)
        import_enable.toggled.connect(import_button.setEnabled)
        import_button.clicked.connect(self.import_cable_settings_from_xcf)
        self.import_cable_button = import_button
        recovery_layout.addWidget(import_enable)
        recovery_layout.addWidget(import_button, alignment=Qt.AlignmentFlag.AlignRight)
        cable_form.addRow("", recovery_group)
        outer.addWidget(cable_group)

        buttons = QHBoxLayout()
        lattice_button = QPushButton("Write Lattice Diamond Programmer project file")
        lattice_button.clicked.connect(self.write_lattice_diamond_project_file)
        program_button = QPushButton("Programm CPLDs via CLI")
        program_button.clicked.connect(self.program_cplds_via_cli)
        self.write_cpld_button = lattice_button
        self.program_cpld_button = program_button
        program_button.setEnabled(False)
        buttons.addStretch(1)
        buttons.addWidget(lattice_button)
        buttons.addWidget(
            self._help_button(
                "Write Lattice Diamond Programmer project file",
                "Writes a Diamond Programmer XCF file for the currently selected D-slot CPLD programs.\n\n"
                f"Default folder:\n{CPLD_CONFIG_DIR}\n\n"
                "The save dialog is shown before writing the file. Existing files are overwritten only if you confirm "
                "that path in the dialog.",
            )
        )
        buttons.addWidget(program_button)
        buttons.addWidget(
            self._help_button(
                "Programm CPLDs via CLI",
                "Runs the configured Lattice Diamond Programmer command-line executable with the current XCF file.\n\n"
                f"Programmer output log folder:\n{LOG_DIR}\n\n"
                "The XCF must be generated first, and the Toolchain page must contain a valid Programmer executable "
                "path. This workflow is intended for MachXO2 D-slot CPLDs.",
            )
        )
        buttons.addStretch(1)
        outer.addLayout(buttons)
        cpld_cli_hint = QLabel(
            "Attention!: The 'Programm CPLDs via CLI' workflow in the 'Slot CPLDs' page is not supported for LA4128/LC4256 CPLDs"
        )
        cpld_cli_hint.setWordWrap(True)
        cpld_cli_hint.setAlignment(Qt.AlignmentFlag.AlignCenter)
        outer.addWidget(cpld_cli_hint)

        self.cpld_status = QTextEdit()
        self.cpld_status.setReadOnly(True)
        self.cpld_status.setLineWrapMode(QTextEdit.LineWrapMode.NoWrap)
        self.cpld_status.setPlainText("No CPLD programmer output yet.")
        outer.addStretch(1)
        scroll.setWidget(content)
        cpld_status_group = QGroupBox("CPLD programmer output")
        cpld_status_layout = QVBoxLayout(cpld_status_group)
        cpld_status_layout.addWidget(self.cpld_status)
        splitter.addWidget(scroll)
        splitter.addWidget(cpld_status_group)
        splitter.setStretchFactor(0, 1)
        splitter.setStretchFactor(1, 0)
        splitter.setSizes([560, 190])
        page_layout.addWidget(splitter, 1)
        return page
