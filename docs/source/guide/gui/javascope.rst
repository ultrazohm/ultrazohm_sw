.. _JavaScope:

=========
JavaScope
=========

This page documents the UltraZohm GUI in ``ultrazohm_sw/javascope``.

.. note::
   The GUI layout changed, but the Vitis-side integration is unchanged.
   Customize ``javascope.h`` and ``javascope.c`` as described in :ref:`javascope_customizing`.
   For the legacy GUI, see :doc:`javascope_legacy`.
   For updating legacy GUI files in older branches, see :ref:`the legacy JavaScope upgrade note <javascope_legacy_upgrade_note>`.

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
- ``Log SlowData`` includes ``SlowData`` values in the log file. All received ``SlowData`` is logged.
- ``ext. log trigger`` allows the UltraZohm software to control logging via its status bit.
- ``Log every N`` reduces the logging rate of FastData by saving only every Nth sample group. If enabled, ``SlowData`` is logged at full rate.
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

Description of tabs and controls
--------------------------------

.. _javascope_setup_scope:

Setup Scope tab
"""""""""""""""

The ``Setup Scope`` tab selects displayed signals and adjusts per-channel vertical scaling.

.. _javascope_setup:

.. figure:: ./images_javascope/setup_scope.png
   :align: center

   JavaScope Setup Scope tab

Each of the 20 scope channels provides the following options:

#. ``Enable`` toggles by clicking on ``CHx``. Colored when active, gray when disabled.
#. ``Signal`` selection. Use num-pad for quick access in the drop-down menu.
#. ``Scaling`` with direct entry and ``+``/``-`` buttons. The displayed value is scaled by ``1/scaling``.
#. ``Offset`` entry to shift the signal on the y-axis.
#. ``Enable All`` and ``Disable All`` for global channel visibility control.

Available signal names are parsed from ``JS_ObservableData`` in ``javascope.h``.
On connection, the GUI sends the preselected channel configuration automatically.
Channel selection changes are applied immediately while connected.
Scaling and offset are applied when you press ``Enter`` or move focus away from the input field.

.. _javascope_control:

Control tab
"""""""""""

The ``Control`` tab is the main interface for state-machine control, user inputs, and selected ``SlowData``.

.. figure:: ./images_javascope/control_panel.png
   :align: center

   JavaScope Control tab

#. ``Enable System``, ``Enable Control``, and ``STOP`` map to the front-panel state-machine buttons. For details on the R5 states and transitions, see :ref:`r5_statemachine`.

   .. admonition:: Note for :ref:`≥Rev05-based UltraZohm systems <hardware>`

      With ≥Rev05 carrier boards, the STOP and Enable buttons on the front panel affect functions beyond the UZ software and must be considered when using JavaScope.
      See the "Warning" info-box in the :ref:`"Powerbutton Functionality" documentation of the Rev05 carrier board <carrier_board_rev05_s3cpwr>` for details.

#. ``Ready``, ``Running``, ``Error``, and ``User`` map to the front-panel status LEDs. If an ``assert`` occurs in the UltraZohm, JavaScope disconnects, and the ``Error`` LED may only be visible on the hardware front panel.

#. The ``receive_fields``

   a. Selected user-defined ``SlowData`` values can be shown more prominently here than in the ``SlowData`` table.

   b. For configuring which values are shown here, see :ref:`javascope_customizing`.

   c. If not all of the up to 20 channels are required, they can be set to ``JSSD_FLOAT_ZEROVALUE``.

#. The ``send_fields``

   a. 20 values are available as references or setpoints for the user application.

   b. After entering a value, press ``enter`` or the ``set`` button to send it to the R5. In ``ipc_ARM.c``, you can define how the value is used in the application.

   .. _javascope_sendfields:

   .. figure:: ./images_javascope_legacy/ipcSend.png
      :align: center

      Part of ``ipc_ARM.c`` code path where ``send_field_x`` values are received

#. The ``mybuttons``

   a. In addition to the ``send_field`` values, eight user buttons are available. In ``ipc_ARM.c``, you can define what happens when the buttons are pressed.

   b. Each button has a status indicator below it. This indicator can also be set in ``ipc_ARM.c`` to provide feedback for button actions.
      See ``/* Bit 4 - My_Button_1 */`` in the right picture below for an example.

   .. _javascope_mybuttons:

   .. figure:: ./images_javascope_legacy/buttons.png
      :align: center

      left: further use of the buttons; right: control of the button status indicators


#. The ``SlowData`` table lists all parsed ``SlowData`` entries from ``javascope.h`` (see :ref:`javascope_customizing`).
   Rows in the ``SlowData`` table can be copied via ``Ctrl+C`` or the context menu.
   The more values are displayed, the longer it takes until they are updated.
#. ``Error Reset`` and the ``error code`` field provide fault handling.

   a. The behavior of ``Error Reset`` must also be programmed in ``ipc_ARM.c``.
   b. To send error codes to the GUI for display in the ``error code`` field, use the ``SlowData`` variable ``JSSD_FLOAT_Error_Code``.

   .. warning::
      Error detection and handling have to be implemented by the user. The GUI just provides an interface.


Vitis-side user C-code integration is unchanged:
``send_field_x`` values, ``receive_field_x`` mappings, error-code handling, button labels, and the eight ``my buttons`` are configured in ``javascope.h`` and ``javascope.c``.


More Send and Receive tab
"""""""""""""""""""""""""

The ``MoreSendAndReceive`` tab extends ``Control`` with the remaining receive and send fields.

.. _javascope_more_send_receive:

.. figure:: ./images_javascope/more_send_receive.png
   :align: center

   JavaScope More Send and Receive tab

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
