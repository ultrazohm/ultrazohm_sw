"""Launch the GUI or control an existing viewer without importing GUI modules."""
import argparse
from dataclasses import asdict, is_dataclass
import inspect
import json
import os
import sys

from .client import Client, RunHandle, NodeHandle, ViewHandle, ViewerError
from .control_protocol import DEFAULT_ENDPOINT


def public_methods():
    return {name: method for name, method in inspect.getmembers(Client, inspect.isfunction)
            if not name.startswith('_') and name != 'close'}


def parameter_kind(parameter):
    annotation = parameter.annotation
    if annotation is inspect.Parameter.empty:
        return 'str'
    if isinstance(annotation, type):
        return annotation.__name__
    return str(annotation).split(' | ')[0].replace('uz_dataviewer.client.', '')


def parser():
    root = argparse.ArgumentParser(prog='uz-dataviewer', description=__doc__)
    root.add_argument('--endpoint', default=os.environ.get('UZ_DATAVIEWER_ENDPOINT', DEFAULT_ENDPOINT))
    root.add_argument('--timeout', type=float, default=120, help='Control request timeout in seconds')
    root.add_argument('--json', action='store_true', help='Print compact JSON results')
    commands = root.add_subparsers(dest='operation')
    gui = commands.add_parser('gui', help='Open a viewer and its local control endpoint')
    gui.add_argument('--endpoint', default=argparse.SUPPRESS, help='Local viewer control endpoint')
    gui.add_argument('files', nargs='*')
    gui.add_argument('--backend', choices=('pyarrow', 'polars'))
    gui.add_argument('--loading-mode', choices=('memory', 'lazy'))
    gui.add_argument('--disk-cache', action='store_true')
    gui.add_argument('--live-repo')
    for name, method in public_methods().items():
        command = commands.add_parser(name.replace('_', '-'), help=method.__doc__)
        for parameter in list(inspect.signature(method).parameters.values())[1:]:
            kind = parameter_kind(parameter)
            options = {'type': {'int': int, 'float': float, 'RunHandle': int,
                                'NodeHandle': int, 'ViewHandle': int}.get(kind, str)}
            if kind == 'bool':
                options['choices'] = ('true', 'false')
            if parameter.default is not inspect.Parameter.empty:
                options.update(nargs='?', default=parameter.default)
            if parameter.kind is inspect.Parameter.KEYWORD_ONLY:
                options.pop('nargs', None)
                command.add_argument('--' + parameter.name, **options)
            else:
                command.add_argument(parameter.name, **options)
    return root


def main(argv=None):
    args = parser().parse_args(argv)
    if args.operation in (None, 'gui'):
        from .app import main as gui_main
        options = ['--endpoint', args.endpoint]
        for name in ('backend', 'loading_mode', 'live_repo'):
            if value := getattr(args, name, None):
                options.extend(['--' + name.replace('_', '-'), value])
        if getattr(args, 'disk_cache', False):
            options.append('--disk-cache')
        return gui_main([*options, *getattr(args, 'files', [])])
    try:
        with Client(args.endpoint, timeout=args.timeout) as client:
            name = args.operation.replace('-', '_')
            method = public_methods()[name]
            arguments = {}
            for parameter in list(inspect.signature(method).parameters.values())[1:]:
                value = getattr(args, parameter.name)
                kind = parameter_kind(parameter)
                if value is not None and kind in ('RunHandle', 'NodeHandle', 'ViewHandle'):
                    if client.session is None:
                        client.status()
                    value = {'RunHandle': RunHandle, 'NodeHandle': NodeHandle, 'ViewHandle': ViewHandle}[kind](client.session, value)
                elif value is not None and kind == 'bool':
                    value = value == 'true'
                arguments[parameter.name] = value
            result = getattr(client, name)(**arguments)
        if is_dataclass(result):
            result = asdict(result)
        print(json.dumps(result, allow_nan=False, indent=None if args.json else 2))
        return 0
    except (ViewerError, OSError, EOFError, ValueError) as exc:
        if args.json:
            print(json.dumps(dict(error=dict(code=getattr(exc, 'code', 'client_error'), message=str(exc)))),
                  file=sys.stderr)
        else:
            print(f'Viewer command failed: {exc}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
