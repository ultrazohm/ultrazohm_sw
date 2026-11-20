"""Workspace runtime preferences and effective session profiles."""

import json
from dataclasses import dataclass
from pathlib import Path

from .user_paths import write_json


def default_profile(repo=None):
    from ultrazohm_cli.configuration import default_profile as cli_defaults

    return cli_defaults(repo)


def read_runtime_settings(path):
    from ultrazohm_cli.configuration import read_profile

    return read_profile(path)


@dataclass(frozen=True)
class WorkspaceSettings:
    path: Path
    mapping: dict
    profile: dict


def load_workspace_settings(mapping_path, user_directory=None):
    """Read workspace configuration, seeding only missing preferences."""
    mapping_path = Path(mapping_path).expanduser().resolve()
    mapping = _check_mapping(json.loads(mapping_path.read_text(encoding="utf-8")))
    directory = (
        Path(user_directory).expanduser().resolve()
        if user_directory
        else mapping_path.parent
    )
    directory.mkdir(parents=True, exist_ok=True)
    settings_path = directory / "settings.json"
    if not settings_path.exists():
        defaults, _ = profile_for_mapping(mapping, default_profile(), None)
        write_json(settings_path, defaults, overwrite=False)
    settings = read_runtime_settings(settings_path)
    write_json(directory / "tools.json", {"xsct": None}, overwrite=False)
    (directory / "logs").mkdir(exist_ok=True)
    return WorkspaceSettings(settings_path, mapping, settings)


def load_repository_settings(repo):
    """Ask the CLI for firmware metadata/defaults; retain explicit user settings."""
    from .live_mapping import read_mapping
    from .user_paths import data_directory

    mapping = _check_mapping(read_mapping(repo))
    directory = data_directory(repo)
    settings_path = directory / "settings.json"
    if not settings_path.exists():
        write_json(settings_path, default_profile(repo), overwrite=False)
    settings = read_runtime_settings(settings_path)
    write_json(directory / "tools.json", {"xsct": None}, overwrite=False)
    (directory / "logs").mkdir(exist_ok=True)
    return WorkspaceSettings(settings_path, mapping, settings)


def prepare_profile(mapping_path, output_profile=None, user_directory=None):
    """Filter a service's effective profile without rewriting user preferences."""
    workspace = load_workspace_settings(mapping_path, user_directory)
    profile, removed = profile_for_mapping(workspace.mapping, workspace.profile, None)
    if output_profile is None and profile == workspace.profile:
        return workspace.path, removed
    effective_path = (
        Path(output_profile)
        if output_profile
        else workspace.path.parent / "runtime.profile.json"
    )
    write_json(effective_path, profile)
    return effective_path, removed


def _check_mapping(mapping):
    if (
        not isinstance(mapping, dict)
        or not isinstance(mapping.get("observables"), dict)
        or type(mapping.get("channels")) is not int
    ):
        raise ValueError(
            "Invalid channel mapping: expected an observables object and integer channels; "
            "regenerate it with create-json-from-javascope-h"
        )
    return mapping


def profile_for_mapping(mapping, previous, assignments):
    from ultrazohm_cli.configuration import remap_profile

    return remap_profile(mapping, previous, assignments)
