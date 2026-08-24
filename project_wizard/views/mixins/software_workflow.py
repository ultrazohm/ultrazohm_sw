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
    QTabWidget,
    QTableWidgetItem,
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


class SoftwareWorkflowMixin:
    def refresh_dirty_software_dependent_views(self) -> None:
        if self.is_loading_config or not self.software_dependent_views_dirty:
            return
        values = self.software_config()
        self.refresh_advanced_driver_config_options()
        self.refresh_data_visualization_options(values, refresh_preview=False)
        self.software_dependent_views_dirty = False


    def rebuild_details(self) -> None:
        if self.adapter_details is None:
            return
        self.adapter_details.rebuild_all()
        if self.is_loading_config:
            self.software_dependent_views_dirty = True
            return
        self.refresh_software_preset_options()
        self.guarded_refresh_data_visualization_options()
        self.refresh_advanced_driver_config_options()
        self.guarded_refresh_tcl_preview()


    def refresh_tcl_preview(self) -> None:
        model = self.resolved_system_model()
        self.tcl_preview.setPlainText(self.generator.generate(model))
        warnings = self.generator.validation_warnings(model)
        if warnings and self.vivado_status:
            self.vivado_status.setPlainText("\n".join(f"- {warning}" for warning in warnings))
        elif self.vivado_status:
            self.vivado_status.setPlainText("No TCL preview warnings.")
        if not self.is_loading_config:
            self.refresh_software_preview()


    def refresh_software_preview(self) -> None:
        if self.software_preview is None:
            return
        self.software_preview.setPlainText(self.software_generator.preview(self.resolved_system_model()))


    def generate_software_files(self) -> None:
        self.refresh_dirty_software_dependent_views()
        source_field = self.software_fields.get("source_dir")
        source_text = source_field.text().strip() if source_field else ""
        if not source_text:
            QMessageBox.warning(self, "Software source folder missing", "Please select the folder that contains globalData.h.")
            return
        model = self.resolved_system_model()
        try:
            plan = self.software_generator.build_plan(model)
        except (OSError, ValueError) as error:
            QMessageBox.warning(self, "Could not prepare software generation", str(error))
            return
        if plan.warnings:
            warning_box = QMessageBox(self)
            warning_box.setIcon(QMessageBox.Icon.Warning)
            warning_box.setWindowTitle("Software generation warnings")
            warning_box.setText("The software generator found warnings.")
            warning_box.setInformativeText("Continue writing files anyway?")
            warning_box.setDetailedText("\n".join(f"- {warning}" for warning in plan.warnings))
            cancel_button = warning_box.addButton("Cancel", QMessageBox.ButtonRole.RejectRole)
            continue_button = warning_box.addButton("Continue", QMessageBox.ButtonRole.AcceptRole)
            warning_box.setDefaultButton(cancel_button)
            warning_box.exec()
            if warning_box.clickedButton() != continue_button:
                if self.software_status:
                    self.software_status.setPlainText("Software generation canceled because warnings were not accepted.")
                return
        confirm_box = QMessageBox(self)
        confirm_box.setIcon(QMessageBox.Icon.Question)
        confirm_box.setWindowTitle("Generate software files")
        confirm_box.setText("Generate software files now?")
        confirm_box.setInformativeText(
            "The wizard will write generated slot files and patch Project Wizard marker blocks in the selected software source folder."
        )
        cancel_button = confirm_box.addButton(QMessageBox.StandardButton.Cancel)
        generate_button = confirm_box.addButton("Generate software files", QMessageBox.ButtonRole.AcceptRole)
        confirm_box.setDefaultButton(cancel_button)
        confirm_box.exec()
        if confirm_box.clickedButton() != generate_button:
            if self.software_status:
                self.software_status.setPlainText("Software generation canceled.")
            return
        try:
            result = self.software_generator.generate(model)
        except (OSError, ValueError) as error:
            QMessageBox.warning(self, "Could not generate software files", str(error))
            return

        status = ["Software generation finished."]
        if result.written_files:
            status.append("Written files:")
            status.extend(f"- {path}" for path in result.written_files)
        else:
            status.append("Written files: none")
        if result.patched_files:
            status.append("Patched files:")
            status.extend(f"- {path}" for path in result.patched_files)
        else:
            status.append("Patched files: none")
        if result.warnings:
            status.append("Warnings:")
            status.extend(f"- {warning}" for warning in result.warnings)
        if self.software_status:
            self.software_status.setPlainText("\n".join(status))
        self.refresh_software_preview()


    def refresh_card_table(self) -> None:
        self.card_table.setRowCount(len(self.database.cards))
        for row, card in enumerate(self.database.cards):
            values = [
                card.get("id", ""),
                card.get("name", ""),
                card.get("family", ""),
                ", ".join(card.get("compatible_slots", [])),
                card.get("vitis", {}).get("driver", ""),
            ]
            for column, value in enumerate(values):
                self.card_table.setItem(row, column, QTableWidgetItem(value))
        self.card_table.resizeColumnsToContents()
