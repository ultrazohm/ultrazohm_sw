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


1. First, press the ``connect`` button (1) in order to connect your scope to the UltraZohm.

2. You will see some moving signs at (2) if the connection was successful.

3. The JavaScope will be initialized by pressing ``initialize scope`` (3).

4. At next, press the ``Run/Stop`` button (4) in order to run the scope.

5. Go to the ``Setup Scope`` panel and press ``sendSelectData (all)`` to get the pre-selected values from the drop-down menus on the scope. For changing the entries of the drop-down menus, see :ref:`javascope_customizing`.

6. In the time-based scope it is possible to debug up to 20 values by receiving data from the ISR (R5 processor).

7. In the ``SlowData`` table it is possible to debug an almost endless number of values by receiving data from the ISR (R5 processor). However, these variables share one frame and are transferred in a chain. The more values are displayed, the longer it takes until they are updated. For changing the entries in the slow data table, see :ref:`javascope_customizing`.


Description of the buttons and pages
------------------------------------

Setup Scope page
""""""""""""""""

The Setup Scope page is used to adjust the scope settings during operation. 

  ..  _javascope_setup:

  ..  figure:: ./images_javascope/setupscope.png
      :scale: 90 %
      :align: center

      JavsScope Setup tab

1. Up to 20 channels, out of a predefined variable selection, can be chosen and displayed.

   If other variables than the predefined ones are necessary, just change them in the ipc_ARM.c of the R5 processor (see :ref:`javascope_customizing`).
   Do not forget to press the ``sendSelectData (all)`` button always after selecting signals from the drop-down menus if you want to change them! 

#. Each channel can have a specific scale factor and an offset.

   The scale factor is comparable to the scale factor of an oscilloscope. It changes the value per grid unit.

   Do not forget to press the ``CHx`` button in the ``Set Scaling`` column if you want to change the scaling! Scaling can also be adjusted by clicking the ``+`` and ``-`` buttons.
   For setting offsets to the channels, type the offset value into the proper field and press the ``CHx`` button of the respective channel. The ``Scale All`` and ``Offset All`` buttons will update the respective settings for all 20 channels.

#. SlowData Logger

   As the name intends, this tool logs slow data into a log file. The logger needs a milliseconds timer sent from the R5 somewhere in the slow data table in order to work. This timer variable has to be named ``JSSD_FLOAT_Milliseconds`` (exists by default).
   The logger logs the variables that are selected for beeing displayed in the receive_field's. See section on :ref:`javascope_customizing`.

   a. Press ``CREATE LOGFILE``

   b. Configure the logger with the drop-down menus. E.g. ``100ms`` for ``time between samples`` and ``3`` for ``samples per log event`` means that when pressing the ``MEASURE DATA`` button 3 samples with a timely distance of about 100 ms will be written into the log file.

   c. Press ``MEASURE DATA`` each time you want to log slow data

Control page
""""""""""""

The control page is used to step through the state-machine of the system and for setting commands and reference values. In addition, some slow data can be visualized.

  ..  _javascope_control:

  ..  figure:: ./images_javascope/control.png
      :align: center
      :scale: 90 %

      Javascope Control tab

1. The ``Enable System`` button has the same functionality as the hardware button on the main front panel.

   a. It sets the system state to enable which mainly enables IO and PWM pins.

   b. When the enable is confirmed by the R5 of the UltraZohm, a green status indicator next to the button will show the state of the system.

2. The ``Enable Control`` button has the same functionality as the hardware button on the main front panel.

   a. It sets the system state to enable control which mainly executes a part of the ISR of the R5 where the user should place its real-time application code.

   b. When the enable is confirmed by the R5 of the UltraZohm, a green status indicator next to the button will show the state of the system.

3. The ``STOP`` button has the same functionality as the hardware button on the main front panel.

   a. It disables the control and system enable states. IOs and PWM are deactivated and the real-time application code in the ISR is no longer executed.

   b. From the disappearing green status indicators left of the button it can be seen that the stop command was confirmed by the R5.

4. The ``receive_fields``

   a. Here some user-defined slow data values can be visualized more prominently than in the slow data table.

   b. For selection which values are shown here, see section :ref:`javascope_customizing`.

5. The ``send_fields``

   a. Six values are available that can be used as references or set points for the user application.

   b. After typing in a value, press ``set`` for sending it to the R5. In ``ipc_ARM.c`` one can choose further usage of the value inside the application.

  ..  _javascope_sendfields:

  ..  figure:: ./images_javascope/ipcSend.png
      :align: center

      Part of ``ipc_ARM.c`` where ``send_field_x`` values are received

6. The ``mybuttons``

   a. Besides the ``send_field`` values, there are 8 buttons available for the user. In ``ipc_ARM.c`` one can choose what happens when pressing the buttons.

   b. Below each button is a status indicator that can be triggered also in ``ipc_ARM.c`` if one likes to have feedback for the button actions. See ``/* Bit 2 - My_Button_1 */`` in the right picture below for example usage.

  ..  _javascope_mybuttons:

  ..  figure:: ./images_javascope/buttons.png
      :align: center

      left: further usage of the buttons, right: control of the status indicators of the buttons


7. The ``Error Reset`` can be used to reset errors that occurred.


   a. What happens when pressing ``Error Reset`` can also be programmed in ``ipc_ARM.c``

   b. For sending error codes to the GUI that are then displayed in the respective text field ``error code`` use the slow data variable ``JSSD_FLOAT_Error_Code``.

.. warning::
   Error detection and handling have to be implemented by the user. The GUI just provides an interface.



  ..  _javascope_customizing:

Customizing
-----------

The GUI itself and the variables that are visualized can be customized by the user.

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

The selection which slow data values are displayed in the ``receive_field`` section works the same way. Simply copy the proper entries from the ``JS_SlowData`` enum into 
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
Philipp Loehdefink (THN), Sebastian Wendel (THN), Eyke Liegmann (TUM), Michael Hoerner (THN) in 01/2022

