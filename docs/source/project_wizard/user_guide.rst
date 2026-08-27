.. _project_wizard_user_guide:

User Guide
==========

The Project Wizard uses one saved configuration to derive hardware generation, CPLD programmer files, and software integration.
The central idea is that the user describes the intended UltraZohm setup once, and the wizard generates the repetitive wiring and software boilerplate from that description.

Mental Model
------------

The wizard has three layers:

Configuration
   The saved ``.pw.json`` file records platform, slots, timing, trigger wiring, tool paths, software choices, and driver options.

Resolved system model
   The wizard resolves the configuration against its card, platform, and software-driver catalogs.
   This produces facts such as selected IP cores, AXI interfaces, visualization signals, and CPLD defaults.

Generated outputs
   The generated Vivado TCL, CPLD programmer files, and Vitis software patches are created from the resolved model.

The user normally interacts only with the GUI and the saved configuration.
The generated outputs can be inspected and committed when they are part of the intended project state.

Hardware Before Software
------------------------

Hardware generation should be done before software generation.
The software generator reads base-address macros from ``xparameters.h``.
Those macros are produced by the Vitis platform generated from the Vivado hardware.

Recommended order:

1. Configure hardware in the wizard.
2. Generate and execute the Vivado TCL.
3. Build or update the bitstream.
4. Export or update the Vitis hardware platform.
5. Generate wizard software integration.
6. Build the Vitis software.

If hardware is changed later, repeat the hardware and software generation steps.

Slot Semantics
--------------

Adapter-card slot choices have explicit meanings.

Bypass
   The wizard leaves the slot untouched.
   It does not clean the slot and does not repair stale content.
   Use this when a slot contains manual design content that should not be affected.

No adapter board
   The wizard removes wizard-owned content from the slot.
   This includes stale slot-local AXI integration.
   Use this when a physical slot is empty or when a previously generated card should be removed.

Selected adapter card
   The wizard generates the selected card content.
   If the new card does not need AXI, stale wizard-owned slot-local AXI content is removed.

The distinction between **Bypass** and **No adapter board** is important.
Bypass is a preservation mode, not a cleanup mode.

Local And Remote Builds
-----------------------

The TCL generation page supports two workflows.

Local Vivado builds
   The wizard exports TCL, writes a Vivado wrapper script, and starts the locally configured Vivado executable.
   This is useful when the repository and toolchain are available on the same machine.

Remote workstation builds
   The wizard exports TCL for use on another workstation.
   This is useful when the GUI is run locally but Vivado builds happen elsewhere.

Both workflows use the same generated block-design TCL.
The difference is only how the TCL is executed.

Software Driver Modes
---------------------

On the software pages, each slot can either follow the selected hardware or generate no software driver.
This allows the hardware and software integration to be separated for unusual development cases.

Driver configuration normally uses **Default**.
Use **Custom** only when an instance-specific configuration value should be written into the generated driver init code.

Visualization
-------------

Visualization options are generated from the selected hardware and software configuration.
Only signals that exist in the generated software model are offered.

A signal can be routed to:

* Javascope observable signals;
* slow data;
* both;
* neither.

Non-float values are converted by generated helper code before they are passed to float-based visualization paths.
Boolean values are represented as ``1.0f`` or ``0.0f``.

Saving And Reusing Configurations
---------------------------------

Saved configurations live in ``project_wizard/user_configurations/``.
They are normal JSON files with the extension ``.pw.json``.

Save configurations for setups that should be reproducible later.
When reopening an old configuration, refresh the previews before generating files so missing paths or invalid options become visible early.

