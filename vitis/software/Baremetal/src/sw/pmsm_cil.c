#include "../include/pmsm_cil.h"
#include "../uz/uz_HAL.h"

static float pmsm_cil_theta_mech_rad;

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
	pmsm_cil_theta_mech_rad = 0.0f;
	return uz_pmsmModel_init(pmsm_cil_config);
}

void reset_uz_pmsm_cil(uz_pmsmModel_t* pmsm)
{
    uz_pmsmModel_reset(pmsm);
    pmsm_cil_theta_mech_rad = 0.0f;
}

struct uz_pmsm_measurement_values pmsm_cil_get_control_measurements(
    struct uz_pmsmModel_outputs_t outputs,
    struct uz_pmsmModel_inputs_t applied_inputs, float dc_link_voltage_V,
    float sample_time_s)
{
    uz_assert(sample_time_s > 0.0f);
    /* The dq IP has no rotor-angle output. Integrate its signed mechanical
     * speed at the ISR rate to emulate an ideal encoder for this CIL instance.
     */
    pmsm_cil_theta_mech_rad = uz_signals_wrap(
        pmsm_cil_theta_mech_rad + outputs.omega_mech_1_s * sample_time_s,
        2.0f * UZ_PIf);
    float theta_el_rad = uz_signals_wrap(
        pmsm_cil_theta_mech_rad * pmsm_cil_config.polepairs, 2.0f * UZ_PIf);
    uz_3ph_dq_t currents = {.d = outputs.i_d_A, .q = outputs.i_q_A, .zero = 0.0f};
    uz_3ph_dq_t voltages = {.d = applied_inputs.v_d_V, .q = applied_inputs.v_q_V, .zero = 0.0f};
    struct uz_pmsm_measurement_values measurements = {
        .i_abc_in_A = uz_transformation_3ph_dq_to_abc(currents, theta_el_rad),
        .v_abc_in_V = uz_transformation_3ph_dq_to_abc(voltages, theta_el_rad),
        .omega_mech_rad_per_sec = outputs.omega_mech_1_s,
        .theta_mech = pmsm_cil_theta_mech_rad,
        .v_dc_in_V = dc_link_voltage_V,
        .i_dc_in_A = 0.0f
    };
    return measurements;
}
