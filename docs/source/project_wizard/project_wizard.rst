.. _project_wizard:

===============
Project Wizard
===============

The Project Wizard is a graphical configuration tool for UltraZohm Vivado and Vitis projects.
It helps users configure platform revision, adapter cards, PWM/timing, ADC trigger wiring, generated TCL, CPLD programmer files, and software-driver integration from one saved project configuration.

The wizard is intended to support the regular UltraZohm repository workflow.
It does not replace Vivado, Vitis, or the adapter-card documentation, but it automates the repetitive project integration steps that are easy to get wrong by hand.

Start The Wizard
****************

The wizard is located in ``project_wizard/``.

On Windows, start it with:

.. code-block:: powershell

   cd project_wizard
   .\run_project_wizard.bat

On Linux, start it with:

.. code-block:: bash

   cd project_wizard
   ./start_project_wizard.sh

The wizard stores user-owned configuration files in ``project_wizard/user_configurations/``.
The default file extension is ``.pw.json``.

Recommended Workflow
********************

1. Select the UltraZohm platform revision on the **Platform** page.
2. Select the Vivado project file and block-design name on the hardware **General** page.
3. Configure **PWM / Timing / Interrupts**.
4. Select adapter cards and card-specific options on the **Adapter cards** page.
5. Configure **ADC triggers** if the default trigger wiring is not suitable.
6. Use **TCL generation** to export and execute the block-design TCL.
7. Generate or execute CPLD programmer files on the **Slot CPLDs** page if digital adapter cards require CPLD updates.
8. Select the Vitis software source folder on the software **General** page.
9. Configure generated software drivers, visualization signals, and advanced driver options.
10. Press **Generate software files** and rebuild the Vitis workspace.

After changing hardware options that affect the block design, regenerate and rerun the TCL before regenerating software.
The software generator reads base-address macros from ``xparameters.h``, therefore the Vitis workspace must match the currently generated bitstream.

Generated Output Folders
************************

The wizard keeps generated files below ``project_wizard/generated/``:

``vivado_bd_config/``
   Generated Vivado block-design TCL.

``vivado_run_scripts/``
   Helper scripts used by the local Vivado workflow.

``cpld_config/``
   Generated Lattice Diamond Programmer ``.xcf`` files.

``logs/``
   Local workflow logs.

``golden_scenarios/``
   Developer regression baselines for representative wizard configurations.

Saved user configurations are not generated output and live in ``project_wizard/user_configurations/``.

Wizard Ownership
****************

The wizard owns selected parts of the Vivado block design and selected marker blocks in the Vitis software project.
This distinction is important when combining wizard-generated content with manual project changes.

In Vivado, the wizard owns:

* selected ``A1`` to ``A3`` adapter-slot hierarchies below ``uz_analog_adapter``;
* selected ``D1`` to ``D5`` adapter-slot hierarchies below ``uz_digital_adapter``;
* the generated ``uz_pwm`` hierarchy;
* slot-local AXI SmartConnect attachment and cleanup for wizard-controlled slots.

The wizard assumes that the surrounding UltraZohm base design exists, for example ``uz_system``, ``uz_user``, ``uz_analog_adapter``, and ``uz_digital_adapter``.
Manual content outside wizard-owned slot hierarchies may stay in the design.

The adapter-card slot selection has three relevant meanings:

``Bypass``
   Leave the slot untouched.
   The wizard does not clean or modify this slot.

``No adapter board``
   Clean wizard-owned content for this slot, including stale slot-local AXI integration.

Selected adapter card
   Generate the selected card.
   If the selected card does not need AXI, stale wizard-owned AXI content for that slot is removed.

Software Generation
*******************

The software generator writes slot-specific init files and patches shared Vitis files only inside Project Wizard marker blocks.
Typical patched files include:

* ``globalData.h``
* ``main.c``
* ``sw/isr.c``
* ``include/javascope.h``
* ``sw/javascope.c``
* ``uz/uz_global_configuration.h``
* ``IP_Cores/uz_dataMover/uz_dataMover.c``

Generated slot files are written to ``include/*_adapter_init.h`` and ``hw_init/*_adapter_init.c``.
The wizard also generates helper files such as ``include/pwm_init.h``, ``hw_init/pwm_init.c``, and ``project_wizard_visualization`` files when needed.

Some generated sections are intentionally user-owned.
For example, AXI GPIO output blocks in ``isr.c`` are inserted once and preserved on later regeneration.
Normal Project Wizard marker blocks are regenerated from the current wizard configuration.

Visualization
*************

The wizard can register generated signals for:

* Javascope observable signals;
* slow-data signals;
* both paths at the same time.

Signals are offered depending on the selected hardware and software-driver configuration.
For example, ADC values, temperature channels, resolver values, encoder values, DAC command values, inverter status values, and AXI GPIO input pins become available only when the respective generated software path exists.

Local And Remote Vivado Workflows
*********************************

The **TCL generation** page separates two workflows:

``Local Vivado builds``
   Export the TCL, optionally clear local Vivado artifacts, and execute the TCL directly with the configured Vivado installation.
   The local workflow can validate and save the block design, run Vivado in GUI mode, generate a bitstream, and export an ``.xsa`` after a successful build.

``Remote workstation builds``
   Export the generated TCL so it can be copied to or executed on another workstation.

The **Clear local Vivado artifacts** action removes common local Vivado cache/build artifacts such as ``.Xil``, ``*.cache``, ``*.runs``, ``*.sim``, and ``*.gen`` folders.
This can fix stale-IP or stale-block-design errors after switching branches or changing generated Vivado content.

CPLD Programmer Files
*********************

The **Slot CPLDs** page generates Lattice Diamond Programmer ``.xcf`` files for selected digital slot CPLD programs.
The generated file can also be executed through the Diamond Programmer command-line interface if the toolchain path is configured.

For older ispMACH CPLDs, the command-line workflow may be limited compared to the graphical Diamond Programmer workflow.
If CLI programming fails for older CPLDs, use the generated ``.xcf`` as a starting point in Diamond Programmer.

Adapter-Card Database
*********************

The Adapter Card Database page is intentionally read-only for the first wizard release.
The card catalog in ``project_wizard/data/adapter_cards.json`` remains the source of truth.

Adding or changing adapter cards should be handled as a developer task:

* update the JSON catalog;
* add or update TCL/software templates;
* update related documentation;
* run the wizard regression checks.

Developer Checks
****************

After changing wizard source files, run:

.. code-block:: powershell

   python -m json.tool project_wizard\data\adapter_cards.json
   python -m json.tool project_wizard\data\software_drivers.json
   python -m compileall project_wizard
   python -m project_wizard.golden_scenarios --check

The golden scenario check compares representative generated TCL and software summaries against stored baselines.
It is a useful smoke test, but it does not replace Vivado execution or hardware testing.
