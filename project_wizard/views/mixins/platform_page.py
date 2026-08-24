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


class PlatformPageMixin:
    def _build_platform_page(self) -> QWidget:
        page = QWidget()
        layout = QVBoxLayout(page)

        title = QLabel("Platform")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title.setFont(title_font)
        layout.addWidget(title)

        group = QGroupBox("Target hardware")
        form = QFormLayout(group)
        self.platform_combo = QComboBox()
        for platform in self.database.platforms:
            platform_name = platform.get("name", platform.get("id", "Unnamed platform"))
            supported = bool(platform.get("supported", True))
            display_name = platform_name if supported else f"{platform_name} - comming soon"
            self.platform_combo.addItem(display_name, platform.get("id"))
            if not supported:
                item = self.platform_combo.model().item(self.platform_combo.count() - 1)
                if item is not None:
                    item.setForeground(QColor("#777"))
                    item.setEnabled(False)
                    item.setSelectable(False)
        self.platform_combo.currentIndexChanged.connect(self.platform_changed)
        form.addRow("Platform", self.platform_combo)
        self.platform_revision_combo = QComboBox()
        self.platform_revision_combo.currentIndexChanged.connect(self.platform_revision_changed)
        form.addRow("Revision", self.platform_revision_combo)
        layout.addWidget(group)

        self.platform_nameplate_group = QGroupBox("Revision on system nameplate")
        nameplate_layout = QVBoxLayout(self.platform_nameplate_group)
        nameplate_hint = QLabel(
            "Use the first two digits of the four-digit group after the third hyphen in the serial number. "
            "In this example, 06 means Rev06."
        )
        nameplate_hint.setWordWrap(True)
        nameplate_layout.addWidget(nameplate_hint)
        nameplate_image = QLabel()
        nameplate_image.setFixedSize(390, 204)
        nameplate_image.setSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        nameplate_image.setStyleSheet("background-color: #ffffff;")
        nameplate_pixmap = QPixmap(str(APP_DIR / "assets" / "nameplate_revision.png"))
        nameplate_image.setPixmap(
            nameplate_pixmap.scaled(
                nameplate_image.size(),
                Qt.AspectRatioMode.KeepAspectRatio,
                Qt.TransformationMode.SmoothTransformation,
            )
        )
        nameplate_image.setAlignment(Qt.AlignmentFlag.AlignLeft | Qt.AlignmentFlag.AlignTop)
        nameplate_layout.addWidget(nameplate_image, 0, Qt.AlignmentFlag.AlignLeft)
        layout.addWidget(self.platform_nameplate_group)

        self.platform_cpld_group = QGroupBox("CPLD type")
        cpld_layout = QVBoxLayout(self.platform_cpld_group)
        self.platform_cpld_type_combo = QComboBox()
        self.platform_cpld_type_combo.addItem("LA4128V", "la4128v")
        self.platform_cpld_type_combo.addItem("LC4256V", "lc4256v")
        self.platform_cpld_type_combo.currentIndexChanged.connect(self.platform_cpld_type_changed)
        cpld_form = QFormLayout()
        cpld_form.addRow("Rev04 CPLD type", self.platform_cpld_type_combo)
        cpld_layout.addLayout(cpld_form)
        cpld_hint = QLabel(
            "UltraZohm Rev04 can use different D-slot CPLDs. Select by system serial number:\n"
            "- LA4128V: Revisions < Rev04 and Rev04 systems from UZ2021-002-001-200-0001 "
            "to UZ2021-001-001-004-0004\n"
            "- LC4256V: Rev04 systems from UZ2022-001-001-401-0007 "
            "up to UZ2024-001-001-0401-0031\n"
            "Attention!: The 'Programm CPLDs via CLI' workflow in the 'Slot CPLDs' page is not supported for LA4128/LC4256 CPLDs"
        )
        cpld_hint.setWordWrap(True)
        cpld_hint.setMinimumHeight(92)
        cpld_layout.addWidget(cpld_hint)
        layout.addWidget(self.platform_cpld_group)
        layout.addStretch(1)
        return page
