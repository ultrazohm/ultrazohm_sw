"""Application-level Python editor with explicit optional device supervision."""

import shlex
import sys
from pathlib import Path

from imgui_bundle import imgui

from ..scripting import ScriptRunner
from .script_editor import ScriptEditor


class PythonPanel:
    def __init__(self, app):
        self.app = app
        self.runner = ScriptRunner(device_control=False)
        self.managed_device = False
        self.arguments = ""
        self.working_directory = str(Path.cwd())
        self.document = ScriptEditor(self.busy, self.execution_target, self.start)

    def endpoint(self):
        server = self.app.control_server
        return server.endpoint if server is not None else ""

    def busy(self):
        return self.runner.busy or bool(self.app.live and self.app.live.scripts.busy)

    def execution_target(self):
        acquisition = self.app.live.controller.endpoint if self.app.live else None
        return self.endpoint(), acquisition, self.managed_device

    def start(self, path, endpoint):
        try:
            if self.busy():
                raise RuntimeError("A Python script is already running")
            target = (
                endpoint
                if isinstance(endpoint, tuple)
                else (endpoint, *self.execution_target()[1:])
            )
            if target != self.execution_target():
                raise RuntimeError(
                    "Script endpoint changed or run mode changed; run the script again"
                )
            endpoint, acquisition, _ = target
            options = dict(args=shlex.split(self.arguments), cwd=self.working_directory)
            if self.managed_device:
                if self.app.live is None:
                    raise RuntimeError("Live acquisition is unavailable")
                self.app.live._start_script(
                    path,
                    self.app.live.controller.endpoint,
                    viewer_endpoint=endpoint,
                    **options,
                )
            else:
                self.runner.start(
                    path, endpoint=acquisition, viewer_endpoint=endpoint, **options
                )
        except Exception as exc:
            self.document.error = str(exc)

    def poll(self):
        self.runner.poll()
        self.document.poll()

    def stop_owned(self):
        """Stop only processes started by this application, with their run policy."""
        if self.runner.busy:
            self.runner.stop()
        if self.app.live and self.app.live.scripts.busy:
            self.app.live.send("stop")

    def render(self):
        imgui.begin_disabled(self.busy() or self.document.dialog is not None)
        _, self.managed_device = imgui.checkbox(
            "Managed device run", self.managed_device
        )
        _, self.arguments = imgui.input_text("Arguments", self.arguments)
        _, self.working_directory = imgui.input_text(
            "Working directory", self.working_directory
        )
        imgui.text_wrapped(
            "Quote arguments containing spaces. Use forward slashes in Windows paths."
        )
        imgui.end_disabled()
        imgui.text_wrapped(f"Python: {sys.executable}")
        imgui.text_wrapped(f"Viewer: {self.endpoint()}")
        live = self.app.live
        allowed = bool(self.endpoint())
        if self.managed_device:
            allowed = bool(
                allowed
                and live
                and live.update.attached
                and live.update.status.get("state", {}).get("connected")
                and not live.block_reason("script")
            )
        self.document.render(allowed)
        runner = live.scripts if self.managed_device and live else self.runner
        imgui.begin_disabled(not runner.busy)
        if imgui.button(
            "Stop script + device" if self.managed_device else "Stop script"
        ):
            if self.managed_device:
                live.send("stop")
            else:
                runner.stop()
        imgui.end_disabled()
        imgui.text_wrapped(runner.message)
        if self.document.error:
            imgui.text_wrapped(self.document.error)
        imgui.separator()
        imgui.text_unformatted(runner.output)

    def close(self):
        self.document.close()
        self.runner.close()
