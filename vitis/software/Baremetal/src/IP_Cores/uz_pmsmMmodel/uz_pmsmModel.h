#ifndef UZ_PMSMMODEL_H
#define UZ_PMSMMODEL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct uz_pmsmModel_t uz_pmsmModel_t;

struct uz_pmsmModel_config_t
{
    uint32_t base_address;
    uint32_t ip_core_frequency_Hz;
    float polepairs;
    float r_1;
    float L_d;
    float L_q;
    float psi_pm;
    float friction_coefficient;
    float coloumb_friction_constant;
    float inertia;
    bool simulate_mechanical_system;
};

struct uz_pmsmModel_outputs_t
{

    float i_d_A;
    float i_q_A;
    float torque_Nm;
    float omega_mech_1_s;
};

struct uz_pmsmModel_inputs_t
{
    float u_d_V;
    float u_q_V;
    float load_torque;
    float omega_mech_1_s;
};

uz_pmsmModel_t *uz_pmsmModel_init(struct uz_pmsmModel_config_t config);

// Struct API
void uz_pmsmModel_set_inputs(uz_pmsmModel_t *self,struct uz_pmsmModel_inputs_t inputs);
struct uz_pmsmModel_outputs_t uz_pmsmModel_get_outputs(uz_pmsmModel_t *self);

float uz_pmsmModel_get_i_d(uz_pmsmModel_t *self);
float uz_pmsmModel_get_i_q(uz_pmsmModel_t *self);
float uz_pmsmModel_get_torque(uz_pmsmModel_t *self);
void uz_pmsmModel_set_u_d(uz_pmsmModel_t *self, float u_d);
void uz_pmsmModel_set_u_q(uz_pmsmModel_t *self, float u_q);
void uz_pmsmModel_set_omega_mech(uz_pmsmModel_t *self,float omega_mech_1_s);
float uz_pmsmModel_get_omega_mech(uz_pmsmModel_t *self);
void uz_pmsmModel_set_load_torque(uz_pmsmModel_t *self, float load_torque);
void uz_pmsmModel_reset(uz_pmsmModel_t *self);
#endif // UZ_PMSMMODEL_H
