# Project Wizard

PyQt based configuration helper for UltraZohm projects.

The wizard supports the main project configuration workflow:

1. Select which adapter card is installed in each UltraZohm slot.
2. Store adapter card metadata in a git-trackable JSON database.
3. Generate and optionally execute Vivado TCL from the selected configuration.
4. Generate CPLD programmer projects and run CPLD programming through the CLI.
5. Generate software driver integration files for the selected hardware setup.

## Run

Install PyQt6 in your Python environment:

```powershell
pip install -r requirements.txt
```

Start the wizard:

```powershell
python .\main.py
```

On Windows, you can also double-click `run_project_wizard.bat`.

## Files

- `main.py`: PyQt GUI entry point.
- `data/adapter_cards.json`: Git-trackable card/IP metadata database.
- `data/platforms.json`: Git-trackable platform revisions and project-level AXI defaults.
- `user_configurations/`: Saved user-owned wizard configuration files.
- `generated/vivado_bd_config/`: Generated Vivado block-design TCL.
- `generated/vivado_run_scripts/`: Generated helper TCL for local Vivado execution.
- `generated/cpld_config/`: Generated CPLD programmer project files.
- `generated/logs/`: Local workflow log files.

## Data Model Idea

Each card entry contains:

- Basic identification: `id`, `name`, `family`, `description`.
- Slot compatibility: e.g. `["D1", "D2", "D3", "D4"]`.
- Vivado information: IP instances, interface pins, external ports and notes.
- Vitis information: driver name and generated or patched integration files.

The GUI supports adding simple database entries. Advanced card definitions can
also be edited directly in JSON.
