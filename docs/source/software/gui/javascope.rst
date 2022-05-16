.. _JavaScope:

=========
JavaScope
=========

The JavaScope is located in the main ultrazohm_sw repository in the folder  ``ultrazohm_sw\javascope``.
The folder contains the following files

- ``javascope_run.bat`` is the executable for Windows, start by double-clicking 
- ``UZ_GUI.jar`` is the binary build file of the JavaScope, the sources are in a separate repository
- ``properties.ini`` is the configuration file that is loaded when starting the JavaScope
- ``JS_plot_data.m`` is a Matlab script, that reads and plots the measurement data 
- ``lib`` is the folder including the required Java libraries
- ``Log_yyyy-mm-dd-hh-mm-ss.csv`` is a log file that is created at every startup of the GUI

  ..  _javascope_folder:

  ..  figure:: ./images_javascope/gui0.png
      :scale: 70 %
      :align: center

      JavaScope folder strucuture

Basics
------

The GUI is shown in :numref:`javascope_gui`. 

  ..  _javascope_gui:

  ..  figure:: ./images_javascope/gui1.png
      :align: center

      GUI


#. First, press the ``connect`` button (1) in order to connect your scope to the UltraZohm.
#. You will see some moving signs at (2) if the connection was successful.
#. The ``Stop`` (3) respectively ``Run`` button stops or restarts the scope. After the connection has been established, the Scope will be put into the ``Run`` mode automatically.
#. You can switch between a **Lightmode** and **Darkmode** for the GUI on the fly.
#. Go to the ``Setup Scope`` panel and press ``sendSelectData (all)`` to get the pre-selected values from the drop-down menus on the scope. For changing the entries of the drop-down menus, see :ref:`javascope_customizing`.
#. In the time-based scope it is possible to debug up to 20 values by receiving data from the ISR (R5 processor).
#. In the top-panel it is possible to configure the data logging and time scale.

Description of the buttons and pages
------------------------------------

..  _javascope_setup_scope:

