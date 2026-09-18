.. _project_wizard_page_reference:

Page Reference
==============

This page explains the purpose of each wizard page and the consequences of important settings.

Toolchain
---------

The Toolchain page stores paths to external tools:

* Vivado executable;
* Lattice Diamond Programmer executable;
* other helper paths where supported.

Press the ``Detect tools`` button once to let the project wizard automatically check for the paths 
to Vivado, Diamond Programmer, and Vitis. Since every user can have local git repositories at very different places
and the project wizard does not perform a search throughout the whole file system, 
the path to the ``CPLD repository`` has to be provided manually in any case. 

Actions that require a missing toolchain path show a warning and navigate back to this page.

Platform
--------

The Platform page selects the target platform and hardware revision.
For UltraZohm, the revision influences generated software defines such as ``UZ_HARDWARE_VERSION``.

The nameplate image is a visual hint for identifying the revision from the UltraZohm serial number.
Future platform entries may be visible but disabled until they are supported.

For UltraZohm revision 4 (``Rev04``) two different types of CPLDs have been used in production. Therefore, 
when this revision is selected, a dropdown menu appears including hints on how to determine the specific CPLD devices placed 
in your UltraZohm device. The correct selection is crucial, since it will choose the device specific folders and bitstream files 
for the CPLD type on the ``Slot CPLD`` page.

Hardware General
----------------

The hardware General page defines the Vivado project context:

Vivado project file
   The ``.xpr`` project that receives the generated block-design TCL.

Block-design name
   The target block design, usually ``zusys``.

PWM / Timing / Interrupts
-------------------------

This page configures global timing and generated PWM resources.

Important settings include:

* ISR interrupt source;
* ADC-to-ISR ratio;
* ADC trigger delay;
* PWM frequency;
* PWM deadtime;
* minimum pulse width;
* number of 2L PWM instances;
* whether the 3L PWM instance is enabled.

These settings affect:

* generated ``uz_pwm`` hierarchy;
* generated PWM driver initialization;
* generated ``uz_global_configuration.h`` defines;
* generated duty-cycle variables in ``Global_Data.rasv``;
* ISR platform-state behavior for idle, running, control, and error states.

.. figure:: img/page_references/pwm_timing_interrupts.png
   :width: 800
   :align: center

   PWM / Timing / Interrupts - Detailed view

The settings are explained in more detail in the four sections below.

- ``1`` **2L PWM:**
  The UltraZohm offers two-level PWM generation (See ``PWM and SS Control V4`` in IP Cores section). You can select the 
  number of instances that the project wizard should place in the Vivado block design. One instance provides three pairs of signals. 
  Each pair consists of a top-switch and a bottom-switch gate signal for switching a two-level half-bridge.

  Every 2L PWM instance is followed by an interlock and deadtime module (See ``Interlock and Deadtime module (2L)`` in IP Cores section). 
  Those modules prevent the top- and bottom-switch gate signals being high at the same time. It also provides an adjustable setting for 
  the deadtime. This setting delays the low-high transition of the gate signals by the configured amount of time. 

  At startup, when the system is in idle, or in the event of an error, init/default values for the duty-cycle values of each half-bridge 
  as well as tri-state mode for all half-bridges can be configured. This way you can set idle/error behavior that matches your application.

- ``2`` **3L PWM:**
  The UltraZohm offers three-level PWM generation. The respective IP-core exists but is not documented. For reasons of backward compatibility, 
  always one instance is placed in the block design.

