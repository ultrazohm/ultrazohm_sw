"""Offline firmware configuration; validation and remapping run in Rust."""

import json
import os
from pathlib import Path

from ._native import configuration as _configuration


def channel_mapping(repo):
    """Parse the checkout's firmware headers without contacting a device."""
    return json.loads(_configuration("mapping", repo=os.fspath(repo)))


def default_profile(repo=None):
    """Return built-in startup preferences, filtered for a checkout if supplied."""
    return json.loads(
        _configuration("defaults", repo=os.fspath(repo) if repo is not None else None)
    )


def validate_profile(profile):
    """Validate runtime preference structure; return normalized preferences."""
    try:
        return json.loads(
            _configuration("validate", json.dumps(profile, allow_nan=False))
        )
    except RuntimeError as exc:
        raise ValueError(f"Invalid runtime settings: {exc}") from exc


def read_profile(path):
    """Load and validate a runtime preference file."""
    return validate_profile(json.loads(Path(path).read_text(encoding="utf-8")))


def remap_profile(mapping, profile=None, assignments=None):
    """Return (effective preferences, removed names) for a firmware contract."""
    profile = dict(default_profile() if profile is None else profile)
    if assignments is not None:
        profile["initial_channels"] = assignments
    result = json.loads(
        _configuration(
            "remap",
            json.dumps({"mapping": mapping, "profile": profile}, allow_nan=False),
        )
    )
    return result["profile"], result["removed"]


def _stored(operation, payload=None, repo=None):
    try:
        return json.loads(
            _configuration(
                operation,
                json.dumps(payload, allow_nan=False),
                repo=os.fspath(repo) if repo is not None else None,
            )
        )
    except RuntimeError as exc:
        raise ValueError(str(exc)) from exc


def preferences_directory(repo=None):
    """Return the shared preferences directory without creating files."""
    return Path(_stored("directory", repo=repo))


def resolve_xsct(path=None, repo=None):
    """Resolve explicit launcher, saved workspace selection, then PATH."""
    return Path(_stored("xsct", {"path": os.fspath(path) if path else None}, repo))


def saved_xsct(repo=None):
    value = _stored("saved_xsct", repo=repo)
    return Path(value) if value else None


def save_xsct(path, repo=None):
    return Path(_stored("save_xsct", os.fspath(path), repo))


def load_or_seed_profile(path, mapping):
    """Atomically seed missing defaults; preserve existing preferences."""
    try:
        return _stored("seed_profile", {"path": os.fspath(path), "mapping": mapping})
    except ValueError as exc:
        raise ValueError(f"Invalid runtime settings: {exc}") from exc


def save_profile(path, profile, mapping):
    """Validate against local firmware before atomically replacing preferences."""
    _stored(
        "save_profile",
        {"path": os.fspath(path), "profile": profile, "mapping": mapping},
    )


def startup_profile_path(repo=None, directory=None):
    """Conventional profile location; explicit directories support mapping-only clients."""
    return (
        Path(directory) if directory is not None else preferences_directory(repo)
    ) / "settings.json"
