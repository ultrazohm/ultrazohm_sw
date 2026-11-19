.. _ultrazohm_dataviewer_build:

=====
Build
=====

``ultrazohm_dataviewer`` is a Python ``imgui_bundle`` application.
``imgui_bundle`` ships prebuilt native binaries (Dear ImGui, ImPlot, hello_imgui) for Windows and Linux, so the same source runs on both.
In the following, the build process of ``ultrazohm_dataviewer`` is described.
Usage of the :ref:`vscode_remote_container` is assumed.

Tasks
=====

Builds and tests run through ``ultrazohm_dataviewer/tasks.py`` (and ``ultrazohm_cli/tasks.py`` for the CLI).
The scripts use only the Python standard library and behave the same on Linux, on Windows and in CI.
The root launcher installs missing uv and the Python version pinned in ``.python-version``; the task implementation installs dependencies from ``uv.lock``.
From the repository root:

.. code-block:: bash

   ./uz check viewer                  # ruff and the full pytest suite
   ./uz task viewer wheel           # publishable viewer wheel
   .\uz.ps1 build viewer           # Windows standalone bundle
   .\uz.ps1 task viewer bundle-smoke  # Windows bundle and live workers

``check viewer`` and ``build viewer`` build a matching CLI wheel from ``ultrazohm_cli`` unless ``--cli-wheel PATH`` names one.
Tests use ``ultrazohm_dataviewer/.venv-ci`` and bundles ``ultrazohm_dataviewer/.venv-build``; the root ``.venv`` is shared by both applications.
On Windows, use ``.\uz.ps1`` with the same arguments.

Native standalone executables (PyInstaller)
============================================

The bundle collects ``imgui_bundle``, ``pyarrow``, the Polars runtime and the CLI into a self-contained directory containing the executable and ``_internal``.
Extract the entire archive and keep ``_internal`` beside the executable.
The distributed executable does not require Python or uv on the target machine.
PyInstaller builds the Windows bundle on Windows. Linux installations use Python wheels.

The frozen smoke test checks native imports, Parquet reading with both backends in memory and lazy modes, downsampling and plot input; the live smoke test starts the bundled CLI workers against the simulator.
These checks do not verify window creation or graphics drivers on the user's desktop.

Releases
========

``.github/workflows/uz_cli.yml`` checks the CLI, builds its wheels, tests the viewer against them and builds the Windows desktop bundle.
Each run computes one version: ``MAJOR.MINOR`` from ``ultrazohm_cli/pyproject.toml`` plus the workflow run number, with ``.dev0`` outside ``main``.
The wheels are stamped and built once; the tests and Windows viewer bundle use exactly those wheels, so ``ultrazohm-cli --version`` and ``run.json`` identify the build.
Pull requests and other branches validate and keep the archives as workflow artifacts for 30 days.

Pushes to ``main`` (stable), ``develop`` and ``feature/uz_cli_dataviewer_testing`` (prereleases) publish:

- one GitHub release ``ultrazohm-v<version>`` with three wheels, two Windows ZIPs and ``SHA256SUMS``;
  it never replaces the repository's latest release designation;
- the wheels on PyPI as ``ultrazohm-cli`` and ``ultrazohm-dataviewer`` through trusted publishing.

Linux users install the published Python wheels with uv or pip. No standalone Linux archive is built.
Windows ZIPs provide CLI-only and viewer-plus-CLI applications without an installed Python.
The viewer ZIP contains one GUI executable and a PowerShell wrapper for terminal commands.


Combined desktop packaging
==========================

Select the ``ultrazohm_sw`` root at startup, or supply ``--live-repo``.
All windows except Python start open, with Analysis tabs selected.
Mode switches select Analysis or Live tabs once without closing other windows.
The live panels appear whenever the ``ultrazohm_cli`` package is installed: always in the bundle, and on Windows and Linux x86-64 in the source environment, where it is a locked dependency.
``./uz setup local`` builds the checkout's CLI and uses it instead.
Both deployments use the same subprocess worker code; bundled scripts can import bundled dependencies, while source scripts can also use packages installed in the developer environment.
Vitis is external and remains required for build/flash.

Workspace data and process ownership
------------------------------------

Both the source launcher and the bundle store viewer-owned data in ``<workspace>/artifacts/_user``, so they share preferences, layout, caches and recordings for the same checkout.
Until a workspace is known, the viewer uses a per-user folder (``%LOCALAPPDATA%\UltraZohm\ultrazohm_dataviewer`` on Windows, ``~/.local/share/ultrazohm/ultrazohm_dataviewer`` on Linux), never its working directory.
The standalone executable and ``_internal`` contain application resources; they are not the destination for mutable workspace preferences.

``settings.json`` contains runtime preferences.
Missing preferences are seeded from the CLI's bundled standard profile, restricted to the selected firmware's available observables.
Existing preferences are preserved.
Connecting or flashing prepares an effective session profile when assignments need filtering; it does not rewrite the saved preferences.
Header-generated mapping JSON is derived data and is regenerated for the selected firmware checkout.

``tools.json`` remembers the selected XSCT launcher.
Its directory is added to the application's process environment for child processes, without changing the system PATH.
``viewer.ini`` holds the window layout, ``viewer_cache`` holds optional analysis caches (unless overridden by ``UZ_DATAVIEWER_CACHE``), and ``logs`` holds default session output.
Explicit export, script, session and recording destinations remain user-selected.
Script and CLI output capture also uses temporary directories.

The live controller tracks its launched service separately from the service to which it is currently attached.
Closing the viewer shuts down its owned service, which sends device Stop and finalizes recordings; the window waits up to ten seconds, after which the detached service completes finalization in the background (see its ``service.log`` and the ``end`` section of ``run.json``).
For an attached external service it sends device Stop without shutting that service down.
Script Stop invalidates queued manual commands and uses a control path independent of display reads.
Flashing shuts the service down (which sends device Stop and finalizes recordings), then programs and reconnects.

The root ``uz`` and ``uz.ps1`` launchers bootstrap uv and pinned Python.
``setup`` installs the selected applications into the shared repository ``.venv``; ``shell`` opens an activated terminal.
Choose ``--app cli`` or ``--app viewer`` and the ``stable``, ``prerelease`` or ``local`` source.
The default is the published stable viewer and CLI; explicit setup recreates the managed environment.
``build viewer``, ``check viewer`` and ``task viewer bundle-smoke`` expose the build and test workflow.
Standalone execution uses its bundled worker entry point and requires no separately installed Python or Rust.
The application log and Python editor are available on Windows and Linux.
External Python scripts use the installed ``ultrazohm_dataviewer.Client``; the bundled Python editor uses the executable's internal script worker.
