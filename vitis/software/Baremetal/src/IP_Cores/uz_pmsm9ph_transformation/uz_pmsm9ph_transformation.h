#pragma once

#include "../../uz/uz_Transformation/uz_Transformation.h"

typedef struct uz_pmsm9ph_transformation_t uz_pmsm9ph_transformation_t;

struct uz_pmsm9ph_config_t{
    uint32_t base_address;
    uint32_t ip_core_frequency_Hz;
};

uz_pmsm9ph_transformation_t* uz_pmsm9ph_transformation_init(struct uz_pmsm9ph_config_t config);

uz_9ph_abc_t uz_pmsm9ph_transformation_get_currents(uz_pmsm9ph_transformation_t* self);
float uz_pmsm9ph_transformation_get_theta_el(uz_pmsm9ph_transformation_t* self);