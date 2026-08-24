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


class NavigationMixin:
    def _build_navigation(self) -> QTreeWidget:
        tree = QTreeWidget()
        tree.setHeaderHidden(True)
        toolchain = QTreeWidgetItem(["Toolchain"])
        platform = QTreeWidgetItem(["Platform"])
        config = QTreeWidgetItem(["Hardware configuration"])
        hardware_general = QTreeWidgetItem(["General"])
        adapter_cards = QTreeWidgetItem(["Adapter cards"])
        pwm = QTreeWidgetItem(["PWM / Timing / Interrupts"])
        axi_interconnect = QTreeWidgetItem(["ADC triggers"])
        tcl_generation = QTreeWidgetItem(["TCL generation"])
        slot_cplds = QTreeWidgetItem(["Slot CPLDs"])
        config.addChild(hardware_general)
        config.addChild(pwm)
        config.addChild(adapter_cards)
        config.addChild(axi_interconnect)
        config.addChild(tcl_generation)
        config.addChild(slot_cplds)
        software_config = QTreeWidgetItem(["Software configuration"])
        software_general = QTreeWidgetItem(["General"])
        ip_driver_setup = QTreeWidgetItem(["IP core driver setup"])
        advanced_driver_config = QTreeWidgetItem(["Advanced driver configuration"])
        data_visualization = QTreeWidgetItem(["Data visualization"])
        software_config.addChild(software_general)
        software_config.addChild(ip_driver_setup)
        software_config.addChild(advanced_driver_config)
        software_config.addChild(data_visualization)
        tree.addTopLevelItem(toolchain)
        tree.addTopLevelItem(platform)
        tree.addTopLevelItem(config)
        tree.addTopLevelItem(software_config)
        config.setExpanded(True)
        software_config.setExpanded(True)
        tree.setCurrentItem(toolchain)
        tree.currentItemChanged.connect(self._navigation_changed)
        return tree


    def _navigation_changed(self, current: QTreeWidgetItem | None) -> None:
        if not current:
            return
        if current.text(0) in {"Hardware configuration", "Software configuration"}:
            first_child = current.child(0)
            if first_child is not None:
                QTimer.singleShot(0, lambda item=first_child: self.tree.setCurrentItem(item))
                return
        page_by_name = {
            "Toolchain": 0,
            "Platform": 1,
            "Hardware configuration": 2,
            "General": 2 if current.parent() and current.parent().text(0) == "Hardware configuration" else 8,
            "Adapter cards": 3,
            "PWM / Timing / Interrupts": 4,
            "ADC triggers": 5,
            "TCL generation": 6,
            "Slot CPLDs": 7,
            "Software configuration": 8,
            "IP core driver setup": 9,
            "Advanced driver configuration": 10,
            "Data visualization": 11,
        }
        self.stack.setCurrentIndex(page_by_name.get(current.text(0), 0))


    def show_platform_page(self) -> None:
        self.stack.setCurrentIndex(1)
        self.tree.setCurrentItem(self.tree.topLevelItem(1))


    def show_toolchain_page(self) -> None:
        self.stack.setCurrentIndex(0)
        self.tree.setCurrentItem(self.tree.topLevelItem(0))


    def show_adapter_cards(self) -> None:
        self.stack.setCurrentIndex(3)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(2))


    def show_hardware_configuration(self) -> None:
        self.show_hardware_general()


    def show_hardware_general(self) -> None:
        self.stack.setCurrentIndex(2)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(0))


    def show_slot_cplds(self) -> None:
        self.stack.setCurrentIndex(7)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(5))


    def show_axi_interconnect(self) -> None:
        self.stack.setCurrentIndex(5)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(3))


    def show_tcl_generation(self) -> None:
        self.stack.setCurrentIndex(6)
        self.tree.setCurrentItem(self.tree.topLevelItem(2).child(4))


    def show_card_database(self) -> None:
        self.stack.setCurrentIndex(12)


    def show_software_general(self) -> None:
        self.stack.setCurrentIndex(8)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(0))


    def show_ip_core_driver_setup(self) -> None:
        self.stack.setCurrentIndex(9)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(1))


    def show_advanced_driver_config(self) -> None:
        self.refresh_dirty_software_dependent_views()
        self.stack.setCurrentIndex(10)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(2))


    def show_data_visualization(self) -> None:
        self.refresh_dirty_software_dependent_views()
        self.stack.setCurrentIndex(11)
        self.tree.setCurrentItem(self.tree.topLevelItem(3).child(3))
