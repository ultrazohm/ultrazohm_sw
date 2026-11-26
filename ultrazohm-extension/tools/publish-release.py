"""Resume a GitHub release without replacing any existing asset."""
import json
import os
from pathlib import Path
import subprocess
import tempfile
import release


def publish(directory):
    release.aggregate(directory)
    info = release.metadata()
    tag = info['tag']
    def gh(*args, check=True):
        return subprocess.run(['gh', *map(str, args)], check=check, text=True, capture_output=True)
    existing = gh('release', 'view', tag, '--json', 'isDraft,assets,targetCommitish', check=False)
    files = sorted(directory.glob('*.vsix')) + [directory/'SHA256SUMS', directory/'release-manifest.json']
    if existing.returncode:
        # A failed lookup is not proof of absence; create fails safely if it exists.
        gh('release', 'create', tag, '--target', os.environ['GITHUB_SHA'], '--latest=false', '--draft',
           *(['--prerelease'] if info['prerelease'] else []), '--title', 'ultrazohm-extension '+info['version'],
           '--notes-file', directory/'release-notes.md', *files)
    else:
        state = json.loads(existing.stdout)
        names = {asset['name'] for asset in state['assets']}
        with tempfile.TemporaryDirectory() as temporary:
            for file in files:
                if file.name in names:
                    gh('release', 'download', tag, '--pattern', file.name, '--dir', temporary)
                    if release.digest(Path(temporary)/file.name) != release.digest(file):
                        raise ValueError('Existing release asset differs: '+file.name)
                elif state['isDraft']:
                    gh('release', 'upload', tag, file)
                else:
                    raise ValueError('Published release is incomplete: '+file.name)
    gh('release', 'edit', tag, '--draft=false')

if __name__ == '__main__':
    publish(Path('dist'))
