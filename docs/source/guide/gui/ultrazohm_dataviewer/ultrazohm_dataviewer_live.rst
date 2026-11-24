Live mode
=========

The Rust ultrazohm-cli process owns the device connection, acquisition and recording.
DataViewer and terminal/Python clients share that ultrazohm-cli process.
JavaScope must not connect to the same device concurrently.

.. code-block:: text

   UltraZohm TCP :1000 <-> acquisition service :19740
                                  ^
                                  | CLI / acquisition Python Client / viewer
                                  |
                          DataViewer :19741 <-> viewer Python Client / terminal

Connect and record
------------------

1. Start the DataViewer from the matching firmware checkout, use ``gui --live-repo PATH``, or select **Live Data → Browse for ultrazohm_sw**.
   Preparation reads the headers; they must match deployed firmware.
   The sample period is configured, not inferred from received traffic.
2. Enter the device IP and port.
   **Connect** launches a DataViewer-owned ultrazohm-cli process.
   To share a running ultrazohm-cli process, enter its endpoint and use **Existing service → Attach**.
   If it is disconnected, use **Connect device**.
   Attachment does not change its settings.
3. Assign channel slots, then drag channels into **Live Plots**.
   Enable system or control only when appropriate for the experiment; connecting does neither.
4. Start fast and/or slow logging.
   They are independent.
   Stop logging and wait for phase **complete** before opening its completed Parquet file.
5. Use **Open completed log** for analysis mode.
   Alternatively, **Freeze plot 1 for analysis** copies a bounded live window into memory; export it to retain it.
   To save a reloadable session, reopen the exported file, replace the snapshot's plot and node-source references with that recording, and remove the memory-only snapshot.

Follow live keeps the newest samples visible.
Panning, Shift-modified zoom, or unchecking Follow live enters Inspect with a frozen RAM snapshot.
Re-enable Follow live or Reset view to catch up.
Neither mode fetches full recording history from disk.
Default live retention is 30 seconds.
Acquisition time uses the nominal sample period and cannot reconstruct unknown transport gaps.

Lifecycle and ownership
-----------------------

- Device **Stop** leaves acquisition and logging running.
- Stopping logging finalizes only that stream; paused logging retains its recording.
  Observable changes are blocked while either stream records or is paused.
- **Detach** leaves the ultrazohm-cli process and recordings running.
- Closing an attached DataViewer sends device Stop.
  A DataViewer-owned ultrazohm-cli process also shuts down; an externally owned ultrazohm-cli process remains running.
- **Disconnect** or **Shutdown** shuts down even an attached external ultrazohm-cli process: device Stop, acquisition end, recording finalization, then ultrazohm-cli process exit.
- **Flash UZ** submits an ultrazohm-cli process job.
  The ultrazohm-cli process stops acquisition, finalizes, builds/programs and creates a fresh session while keeping its endpoint available.
  Logging starts idle.
  Shutdown waits for programming already underway.

Firmware tools and recording files belong to the machine running ultrazohm-cli.
An attached DataViewer does not need local XSCT or a checkout.
Live viewing works over an SSH forward; opening completed files requires local/shared access or copying them.
See :doc:`../ultrazohm_cli` and the ultrazohm-cli README for firmware prerequisites and failures.

Configuration and files
-----------------------

.. list-table::
   :header-rows: 1

   * - Item
     - Location / rule
   * - Startup profile
     - Explicit ultrazohm-cli process profile, then checkout ``artifacts/_user/settings.json``, then built-in defaults; saved profiles are validated strictly.
   * - XSCT selection
     - Explicit ultrazohm-cli process ``--xsct``, then checkout ``tools.json`` under ``artifacts/_user``, then PATH.
   * - DataViewer layout / live preferences
     - ``viewer.ini`` / ``live_view.json`` under checkout ``artifacts/_user``.
   * - Application defaults
     - ``viewer_preferences.json`` in the platform user-data directory.
   * - GUI cache
     - Workspace ``viewer_cache``; ``UZ_DATAVIEWER_CACHE`` overrides it.
   * - Default DataViewer recordings
     - Workspace ``artifacts/_user/logs``.
   * - Default ultrazohm-cli recordings
     - Checkout ``artifacts/live_logs/<timestamp>``.

Without a checkout, DataViewer workspace data uses ``%LOCALAPPDATA%\UltraZohm\ultrazohm_dataviewer`` on Windows or ``${XDG_DATA_HOME:-~/.local/share}/ultrazohm/ultrazohm_dataviewer`` on Linux.
Explicit recording directories must be new and their parent must exist.
Save startup profile and Save view preferences are separate actions.
