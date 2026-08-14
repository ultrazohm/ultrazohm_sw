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

The build collects ``imgui_bundle`` and ``pyarrow`` (which carry native libraries) into one self-contained binary.
Both native builds wrap ``pyinstaller build/uz_dataviewer.spec``.
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

   ``uz_dataviewer`` can not be run by opening ``index.html`` directly from disk (``file://``) because the browser blocks Pyodide's package downloads from a ``file://`` origin. Use any static server, e.g., ``python -m http.server``. ``uz_dataviewer`` requires internet access at runtime.

.. note::

   ``uz_dataviewer`` is not fully identical in the web-version to the native version. See :doc:`uz_dataviewer_native_vs_web` for details.

