"""Python utilities for UltraZohm."""

from importlib import import_module

__version__ = "0.1.0"

__all__ = ["__version__", "docs", "machine_catalog", "pmsm"]


def __getattr__(name: str):
	if name in {"docs", "machine_catalog", "pmsm"}:
		return import_module(f"pyuzlib.{name}")
	raise AttributeError(f"module 'pyuzlib' has no attribute {name!r}")
