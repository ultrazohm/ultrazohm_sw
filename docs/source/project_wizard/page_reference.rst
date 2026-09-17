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

  ``INTERRPUT_ISR_TRIGGER_ON_ADC_DATA_READY``: Select either immediate ISR triggering at the selected PWM 
  event or only after writing ADC results to the tightly coupled memory (TCM) has finished. Immediate ISR triggering might 
  lead to a race condition. When ISR reads ADC results from the TCM it is not guaranteed that the latest results are already written. 
  To enforce this, select the ``axi2tcm_write_done`` option.

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

ADC Triggers
------------

The ADC triggers page configures trigger wiring between generated analog cards, AXI2TCM, and conversion trigger logic.

The defaults are intended for common generated A-slot configurations.
Only change these settings if the block design uses a different trigger source or target.

If the selected RAW-valid source is not generated by the selected A-slot cards, the wizard falls back to an available generated source where possible and reports a warning.

TCL Generation
--------------

The TCL generation page exports the generated block-design TCL and optionally executes a local Vivado workflow.

Local Vivado builds
   Runs Vivado on the local machine.
   Options include GUI mode, checkpoint workaround, validate BD, save BD, generate bitstream, and export XSA after a successful build.

Remote workstation builds
   Exports the TCL for use on another workstation.

The preview warning section reports potential generation issues before the TCL is executed.
If there are no warnings, the wizard reports that no TCL preview warnings were found.

Disable BD/IP synthesis checkpoints
   Applies the Vivado checkpoint workaround for projects that fail while writing block-design checkpoints.

These values affect TCL export and local Vivado execution.

Slot CPLDs
----------

The Slot CPLDs page generates Lattice Diamond Programmer ``.xcf`` files from the selected digital slot CPLD programs.

The selected adapter card usually determines the default CPLD program.
Users can inspect or override the selection before generating programmer files.

The command-line execution path requires a configured Programmer executable on the Toolchain page.

Software General
----------------

The software General page selects the Vitis bare-metal source folder.
The folder must contain the files patched by the wizard, especially ``globalData.h``.

Each slot can follow the hardware selection or generate no software driver.
Selecting no software driver clears slot-owned generated integration for that slot.

IP Core Drivers Setup
---------------------

This page exposes software-driver instances derived from the current hardware and software configuration.

Each driver instance can use:

Default
   Preset-generated configuration values.

Custom
   User-edited configuration fields for that instance.

Use custom values only when the application requires them.
Wrong custom values can produce compiling code with incorrect runtime behavior.

Data Visualization
------------------

The Data visualization page selects which generated signals are registered for Javascope and slow data.

Available signals depend on the generated software model.
If a card or channel does not generate a software signal, it is not shown here.

Adapter Card Database
---------------------

The Adapter Card Database page is intentionally read-only for the first wizard release.
The JSON catalog remains the source of truth.

Do not rely on this page to add or edit cards.
Adding new cards is a developer workflow described in :ref:`project_wizard_developer_guide`.

