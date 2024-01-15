#ifndef UZ_PARAMETERID_RS_H
#define UZ_PARAMETERID_RS_H


typedef struct uz_parameterid_rs_t uz_parameterid_rs_t;

struct uz_parameterid_rs_config_t
{
    float n_start;
    float n_end;
    float n_steps;
    float i_start;
    float i_end;
    float i_steps;
};

struct uz_parameterid_rs_increments_t
{
    float n_increment;
    float i_increment;

};

uz_parameterid_rs_t *uz_parameterid_rs_init(struct uz_parameterid_rs_config_t initial_config);
struct uz_parameterid_rs_config_t uz_parameterid_rs_get_current_config(uz_parameterid_rs_t* self);
struct uz_parameterid_rs_increments_t uz_parameterid_rs_get_current_increments(uz_parameterid_rs_t* self);



#endif // UZ_PARAMETERID_RS_H
