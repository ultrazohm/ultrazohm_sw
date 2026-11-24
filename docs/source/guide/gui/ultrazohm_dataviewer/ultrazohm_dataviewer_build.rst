.. _ultrazohm_dataviewer_build:

=====
Build
=====

Tasks
=====

Builds and tests run through ``ultrazohm_dataviewer/tasks.py`` (and ``ultrazohm_cli/tasks.py`` for the ultrazohm-cli).
The scripts use only the Python standard library and behave the same on Linux, on Windows and in CI.
The root launcher installs missing uv and the Python version pinned in ``.python-version``; the task implementation installs dependencies from ``uv.lock``.
From the repository root:

.. code-block:: bash

   ./uz_developer check dataviewer        # lint, format check, and tests
   ./uz_developer task dataviewer wheel   # Python wheel

On Windows, use ``.\uz_developer.ps1`` with the same arguments.
Build and test the Windows bundle in PowerShell.

.. code-block:: powershell

   .\uz_developer.ps1 build windows_bundle
   .\uz_developer.ps1 task dataviewer bundle-smoke

``build linux_wheels`` builds CI-format CLI and DataViewer wheels and installs both into the persistent development environment.
``build cli`` and ``build dataviewer`` also refresh the matching pair.
``build windows_bundle`` performs this installation and creates the Windows desktop distribution.
Use ``./uz_developer shell`` or ``./uz venv dev`` to activate the existing environment without rebuilding.
Rebuild after source changes and restart running applications.

``check linux_wheels`` validates the built pair, including Rust, Python and GUI smoke checks.
The shared container supplies the virtual display; the GUI task starts it automatically when no display is available.
Checks use temporary environments, cleaned up on completion.
Low-level ``task dataviewer check`` and ``task dataviewer bundle`` accept ``--cli-wheel PATH`` and ``--dataviewer-wheel PATH`` for CI artifact testing.
The repository ``.venv`` is not used.

Native standalone executables (PyInstaller)
===========================================

The bundle collects ``imgui_bundle``, ``pyarrow``, the Polars runtime and the ultrazohm-cli into a self-contained directory containing the executable and ``_internal``.
Extract the entire archive and keep ``_internal`` beside the executable.
The distributed executable does not require Python or uv on the target machine.
PyInstaller builds the Windows bundle on Windows.
Linux installations use Python wheels.

The frozen smoke test checks native imports, Parquet reading with both backends in memory and lazy modes, downsampling and plot input; the live smoke test starts the bundled ultrazohm-cli workers against the simulator.
CI also checks GUI startup on Linux and Windows using a headless display.

Releases
========

``.github/workflows/uz_cli.yml`` checks the ultrazohm-cli, builds its wheels, tests the DataViewer against them and builds the Windows desktop bundle.
Each run computes one version: ``MAJOR.MINOR`` from ``ultrazohm_cli/pyproject.toml`` plus the workflow run number, with ``.dev0`` outside ``main``.
The wheels are stamped and built once; the tests and Windows DataViewer bundle use exactly those wheels, so ``ultrazohm-cli --version`` and ``run.json`` identify the build.
Pull requests and other branches validate and keep the archives as workflow artifacts for 30 days.

Pushes to ``main`` (stable) and ``develop`` (prereleases) publish.
Manual dispatch can publish a prerelease from ``develop`` or ``feature/uz_cli_dataviewer_testing`` when ``publish_prerelease`` is selected.
Publication produces:

- one GitHub release ``ultrazohm-v<version>`` with three wheels, two Windows ZIPs and ``SHA256SUMS``; it never replaces the repository's latest release designation;
- the wheels on PyPI as ``ultrazohm-cli`` and ``ultrazohm-dataviewer`` through trusted publishing.

Linux users install the published Python wheels with uv or pip.
Windows ZIPs provide ultrazohm-cli alone or DataViewer bundled with ultrazohm-cli, without requiring an installed Python.
The DataViewer ZIP contains one GUI executable and a PowerShell wrapper for terminal commands.


Workspace data and process ownership
------------------------------------

Both the source launcher and the bundle store DataViewer-owned data in ``<workspace>/artifacts/_user``, so they share preferences, layout, caches and recordings for the same checkout.
Until a workspace is known, the DataViewer uses a per-user folder (``%LOCALAPPDATA%\UltraZohm\ultrazohm_dataviewer`` on Windows, ``~/.local/share/ultrazohm/ultrazohm_dataviewer`` on Linux), never its working directory.
The standalone executable and ``_internal`` contain application resources; they are not the destination for mutable workspace preferences.

``settings.json`` contains runtime preferences.
Missing preferences are seeded from the ultrazohm-cli's bundled standard profile, restricted to the selected firmware's available observables.
Existing preferences are preserved.
Connect passes saved preferences to the ultrazohm-cli, which rejects unavailable explicit channel assignments.
Flash is an ultrazohm-cli-owned firmware job.
It captures and validates headers, preserves compatible assignments, and replaces the acquisition session without rewriting saved startup preferences.

``tools.json`` remembers the selected XSCT launcher.
The ultrazohm-cli resolves XSCT from an explicit ultrazohm-cli process option, then saved tools.json, then PATH.
Saving a launcher does not modify PATH; an attached DataViewer uses the tools on the machine running ultrazohm-cli.
``viewer.ini`` holds the window layout, ``viewer_cache`` holds optional analysis caches (unless overridden by ``UZ_DATAVIEWER_CACHE``), and ``logs`` holds default session output.
Explicit export, script, session and recording destinations remain user-selected.
Script and ultrazohm-cli output capture also uses temporary directories.

The live controller tracks its launched ultrazohm-cli process separately from the ultrazohm-cli process to which it is currently attached.
Closing the DataViewer shuts down its owned ultrazohm-cli process, which sends device Stop and finalizes recordings; the window waits up to ten seconds, after which the detached ultrazohm-cli process completes finalization in the background (see its ``service.log`` and the ``end`` section of ``run.json``).
For an attached external ultrazohm-cli process it sends device Stop without shutting that ultrazohm-cli process down.
Script Stop invalidates queued manual commands and uses a control path independent of display reads.
Flashing sends device Stop and finalizes recordings, then builds/programs and replaces the acquisition session.
The ultrazohm-cli process endpoint stays available.
Clients refresh catalogs and discard old cursors when session identity changes.
Logging restarts idle.

Standalone execution uses its bundled worker entry point and requires no separately installed Python or Rust.
The application log and Python editor are available on Windows and Linux.
External Python scripts use the installed ``ultrazohm_dataviewer.Client``; the bundled Python editor uses the executable's internal script worker.
