.. _JavaScope:

=========
JavaScope
=========

This page documents the UltraZohm GUI in the folder ``ultrazohm_sw/javascope``.

.. note::
   The GUI layout was reworked, but the UltraZohm software-side integration in Vitis stays the same.
   Continue to customize ``javascope.h`` and ``javascope.c`` as described in :ref:`javascope_customizing`.
   For the preserved documentation of the older GUI, see :doc:`javascope_legacy`.

.. toctree::
   :hidden:

   javascope_customization
   javascope_legacy

.. _javascope_folder:

Folder contents
---------------

The ``javascope`` folder contains the following files:

- ``javascope_run.bat`` starts the GUI on Windows.
- ``UZ_GUI.jar`` is the current GUI binary.
- ``properties.ini`` contains the startup configuration that is loaded when the GUI starts.
- ``JS_plot_data.m`` is a MATLAB script that reads and plots recorded data.
- ``dataviewer.py`` and the related Python helper scripts support offline analysis of recorded data.
- ``lib`` contains the required Java libraries.
- ``Log_yyyy-mm-dd_hh-mm-ss.csv`` is created when the logger is enabled.

Build and source-code changes of the GUI itself are maintained in the JavaScope source repository.
For running the binary in ``uz_sw``, install :ref:`JDK 21 or higher <install_java>`.

Basics
------

At startup the current GUI prefers a Full HD window size and falls back to fullscreen if this does not fit the current display scaling.
It also tries to connect automatically to the IP address configured in ``properties.ini``.

.. _javascope_gui:

.. figure:: ./images_javascope/overview.png
   :align: center

   Current JavaScope overview

#. The redesigned header groups scope, trigger, and logging controls in one place.
#. The plot on the left shows up to 20 fast channels.
#. The right side hosts the ``Setup Scope``, ``Control``, and ``MoreSendAndReceive`` tabs.
#. The footer now combines runtime status, connection handling, sampling-rate display, and throughput feedback.


Header controls
"""""""""""""""

.. _javascope_header:

.. figure:: ./images_javascope/header.png
   :align: center

   Header groups of the current GUI

#. ``Scope`` group: acquisition state indicator, ``Run/Stop``, time base selection, ``fixAxis``, and ``Save Settings``.
#. ``Trigger`` group: trigger channel selection, rising/falling edge toggle, trigger enable toggle, trigger level, pretrigger slider, and ``SingleShot``.
#. ``Logging`` group: ``Logging OFF/ON``, ``Log FastData``, ``Log SlowData``, ``ext. log trigger``, ``Log every N``, and the log-state indicator.

The trigger controls apply immediately.
``SingleShot`` now behaves like a modern oscilloscope single acquisition: the scope keeps rolling while armed and freezes only after a valid trigger plus the configured post-trigger capture window.

``Save Settings`` writes the current trigger setup, selected scope channels, channel visibility, scaling, offsets, detected sampling rate and related defaults back to ``properties.ini``.

Footer and connection area
""""""""""""""""""""""""""

Compared with the legacy GUI, the footer now carries the most important runtime information and connection controls in one place.

.. _javascope_footer:

.. figure:: ./images_javascope/footer.png
   :align: center

   Footer of the current GUI

#. Status text for connection and runtime feedback.
#. Connection indicator.
#. Target IP address and the ``connect`` button.
#. ``disconnect`` button.
#. Effective sampling-rate display.
#. Throughput display of the received data stream.

The footer makes it easier to spot connection problems and dropped data without opening extra dialogs.
When throughput drops below 95% of expected data rate, the text color switches to red.

Description of pages and controls
---------------------------------

.. _javascope_setup_scope:

Setup Scope page
""""""""""""""""

The ``Setup Scope`` page is used to choose the displayed signals and adjust the vertical scaling of each plotted channel.

.. _javascope_setup:

.. figure:: ./images_javascope/setup_scope.png
   :align: center

   Current ``Setup Scope`` tab

#. Signal selection for the 20 scope channels.
#. Per-channel enable toggles for hiding or showing channels.
#. Per-channel scaling with direct value entry and ``+``/``-`` buttons.
#. Per-channel offset entry.
#. ``Enable All`` and ``Disable All`` for quick channel visibility changes.

The available signal names are still parsed from ``JS_ObservableData`` in ``javascope.h``.
While connected, changing a channel selection is applied immediately.
On a fresh connection the GUI also sends the preselected channel configuration automatically, so the old manual startup workflow is shorter.

.. _javascope_control:

Control page
""""""""""""

The ``Control`` page is still the main page for stepping through the UltraZohm state machine, sending user values, and watching selected slow data.

.. figure:: ./images_javascope/control.png
   :align: center

   Current ``Control`` tab

#. ``receive_field_1`` to ``receive_field_6`` show selected slow data prominently.
#. ``send_field_1`` to ``send_field_6`` send user-defined values to the UltraZohm software.
#. ``Enable System``, ``Enable Control``, and ``STOP`` mirror the hardware front-panel state-machine buttons.
#. ``Ready``, ``Running``, ``Error``, and ``User`` mirror the front-panel status LEDs.
#. ``Error Reset`` and the ``error code`` field remain available.
#. The ``SlowData`` table provides the complete parsed slow-data list.

All functionality related to the user C-code in Vitis remains the same:
``send_field_x`` values, ``receive_field_x`` mappings, error-code handling, button labels, and the eight ``my buttons`` are still configured on the UltraZohm side through ``javascope.h`` and ``javascope.c``.

Rows in the ``SlowData`` table can now be copied directly with ``Ctrl+C`` or the context menu, which is useful for debugging and issue reports.

MoreSendAndReceive page
"""""""""""""""""""""""

The ``MoreSendAndReceive`` page extends the ``Control`` page with the remaining receive and send fields.

.. _javascope_more_send_receive:

.. figure:: ./images_javascope/more_send_receive.png
   :align: center

   Current ``MoreSendAndReceive`` tab

#. Additional ``receive_field_7`` to ``receive_field_20`` entries.
#. Additional ``send_field_7`` to ``send_field_20`` entries.
#. A duplicated control/status block for the common state-machine actions.

This tab is primarily useful if more than the first six receive and send fields are needed at the same time.

.. note::
   If ``ScopeDevTab = 1`` is set in ``properties.ini``, an additional ``ScopeDev`` tab appears.
   It contains developer tools such as the pause-ack toggle, throughput readout in MBit/s, and the lifecheck monitor for packet-gap detection.

Logging
"""""""

The logger is now controlled from the header instead of a separate legacy logging strip.

#. ``Logging OFF/ON`` starts and stops logging.
#. ``Log FastData`` and ``Log SlowData`` select which data groups are written to the log file.
#. ``Log every N`` reduces the logging rate for fast and slow data together.
#. ``ext. log trigger`` still allows the UltraZohm software to control logging via the status bit, as in the legacy GUI.

Each time logging is started, the GUI creates a new ``Log_yyyy-mm-dd_hh-mm-ss.csv`` file automatically.



Configuration and customization
-------------------------------

The common customization workflow for the current GUI and the legacy GUI is documented in :ref:`javascope_customizing`.
That page describes:

- the shared ``properties.ini`` settings
- current-GUI-only optional settings such as trigger defaults, automatic sampling-rate detection, ``sendZeroAckCommand``, and ``ScopeDevTab``
- adding observable scope signals in ``javascope.h`` and ``javascope.c``
- adding slow data variables
- configuring receive fields, send fields, and button labels in ``javascope.h``

