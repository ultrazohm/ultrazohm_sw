#pragma once

uz_CurrentControl_t* init_FOC(void);
uz_pmsmModel_t* init_pmsmModel(void);
uz_approximate_flux_t* init_FluxApproximation(void);
uz_LUT_1D_t* init_LUT_CIL_current_angle(void);
uz_LUT_1D_t* init_LUT_CIL_Is(void);
uz_LUT_1D_t* init_LUT_bench_current_angle(void);
uz_LUT_1D_t* init_LUT_bench_Is(void);
