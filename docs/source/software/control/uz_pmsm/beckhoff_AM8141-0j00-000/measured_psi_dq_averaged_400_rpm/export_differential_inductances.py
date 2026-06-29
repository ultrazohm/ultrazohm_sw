from pathlib import Path

import pyuzlib


SCRIPT_DIR = Path(__file__).resolve().parent
FLUX_MAP_CSV = SCRIPT_DIR / "flux_map.csv"
DIFFERENTIAL_INDUCTANCES_CSV = SCRIPT_DIR / "differential_inductances.csv"


motor = pyuzlib.pmsm.PMSM()
motor.load_flux_map_csv(FLUX_MAP_CSV)
motor.calculate_differential_inductances()
motor.export_differential_inductances_csv(DIFFERENTIAL_INDUCTANCES_CSV)

print(f"Exported {DIFFERENTIAL_INDUCTANCES_CSV}")
