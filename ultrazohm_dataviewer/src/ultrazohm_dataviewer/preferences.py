"""Versioned application preferences, independent of sessions and device settings."""

import json
from pathlib import Path

from .user_paths import user_data_directory, write_json
from .validation import boolean, cache_budget_mb, display_budget

DEFAULTS = {
    "backend": "polars",
    "loading_mode": "lazy",
    "disk_cache": False,
    "cache_budget": 1024,
    "max_points": 2000,
    "log_directory": "",
    "show_application_log": True,
    "show_python": False,
}
COMMANDS = {
    "backend": "backend",
    "loading_mode": "loading_mode",
    "disk_cache": "disk_cache",
    "cache_budget": "cache_budget",
    "max_points": "set_max_points",
}
SECTIONS = {
    "General": ("log_directory", "show_application_log", "show_python"),
    "Data loading": ("backend", "loading_mode", "disk_cache"),
    "Performance": ("cache_budget", "max_points"),
}


def validate(name, value):
    if name not in DEFAULTS:
        raise ValueError(f"Unknown setting: {name}")
    if name in ("backend", "loading_mode"):
        choices = ("pyarrow", "polars") if name == "backend" else ("memory", "lazy")
        if value not in choices:
            raise ValueError(f"{name} must be one of {choices}")
    elif name in ("disk_cache", "show_application_log", "show_python"):
        value = boolean(value)
    elif name == "cache_budget":
        value = cache_budget_mb(value)
    elif name == "max_points":
        value = display_budget(value)
    elif name == "log_directory":
        if not isinstance(value, str):
            raise ValueError("Log directory must be a path string")
        value = str(Path(value).expanduser().resolve()) if value.strip() else ""
    return value


class Preferences:
    def __init__(self, state=None):
        self.state = state
        self.path = user_data_directory() / "viewer_preferences.json"
        self.values = dict(DEFAULTS)
        self.changed = None
        self.error = ""
        try:
            if self.path.exists():
                data = json.loads(self.path.read_text(encoding="utf-8"))
                if data.get("version") != 1 or not isinstance(
                    data.get("settings"), dict
                ):
                    raise ValueError("Unsupported viewer preferences format")
                loaded = {
                    name: validate(name, value)
                    for name, value in data["settings"].items()
                }
                self.values.update(loaded)
        except (OSError, ValueError, TypeError, AttributeError) as exc:
            self.error = f"Could not load Settings: {exc}"

    def apply(self):
        if self.state is not None:
            for name, command in COMMANDS.items():
                self.state.commands.execute(
                    self.state, command, [self.values[name]], echo=False
                )

    def update(self, changes):
        values = dict(self.values)
        values.update({name: validate(name, value) for name, value in changes.items()})
        if "backend" in changes:
            from .loader import validate_backend

            validate_backend(values["backend"])
        self.path.parent.mkdir(parents=True, exist_ok=True)
        write_json(self.path, {"version": 1, "settings": values})
        self.values = values
        if self.state is not None:
            for name in changes:
                if name in COMMANDS:
                    self.state.commands.execute(
                        self.state, COMMANDS[name], [values[name]], echo=False
                    )
        if self.changed is not None:
            self.changed(changes)

    def reset(self, section):
        self.update({name: DEFAULTS[name] for name in SECTIONS[section]})
