.. _uz_scope:

===============
UltraZohm Scope
===============

``uz_scope`` is the modern live GUI for the UltraZohm — the successor to the :ref:`JavaScope <JavaScope>`.
It speaks the **same TCP protocol against unmodified firmware**, so it is a drop-in client: it connects to the APU at ``192.168.1.233:1000``, plots the scope channels live, drives the device state machine (Enable System / Enable Control / Stop / Error Reset), MyButtons and send fields, shows SlowData and receive fields, triggers, and logs captures.
It is built in Python on Dear ImGui / ImPlot (``imgui_bundle``) — the same stack as the :ref:`Data Viewer <uz_dataviewer>`, which it imports as a library.

.. note::

   The UltraZohm accepts **one** GUI client at a time: starting ``uz_scope`` while the JavaScope is connected (or vice versa) takes over the connection slot.
   ``uz_scope`` also warns when a second instance of itself is started on the same machine.

.. toctree::
   :hidden:

   uz_scope_architecture
   uz_scope_build

Install and run
===============

From the repository root::

   pip install -e ./uz_dataviewer -e ./uz_scope
   python uz_scope/run.py

Useful flags: ``--ip`` and ``--port`` override the saved connection settings, and ``--connect`` connects on startup without changing the saved auto-connect setting.
Settings persist in ``uz_scope_settings.json`` and the window layout in ``uz_scope_layout_v2.ini``, both next to the working directory.

To try it without hardware, run the JavaScope test server and point the scope at it::

   python javascope/test_server.py --port 5555
   python uz_scope/run.py --ip 127.0.0.1 --port 5555 --connect

The test server is lock-step, so leave *ack pacing* on (the default).
It also simulates at 1 kHz instead of the usual 10 kHz; the rate auto-detection notices this after a few seconds, warns in the console, and corrects the time axis (or set ``set_timestep(1000)`` up front).

Panels
======

The window docks the **Scope** plot windows (center, with Control, Dashboard, Trigger, SlowData, Logging and Diagnostics as tabs), the **Logged variables** list and **Observables** browser (right), a **Console** (bottom) and a status footer showing connection, throughput and log state.
Any panel — including every plot window — can be dragged out of the dock to float freely.

Everything is a command
=======================

Like the Data Viewer, every action — connecting, selecting an observable, arming the trigger, starting a log — is a *command* that is echoed to the console at the bottom.
Commands can be typed there directly, and ``help`` lists all of them.
For example ``connect`` always connects to the saved UltraZohm address (``192.168.1.233:1000`` unless changed with ``set_ip``/``set_port``), while ``connect(127.0.0.1, 5555)`` is a one-off — handy for the test server — that leaves the saved default untouched (the ``--ip``/``--port`` command line flags behave the same way).
``export_script(my_setup.uzscript)`` writes the session as a replayable script and ``run_script(...)`` replays one.
``save_state``/``load_state`` snapshot the whole configuration as JSON.

Logged variables and the observable browser
===========================================

The **Observables** panel lists every variable from ``enum JS_OberservableData`` in ``vitis/software/Baremetal/src/include/javascope.h`` (the scope parses this header directly, so names always match your firmware build).
Drag an observable onto the **Logged variables** panel — or right-click it and choose *Add to logged* — to stream it: it is assigned to the first free of the firmware's 20 channel slots (``log_add``), exactly like the JavaScope's channel select (command ids 201…).
The Logged variables list shows the active slots with a visibility checkbox, scale/offset and a color picker; right-click a row to free its slot again (``log_remove``).
Rows in the logged list are drag sources for the plot windows.
Scale and offset transform the display only (``(y + offset) / scale``); logged data stays raw.

Plot windows, zoom and session history
======================================

Plot windows work like the Data Viewer's plot grid:

- Every plot window has a **grid selector** (1x1, 1x2, 2x1, 2x2, 1x3, 3x1); each cell is an independent plot with its own axes (``plot_grid``), optionally x-linked (*Link X*).
- **Drag a logged variable into any cell** to show it there (``plot_assign``); right-click a legend entry to remove it again.
  Window 1's first cell mirrors the classic visibility checkboxes.
- **+ Plot window** (or ``plot_add``) opens more independent plot windows; drag them out of the dock to place them on a second monitor.
- The **timebase dropdown** offers the "last X s" presets plus ``cont``: in cont mode the time axis grows from t=0 for as long as the session runs.

