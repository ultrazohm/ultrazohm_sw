.. _JavaScope:

=========
JavaScope
=========

This page documents the UltraZohm GUI in ``ultrazohm_sw/javascope``.

.. note::
   The GUI layout changed, but the Vitis-side integration is unchanged.
   Customize ``javascope.h`` and ``javascope.c`` as described in :ref:`javascope_customizing`.
   For the legacy GUI, see :doc:`javascope_legacy`.

.. toctree::
   :hidden:

   javascope_customization
   javascope_legacy

.. _javascope_folder:

Folder contents
---------------

The ``javascope`` folder contains:

- ``javascope_run.bat`` starts the GUI on Windows.
- ``UZ_GUI.jar`` is the GUI binary.
- ``properties.ini`` contains the startup configuration that is loaded when the GUI starts.
- ``JS_plot_data.m`` is a MATLAB script that reads and plots recorded data.
- ``dataviewer.py`` and the related Python helper scripts support offline analysis of recorded data.
- ``lib`` contains the required Java libraries.
- ``Log_yyyy-mm-dd_hh-mm-ss.csv`` is created when the logger is enabled.


.. figure:: ./images_javascope_legacy/gui0.png
   :scale: 50 %
   :align: center

   JavaScope folder structure

GUI source and build changes are maintained in the JavaScope source repository.
To run the binary in ``uz_sw``, install :ref:`JDK 21 or higher <install_java>`.


Basics
------

At startup, JavaScope uses a Full HD window and falls back to fullscreen if required.
It then attempts to connect to the IP address in ``properties.ini``.
After connection, it applies the preconfigured channel selection from ``properties.ini``.

.. _javascope_gui:

.. figure:: ./images_javascope/overview_numbered.png
   :align: center

   JavaScope overview

#. The header contains scope, trigger, and logging controls.
#. The plot displays up to 20 fast channels.
#. The right side contains the ``Setup Scope``, ``Control``, and ``MoreSendAndReceive`` tabs.
#. The footer shows runtime status, connection state, sampling rate, and throughput.


Header controls
"""""""""""""""

.. _javascope_header:

.. figure:: ./images_javascope/header.png
   :align: center

   JavaScope header controls


Scope
'''''

- ``Run/Stop`` starts or pauses acquisition display updates.
- ``Time base`` changes the displayed time window by plotting every Nth sample.
- ``fixAxis`` disables automatic axis rescaling during acquisition.
- ``Save Settings`` writes trigger, channel, scaling, offset, and sampling-rate settings to ``properties.ini``.

Trigger
'''''''

- ``Trigger channel`` selects the trigger source.
- ``Rising`` or ``Falling`` selects the signal edge.
- ``Trigger enable`` enables or disables triggered acquisition.
- ``Level`` sets the trigger threshold.
- ``PreTrig.`` sets the fraction of pre-trigger data in the capture window.
- ``SingleShot`` arms one triggered capture and freezes the display after the next valid event.

Logging
'''''''

- ``Logging OFF/ON`` starts or stops writing log files.
- ``Log FastData`` includes fast scope samples in the log file.
- ``Log SlowData`` includes slow-data values in the log file.
- ``ext. log trigger`` allows the UltraZohm software to control logging via its status bit.
- ``Log every N`` reduces the logging rate by saving only every Nth sample group.
- ``Log state`` shows whether logging is active.
- Each logging start creates a new ``Log_yyyy-mm-dd_hh-mm-ss.csv`` file.


Footer and connection area
""""""""""""""""""""""""""

.. _javascope_footer:

.. figure:: ./images_javascope/footer.png
   :align: center

   JavaScope footer and connection controls

- ``Status`` shows 32-bit status register.
- ``Connection indicator`` moves when new data package arrives.
- ``IP address`` shows the target device address.
- ``connect`` opens the connection to the UltraZohm at the configured IP address.
- ``disconnect`` closes the active connection.
- ``Sampling rate`` shows the configured or detected acquisition rate.
- ``Throughput`` shows the fraction of the expected data stream received. If throughput drops below 95 % of the expected rate, the text turns red.

Description of pages and controls
---------------------------------

.. _javascope_setup_scope:

Setup Scope page
""""""""""""""""

The ``Setup Scope`` page selects displayed signals and adjusts per-channel vertical scaling.

.. _javascope_setup:

.. figure:: ./images_javascope/setup_scope.png
   :align: center

   ``Setup Scope`` tab

#. Signal selection for 20 scope channels. Use num-pad for quick access.
#. Per-channel enable toggles by clicking on ``CHx``.
#. Per-channel scaling with direct entry and ``+``/``-`` buttons.
#. Per-channel offset entry.
#. ``Enable All`` and ``Disable All`` for global channel visibility control.

Available signal names are parsed from ``JS_ObservableData`` in ``javascope.h``.
Channel selection changes are applied immediately while connected.
On connection, the GUI sends the preselected channel configuration automatically.

.. _javascope_control:

Control page
""""""""""""

The ``Control`` page is the main interface for state-machine control, user inputs, and selected slow data.

.. figure:: ./images_javascope/control.png
   :align: center

   ``Control`` tab

#. ``receive_field_1`` to ``receive_field_6`` display selected slow data.
#. ``send_field_1`` to ``send_field_6`` transmit user-defined values.
#. ``Enable System``, ``Enable Control``, and ``STOP`` map to the front-panel state-machine buttons.
#. ``Ready``, ``Running``, ``Error``, and ``User`` map to the front-panel status LEDs.
#. ``Error Reset`` and the ``error code`` field provide fault handling.
#. The ``SlowData`` table lists all parsed slow-data entries.

Vitis-side user C-code integration is unchanged:
``send_field_x`` values, ``receive_field_x`` mappings, error-code handling, button labels, and the eight ``my buttons`` are configured in ``javascope.h`` and ``javascope.c``.

Rows in the ``SlowData`` table can be copied via ``Ctrl+C`` or the context menu.

MoreSendAndReceive page
"""""""""""""""""""""""

The ``MoreSendAndReceive`` page extends ``Control`` with the remaining receive and send fields.

.. _javascope_more_send_receive:

.. figure:: ./images_javascope/more_send_receive.png
   :align: center

   ``MoreSendAndReceive`` tab

#. ``receive_field_7`` to ``receive_field_20``.
#. ``send_field_7`` to ``send_field_20``.
#. A duplicated control/status block for common state-machine actions.

This tab is intended for operation with more than six receive or send fields.

.. note::
   If ``ScopeDevTab = 1`` is set in ``properties.ini``, an additional ``ScopeDev`` tab is shown.
   It contains developer tools such as the pause-ack toggle, throughput readout in MBit/s, and the lifecheck monitor for packet-gap detection.

Configuration and customization
-------------------------------

Customization is documented in :ref:`javascope_customizing`.
It covers:

- the shared ``properties.ini`` settings
- optional settings such as trigger defaults, automatic sampling-rate detection, ``sendZeroAckCommand``, and ``ScopeDevTab``
- adding observable scope signals in ``javascope.h`` and ``javascope.c``
- adding slow data variables
- configuring receive fields, send fields, and button labels in ``javascope.h``
