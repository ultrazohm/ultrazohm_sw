"""Fail early when the selected backend lacks the live-viewer API. No device IO."""
import sys


def main():
    try:
        from ultrazohm import Client
    except ImportError as exc:
        print(f'Cannot load the live backend: {exc}', file=sys.stderr)
        return 1
    if not all(callable(getattr(Client, name, None)) for name in ('catalog', 'read_since')):
        print('The selected CLI wheel lacks live-viewer APIs. Use a current branch wheel '
              'with --live-wheel or a compatible release via --live-channel testing.', file=sys.stderr)
        return 1
    print('Live backend ready.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
