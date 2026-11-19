"""Install a release from PyPI into fresh CLI-only and combined environments."""
import argparse
import os
from pathlib import Path
import subprocess
import tempfile
import time


def verify(version):
    from release_build import VERSION
    if not VERSION.fullmatch(version):
        raise ValueError('Invalid release version')
    with tempfile.TemporaryDirectory(prefix='ultrazohm-pypi-') as directory:
        root = Path(directory)
        for package in ('ultrazohm-cli', 'ultrazohm-dataviewer'):
            venv = root / package
            subprocess.run(['uv', 'venv', '--python', '3.12', str(venv)], check=True)
            scripts = venv / ('Scripts' if os.name == 'nt' else 'bin')
            python = scripts / ('python.exe' if os.name == 'nt' else 'python')
            command = ['uv', 'pip', 'install', '--python', str(python), '--index-url',
                       'https://pypi.org/simple', '--only-binary', ':all:', '--refresh', f'{package}=={version}']
            for attempt in range(12):
                result = subprocess.run(command, cwd=root, check=False)
                if result.returncode == 0:
                    break
                if attempt == 11:
                    result.check_returncode()
                time.sleep(10)
            subprocess.run(['uv', 'pip', 'check', '--python', str(python)], check=True)
            names = ['ultrazohm-cli'] + (['ultrazohm-dataviewer'] if package.endswith('dataviewer') else [])
            for name in names:
                exe = scripts / (name + ('.exe' if os.name == 'nt' else ''))
                reported = subprocess.check_output([str(exe), '--version'], cwd=root, text=True)
                if version not in reported.split():
                    raise RuntimeError(f'{name} reports {reported!r}, expected {version}')
            code = ('import importlib.metadata as m; from ultrazohm_cli import Acquisition, Client; '
                    f'assert m.version("ultrazohm-cli") == {version!r}; ')
            if package.endswith('dataviewer'):
                code += (f'from ultrazohm_dataviewer import Client, __version__; assert __version__ == {version!r}')
            else:
                code += 'assert not any(d.metadata["Name"] == "imgui-bundle" for d in m.distributions())'
            subprocess.run([str(python), '-c', code], cwd=root, check=True)
    print(f'PyPI release {version}: both clean installations verified.')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('version')
    verify(parser.parse_args().version)
