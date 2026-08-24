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


class TclGenerationPageMixin:
    def _build_tcl_generation_page(self) -> QWidget:
        page = QWidget()
        outer = QVBoxLayout(page)

        title = QLabel("TCL generation")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        outer.addWidget(title)

        splitter = QSplitter(Qt.Orientation.Vertical)
        controls = QWidget()
        controls_layout = QHBoxLayout(controls)

        local_group = QGroupBox()
        local_select = QCheckBox("Local Vivado builds")
        local_content = QWidget()
        local_group_layout = QVBoxLayout(local_group)
        local_group_layout.addWidget(local_select)
        local_group_layout.addWidget(local_content)
        local_layout = QVBoxLayout(local_content)

        options_title = QLabel("Vivado execution options")
        options_title_font = QFont(options_title.font())
        options_title_font.setBold(True)
        options_title.setFont(options_title_font)
        local_layout.addWidget(options_title)

        options_widget = QWidget()
        options_form = QFormLayout(options_widget)
        open_gui_checkbox = QCheckBox("Run Vivado in GUI mode")
        disable_checkpoints_checkbox = QCheckBox("Disable BD/IP synthesis checkpoints")
        validate_checkbox = QCheckBox("Validate block design after applying TCL")
        save_checkbox = QCheckBox("Save block design after applying TCL")
        bitstream_checkbox = QCheckBox("Generate bitstream")
        export_xsa_checkbox = QCheckBox("Export .xsa after successful build")
        self.tcl_disable_checkpoints_checkbox = disable_checkpoints_checkbox
        self.hardware_checkboxes["tcl_workflow_local"] = local_select
        self.hardware_checkboxes["open_vivado_gui"] = open_gui_checkbox
        self.hardware_checkboxes["disable_bd_synth_checkpoints"] = disable_checkpoints_checkbox
        self.hardware_checkboxes["validate_block_design"] = validate_checkbox
        self.hardware_checkboxes["save_block_design"] = save_checkbox
        self.hardware_checkboxes["generate_bitstream"] = bitstream_checkbox
        self.hardware_checkboxes["export_xsa_after_build"] = export_xsa_checkbox
        options_form.addRow("", open_gui_checkbox)
        options_form.addRow("", disable_checkpoints_checkbox)
        options_form.addRow("", validate_checkbox)
        options_form.addRow("", save_checkbox)
        options_form.addRow("", bitstream_checkbox)
        options_form.addRow("", export_xsa_checkbox)
        hint = QLabel(
            "These options only affect the TCL execution/export flow. Complete the hardware configuration pages first, "
            "then run the workflow from here."
        )
        hint.setWordWrap(True)
        options_form.addRow("", hint)
        local_layout.addWidget(options_widget)

        workflow_title = QLabel("TCL workflow")
        workflow_title_font = QFont(workflow_title.font())
        workflow_title_font.setBold(True)
        workflow_title.setFont(workflow_title_font)
        local_layout.addWidget(workflow_title)

        workflow_widget = QWidget()
        workflow_layout = QGridLayout(workflow_widget)
        preview_button = QPushButton("Refresh TCL Preview")
        preview_button.clicked.connect(self.refresh_tcl_preview)
        clear_cache_button = QPushButton("Clear local Vivado artifacts")
        clear_cache_button.clicked.connect(self.clear_vivado_cache)
        export_button = QPushButton("Export TCL")
        export_button.clicked.connect(self.export_tcl)
        workflow_button = QPushButton("Execute TCL workflow")
        workflow_button.clicked.connect(self.execute_tcl_workflow)
        self.tcl_workflow_button = workflow_button
        workflow_layout.addWidget(preview_button, 0, 0)
        workflow_layout.addWidget(clear_cache_button, 0, 1)
        workflow_layout.addWidget(
            self._help_button(
                "Clear local Vivado artifacts",
                "Deletes local Vivado cache/build artifacts for the configured Vivado project and block design.\n\n"
                "This is useful after switching branches or changing the block design structure, because stale cached "
                "IP data can cause misleading Vivado errors.\n\n"
                "The action asks for confirmation before deleting anything.",
            ),
            0,
            2,
        )
        workflow_layout.addWidget(workflow_button, 0, 3)
        workflow_layout.addWidget(
            self._help_button(
                "Execute TCL workflow",
                "Exports the generated block-design TCL, writes a Vivado run wrapper, and starts Vivado with the "
                "selected local workflow options.\n\n"
                f"Default TCL export folder:\n{VIVADO_BD_CONFIG_DIR}\n\n"
                f"Vivado run wrapper folder:\n{VIVADO_RUN_SCRIPT_DIR}\n\n"
                "Depending on the selected checkboxes, Vivado can validate/save the block design, run in GUI mode, "
                "generate a bitstream, and export an XSA.",
            ),
            0,
            4,
        )
        workflow_layout.setColumnStretch(5, 1)
        local_layout.addWidget(workflow_widget)
        local_layout.addStretch(1)

        separator = QFrame()
        separator.setFrameShape(QFrame.Shape.VLine)
        separator.setFrameShadow(QFrame.Shadow.Sunken)
        separator.setLineWidth(2)
        separator.setMidLineWidth(1)

        remote_group = QGroupBox()
        remote_select = QCheckBox("Remote workstation builds")
        remote_content = QWidget()
        self.hardware_checkboxes["tcl_workflow_remote"] = remote_select
        self.tcl_local_workflow_checkbox = local_select
        self.tcl_remote_workflow_checkbox = remote_select
        self.tcl_local_workflow_content = local_content
        self.tcl_remote_workflow_content = remote_content
        remote_group_layout = QVBoxLayout(remote_group)
        remote_group_layout.addWidget(remote_select)
        remote_group_layout.addWidget(remote_content)
        remote_layout = QVBoxLayout(remote_content)
        remote_title = QLabel("TCL export")
        remote_title_font = QFont(remote_title.font())
        remote_title_font.setBold(True)
        remote_title.setFont(remote_title_font)
        remote_layout.addWidget(remote_title)
        remote_hint = QLabel("Export the generated TCL for execution on another workstation.")
        remote_hint.setWordWrap(True)
        remote_layout.addWidget(remote_hint)
        remote_disable_checkpoints_checkbox = QCheckBox("Disable BD/IP synthesis checkpoints")
        self.tcl_remote_disable_checkpoints_checkbox = remote_disable_checkpoints_checkbox
        remote_layout.addWidget(remote_disable_checkpoints_checkbox)
        remote_buttons = QHBoxLayout()
        remote_buttons.addStretch(1)
        remote_buttons.addWidget(export_button)
        remote_buttons.addWidget(
            self._help_button(
                "Export TCL",
                "Writes the generated block-design TCL to a user-selected file.\n\n"
                f"Default folder:\n{VIVADO_BD_CONFIG_DIR}\n\n"
                "Use this when the TCL should be copied to or executed on another workstation. The export dialog is "
                "shown before writing the file.",
            )
        )
        remote_buttons.addStretch(1)
        remote_layout.addLayout(remote_buttons)
        remote_layout.addStretch(1)

        def set_remote_disable_checkpoints(state: int) -> None:
            remote_disable_checkpoints_checkbox.blockSignals(True)
            remote_disable_checkpoints_checkbox.setChecked(state == Qt.CheckState.Checked.value)
            remote_disable_checkpoints_checkbox.blockSignals(False)
            self.guarded_refresh_tcl_preview()

        def set_local_disable_checkpoints(state: int) -> None:
            disable_checkpoints_checkbox.blockSignals(True)
            disable_checkpoints_checkbox.setChecked(state == Qt.CheckState.Checked.value)
            disable_checkpoints_checkbox.blockSignals(False)
            self.guarded_refresh_tcl_preview()

        disable_checkpoints_checkbox.stateChanged.connect(set_remote_disable_checkpoints)
        remote_disable_checkpoints_checkbox.stateChanged.connect(set_local_disable_checkpoints)
        self.sync_tcl_disable_checkpoints_checkbox()

        def select_local_workflow(checked: bool) -> None:
            if checked:
                remote_select.blockSignals(True)
                remote_select.setChecked(False)
                remote_select.blockSignals(False)
                self.sync_tcl_workflow_sections()
                return
            if not remote_select.isChecked():
                remote_select.setChecked(True)
            self.sync_tcl_workflow_sections()

        def select_remote_workflow(checked: bool) -> None:
            if checked:
                local_select.blockSignals(True)
                local_select.setChecked(False)
                local_select.blockSignals(False)
                self.sync_tcl_workflow_sections()
                return
            if not local_select.isChecked():
                local_select.setChecked(True)
            self.sync_tcl_workflow_sections()

        local_select.toggled.connect(select_local_workflow)
        remote_select.toggled.connect(select_remote_workflow)
        self.sync_tcl_workflow_sections()

        controls_layout.addWidget(local_group, 1)
        controls_layout.addWidget(separator)
        controls_layout.addWidget(remote_group, 1)
        splitter.addWidget(controls)

        output = QWidget()
        output_layout = QVBoxLayout(output)

        warning_group = QGroupBox("TCL preview warnings and workflow output")
        warning_layout = QVBoxLayout(warning_group)
        self.vivado_status = QPlainTextEdit()
        self.vivado_status.setReadOnly(True)
        self.vivado_status.setPlainText("No TCL preview warnings.")
        self.vivado_status.setMaximumHeight(72)
        warning_layout.addWidget(self.vivado_status)
        output_layout.addWidget(warning_group)

        preview_group = QGroupBox("TCL preview")
        preview_layout = QVBoxLayout(preview_group)
        self.tcl_preview = QPlainTextEdit()
        self.tcl_preview.setReadOnly(True)
        self.tcl_preview.setLineWrapMode(QPlainTextEdit.LineWrapMode.NoWrap)
        self.tcl_preview.setPlainText("Generated TCL preview is shown here.")
        preview_layout.addWidget(self.tcl_preview)
        output_layout.addWidget(preview_group, 2)
        splitter.addWidget(output)
        splitter.setStretchFactor(0, 0)
        splitter.setStretchFactor(1, 1)
        splitter.setSizes([360, 460])
        outer.addWidget(splitter, 1)
        return page
