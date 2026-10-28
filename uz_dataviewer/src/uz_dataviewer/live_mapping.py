"""Generate a fresh firmware contract with the installed CLI, without device IO."""
from datetime import datetime, timezone
import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile

HEADER = Path('vitis/software/Baremetal/src/include/javascope.h')


def repository(explicit=None):
    if explicit is not None:
        root = Path(explicit).expanduser().resolve()
        if not (root / HEADER).is_file():
            raise ValueError(f'JavaScope header not found under {root}')
        return root
    for start in (Path.cwd(), Path(__file__).resolve().parent):
        for root in (start, *start.parents):
            if (root / HEADER).is_file():
                return root
    raise ValueError('UltraZohm repository not found; pass --live-repo PATH to generate its channel mapping')


def generate_mapping(repo=None, *, overwrite=False):
    root = repository(repo)
    cache = root / 'uz_cli_channel_mappings'
    cache.mkdir(parents=True, exist_ok=True)
    # Only publish successful output; a parser error must never reuse stale data.
    with tempfile.TemporaryDirectory(prefix='.generate-', dir=cache) as temporary:
        generated = Path(temporary) / 'javascope.json'
        result = subprocess.run([sys.executable, '-m', 'ultrazohm',
            'create-json-from-javascope-h', '--repo', str(root), '--output', str(generated)],
            capture_output=True, text=True, encoding='utf-8', errors='replace')
        if result.returncode:
            raise RuntimeError('Channel mapping generation failed: ' + (result.stderr.strip() or result.stdout.strip()))
        mapping = json.loads(generated.read_text(encoding='utf-8'))
        commit = mapping['repository']['commit']
        if not isinstance(commit, str) or not re.fullmatch(r'[A-Za-z0-9_-]+', commit):
            raise ValueError('Generated channel mapping has an invalid repository commit')
        timestamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ')
        name = f'javascope_{commit}.json' if overwrite else f'javascope_{timestamp}_{commit}.json'
        destination = cache / name
        generated.replace(destination)
    print(f'Live channel mapping: {destination}', flush=True)
    return destination
