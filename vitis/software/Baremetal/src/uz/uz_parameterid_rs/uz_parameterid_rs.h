#ifndef UZ_PARAMETERID_RS_H
#define UZ_PARAMETERID_RS_H

typedef struct uz_parameterid_rs_t uz_parameterid_rs_t;

struct uz_parameterid_rs_config_t
{
    float omega_start;
    float omega_end;
    float omega_increment;
};

uz_parameterid_rs_t *uz_parameterid_rs_init(struct uz_parameterid_rs_config_t initial_config);
struct uz_parameterid_rs_config_t uz_parameterid_rs_get_current_config(uz_parameterid_rs_t *self);

#endif // UZ_PARAMETERID_RS_H
