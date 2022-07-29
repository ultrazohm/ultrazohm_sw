#pragma once

#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

uz_9ph_abc_t uz_pmsm9ph_transformation_hw_read_currents(uint32_t base_address);
void uz_pmsm9ph_transformation_hw_trigger_output_strobe(uint32_t base_address);
float uz_pmsm9ph_transformation_hw_read_theta_el(uint32_t base_address);