Setup Scope page
""""""""""""""""

The Setup Scope page is used to adjust the scope settings during operation. 

..  _javascope_setup:

  ..  figure:: ./images_javascope/setupscope.png
      :scale: 90 %
      :align: center

      JavsScope Setup tab

#. Up to 20 channels, out of a predefined variable selection, can be chosen and displayed.

   If other variables than the predefined ones are necessary, just change them in the ``ipc_ARM.c`` file of the R5 processor (see :ref:`javascope_customizing`).
   Do not forget to press the ``sendSelectData (all)`` button always after selecting signals from the drop-down menus if you want to change them! 

#. Each channel can have a specific scale factor and an offset.

   The scale factor is comparable to the scale factor of an oscilloscope. It changes the value per grid unit.

   Do not forget to press the ``CHx`` button in the ``Set Scaling`` column if you want to change the scaling! Scaling can also be adjusted by clicking the ``+`` and ``-`` buttons.
   For setting offsets to the channels, type the offset value into the proper field and press the ``CHx`` button of the respective channel. The ``Scale All`` and ``Offset All`` buttons will update the respective settings for all 20 channels.

Control page
""""""""""""

The control page is used to step through the state-machine of the system and for setting commands and reference values. All buttons and LEDs of the front panel are mirrored in the GUI. In addition, some slow data can be visualized.

..  _javascope_control:

  ..  figure:: ./images_javascope/control.png
      :align: center
      :scale: 90 %

      Javascope Control tab

#. The ``Enable System`` button has the same functionality as the hardware button on the main front panel.

   a. It sets the system state to enable which mainly enables IO and PWM pins.

   b. When the enable is confirmed by the R5 of the UltraZohm, the ``Ready`` LED on the front panel as well as its mirrored twin in the GUI will blink faster.

#. The ``Enable Control`` button has the same functionality as the hardware button on the main front panel.

   a. It sets the system state to enable control which mainly executes a part of the ISR of the R5 where the user should place its real-time application code.

   b. When the enable is confirmed by the R5 of the UltraZohm, the ``Running`` LED on the front panel as well as its mirrored twin in the GUI will turn on in addition to the blinking ``Ready`` LED.

#. The ``STOP`` button has the same functionality as the hardware button on the main front panel.

   a. It disables the control and system enable states. IOs and PWM are deactivated and the real-time application code in the ISR is no longer executed.

   b. From returning to the slow blinking of the ``Ready`` LED and turning off the ``Running`` LED it can be seen that the stop command was confirmed by the R5.

#. The four LEDs mirror the LEDs of the front panel and always show the same state as the real LEDs do. In the case of an ``assert`` event in the UltraZohm no data is transferred anymore to the GUI. In this case, the ``Error`` LED will only be seen on the real hardware front panel.

#. The ``receive_fields``

   a. Here some user-defined slow data values can be visualized more prominently than in the slow data table.

   b. For the selection of which values are shown here, see section :ref:`javascope_customizing`.

#. The ``send_fields``

   a. Six values are available that can be used as references or setpoints for the user application.

   b. After typing in a value, press ``set`` for sending it to the R5. In ``ipc_ARM.c`` one can choose further usage of the value inside the application.

   ..  _javascope_sendfields:

   ..  figure:: ./images_javascope/ipcSend.png
       :align: center

       Part of ``ipc_ARM.c`` where ``send_field_x`` values are received

#. The ``mybuttons``

   a. Besides the ``send_field`` values, there are 8 buttons available for the user. In ``ipc_ARM.c`` one can choose what happens when pressing the buttons.

   b. Below each button is a status indicator that can be triggered also in ``ipc_ARM.c`` if one likes to have feedback for the button actions. See ``/* Bit 4 - My_Button_1 */`` in the right picture below for example usage.

   ..  _javascope_mybuttons:

   ..  figure:: ./images_javascope/buttons.png
       :align: center

       left: further usage of the buttons, right: control of the status indicators of the buttons


#. The ``Error Reset`` can be used to reset errors that occurred.

   a. What happens when pressing ``Error Reset`` can also be programmed in ``ipc_ARM.c``

   b. For sending error codes to the GUI that are then displayed in the respective text field ``error code`` use the slow data variable ``JSSD_FLOAT_Error_Code``.

#. In the ``SlowData`` table it is possible to debug an almost endless number of values by receiving data from the ISR (R5 processor). However, these variables share one frame and are transferred in a chain. The more values are displayed, the longer it takes until they are updated. For changing the entries in the slow data table, see :ref:`javascope_customizing`.

.. warning::
   Error detection and handling have to be implemented by the user. The GUI just provides an interface.

Logging panel
"""""""""""""

The logging panel is used to setup the data logger of the GUI.

..  figure:: ./images_javascope/loggingpanel.png
    :align: center

    logging panel

#. The ``setTime`` button sets the time base of the Scope. It simply scales the time base of the scope by the selected value.
#. After zooming in on one or both axis, the ``fixAxis`` button reverts the axis limits to the default value.
#. Here the trigger level for a manual trigger can be set (e.g. 1V).
#. With this slider, the preTrigger can be configured. (e.g. how much time is visible before the trigger event happens).
#. The button ``setTrigger`` sets the selection for rising or falling edge for CH1->Ch4. Choose the desired setting in the dropdown menu above.
#. The button ``SingleShot`` triggers the scope once.
#. The button ``SaveScreen XLS`` saves the visible scope content in a xls file.
#. The button ``Logging OFF`` respectively ``Logging ON`` toggles the data logger. 
   If the button reads ``Logging OFF``, pressing it will turn on the logger. 
   If the button reads ``Logging ON`` and is highlighted green, pressing the button again will turn off the logger.
#. The button ``Log FastData`` enables or disables the logging of the fast data (the selection in the :ref:`javascope_setup_scope` panel). 
   If the selection is enabled, the text of the button is highlighted green. If the logging is active, this button is deactivated.
#. The button ``Log SlowData`` enables or disables the logging of the slow data.
   The slow data values, which are logged, are the values displayed in the ``receive fields``. 
   For customizing them see :ref:`javascope_customizing`.
   If the selection is enabled, the text of the button is highlighted green. If the logging is active, this button is deactivated.
#. With the ``set n-th log value`` the logging rate can be configured. Only the ``x-th`` value will then be logged (e.g. Factor ``10``, only the values for every 10th timestamp will be logged). 
   This logging rate counts for the fast and slow data. Choose the desired value from the dropdown menu above.
#. The button ``allow ext. logging`` enables the start and stop of the logging via a status-bit of the R5.
   If this functionality is enabled, the text of the button is highlighted and the button ``Logging ON/OFF`` is disabled/overwritten. 
   To activate this status bit, comment in the status-bit 12 in the ``ipc_ARM.c`` file and replace the variable for the condition with your own.

   .. code-block:: c
     :linenos:
     :caption: Status bit in ``ipc_ARM.c`` to transmit the external data logger signal from the R5 to the GUI. Has to be commented in

      /* Bit 12 - trigger ext. logging */
       // if (your condition == true) {
       //   js_status_BareToRTOS |= (1 << 12);
       // } else {
       //   js_status_BareToRTOS &= ~(1 << 12);
       // }

#. Status indicator to display, if the logging is active. 
   It is highlighted green and displays ``Log ON`` if either the logging through the GUI-button press or via the external signal is active. 
   If no logging is active, the text states ``Log OFF``.

..  _javascope_customizing:

Customizing
-----------

The GUI itself and the variables that are visualized can be customized by the user.

Adjusting the properties.ini file
"""""""""""""""""""""""""""""""""

Some settings can be configured before the start-up of the GUI in the ``properties.ini`` file.

#. The ``smallestTimeStepUSEC`` variable sets the time, with which data is assumed to be transferred to Java. 
   It's used to calculate the time-axis of the scope and logger. 
   It should match the sample time of the ISR (e.q. ISR-frequency of 10kHz -> smallestTimeStepUSEC=100). 
#. The ``initScaleChx`` variable sets the initial scaling factor for each of the 20 channels in the scope. 
   Use delimiter (;) to separate the scaling values for the channels.
#. The ``initOffsetCHx`` variable sets the initial offset for each of the 20 channels in the scope. 
   Use delimiter (;) to separate the scaling values for the channels.
