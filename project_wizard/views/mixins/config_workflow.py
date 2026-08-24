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


class ConfigWorkflowMixin:
    def new_config(self) -> None:
        if not self.confirm_save_config_changes("starting a new config"):
            return
        self.current_config_path = None
        if self.platform_combo.count() > 0:
            self.platform_combo.setCurrentIndex(0)
        self.refresh_platform_revisions()
        if self.platform_cpld_type_combo:
            self.platform_cpld_type_combo.setCurrentIndex(0)
        self.refresh_platform_cpld_visibility()
        self.detail_options = {}
        if self.adapter_details is not None:
            self.adapter_details.detail_options = self.detail_options
        self.reset_hardware_config()
        for slot, combo in self.slot_combos.items():
            default_card_id = "no_adapter_board" if slot.startswith("A") else "empty"
            index = combo.findData(default_card_id)
            combo.setCurrentIndex(index if index >= 0 else 0)
        for slot in DIGITAL_SLOTS:
            self.prefill_cpld_for_slot(slot)
        self.refresh_software_preset_options()
        self.reset_axi_config()
        self.reset_software_config()
        self.rebuild_details()
        self.refresh_tcl_preview()
        self.saved_config_snapshot = self.config_snapshot()


    def open_config(self) -> None:
        if not self.confirm_save_config_changes("opening another config"):
            return
        USER_CONFIG_DIR.mkdir(parents=True, exist_ok=True)
        path_text, _ = QFileDialog.getOpenFileName(
            self,
            "Open config",
            str(USER_CONFIG_DIR),
            "Project Wizard config (*.pw.json);;JSON files (*.json)",
        )
        if not path_text:
            return
        path = Path(path_text)
        progress = QProgressDialog("Reading config file...", "", 0, 7, self)
        progress.setWindowTitle("Loading config")
        progress.setCancelButton(None)
        progress.setWindowModality(Qt.WindowModality.ApplicationModal)
        progress.setMinimumDuration(0)
        progress.setValue(0)
        progress.show()
        QApplication.processEvents()
        self.is_loading_config = True
        self.set_bulk_updates_enabled(False)
        try:
            self.update_config_load_progress(progress, 1, "Parsing config file...")
            document = json.loads(path.read_text(encoding="utf-8"))
            self.load_config_document(document, progress)
        except (OSError, json.JSONDecodeError, ValueError) as error:
            QMessageBox.warning(self, "Could not open config", str(error))
            return
        except Exception as error:  # noqa: BLE001 - keep the GUI recoverable on unexpected load failures.
            details = traceback.format_exc()
            print(details, file=sys.stderr)
            QMessageBox.critical(
                self,
                "Could not open config",
                "An unexpected error occurred while loading the config.\n\n"
                f"{type(error).__name__}: {error}\n\n"
                "Details were also written to the console.",
            )
            return
        finally:
            self.is_loading_config = False
            self.set_bulk_updates_enabled(True)
            progress.close()
        self.current_config_path = path
        QTimer.singleShot(0, lambda document=document: self.finish_config_load_refresh(document))


    def finish_config_load_refresh(self, document: dict[str, Any]) -> None:
        self.set_bulk_updates_enabled(False)
        try:
            self.refresh_software_preset_options(SystemConfig.from_document(document).flat_software_values)
            self.software_dependent_views_dirty = False
            self.refresh_tcl_preview()
        except Exception as error:  # noqa: BLE001 - keep the GUI alive after refresh errors.
            details = traceback.format_exc()
            print(details, file=sys.stderr)
            QMessageBox.critical(
                self,
                "Could not refresh config",
                "The config was loaded, but refreshing generated previews failed.\n\n"
                f"{type(error).__name__}: {error}\n\n"
                "Details were also written to the console.",
            )
        finally:
            self.set_bulk_updates_enabled(True)
        self.saved_config_snapshot = self.config_snapshot()


    def save_config(self) -> bool:
        if self.current_config_path is None:
            return self.save_config_as()
        return self.write_config(self.current_config_path)


    def save_config_as(self) -> bool:
        default_path = self.current_config_path or (USER_CONFIG_DIR / "project_wizard_config.pw.json")
        path_text, _ = QFileDialog.getSaveFileName(
            self,
            "Save config as",
            str(default_path),
            "Project Wizard config (*.pw.json);;JSON files (*.json)",
        )
        if not path_text:
            return False
        path = Path(path_text)
        self.current_config_path = path
        return self.write_config(path)


    def write_config(self, path: Path) -> bool:
        try:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(json.dumps(self.config_document(), indent=2) + "\n", encoding="utf-8")
        except OSError as error:
            QMessageBox.warning(self, "Could not save config", str(error))
            return False
        self.saved_config_snapshot = self.config_snapshot()
        QMessageBox.information(self, "Config saved", f"Wrote {path}")
        return True


    def config_snapshot(self) -> str:
        return json.dumps(self.config_document(), sort_keys=True, separators=(",", ":"), ensure_ascii=True)


    def has_unsaved_config_changes(self) -> bool:
        return self.config_snapshot() != self.saved_config_snapshot


    def confirm_save_config_changes(self, action: str) -> bool:
        if not self.saved_config_snapshot or not self.has_unsaved_config_changes():
            return True
        dialog = QMessageBox(self)
        dialog.setIcon(QMessageBox.Icon.Question)
        dialog.setWindowTitle("Save config changes")
        dialog.setText("The current config has unsaved changes.")
        dialog.setInformativeText(f"Do you want to save the config before {action}?")
        save_button = dialog.addButton("Save", QMessageBox.ButtonRole.AcceptRole)
        discard_button = dialog.addButton("Discard", QMessageBox.ButtonRole.DestructiveRole)
        cancel_button = dialog.addButton(QMessageBox.StandardButton.Cancel)
        dialog.setDefaultButton(save_button)
        dialog.exec()
        clicked_button = dialog.clickedButton()
        if clicked_button == save_button:
            return self.save_config()
        if clicked_button == discard_button:
            return True
        return False


    def config_document(self) -> dict[str, Any]:
        return self.system_config().to_document()


    def system_config(self, refresh_dependent_views: bool = True) -> SystemConfig:
        if refresh_dependent_views:
            self.refresh_dirty_software_dependent_views()
        return SystemConfig.from_document(
            build_config_document(
                self.selected_platform(),
                self.platform_cpld_config(),
                self.toolchain_config(),
                self.hardware_config(),
                self.assignments(),
                self.option_values(),
                self.cpld_assignments(),
                self.cpld_programmer_config(),
                self.axi_config(),
                self.software_config(),
                self.software_modes(),
                self.software_presets(),
                self.selected_visualization_signals(),
                self.driver_config_values(),
            )
        )


    def resolved_system_model(self, refresh_dependent_views: bool = True):
        return self.system_resolver.resolve(self.system_config(refresh_dependent_views))


    def update_config_load_progress(self, progress: QProgressDialog | None, value: int, message: str) -> None:
        if progress is None:
            return
        progress.setLabelText(message)
        progress.setValue(value)
        QApplication.processEvents()


    def load_config_document(self, document: dict[str, Any], progress: QProgressDialog | None = None) -> None:
        config = SystemConfig.from_document(document)
        self.update_config_load_progress(progress, 2, "Loading platform and toolchain...")
        platform_id = config.platform_id
        platform_index = self.platform_combo.findData(platform_id)
        if platform_index >= 0:
            self.platform_combo.setCurrentIndex(platform_index)
        self.refresh_platform_revisions(config.platform_revision)

        self.load_platform_cpld_config(config.platform_cpld)
        self.refresh_platform_cpld_visibility()

        self.load_toolchain_config(config.toolchain)

        self.load_hardware_config(config.hardware)

        self.update_config_load_progress(progress, 3, "Loading adapter cards...")
        slots = config.slot_card_assignments
        for slot, combo in self.slot_combos.items():
            card_id = slots.get(slot, "empty")
            index = combo.findData(card_id)
            if index < 0:
                fallback_card_id = "no_adapter_board" if slot.startswith("A") else "empty"
                index = combo.findData(fallback_card_id)
            combo.setCurrentIndex(index if index >= 0 else 0)

        self.update_config_load_progress(progress, 4, "Loading adapter card details...")
        self.detail_options = {slot: dict(options) for slot, options in config.slot_option_values.items()}
        if self.adapter_details is not None:
            self.adapter_details.detail_options = self.detail_options
        self.rebuild_details()

        self.update_config_load_progress(progress, 5, "Loading software configuration...")
        self.load_software_config(config.flat_software_values)

        self.update_config_load_progress(progress, 6, "Loading CPLD and AXI settings...")
        slot_cplds = config.slot_cplds
        for slot, combo in self.cpld_combos.items():
            program_id = slot_cplds.get(slot)
            if program_id is None:
                self.prefill_cpld_for_slot(slot)
                continue
            index = combo.findData(program_id)
            combo.blockSignals(True)
            combo.setCurrentIndex(index if index >= 0 else max(combo.findData("none"), 0))
            combo.blockSignals(False)

        self.load_cpld_programmer_config(config.cpld_programmer)

        self.load_axi_config(config.axi)


    def show_docs(self) -> None:
        QMessageBox.information(
            self,
            "Docs",
            f"Project notes are currently in:\n{APP_DIR / 'README.md'}",
        )


    def show_info(self) -> None:
        git_revision = self.git_metadata(["describe", "--tags", "--always", "--dirty"])
        branch = self.git_metadata(["rev-parse", "--abbrev-ref", "HEAD"])
        dialog = QMessageBox(self)
        dialog.setIcon(QMessageBox.Icon.Information)
        dialog.setWindowTitle("Info")
        dialog.setText("Project Wizard")
        dialog.setInformativeText(
            "\n".join(
                [
                    "Configuration helper for UltraZohm Vivado, CPLD, and software integration workflows.",
                    "",
                    f"Version: {__version__}",
                    "License: Apache License 2.0",
                ]
            )
        )
        dialog.setDetailedText(
            "\n".join(
                [
                    "Project Wizard",
                    "",
                    "Purpose:",
                    "  Configure UltraZohm hardware slots, generate Vivado TCL, generate CPLD programmer files,",
                    "  and generate or patch Vitis software integration files.",
                    "",
                    "Version control:",
                    f"  Application version: {__version__}",
                    f"  Git revision: {git_revision}",
                    f"  Branch: {branch}",
                    "",
                    "Runtime:",
                    f"  Python: {platform.python_version()}",
                    f"  PyQt: {PYQT_VERSION_STR}",
                    f"  Qt: {QT_VERSION_STR}",
                    f"  Operating system: {platform.platform()}",
                    "",
                    "Paths:",
                    f"  Wizard folder: {APP_DIR}",
                    f"  Data folder: {DATA_FILE.parent}",
                    f"  User configurations folder: {USER_CONFIG_DIR}",
                    f"  Generated folder: {OUTPUT_DIR}",
                    f"  Vivado BD TCL folder: {VIVADO_BD_CONFIG_DIR}",
                    f"  Vivado run scripts folder: {VIVADO_RUN_SCRIPT_DIR}",
                    f"  CPLD config folder: {CPLD_CONFIG_DIR}",
                    f"  Logs folder: {LOG_DIR}",
                    "",
                    "License:",
                    "  Apache License 2.0",
                    f"  Full license text: {APP_DIR.parent / 'LICENSE'}",
                ]
            )
        )
        dialog.exec()

    @staticmethod

    def git_metadata(args: list[str]) -> str:
        try:
            result = subprocess.run(
                ["git", *args],
                cwd=APP_DIR.parent,
                check=True,
                capture_output=True,
                text=True,
                timeout=2,
            )
        except (OSError, subprocess.SubprocessError):
            return "unknown"
        return result.stdout.strip() or "unknown"
