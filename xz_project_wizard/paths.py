from __future__ import annotations

from pathlib import Path

APP_DIR = Path(__file__).resolve().parent
DATA_FILE = APP_DIR / "data" / "adapter_cards.json"
PLATFORM_FILE = APP_DIR / "data" / "platforms.json"
OUTPUT_DIR = APP_DIR / "generated"
TEMPLATE_DIR = APP_DIR / "templates"
SLOTS = ["A1", "A2", "A3", "D1", "D2", "D3", "D4", "D5"]
DIGITAL_SLOTS = ["D1", "D2", "D3", "D4", "D5"]