#. The ``preSelectedChannelNumbers`` variable sets the pre-selected channel number for each of the 20 channels in the scope. 
   The numbers correspond to the ``JS_OberservableData`` enum in the ``javascope.h`` file (E.g. selecting ``1`` for ``CH1`` will set CH1 to ISR_ExecTime_us).
   Use delimiter (;) to separate the scaling values for the channels.
#. The ``preSelectedChannelVisibility`` variable sets the initial visibility for each of the 20 channels in the scope. 
   Using ``0`` disables the visibility of the specific channel, whilst ``1`` turns it on. 
   The visibility of the channels can still be changed during runtime by clicking on the appropriate channel in the legend of the scope. 
   Use delimiter (;) to separate the scaling values for the channels.
#. Panel extension selection. Setting the ``ParameterID`` variable to **1** enables this extension panel.


Add variables to the scope drop-down menus
""""""""""""""""""""""""""""""""""""""""""

For adding a variable to the drop-down menus of the 20 scope channels, two steps are required:

   1. Open ``javascope.h`` (Vitis: ``Baremetal\src\include\``) and add the name that should appear in the drop-down menu into the enum ``JS_ObservableData`` inside ``javascope.h`` (see blue box in the middle picture below). Pay attention to the naming convention starting with ``JSO_``.

   2. Open ``javascope.c`` (Vitis: ``Baremetal\src\sw\``) and assign a pointer of the variable to be viewed in the scope to the new enum entry from step 1 (see red and blue boxes in the right picture below). 

   The GUI parses the enum ``JS_ObservableData`` at startup and your new variable will appear in the drop-down menu (see green box in the left picture below). This way the user can add an almost infinite number of observable variables to the list, where 20 of them can be seen in the GUI at the same time.

  ..  _javascope_scopedata:

  ..  figure:: ./images_javascope/addscopevariable.png
      :align: center

      Correlation of ``javascope.c``, ``javascope.h`` and GUI for adding scope data

Add variables to the slow data table
""""""""""""""""""""""""""""""""""""
For adding a variable to the slow data table, two steps are required:

   1. Open ``javascope.h`` (Vitis: ``Baremetal\src\include\``) and add the name that should appear in the slow data table into the enum ``JS_SlowData`` inside ``javascope.h`` (see the blue box in the middle picture below). Pay attention to the naming convention starting with ``JSSD_INT_`` or ``JSSD_FLOAT_``.

   2. Open ``javascope.c`` (Vitis: ``Baremetal\src\sw\``) and assign a variable to be viewed in the slow data table to the new enum entry from step 1 (see red and blue boxes in the right picture below). 

   The GUI parses the enum ``JS_SlowData`` at startup and your new variable will appear in the slow data table (see green box in the left picture below). This way the user can add an almost infinite number of slow data variables to the list. The longer the table, the slower it is updated, because the slow data are sent one after another with each scope data frame.

  ..  _javascope_slowdata:

  ..  figure:: ./images_javascope/addslowdatavariable.png
      :align: center

      Correlation of ``javascope.c``, ``javascope.h`` and GUI for adding slow data

Customize the Control tab in the GUI
""""""""""""""""""""""""""""""""""""

For better usability and presentations, one might want to customize the slow data variables to be shown in the ``receive_field_x`` section as well as the description and physical units of ``send_field_x`` and ``receive_field_x`` entries in the control tab of the GUI.
All those can be customized in the ``javascope.h`` file. Towards the end of this file, you will notice a commented-out section that begins with ``/* Visualization Config for GUI */``. The text below is parsed by the GUI at startup 
and configures some text and the slow data to be displayed in the ``receive_field`` section. As shown below, one can simply change the text strings to adopt the GUI for the user application.

  ..  _javascope_customcontrol:

  ..  figure:: ./images_javascope/customizingGUI.png
      :align: center

      Correlation of ``javascope.h`` and text entries in the GUI

The selection of which slow data values are displayed in the ``receive_field`` section works the same way. Simply copy the proper entries from the ``JS_SlowData`` enum into 
the commented out enum at the end of the file ``javascope.h`` as shown below. The slow data values of the six ``JSSD_FLOAT_x`` entries that are above the ``JSSD_FLOAT_Error_Code`` will be displayed in the receive_fields 1 to 6 from top to bottom.
The ``JSSD_FLOAT_Error_Code`` value is always mapped to the error code text field of the GUI and should not be changed.

  ..  _javascope_selectslowdata:

  ..  figure:: ./images_javascope/customizationslowdata.png
      :align: center

      Correlation of ``javascope.h`` and which slow data are displayed in the control tab

Known issues
------------

.. warning::
   * If the JavaScope is distorted or the font is not readable, this may is due to an old Java version. 
   * If this is the case, just update your local Java version, as described in the section :ref:`install_java`.


See also
"""""""""""""""


Designed by
"""""""""""
Philipp Loehdefink (THN), Sebastian Wendel (THN), Eyke Liegmann (TUM), Michael Hoerner (THN) , Dennis Hufnagel (THN) in 04/2022

