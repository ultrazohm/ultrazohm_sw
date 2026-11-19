"""Package the two Windows application selections from tested build artifacts."""
import argparse
from pathlib import Path
import shutil
import tempfile
import zipfile


def archive(source, destination):
    with zipfile.ZipFile(destination, 'w', zipfile.ZIP_DEFLATED) as output:
        for path in sorted(source.rglob('*')):
            if path.is_file():
                output.write(path, path.relative_to(source.parent))


def package(version, cli, viewer, output):
    from release_build import VERSION
    if not VERSION.fullmatch(version):
        raise ValueError('Invalid release version')
    cli, viewer, output = Path(cli), Path(viewer), Path(output)
    for path in (cli, viewer / 'ultrazohm-dataviewer.exe', viewer / 'ultrazohm-dataviewer.ps1'):
        if not path.is_file():
            raise FileNotFoundError(path)
    output.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='ultrazohm-windows-') as directory:
        cli_dir = Path(directory) / 'ultrazohm-cli'
        cli_dir.mkdir()
        shutil.copy2(cli, cli_dir / 'ultrazohm-cli.exe')
        archive(cli_dir, output / f'ultrazohm-cli-{version}-windows-x86_64.zip')
        viewer_dir = Path(directory) / 'ultrazohm-dataviewer'
        shutil.copytree(viewer, viewer_dir)
        shutil.copy2(cli, viewer_dir / 'ultrazohm-cli.exe')
        archive(viewer_dir, output / f'ultrazohm-dataviewer-{version}-windows-x86_64.zip')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('version', 'cli', 'viewer', 'output'):
        parser.add_argument('--' + name, required=True)
    package(**vars(parser.parse_args()))
