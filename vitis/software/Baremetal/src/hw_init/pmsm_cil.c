#include "../include/pmsm_cil.h"
#include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
#include "xparameters.h"
#include "../main.h"
#include "../uz/uz_CurrentControl/uz_CurrentControl.h"

const struct uz_PMSM_t Beckhoff_AM8141 = {
      .R_ph_Ohm = 0.51,
      .Ld_Henry = 0.002f,
      .Lq_Henry = 0.002f,
      .Psi_PM_Vs = 0.042f,
	  .polePairs = 4.0f,
	  .I_max_Ampere = 12.0f,
	  .J_kg_m_squared = 0.000108
    };

struct uz_pmsmModel_config_t pmsm_ip_config={
           .base_address=XPAR_UZ_PMSM_MODEL_0_BASEADDR,
           .ip_core_frequency_Hz=100000000,
           .simulate_mechanical_system = false,
           .r_1 = Beckhoff_AM8141.R_ph_Ohm,
           .L_d = Beckhoff_AM8141.Ld_Henry,
           .L_q = Beckhoff_AM8141.Lq_Henry,
           .psi_pm = Beckhoff_AM8141.Psi_PM_Vs,
           .polepairs = Beckhoff_AM8141.polePairs,
           .inertia = Beckhoff_AM8141.J_kg_m_squared,
           .coulomb_friction_constant = 0.01f,
           .friction_coefficient = 0.001f};

uz_pmsmModel_t* init_pmsm_cil(void) {
   	return(uz_pmsmModel_init(pmsm_ip_config));
   }