- ``3`` **Global PWM timing:**
  In this section the PWM/ADC/ISR interaction is configured.

  ``INTERRUPT_ISR_SOURCE_USER_CHOICE``: Select the signal source that triggers ADC conversions and ISR. The dropdown menu provides 
  PWM events from 2L and 3L PWM and their respective triangle counters. Default is Interrupt_2L_min.

  ``INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY``: Select either immediate ISR triggering at the selected PWM 
  event or only after writing ADC results to the tightly coupled memory (TCM) has finished. Immediate ISR triggering might 
  lead to a race condition. When ISR reads ADC results from the TCM it is not guaranteed that the latest results are already written. 
  To enforce deterministic behavior, select the ``axi2tcm_write_done`` option.

  ``INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE``: Select if every PWM event from **INTERRUPT_ISR_SOURCE_USER_CHOICE** should trigger
  ADC conversion and ISR or if ISR should only be triggered every N-th PWM event. E.g., if you need 100 kHz PWM frequency or a fast 
  control loop within the FPGA but your code in the ISR cannot be computed within 10 microseconds you might find it useful to set this 
  ratio to 10U to maintain ISR execution only at every 10th PWM event (equals 10 kHz), while PWM frequency is 100 kHz. Default is 1U.

  ``ADC_TRIGGER_DELAY_IN_US``: Specifically delays the ADC conversion, i.e. the **trigger_conversions** signal in the block design, by
  the configured time in microseconds. Default is 0.01f.

  ``UZ_PWM_FREQUENCY``: Configure the global PWM frequency in Hz. Default is 10.0e3f (10 kHz).

  ``UZ_PWM_DEADTIME_IN_US``: Configure the global deadtime value in microseconds for the interlock and deadtime modules of the 
  2L PWM. Default is 1.0f.

  ``UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US``: Configure the minimum pulse width in microseconds that the 2L PWM modules are allowed to generate. 
  Every duty-cycle input that leads to a pulse width below this minimum will result in no output pulse of the PWM module.
  Default is 0.5f.

- ``4`` **Project-level enable:**
  Selects the source signal in the block design that enables the 3L PWM module. 2L PWM modules are enabled/disabled over AXI4Lite commands 
  via IP core driver functions.

Adapter Cards
-------------

The Adapter cards page selects the cards installed in A and D slots.

For each slot, the selected card determines:

* generated Vivado hierarchy;
* IP cores;
* constraints;
* AXI interfaces;
* default CPLD program;
* available software drivers;
* available visualization signals.

Some cards expose additional options in the card detail view.
Examples include IO-card direction variants, resolver PL-interface checkboxes, absolute encoder channel types, and incremental encoder channel enable selections.

.. figure:: img/page_references/adapter_cards.png
   :width: 800
   :align: center

   Adapter Cards - Detailed view

The settings, especially the IO-card options, are explained in more detail below.

- ``1`` **Adapter card slots:** For each of the eight adapter card slots (3x analog, 5x digital), a dropdown menu is provided 
  for selecting the adapter that is placed in the respective slot. Only compatible adapter cards are selectable for each slot. E.g., 
  UZ_D Voltage 3V3/5V cannot be selected for slot D5, but for D1 to D4. Make the selection according to your physical UltraZohm setup.

- ``2`` **Selected card details:** Depending on the selected adapter card, additional information or configurable options are shown in this section. 
  In the case of ADC cards it is mainly information, for the incremental encoder card the user can select board revision and up to three encoders. In the 
  case of voltage or optical IO cards several options exist that will be described in further detail below at the example of the UZ_D Voltage 3V3/5V 
  adapter card.

- ``3`` **DIG IO xx-yy direction:** The 30 IO pins are organized in four IO groups per adapter card. Each group can be configured to ``TX output from FPGA`` 
  or ``RX input to FPGA``. 
  
  .. warning:: This selection affects the Vivado block design and software implementation and not the hardware setup of the adapter card itself. On the adapter card the matching configuration of the respective dip switches has to be done manually.

