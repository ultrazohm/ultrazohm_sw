.. _uz_dataviewer_build:

=====
Build
=====

``uz_dataviewer`` is a Python ``imgui_bundle`` application.
``imgui_bundle`` ships prebuilt native binaries (Dear ImGui, ImPlot, hello_imgui) for Windows, and Linux so the same source runs on all desktop platforms, and can also be executed in the browser via Pyodide.
In the following, the build process of ``uz_dataviewer`` is described.
Usage of the :ref:`vscode_remote_container` is assumed.

Native single-file executables (PyInstaller)
============================================

The build collects ``imgui_bundle``, ``pyarrow``, and the Polars Rust runtime into one self-contained binary.
The frozen smoke test exercises both backends in memory and lazy modes.
Install ``uv`` before invoking either build script.
Both scripts install Python 3.12 and the dependencies from ``uv.lock`` into ``.venv-build``, then invoke PyInstaller.
An existing Python 3.12 installation is reused when available.
The initial build requires internet access to download missing dependencies.
The distributed executable does not require Python or uv on the target machine.
Cross-compiling is not supported by PyInstaller.
Build each OS's binary on that OS.

Linux / Ubuntu
--------------

.. code-block:: bash

   ./build/build_native.sh # from ultrazohm_sw/uz_dataviewer
   # -> dist/uz_dataviewer

Windows (PowerShell)
--------------------

.. code-block:: powershell

   .\build\build_native.ps1 # from ultrazohm_sw/uz_dataviewer
   # -> dist\uz_dataviewer\uz_dataviewer.exe



GitHub binary releases
======================

``.github/workflows/uz_dataviewer.yml`` tests and builds Linux and Windows binaries when viewer files, the workflow, or the command reference change.
Pull requests run validation without publishing releases.
Pushes to ``main`` publish a release after both native builds and the browser smoke test succeed.
Manual workflow runs follow the same branch restrictions.
Each release uses a unique ``uz-dataviewer-build-<run-id>`` tag and includes two archives and SHA-256 checksums.
Viewer releases do not replace the repository's latest release designation.
Build artifacts are retained for 30 days; published release downloads remain available independently.
The existing documentation Pages workflow is unchanged.

Linux binaries are built on Debian 12 and require x86_64, glibc 2.36 or newer, and desktop graphics libraries on the target system.
Windows binaries target x86_64 and must be extracted from the ZIP before launching.
Each build runs a headless smoke test of the frozen executable, checking native imports, Parquet reading, and lazy downsampling.
This check does not verify window creation or graphics drivers on the user's desktop.
To repeat it locally after building, run ``python build/smoke_binary.py dist/uz_dataviewer/uz_dataviewer`` (use ``dist/uz_dataviewer/uz_dataviewer.exe`` on Windows).

.. _uz_dataviewer_build_web:

Web / WASM (Pyodide)
====================

.. code-block:: bash

   ./build/build_web.sh                      # writes web/index.html (self-contained)
   cd web && python -m http.server 8000      # then open http://localhost:8000/

``build_web.sh`` runs ``build/gen_web.py``, which emits a single self-contained ``web/index.html`` following the official imgui_bundle Pyodide template.
At load time the page:

#. loads Pyodide ``v0.29.4`` from the CDN and wires the WebGL canvas to SDL;
#. ``micropip``-installs the **imgui_bundle WASM wheel** (hosted by pthom at ``https://imgui-bundle.pages.dev/local_wheels/``) plus ``numpy``/``pandas``/``pyarrow`` from the Pyodide package index;
#. writes the embedded ``uz_dataviewer`` sources into the Pyodide FS and starts the app (in Pyodide ``immapp.run()`` is auto-patched to be non-blocking).

.. note::

   ``uz_dataviewer`` can not be run by opening ``index.html`` directly from disk (``file://``) because the browser blocks Pyodide's package downloads from a ``file://`` origin.
   Use any static server, e.g., ``python -m http.server``.
   ``uz_dataviewer`` requires internet access at runtime.

.. note::

   ``uz_dataviewer`` is not fully identical in the web-version to the native version.
   See :doc:`uz_dataviewer_native_vs_web` for details.

Validation and dependency updates
---------------------------------

Native builds require Python 3.12 or newer and use the versions in ``uv.lock``.
The browser embeds the sources and uses its separate Pyodide package index and
ABI-compatible imgui-bundle wheel. When updating that wheel, update both its
filename and SHA-256 in ``build/gen_web.py``; incomplete or mismatched downloads
are rejected before publication.

Run the Python checks from ``uz_dataviewer/``::

   uv sync --locked --extra dev --python 3.12
   uv run --no-sync ruff check src tests build examples
   uv run --no-sync python -m pytest

The browser smoke test uses Playwright and Chromium::

   python build/gen_web.py
   uv venv .venv-web --python 3.12
   uv pip install --python .venv-web/bin/python playwright==1.64.1
   .venv-web/bin/python -m playwright install chromium
   .venv-web/bin/python build/smoke_web.py

Set ``UZ_BROWSER_EXECUTABLE`` to use an existing Chromium/Chrome installation.
CI runs the browser smoke test before publishing native release artifacts.

Combined desktop packaging
==========================

Set ``UZ_CLI_WHEEL`` to the absolute path of a matching CLI wheel before running
native build scripts. The result is a folder distribution: extract the entire
archive and keep ``_internal`` beside the executable. The CLI and Python runtime
are bundled. Windows and Linux releases include matching standalone wheels.
The integration branch publishes prereleases; main publishes stable releases.

Select the ``ultrazohm_sw`` root at startup, or supply ``--live-repo``. Live windows
start hidden and can be opened through View. Source launchers still use
``--use-live`` to install the backend. Both deployments use the same subprocess
worker code; bundled scripts can import bundled dependencies, while source
scripts can also use packages installed in the developer environment. Vitis is
external and remains required for build/flash.
