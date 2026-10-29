"""Workspace runtime preferences and effective session profiles."""
import json
import math
import subprocess
from pathlib import Path

from .user_paths import write_json


def default_profile():
    from .process_launcher import command
    try:
        result = subprocess.run(command('cli', 'profile'), capture_output=True,
                                text=True, encoding='utf-8', errors='replace', check=True, timeout=15)
    except subprocess.CalledProcessError as exc:
        raise RuntimeError('Could not load default runtime settings: ' + (exc.stderr or str(exc)).strip()) from exc
    except subprocess.TimeoutExpired as exc:
        raise RuntimeError('Timed out loading default runtime settings') from exc
    return json.loads(result.stdout)


def read_runtime_settings(path):
    settings = json.loads(Path(path).read_text(encoding='utf-8'))
    fields = {'schema_version', 'name', 'sample_period_us', 'initial_channels'}
    valid = isinstance(settings, dict) and not (settings.keys() - fields)
    if valid:
        period = settings.get('sample_period_us')
        initial = settings.get('initial_channels', {})
        valid = (type(settings.get('schema_version')) is int and settings['schema_version'] == 1
                 and isinstance(settings.get('name'), str)
                 and type(period) in (int, float) and math.isfinite(period) and period > 0
                 and isinstance(initial, dict)
                 and all(isinstance(key, str) and key.isascii() and key.isdecimal()
                         and isinstance(value, str) for key, value in initial.items()))
    if not valid:
        raise ValueError(f'Invalid runtime settings in {path}: expected schema_version 1, name, '
                         'positive sample_period_us and optional initial_channels object')
    return settings


def initialize_user_settings(mapping_path, user_directory=None):
    """Seed workspace preferences once, preserving existing files byte for byte."""
    mapping_path = Path(mapping_path).expanduser().resolve()
    directory = Path(user_directory).expanduser().resolve() if user_directory else mapping_path.parent
    directory.mkdir(parents=True, exist_ok=True)
    settings_path = directory / 'settings.json'
    if not settings_path.exists():
        mapping = json.loads(mapping_path.read_text(encoding='utf-8'))
        defaults, _ = profile_for_mapping(mapping, default_profile(), None)
        write_json(settings_path, defaults, overwrite=False)
    read_runtime_settings(settings_path)
    write_json(directory / 'tools.json', {'xsct': None}, overwrite=False)
    (directory / 'logs').mkdir(exist_ok=True)
    return settings_path


def prepare_profile(mapping_path, output_profile=None, user_directory=None):
    """Filter a service's effective profile without rewriting user preferences."""
    mapping_path = Path(mapping_path).expanduser().resolve()
    settings_path = initialize_user_settings(mapping_path, user_directory)
    settings = read_runtime_settings(settings_path)
    mapping = json.loads(mapping_path.read_text(encoding='utf-8'))
    profile, removed = profile_for_mapping(mapping, settings, None)
    if output_profile is None and profile == settings:
        return settings_path, removed
    effective_path = Path(output_profile) if output_profile else settings_path.parent / 'runtime.profile.json'
    write_json(effective_path, profile)
    return effective_path, removed


def profile_for_mapping(mapping, previous, assignments):
    settings = previous if previous else default_profile()
    initial = assignments if assignments is not None else settings.get('initial_channels', {})
    selected, removed = {}, []
    for channel, name in initial.items():
        canonical = name if name in mapping['observables'] else f'JSO_{name}'
        if canonical in mapping['observables'] and 1 <= int(channel) <= mapping['channels']:
            selected[str(channel)] = canonical
        else:
            removed.append(name)
    if not selected and initial and 'JSO_ZEROVALUE' in mapping['observables']:
        selected['1'] = 'JSO_ZEROVALUE'
    return {'schema_version': 1, 'name': settings.get('name', 'viewer-flash'),
            'sample_period_us': settings['sample_period_us'], 'initial_channels': selected}, removed
