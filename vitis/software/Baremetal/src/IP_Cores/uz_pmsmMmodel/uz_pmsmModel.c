#define UZ_PMSMMODEL_MAX_INSTANCES 10U
#if UZ_PMSMMODEL_MAX_INSTANCES >0U
#include "uz_pmsmModel.h"
#include "uz_pmsmModel_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

struct uz_pmsmModel_t{
    bool is_ready;
    struct uz_pmsmModel_config_t config;
        float i_d_A;
    float i_q_A;
    float torque_Nm;
    float omega_mech_1_s;
};

static size_t instance_counter=0U;
static uz_pmsmModel_t instances[UZ_PMSMMODEL_MAX_INSTANCES]={0};

static uz_pmsmModel_t *uz_pmsmModel_allocation(void);

static uz_pmsmModel_t *uz_pmsmModel_allocation(void){
    uz_assert(instance_counter < UZ_PMSMMODEL_MAX_INSTANCES);
    uz_pmsmModel_t *self=&instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready=true;
    return(self);
}

uz_pmsmModel_t *uz_pmsmModel_init(struct uz_pmsmModel_config_t config){
    uz_assert_not_zero(config.base_address);
    uz_assert_not_zero(config.ip_core_frequency_Hz);
    uz_pmsmModel_t *self=uz_pmsmModel_allocation();
    self->config=config;
    return(self);
}

float uz_pmsmModel_get_i_d(uz_pmsmModel_t *self){
    uz_assert_not_NULL(self);
    return uz_pmsmModel_hw_read_i_d(self->config.base_address);
}

float uz_pmsmModel_get_i_q(uz_pmsmModel_t *self){
    uz_assert_not_NULL(self);
    return uz_pmsmModel_hw_read_i_q(self->config.base_address);
}

float uz_pmsmModel_get_torque(uz_pmsmModel_t *self){
    uz_assert_not_NULL(self);
    return uz_pmsmModel_hw_read_torque(self->config.base_address);
}

void uz_pmsmModel_set_u_d(uz_pmsmModel_t *self, float u_d){
    uz_assert_not_NULL(self);
    uz_pmsmModel_hw_write_u_d(self->config.base_address,u_d);
}

void uz_pmsmModel_set_u_q(uz_pmsmModel_t *self, float u_q){
    uz_assert_not_NULL(self);
    uz_pmsmModel_hw_write_u_q(self->config.base_address,u_q);
}

void uz_pmsmModel_set_omega_mech(uz_pmsmModel_t *self,float omega_mech_1_s){
    uz_assert_not_NULL(self);
    uz_pmsmModel_hw_write_omega_mech(self->config.base_address,omega_mech_1_s);
}

void uz_pmsmModel_reset(uz_pmsmModel_t *self){
    // Resets the model by writing 0.0f to all input registers
    // Then resets the integrators
    uz_pmsmModel_hw_write_omega_mech(self->config.base_address,0.0f);
    uz_pmsmModel_hw_write_u_d(self->config.base_address,0.0f);
    uz_pmsmModel_hw_write_u_q(self->config.base_address,0.0f);
    uz_pmsmModel_hw_write_reset(self->config.base_address,false);
    uz_sleep_useconds(1);
    uz_pmsmModel_hw_write_reset(self->config.base_address,true);
    uz_sleep_useconds(1);
    uz_pmsmModel_hw_write_reset(self->config.base_address,false);
}


#endif