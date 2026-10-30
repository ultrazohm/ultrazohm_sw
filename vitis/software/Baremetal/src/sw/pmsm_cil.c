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
  .inertia = 0.001,
  .coulomb_friction_constant = 0.01f,
  .friction_coefficient = 0.001f
};

uz_pmsmModel_t* initialize_uz_pmsm_cil(void) {
	return uz_pmsmModel_init(pmsm_cil_config);
}
