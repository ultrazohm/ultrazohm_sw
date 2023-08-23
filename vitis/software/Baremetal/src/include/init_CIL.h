#pragma once
#include "../uz/uz_global_configuration.h"
#include "../IP_Cores/uz_pmsm_model_9ph_dq/uz_pmsm_model9ph_dq.h"
#include "../IP_Cores/uz_pmsm9ph_transformation/uz_pmsm9ph_transformation.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"

#define UDC_CIL 250.0f

struct CIL_objects{
	uz_inverter_3ph_t* inv1;
	uz_inverter_3ph_t* inv2;
	uz_inverter_3ph_t* inv3;
	uz_pmsm9ph_transformation_t* transformation;
	uz_pmsm_model9ph_dq_t* pmsm;
};

struct CIL_objects init_all_objects_CIL(void);
