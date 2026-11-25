"""Generate a fresh firmware contract with the installed CLI, without device IO."""

import re
from pathlib import Path

from .user_paths import HEADER, find_repository


def repository(explicit=None):
    if explicit is not None:
        root = Path(explicit).expanduser().resolve()
        if not (root / HEADER).is_file():
            raise ValueError(f"JavaScope header not found under {root}")
        return root
    for start in (Path.cwd(), Path(__file__).resolve().parent):
        if root := find_repository(start):
            return root
    raise ValueError(
        "UltraZohm repository not found; pass --live-repo PATH to generate its channel mapping"
    )


def read_mapping(repo):
    """Read the CLI's repository mapping without a subprocess or intermediate file."""
    from ultrazohm_cli.configuration import channel_mapping

    return channel_mapping(repo)


def generate_mapping(repo=None):
    """Publish a fresh mapping obtained through the CLI configuration API."""
    from .user_paths import data_directory, write_json

    root = repository(repo)
    mapping = read_mapping(root)
    commit = mapping["repository"]["commit"]
    if not isinstance(commit, str) or not re.fullmatch(r"[A-Za-z0-9_-]+", commit):
        raise ValueError("Generated channel mapping has an invalid repository commit")
    destination = data_directory(root) / f"javascope_{commit}.json"
    write_json(destination, mapping)
    return destination
