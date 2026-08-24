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


class TclWorkflowMixin:
    def execute_tcl_workflow(self) -> None:
        if self.vivado_process and self.vivado_process.state() != QProcess.ProcessState.NotRunning:
            QMessageBox.warning(self, "Vivado is running", "A Vivado process started by the wizard is still running.")
            return
        if not self.require_toolchain_paths(
            [("vivado_executable", "Vivado executable", "file")],
            "Vivado toolchain path missing",
        ):
            return

        tcl_path = self.ask_tcl_export_path()
        if tcl_path is None:
            return

        try:
            self.write_generated_tcl(tcl_path)
        except OSError as error:
            QMessageBox.warning(self, "Could not write TCL", str(error))
            return

        self.run_tcl_in_vivado(tcl_path)


    def ask_tcl_export_path(self) -> Path | None:
        VIVADO_BD_CONFIG_DIR.mkdir(parents=True, exist_ok=True)
        default_path = VIVADO_BD_CONFIG_DIR / "project_wizard_config.tcl"
        path_text, _ = QFileDialog.getSaveFileName(self, "Export TCL", str(default_path), "TCL files (*.tcl)")
        return Path(path_text) if path_text else None


    def write_generated_tcl(self, path: Path) -> None:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(self.generator.generate(self.resolved_system_model()), encoding="utf-8")
        if self.vivado_status:
            self.vivado_status.setPlainText(f"Wrote TCL: {path}")


    def show_tcl_export_result(self, path: Path) -> None:
        warnings = self.generator.validation_warnings(self.resolved_system_model())
        if warnings:
            QMessageBox.warning(
                self,
                "TCL exported with warnings",
                f"Wrote {path}\n\n" + "\n".join(f"- {warning}" for warning in warnings),
            )
            return
        QMessageBox.information(self, "TCL exported", f"Wrote {path}")


    def export_tcl(self) -> None:
        tcl_path = self.ask_tcl_export_path()
        if tcl_path is None:
            return
        try:
            self.write_generated_tcl(tcl_path)
        except OSError as error:
            QMessageBox.warning(self, "Could not write TCL", str(error))
            return
        self.show_tcl_export_result(tcl_path)


    def clear_vivado_cache(self) -> None:
        if self.vivado_process and self.vivado_process.state() != QProcess.ProcessState.NotRunning:
            QMessageBox.warning(self, "Vivado is running", "Close or stop the Vivado process before clearing the cache.")
            return
        hardware = self.hardware_config()
        project_text = hardware.get("vivado_project_file", "").strip()
        if not project_text:
            QMessageBox.warning(self, "Vivado project missing", "Select a Vivado project file on the Hardware General page first.")
            self.show_hardware_general()
            return
        project_path = Path(project_text)
        if not project_path.is_file():
            QMessageBox.warning(self, "Vivado project missing", f"Vivado project not found:\n{project_path}")
            self.show_hardware_general()
            return

        targets = [target for target in vivado_cache_targets(project_path, hardware.get("block_design_name", "zusys")) if target.exists()]
        if not targets:
            self.set_vivado_status(f"No Vivado cache artifacts found under:\n{project_path.parent}")
            return
        target_list = "\n".join(f"- {target}" for target in targets)
        question = QMessageBox(self)
        question.setIcon(QMessageBox.Icon.Warning)
        question.setWindowTitle("Clear Vivado cache")
        question.setText("Remove generated Vivado cache/build artifacts?")
        question.setInformativeText(
            "This deletes local generated folders such as .Xil, *.cache, *.runs, *.sim, *.gen, and generated "
            "block-design output below the selected Vivado project directory. The .xpr and source-controlled "
            "block-design files are kept."
        )
        question.setDetailedText(target_list)
        cancel_button = question.addButton("Cancel", QMessageBox.ButtonRole.RejectRole)
        clear_button = question.addButton("Clear cache", QMessageBox.ButtonRole.DestructiveRole)
        question.setDefaultButton(cancel_button)
        question.exec()
        if question.clickedButton() != clear_button:
            return

        result = clear_vivado_cache(project_path, hardware.get("block_design_name", "zusys"))
        status = ["Vivado cache cleanup complete."]
        if result.removed:
            status.append("")
            status.append("Removed:")
            status.extend(f"- {path}" for path in result.removed)
        if result.errors:
            status.append("")
            status.append("Errors:")
            status.extend(f"- {error}" for error in result.errors)
        self.set_vivado_status("\n".join(status))


    def run_tcl_in_vivado(self, tcl_path: Path) -> None:
        if not self.require_toolchain_paths(
            [("vivado_executable", "Vivado executable", "file")],
            "Vivado toolchain path missing",
        ):
            return
        toolchain = self.toolchain_config()
        hardware = self.hardware_config()
        vivado_path = Path(toolchain.get("vivado_executable", ""))
        project_path = Path(hardware.get("vivado_project_file", ""))
        open_gui = hardware.get("open_vivado_gui", "false").lower() in {"1", "true", "yes", "on"}
        if not vivado_path.exists():
            QMessageBox.warning(self, "Vivado executable missing", f"Vivado executable not found:\n{vivado_path}")
            return
        if not project_path.exists():
            QMessageBox.warning(self, "Vivado project missing", f"Vivado project not found:\n{project_path}")
            return

        wrapper_path = VIVADO_RUN_SCRIPT_DIR / "project_wizard_run_vivado.tcl"
        generate_bitstream = hardware.get("generate_bitstream", "false").lower() in {"1", "true", "yes", "on"}
        export_xsa = hardware.get("export_xsa_after_build", "false").lower() in {"1", "true", "yes", "on"}
        if export_xsa and not generate_bitstream:
            QMessageBox.warning(
                self,
                "Build step missing",
                "Select Generate bitstream before exporting an .xsa after the build.",
            )
            return
        try:
            write_vivado_run_wrapper(
                wrapper_path,
                project_path,
                tcl_path,
                hardware.get("block_design_name", "zusys"),
                hardware.get("validate_block_design", "true").lower() in {"1", "true", "yes", "on"},
                hardware.get("save_block_design", "false").lower() in {"1", "true", "yes", "on"},
                hardware.get("open_vivado_gui", "false").lower() in {"1", "true", "yes", "on"},
                generate_bitstream,
                export_xsa,
                APP_DIR.parent / "tcl_scripts" / "vivado_export_xsa.tcl" if export_xsa else None,
            )
        except (OSError, ValueError) as error:
            QMessageBox.warning(self, "Could not write Vivado wrapper", str(error))
            return

        self.set_vivado_status(
            "\n".join(
                [
                    "Starting interactive Vivado run..." if open_gui else "Starting Vivado batch run...",
                    f"Vivado: {vivado_path}",
                    f"Project: {project_path}",
                    f"Generated TCL: {tcl_path}",
                    f"Wrapper TCL: {wrapper_path}",
                    "Close Vivado to finish this workflow." if open_gui else "",
                ]
            )
        )
        self.set_vivado_busy(True)
        self.statusBar().showMessage(
            "Running Vivado TCL workflow. Close Vivado to finish." if open_gui else "Running Vivado TCL workflow..."
        )
        process = QProcess(self)
        self.vivado_process = process
        vivado_args = ["-mode", "gui" if open_gui else "batch", "-source", str(wrapper_path)]
        if vivado_path.suffix.lower() in {".bat", ".cmd"}:
            process.setProgram("cmd.exe")
            process.setArguments(["/c", str(vivado_path), *vivado_args])
        else:
            process.setProgram(str(vivado_path))
            process.setArguments(vivado_args)
        process.setWorkingDirectory(str(project_path.parent))
        process.readyReadStandardOutput.connect(self.read_vivado_process_stdout)
        process.readyReadStandardError.connect(self.read_vivado_process_stderr)
        process.errorOccurred.connect(self.vivado_process_error)
        process.finished.connect(self.vivado_process_finished)
        process.start()


    def set_vivado_status(self, text: str) -> None:
        if self.vivado_status:
            self.vivado_status.setPlainText(text)
            self.vivado_status.moveCursor(QTextCursor.MoveOperation.End)


    def append_vivado_status(self, text: str) -> None:
        if self.vivado_status:
            self.vivado_status.appendPlainText(text)
            self.vivado_status.moveCursor(QTextCursor.MoveOperation.End)


    def read_vivado_process_stdout(self) -> None:
        if not self.vivado_process:
            return
        text = bytes(self.vivado_process.readAllStandardOutput()).decode(errors="replace")
        if text:
            self.append_vivado_status(text.rstrip())


    def read_vivado_process_stderr(self) -> None:
        if not self.vivado_process:
            return
        text = bytes(self.vivado_process.readAllStandardError()).decode(errors="replace")
        if text:
            self.append_vivado_status(text.rstrip())


    def vivado_process_error(self, error: QProcess.ProcessError) -> None:
        self.append_vivado_status(f"Process error: {error.name}")


    def vivado_process_finished(self, exit_code: int, _exit_status: QProcess.ExitStatus) -> None:
        self.set_vivado_busy(False)
        self.statusBar().clearMessage()
        self.append_vivado_status("")
        self.append_vivado_status(f"Vivado exited with code {exit_code}")
        if exit_code == 0:
            QMessageBox.information(self, "Vivado TCL workflow finished", "Vivado finished successfully.")
        else:
            QMessageBox.warning(self, "Vivado TCL workflow failed", f"Vivado exited with code {exit_code}.")
        self.vivado_process = None


    def set_vivado_busy(self, busy: bool) -> None:
        if self.tcl_workflow_button:
            self.tcl_workflow_button.setEnabled(not busy)
            self.tcl_workflow_button.setText("Running Vivado..." if busy else "Execute TCL workflow")
