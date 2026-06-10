from pathlib import Path

import pyuzlib


dataset_dir = Path(__file__).resolve().parent
flux_map_csv = dataset_dir / "flux_map.csv"
coefficient_csv = dataset_dir / "coefficient.csv"

coefficient_table = pyuzlib.docs.pmsm.L_dd_L_qq_from_flux_map_assuming_no_saturation(flux_map_csv)
coefficient_table.to_csv(coefficient_csv, index=False)

print(f"Wrote {coefficient_csv}")