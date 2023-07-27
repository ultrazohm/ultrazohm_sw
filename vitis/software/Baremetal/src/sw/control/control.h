#pragma once
#include "../../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../../uz/uz_subspace_resonant_control/uz_subspace_resonant_control.h"
#include "../../uz/uz_global_configuration.h"
#include "../../uz/uz_Transformation/uz_Transformation.h"
#include "../../uz/uz_math_constants.h"

// general defines and limits
#define SAMPLETIME (1.0f/UZ_PWM_FREQUENCY)
#define DQ_SYSTEM_LIMIT 10.0f
#define ADDITIONAL_SYSTEM_LIMIT 2.5f//10.0f
#define RESONANT_ANTIWINDUP_GAIN 10.0f
#define PROGNOSE_DC_LIMIT 250.0f
#define MODULATION_INDEX 1.0f/sqrtf(3)

enum controller_type {reset, PI_0, PI_PI, PI_R, PIR_PIR};

#include "../../globalData.h"
#include "PI_0.h"
#include "PI_PI.h"
#include "PI_R.h"
#include "PIR_PIR.h"


// testbench data
#define PHASE_PSI_PM_3 UZ_PIf
#define PHASE_PSI_PM_5 UZ_PIf
#define PHASE_PSI_PM_7 UZ_PIf/2.0f

void subspace_park_transform(DS_Data* Data);
