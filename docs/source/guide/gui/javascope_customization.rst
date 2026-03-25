.. _javascope_customizing:

=======================
JavaScope Customization
=======================

This page documents the configuration and customization workflow shared by the current GUI and the legacy GUI.
The current GUI supports additional optional ``properties.ini`` keys listed below.

Adjusting the properties.ini file
---------------------------------

Some settings can be configured in ``properties.ini`` before GUI startup.
In the GUI, ``Save Settings`` writes the current settings to ``properties.ini`` and overwrites the previous values.

Common settings used by both GUI generations
""""""""""""""""""""""""""""""""""""""""""""

#. ``ipAdress`` sets the target IP address used by the GUI.
#. ``MEASUREMENTS_PER_TCP_PACKET`` sets how many measurements are transferred per TCP packet. Keep this value aligned with the GUI and target implementation.
#. ``scopeChannelNumber`` sets the number of available scope channels. In the current UltraZohm setup this value is ``20``.
#. ``smallestTimeStepUSEC`` sets the time step in microseconds with which data is assumed to be transferred to Java.
   It is used to calculate the time axis of the scope and logger.
#. ``initScaleCHx`` sets the initial scaling factor for each of the 20 channels in the scope.
   Use the delimiter ``;`` to separate the scaling values for the channels.
#. ``initOffsetCHx`` sets the initial offset for each of the 20 channels in the scope.
   Use the delimiter ``;`` to separate the offset values for the channels.
#. ``preSelectedChannelNumbers`` sets the pre-selected channel number for each of the 20 channels in the scope.
   The numbers correspond to the ``JS_ObservableData`` enum in ``javascope.h``.
   Use the delimiter ``;`` to separate the values for the channels.
#. ``preSelectedChannelVisibility`` sets the initial visibility for each of the 20 channels in the scope.
   Using ``0`` disables the visibility of the specific channel, while ``1`` turns it on.
   The visibility can still be changed during runtime by clicking the appropriate channel in the scope legend.
#. ``ParameterID`` selects whether the extension panel is visible. Setting the variable to ``1`` enables the panel.

Current GUI optional settings
"""""""""""""""""""""""""""""

#. ``autoDetectSamplingRate`` automatically detects the effective sampling rate from the incoming packet rate during the first 5 seconds after establishing the connection.
   If the value is ``0``, the GUI uses ``smallestTimeStepUSEC`` instead.
#. ``triggerChannel`` selects the trigger source at startup.
   ``0`` selects automatic triggering, ``1`` selects ``CH1``, ``2`` selects ``CH2``, and so on.
#. ``triggerEdge`` selects the trigger edge.
   The current GUI accepts ``rising`` or ``falling`` and also the numeric values ``1`` and ``2``.
#. ``triggerValue`` sets the trigger threshold in plot units.
#. ``pretrigger`` sets the fraction of the buffer that is shown before the trigger event.
#. ``sendZeroAckCommand`` enables the idle ``0x00`` acknowledge commands sent by the GUI.
   Keep this value at ``1`` unless the FreeRTOS side of the UltraZohm project was adapted accordingly.
#. ``ScopeDevTab`` shows or hides the optional ``ScopeDev`` tab with extended functions for development and testing.

Add variables to the scope drop-down menus
------------------------------------------

To add a variable to the drop-down menus of the 20 scope channels, follow these two steps:

1. Open ``javascope.h`` (Vitis: ``Baremetal\src\include\``) and add the name that should appear in the drop-down menu into the enum ``JS_ObservableData`` inside ``javascope.h``. Pay attention to the naming convention starting with ``JSO_``.
2. Open ``javascope.c`` (Vitis: ``Baremetal\src\sw\``) and assign a pointer of the variable to be viewed in the scope to the new enum entry from step 1.

The GUI parses the enum ``JS_ObservableData`` at startup and your new variable appears in the drop-down menu.
This allows users to add a large number of observable variables to the list, while 20 can be displayed at the same time.

After changing ``JS_ObservableData``, restart the GUI so the updated list is parsed again.

.. _javascope_scopedata:

.. figure:: ./images_javascope_legacy/addscopevariable.png
   :align: center

   Correlation of ``javascope.c``, ``javascope.h`` and the GUI for adding scope data

Add variables to SlowData table
-------------------------------

To add a variable to the ``SlowData`` table, follow these two steps:

1. Open ``javascope.h`` (Vitis: ``Baremetal\src\include\``) and add the name that should appear in the ``SlowData`` table to the enum ``JS_SlowData`` inside ``javascope.h``. Pay attention to the naming convention starting with ``JSSD_INT_`` or ``JSSD_FLOAT_``.
2. Open ``javascope.c`` (Vitis: ``Baremetal\src\sw\``) and assign a variable to be viewed in the ``SlowData`` table to the new enum entry from step 1.

The GUI parses the enum ``JS_SlowData`` at startup and your new variable appears in the ``SlowData`` table.
This allows users to add a large number of ``SlowData`` variables to the list.
The longer the table, the slower it updates because ``SlowData`` entries are sent one after another with each scope data frame.

After changing ``JS_SlowData``, restart the GUI so the updated table is parsed again.

.. _javascope_slowdata:

.. figure:: ./images_javascope_legacy/addslowdatavariable.png
   :align: center

   Correlation of ``javascope.c``, ``javascope.h`` and the GUI for adding ``SlowData``

Customize the Control tab in the GUI
------------------------------------

For better usability and presentation, you may want to customize the ``SlowData`` variables shown in the ``receive_field_x`` section, as well as the descriptions and physical units of the ``send_field_x`` and ``receive_field_x`` entries in the Control tab.
All those can be customized in ``javascope.h``.
Towards the end of this file, there is a commented-out section that begins with ``/* Visualization Config for GUI */``.
The text below is parsed by the GUI at startup and configures text labels and the ``SlowData`` shown in the ``receive_field`` section.
The eight individual buttons can be labeled in the same way.

.. _javascope_customcontrol:

.. figure:: ./images_javascope_legacy/customizingGUI.png
   :align: center

   Correlation of ``javascope.h`` and text entries in the GUI

The selection of which ``SlowData`` values are displayed in the ``receive_field`` section works in the same way.
Simply copy the proper entries from the ``JS_SlowData`` enum into the commented-out enum at the end of ``javascope.h`` as shown below.
The ``SlowData`` values of the twenty ``JSSD_FLOAT_x`` entries above ``JSSD_FLOAT_Error_Code`` are displayed in receive fields 1 to 20 from top to bottom.
The ``JSSD_FLOAT_Error_Code`` value is always mapped to the error code text field of the GUI and should not be changed.

.. _javascope_selectslowdata:

.. figure:: ./images_javascope_legacy/customizationslowdata.png
   :align: center

   Correlation of ``javascope.h`` and the ``SlowData`` displayed in the Control tab

If not all 20 ``receive_fields`` are needed, unused channels can be set to ``JSSD_FLOAT_ZEROVALUE``.
They will appear as value ``0`` in the receive fields.