- ``4`` **IO source and sink:** In this section the mode and signal routing of each pin (Dig_00_Chx to Dig_29_Chx) is configured. The pins are listed top to bottom. 
  The selected direction is highlighted via the blue ``TX`` or ``RX`` indicators.

  ``Mode``: 
  
  For ``TX`` pins one out of four options can be selected:

  - ``AXI GPIO``: The pin is controlled via an AXI-GPIO IP core. The respective software driver will be instantiated and the output is made available 
    to the user in isr.c on the R5 processor. 
  - ``PWM``: The pin is connected to one of the configured 2L or 3L PWM instances.
  - ``Custom BD source``: The pin is connected to a specific signal from the block design. 
    This can be any available signal, e.g. PWM counter events, conversion triggers, debug signals, inputs from another IO card, ... .
    Assignment is done as a string in the ``Signal`` section.
  - ``Constant``: The pin is set to a constant value. ``High`` or ``Low`` are assigned via the dropdown menu in the ``Constant value`` section.

  For ``RX`` pins one out of two options can be selected:

  - ``AXI GPIO``: The pin is routed to an AXI-GPIO IP core. The respective software driver will be instantiated and the input signal is made available 
    to the user in isr.c on the R5 processor and in the ``Data visualization`` section.
  - ``Top-level port``: The pin is made available in the Vivado block design as top-level port of the respective D-slot hierarchy. From there, one can use 
    the signal for further processing within the block design.
  
  ``Signal``: 
  
  Depending on the selected mode (``PWM`` or ``Custom BD source``), the signal source is configured in this section.

  - ``PWM``: Two dropdown menus appear when PWM mode is selected for the pin. In the first one, one of the PWM instances that have been configured in the 
    ``PWM / Timing Interrupts`` section can be selected. In the second dropdown menu the specific output pin of the PWM instance is selected for the pin. 
    Specifically, it is the output of the subsequent Interlock and Deadtime instance of the respective PWM instance. In case of the 2L PWM the signals are named 
    **s0_out** to **s5_out**, where s0_out is the top-switch switching signal of the first half-bridge, s1_out is the bottom-switch switching signal of the first half-bridge,  
    s2_out/s3_out form the pair of the second half-bridge, and so on.

  - ``Custom BD source``: The custom block design signal that should be connected to the output pin is selected via a text string that describes the hierarchical path 
    within the Vivado block design. E.g., if the trigger_conversions signal that is a top-level output of the uz_system hierarchy should be used, the string has to be 
    ``uz_system/trigger_conversions``. The same scheme applies to any other block design signal, also within sub-hierarchies. Simply provide the correct path and signal name 
    from the block design.

The described configuration details for the UZ_D Voltage 3V3/5V adapter card apply in a similar fashion to UZ_D Voltage RS422 and UZ_D Optical IO cards.

ADC Triggers
------------

The ADC triggers page configures trigger wiring between generated analog cards, AXI2TCM, and conversion trigger logic.

The defaults are intended for common generated A-slot configurations.
Only change these settings if the block design uses a different trigger source or target.

If the selected RAW-valid source is not generated by the selected A-slot cards, the wizard falls back to an available generated source where possible and reports a warning.

TCL Generation
--------------

The TCL generation page exports the generated block-design TCL and optionally executes a local Vivado workflow.

.. figure:: img/page_references/tcl_generation.png
   :width: 800
   :align: center

   TCL generation - Detailed view

