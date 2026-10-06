.. _uz_scope_build:

===============
Build uz_scope
===============

Development install
===================

From the repository root::

   pip install -e ./uz_dataviewer -e ./uz_scope
   python -m pytest uz_scope/tests
   python uz_scope/run.py

``run.py`` also works without installing (it adds both ``src`` trees to the path).

Standalone executable
=====================

A self-contained native binary (no Python required on the target machine)::

   cd uz_scope
   ./build/build_native.sh        # Linux/macOS
   # output: uz_scope/dist/uz_scope

The PyInstaller spec (``build/uz_scope.spec``) bundles ``imgui_bundle``'s compiled extensions and assets, ``pyarrow``'s native libraries and the ``uz_dataviewer`` package the scope imports.

Benchmarks
==========

``uz_scope/tools`` contains the performance harness (not part of CI):

- ``bench_server.py`` — non-lock-step firehose emulating the APU at a configurable geometry/rate, with a counter channel for loss detection.
- ``bench_client.py`` — soak client running the full ingest path; exits non-zero if the rate is not sustained or any sample went missing.
- ``bench_parse.py`` — offline parse+ring micro-benchmark.

Continuous integration
======================

``bitbucket-pipelines.yml`` runs ``pytest`` on the ``uz_scope`` test suite whenever ``uz_scope/`` or ``uz_dataviewer/`` change.
