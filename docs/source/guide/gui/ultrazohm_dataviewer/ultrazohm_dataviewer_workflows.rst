End-to-end workflows
====================

Standalone desktop user
-----------------------

On Windows, extract the complete DataViewer release ZIP, keeping ``_internal`` next to the executable.
Double-click ``ultrazohm-dataviewer.exe``.
No Python, uv or Rust installation is required.
Select the firmware checkout in Live Data, connect, assign signals, start/stop logging and open the completed log as described in :doc:`ultrazohm_dataviewer_live`.
For existing recordings, follow :doc:`ultrazohm_dataviewer_analysis` without connecting a device.

For terminal automation, open PowerShell in the extracted directory:

.. code-block:: powershell

   .\ultrazohm-dataviewer.ps1 gui measurement.parquet
   # In a second terminal while the viewer is open:
   .\ultrazohm-dataviewer.ps1 --json list-runs
   .\ultrazohm-cli.exe status

The last command requires an ultrazohm-cli process, not just an offline DataViewer.
Linux uses Python wheels instead of a standalone ZIP: ``uvx --python 3.12 --prerelease allow ultrazohm-dataviewer``.
Omit the prerelease option to select stable releases only.

Repository launcher
-------------------

From the repository root (Windows: replace ``./uz`` with ``.\uz.ps1``):

.. code-block:: bash

   ./uz dataviewer prerelease -- gui --live-repo .
   # Or open an existing recording without device access:
   ./uz dataviewer prerelease -- gui measurement.parquet
   # In another terminal, query the open viewer:
   ./uz dataviewer prerelease -- --json list-runs

``stable`` is the default channel; ``prerelease`` allows development releases.
These commands run published applications, including inside a development shell.
To run checkout code instead:

.. code-block:: bash

   ./uz venv dev
   ultrazohm-dataviewer gui --live-repo .

Dev mode requires Rust and a C/C++ toolchain, builds the ultrazohm-cli, and installs the DataViewer editable.
Close applications before ``exit`` deletes the temporary environment.
Reopen a dev shell after ultrazohm-cli changes; restart the DataViewer after Python changes.
``./uz venv prerelease`` provides both published applications and Python libraries.
All shell modes add root ``requirements.txt`` dependencies; application launch commands do not add those extra dependencies.

``./uz cli --help`` describes the launcher; ``./uz cli stable -- --help`` describes the application.
Files require ``gui``: ``./uz dataviewer measurement.csv`` is invalid.
DataViewer global options such as ``--json`` and control ``--endpoint`` precede the subcommand.
``./uz cli dev`` is not a source mode.
The launcher preserves the caller's working directory.
Calling a checkout's absolute launcher path from elsewhere does not select that firmware checkout; pass ``--repo`` to ultrazohm-cli serve or ``--live-repo`` to DataViewer gui explicitly.

For reproducible published versions, use exact package versions directly, e.g. ``uvx --python 3.12 ultrazohm-dataviewer==VERSION gui`` (replace VERSION).
The DataViewer requires its matching ultrazohm-cli version.
Use application ``--version`` and ultrazohm-cli process ``status`` to inspect versions; upgrade clients and ultrazohm-cli process together.
To refresh a published tool run, use ``uvx --refresh --prerelease allow ultrazohm-dataviewer``; for persistent installations use ``uv tool upgrade ultrazohm-dataviewer``.
``./uz install dataviewer prerelease`` exposes the DataViewer command on user PATH; ``./uz venv prerelease`` exposes both commands within its shell.

ultrazohm-cli process and terminal clients
------------------------------------------

Start one ultrazohm-cli process in terminal A; select headers matching the deployed firmware:

.. code-block:: bash

   ./uz cli prerelease -- serve --repo . --device 192.168.1.233:1000

In terminal B:

.. code-block:: bash

   ./uz cli prerelease -- status
   ./uz cli prerelease -- set-observable lifecheck 1
   ./uz cli prerelease -- start-logging
   # Perform the measurement, then:
   ./uz cli prerelease -- stop-logging
   ./uz cli prerelease -- status

