#ifndef UZ_INCREMENTALENCODER_H
#define UZ_INCREMENTALENCODER_H
#include <stdint.h>

typedef struct uz_incrementalEncoder_t uz_incrementalEncoder_t;

struct uz_incrementalEncoder_config{
    uint32_t base_address;
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */
    uint32_t increments_per_turn_mech;
    float OmegaPerOverSample_in_rpm;
    uint32_t drive_pole_pair;
};

uz_incrementalEncoder_t* uz_incrementalEncoder_init(struct uz_incrementalEncoder_config config);
float uz_incrementalEncoder_get_omega(uz_incrementalEncoder_t* self);
float uz_incrementalEncoder_get_theta_el(uz_incrementalEncoder_t* self);
uint32_t uz_incrementalEncoder_get_position(uz_incrementalEncoder_t* self);

#endif // UZ_INCREMENTALENCODER_H