While a window is *attached* it follows the live edge.
Any pan or zoom gesture detaches it — the plot then behaves exactly like the Data Viewer (mouse-wheel zoom, drag to pan, right-drag to box-zoom) and you can pan arbitrarily far into the past.
A *Follow* button (and an overlay hint in the plot) re-attaches to the live edge; *Fit* zooms out to the whole session.

How much old data is available is the **history mode** (``history_mode``):

- ``ram`` (default) — the recent past (the ring, ~10 s at full rate) stays sample-exact, and a min/max envelope of the *whole session* is kept in RAM (a few hundred MB/day at 20 ch x 10 kHz, capped by ``history_limit`` — the envelope coarsens instead of growing without bound).
  Zooming deep into old data shows the envelope, not individual samples.
- ``disk`` — additionally spills the raw stream to disk (``history_dir``, ~2.9 GB/h at 20 ch x 10 kHz); zooming into *any* old region loads full detail in the background and swaps it in.
  ``history_keep(on)`` preserves the spill files (plus a JSON sidecar) after exit.
- ``off`` — only the ring is available, like the classic scope.

Reassigning a channel slot to a different observable starts a new history epoch for that slot; older samples (which belong to the previous observable) are no longer shown.

Dashboard
=========

The **Dashboard** tab is a free canvas for your own command & control layout.
In *Edit* mode, drag entries from the palette — slowdata values, receive fields, send fields, MyButtons, the system buttons and status bits — onto the canvas; each drop creates a widget at that position (``dash_add``).
Drag widgets to arrange them, double-click one to configure it (widget kind, label, min/max range, number format, indicator bit), right-click to remove it.
Widget kinds: numeric **readout**, **gauge** (knob-style), **progress bar** and **LED** for values; **slider**, **knob** and **input field** for send fields (the value is transmitted when you release the slider/knob or press Enter); **button** and **toggle** for MyButtons and the state machine, with the matching status-bit indicator.
Leaving *Edit* mode makes the widgets live.
The layout persists in the settings JSON and replays through ``dash_*`` commands like everything else.

Trigger
=======

The Trigger tab arms an edge trigger (rising/falling, level, pretrigger fraction) on any channel, in ``auto``, ``normal`` or ``single`` mode.
While the trigger hunts for an edge, the plot keeps rolling and shows the armed level as a horizontal line.
The level is compared against the raw signal values, and the line is drawn through the channel's display transform — exactly like the JavaScope.
Each trigger event freezes the captured window in the plot with a crosshair at the trigger point.
``auto`` falls back to the rolling display when no further edge arrives within two window lengths, ``normal`` holds the last capture and re-arms, and ``single`` freezes after one capture.
``export_capture`` writes the frozen window to a file, and the *Export & open in Data Viewer* button hands it straight to the Data Viewer.

Logging
=======

The Logging tab streams incoming samples to disk while you work:

- **parquet** (default) — compressed, loads directly in the Data Viewer; keeps up with the full design rate.
- **csv** — plain text (``time,<name>,...``), opens in the Data Viewer, Excel or MATLAB; intended for moderate rates — at very high rates the writer reports drops instead of stalling the stream.
- **bin** — raw float32 spill with a JSON sidecar, the guaranteed-rate fallback; convert to Parquet afterwards.

``Log every N-th sample`` decimates before writing.
*External trigger* starts/stops the log from the device via status-word bit 12.
Legacy ``properties.ini`` files import with ``import_properties(path)``.

Sample rate
===========

The wire protocol does not carry the sample rate: the time axis derives from the configured timestep (default 100 µs → 10 kHz, matching ``UZ_PWM_FREQUENCY``).
With auto-detection enabled the scope measures the actual packet rate after connecting and warns if it disagrees with the configuration.
A mismatch usually means the configured geometry or timestep does not match the firmware.
``detect_rate`` (or the *Detect now* button in Diagnostics) re-measures on demand.

Diagnostics
===========

The Diagnostics tab shows link statistics, an ack-pacing toggle, and a trace of the last commands sent to the device.
When a channel observes ``JSO_lifecheck`` it also shows a continuity monitor that counts any dropped samples end-to-end.
The monitor knows that the firmware wraps this counter at 1000, so the periodic wrap is not reported as a drop.

Migrating from the JavaScope
============================

- ``import_properties(javascope/properties.ini)`` carries over IP, geometry, timestep, channel selection/visibility, scales/offsets and trigger settings.
- Send/receive fields, MyButtons and their labels come from the same header sections the JavaScope used — no re-configuration needed.
- Logs are Parquet/CSV instead of the legacy CSV layout; the Data Viewer opens both.
