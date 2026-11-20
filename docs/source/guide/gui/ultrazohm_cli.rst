UltraZohm CLI
=============

Use ``ultrazohm-cli`` to acquire live data, record measurements, and send commands to an UltraZohm.
Install the published CLI with ``uv tool install ultrazohm-cli``, or extract the standalone Windows ZIP from a release.
To try this checkout, run ``./uz shell local --app cli`` on Linux or ``.\uz.ps1 shell local --app cli`` on Windows.

Run ``ultrazohm-cli`` from the firmware checkout to open a disconnected prompt.
From another directory, use ``ultrazohm-cli serve --interactive --repo PATH`` to select the matching firmware checkout.
At the prompt, enter ``connect`` (or ``connect IP PORT``), then ``status`` and ``start-logging``.
Parquet is the default recording format.
Add ``--format csv`` to the ``serve`` command to export CSV as well.
Use ``stop-logging`` to finalize the recording and ``shutdown`` to stop the service.

Run ``ultrazohm-cli serve --repo PATH --device IP:PORT`` for a headless service.
Send commands such as ``ultrazohm-cli status`` from another terminal.
For Python automation, install ``ultrazohm-cli`` in the script's environment.
Import ``Client`` from ``ultrazohm_cli`` to control a running service or ``Acquisition`` to own one.
For graphical operation, see :doc:`ultrazohm_dataviewer/ultrazohm_dataviewer`.

See the `CLI README <https://github.com/ultrazohm/ultrazohm_sw/tree/develop/ultrazohm_cli#readme>`_ for the Python API, recording options, and Vitis commands.
