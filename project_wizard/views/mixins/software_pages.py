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


class SoftwarePageMixin:
    def _build_software_general_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("General")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        source_group = QGroupBox("Software project")
        source_form = QFormLayout(source_group)
        source_form.addRow("Source folder", self._software_path_picker("source_dir", file_mode=False))
        source_hint = QLabel(
            "Select the folder that contains the R5 baremetal software sources. "
            "This is usually vitis/software/Baremetal/src"
        )
        source_hint.setWordWrap(True)
        source_form.addRow("", source_hint)
        layout.addWidget(source_group)

        marker_group = QGroupBox("Marker-based edits")
        marker_layout = QVBoxLayout(marker_group)
        marker_hint = QLabel(
            "The wizard keeps one permanent init header/source pair per adapter slot and rewrites only "
            "Project Wizard marker blocks. Setting a slot to No software driver clears the slot-owned "
            "markers and removes its generated integration from shared marker blocks."
        )
        marker_hint.setWordWrap(True)
        marker_layout.addWidget(marker_hint)
        layout.addWidget(marker_group)

        layout.addStretch(1)
        return page



    def _build_software_driver_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("IP Core Driver Setup")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        splitter = QSplitter(Qt.Orientation.Vertical)
        controls = QWidget()
        controls_layout = QVBoxLayout(controls)

        slot_group = QGroupBox("Slot software integration")
        slot_grid = QGridLayout(slot_group)
        header_font = QFont()
        header_font.setBold(True)
        for column, header in enumerate(["Slot", "Mode", "Preset"]):
            label = QLabel(header)
            label.setFont(header_font)
            slot_grid.addWidget(label, 0, column)
        for row, slot in enumerate(SLOTS, start=1):
            slot_grid.addWidget(QLabel(slot), row, 0)
            combo = QComboBox()
            combo.addItem("Follow hardware selection", "follow_hardware")
            combo.addItem("No software driver", "no_driver")
            combo.currentIndexChanged.connect(self.software_driver_selection_changed)
            self.software_mode_combos[slot] = combo
            slot_grid.addWidget(combo, row, 1)
            preset_combo = QComboBox()
            preset_combo.currentIndexChanged.connect(self.software_driver_selection_changed)
            self.software_preset_combos[slot] = preset_combo
            slot_grid.addWidget(preset_combo, row, 2)
        slot_grid.setColumnStretch(1, 1)
        slot_grid.setColumnStretch(2, 1)
        controls_layout.addWidget(slot_group)

        buttons = QHBoxLayout()
        generate_button = QPushButton("Generate software files")
        generate_button.clicked.connect(self.generate_software_files)
        buttons.addStretch(1)
        buttons.addWidget(generate_button)
        buttons.addWidget(
            self._help_button(
                "Generate software files",
                "Writes generated adapter-slot init files to the selected software source folder.\n\n"
                "Also patches shared Vitis source files only inside Project Wizard marker blocks, for example "
                "globalData.h, main.c, isr.c, javascope files, and uz_global_configuration.h.\n\n"
                "The action asks for confirmation before writing files.",
            )
        )
        controls_layout.addLayout(buttons)
        controls_layout.addStretch(1)
        splitter.addWidget(controls)

        output = QWidget()
        output_layout = QVBoxLayout(output)

        preview_group = QGroupBox("Software generation preview")
        preview_layout = QVBoxLayout(preview_group)
        self.software_preview = QPlainTextEdit()
        self.software_preview.setReadOnly(True)
        self.software_preview.setLineWrapMode(QPlainTextEdit.LineWrapMode.NoWrap)
        self.software_preview.setPlainText("Software generation preview is shown here after the wizard refreshes the driver setup.")
        preview_layout.addWidget(self.software_preview)
        output_layout.addWidget(preview_group, 2)

        status_group = QGroupBox("Software generation output")
        status_layout = QVBoxLayout(status_group)
        self.software_status = QPlainTextEdit()
        self.software_status.setReadOnly(True)
        self.software_status.setPlainText("No software generation output yet.")
        status_layout.addWidget(self.software_status)
        output_layout.addWidget(status_group)
        splitter.addWidget(output)
        splitter.setStretchFactor(0, 0)
        splitter.setStretchFactor(1, 1)
        splitter.setSizes([310, 430])
        layout.addWidget(splitter, 1)
        return page



    def _build_advanced_driver_config_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("Advanced Driver Configuration")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        advanced_hint = QLabel("Use Default for preset-generated config structs, or Custom to edit instance-specific config fields.")
        advanced_hint.setWordWrap(True)
        layout.addWidget(advanced_hint)
        self.driver_config_tabs = QTabWidget()
        self.driver_config_tab_layouts = {}
        for slot in ["PWM", *SLOTS]:
            scroll = QScrollArea()
            scroll.setWidgetResizable(True)
            content = QWidget()
            slot_layout = QVBoxLayout(content)
            slot_layout.addStretch(1)
            self.driver_config_tab_layouts[slot] = slot_layout
            scroll.setWidget(content)
            self.driver_config_tabs.addTab(scroll, slot)
        layout.addWidget(self.driver_config_tabs, 1)

        buttons = QHBoxLayout()
        generate_button = QPushButton("Generate software files")
        generate_button.clicked.connect(self.generate_software_files)
        buttons.addStretch(1)
        buttons.addWidget(generate_button)
        buttons.addWidget(
            self._help_button(
                "Generate software files",
                "Writes generated adapter-slot init files to the selected software source folder.\n\n"
                "Also patches shared Vitis source files only inside Project Wizard marker blocks, for example "
                "globalData.h, main.c, isr.c, javascope files, and uz_global_configuration.h.\n\n"
                "The action asks for confirmation before writing files.",
            )
        )
        layout.addLayout(buttons)
        return page



    def _build_data_visualization_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("Data Visualization")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        hint = QLabel(
            "Select generated float signals that should be registered as Javascope observable signals. "
            "The wizard writes the enum entries in javascope.h and the pointer assignments in javascope.c. "
            "IO-card pin entries are generated from the AXI GPIO-backed pins of the selected card variant "
            "and represent the software-visible GPIO bit value."
        )
        hint.setWordWrap(True)
        layout.addWidget(hint)

        self.visualization_tabs = QTabWidget()
        self.visualization_tab_layouts = {}
        for slot in SLOTS:
            scroll = QScrollArea()
            scroll.setWidgetResizable(True)
            content = QWidget()
            slot_layout = QVBoxLayout(content)
            slot_layout.addStretch(1)
            self.visualization_tab_layouts[slot] = slot_layout
            scroll.setWidget(content)
            self.visualization_tabs.addTab(scroll, slot)
        layout.addWidget(self.visualization_tabs, 1)

        action_group = QGroupBox("Software generation")
        action_layout = QVBoxLayout(action_group)
        action_hint = QLabel("The selected visualization signals are written together with the software driver integration.")
        action_hint.setWordWrap(True)
        action_layout.addWidget(action_hint)
        buttons = QHBoxLayout()
        generate_button = QPushButton("Generate software files")
        generate_button.clicked.connect(self.generate_software_files)
        buttons.addStretch(1)
        buttons.addWidget(generate_button)
        buttons.addWidget(
            self._help_button(
                "Generate software files",
                "Writes generated adapter-slot init files to the selected software source folder.\n\n"
                "Also patches shared Vitis source files only inside Project Wizard marker blocks, for example "
                "globalData.h, main.c, isr.c, javascope files, and uz_global_configuration.h.\n\n"
                "The action asks for confirmation before writing files.",
            )
        )
        action_layout.addLayout(buttons)
        layout.addWidget(action_group)

        return page



    def _software_path_picker(self, key: str, file_mode: bool) -> QWidget:
        container = QWidget()
        layout = QHBoxLayout(container)
        layout.setContentsMargins(0, 0, 0, 0)
        field = QLineEdit()
        field.textChanged.connect(self.refresh_software_preview)
        button = QPushButton("Browse...")
        button.clicked.connect(lambda: self.browse_software_path(key, file_mode))
        self.software_fields[key] = field
        layout.addWidget(field, 1)
        layout.addWidget(button)
        return container



    def browse_software_path(self, key: str, file_mode: bool) -> None:
        field = self.software_fields[key]
        start_path = field.text().strip() or str(APP_DIR.parent)
        if file_mode:
            path_text, _ = QFileDialog.getOpenFileName(self, "Select file", start_path, "All files (*)")
        else:
            path_text = QFileDialog.getExistingDirectory(self, "Select folder", start_path)
        if path_text:
            field.setText(path_text)