- ``1`` **Local Vivado builds:**
   When checked, Vivado is executed on your local machine.
   Options include GUI mode, checkpoint workaround, validate BD, save BD, generate bitstream, and export XSA after a successful build.

   - ``Run Vivado in GUI mode``: When checked, the project wizard will execute Vivado in GUI mode and the user can visually follow the 
     execution in Vivado. When using the project wizard for the first times, seeing what is happening might give the user more trust in the workflow. 
     When not checked, Vivado is executed in the background. During execution, the hint ``Running Vivado TCL workflow...`` is shown in the lower left 
     corner of the wizard and TCL console output from Vivado is printed to the ``TCL preview warnings and workflow output`` section. 
     After successful execution a message box will appear ``Vivado finished successfully..`` only after you manually close Vivado. Default is not checked.

   - ``Disable BD/IP synthesis checkpoints``: Applies the Vivado checkpoint workaround for projects that fail while writing block-design checkpoints. 
     It has been observed when the UZ_D 3-Phase Inverter adapter card is placed that during the writing the bitstream step in the Vivado workflow an error 
     can occur regarding design checkpoints. In case this ever happens, check this option and try again. This should prevent the error from reoccurring. 
     Default is not checked.

   - ``Validate block design after applying TCL``: When checked, the validation of the block design in Vivado is executed. Normally this has to be done 
     before bitstream generation workflow. Default is checked.

   - ``Save block design after applying TCL``: When checked, the block design is saved after the project wizard's block design modifications are done. 
     Default is checked.

   - ``Generate bitstream```: When checked, the bitstream generation workflow in Vivado is executed after the modifications and the validation of the 
     block design. 

   - ``Refresh TCL Preview``: Press this button to refresh the ``TCL preview warnings and workflow output`` section.

   - ``Clear local Vivado artifacts``: When working on different git branches in your locally cloned repository some of the untracked Vivado cache files and 
     artifacts can become inconsistent to the tracked Vivado project file and block design. This leads to error messages when opening the Vivado project or the block design. 
     In order to prevent that, pressing this button deletes the cache files and artifacts. A confirmation dialog explicitly tells which folders and files will be deleted. 

     **Recommendation: Clear local Vivado artifacts before working on the Vivado project or block design.**

   - ``Execute TCL workflow``: Press this button to execute the local Vivado workflow with the selected options. A save dialog appears within the folder ``/generated/vivado_bd_config/``. 
     Here, the TCL file ``project_wizard_config.tcl`` will be saved that handles the block design modifications. After saving it the local Vivado build starts.

- ``2`` **Remote workstation builds:**
   When checked, only the TCL file for execution in the Vivado block design is exported for use on another workstation or remote computer. 
   
   - ``Export TCL``: A save dialog appears within the folder ``/generated/vivado_bd_config/``. 
     Here, the TCL file ``project_wizard_config.tcl`` will be saved that handles the block design modifications. You have to 
     copy the TCL file to your remote computer. There, open Vivado and the UltraZohm project ``ultrazohm_sw/vivado/project/ultrazohm.xpr``. 
     Open the block design. Execute the TCL script ``project_wizard_config.tcl`` via ``Tools -> Run TCL script....```.
   
     **After the TCL script finished you will need to manually validate the block design, start bitstream generation, and export the resulting .xsa file.**

- ``3`` **TCL preview warnings and workflow output:** The preview warning section reports potential generation issues before the TCL is executed.
  If there are no warnings, the wizard reports that no TCL preview warnings were found. During local Vivado execution the Vivado TCL console outputs are 
  printed in this section.

Slot CPLDs
----------

The Slot CPLDs page generates Lattice Diamond Programmer ``.xcf`` files from the selected digital slot CPLD programs.
A command-line (CLI) execution of the Diamond Programmer is available to directly program the D-slot CPLDs of UltraZohm revisions 5 and newer 
from the project wizard. 

.. figure:: img/page_references/slot_cplds.png
   :width: 800
   :align: center

   Slot CPLDs - Detailed view

- ``1`` **Digital slot CPLD programs:** The selected adapter card usually determines the default CPLD program and in the background also the 
  correct CPLD device (ispMACH LA4128, LV4256 or MACHXO2). Users can inspect or override the selection before generating programmer files. When 
  ``No CPLD program`` is selected for a slot, this specific slot is set to ``Bypass`` in the Diamond Programmer.

- ``2`` **Lattice cable settings:** Diamond Programmer needs the correct cable settings for executing programming via the CLI. 
  Best practice is either to look them up by following the manual CPLD programming workflow and put them into the wizard text fields or to use 
  the ``Cable setup recovery`` if you have a local Diamond Programmer .xcf project file that contains the correct settings for your setup. 
  For the recovery workflow check the respective checkbox and press ``Import cable settings from XCF``. In the dialog navigate to the project file that 
  contains working settings and select it. The settings are read from the project file and written into the wizard fields. 
  Additionally, the ``CPLD programmer output`` section reports the settings that have been exported from the existing .xcf file.

- ``Write Lattice Diamond Programmer project file``: A save dialog appears within the folder ``/generated/cpld_config/`` folder when 
  pressing this button. Here, the XCF file ``project_wizard_slot_cpld.xcf`` will be saved that is a complete Diamond Programmer project containing 
  the selected D-slot CPLD configuration. After saving the file, the ``Programm CPLDs via CLI`` button gets activated.

