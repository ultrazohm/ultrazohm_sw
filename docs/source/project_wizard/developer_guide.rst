.. _project_wizard_developer_guide:

Developer Guide
===============

This page summarizes the internal architecture for developers who extend the Project Wizard.

Architecture
------------

The public generator boundary is model-based:

.. code-block:: text

   GUI widget state / saved JSON
     -> SystemConfig
     -> ResolvedSystemModel
     -> Tcl/Software/CPLD services

Important files:

``project_wizard/models.py``
   Typed configuration and resolved model dataclasses.

``project_wizard/services/system_resolver.py``
   Resolves saved configuration against card and platform catalogs.
   Owns software-driver discovery, visualization signal discovery, analog datamover facts, and AXI attachment/cleanup facts.

``project_wizard/tcl_generator.py``
   High-level Vivado TCL generator.

``project_wizard/services/software_generator_service.py``
   High-level Vitis software integration generator.

``project_wizard/services/software_patcher.py``
   Marker-based patching of Vitis files.

``project_wizard/services/visualization_catalog.py``
   Shared visualization and IO-card helper functions.

``project_wizard/data/adapter_cards.json``
   Adapter-card hardware catalog.

``project_wizard/data/software_drivers.json``
   Software-driver and advanced-driver-option catalog.

``project_wizard/data/platforms.json``
   Platform and default AXI configuration catalog.

Configuration Schema
--------------------

Project configuration files use schema version 2.
Top-level sections include:

* ``platform``;
* ``toolchain``;
* ``hardware``;
* ``slots``;
* ``cpld_programmer``;
* ``axi``;
* ``software``.

Do not reintroduce ambiguous old-style public dictionaries.
If a legacy-shaped value is still required inside a proven generator path, use the explicit compatibility bridge from ``SystemConfig``.

Adding An Adapter Card
----------------------

Typical steps:

1. Add card metadata to ``adapter_cards.json``.
2. Define compatible slots.
3. Define Vivado generation metadata, templates, IP cores, ports, constraints, and AXI interfaces.
4. Add or update TCL templates under ``project_wizard/templates/cards/``.
5. Add software-driver metadata to ``software_drivers.json`` if the card has generated software.
6. Add software templates under ``project_wizard/templates/software/`` if needed.
7. Add resolver/generator logic only where catalog-driven behavior is not enough.
8. Add visualization signal definitions if the card exposes generated software signals.
9. Add or update golden scenarios.
10. Run checks and perform Vivado execution tests.

Adding Software Driver Support
------------------------------

Software generation usually writes:

* slot-specific ``*_adapter_init.c/.h`` files;
* object pointers in ``globalData.h``;
* init calls in ``main.c``;
* runtime calls in ``sw/isr.c``;
* visualization entries when selected.

Prefer generated code that uses existing UltraZohm drivers.
Do not duplicate driver internals in wizard templates unless there is a clear reason.

Adding Visualization Signals
----------------------------

Visualization signals should be registered in ``services/visualization_catalog.py``.
Each signal defines:

* stable signal id;
* slot;
* user-facing label;
* generated enum name;
* pointer expression or source expression;
* source type.

The software visualization generator handles conversion of integer and boolean signals to float transport values.

TCL Template Rules
------------------

Use helpers from ``project_wizard/templates/helpers/bd_helpers.tcl`` whenever possible.
Do not hand-roll duplicate connection logic.

Generated TCL must not contain unresolved template syntax such as:

* ``{% if ... %}``;
* ``{% for ... %}``;
* ``{{ variable }}``.

After changing templates or the renderer, scan generated TCL and run the golden scenario check.

AXI Rules
---------

Prefer Vivado automatic address assignment.
Do not introduce fixed AXI addresses unless a system-level reason is proven.
Generated software should use final macros from ``xparameters.h``.

The resolver owns AXI interface discovery and slot cleanup facts.
The TCL generator should render those facts instead of rediscovering them from card JSON.

Golden Scenario Checks
----------------------

Golden scenarios live in ``project_wizard/generated/golden_scenarios/``.
They protect representative generated TCL and software summaries.

Run:

.. code-block:: powershell

   python -m project_wizard.golden_scenarios --check

When expected generator output changes, refresh the baselines intentionally:

.. code-block:: powershell

   python -m project_wizard.golden_scenarios

Golden checks do not replace Vivado execution or hardware tests.

Standard Checks
---------------

Run these after wizard changes:

.. code-block:: powershell

   python -m json.tool project_wizard\data\adapter_cards.json
   python -m json.tool project_wizard\data\software_drivers.json
   python -m compileall project_wizard
   python -m project_wizard.golden_scenarios --check

Remove ``__pycache__`` folders before committing if ``compileall`` created them.

Known Development Boundaries
----------------------------

The Adapter Card Database page is read-only for the first wizard release.
Do not wire the old draft card editor back into the GUI without a schema-complete redesign.

Future platform support is not just a combo-box change.
The current generator intentionally targets the UltraZohm naming and block-design architecture.
MicroZohm or Kria support needs a deliberate platform abstraction.

