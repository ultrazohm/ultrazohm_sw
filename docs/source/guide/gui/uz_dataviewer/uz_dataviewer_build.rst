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
   # -> dist\uz_dataviewer.exe



GitHub binary releases
======================

``.github/workflows/uz_dataviewer.yml`` tests and builds Linux and Windows binaries when viewer files, the workflow, or the command reference change.
Pull requests run validation without publishing releases.
Pushes to ``main`` publish a release after both builds succeed.
Temporarily, pushes to ``feature/uz_dataviewer_revision`` also publish, marked as prereleases for testing.
Remove that branch exception from the release job after testing.
Manual workflow runs follow the same branch restrictions.
Each release uses a unique ``uz-dataviewer-build-<run-id>`` tag and includes two archives and SHA-256 checksums.
Viewer releases do not replace the repository's latest release designation.
Build artifacts are retained for 30 days; published release downloads remain available independently.
The existing documentation Pages workflow is unchanged.

Linux binaries are built on Debian 12 and require x86_64, glibc 2.36 or newer, and desktop graphics libraries on the target system.
Windows binaries target x86_64 and must be extracted from the ZIP before launching.
Each build runs a headless smoke test of the frozen executable, checking native imports, Parquet reading, and lazy downsampling.
This check does not verify window creation or graphics drivers on the user's desktop.
To repeat it locally after building, run ``python build/smoke_binary.py dist/uz_dataviewer`` (use ``dist/uz_dataviewer.exe`` on Windows).

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

