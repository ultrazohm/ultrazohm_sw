"""Run before replacing the locked CLI with a locally built wheel in CI."""
import json
from pathlib import Path
import platform
import subprocess
import sys

import pytest


def test_cli_supports_repository_configuration():
    supported = ((sys.platform == 'linux' and platform.machine() == 'x86_64')
                 or (sys.platform == 'win32' and platform.machine() == 'AMD64'))
    if not supported:
        pytest.skip('Published CLI wheels are unavailable on this platform')
    __import__('ultrazohm_cli')  # Missing/broken native wheels must fail on supported platforms.
    root = Path(__file__).resolve().parents[2]
    results = {}
    for command in ('channel-mapping', 'profile'):
        result = subprocess.run([sys.executable, '-m', 'ultrazohm_cli', command, '--repo', str(root)],
                                capture_output=True, text=True, encoding='utf-8', timeout=30)
        assert result.returncode == 0, result.stderr
        results[command] = json.loads(result.stdout)
    mapping, profile = results['channel-mapping'], results['profile']
    assert mapping['channels'] == 20
    assert profile['schema_version'] == 1
    assert set(profile['initial_channels'].values()) <= mapping['observables'].keys()
