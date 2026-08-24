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


class CpldWorkflowMixin:
    def import_cable_settings_from_xcf(self) -> None:
        path_text, _ = QFileDialog.getOpenFileName(
            self,
            "Import cable settings from XCF",
            str(APP_DIR),
            "Lattice Diamond Programmer project (*.xcf);;All files (*)",
        )
        if not path_text:
            return
        path = Path(path_text)
        try:
            settings = read_cable_settings_from_xcf(path)
        except (OSError, ValueError) as error:
            QMessageBox.warning(self, "Could not import cable settings", str(error))
            return

        self.load_cpld_programmer_config({key: value for key, value in settings.items() if value or key == "usb_id"})
        self.invalidate_cpld_project_file()
        imported = [
            f"Imported cable settings from {path}",
            f"CableName: {settings.get('cable_name', '')}",
            f"PortAdd: {settings.get('port_address', '')}",
            f"USBID: {settings.get('usb_id', '')}",
            f"TCKDelay: {settings.get('tck_delay', '')}",
        ]
        self.set_cpld_status("\n".join(imported))


    def write_lattice_diamond_project_file(self) -> None:
        if not self.require_toolchain_paths(
            [
                ("cpld_repository", "CPLD repository", "directory"),
                ("lattice_programmer_executable", "Lattice Programmer executable", "file"),
            ],
            "CPLD toolchain paths missing",
        ):
            return
        xcf_path = self.ask_cpld_project_export_path()
        if xcf_path is None:
            return
        self.cpld_xcf_path = xcf_path
        try:
            result = self.generate_lattice_diamond_project_file()
        except (OSError, ValueError) as error:
            self.cpld_xcf_current = False
            self.refresh_cpld_program_button_state()
            self.set_cpld_status(f"Could not write Lattice Diamond Programmer project file:\n{error}")
            QMessageBox.warning(self, "Could not write project file", str(error))
            return
        messages = [
            f"Wrote {result.path}",
            f"Active slots: {', '.join(result.active_slots) if result.active_slots else 'none'}",
            f"Not programmed: {', '.join(result.inactive_slots) if result.inactive_slots else 'none'}",
        ]
        messages.extend(f"WARNING: {warning}" for warning in result.warnings)
        self.cpld_xcf_current = True
        self.refresh_cpld_program_button_state()
        self.set_cpld_status("\n".join(messages))


    def ask_cpld_project_export_path(self) -> Path | None:
        CPLD_CONFIG_DIR.mkdir(parents=True, exist_ok=True)
        default_path = self.cpld_xcf_path if self.cpld_xcf_path else CPLD_CONFIG_DIR / "project_wizard_slot_cplds.xcf"
        if not default_path.is_absolute():
            default_path = CPLD_CONFIG_DIR / default_path.name
        path_text, _ = QFileDialog.getSaveFileName(
            self,
            "Write Lattice Diamond Programmer project file",
            str(default_path),
            "Lattice Diamond Programmer project (*.xcf);;All files (*)",
        )
        return Path(path_text) if path_text else None


    def program_cplds_via_cli(self) -> None:
        if self.cpld_process and self.cpld_process.state() != QProcess.ProcessState.NotRunning:
            return
        if not self.require_toolchain_paths(
            [("lattice_programmer_executable", "Lattice Programmer executable", "file")],
            "CPLD toolchain paths missing",
        ):
            return
        try:
            programmer_path = Path(self.toolchain_config().get("lattice_programmer_executable", ""))
            if not programmer_path.exists():
                raise FileNotFoundError(f"Lattice Programmer executable not found: {programmer_path}")
            if not self.cpld_xcf_current or not self.cpld_xcf_path.exists():
                raise FileNotFoundError("Generate the Lattice Diamond Programmer project file before programming.")
            LOG_DIR.mkdir(parents=True, exist_ok=True)
            log_path = LOG_DIR / "project_wizard_slot_cplds.log"
        except (OSError, ValueError) as error:
            self.set_cpld_status(f"Could not program CPLDs:\n{error}")
            QMessageBox.warning(self, "Could not program CPLDs", str(error))
            return

        try:
            if log_path.exists():
                log_path.unlink()
        except OSError:
            pass

        command = [str(programmer_path), "-infile", str(self.cpld_xcf_path), "-logfile", str(log_path)]
        self.cpld_log_path = log_path
        self.set_cpld_status("")
        self.append_cpld_status("Programming CPLDs via Lattice Programmer...", "#0057b8")
        self.append_cpld_status(f"Command: {' '.join(command)}")
        self.append_cpld_status(f"Project file: {self.cpld_xcf_path}")
        self.append_cpld_status(f"Log file: {log_path}")
        self.set_cpld_programming_busy(True)
        self.statusBar().showMessage("Programming CPLDs...")

        process = QProcess(self)
        self.cpld_process = process
        process.setProgram(str(programmer_path))
        process.setArguments(["-infile", str(self.cpld_xcf_path), "-logfile", str(log_path)])
        process.setWorkingDirectory(str(programmer_path.parent))
        process.readyReadStandardOutput.connect(self.read_cpld_process_stdout)
        process.readyReadStandardError.connect(self.read_cpld_process_stderr)
        process.errorOccurred.connect(self.cpld_process_error)
        process.finished.connect(self.cpld_process_finished)
        process.start()


    def generate_lattice_diamond_project_file(self):
        toolchain = self.toolchain_config()
        repository_path = Path(toolchain.get("cpld_repository", ""))
        programmer_path = Path(toolchain.get("lattice_programmer_executable", ""))
        if not repository_path.exists():
            raise FileNotFoundError(f"CPLD repository not found: {repository_path}")
        if not programmer_path.exists():
            raise FileNotFoundError(f"Lattice Programmer executable not found: {programmer_path}")
        return generate_d_slot_xcf(
            self.cpld_xcf_path,
            repository_path,
            programmer_path,
            self.resolved_system_model(refresh_dependent_views=False).slot_cpld_programs,
            self.cpld_programmer_config(include_variant=True),
        )


    def set_cpld_status(self, text: str) -> None:
        if self.cpld_status:
            self.cpld_status.setPlainText(text)


    def append_cpld_status(self, text: str, color: str | None = None) -> None:
        if not self.cpld_status:
            return
        escaped = html.escape(text)
        if color:
            self.cpld_status.append(f'<span style="color: {color};">{escaped}</span>')
        else:
            self.cpld_status.append(escaped)


    def set_cpld_programming_busy(self, busy: bool) -> None:
        if self.write_cpld_button:
            self.write_cpld_button.setEnabled(not busy)
        if self.program_cpld_button:
            self.program_cpld_button.setEnabled((not busy) and self.cpld_xcf_current and self.cpld_xcf_path.exists())
            self.program_cpld_button.setText("Programming..." if busy else "Programm CPLDs via CLI")


    def invalidate_cpld_project_file(self) -> None:
        self.cpld_xcf_current = False
        self.refresh_cpld_program_button_state()


    def refresh_cpld_program_button_state(self) -> None:
        if not self.program_cpld_button:
            return
        busy = self.cpld_process is not None and self.cpld_process.state() != QProcess.ProcessState.NotRunning
        self.program_cpld_button.setEnabled((not busy) and self.cpld_xcf_current and self.cpld_xcf_path.exists())


    def read_cpld_process_stdout(self) -> None:
        if not self.cpld_process:
            return
        text = bytes(self.cpld_process.readAllStandardOutput()).decode(errors="replace")
        self.append_cpld_process_text(text)


    def read_cpld_process_stderr(self) -> None:
        if not self.cpld_process:
            return
        text = bytes(self.cpld_process.readAllStandardError()).decode(errors="replace")
        self.append_cpld_process_text(text, default_color="#c62828")


    def append_cpld_process_text(self, text: str, default_color: str | None = None) -> None:
        for line in text.splitlines():
            self.append_cpld_status(line, self.cpld_log_line_color(line) or default_color)


    def cpld_process_error(self, error: QProcess.ProcessError) -> None:
        self.append_cpld_status(f"Process error: {error.name}", "#c62828")


    def cpld_process_finished(self, exit_code: int, _exit_status: QProcess.ExitStatus) -> None:
        self.set_cpld_programming_busy(False)
        self.statusBar().clearMessage()
        self.append_cpld_status("")
        self.append_cpld_status(f"Lattice Programmer exited with code {exit_code}", "#2e7d32" if exit_code == 0 else "#c62828")
        self.append_cpld_log_file()
        if exit_code == 0:
            QMessageBox.information(self, "CPLD programming finished", "Lattice Programmer finished successfully.")
        else:
            QMessageBox.warning(self, "CPLD programming failed", f"Lattice Programmer exited with code {exit_code}.")
        self.cpld_process = None


    def append_cpld_log_file(self) -> None:
        if not self.cpld_log_path:
            return
        if not self.cpld_log_path.exists():
            self.append_cpld_status(f"Log file was not written: {self.cpld_log_path}", "#c62828")
            return
        self.append_cpld_status("")
        self.append_cpld_status(f"Log file: {self.cpld_log_path}", "#0057b8")
        log_text = self.cpld_log_path.read_text(encoding="utf-8", errors="replace")
        if not log_text.strip():
            self.append_cpld_status("No log text was written.")
            return
        for line in log_text.splitlines():
            self.append_cpld_status(line, self.cpld_log_line_color(line))

    @staticmethod

    def cpld_log_line_color(line: str) -> str | None:
        upper_line = line.upper()
        if "NO ERROR" in upper_line or "NO ERRORS" in upper_line:
            return None
        if "ERROR" in upper_line or "FAILED" in upper_line or "FAIL" in upper_line:
            return "#c62828"
        if "PASS" in upper_line or "SUCCESS" in upper_line or "SUCCESSFULLY" in upper_line:
            return "#2e7d32"
        return None
