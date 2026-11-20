.. _ultrazohm_dataviewer_build:

=====
Build
=====

Tasks
=====

Builds and tests run through ``ultrazohm_dataviewer/tasks.py`` (and ``ultrazohm_cli/tasks.py`` for the CLI).
The scripts use only the Python standard library and behave the same on Linux, on Windows and in CI.
The root launcher installs missing uv and the Python version pinned in ``.python-version``; the task implementation installs dependencies from ``uv.lock``.
From the repository root:

.. code-block:: bash

   ./uz check viewer        # lint, format check, and tests
   ./uz task viewer wheel   # Python wheel

On Windows, use ``.\uz.ps1`` with the same arguments.
Build and test the Windows bundle in PowerShell.

.. code-block:: powershell

   .\uz.ps1 build viewer
   .\uz.ps1 task viewer bundle-smoke

``check viewer`` and ``build viewer`` build a matching CLI wheel from ``ultrazohm_cli`` unless ``--cli-wheel PATH`` names one.
Tests use ``ultrazohm_dataviewer/.venv-ci`` and bundles use ``ultrazohm_dataviewer/.venv-build``.
The root ``.venv`` is shared by both applications.

Native standalone executables (PyInstaller)
============================================

The bundle collects ``imgui_bundle``, ``pyarrow``, the Polars runtime and the CLI into a self-contained directory containing the executable and ``_internal``.
Extract the entire archive and keep ``_internal`` beside the executable.
The distributed executable does not require Python or uv on the target machine.
PyInstaller builds the Windows bundle on Windows.
Linux installations use Python wheels.

The frozen smoke test checks native imports, Parquet reading with both backends in memory and lazy modes, downsampling and plot input; the live smoke test starts the bundled CLI workers against the simulator.
CI also checks GUI startup on Linux and Windows using a headless display.

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

Linux users install the published Python wheels with uv or pip.
Windows ZIPs provide CLI-only and viewer-plus-CLI applications without an installed Python.
The viewer ZIP contains one GUI executable and a PowerShell wrapper for terminal commands.


Workspace data and process ownership
------------------------------------

Both the source launcher and the bundle store viewer-owned data in ``<workspace>/artifacts/_user``, so they share preferences, layout, caches and recordings for the same checkout.
Until a workspace is known, the viewer uses a per-user folder (``%LOCALAPPDATA%\UltraZohm\ultrazohm_dataviewer`` on Windows, ``~/.local/share/ultrazohm/ultrazohm_dataviewer`` on Linux), never its working directory.
The standalone executable and ``_internal`` contain application resources; they are not the destination for mutable workspace preferences.

``settings.json`` contains runtime preferences.
Missing preferences are seeded from the CLI's bundled standard profile, restricted to the selected firmware's available observables.
Existing preferences are preserved.
Connect passes saved preferences to the CLI, which rejects unavailable explicit channel assignments.
Flash generates a mapping snapshot and a separate session profile that drops unavailable assignments without rewriting saved preferences.

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

Standalone execution uses its bundled worker entry point and requires no separately installed Python or Rust.
The application log and Python editor are available on Windows and Linux.
External Python scripts use the installed ``ultrazohm_dataviewer.Client``; the bundled Python editor uses the executable's internal script worker.
