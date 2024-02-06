#include "uz_pmsm_linear.h"

#include "../uz_global_configuration.h"
#if UZ_PMSM_LINEAR_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_pmsm_linear.h"
#include "../uz_integrator/uz_integrator.h"

struct uz_pmsm_linear_t {
    bool is_ready;
    uz_3ph_dq_t i;
    uz_3ph_dq_t phi_k;
    uz_3ph_dq_t phi_k_1;
    float R;
    float ts;
    float psi_pm;
    float L_d;
    float L_q;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_linear_t instances[UZ_PMSM_LINEAR_MAX_INSTANCES] = { 0 };

static uz_pmsm_linear_t* uz_pmsm_linear_allocation(void);

static uz_pmsm_linear_t* uz_pmsm_linear_allocation(void){
    uz_assert(instance_counter < UZ_PMSM_LINEAR_MAX_INSTANCES);
    uz_pmsm_linear_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_pmsm_linear_t* uz_pmsm_linear_init(float R, float L_d, float L_q, float ts) {
    uz_pmsm_linear_t* self = uz_pmsm_linear_allocation();
    uz_pmsm_linear_reset(self);
    uz_assert(R>0.0f);
    uz_assert(ts>0.0f);
    uz_assert(L_d>0.0f);
    uz_assert(L_q>0.0f);
    self->R=R;
    self->L_d=L_d;
    self->L_q=L_q;
    self->ts=ts;
    return (self);
}

uz_3ph_dq_t uz_pmsm_linear_step(uz_pmsm_linear_t *self, uz_3ph_dq_t v, float omega_el)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_3ph_dq_t i_k = {0.0f};
    i_k.d = (self->phi_k.d - self->psi_pm) / self->L_d;
    i_k.q = (self->phi_k.q) / self->L_q;

    float dphi_d_dt = v.d - self->R * i_k.d + omega_el * self->phi_k.q;
    float dphi_q_dt = v.q - self->R * i_k.q - omega_el * self->phi_k.d;
    self->phi_k_1.d = uz_integrator_eulerforward(dphi_d_dt, self->phi_k.d, self->ts, false);
    self->phi_k_1.q = uz_integrator_eulerforward(dphi_q_dt, self->phi_k.q, self->ts, false);
    self->i.d = (self->phi_k.d - self->psi_pm) / self->L_d;
    self->i.q = (self->phi_k.q) / self->L_q;
    self->phi_k.d = self->phi_k_1.d;
    self->phi_k.q = self->phi_k_1.q;
    return self->i;
}


void uz_pmsm_linear_reset(uz_pmsm_linear_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->phi_k_1.d=0.0f; 
    self->phi_k_1.q=0.0f; 
    self->i.d=0.0f;  
    self->i.q=0.0f;  
    self->phi_k.d=0.0f;
    self->phi_k.q=0.0f;
}

#endif