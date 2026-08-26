# Project Wizard

PyQt-based configuration helper for UltraZohm Vivado/Vitis projects.

The wizard guides the user through platform, adapter-card, PWM/timing, ADC-trigger,
TCL, CPLD, and software-driver configuration. It can generate Vivado block-design
TCL, local Vivado run scripts, Lattice Diamond Programmer `.xcf` files, and
marker-based Vitis software integration files.

## Run

Install the Python dependencies:

```powershell
pip install -r requirements.txt
```

Start the wizard:

```powershell
python .\main.py
```

On Windows, `run_project_wizard.bat` can also be used. On Linux, use
`start_project_wizard.sh`.

## Architecture

The application boundary is model-first:

```text
GUI widget state
  -> SystemConfig
  -> ResolvedSystemModel
  -> TCL/software/CPLD services
```

Important files:

- `models.py`: typed project configuration and resolved model dataclasses.
- `services/system_resolver.py`: resolves a `SystemConfig` against the card/platform catalogs.
  It owns card-derived CPLD defaults, resolved software-driver instance discovery,
  available visualization signal discovery, analog datamover stream facts, and
  slot-local AXI cleanup/attachment facts.
- `services/visualization_catalog.py`: shared visualization signal and IO-card
  direction/AXI helper functions used by resolver and generators.
- `tcl_generator.py`: model-based Vivado TCL generator.
- `services/software_generator_service.py`: model-based Vitis software integration generator.
- `services/software_analog.py`: analog-card software contexts, ADC readout
  snippets, ADC packed-buffer offsets, and DAC wavegen helper logic.
- `services/software_models.py`: software-generation plan dataclasses, marker
  definitions, and small shared constants.
- `services/software_driver_config.py`: reusable driver-configuration value
  resolution for default/custom advanced driver options.
- `services/software_digital.py`: digital-card software contexts and generated
  snippets for inverter, incremental encoder, absolute encoder, and resolver
  integrations.
- `services/software_patcher.py`: marker-based Vitis file patching and
  generated software file writes.
- `services/software_pwm.py`: PWM software config fields, PWM init context,
  PWM runtime ISR lines, and PWM-owned RASV duty-cycle entries.
- `services/software_temperature_io.py`: temperature-card software context,
  temperature readout snippets, and AXI GPIO IO-card context.
- `services/software_visualization.py`: formatting of generated visualization
  fields, Javascope observable entries, and slow-data entries.
- `services/xparameters.py`: `xparameters.h` discovery and generated
  base-address/device-id macro selection.
- `views/main_window.py`: main application shell, menu, service wiring, and page registration.
- `views/mixins/`: focused GUI page/workflow modules used by `MainWindow`.

Generators receive a `ResolvedSystemModel` at their public boundary. Some
private generator internals still use the historical flat value shapes to
preserve tested rendering behavior; those values are exposed only through the
explicit `SystemConfig.legacy_generator_values()` bridge.

## Data And Output

- `data/adapter_cards.json`: source of truth for adapter-card hardware metadata.
- `data/platforms.json`: source of truth for platform revisions and AXI defaults.
- `data/software_drivers.json`: source of truth for software-driver templates and options.
- `user_configurations/`: saved user-owned `.pw.json` configuration files.
- `generated/vivado_bd_config/`: generated Vivado block-design TCL.
- `generated/vivado_run_scripts/`: generated local Vivado helper scripts.
- `generated/cpld_config/`: generated CPLD programmer project files.
- `generated/logs/`: local workflow logs.
- `generated/golden_scenarios/`: regression baselines for representative configurations.

Project configuration files use schema version 2 and are loaded through
`SystemConfig`. Older schema versions are intentionally not supported.

## Adapter-Card Database

The Adapter Card Database page is intentionally read-only for v1 and marked
under construction. The JSON catalog remains the source of truth. New cards or
card changes should be made as developer changes in `adapter_cards.json`,
software templates, and supporting documentation, then verified with the golden
scenario check.

`views/card_editor.py` is an unused draft editor kept only as reference code. It
is not wired into the GUI because it is not schema-complete enough for safe
catalog editing.

## Verification

Useful checks after wizard changes:

```powershell
python -m json.tool project_wizard\data\adapter_cards.json
python -m json.tool project_wizard\data\software_drivers.json
python -m compileall project_wizard
python -m project_wizard.golden_scenarios --check
```

The golden scenario check compares representative generated TCL and software
summaries against stored baselines. It is a smoke/regression check, not a
replacement for Vivado execution or hardware testing.

## Current Boundary

The highest-risk behavior remains dirty-block-design AXI cleanup/attachment in
Vivado. The facts are resolved in `system_resolver.py` and rendered by
`tcl_generator.py`, with golden scenarios protecting generated output. Changes
there should still be paired with manual Vivado transition tests, especially AXI
card to `No adapter board`, AXI card to non-AXI card, and dirty legacy slot
content to selected AXI card.
