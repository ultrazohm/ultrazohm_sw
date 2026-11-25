ultrazohm-cli
=============

Use ``ultrazohm-cli`` to acquire live data, record measurements, and send commands to an UltraZohm.
Install the published ultrazohm-cli with ``uv tool install ultrazohm-cli``, or extract the standalone Windows ZIP from a release.
To try this checkout, run ``./uz_developer build``, ``./uz_developer shell``, then ``ultrazohm-cli``.
On Windows, use ``.\uz_developer.ps1`` with the same arguments.

Run ``ultrazohm-cli`` from the firmware checkout to open a disconnected prompt.
From another directory, use ``ultrazohm-cli serve --interactive --repo PATH`` to select the matching firmware checkout.
At the prompt, enter ``connect`` (or ``connect IP PORT``), then ``status`` and ``start-logging``.
Parquet is the default recording format.
Add ``--format csv`` to the ``serve`` command to export CSV as well.
Use ``stop-logging`` to finalize the recording and ``shutdown`` to stop the ultrazohm-cli process.

Run ``ultrazohm-cli serve --repo PATH --device IP:PORT`` for a headless ultrazohm-cli process.
Send commands such as ``ultrazohm-cli status`` from another terminal.
For Python automation, install ``ultrazohm-cli`` in the script's environment.
Import ``Client`` from ``ultrazohm_cli`` to control a running ultrazohm-cli process or ``Acquisition`` to own one.
For graphical operation, see :doc:`ultrazohm_dataviewer/ultrazohm_dataviewer`.

See the `ultrazohm-cli README <https://github.com/ultrazohm/ultrazohm_sw/tree/develop/ultrazohm_cli#readme>`_ for the Python API, recording options, and Vitis commands.

Firmware operations
-------------------

Start the ultrazohm-cli process with ``--repo PATH`` on the machine with Vitis/XSCT and JTAG access.
``--xsct PATH`` selects its launcher explicitly.
Both DataViewer Flash UZ and terminal ``build``, ``build-clean``, and ``flash`` commands submit jobs to this ultrazohm-cli process.
``--endpoint`` selects the ultrazohm-cli process; no command falls back to local execution.
Use ``jobs`` and ``job JOB_ID --follow`` to inspect progress.
``--no-wait`` submits a job without waiting.
Offline builds require ``build --local --repo PATH``; ``flash --local`` builds and programs without a service.
``--local`` runs are synchronous, so ``--no-wait`` and the service-only ``--device``/``--no-reconnect`` options are rejected with them.

Flashing stops acquisition and finishes recordings, then builds/programs and replaces the session with new firmware configuration.
The ultrazohm-cli process endpoint remains available.
Logging starts idle; system/control enable is never automatic.
Initially disconnected ultrazohm-cli processes can use ``flash --device IP:PORT`` or ``flash --no-reconnect``.

Closing a DataViewer always sends device Stop.
A DataViewer that started the ultrazohm-cli process also requests its shutdown; an attached DataViewer leaves the ultrazohm-cli process running.
Shutdown waits for programming already underway to finish.
Other clients observe Stop or shutdown.

Complete workflows
------------------

See :doc:`ultrazohm_dataviewer/ultrazohm_dataviewer_workflows` for launcher, standalone, multi-terminal, SSH and Python measurement tutorials.
