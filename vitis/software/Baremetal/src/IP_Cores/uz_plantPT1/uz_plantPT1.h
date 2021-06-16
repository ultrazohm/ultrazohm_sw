#ifndef UZ_PLANTPT1_H
#define UZ_PLANTPT1_H

typedef struct uz_plantPT1_t uz_plantPT1_t;

struct uz_plantPT1_config_t
{
    uint32_t base_address;
    uint32_t ip_core_frequency_Hz;
};

uz_plantPT1_t *uz_plantPT1_init(struct uz_plantPT1_config_t config);
void uz_plantPT1_reset_integrator(uz_plantPT1_t *self);
void uz_plantPT1_set_input(uz_plantPT1_t *self, float input_value);
void uz_plantPT1_set_gain(uz_plantPT1_t *self, float gain);
void uz_plantPT1_set_time_constant(uz_plantPT1_t *self, float time_constant);
float uz_plantPT1_read_output(uz_plantPT1_t *self);

#endif // UZ_PLANTPT1_H
