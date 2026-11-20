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
