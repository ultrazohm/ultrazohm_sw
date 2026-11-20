"""Guards for the generated console-command reference (see command_doc.py)."""

from pathlib import Path

import pytest

from ultrazohm_dataviewer.cli import public_methods
from ultrazohm_dataviewer.command_doc import build_csv, group_for


def test_csv_up_to_date():
    """The committed CSV must match what the registry produces.

    If this fails, a command changed without regenerating the docs table. Run:
        python -m ultrazohm_dataviewer.command_doc
    """
    csv_path = (
        Path(__file__).resolve().parents[2]
        / "docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_commands.csv"
    )
    committed = csv_path.read_text(encoding="utf-8")
    assert committed == build_csv(), (
        "ultrazohm_dataviewer_commands.csv is stale; "
        "regenerate with `python -m ultrazohm_dataviewer.command_doc`"
    )


def test_every_command_grouped():
    """Every registered command must resolve to a documentation group."""
    for name in public_methods():
        try:
            group_for(name)
        except KeyError as exc:  # pragma: no cover - failure path
            pytest.fail(str(exc))
