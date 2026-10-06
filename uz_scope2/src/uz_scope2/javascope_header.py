"""Parser for ``javascope.h`` — the client's configuration source (GUI-free).

Ports ``javascope/src/UZ_GUI/JavascopeHeaderParser.java``: the header is not
parsed as C, but scanned line by line for marker-delimited sections.  A section
starts at its ``*_ZEROVALUE`` line (which itself becomes entry 0, so list index
== enum index == wire id) and ends before its ``*_ENDMARKER`` line.  Comments
are stripped per line, so the sections inside the block comment
``/* Visualization Config for GUI */`` parse the same way as real enums.

Two sanitize modes mirror the Java ``ParseMode``:

- ``identifier``: whitespace removed, everything from ``=`` on dropped
  (enum entries, slowdata display mapping).
- ``compact_text``: whitespace removed, a literal ``=0`` removed
  (display labels such as ``dut_n_ref_rpm`` or units such as ``-``).
"""

from __future__ import annotations

import re
from dataclasses import dataclass, field
from pathlib import Path

DEFAULT_HEADER_RELPATH = "vitis/software/Baremetal/src/include/javascope.h"

_SECTIONS = (
    # (attribute, start marker, end marker, mode)
    ("observables", "JSO_ZEROVALUE", "JSO_ENDMARKER", "identifier"),
    ("slowdata", "JSSD_ZEROVALUE", "JSSD_ENDMARKER", "identifier"),
    ("buttons", "GUI_BTN_ZEROVALUE", "GUI_BTN_ENDMARKER", "identifier"),
    ("send_field_names", "SND_FLD_ZEROVALUE", "SND_FLD_ENDMARKER", "compact_text"),
    ("send_field_units", "SND_LABELS_ZEROVALUE", "SND_LABELS_ENDMARKER", "compact_text"),
    ("receive_field_names", "RCV_FLD_ZEROVALUE", "RCV_FLD_ENDMARKER", "compact_text"),
    ("receive_field_units", "RCV_LABELS_ZEROVALUE", "RCV_LABELS_ENDMARKER", "compact_text"),
    ("mybutton_labels", "MYBUTTONS_LABELS_ZEROVALUE", "MYBUTTONS_LABELS_ENDMARKER", "compact_text"),
    ("slowdata_display", "SLOWDAT_DISPLAY_ZEROVALUE", "SLOWDAT_DISPLAY_ENDMARKER", "identifier"),
)


@dataclass
class HeaderConfig:
    """All GUI-relevant sections of ``javascope.h``. List index == enum index."""

    source: str = ""
    observables: list[str] = field(default_factory=list)
    slowdata: list[str] = field(default_factory=list)
    buttons: list[str] = field(default_factory=list)
    send_field_names: list[str] = field(default_factory=list)
    send_field_units: list[str] = field(default_factory=list)
    receive_field_names: list[str] = field(default_factory=list)
    receive_field_units: list[str] = field(default_factory=list)
    mybutton_labels: list[str] = field(default_factory=list)
    slowdata_display: list[str] = field(default_factory=list)
    warnings: list[str] = field(default_factory=list)

    @property
    def observable_index(self) -> dict[str, int]:
        return {name: i for i, name in enumerate(self.observables)}

    @property
    def button_id(self) -> dict[str, int]:
        return {name: i for i, name in enumerate(self.buttons)}

    @property
    def slowdata_index(self) -> dict[str, int]:
        return {name: i for i, name in enumerate(self.slowdata)}


def _strip_comments(line: str) -> str:
    pos = line.find("//")
    if pos >= 0:
        line = line[:pos]
    while True:
        start = line.find("/*")
        if start < 0:
            break
        end = line.find("*/", start + 2)
        if end < 0:
            line = line[:start]
            break
        line = line[:start] + line[end + 2 :]
    return line


def _remove_trailing_delimiters(token: str) -> str:
    return token.strip().rstrip(",;").strip()


def _normalize_marker(line: str) -> str:
    token = _remove_trailing_delimiters(_strip_comments(line).strip())
    return "".join(token.split())


def _identifier_part(token: str) -> str:
    return token.split("=", 1)[0]


def _sanitize(line: str, mode: str) -> str:
    token = _strip_comments(line).strip()
    if not token:
        return ""
    token = _remove_trailing_delimiters(token)
    token = "".join(token.split())
    if mode == "identifier":
        token = _identifier_part(token)
        token = _remove_trailing_delimiters(token)
        # Drop structural junk ('}', '};', ...) that an unterminated section
        # would otherwise sweep up.
        if not re.fullmatch(r"[A-Za-z_]\w*", token):
            return ""
        return token
    token = token.replace("=0", "")
    return _remove_trailing_delimiters(token)


def _read_section(
    lines: list[str], start_marker: str, end_marker: str, mode: str
) -> tuple[list[str], int, int]:
    """Collect sanitized entries between the markers; the start line is entry 0."""
    entries: list[str] = []
    start_count = end_count = 0
    in_section = False
    for line in lines:
        candidate = _normalize_marker(line)
        if candidate and _identifier_part(candidate) == start_marker:
            start_count += 1
            in_section = True
            entry = _sanitize(line, mode)
            if entry:
                entries.append(entry)
            continue
        if candidate and _identifier_part(candidate) == end_marker:
            end_count += 1
            in_section = False
            continue
        if not in_section:
            continue
        entry = _sanitize(line, mode)
        if entry:
            entries.append(entry)
    return entries, start_count, end_count


def parse_header_text(text: str, source: str = "<string>") -> HeaderConfig:
    lines = text.splitlines()
    cfg = HeaderConfig(source=source)
    for attr, start_marker, end_marker, mode in _SECTIONS:
        entries, starts, ends = _read_section(lines, start_marker, end_marker, mode)
        setattr(cfg, attr, entries)
        if starts != 1 or ends != 1:
            cfg.warnings.append(
                f"section {start_marker}..{end_marker}: expected exactly one "
                f"start/end marker, found {starts}/{ends}"
            )
        elif not entries:
            cfg.warnings.append(f"section {start_marker}..{end_marker}: empty")
    for name in cfg.slowdata_display[1:]:  # entry 0 is the section marker itself
        if name not in cfg.slowdata and name != "JSSD_FLOAT_ZEROVALUE":
            cfg.warnings.append(
                f"SLOWDAT_DISPLAY entry {name!r} is not in the JS_SlowData enum"
            )
    return cfg


def parse_header(path: str | Path) -> HeaderConfig:
    path = Path(path)
    return parse_header_text(path.read_text(encoding="utf-8", errors="replace"), str(path))


def find_header(start_dir: str | Path | None = None) -> Path | None:
    """Walk up from ``start_dir`` (default: cwd) looking for the repo header."""
    directory = Path(start_dir) if start_dir is not None else Path.cwd()
    directory = directory.resolve()
    for candidate_root in (directory, *directory.parents):
        candidate = candidate_root / DEFAULT_HEADER_RELPATH
        if candidate.is_file():
            return candidate
    return None
