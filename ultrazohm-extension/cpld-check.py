"""Check the published CPLD package using the extension's private runtime."""
import argparse
import subprocess
import sys


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--uv', required=True)
    parser.add_argument('--channel', choices=['stable', 'prerelease'], required=True)
    args = parser.parse_args()
    selection = [args.uv, 'tool', 'run', '--isolated', '--python', '3.12',
                 '--prerelease', 'allow' if args.channel == 'prerelease' else 'disallow',
                 'ultrazohm-cpld-user']
    result = 0
    for command in [['doctor'], ['programmer_gui', '--check']]:
        print('+ ultrazohm-cpld-user ' + ' '.join(command), flush=True)
        code = subprocess.run([*selection, *command]).returncode
        result = result or code
    return result


if __name__ == '__main__':
    sys.exit(main())
