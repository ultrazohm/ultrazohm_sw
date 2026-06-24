"""Guards for the generated console-command reference (see command_doc.py)."""

import pytest

from uz_dataviewer.command_doc import CSV_PATH, build_csv, group_for
from uz_dataviewer.commands import CommandRegistry


def test_csv_up_to_date():
    """The committed CSV must match what the registry produces.

    If this fails, a command changed without regenerating the docs table. Run:
        python -m uz_dataviewer.command_doc
    """
    committed = CSV_PATH.read_text(encoding="utf-8")
    assert committed == build_csv(), (
        "uz_dataviewer_commands.csv is stale; "
        "regenerate with `python -m uz_dataviewer.command_doc`"
    )


def test_every_command_grouped():
    """Every registered command must resolve to a documentation group."""
    for cmd in CommandRegistry().all():
        try:
            group_for(cmd.name)
        except KeyError as exc:  # pragma: no cover - failure path
            pytest.fail(str(exc))
