"""Generate ``client_methods.py`` from the command specifications.

Usage: ``python tools/generate_client.py [--check]``. ``--check`` fails if the
committed file differs (ignoring formatting) from the generated code.
"""

import ast
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "src" / "ultrazohm_dataviewer" / "client_methods.py"
TYPES = {
    "int": "int",
    "float": "float",
    "bool": "bool",
    "str": "str",
    "plot": "int",
    "run": "RunHandle",
    "node": "NodeHandle",
    "fwindow": "str | int",
    "weights": "list[float]",
}
HEADER = '''"""Python control methods, generated from the command specifications.

Do not edit: run ``uz_developer dataviewer generate`` after changing
``commands.py``.
"""

from __future__ import annotations

from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .client import NodeHandle, RunHandle, ViewHandle


class ViewerMethods:
'''


def render():
    sys.path.insert(0, str(ROOT / "src"))
    from ultrazohm_dataviewer.commands import PUBLIC_COMMANDS, CommandRegistry

    registry = CommandRegistry()
    methods = []
    for name in sorted(PUBLIC_COMMANDS):
        command = registry.get(name)
        if command is None:
            raise SystemExit(f"Public command {name} is not registered")
        arguments, values = ["self"], []
        for param in command.params:
            annotation = TYPES[param.kind]
            if param.optional:
                arguments.append(f"{param.name}: {annotation} | None = None")
            else:
                arguments.append(f"{param.name}: {annotation}")
            values.append(f'"{param.name}": {param.name}')
        # Plot commands address one plot window; the main grid by default.
        if any(p.kind == "plot" for p in command.params) or name == "set_max_points":
            arguments += ["*", "view: ViewHandle | None = None"]
            values.append('"view": view')
        methods.append(
            f"    def {name}({', '.join(arguments)}):\n"
            f"        {command.help!r}\n"
            f'        return self._invoke("{name}", {{{", ".join(values)}}})\n'
        )
    return HEADER + "\n".join(methods)


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    code = render()
    if "--check" in argv:
        current = TARGET.read_text(encoding="utf-8")
        if ast.dump(ast.parse(current)) != ast.dump(ast.parse(code)):
            raise SystemExit(
                f"{TARGET.name} is out of date; run uz_developer dataviewer generate"
            )
        return
    TARGET.write_text(code, encoding="utf-8")


if __name__ == "__main__":
    main()
