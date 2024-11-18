#pragma once
#include "../IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"
#include "xparameters.h"
#include "../uz/uz_approximate_flux/uz_approximate_flux.h"
#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_CurrentControl/uz_static_nonlinear_decoupling.h"

uz_pmsmModel_t * uz_init_pmsm_model(void);
uz_approximate_flux_t* uz_init_approximate_flux(void);
uz_CurrentControl_t* uz_init_CC(void);
