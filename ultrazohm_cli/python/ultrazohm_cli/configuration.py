"""Offline firmware configuration; validation and remapping run in Rust.

Invalid configurations raise ValueError.
"""

import os
from pathlib import Path

from . import _native


def _path(value):
    return None if value is None else Path(os.fspath(value))


def channel_mapping(repo):
    """Parse the checkout's firmware headers without contacting a device."""
    return _native.channel_mapping(Path(os.fspath(repo)))


def default_profile(repo=None):
    """Return built-in startup preferences, filtered for a checkout if supplied."""
    return _native.default_profile(_path(repo))


def validate_profile(profile):
    """Validate runtime preference structure; return normalized preferences."""
    try:
        return _native.validate_profile(profile)
    except ValueError as exc:
        raise ValueError(f"Invalid runtime settings: {exc}") from exc


def read_profile(path):
    """Load and validate a runtime preference file."""
    import json

    return validate_profile(json.loads(Path(path).read_text(encoding="utf-8")))


def remap_profile(mapping, profile=None, assignments=None):
    """Return (effective preferences, removed names) for a firmware contract."""
    profile = dict(default_profile() if profile is None else profile)
    if assignments is not None:
        profile["initial_channels"] = assignments
    return _native.remap_profile(mapping, profile)


def preferences_directory(repo=None):
    """Return the shared preferences directory without creating files."""
    return _native.preferences_directory(_path(repo))


def resolve_xsct(path=None, repo=None):
    """Resolve explicit launcher, saved workspace selection, then PATH."""
    return _native.resolve_xsct(_path(path) if path else None, _path(repo))


def saved_xsct(repo=None):
    return _native.saved_xsct(_path(repo))


def save_xsct(path, repo=None):
    return _native.save_xsct(_path(path), _path(repo))


def load_or_seed_profile(path, mapping):
    """Atomically seed missing defaults; preserve existing preferences."""
    try:
        return _native.load_or_seed_profile(_path(path), mapping)
    except ValueError as exc:
        raise ValueError(f"Invalid runtime settings: {exc}") from exc


def save_profile(path, profile, mapping):
    """Validate against local firmware before atomically replacing preferences."""
    _native.save_profile(_path(path), profile, mapping)


def startup_profile_path(repo=None, directory=None):
    """Conventional profile location; explicit directories support mapping-only clients."""
    return (
        Path(directory) if directory is not None else preferences_directory(repo)
    ) / "settings.json"
