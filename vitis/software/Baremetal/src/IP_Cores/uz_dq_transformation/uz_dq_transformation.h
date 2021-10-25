#ifndef UZ_DQ_TRANSFORMATION_H
#define UZ_DQ_TRANSFORMATION_H

#include "../../uz/uz_Transformation/uz_Transformation.h"

typedef struct uz_dq_transformation_t uz_dq_transformation_t;

struct uz_dq_transformation_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float theta_offset; /**< Offset of encoder to alpha-axis */
};

uz_dq_transformation_t* uz_dq_transformation_init(struct uz_dq_transformation_config_t config);

struct uz_dq_t uz_dqTransformation_get_id_iq(uz_dq_transformation_t* self);

#endif // UZ_DQ_TRANSFORMATION_H
