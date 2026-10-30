#include "../include/pmsm_cil.h"

struct uz_pmsmModel_config_t pmsm_cil_config={
  .base_address=XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR,
  .ip_core_frequency_Hz=100000000,
  .simulate_mechanical_system = false,
  .r_1 = 0.51f,
  .L_d = 0.00175f,
  .L_q = 0.00175f,
  .psi_pm = 0.042f,
  .polepairs = 4.0f,
  .inertia = 0.000108f,
  .coulomb_friction_constant = 0.01f,
  .friction_coefficient = 0.001f
};

uz_pmsmModel_t* initialize_uz_pmsm_cil(void) {
	return uz_pmsmModel_init(pmsm_cil_config);
}

struct uz_pmsm_measurement_values pmsm_cil_get_control_measurements(
    struct uz_pmsmModel_outputs_t outputs,
    struct uz_pmsmModel_inputs_t applied_inputs, float dc_link_voltage_V)
{
    uz_3ph_dq_t currents = {.d = outputs.i_d_A, .q = outputs.i_q_A, .zero = 0.0f};
    uz_3ph_dq_t voltages = {.d = applied_inputs.v_d_V, .q = applied_inputs.v_q_V, .zero = 0.0f};
    struct uz_pmsm_measurement_values measurements = {
        .i_abc_in_A = uz_transformation_3ph_dq_to_abc(currents, 0.0f),
        .v_abc_in_V = uz_transformation_3ph_dq_to_abc(voltages, 0.0f),
        .omega_mech_rad_per_sec = outputs.omega_mech_1_s,
        .theta_mech = 0.0f,
        .v_dc_in_V = dc_link_voltage_V,
        .i_dc_in_A = 0.0f
    };
    return measurements;
}