Repeat status until ``logging.fast.phase`` is ``complete``; open the reported Parquet path in the DataViewer.
Then ``./uz cli prerelease -- shutdown`` and wait for terminal A to exit.
Stop-logging replies before finalization completes.
Connecting does not enable the system or start recording automatically.
An interactive alternative is ``./uz cli prerelease`` from the checkout; enter ``connect``, ``start-logging``, ``stop-logging`` and ``shutdown`` at its prompt.

For a hardware-free trial, start ``python javascope/test_server.py --host 127.0.0.1 --port 1000`` in another terminal and replace the ultrazohm-cli process device with ``127.0.0.1:1000``.
Use an installed project environment for the simulator.
It validates workflows, not physical interlocks or hardware readiness.

For a remote ultrazohm-cli process listening on its default loopback endpoint:

.. code-block:: bash

   ssh -N -L 19750:127.0.0.1:19740 user@service-host
   # In another local terminal:
   ./uz cli prerelease -- --endpoint 127.0.0.1:19750 status

Set the DataViewer's **Live Data** ultrazohm-cli process endpoint to ``127.0.0.1:19750`` and Attach.
DataViewer command-line ``--endpoint`` instead selects its own automation listener (default ``19741``); it does not select acquisition (default ``19740``).

Python measurement and analysis
-------------------------------

Open ``./uz venv prerelease`` (or ``dev``), then save and run the following as ``python measurement.py`` from the firmware checkout.
Choose an unused output name on each run.
This example owns its ultrazohm-cli process; no other ultrazohm-cli process may use 19740.

.. code-block:: python

   import time
   from ultrazohm_cli import Acquisition, Client

   with Acquisition(repo=".", output="measurement-001") as acquisition:
       device = Client()
       try:
           device.connect()
           device.set_observable("lifecheck", 1)
           device.start_logging()
           time.sleep(2)
       finally:
           device.close()
   # Context exit sends device Stop and waits for finalization.
   data = acquisition.read_recording()
   print(data.shape)

To control an existing ultrazohm-cli process, create only ``Client``; do not create Acquisition.
Closing Client closes its socket, not the ultrazohm-cli process or device.
Explicitly stop logging and poll completion, or request shutdown if you intend to end that ultrazohm-cli process.

For scripting from the DataViewer, open **View → Python**, save a Python file and run it.
The ordinary runner does not issue device Stop when stopping a script.
**Managed device run** requires a connected ultrazohm-cli process, locks manual controls and provides **Stop script + device**.
Use the supplied endpoints explicitly:

.. code-block:: python

   import os
   from ultrazohm_cli import Client as DeviceClient
   from ultrazohm_dataviewer import Client as ViewerClient

   device = DeviceClient(os.environ["UZ_ACQUISITION_ENDPOINT"])
   try:
       print(device.status())
       with ViewerClient() as viewer:
           print(viewer.list_runs())
   finally:
       device.close()

ViewerClient reads ``UZ_DATAVIEWER_ENDPOINT`` automatically.
DeviceClient does not read ``UZ_ACQUISITION_ENDPOINT`` automatically; pass it as above, especially for non-default ports and SSH forwards.
External scripts own their process lifetime.

To automate analysis, keep a DataViewer open, then run this in its matching environment:

.. code-block:: python

   from ultrazohm_dataviewer import Client

   with Client() as viewer:
       run = viewer.load("measurement-001/data.parquet")
       viewer.set_grid(1, 1)
       viewer.add_signal(1, run, "JSO_lifecheck")
       viewer.save_session("analysis.json")

Paths resolve from the script's working directory.
Calls wait for completion; several calls are not a transaction.
Obtain new handles after replacing a session.
For numerical work without an open DataViewer, use ``ultrazohm_dataviewer.read`` and its analysis functions, documented in :doc:`ultrazohm_dataviewer_library`.
