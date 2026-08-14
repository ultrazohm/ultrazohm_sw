from __future__ import annotations

from pathlib import Path

APP_DIR = Path(__file__).resolve().parent
DATA_FILE = APP_DIR / "data" / "adapter_cards.json"
PLATFORM_FILE = APP_DIR / "data" / "platforms.json"
SOFTWARE_DRIVER_FILE = APP_DIR / "data" / "software_drivers.json"
OUTPUT_DIR = APP_DIR / "generated"
USER_CONFIG_DIR = APP_DIR / "user_configurations"
GOLDEN_SCENARIO_DIR = OUTPUT_DIR / "golden_scenarios"
VIVADO_BD_CONFIG_DIR = OUTPUT_DIR / "vivado_bd_config"
VIVADO_RUN_SCRIPT_DIR = OUTPUT_DIR / "vivado_run_scripts"
CPLD_CONFIG_DIR = OUTPUT_DIR / "cpld_config"
LOG_DIR = OUTPUT_DIR / "logs"
TEMPLATE_DIR = APP_DIR / "templates"
SLOTS = ["A1", "A2", "A3", "D1", "D2", "D3", "D4", "D5"]
DIGITAL_SLOTS = ["D1", "D2", "D3", "D4", "D5"]
