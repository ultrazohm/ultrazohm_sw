# xZohm Project Wizard

First sketch for a PyQt based configuration helper for UltraZohm projects.

The first workflow is intentionally small:

1. Select which adapter card is installed in each UltraZohm slot.
2. Store adapter card metadata in a git-trackable JSON database.
3. Generate a first Vivado TCL script draft from the selected configuration.

The generated TCL is a scaffold, not yet a replacement for the manual Vivado
flow. The next useful step is to refine the Vivado entries in
`data/adapter_cards.json` until each card describes the exact IP cores, pins,
ports, interfaces, constraints and software driver snippets it needs.

## Run

Install PyQt6 in your Python environment:

```powershell
pip install -r requirements.txt
```

Start the sketch:

```powershell
python .\main.py
```

On Windows, you can also double-click `run_xzohm_project_wizard.bat`.

## Files

- `main.py`: PyQt GUI prototype.
- `data/adapter_cards.json`: Git-trackable card/IP metadata database.
- `data/platforms.json`: Git-trackable platform revisions and project-level AXI defaults.
- `generated/`: Output folder for generated TCL scripts.

## Data Model Idea

Each card entry contains:

- Basic identification: `id`, `name`, `family`, `description`.
- Slot compatibility: e.g. `["D1", "D2", "D3", "D4"]`.
- Vivado information: IP instances, interface pins, external ports and notes.
- Vitis information: driver name and files that should eventually be patched or generated.

The GUI already supports adding simple database entries. More advanced card
definitions can be edited directly in JSON until the editor grows into a richer
form.
