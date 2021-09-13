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


#endif // UZ_INCREMENTALENCODER_H
