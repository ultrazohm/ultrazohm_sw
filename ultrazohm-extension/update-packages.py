"""Refresh the launcher's cached PyPI environments using extension-owned uv/Python."""
import argparse
import subprocess
import sys


def commands(uv, channel, requirements):
    selection = [uv, 'tool', 'run', '--isolated', '--refresh', '--python', '3.12',
                 '--prerelease', 'allow' if channel == 'prerelease' else 'disallow']
    report = 'from importlib.metadata import version; print("; ".join(p+"=="+version(p) for p in ("ultrazohm-cli", "ultrazohm-dataviewer", "matplotlib")))'
    return [
        ('CLI', [*selection, '--from', 'ultrazohm-cli', 'python', '-c',
                 'from importlib.metadata import version; print("ultrazohm-cli=="+version("ultrazohm-cli"))']),
        ('DataViewer', [*selection, '--from', 'ultrazohm-dataviewer', 'python', '-c',
                 'from importlib.metadata import version; print("ultrazohm-dataviewer=="+version("ultrazohm-dataviewer")+"; ultrazohm-cli=="+version("ultrazohm-cli"))']),
        ('Python environment', [*selection, '--with-requirements', requirements,
                 '--from', 'ultrazohm-dataviewer', 'python', '-c', report]),
    ]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--uv', required=True)
    parser.add_argument('--channel', choices=['stable', 'prerelease'], required=True)
    parser.add_argument('--requirements', required=True)
    args = parser.parse_args()
    for label, command in commands(args.uv, args.channel, args.requirements):
        print(f'Updating {label} ({args.channel})...', flush=True)
        try:
            subprocess.run(command, check=True)
        except subprocess.CalledProcessError as error:
            print(f'{label} update failed. Earlier steps may have completed; resolve the error and retry.', file=sys.stderr)
            return error.returncode or 1
    print('Python packages updated. Subsequent launches use these cached environments.', flush=True)
    return 0


if __name__ == '__main__':
    sys.exit(main())
