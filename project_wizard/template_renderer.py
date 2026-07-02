from __future__ import annotations

import re
from pathlib import Path
from typing import Any

from .paths import TEMPLATE_DIR


class SimpleTemplateRenderer:
    def render_file(self, relative_path: str, context: dict[str, Any]) -> str:
        path = (TEMPLATE_DIR / relative_path).resolve()
        if not self._is_relative_to(path, TEMPLATE_DIR.resolve()):
            raise ValueError(f"Template path is outside the template directory: {relative_path}")
        return self.render(path.read_text(encoding="utf-8"), context)

    def render(self, template: str, context: dict[str, Any]) -> str:
        return self._render_block(template, context)

    def _render_block(self, template: str, context: dict[str, Any]) -> str:
        template = self._render_for_blocks(template, context)
        template = self._render_if_blocks(template, context)
        return self._render_variables(template, context)

    def _render_for_blocks(self, template: str, context: dict[str, Any]) -> str:
        pattern = re.compile(r"{%\s*for\s+(\w+)\s+in\s+([\w.]+)\s*%}(.*?){%\s*endfor\s*%}", re.DOTALL)
        while True:
            match = pattern.search(template)
            if not match:
                return template
            item_name, list_name, body = match.groups()
            rendered = []
            for item in self._resolve(list_name, context) or []:
                child_context = dict(context)
                child_context[item_name] = item
                rendered.append(self._render_block(body, child_context))
            template = template[: match.start()] + "".join(rendered) + template[match.end() :]

    def _render_if_blocks(self, template: str, context: dict[str, Any]) -> str:
        pattern = re.compile(
            r"{%\s*if\s+([\w.]+)\s*%}((?:(?!{%\s*if\b|{%\s*endif\s*%}).)*?){%\s*endif\s*%}",
            re.DOTALL,
        )
        while True:
            match = pattern.search(template)
            if not match:
                return template
            name, body = match.groups()
            rendered = self._render_block(body, context) if self._resolve(name, context) else ""
            template = template[: match.start()] + rendered + template[match.end() :]

    def _render_variables(self, template: str, context: dict[str, Any]) -> str:
        pattern = re.compile(r"{{\s*([\w.]+)\s*}}")
        return pattern.sub(lambda match: self._format_value(self._resolve(match.group(1), context)), template)

    def _format_value(self, value: Any) -> str:
        if value is None:
            return ""
        return str(value)

    def _resolve(self, name: str, context: dict[str, Any]) -> Any:
        value: Any = context
        for part in name.split("."):
            if isinstance(value, dict):
                value = value.get(part)
            else:
                value = getattr(value, part, None)
            if value is None:
                return None
        return value

    def _is_relative_to(self, path: Path, parent: Path) -> bool:
        try:
            path.relative_to(parent)
            return True
        except ValueError:
            return False
