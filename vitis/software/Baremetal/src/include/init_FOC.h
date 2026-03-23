#pragma once

uz_CurrentControl_t* init_FOC_DUT(void);
uz_CurrentControl_t* init_FOC_Load(void);
uz_SetPoint_t* init_SetPoint_Load(void);
uz_SpeedControl_t* init_SpeedControl_Load(void);
uz_pmsmModel_t* init_pmsmModel(void);
uz_approximate_flux_t* init_FluxApproximation_DUT(void);
uz_LUT_1D_t* init_LUT_id(void);
uz_LUT_1D_t* init_LUT_iq(void);
