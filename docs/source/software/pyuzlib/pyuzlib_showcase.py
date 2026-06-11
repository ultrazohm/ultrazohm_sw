from pathlib import Path
import plotly.io as pio

pio.renderers.default = "vscode"
import pyuzlib


PARAMETER_CSV = Path(
    "/workspaces/ultrazohm_sw/docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/machine_parameters.csv"
)
FLUX_MAP_CSV = Path("/workspaces/ultrazohm_sw/docs/source/software/control/uz_pmsm/beckhoff_AM8141-0j00-000/measured_psi_dq_averaged_800_rpm/flux_map.csv")


motor = pyuzlib.pmsm.PMSM()

parameters = motor.load_parameters_csv(PARAMETER_CSV)
print("C-compatible PMSM parameters")
print(parameters.to_c_dict())
print()

flux_map = motor.load_flux_map_csv(FLUX_MAP_CSV)
print("Canonical flux-map table")
print(flux_map.data.head())
print()

print("psi_d grid")
print(flux_map.psi_d)
print()

fit = motor.fit_linear_flux_model(fit_name="Dummy motor linear flux fit")
print("Linear flux-model fit")
print(fit)
print()

motor.update_parameters(Torque_rated_Nm=1.2, speed_rated_rpm=1000.0)
print("Additional non-C parameters kept with the PMSM object")
print(motor.parameters.additional_parameters)
print()

parameter_export =  "pmsm_parameters.csv"
flux_map_export =  "flux_map_canonical.csv"
fit_export =  "linear_flux_fit.csv"

# motor.export_parameters_csv(parameter_export)
# motor.export_flux_map_csv(flux_map_export)
# motor.export_result_csv("linear_no_saturation", fit_export)

print("CSV exports")
print(parameter_export)
print(flux_map_export)
print(fit_export)
print()

figure = motor.plot_flux_map_plotly()
figure.show()

fig2=motor.plot_flux_map()
print(fig2)