- ``Programm CPLDs via CLI``: Pressing this button executes the programming of the D-slot CPLDs via the Diamond Programmer CLI. 
  The UltraZohm has to be connected to your computer and has to be powered on (LED ring around the Power button is green). 
  Other tools that might occupy the JTAG interface, e.g. Vivado/Vitis, have to be closed. Be aware that the CLI workflow is only 
  tested with MACHXO2 CPLDs that are used from UltraZohm Rev05 and higher. While execution of the CLI workflow, The console outputs of the 
  Diamond Programmer are printed to the ``CPLD programmer output`` section.

Software General
----------------

The software General page selects the Vitis bare-metal source folder.
This is selected automatically by the wizard and should point to ``/$yourClonedRepoFolder/vitis/software/Baremetal/src/``.

IP Core Driver Setup
--------------------

This page exposes software-driver instances derived from the current hardware and software configuration.

.. figure:: img/page_references/ip_core_driver_setup.png
   :width: 800
   :align: center

   IP Core Driver Setup - Detailed view

- ``1`` **Slot software integration:**
  
  - ``Mode``: For every adapter card slot it can be selected if a software driver that matches the selected adapter card is used ``Follow hardware selection`` 
    or if no software integration should be used at all ``No software driver``. Default is ``Follow hardware selection``.
  - ``Preset``: Most adapter cards provide one default driver preset. E.g. the UZ_D Temperature LTC2983 adapter card provides two presets, depending 
    on the type of temperature sensors. For all other adapter cards use the default preset option.

- ``2`` **Software generation preview:** The preview reports the exact source files and the specific code that will be modified by the wizard. The modification is based on markers 
  in those source files. The wizard only modifies content between those markers. For details see :ref:`project_wizard_generated_outputs` section of the project wizard docs. 

- ``Generate software files``: When pressing this button, the selected PWM / Timing / Interrupt options, the IP core driver setup, the Advanced driver configuration, and 
  the Data visualization options are written to the source code. This button is mirrored to the ``Advanced driver options`` section and ``Data visualization`` section for convenience. 
  When software file generation is executed, the ``Software generation output`` section at the very bottom of the view will report the successful source code modifications.
  
  **Recommendation: Finish IP core driver setup, Advanced driver configuration and Data visualization sections first before pressing Generate software files in order to write a completely configured 
  set of code changes to the source code.**

Advanced driver options
-----------------------

Initially, all advanced driver options are set to ``Default``.
The tabs for  ``PWM``  and the adapter card slots ``A1-A3``, and ``D1-D5`` mainly reflect the config structs of the software drivers 
of the selected PWM instances and adapter card hardware. Go through the tabs and set the ``Config mode`` to ``Custom`` 
whenever you need to change config values. See the respective IP core driver documentation for specific details of each driver.

.. warning:: Wrong custom values can produce compiling errors or compiling code with incorrect runtime behavior.

- ``Generate software files``: When pressing this button, the selected PWM / Timing / Interrupt options, the IP core driver setup, the Advanced driver configuration, and 
  the Data visualization options are written to the source code. This button is mirrored to the ``Advanced driver options`` section and ``Data visualization`` section for convenience. 
  When software file generation is executed, the ``Software generation output`` section at the very bottom of the view will report the successful source code modifications.
  
  **Recommendation: Finish IP core driver setup, Advanced driver configuration and Data visualization sections first before pressing Generate software files in order to write a completely configured 
  set of code changes to the source code.**

Data Visualization
------------------

The Data visualization page selects which generated signals are registered for Javascope and slow data.

Available signals depend on the respective IP core drivers.
If a card or channel does not provide software signals, it is indicated by ``No generated visualization signals for Dx.``.

- ``Generate software files``: When pressing this button, the selected PWM / Timing / Interrupt options, the IP core driver setup, the Advanced driver configuration, and 
  the Data visualization options are written to the source code. This button is mirrored to the ``Advanced driver options`` section and ``Data visualization`` section for convenience. 
  When software file generation is executed, the ``Software generation output`` section at the very bottom of the view will report the successful source code modifications.
  
  **Recommendation: Finish IP core driver setup, Advanced driver configuration and Data visualization sections first before pressing Generate software files in order to write a completely configured 
  set of code changes to the source code.**
