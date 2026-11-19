"""Test the extracted Windows downloads from paths containing spaces."""
import argparse
from pathlib import Path
import subprocess
import sys
import tempfile
import zipfile


def smoke(directory, version):
    if sys.platform != 'win32':
        raise RuntimeError('Windows archives must be tested on Windows')
    root = Path(__file__).resolve().parents[1]
    for name in ('ultrazohm-cli', 'ultrazohm-dataviewer'):
        archive = Path(directory).resolve() / f'{name}-{version}-windows-x86_64.zip'
        with tempfile.TemporaryDirectory(prefix='UltraZohm extracted release ') as directory:
            with zipfile.ZipFile(archive) as package:
                package.extractall(directory)
            application = Path(directory) / name
            cli = application / 'ultrazohm-cli.exe'
            output = subprocess.check_output([str(cli), '--version'], cwd=directory, text=True, timeout=30)
            if output.strip() != f'ultrazohm-cli {version}':
                raise RuntimeError(f'Unexpected standalone CLI version: {output!r}')
            if name.endswith('dataviewer'):
                build = root / 'ultrazohm_dataviewer' / 'build'
                subprocess.run([sys.executable, str(build / 'smoke_powershell.py'),
                                str(application / 'ultrazohm-dataviewer.ps1')],
                               cwd=directory, check=True, timeout=180)
                subprocess.run([sys.executable, str(build / 'smoke_binary.py'),
                                str(application / 'ultrazohm-dataviewer.exe')],
                               cwd=directory, check=True, timeout=180)
    print('Both extracted Windows archives passed.')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory')
    parser.add_argument('version')
    args = parser.parse_args()
    smoke(args.directory, args.version)
