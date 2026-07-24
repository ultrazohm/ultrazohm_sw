from pathlib import Path

import pyuzlib


SCRIPT_DIR = Path(__file__).resolve().parent
FLUX_MAP_CSV = SCRIPT_DIR / "flux_map_raw_from_fem.csv"


motor = pyuzlib.pmsm.PMSM()
motor.load_flux_map_csv(FLUX_MAP_CSV,i_d_col="I_d", i_q_col="I_q", psi_d_col="Psi_d", psi_q_col="Psi_q")
motor.calculate_differential_inductances()
motor.export_flux_map_csv(SCRIPT_DIR / "flux_map.csv")
motor.export_differential_inductances_csv(SCRIPT_DIR / "differential_inductances.csv")

motor.plot_differential_inductances()
motor.plot_flux_map()
