#include "uz_CurrentControl_Kp_id_adjustment.h"
#include "../uz_global_configuration.h"
#if UZ_CURRENTCONTROL_KP_ID_ADJUSTMENT_MAX_INSTANCES > 0U
#include "CurrentControl_Kp_id_adjustment_ert_rtw/CurrentControl_Kp_id_adjustment.h"
#include "../uz_HAL.h"

struct uz_CurrentControl_Kp_id_adjustment_t {
    bool is_ready;
    ExtY output;
    ExtU input;
    RT_MODEL modelData;
    RT_MODEL *PtrToModelData; 
};

float Kp_id;
static uint32_t instance_counter = 0U;
static uz_CurrentControl_Kp_id_adjustment_t instances[UZ_APPROXIMATE_FLUX_D_MAX_INSTANCES] = { 0 };

static uz_CurrentControl_Kp_id_adjustment_t *uz_CurrentControl_Kp_id_adjustment_allocation(void);

static uz_CurrentControl_Kp_id_adjustment_t *uz_CurrentControl_Kp_id_adjustment_allocation(void){
    uz_assert(instance_counter < UZ_APPROXIMATE_FLUX_D_MAX_INSTANCES);
    uz_CurrentControl_Kp_id_adjustment_t *self = &instances[instance_counter];
    uz_assert(self->is_ready == false);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_CurrentControl_Kp_id_adjustment_t* uz_CurrentControl_Kp_id_adjustment_init(float dead_time_reciprocal){
    uz_CurrentControl_Kp_id_adjustment_t* self = uz_CurrentControl_Kp_id_adjustment_allocation();
    self->PtrToModelData=&self->modelData;
    self->PtrToModelData->inputs=&self->input;
    self->PtrToModelData->outputs=&self->output;
    self->input.dead_time_reciprocal= dead_time_reciprocal;
    return(self);
}

float uz_CurrentControl_Kp_id_adjustment_step(uz_CurrentControl_Kp_id_adjustment_t* self, uz_3ph_dq_t i_reference_Ampere,uz_3ph_dq_t i_actual_Ampere,float psid_reference,float psid_actual){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->input.id_ref=i_reference_Ampere.d;
    self->input.id_mea= i_actual_Ampere.d;
    self->input.psi_d_ref= psid_reference;
    self->input.psi_d_mea= psid_actual;
    CurrentControl_Kp_id_adjustment_step(self->PtrToModelData);
    Kp_id = self->output.Kp_id;
    return(Kp_id);
}

#endif

